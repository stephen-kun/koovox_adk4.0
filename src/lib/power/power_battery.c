/****************************************************************************
Copyright (C) Cambridge Silicon Radio Ltd. 2005

FILE NAME
    power_battery.c

DESCRIPTION
    This file contains the battery voltage monitoring specific functionality

NOTES
    Certain assumptions have been made on the assignment of the analog input
    signals:
    
    VBAT = AIO *   Ra
                 -------
                 Ra + Rb
    
    Where the divisor ratio of Ra and Rb is configured from persistent store
*/


/****************************************************************************
    Header files
*/
#include "power.h"
#include "power_private.h"
#include "power_battery.h"
#include "power_init.h"


/****************************************************************************
NAME    
    powerBatterySendVoltageInd
    
DESCRIPTION
    Call to send the battery voltage and its level to App.
*/
static void powerBatteryQueueVoltageInd(uint8 level)
{
    /* Queue next battery voltage indication if configured to do so */
    uint8 notify_period = power->config.vbat.limits[level].notify_period;
    PRINT(("POWER: Queue VBAT Notification in %d seconds\n", (POWER_PERIOD_SCALE * notify_period)));
    MessageCancelFirst(&power->task, POWER_INTERNAL_VBAT_NOTIFY_REQ);
    /* notify_period interval is in multiples of POWER_PERIOD_SCALE (10s) */
    if(notify_period) MessageSendLater(&power->task, POWER_INTERNAL_VBAT_NOTIFY_REQ, 0, D_SEC(POWER_PERIOD_SCALE * notify_period));
}


/****************************************************************************
NAME    
    powerBatterySendVoltageInd
    
DESCRIPTION
    Call to send the battery voltage and its level to App.
*/
void powerBatterySendVoltageInd(void)
{
    MAKE_POWER_MESSAGE(POWER_BATTERY_VOLTAGE_IND);
    PowerBatteryGetVoltage(&message->vbat);
    powerBatteryQueueVoltageInd(message->vbat.level);
    MessageSend(power->clientTask, POWER_BATTERY_VOLTAGE_IND, message);
}


/****************************************************************************
NAME
    powerBatterySendTemperatureInd
    
DESCRIPTION
    Call to send the battery temperature and its level to App.
*/
static void powerBatterySendTemperatureInd(void)
{
    MAKE_POWER_MESSAGE(POWER_BATTERY_TEMPERATURE_IND);
    PowerBatteryGetTemperature(&message->vthm);
    MessageSend(power->clientTask, POWER_BATTERY_TEMPERATURE_IND, message);
}


/****************************************************************************
NAME
    powerBatteryGetVoltageLevel
    
DESCRIPTION
    This function is called to decide the battery level based on most recent
    battery voltage measurement.
    
RETURNS
    uint8
*/
static uint8 powerBatteryGetVoltageLevel(void)
{
    uint8  level;
    
    for(level=0; level < POWER_MAX_VBAT_LIMITS; level++)
    {
        uint16 limit = power->config.vbat.limits[level].limit;
        if(limit == POWER_VBAT_LIMIT_END || power->vbat < (limit * POWER_VSCALE))
            break;
    }
    
    return(level);
}


/****************************************************************************
NAME
    powerBatteryGetTemperatureLevel
    
DESCRIPTION
    This function is called to decide the temperature level based on most 
    recent temperature measurement.
    
RETURNS
    uint8
*/
static uint8 powerBatteryGetTemperatureLevel(void)
{
    uint8 level;
    
    for(level=0; level < POWER_MAX_VTHM_LIMITS; level++)
    {
        uint16 limit = power->config.vthm.limits[level];
        if(limit == POWER_VTHM_LIMIT_END || power->vthm < limit)
            break;
    }
    return(level);
}

/****************************************************************************
NAME    
    powerBatterySmoothVoltageReading
    
DESCRIPTION
    Using double exponential smoothing to average out the current
	battery voltage reading.
*/
static void powerBatterySmoothVoltageReading(uint16 reading)
{
	/* Until the charger state is STANDBY, adcsel_vdd_bat or adcsel_vdd_sense
	   readings will be unusually low, e.g. ~65mV. This is not a value that
	   could be returned from a real battery, so don't use these readings for
	   calculating the average. */
	if (power->vbat == POWER_DEFAULT_VOLTAGE
		|| power->vbat <= 100)
	{
		power->vbat = reading;
		power->vbat_trend = 0;
	}
	else
	{
		int16 old = power->vbat;
		power->vbat = ((9 * old) + (1 * (power->vbat_trend + reading)) + 5) / 10;
		power->vbat_trend = (power->vbat_trend + (int16)(power->vbat - old)) / 2;
	}
	
	PRINT(("POWER: vbat %u trend %d reading %u\n", 
		power->vbat, power->vbat_trend, reading));
}

/****************************************************************************
NAME    
    powerBatteryHandleVoltageReading
    
DESCRIPTION
    Calculate current battery voltage and check to determine the battery level.
    Both battery voltage and level are sent to App and the App decides the 
    further operation base on the reported results.
*/
void powerBatteryHandleVoltageReading(uint16 reading)
{
    PRINT(("POWER: VBAT old - %u(mV) new - %u(mV) chg_state %x\n", power->vbat, reading, power->chg_state));
    
    if(POWER_INIT_GET(power_init_vbat))
    {
        uint8 old_level = powerBatteryGetVoltageLevel();
        uint8 new_level;

		powerBatterySmoothVoltageReading(reading);

        new_level = powerBatteryGetVoltageLevel();

        /* Send indication if the battery level changed */
        if(new_level != old_level)
            powerBatterySendVoltageInd();
    }
    else
    {
		/* Initial reading */
		powerBatterySmoothVoltageReading(reading);
		powerBatteryQueueVoltageInd(powerBatteryGetVoltageLevel());
		POWER_INIT_SET(power_init_vbat);
    }
    PRINT(("POWER: VBAT %u(mV)\n", power->vbat));
}


/****************************************************************************
NAME
    powerBatteryHandleTemperatureReading
    
DESCRIPTION
    Calculate the current battery temperature
*/
void powerBatteryHandleTemperatureReading(uint16 reading)
{
    uint8 old_level;
    /* Get previous level */
    PRINT(("POWER: Old Vthm %u(%s)\n", power->vthm, power->config.vthm.raw_limits ? "ADC counts" : "mV"));
    old_level = powerBatteryGetTemperatureLevel();
    /* Update reading */
    power->vthm = reading;
    PRINT(("POWER: New Vthm %u(%s)\n", power->vthm, power->config.vthm.raw_limits ? "ADC counts" : "mV"));
    
    if(POWER_INIT_GET(power_init_vthm))
    {
        /* If threshold has been crossed inform the client task */
        uint8 new_level = powerBatteryGetTemperatureLevel();
        if(new_level != old_level) 
            powerBatterySendTemperatureInd();
    }
    else
    {
        /* Initial reading of VTHM has been taken */
        POWER_INIT_SET(power_init_vthm);
    }
}


/****************************************************************************
NAME    
    PowerBatteryGetVoltage
    
DESCRIPTION
    Call this function to get the current battery voltage and its level
    
RETURN
    bool
*/
bool PowerBatteryGetVoltage(voltage_reading* vbat)
{
    if(POWER_INIT_GET(power_init_vbat))
    {
        vbat->voltage = power->vbat;
        vbat->level = powerBatteryGetVoltageLevel();
        return TRUE;
    }
    return FALSE;
}


/****************************************************************************
NAME
    PowerBatteryGetTemperature
    
DESCRIPTION
    Call this function to get the current battery temperature in 'C
    
RETURN
    bool
*/
bool PowerBatteryGetTemperature(voltage_reading* vthm)
{
    if(POWER_INIT_GET(power_init_vthm))
    {
        vthm->voltage = power->vthm;
        vthm->level = powerBatteryGetTemperatureLevel();
        return TRUE;
    }
    return FALSE;
}
