/******************************************************************************
Copyright Cambridge Silicon Radio Limited 2014 - 2015.
Part of ADK 4.0
 
FILE NAME
    csr_multi_channel_gain.c
 
DESCRIPTION
    Contains functions related to setting/getting of multi-channel gains.
*/

#include "csr_multi_channel_plugin.h"
#include "csr_multi_channel_private.h"

#ifdef ANC
#include "anc.h"
#endif

#include <csr_i2s_audio_plugin.h>
#include <print.h>
#include <stdlib.h>
#include <codec.h>

static uint16 system_gain_from_master(int16 master)
{
    /* Convert dB master volume to DAC based system volume */
    int16 system = (CODEC_STEPS + (master / DB_TO_DAC));
    
    /* DAC gain only goes down to -45dB, DSP volume control goes to -60dB */
    if(system < 0)
        system = 0;
    
    return (uint16)system;
}

static i2s_out_t get_i2s_chan(multi_channel_out_t mch_out)
{
    audio_output_hardware_instance_t inst = config->mapping[mch_out].endpoint.instance;
    audio_output_channel_t chan = config->mapping[mch_out].endpoint.channel;
    
    if(inst == audio_output_hardware_instance_0)
    {
        if(chan == audio_output_channel_a)
            return i2s_out_1_left;
        if(chan == audio_output_channel_b)
            return i2s_out_1_right;
    }
    else if(inst == audio_output_hardware_instance_1)
    {
        if(chan == audio_output_channel_a)
            return i2s_out_2_left;
        if(chan == audio_output_channel_b)
            return i2s_out_2_right;
    }
    
    /* Catch invalid configuration with panic */
    Panic();
    return i2s_out_1_left;
}

static int16 get_trim(multi_channel_out_t mch_out, bool skip_i2s_trim)
{
    audio_output_hardware_type_t type = config->mapping[mch_out].endpoint.type;
    
    if(skip_i2s_trim && type == audio_output_type_i2s)
        return 0;
    
    return config->mapping[mch_out].volume_trim;
}

static void get_all_trims(const multi_channel_group_t group, bool skip_i2s_trim,
                          multi_channel_gain_t* gain_info)
{
    if(group == multi_channel_group_main)
    {
        gain_info->trim.main.primary_left    = get_trim(mch_out_primary_left, skip_i2s_trim);
        gain_info->trim.main.primary_right   = get_trim(mch_out_primary_right, skip_i2s_trim);
        gain_info->trim.main.secondary_left  = get_trim(mch_out_secondary_left, skip_i2s_trim);
        gain_info->trim.main.secondary_right = get_trim(mch_out_secondary_right, skip_i2s_trim);
        gain_info->trim.main.wired_sub       = get_trim(mch_out_wired_sub, skip_i2s_trim);
    }
    else if(group == multi_channel_group_aux)
    {
        gain_info->trim.aux.aux_left  = get_trim(mch_out_aux_left, skip_i2s_trim);
        gain_info->trim.aux.aux_right = get_trim(mch_out_aux_right, skip_i2s_trim);
    }
}

void CsrMultiChanGainGetDigital(const multi_channel_group_t group, 
                                const int16 master_gain, const int16 tone_gain,
                                multi_channel_gain_t* gain_info)
{
    hybrid_gains_t hybrid;
    
    PRINT(("CsrMultiChanGainGetDigital  "));
    PRINT(("%s: ", (group == multi_channel_group_main ? "Main" : " Aux")));
    PRINT(("master gain %d tone %d ", master_gain, tone_gain));
    PRINT(("%s", (gain_info == NULL ? "NULL info" : "")));
    
    if(config == NULL || group >= multi_channel_group_all || gain_info == NULL)
    {
        Panic();
        return;
    }
    
    gain_info->common.tone = tone_gain;
    
    switch(config->gain_type[group])
    {
        case multi_channel_gain_hardware:
            /* Tell the DSP the current hardware gain */
            gain_info->common.system = system_gain_from_master(master_gain);
            /* Set the digital gain to 0dB */
            gain_info->common.master = MAXIMUM_DIGITAL_VOLUME_0DB;
            /* Get all trims, excluding I2S (as I2S trims are handled in hw) */
            get_all_trims(group, TRUE, gain_info);
        break;
        
        case multi_channel_gain_digital:
            /* Ensure DSP is told the correct fixed hardware gain */
            gain_info->common.system = system_gain_from_master(config->fixed_hw_gain);
            /* Apply master gain in DSP */
            gain_info->common.master = master_gain;
            /* Get all trims */
            get_all_trims(group, FALSE, gain_info);
        break;
        
        case multi_channel_gain_hybrid:
            /* Use existing codec function to obtain hybrid values */
            CodecCalcHybridValues(&hybrid, master_gain);
            /* Ensure DSP is told the correct hardware gain */
            gain_info->common.system = hybrid.dac_gain;
            /* Apply master gain in DSP */
            gain_info->common.master = hybrid.dsp_db_scaled;
            /* Get all trims */
            get_all_trims(group, FALSE, gain_info);
        break;
        
        default:
            Panic();
            return;
    }
    
    PRINT(("applied gain %d\n", gain_info->common.master));
}

void CsrMultiChanGainGetDigitalOnly(const multi_channel_group_t group, 
                                    const int16 master_gain, const int16 tone_gain,
                                    multi_channel_gain_t* gain_info)
{
    PRINT(("CsrMultiChanGainGetDigitalOnly  "));
    PRINT(("%s: ", (group == multi_channel_group_main ? "Main" : " Aux")));
    PRINT(("master gain %d tone %d ", master_gain, tone_gain));
    PRINT(("%s\n", (gain_info == NULL ? "NULL info" : "")));
    
    if(config == NULL || group >= multi_channel_group_all || gain_info == NULL)
    {
        Panic();
        return;
    }
    
    /* Tell DSP the overall system gain, master gain and tone gain - typically 
       this is used to sync volume changes on TWS. The DSP will send this 
       information back to the VM at the same time on both TWS devices*/
    gain_info->common.system = system_gain_from_master(master_gain);
    gain_info->common.master = master_gain;
    gain_info->common.tone   = tone_gain;
    
    /* Tell the DSP all trims, again this information is used for TWS 
       synchronised volume changes*/
    get_all_trims(group, FALSE, gain_info);
}

static void set_hardware_gain(multi_channel_out_t mch_out, int16 hardware_gain, int16 trim)
{
#ifdef ANC

    /* If using ANC then only DAC output type allowed. Setting the gain also needs
       to be done using the ANC library */
    if ((config->mapping[mch_out].endpoint.type == audio_output_type_dac) &&
        (hardware_gain != DIGITAL_VOLUME_MUTE))
    {
        /* If not muting then apply the ANC specific gain */
        AncApplyDacGain();
        return;
    }

#endif /* ANC */

    switch(config->mapping[mch_out].endpoint.type)
    {
        case audio_output_type_dac:
        {
            Sink sink = csrMultiChanGetSink(mch_out);
            /* Calculate system value corresponding to the hardware gain */
            uint16 system_gain = system_gain_from_master(hardware_gain);
            PanicFalse(SinkConfigure(sink, STREAM_CODEC_OUTPUT_GAIN, system_gain));
        }
        break;
        
        case audio_output_type_i2s:
        {
            /* Include trim in hardware setting (only for i2s) */
            hardware_gain += trim;
            CsrSetVolumeI2SChannel(get_i2s_chan(mch_out), hardware_gain, TRUE);
        }
        break;
        
        default:
            /* Ignore unrecognised type */
        break;
    }
}

/* If gain_info is NULL get trim from config->mapping, otherwise get it from gain_info */
#define get_trim(gain_info, group, chan) (gain_info ? gain_info->trim.group.chan : config->mapping[mch_out_##chan].volume_trim)

/* If I2S trim not enabled return 0, otherwise get the trim using get_trim */
#define get_trim_if_enabled(inc_i2s_trim, gain_info, group, chan) (inc_i2s_trim ? get_trim(gain_info, group, chan) : 0)

static void set_all_hardware_gains(const multi_channel_group_t group,
                                   const int16 hardware_gain, 
                                   const bool inc_i2s_trim,
                                   const multi_channel_gain_t* gain_info)
{
    PRINT(("applied hw gain %d ", system_gain_from_master(hardware_gain)));
    PRINT(("%s\n", (inc_i2s_trim ? "(+I2S trims)" : "")));
    
    if(group == multi_channel_group_main)
    {
        set_hardware_gain(mch_out_primary_left, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, main, primary_left));
        set_hardware_gain(mch_out_primary_right, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, main, primary_right));
        set_hardware_gain(mch_out_secondary_left, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, main, secondary_left));
        set_hardware_gain(mch_out_secondary_right, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, main, secondary_right));
        set_hardware_gain(mch_out_wired_sub, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, main, wired_sub));
    }
    else if(group == multi_channel_group_aux)
    {
        set_hardware_gain(mch_out_aux_left, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, aux, aux_left));
        set_hardware_gain(mch_out_aux_right, hardware_gain, get_trim_if_enabled(inc_i2s_trim, gain_info, aux, aux_right));
    }
}

void CsrMultiChanGainSetHardware(const multi_channel_group_t group,
                                 const int16 master_gain,
                                 const multi_channel_gain_t* gain_info)
{
    int16 hardware_gain;
    hybrid_gains_t hybrid;
    bool inc_i2s_trim = FALSE;
    
    PRINT(("CsrMultiChanGainSetHardware "));
    PRINT(("%s: ", (group == multi_channel_group_main ? "Main" : " Aux")));
    PRINT(("master gain %d ", master_gain));
    
    if(config == NULL || group >= multi_channel_group_all)
    {
        Panic();
        return;
    }
    
    switch(config->gain_type[group])
    {
        case multi_channel_gain_hardware:
            /* Apply master gain at hardware level */
            hardware_gain = master_gain;
            
            /* When using hardware gain (and not muting) I2S trims should be adjusted 
               to include the channel trim */
            inc_i2s_trim = (hardware_gain != DIGITAL_VOLUME_MUTE);
        break;
        
        case multi_channel_gain_digital:
            /* Master gain applied in DSP, set fixed gain at hardware level */
            hardware_gain = config->fixed_hw_gain;
        break;
        
        case multi_channel_gain_hybrid:
            /* Use codec function to obtain hybrid values */
            CodecCalcHybridValues(&hybrid, master_gain);
            /* Convert the DAC gain to dB/60 */
            hardware_gain = VolumeConvertDACGainToDB(hybrid.dac_gain);
        break;
        
        default:
            Panic();
            return;
    }
    
    set_all_hardware_gains(group, hardware_gain, inc_i2s_trim, gain_info);
}

void CsrMultiChanGainSetHardwareOnly(const multi_channel_group_t group,
                                     const int16 master_gain)
{
    /* When not muting I2S trims should be adjusted to include the channel trim */
    bool inc_i2s_trim = (master_gain != DIGITAL_VOLUME_MUTE);

    PRINT(("CsrMultiChanGainSetHardwareOnly "));
    PRINT(("%s: ", (group == multi_channel_group_main ? "Main" : " Aux")));
    PRINT(("master gain %d ", master_gain));
    
    if(config == NULL || group >= multi_channel_group_all)
    {
        Panic();
        return;
    }
    
    set_all_hardware_gains(group, master_gain, inc_i2s_trim, NULL);
}

multi_channel_group_gain_type_t CsrMultiChanGainGetType(const multi_channel_group_t group)
{
    if(config == NULL || group >= multi_channel_group_all)
    {
        Panic();
        return multi_channel_gain_invalid;
    }
    
    return config->gain_type[group];
}

void csrMultiChanGainMuteHardware(multi_channel_out_t mch_out)
{
    set_hardware_gain(mch_out, DIGITAL_VOLUME_MUTE, FALSE);
    PanicFalse(SinkConfigure(csrMultiChanGetSink(mch_out), STREAM_AUDIO_MUTE_ENABLE, TRUE));
}
