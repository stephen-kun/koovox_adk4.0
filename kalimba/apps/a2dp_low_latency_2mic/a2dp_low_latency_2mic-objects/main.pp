.linefile 1 "main.asm"
.linefile 1 "<command-line>"
.linefile 1 "main.asm"
.linefile 18 "main.asm"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 1
.linefile 9 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/stack.h" 1
.linefile 10 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/timer.h" 1
.linefile 14 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/timer.h"
   .CONST $timer.MAX_TIMER_HANDLERS 50;

   .CONST $timer.LAST_ENTRY -1;

   .CONST $timer.NEXT_ADDR_FIELD 0;
   .CONST $timer.TIME_FIELD 1;
   .CONST $timer.HANDLER_ADDR_FIELD 2;
   .CONST $timer.ID_FIELD 3;
   .CONST $timer.STRUC_SIZE 4;

   .CONST $timer.n_us_delay.SHORT_DELAY 10;
   .CONST $timer.n_us_delay.MEDIUM_DELAY 150;
.linefile 11 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/message.h" 1
.linefile 12 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/message.h"
.linefile 1 "C:/ADK4.0.0/kalimba/architecture/architecture.h" 1
.linefile 20 "C:/ADK4.0.0/kalimba/architecture/architecture.h"
.linefile 1 "C:/ADK4.0.0/kalimba/architecture/gordon.h" 1
.linefile 14 "C:/ADK4.0.0/kalimba/architecture/gordon.h"
   .CONST $FLASHWIN1_START 0xFFB000;
   .CONST $FLASHWIN1_SIZE 0x001000;
   .CONST $FLASHWIN2_START 0xFFC000;
   .CONST $FLASHWIN2_SIZE 0x001000;
   .CONST $FLASHWIN3_START 0xFFD000;
   .CONST $FLASHWIN3_SIZE 0x001000;
   .CONST $MCUWIN1_START 0xFFE000;
   .CONST $MCUWIN1_SIZE 0x001000;
   .CONST $MCUWIN2_START 0xFFF000;
   .CONST $MCUWIN2_SIZE 0x000E00;

   .CONST $PMWIN_HI_START 0x020000;
   .CONST $PMWIN_LO_START 0x030000;
   .CONST $PMWIN_24_START 0x040000;
   .CONST $PMWIN_SIZE 0x003000;

   .CONST $FLASHWIN1_LARGE_START 0xD00000;
   .CONST $FLASHWIN1_LARGE_SIZE 0x100000;
   .CONST $FLASHWIN2_LARGE_START 0xE00000;
   .CONST $FLASHWIN2_LARGE_SIZE 0x100000;
   .CONST $FLASHWIN3_LARGE_START 0xF00000;
   .CONST $FLASHWIN3_LARGE_SIZE 0x0D0000;





   .CONST $INT_LOAD_INFO_CLR_REQ_MASK 16384;

   .CONST $INT_SOURCE_TIMER1_POSN 0;
   .CONST $INT_SOURCE_TIMER2_POSN 1;
   .CONST $INT_SOURCE_MCU_POSN 2;
   .CONST $INT_SOURCE_PIO_POSN 3;
   .CONST $INT_SOURCE_MMU_UNMAPPED_POSN 4;
   .CONST $INT_SOURCE_SW0_POSN 5;
   .CONST $INT_SOURCE_SW1_POSN 6;
   .CONST $INT_SOURCE_SW2_POSN 7;
   .CONST $INT_SOURCE_SW3_POSN 8;

   .CONST $INT_SOURCE_TIMER1_MASK 1;
   .CONST $INT_SOURCE_TIMER2_MASK 2;
   .CONST $INT_SOURCE_MCU_MASK 4;
   .CONST $INT_SOURCE_PIO_MASK 8;
   .CONST $INT_SOURCE_MMU_UNMAPPED_MASK 16;
   .CONST $INT_SOURCE_SW0_MASK 32;
   .CONST $INT_SOURCE_SW1_MASK 64;
   .CONST $INT_SOURCE_SW2_MASK 128;
   .CONST $INT_SOURCE_SW3_MASK 256;

   .CONST $INT_SOURCE_TIMER1_EVENT 0;
   .CONST $INT_SOURCE_TIMER2_EVENT 1;
   .CONST $INT_SOURCE_MCU_EVENT 2;
   .CONST $INT_SOURCE_PIO_EVENT 3;
   .CONST $INT_SOURCE_MMU_UNMAPPED_EVENT 4;
   .CONST $INT_SOURCE_SW0_EVENT 5;
   .CONST $INT_SOURCE_SW1_EVENT 6;
   .CONST $INT_SOURCE_SW2_EVENT 7;
   .CONST $INT_SOURCE_SW3_EVENT 8;





   .CONST $CLK_DIV_1 0;
   .CONST $CLK_DIV_2 1;
   .CONST $CLK_DIV_4 3;
   .CONST $CLK_DIV_8 7;
   .CONST $CLK_DIV_16 15;
   .CONST $CLK_DIV_32 31;
   .CONST $CLK_DIV_64 63;
   .CONST $CLK_DIV_128 127;
   .CONST $CLK_DIV_256 255;
   .CONST $CLK_DIV_512 511;
   .CONST $CLK_DIV_1024 1023;
   .CONST $CLK_DIV_2048 2047;
   .CONST $CLK_DIV_4096 4095;
   .CONST $CLK_DIV_8192 8191;
   .CONST $CLK_DIV_16384 16383;


   .CONST $CLK_DIV_MAX $CLK_DIV_64;



   .CONST $N_FLAG 1;
   .CONST $Z_FLAG 2;
   .CONST $C_FLAG 4;
   .CONST $V_FLAG 8;
   .CONST $UD_FLAG 16;
   .CONST $SV_FLAG 32;
   .CONST $BR_FLAG 64;
   .CONST $UM_FLAG 128;

   .CONST $NOT_N_FLAG (65535-$N_FLAG);
   .CONST $NOT_Z_FLAG (65535-$Z_FLAG);
   .CONST $NOT_C_FLAG (65535-$C_FLAG);
   .CONST $NOT_V_FLAG (65535-$V_FLAG);
   .CONST $NOT_UD_FLAG (65535-$UD_FLAG);
   .CONST $NOT_SV_FLAG (65535-$SV_FLAG);
   .CONST $NOT_BR_FLAG (65535-$BR_FLAG);
   .CONST $NOT_UM_FLAG (65535-$UM_FLAG);
.linefile 21 "C:/ADK4.0.0/kalimba/architecture/architecture.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/architecture/gordon_io_defs.h" 1
.linefile 10 "C:/ADK4.0.0/kalimba/architecture/gordon_io_defs.h"
   .CONST $FLASH_CACHE_SIZE_1K_ENUM 0x000000;
   .CONST $FLASH_CACHE_SIZE_512_ENUM 0x000001;
   .CONST $ADDSUB_SATURATE_ON_OVERFLOW_POSN 0x000000;
   .CONST $ADDSUB_SATURATE_ON_OVERFLOW_MASK 0x000001;
   .CONST $ARITHMETIC_16BIT_MODE_POSN 0x000001;
   .CONST $ARITHMETIC_16BIT_MODE_MASK 0x000002;
   .CONST $DISABLE_UNBIASED_ROUNDING_POSN 0x000002;
   .CONST $DISABLE_UNBIASED_ROUNDING_MASK 0x000004;
   .CONST $DISABLE_FRAC_MULT_ROUNDING_POSN 0x000003;
   .CONST $DISABLE_FRAC_MULT_ROUNDING_MASK 0x000008;
   .CONST $DISABLE_RMAC_STORE_ROUNDING_POSN 0x000004;
   .CONST $DISABLE_RMAC_STORE_ROUNDING_MASK 0x000010;
   .CONST $FLASHWIN_CONFIG_NOSIGNX_POSN 0x000000;
   .CONST $FLASHWIN_CONFIG_NOSIGNX_MASK 0x000001;
   .CONST $FLASHWIN_CONFIG_24BIT_POSN 0x000001;
   .CONST $FLASHWIN_CONFIG_24BIT_MASK 0x000002;
   .CONST $INT_EVENT_TIMER1_POSN 0x000000;
   .CONST $INT_EVENT_TIMER1_MASK 0x000001;
   .CONST $INT_EVENT_TIMER2_POSN 0x000001;
   .CONST $INT_EVENT_TIMER2_MASK 0x000002;
   .CONST $INT_EVENT_XAP_POSN 0x000002;
   .CONST $INT_EVENT_XAP_MASK 0x000004;
   .CONST $INT_EVENT_PIO_POSN 0x000003;
   .CONST $INT_EVENT_PIO_MASK 0x000008;
   .CONST $INT_EVENT_MMU_UNMAPPED_POSN 0x000004;
   .CONST $INT_EVENT_MMU_UNMAPPED_MASK 0x000010;
   .CONST $INT_EVENT_SW0_POSN 0x000005;
   .CONST $INT_EVENT_SW0_MASK 0x000020;
   .CONST $INT_EVENT_SW1_POSN 0x000006;
   .CONST $INT_EVENT_SW1_MASK 0x000040;
   .CONST $INT_EVENT_SW2_POSN 0x000007;
   .CONST $INT_EVENT_SW2_MASK 0x000080;
   .CONST $INT_EVENT_SW3_POSN 0x000008;
   .CONST $INT_EVENT_SW3_MASK 0x000100;
   .CONST $INT_EVENT_GPS_POSN 0x000009;
   .CONST $INT_EVENT_GPS_MASK 0x000200;
   .CONST $BITMODE_POSN 0x000000;
   .CONST $BITMODE_MASK 0x000003;
   .CONST $BITMODE_8BIT_ENUM 0x000000;
   .CONST $BITMODE_16BIT_ENUM 0x000001;
   .CONST $BITMODE_24BIT_ENUM 0x000002;
   .CONST $BYTESWAP_POSN 0x000002;
   .CONST $BYTESWAP_MASK 0x000004;
   .CONST $SATURATE_POSN 0x000003;
   .CONST $SATURATE_MASK 0x000008;
   .CONST $NOSIGNEXT_POSN 0x000003;
   .CONST $NOSIGNEXT_MASK 0x000008;
.linefile 22 "C:/ADK4.0.0/kalimba/architecture/architecture.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/architecture/gordon_io_map.h" 1
.linefile 10 "C:/ADK4.0.0/kalimba/architecture/gordon_io_map.h"
   .CONST $INT_SW_ERROR_EVENT_TRIGGER 0xFFFE00;
   .CONST $INT_GBL_ENABLE 0xFFFE11;
   .CONST $INT_ENABLE 0xFFFE12;
   .CONST $INT_CLK_SWITCH_EN 0xFFFE13;
   .CONST $INT_SOURCES_EN 0xFFFE14;
   .CONST $INT_PRIORITIES 0xFFFE15;
   .CONST $INT_LOAD_INFO 0xFFFE16;
   .CONST $INT_ACK 0xFFFE17;
   .CONST $INT_SOURCE 0xFFFE18;
   .CONST $INT_SAVE_INFO 0xFFFE19;
   .CONST $INT_ADDR 0xFFFE1A;
   .CONST $DSP2MCU_EVENT_DATA 0xFFFE1B;
   .CONST $PC_STATUS 0xFFFE1C;
   .CONST $MCU2DSP_EVENT_DATA 0xFFFE1D;
   .CONST $DOLOOP_CACHE_EN 0xFFFE1E;
   .CONST $TIMER1_EN 0xFFFE1F;
   .CONST $TIMER2_EN 0xFFFE20;
   .CONST $TIMER1_TRIGGER 0xFFFE21;
   .CONST $TIMER2_TRIGGER 0xFFFE22;
   .CONST $WRITE_PORT0_DATA 0xFFFE23;
   .CONST $WRITE_PORT1_DATA 0xFFFE24;
   .CONST $WRITE_PORT2_DATA 0xFFFE25;
   .CONST $WRITE_PORT3_DATA 0xFFFE26;
   .CONST $WRITE_PORT4_DATA 0xFFFE27;
   .CONST $WRITE_PORT5_DATA 0xFFFE28;
   .CONST $WRITE_PORT6_DATA 0xFFFE29;
   .CONST $WRITE_PORT7_DATA 0xFFFE2A;
   .CONST $READ_PORT0_DATA 0xFFFE2B;
   .CONST $READ_PORT1_DATA 0xFFFE2C;
   .CONST $READ_PORT2_DATA 0xFFFE2D;
   .CONST $READ_PORT3_DATA 0xFFFE2E;
   .CONST $READ_PORT4_DATA 0xFFFE2F;
   .CONST $READ_PORT5_DATA 0xFFFE30;
   .CONST $READ_PORT6_DATA 0xFFFE31;
   .CONST $READ_PORT7_DATA 0xFFFE32;
   .CONST $PORT_BUFFER_SET 0xFFFE33;
   .CONST $WRITE_PORT8_DATA 0xFFFE34;
   .CONST $WRITE_PORT9_DATA 0xFFFE35;
   .CONST $WRITE_PORT10_DATA 0xFFFE36;
   .CONST $READ_PORT8_DATA 0xFFFE38;
   .CONST $READ_PORT9_DATA 0xFFFE39;
   .CONST $READ_PORT10_DATA 0xFFFE3A;
   .CONST $MM_DOLOOP_START 0xFFFE40;
   .CONST $MM_DOLOOP_END 0xFFFE41;
   .CONST $MM_QUOTIENT 0xFFFE42;
   .CONST $MM_REM 0xFFFE43;
   .CONST $MM_RINTLINK 0xFFFE44;
   .CONST $CLOCK_DIVIDE_RATE 0xFFFE4D;
   .CONST $INT_CLOCK_DIVIDE_RATE 0xFFFE4E;
   .CONST $PIO_IN 0xFFFE4F;
   .CONST $PIO2_IN 0xFFFE50;
   .CONST $PIO_OUT 0xFFFE51;
   .CONST $PIO2_OUT 0xFFFE52;
   .CONST $PIO_DIR 0xFFFE53;
   .CONST $PIO2_DIR 0xFFFE54;
   .CONST $PIO_EVENT_EN_MASK 0xFFFE55;
   .CONST $PIO2_EVENT_EN_MASK 0xFFFE56;
   .CONST $INT_SW0_EVENT 0xFFFE57;
   .CONST $INT_SW1_EVENT 0xFFFE58;
   .CONST $INT_SW2_EVENT 0xFFFE59;
   .CONST $INT_SW3_EVENT 0xFFFE5A;
   .CONST $FLASH_WINDOW1_START_ADDR 0xFFFE5B;
   .CONST $FLASH_WINDOW2_START_ADDR 0xFFFE5C;
   .CONST $FLASH_WINDOW3_START_ADDR 0xFFFE5D;
   .CONST $NOSIGNX_MCUWIN1 0xFFFE5F;
   .CONST $NOSIGNX_MCUWIN2 0xFFFE60;
   .CONST $FLASHWIN1_CONFIG 0xFFFE61;
   .CONST $FLASHWIN2_CONFIG 0xFFFE62;
   .CONST $FLASHWIN3_CONFIG 0xFFFE63;
   .CONST $NOSIGNX_PMWIN 0xFFFE64;
   .CONST $PM_WIN_ENABLE 0xFFFE65;
   .CONST $STACK_START_ADDR 0xFFFE66;
   .CONST $STACK_END_ADDR 0xFFFE67;
   .CONST $STACK_POINTER 0xFFFE68;
   .CONST $STACK_OVERFLOW_PC 0xFFFE69;
   .CONST $FRAME_POINTER 0xFFFE6A;
   .CONST $NUM_RUN_CLKS_MS 0xFFFE6B;
   .CONST $NUM_RUN_CLKS_LS 0xFFFE6C;
   .CONST $NUM_INSTRS_MS 0xFFFE6D;
   .CONST $NUM_INSTRS_LS 0xFFFE6E;
   .CONST $NUM_STALLS_MS 0xFFFE6F;
   .CONST $NUM_STALLS_LS 0xFFFE70;
   .CONST $TIMER_TIME 0xFFFE71;
   .CONST $TIMER_TIME_MS 0xFFFE72;
   .CONST $WRITE_PORT0_CONFIG 0xFFFE73;
   .CONST $WRITE_PORT1_CONFIG 0xFFFE74;
   .CONST $WRITE_PORT2_CONFIG 0xFFFE75;
   .CONST $WRITE_PORT3_CONFIG 0xFFFE76;
   .CONST $WRITE_PORT4_CONFIG 0xFFFE77;
   .CONST $WRITE_PORT5_CONFIG 0xFFFE78;
   .CONST $WRITE_PORT6_CONFIG 0xFFFE79;
   .CONST $WRITE_PORT7_CONFIG 0xFFFE7A;
   .CONST $READ_PORT0_CONFIG 0xFFFE7B;
   .CONST $READ_PORT1_CONFIG 0xFFFE7C;
   .CONST $READ_PORT2_CONFIG 0xFFFE7D;
   .CONST $READ_PORT3_CONFIG 0xFFFE7E;
   .CONST $READ_PORT4_CONFIG 0xFFFE7F;
   .CONST $READ_PORT5_CONFIG 0xFFFE80;
   .CONST $READ_PORT6_CONFIG 0xFFFE81;
   .CONST $READ_PORT7_CONFIG 0xFFFE82;
   .CONST $PM_FLASHWIN_START_ADDR 0xFFFE83;
   .CONST $PM_FLASHWIN_SIZE 0xFFFE84;
   .CONST $BITREVERSE_VAL 0xFFFE89;
   .CONST $BITREVERSE_DATA 0xFFFE8A;
   .CONST $BITREVERSE_DATA16 0xFFFE8B;
   .CONST $BITREVERSE_ADDR 0xFFFE8C;
   .CONST $ARITHMETIC_MODE 0xFFFE93;
   .CONST $FORCE_FAST_MMU 0xFFFE94;
   .CONST $DBG_COUNTERS_EN 0xFFFE9F;
   .CONST $PM_FLASHWIN_CACHE_SIZE 0xFFFEE0;
   .CONST $WRITE_PORT8_CONFIG 0xFFFEE1;
   .CONST $WRITE_PORT9_CONFIG 0xFFFEE2;
   .CONST $WRITE_PORT10_CONFIG 0xFFFEE3;
   .CONST $READ_PORT8_CONFIG 0xFFFEE5;
   .CONST $READ_PORT9_CONFIG 0xFFFEE6;
   .CONST $READ_PORT10_CONFIG 0xFFFEE7;

   .CONST $READ_CONFIG_GAP $READ_PORT8_CONFIG - $READ_PORT7_CONFIG;
   .CONST $READ_DATA_GAP $READ_PORT8_DATA - $READ_PORT7_DATA;
   .CONST $WRITE_CONFIG_GAP $WRITE_PORT8_CONFIG - $WRITE_PORT7_CONFIG;
   .CONST $WRITE_DATA_GAP $WRITE_PORT8_DATA - $WRITE_PORT7_DATA;


   .CONST $INT_UNBLOCK $INT_ENABLE;
.linefile 23 "C:/ADK4.0.0/kalimba/architecture/architecture.h" 2
.linefile 13 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/message.h" 2






   .CONST $message.MAX_LONG_MESSAGE_TX_PAYLOAD_SIZE 80;
   .CONST $message.MAX_LONG_MESSAGE_RX_PAYLOAD_SIZE 80;



   .CONST $message.MAX_LONG_MESSAGE_TX_SIZE ($message.MAX_LONG_MESSAGE_TX_PAYLOAD_SIZE + 2);
   .CONST $message.MAX_LONG_MESSAGE_RX_SIZE ($message.MAX_LONG_MESSAGE_RX_PAYLOAD_SIZE + 2);


   .CONST $message.QUEUE_SIZE_IN_MSGS (($message.MAX_LONG_MESSAGE_TX_SIZE+3)>>2)+1;


   .CONST $message.QUEUE_SIZE_IN_WORDS ($message.QUEUE_SIZE_IN_MSGS * (1+4));
   .CONST $message.LONG_MESSAGE_BUFFER_SIZE (((($message.MAX_LONG_MESSAGE_RX_SIZE+3)>>2)+1) * 4);



   .CONST $message.MAX_MESSAGE_HANDLERS 50;





   .CONST $message.REATTEMPT_SEND_PERIOD 1000;


   .CONST $message.TO_DSP_SHARED_WIN_SIZE 4;
   .CONST $message.TO_MCU_SHARED_WIN_SIZE 4;
   .CONST $message.ACK_FROM_MCU ($MCUWIN1_START + 0);
   .CONST $message.ACK_FROM_DSP ($MCUWIN1_START + 1);
   .CONST $message.DATA_TO_MCU ($MCUWIN1_START + 2);
   .CONST $message.DATA_TO_DSP ($MCUWIN1_START + 2 + $message.TO_DSP_SHARED_WIN_SIZE);


   .CONST $message.LAST_ENTRY -1;


   .CONST $message.LONG_MESSAGE_MODE_ID -2;


   .CONST $message.NEXT_ADDR_FIELD 0;
   .CONST $message.ID_FIELD 1;
   .CONST $message.HANDLER_ADDR_FIELD 2;
   .CONST $message.MASK_FIELD 3;
   .CONST $message.STRUC_SIZE 4;


   .CONST $message.QUEUE_WORDS_PER_MSG (1+4);
.linefile 12 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cbuffer.h" 1
.linefile 11 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cbuffer.h"
   .CONST $cbuffer.SIZE_FIELD 0;
   .CONST $cbuffer.READ_ADDR_FIELD 1;
   .CONST $cbuffer.WRITE_ADDR_FIELD 2;




      .CONST $cbuffer.STRUC_SIZE 3;




 .CONST $frmbuffer.CBUFFER_PTR_FIELD 0;
 .CONST $frmbuffer.FRAME_PTR_FIELD 1;
 .CONST $frmbuffer.FRAME_SIZE_FIELD 2;
 .CONST $frmbuffer.STRUC_SIZE 3;
.linefile 42 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cbuffer.h"
      .CONST $cbuffer.NUM_PORTS 12;
      .CONST $cbuffer.WRITE_PORT_OFFSET 0x00000C;
      .CONST $cbuffer.PORT_NUMBER_MASK 0x00000F;
      .CONST $cbuffer.TOTAL_PORT_NUMBER_MASK 0x00001F;
      .CONST $cbuffer.TOTAL_CONTINUOUS_PORTS 8;







   .CONST $cbuffer.MMU_PAGE_SIZE 64;


   .CONST $cbuffer.READ_PORT_MASK 0x800000;
   .CONST $cbuffer.WRITE_PORT_MASK $cbuffer.READ_PORT_MASK + $cbuffer.WRITE_PORT_OFFSET;




   .CONST $cbuffer.FORCE_ENDIAN_MASK 0x300000;
   .CONST $cbuffer.FORCE_ENDIAN_SHIFT_AMOUNT -21;
   .CONST $cbuffer.FORCE_LITTLE_ENDIAN 0x100000;
   .CONST $cbuffer.FORCE_BIG_ENDIAN 0x300000;


   .CONST $cbuffer.FORCE_SIGN_EXTEND_MASK 0x0C0000;
   .CONST $cbuffer.FORCE_SIGN_EXTEND_SHIFT_AMOUNT -19;
   .CONST $cbuffer.FORCE_SIGN_EXTEND 0x040000;
   .CONST $cbuffer.FORCE_NO_SIGN_EXTEND 0x0C0000;


   .CONST $cbuffer.FORCE_BITWIDTH_MASK 0x038000;
   .CONST $cbuffer.FORCE_BITWIDTH_SHIFT_AMOUNT -16;
   .CONST $cbuffer.FORCE_8BIT_WORD 0x008000;
   .CONST $cbuffer.FORCE_16BIT_WORD 0x018000;
   .CONST $cbuffer.FORCE_24BIT_WORD 0x028000;
   .CONST $cbuffer.FORCE_32BIT_WORD 0x038000;


   .CONST $cbuffer.FORCE_SATURATE_MASK 0x006000;
   .CONST $cbuffer.FORCE_SATURATE_SHIFT_AMOUNT -14;
   .CONST $cbuffer.FORCE_NO_SATURATE 0x002000;
   .CONST $cbuffer.FORCE_SATURATE 0x006000;


   .CONST $cbuffer.FORCE_PADDING_MASK 0x001C00;
   .CONST $cbuffer.FORCE_PADDING_SHIFT_AMOUNT -11;
   .CONST $cbuffer.FORCE_PADDING_NONE 0x000400;
   .CONST $cbuffer.FORCE_PADDING_LS_BYTE 0x000C00;
   .CONST $cbuffer.FORCE_PADDING_MS_BYTE 0x001400;


   .CONST $cbuffer.FORCE_PCM_AUDIO $cbuffer.FORCE_LITTLE_ENDIAN +
                                                      $cbuffer.FORCE_SIGN_EXTEND +
                                                      $cbuffer.FORCE_SATURATE;
   .CONST $cbuffer.FORCE_24B_PCM_AUDIO $cbuffer.FORCE_LITTLE_ENDIAN +
                                                      $cbuffer.FORCE_32BIT_WORD +
                                                      $cbuffer.FORCE_PADDING_MS_BYTE +
                                                      $cbuffer.FORCE_NO_SATURATE;

   .CONST $cbuffer.FORCE_16BIT_DATA_STREAM $cbuffer.FORCE_BIG_ENDIAN +
                                                      $cbuffer.FORCE_NO_SIGN_EXTEND +
                                                      $cbuffer.FORCE_NO_SATURATE;
.linefile 13 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/interrupt.h" 1
.linefile 28 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/interrupt.h"
      .CONST $INTERRUPT_STORE_STATE_SIZE 48;
.linefile 14 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/pskey.h" 1
.linefile 17 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/pskey.h"
   .CONST $pskey.NEXT_ENTRY_FIELD 0;
   .CONST $pskey.KEY_NUM_FIELD 1;
   .CONST $pskey.HANDLER_ADDR_FIELD 2;
   .CONST $pskey.STRUC_SIZE 3;



   .CONST $pskey.MAX_HANDLERS 50;

   .CONST $pskey.LAST_ENTRY -1;
   .CONST $pskey.REATTEMPT_TIME_PERIOD 10000;

   .CONST $pskey.FAILED_READ_LENGTH -1;
.linefile 15 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/flash.h" 1
.linefile 17 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/flash.h"
      .CONST $PM_FLASHWIN_SIZE_MAX 0x40000;




   .CONST $flash.get_file_address.MAX_HANDLERS 10;


   .CONST $flash.get_file_address.NEXT_ENTRY_FIELD 0;
   .CONST $flash.get_file_address.FILE_ID_FIELD 1;
   .CONST $flash.get_file_address.HANDLER_ADDR_FIELD 2;
   .CONST $flash.get_file_address.STRUC_SIZE 3;

   .CONST $flash.get_file_address.LAST_ENTRY -1;
   .CONST $flash.get_file_address.REATTEMPT_TIME_PERIOD 10000;

   .CONST $flash.get_file_address.MESSAGE_HANDLER_UNINITIALISED -1;
.linefile 16 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/wall_clock.h" 1
.linefile 13 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/wall_clock.h"
   .CONST $wall_clock.FIRMWARE_WALL_CLOCK_PERIOD_VALUE 625;
   .CONST $wall_clock.FIRMWARE_WALL_CLOCK_PERIOD_SHIFT -1;

   .CONST $wall_clock.UPDATE_TIMER_PERIOD 100000;





   .CONST $wall_clock.MAX_WALL_CLOCKS 7;

   .CONST $wall_clock.LAST_ENTRY -1;

   .CONST $wall_clock.NEXT_ADDR_FIELD 0;
   .CONST $wall_clock.BT_ADDR_TYPE_FIELD 1;
   .CONST $wall_clock.BT_ADDR_WORD0_FIELD 2;
   .CONST $wall_clock.BT_ADDR_WORD1_FIELD 3;
   .CONST $wall_clock.BT_ADDR_WORD2_FIELD 4;
   .CONST $wall_clock.ADJUSTMENT_VALUE_FIELD 5;
   .CONST $wall_clock.CALLBACK_FIELD 6;
   .CONST $wall_clock.TIMER_STRUC_FIELD 7;
   .CONST $wall_clock.STRUC_SIZE 8 + $timer.STRUC_SIZE;

   .CONST $wall_clock.BT_TICKS_IN_7500_US 24;
.linefile 17 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/pio.h" 1
.linefile 17 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/pio.h"
   .CONST $pio.NEXT_ADDR_FIELD 0;
   .CONST $pio.PIO_BITMASK_FIELD 1;
   .CONST $pio.HANDLER_ADDR_FIELD 2;
   .CONST $pio.STRUC_SIZE 3;



   .CONST $pio.MAX_HANDLERS 20;

   .CONST $pio.LAST_ENTRY -1;
.linefile 18 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/profiler.h" 1
.linefile 41 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/profiler.h"
   .CONST $profiler.MAX_PROFILER_HANDLERS 50;

   .CONST $profiler.LAST_ENTRY -1;





   .CONST $profiler.UNINITIALISED -2;

   .CONST $profiler.NEXT_ADDR_FIELD 0;
   .CONST $profiler.CPU_FRACTION_FIELD 1;
   .CONST $profiler.START_TIME_FIELD 2;
   .CONST $profiler.INT_START_TIME_FIELD 3;
   .CONST $profiler.TOTAL_TIME_FIELD 4;

      .CONST $profiler.RUN_CLKS_MS_START_FIELD 5;
      .CONST $profiler.RUN_CLKS_LS_START_FIELD 6;
      .CONST $profiler.RUN_CLKS_MS_TOTAL_FIELD 7;
      .CONST $profiler.RUN_CLKS_LS_TOTAL_FIELD 8;
      .CONST $profiler.RUN_CLKS_AVERAGE_FIELD 9;
      .CONST $profiler.RUN_CLKS_MS_MAX_FIELD 10;
      .CONST $profiler.RUN_CLKS_LS_MAX_FIELD 11;
      .CONST $profiler.INT_START_CLKS_MS_FIELD 12;
      .CONST $profiler.INT_START_CLKS_LS_FIELD 13;
      .CONST $profiler.INSTRS_MS_START_FIELD 14;
      .CONST $profiler.INSTRS_LS_START_FIELD 15;
      .CONST $profiler.INSTRS_MS_TOTAL_FIELD 16;
      .CONST $profiler.INSTRS_LS_TOTAL_FIELD 17;
      .CONST $profiler.INSTRS_AVERAGE_FIELD 18;
      .CONST $profiler.INSTRS_MS_MAX_FIELD 19;
      .CONST $profiler.INSTRS_LS_MAX_FIELD 20;
      .CONST $profiler.INT_START_INSTRS_MS_FIELD 21;
      .CONST $profiler.INT_START_INSTRS_LS_FIELD 22;
      .CONST $profiler.STALLS_MS_START_FIELD 23;
      .CONST $profiler.STALLS_LS_START_FIELD 24;
      .CONST $profiler.STALLS_MS_TOTAL_FIELD 25;
      .CONST $profiler.STALLS_LS_TOTAL_FIELD 26;
      .CONST $profiler.STALLS_AVERAGE_FIELD 27;
      .CONST $profiler.STALLS_MS_MAX_FIELD 28;
      .CONST $profiler.STALLS_LS_MAX_FIELD 29;
      .CONST $profiler.INT_START_STALLS_MS_FIELD 30;
      .CONST $profiler.INT_START_STALLS_LS_FIELD 31;
      .CONST $profiler.TEMP_COUNT_FIELD 32;
      .CONST $profiler.COUNT_FIELD 33;
      .CONST $profiler.STRUC_SIZE 34;
.linefile 19 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/fwrandom.h" 1
.linefile 17 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/fwrandom.h"
   .CONST $fwrandom.NEXT_ENTRY_FIELD 0;
   .CONST $fwrandom.NUM_REQ_FIELD 1;
   .CONST $fwrandom.NUM_RESP_FIELD 2;
   .CONST $fwrandom.RESP_BUF_FIELD 3;
   .CONST $fwrandom.HANDLER_ADDR_FIELD 4;
   .CONST $fwrandom.STRUC_SIZE 5;



   .CONST $fwrandom.MAX_HANDLERS 50;

   .CONST $fwrandom.LAST_ENTRY -1;
   .CONST $fwrandom.REATTEMPT_TIME_PERIOD 10000;
   .CONST $fwrandom.MAX_RAND_BITS 512;

   .CONST $fwrandom.FAILED_READ_LENGTH -1;
.linefile 20 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 2
.linefile 19 "main.asm" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/codec_library.h" 1
.linefile 11 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/codec_library.h"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/core_library.h" 1
.linefile 12 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/codec_library.h" 2






   .CONST $codec.NORMAL_DECODE 0;
   .CONST $codec.NO_OUTPUT_DECODE 1;
   .CONST $codec.GOBBLE_DECODE 2;

   .CONST $codec.SUCCESS 0;
   .CONST $codec.NOT_ENOUGH_INPUT_DATA 1;
   .CONST $codec.NOT_ENOUGH_OUTPUT_SPACE 2;
   .CONST $codec.ERROR 3;
   .CONST $codec.EOF 4;
   .CONST $codec.FRAME_CORRUPT 5;

   .CONST $codec.ENCODER_OUT_BUFFER_FIELD 0;
   .CONST $codec.ENCODER_IN_LEFT_BUFFER_FIELD 1;
   .CONST $codec.ENCODER_IN_RIGHT_BUFFER_FIELD 2;
   .CONST $codec.ENCODER_MODE_FIELD 3;
   .CONST $codec.ENCODER_DATA_OBJECT_FIELD 4;
   .CONST $codec.ENCODER_STRUC_SIZE 5;

   .CONST $codec.DECODER_IN_BUFFER_FIELD 0;
   .CONST $codec.DECODER_OUT_LEFT_BUFFER_FIELD 1;
   .CONST $codec.DECODER_OUT_RIGHT_BUFFER_FIELD 2;
   .CONST $codec.DECODER_MODE_FIELD 3;
   .CONST $codec.DECODER_NUM_OUTPUT_SAMPLES_FIELD 4;
   .CONST $codec.DECODER_DATA_OBJECT_FIELD 5;
   .CONST $codec.TWS_CALLBACK_FIELD 6;
   .CONST $codec.DECODER_STRUC_SIZE 7;

   .CONST $codec.DECRYPTER_IN_BUFFER_FIELD 0;
   .CONST $codec.DECRYPTER_OUT_BUFFER_FIELD 1;
   .CONST $codec.DECRYPTER_EXTRA_STRUC_PTR_FIELD 2;
   .CONST $codec.DECRYPTER_STRUC_SIZE 3;

   .CONST $codec.STREAM_CAN_IDLE 0;
   .CONST $codec.STREAM_DONT_IDLE 1;


   .CONST $codec.FRAME_DECODE 0;
   .CONST $codec.INIT_DECODER 1;
   .CONST $codec.RESET_DECODER 2;
   .CONST $codec.SILENCE_DECODER 3;
   .CONST $codec.SUSPEND_DECODER 4;
   .CONST $codec.RESUME_DECODER 5;
   .CONST $codec.STORE_BOUNDARY_SNAPSHOT 6;
   .CONST $codec.RESTORE_BOUNDARY_SNAPSHOT 7;
   .CONST $codec.FAST_SKIP 8;
   .CONST $codec.SET_SKIP_FUNCTION 9;
   .CONST $codec.SET_AVERAGE_BITRATE 10;
   .CONST $codec.SET_FILE_TYPE 11;
   .CONST $codec.DECRYPTER_SET_DECODER 12;
   .CONST $codec.DECRYPTER_SET_PARAMETERS 13;




   .CONST $codec.stream_encode.ADDR_FIELD 0;
   .CONST $codec.stream_encode.RESET_ADDR_FIELD 1;
   .CONST $codec.stream_encode.ENCODER_STRUC_FIELD $codec.stream_encode.RESET_ADDR_FIELD + 1;

   .CONST $codec.stream_encode.STATE_FIELD $codec.stream_encode.ENCODER_STRUC_FIELD + $codec.ENCODER_STRUC_SIZE;
   .CONST $codec.stream_encode.MEDIA_HDR_ADDR_FIELD $codec.stream_encode.STATE_FIELD + 1;
   .CONST $codec.stream_encode.STRUC_SIZE $codec.stream_encode.MEDIA_HDR_ADDR_FIELD + 1;


   .CONST $codec.stream_encode.OUT_BUFFER_FIELD $codec.stream_encode.ENCODER_STRUC_FIELD + $codec.ENCODER_OUT_BUFFER_FIELD;
   .CONST $codec.stream_encode.IN_LEFT_BUFFER_FIELD $codec.stream_encode.ENCODER_STRUC_FIELD + $codec.ENCODER_IN_LEFT_BUFFER_FIELD;
   .CONST $codec.stream_encode.IN_RIGHT_BUFFER_FIELD $codec.stream_encode.ENCODER_STRUC_FIELD + $codec.ENCODER_IN_RIGHT_BUFFER_FIELD;
   .CONST $codec.stream_encode.MODE_FIELD $codec.stream_encode.ENCODER_STRUC_FIELD + $codec.ENCODER_MODE_FIELD;






   .CONST $codec.SBC_RTP_AND_PAYLOAD_HEADER_SIZE 13;
   .CONST $codec.MP3_RTP_AND_PAYLOAD_HEADER_SIZE 16;
   .CONST $codec.APTX_RTP_AND_PAYLOAD_HEADER_SIZE 0;


   .CONST $codec.media_header.WRITE_HDR_FIELD 0;
   .CONST $codec.media_header.RTP_SEQUENCE_NUM_FIELD 1;
   .CONST $codec.media_header.RTP_TIMESTAMP_MS_FIELD 2;
   .CONST $codec.media_header.RTP_TIMESTAMP_LS_FIELD 3;
   .CONST $codec.media_header.FRAME_COUNT_FIELD 4;
   .CONST $codec.media_header.SAMPLES_PER_FRAME 5;
   .CONST $codec.media_header.PUT_BITS_ADDR_FIELD 6;
   .CONST $codec.media_header.GET_ENCODED_FRAME_INFO 7;
   .CONST $codec.media_header.NUM_FRAMES_FIELD 8;
   .CONST $codec.media_header.L2CAP_ATU_SIZE_FIELD 9;
   .CONST $codec.media_header.SHUNT_FRAME_BYTE_COUNT_FIELD 10;
   .CONST $codec.media_header.RTP_AND_PAYLOAD_HEADER_SIZE_FIELD 11;
   .CONST $codec.media_header.FASTSTREAM_ENABLED_FIELD 12;
   .CONST $codec.media_header.MEDIA_HDR_STRUC_SIZE $codec.media_header.FASTSTREAM_ENABLED_FIELD + 1;

   .CONST $codec.stream_encode.STATE_STOPPED 0;
   .CONST $codec.stream_encode.STATE_STREAMING 1;
   .CONST $codec.stream_encode.STATE_MASK 1;

   .CONST $codec.stream_decode.ADDR_FIELD 0;
   .CONST $codec.stream_decode.RESET_ADDR_FIELD 1;
   .CONST $codec.stream_decode.SILENCE_ADDR_FIELD 2;
   .CONST $codec.stream_decode.DECODER_STRUC_FIELD $codec.stream_decode.SILENCE_ADDR_FIELD + 1;

   .CONST $codec.stream_decode.COMFORT_NOISE_GAIN_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 0;
   .CONST $codec.stream_decode.GOOD_WORKING_BUFLEVEL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 1;
   .CONST $codec.stream_decode.POORLINK_DETECT_BUFLEVEL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 2;
   .CONST $codec.stream_decode.POORLINK_PERIOD_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 3;
   .CONST $codec.stream_decode.PLAYING_ZERO_DATARATE_PERIOD_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 4;
   .CONST $codec.stream_decode.BUFFERING_ZERO_DATARATE_PERIOD_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 5;
   .CONST $codec.stream_decode.POORLINK_DETECT_TABLE_ADDR_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 6;
   .CONST $codec.stream_decode.POORLINK_DETECT_TABLE_SIZE_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 7;
   .CONST $codec.stream_decode.WARP_RATE_HIGH_COEF_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 8;
   .CONST $codec.stream_decode.WARP_RATE_LOW_COEF_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 9;
   .CONST $codec.stream_decode.WARP_RATE_TRANSITION_LEVEL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 10;
   .CONST $codec.stream_decode.POORLINK_DETECT_TABLE_OFFSET_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 11;
   .CONST $codec.stream_decode.RAND_LAST_VAL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 12;
   .CONST $codec.stream_decode.STATE_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 13;
   .CONST $codec.stream_decode.POORLINK_ENDTIME_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 14;
   .CONST $codec.stream_decode.ZERO_DATARATE_ENDTIME_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 15;
   .CONST $codec.stream_decode.PLAYING_STARTTIME_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 16;
   .CONST $codec.stream_decode.PREV_WRITE_PTR_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 17;
   .CONST $codec.stream_decode.FAST_AVERAGE_BUFLEVEL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 18;
   .CONST $codec.stream_decode.SLOW_AVERAGE_BUFLEVEL_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 19;
   .CONST $codec.stream_decode.SLOW_AVERAGE_SAMPLE_TIME_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 20;
   .CONST $codec.stream_decode.WARP_TARGET_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_STRUC_SIZE + 21;
   .CONST $codec.stream_decode.STRUC_SIZE $codec.stream_decode.WARP_TARGET_FIELD + 1;


   .CONST $codec.stream_decode.IN_BUFFER_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_IN_BUFFER_FIELD;
   .CONST $codec.stream_decode.OUT_LEFT_BUFFER_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_OUT_LEFT_BUFFER_FIELD;
   .CONST $codec.stream_decode.OUT_RIGHT_BUFFER_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_OUT_RIGHT_BUFFER_FIELD;
   .CONST $codec.stream_decode.MODE_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_MODE_FIELD;
   .CONST $codec.stream_decode.NUM_OUTPUT_SAMPLES_FIELD $codec.stream_decode.DECODER_STRUC_FIELD + $codec.DECODER_NUM_OUTPUT_SAMPLES_FIELD;



   .CONST $codec.stream_decode.STATE_BUFFERING 0;
   .CONST $codec.stream_decode.STATE_PLAYING 1;
   .CONST $codec.stream_decode.STATE_MASK 1;

   .CONST $codec.stream_decode_sync.CONDITION_READ_WALL_CLOCK 2;
   .CONST $codec.stream_decode_sync.CONDITION_DECODE_FRAME 4;
   .CONST $codec.stream_decode_sync.CONDITION_INSERT_SAMPLES 8;

   .CONST $codec.stream_decode.CONDITION_POORLINK 2;
   .CONST $codec.stream_decode.CONDITION_DETECT_POORLINK_ENABLE 4;
   .CONST $codec.stream_decode.CONDITION_ZERO_DATARATE 8;
   .CONST $codec.stream_decode.CONDITION_STOPPING 16;

   .CONST $codec.stream_decode.FAST_AVERAGE_SHIFT_CONST -6;
   .CONST $codec.stream_decode.SLOW_AVERAGE_SHIFT_CONST -2;
   .CONST $codec.stream_decode.SLOW_AVERAGE_SAMPLE_PERIOD 50000;
.linefile 177 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/codec_library.h"
   .CONST $codec.stream_relay.GET_FRAME_INFO_ADDR_FIELD 0;
   .CONST $codec.stream_relay.IN_BUFFER_FIELD 1;
   .CONST $codec.stream_relay.LOCAL_RELAY_BUFFER_FIELD 2;
   .CONST $codec.stream_relay.REMOTE_RELAY_BUFFER_FIELD 3;
   .CONST $codec.stream_relay.BUFFER_DELAY_IN_US_FIELD 4;
   .CONST $codec.stream_relay.WARP_RATE_COEF_FIELD 5;
   .CONST $codec.stream_relay.NUM_AUDIO_SAMPLES_CONSUMED_PNTR_FIELD 6;
   .CONST $codec.stream_relay.WALL_CLOCK_STRUC_PNTR_FIELD 7;
   .CONST $codec.stream_relay.NUM_MICRO_SECS_PER_1024_SAMPLES_FIELD 8;
   .CONST $codec.stream_relay.PREVIOUS_AUDIO_FRAME_LENGTH_FIELD 9;
   .CONST $codec.stream_relay.SLOW_AVERAGE_BUFLEVEL_FIELD 10;
   .CONST $codec.stream_relay.SLOW_AVERAGE_SAMPLE_TIME_FIELD 11;
   .CONST $codec.stream_relay.STATE_FIELD 12;
   .CONST $codec.stream_relay.TIME_TO_PLAY_FIELD 13;
   .CONST $codec.stream_relay.NUM_AUDIO_SAMPLES_IN_BUFFER_FIELD 14;
   .CONST $codec.stream_relay.GOOD_WORKING_BUFLEVEL_FIELD 15;
   .CONST $codec.stream_relay.STRUC_SIZE 16;

   .CONST $codec.stream_relay.SLOW_AVERAGE_SAMPLE_PERIOD 50000;
   .CONST $codec.stream_relay.SLOW_AVERAGE_SHIFT_CONST -2;

   .CONST $codec.stream_relay.STATE_BUFFERING 0;
   .CONST $codec.stream_relay.STATE_PLAYING 1;



   .CONST $codec.stream_decode_sync.ADDR_FIELD 0;
   .CONST $codec.stream_decode_sync.RESET_ADDR_FIELD 1;
   .CONST $codec.stream_decode_sync.SILENCE_ADDR_FIELD 2;
   .CONST $codec.stream_decode_sync.GET_FRAME_INFO_ADDR_FIELD 3;
   .CONST $codec.stream_decode_sync.LEFT_DAC_PORT_FIELD 4;
   .CONST $codec.stream_decode_sync.RIGHT_DAC_PORT_FIELD 5;
   .CONST $codec.stream_decode_sync.IN_BUFFER_FIELD 6;
   .CONST $codec.stream_decode_sync.OUT_LEFT_BUFFER_FIELD 7;
   .CONST $codec.stream_decode_sync.OUT_RIGHT_BUFFER_FIELD 8;
   .CONST $codec.stream_decode_sync.MODE_FIELD 9;
   .CONST $codec.stream_decode_sync.NUM_OUTPUT_SAMPLES_FIELD 10;
   .CONST $codec.stream_decode_sync.COMFORT_NOISE_GAIN_FIELD 11;
   .CONST $codec.stream_decode_sync.DELAY_TO_WARP_COEF_FIELD 12;
   .CONST $codec.stream_decode_sync.MAX_PLAY_TIME_OFFSET_IN_US_FIELD 13;
   .CONST $codec.stream_decode_sync.GENERATE_SILENCE_THRESHOLD_FIELD 14;
   .CONST $codec.stream_decode_sync.AMOUNT_OF_SILENCE_TO_GENERATE_FIELD 15;
   .CONST $codec.stream_decode_sync.CURRENT_MODE_FIELD 16;
   .CONST $codec.stream_decode_sync.DECODER_MODE_FIELD 17;
   .CONST $codec.stream_decode_sync.FRAME_PLAY_TIME_FIELD 18;
   .CONST $codec.stream_decode_sync.NUM_MICRO_SECS_PER_1024_SAMPLES_FIELD 19;
   .CONST $codec.stream_decode_sync.NUM_SAMPLES_PER_US_FIELD 20;
   .CONST $codec.stream_decode_sync.PADDING_BYTE_FIELD 21;
   .CONST $codec.stream_decode_sync.RAND_LAST_VAL_FIELD 22;
   .CONST $codec.stream_decode_sync.REQUESTED_WARP_FIELD 23;
   .CONST $codec.stream_decode_sync.STREAMING_FIELD 24;
   .CONST $codec.stream_decode_sync.AUDIO_SAMPLES_CONSUMED_FIELD 25;
   .CONST $codec.stream_decode_sync.WALL_CLOCK_STRUC_FIELD 26;
   .CONST $codec.stream_decode_sync.STRUC_SIZE ($codec.stream_decode_sync.WALL_CLOCK_STRUC_FIELD + $wall_clock.STRUC_SIZE);

   .CONST $codec.stream_decode_sync.STREAMING_STOPPED 0;
   .CONST $codec.stream_decode_sync.STREAMING_PLAYING 1;



   .CONST $codec.av_encode.ADDR_FIELD 0;
   .CONST $codec.av_encode.RESET_ADDR_FIELD $codec.av_encode.ADDR_FIELD + 1;

   .CONST $codec.av_encode.ENCODER_STRUC_FIELD $codec.av_encode.RESET_ADDR_FIELD + 1;
   .CONST $codec.av_encode.OUT_BUFFER_FIELD $codec.av_encode.ENCODER_STRUC_FIELD;
   .CONST $codec.av_encode.IN_LEFT_BUFFER_FIELD $codec.av_encode.OUT_BUFFER_FIELD + 1;
   .CONST $codec.av_encode.IN_RIGHT_BUFFER_FIELD $codec.av_encode.IN_LEFT_BUFFER_FIELD + 1;
   .CONST $codec.av_encode.MODE_FIELD $codec.av_encode.IN_RIGHT_BUFFER_FIELD + 1;

   .CONST $codec.av_encode.ENCODER_DATA_OBJECT_FIELD $codec.av_encode.MODE_FIELD + 1;
   .CONST $codec.av_encode.BUFFERING_THRESHOLD_FIELD $codec.av_encode.ENCODER_DATA_OBJECT_FIELD + 1;
   .CONST $codec.av_encode.STALL_COUNTER_FIELD $codec.av_encode.BUFFERING_THRESHOLD_FIELD + 1;

   .CONST $codec.av_encode.STRUC_SIZE $codec.av_encode.STALL_COUNTER_FIELD + 1;


   .CONST $codec.av_decode.ADDR_FIELD 0;
   .CONST $codec.av_decode.RESET_ADDR_FIELD $codec.av_decode.ADDR_FIELD + 1;
   .CONST $codec.av_decode.SILENCE_ADDR_FIELD $codec.av_decode.RESET_ADDR_FIELD + 1;

   .CONST $codec.av_decode.DECODER_STRUC_FIELD $codec.av_decode.SILENCE_ADDR_FIELD + 1;
   .CONST $codec.av_decode.IN_BUFFER_FIELD $codec.av_decode.DECODER_STRUC_FIELD;
   .CONST $codec.av_decode.OUT_LEFT_BUFFER_FIELD $codec.av_decode.IN_BUFFER_FIELD + 1;
   .CONST $codec.av_decode.OUT_RIGHT_BUFFER_FIELD $codec.av_decode.OUT_LEFT_BUFFER_FIELD + 1;
   .CONST $codec.av_decode.MODE_FIELD $codec.av_decode.OUT_RIGHT_BUFFER_FIELD + 1;
   .CONST $codec.av_decode.DECODER_NUM_OUTPUT_SAMPLES_FIELD $codec.av_decode.MODE_FIELD + 1;

   .CONST $codec.av_decode.DECODER_DATA_OBJECT_FIELD $codec.av_decode.DECODER_NUM_OUTPUT_SAMPLES_FIELD + 1;
   .CONST $codec.av_decode.TWS_CALLBACK_FIELD $codec.av_decode.DECODER_DATA_OBJECT_FIELD + 1;
   .CONST $codec.av_decode.DECODE_TO_STALL_THRESHOLD $codec.av_decode.TWS_CALLBACK_FIELD + 1;
   .CONST $codec.av_decode.STALL_BUFFER_LEVEL_FIELD $codec.av_decode.DECODE_TO_STALL_THRESHOLD + 1;
   .CONST $codec.av_decode.NORMAL_BUFFER_LEVEL_FIELD $codec.av_decode.STALL_BUFFER_LEVEL_FIELD + 1;
   .CONST $codec.av_decode.CODEC_PURGE_ENABLE_FIELD $codec.av_decode.NORMAL_BUFFER_LEVEL_FIELD + 1;
   .CONST $codec.av_decode.MASTER_RESET_FUNC_FIELD $codec.av_decode.CODEC_PURGE_ENABLE_FIELD + 1;

   .CONST $codec.av_decode.CODEC_PREV_WADDR_FIELD $codec.av_decode.MASTER_RESET_FUNC_FIELD + 1;
   .CONST $codec.av_decode.PAUSE_TIMER_FIELD $codec.av_decode.CODEC_PREV_WADDR_FIELD + 1;
   .CONST $codec.av_decode.CURRENT_RUNNING_MODE_FIELD $codec.av_decode.PAUSE_TIMER_FIELD + 1;
   .CONST $codec.av_decode.CAN_SWITCH_FIELD $codec.av_decode.CURRENT_RUNNING_MODE_FIELD + 1;
   .CONST $codec.av_decode.PREV_TIME_FIELD $codec.av_decode.CAN_SWITCH_FIELD + 1;
   .CONST $codec.av_decode.STALL_TIMER_FIELD $codec.av_decode.PREV_TIME_FIELD + 1;


   .CONST $codec.av_decode.STRUC_SIZE $codec.av_decode.STALL_TIMER_FIELD + 1;

   .CONST $codec.av_decode.PAUSE_TO_CLEAR_THRESHOLD 150;
   .CONST $codec.av_decode.STALL_TO_DECODE_THRESHOLD 70;
   .CONST $codec.av_encode.STALL_THRESHOLD 10;

   .CONST $codec.pre_post_proc.PRE_PROC_FUNC_ADDR_FIELD 0;
   .CONST $codec.pre_post_proc.PRE_PROC_FUNC_DATA1_FIELD 1;
   .CONST $codec.pre_post_proc.PRE_PROC_FUNC_DATA2_FIELD 2;
   .CONST $codec.pre_post_proc.POST_PROC_FUNC_ADDR_FIELD 3;
   .CONST $codec.pre_post_proc.POST_PROC_FUNC_DATA1_FIELD 4;
   .CONST $codec.pre_post_proc.POST_PROC_FUNC_DATA2_FIELD 5;
   .CONST $codec.pre_post_proc.STRUC_SIZE 6;

   .CONST $codec.stream_encode.mux.NEXT_SINK_HANDLER_FIELD 0;
   .CONST $codec.stream_encode.mux.STATE_FIELD 1;
   .CONST $codec.stream_encode.mux.PREV_READ_PNTR_FIELD 2;
   .CONST $codec.stream_encode.mux.AMOUNT_LEFT_TO_DISCARD_FIELD 3;
   .CONST $codec.stream_encode.mux.TERMINAL_FIELD 4;
   .CONST $codec.stream_encode.mux.PORT_FIELD 5;
   .CONST $codec.stream_encode.mux.BYTE_ALIGNMENT_FIELD 6;
   .CONST $codec.stream_encode.mux.CBUFFER_STRUC_FIELD 7;
   .CONST $codec.stream_encode.mux.STRUC_SIZE $codec.stream_encode.mux.CBUFFER_STRUC_FIELD + $cbuffer.STRUC_SIZE;
.linefile 20 "main.asm" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/spi_comm_library.h" 1
.linefile 28 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/spi_comm_library.h"
.CONST $SPI_COMM_VERSION 0x010000;


.CONST $spi_comm.NEXT_ADDR_FIELD 0;
.CONST $spi_comm.ID_FIELD 1;
.CONST $spi_comm.HANDLER_ADDR_FIELD 2;
.CONST $spi_comm.STRUC_SIZE 3;
.linefile 21 "main.asm" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 1
.linefile 15 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules_library.h" 1
.linefile 11 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules_library.h"
.CONST $CVC_VERSION 0x0001;
.linefile 16 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2

.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec500/aec500_library.h" 1
.linefile 16 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec500/aec500_library.h"
.CONST $AEC_500_VERSION 0x001000;


.CONST $M.AEC_500.CALLST.CONNECTING 2;


.CONST $M.AEC_500.AEC_L2Px_HB 0xF80000;


.CONST $M.AEC_500.L_MUA_ON 0xFF0000;
.CONST $M.AEC_500_HF.L_MUA_ON 0xFD0000;


.CONST $M.AEC_500.L_ALFA_A 0xFEA782;
.CONST $M.AEC_500_HF.L_ALFA_A 0xFCE929;


.CONST $M.AEC_500.CNG_G_ADJUST 0x727C97;


.CONST $M.AEC_500.Num_Auxillary_Taps 0;
.CONST $M.AEC_500_HF.Num_Auxillary_Taps 3;

.CONST $M.AEC_500.Num_Primary_Taps 2;
.CONST $M.AEC_500_HF.Num_Primary_Taps 8;

.CONST $M.AEC_500.RER_dim 64;


.CONST $M.AEC_500_WB.Num_HFK_Freq_Bins 129;
.CONST $M.AEC_500_WB.LPwrX_margin.overflow_bits -4;
.CONST $M.AEC_500_WB.LPwrX_margin.scale_factor (16.0/129.0);

.CONST $M.AEC_500_NB.Num_HFK_Freq_Bins 65;
.CONST $M.AEC_500_NB.LPwrX_margin.overflow_bits -3;
.CONST $M.AEC_500_NB.LPwrX_margin.scale_factor (8.0/65.0);
.linefile 60 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec500/aec500_library.h"
.CONST $M.AEC_500.OFFSET_E_REAL_PTR 0;


.CONST $M.AEC_500.OFFSET_E_IMAG_PTR $M.AEC_500.OFFSET_E_REAL_PTR +1;


.CONST $M.AEC_500.OFFSET_D_EXP_PTR $M.AEC_500.OFFSET_E_IMAG_PTR+1;


.CONST $M.AEC_500.OFFSET_D_REAL_PTR $M.AEC_500.OFFSET_D_EXP_PTR+1;


.CONST $M.AEC_500.OFFSET_D_IMAG_PTR $M.AEC_500.OFFSET_D_REAL_PTR +1;


.CONST $M.AEC_500.OFFSET_SCRPTR_Exp_Mts_adapt $M.AEC_500.OFFSET_D_IMAG_PTR+1;





.CONST $M.AEC_500.OFFSET_RER_EXT_FUNC_PTR $M.AEC_500.OFFSET_SCRPTR_Exp_Mts_adapt+1;

.CONST $M.AEC_500.OFFSET_RER_D_REAL_PTR $M.AEC_500.OFFSET_RER_EXT_FUNC_PTR+1;

.CONST $M.AEC_500.OFFSET_RER_D_IMAG_PTR $M.AEC_500.OFFSET_RER_D_REAL_PTR +1;


.CONST $M.AEC_500.OFFSET_PTR_Gr_imag $M.AEC_500.OFFSET_RER_D_IMAG_PTR+1;


.CONST $M.AEC_500.OFFSET_PTR_Gr_real $M.AEC_500.OFFSET_PTR_Gr_imag+1;


.CONST $M.AEC_500.OFFSET_PTR_SqGr $M.AEC_500.OFFSET_PTR_Gr_real+1;


.CONST $M.AEC_500.OFFSET_PTR_L2absGr $M.AEC_500.OFFSET_PTR_SqGr+1;


.CONST $M.AEC_500.OFFSET_PTR_LPwrD $M.AEC_500.OFFSET_PTR_L2absGr +1;


.CONST $M.AEC_500.OFFSET_SCRPTR_W_ri $M.AEC_500.OFFSET_PTR_LPwrD +1;


.CONST $M.AEC_500.OFFSET_SCRPTR_L_adaptR $M.AEC_500.OFFSET_SCRPTR_W_ri +1;


.CONST $M.AEC_500.OFFSET_RER_SQGRDEV $M.AEC_500.OFFSET_SCRPTR_L_adaptR +1;




.CONST $M.AEC_500.OFFSET_X_REAL_PTR $M.AEC_500.OFFSET_RER_SQGRDEV +1;


.CONST $M.AEC_500.OFFSET_X_IMAG_PTR $M.AEC_500.OFFSET_X_REAL_PTR +1;


.CONST $M.AEC_500.OFFSET_X_EXP_PTR $M.AEC_500.OFFSET_X_IMAG_PTR +1;


.CONST $M.AEC_500.OFFSET_OMS1_G_PTR $M.AEC_500.OFFSET_X_EXP_PTR +1;


.CONST $M.AEC_500.OFFSET_OMS1_D_NZ_PTR $M.AEC_500.OFFSET_OMS1_G_PTR +1;


.CONST $M.AEC_500.OFFSET_oms_adapt_G_PTR $M.AEC_500.OFFSET_OMS1_D_NZ_PTR +1;


.CONST $M.AEC_500.OFFSET_OMS2_G_PTR $M.AEC_500.OFFSET_oms_adapt_G_PTR +1;


.CONST $M.AEC_500.OFFSET_OMS_AGGRESSIVENESS $M.AEC_500.OFFSET_OMS2_G_PTR +1;


.CONST $M.AEC_500.OFFSET_CNG_Q_ADJUST $M.AEC_500.OFFSET_OMS_AGGRESSIVENESS +1;

.CONST $M.AEC_500.OFFSET_CNG_G_ADJUST $M.AEC_500.OFFSET_CNG_Q_ADJUST +1;


.CONST $M.AEC_500.OFFSET_DTC_AGRESSIVENESS $M.AEC_500.OFFSET_CNG_G_ADJUST +1;

.CONST $M.AEC_500.OFFSET_RER_WGT_L2PXR $M.AEC_500.OFFSET_DTC_AGRESSIVENESS +1;

.CONST $M.AEC_500.OFFSET_RER_WGT_L2PDR $M.AEC_500.OFFSET_RER_WGT_L2PXR +1;




.CONST $M.AEC_500.OFFSET_ENABLE_AEC_REUSE $M.AEC_500.OFFSET_RER_WGT_L2PDR +1;


.CONST $M.AEC_500.OFFSET_CONFIG $M.AEC_500.OFFSET_ENABLE_AEC_REUSE +1;


.CONST $M.AEC_500.OFFSET_MAX_LPWR_MARGIN $M.AEC_500.OFFSET_CONFIG +1;


.CONST $M.AEC_500.OFFSET_NUM_AUXILLARY_TAPS $M.AEC_500.OFFSET_MAX_LPWR_MARGIN+1;

.CONST $M.AEC_500.OFFSET_NUM_PRIMARY_TAPS $M.AEC_500.OFFSET_NUM_AUXILLARY_TAPS+1;



.CONST $M.AEC_500.OFFSET_NUM_FREQ_BINS $M.AEC_500.OFFSET_NUM_PRIMARY_TAPS+1;




.CONST $M.AEC_500.OFFSET_LPWRX_MARGIN_OVFL $M.AEC_500.OFFSET_NUM_FREQ_BINS+1;




.CONST $M.AEC_500.OFFSET_LPWRX_MARGIN_SCL $M.AEC_500.OFFSET_LPWRX_MARGIN_OVFL+1;




.CONST $M.AEC_500.OFFSET_RERCBA_ENABLE_MASK $M.AEC_500.OFFSET_LPWRX_MARGIN_SCL+1;



.CONST $M.AEC_500.OFFSET_RER_AGGRESSIVENESS $M.AEC_500.OFFSET_RERCBA_ENABLE_MASK+1;


.CONST $M.AEC_500.OFFSET_RER_WGT_SY $M.AEC_500.OFFSET_RER_AGGRESSIVENESS+1;


.CONST $M.AEC_500.OFFSET_RER_OFFSET_SY $M.AEC_500.OFFSET_RER_WGT_SY+1;


.CONST $M.AEC_500.OFFSET_RER_POWER $M.AEC_500.OFFSET_RER_OFFSET_SY+1;



.CONST $M.AEC_500.OFFSET_AEC_REF_LPWR_HB $M.AEC_500.OFFSET_RER_POWER+1;





.CONST $M.AEC_500.OFFSET_SCRPTR_RERDT_DTC $M.AEC_500.OFFSET_AEC_REF_LPWR_HB+1;


.CONST $M.AEC_500.OFFSET_L2TH_RERDT_OFF $M.AEC_500.OFFSET_SCRPTR_RERDT_DTC+1;


.CONST $M.AEC_500.OFFSET_RERDT_ADJUST $M.AEC_500.OFFSET_L2TH_RERDT_OFF+1;


.CONST $M.AEC_500.OFFSET_RERDT_POWER $M.AEC_500.OFFSET_RERDT_ADJUST+1;





.CONST $M.AEC_500.OFFSET_AEC_L_MUA_ON $M.AEC_500.OFFSET_RERDT_POWER+1;



.CONST $M.AEC_500.OFFSET_AEC_L_ALFA_A $M.AEC_500.OFFSET_AEC_L_MUA_ON+1;






.CONST $M.AEC_500.OFFSET_DT_FUNC1_PTR $M.AEC_500.OFFSET_AEC_L_ALFA_A+1;



.CONST $M.AEC_500.OFFSET_DT_FUNC2_PTR $M.AEC_500.OFFSET_DT_FUNC1_PTR+1;



.CONST $M.AEC_500.OFFSET_DTC_AGRESS_FUNC_PTR $M.AEC_500.OFFSET_DT_FUNC2_PTR+1;



.CONST $M.AEC_500.OFFSET_LPWRX_UPDT_FUNC_PTR $M.AEC_500.OFFSET_DTC_AGRESS_FUNC_PTR+1;



.CONST $M.AEC_500.OFFSET_RER_DIVERGE_FUNC_PTR $M.AEC_500.OFFSET_LPWRX_UPDT_FUNC_PTR+1;




.CONST $M.AEC_500.OFFSET_CONST_DM1 $M.AEC_500.OFFSET_RER_DIVERGE_FUNC_PTR+1;




.CONST $M.AEC_500.OFFSET_PTR_RcvBuf_real $M.AEC_500.OFFSET_CONST_DM1+1;


.CONST $M.AEC_500.OFFSET_PTR_RcvBuf_imag $M.AEC_500.OFFSET_PTR_RcvBuf_real+1;


.CONST $M.AEC_500.OFFSET_PTR_Ga_imag $M.AEC_500.OFFSET_PTR_RcvBuf_imag+1;


.CONST $M.AEC_500.OFFSET_PTR_Ga_real $M.AEC_500.OFFSET_PTR_Ga_imag+1;



.CONST $M.AEC_500.OFFSET_PTR_Gb_imag $M.AEC_500.OFFSET_PTR_Ga_real+1;



.CONST $M.AEC_500.OFFSET_PTR_Gb_real $M.AEC_500.OFFSET_PTR_Gb_imag+1;


.CONST $M.AEC_500.OFFSET_PTR_L2PxR $M.AEC_500.OFFSET_PTR_Gb_real+1;


.CONST $M.AEC_500.OFFSET_PTR_BExp_Ga $M.AEC_500.OFFSET_PTR_L2PxR+1;



.CONST $M.AEC_500.OFFSET_PTR_BExp_Gb $M.AEC_500.OFFSET_PTR_BExp_Ga+1;


.CONST $M.AEC_500.OFFSET_PTR_LPwrX0 $M.AEC_500.OFFSET_PTR_BExp_Gb+1;


.CONST $M.AEC_500.OFFSET_PTR_RatFE $M.AEC_500.OFFSET_PTR_LPwrX0+1;


.CONST $M.AEC_500.OFFSET_PTR_BExp_X_buf $M.AEC_500.OFFSET_PTR_RatFE+1;


.CONST $M.AEC_500.OFFSET_PTR_LpZ_nz $M.AEC_500.OFFSET_PTR_BExp_X_buf+1;


.CONST $M.AEC_500.OFFSET_PTR_LPwrX1 $M.AEC_500.OFFSET_PTR_LpZ_nz+1;




.CONST $M.AEC_500.OFFSET_SCRPTR_Attenuation $M.AEC_500.OFFSET_PTR_LPwrX1+1;


.CONST $M.AEC_500.OFFSET_SCRPTR_L_adaptA $M.AEC_500.OFFSET_SCRPTR_Attenuation+1;



.CONST $M.AEC_500.OFFSET_SCRPTR_L_RatSqGt $M.AEC_500.OFFSET_SCRPTR_L_adaptA+1;


.CONST $M.AEC_500.OFFSET_L_DTC $M.AEC_500.OFFSET_SCRPTR_L_RatSqGt+1;


.CONST $M.AEC_500.OFFSET_CNG_NOISE_COLOR $M.AEC_500.OFFSET_L_DTC+1;




.CONST $M.AEC_500.OFFSET_PTR_NZ_TABLES $M.AEC_500.OFFSET_CNG_NOISE_COLOR+1;

.CONST $M.AEC_500.OFFSET_PTR_CUR_NZ_TABLE $M.AEC_500.OFFSET_PTR_NZ_TABLES+1;



.CONST $M.AEC_500.OFFSET_L_RatSqG $M.AEC_500.OFFSET_PTR_CUR_NZ_TABLE+1;
.CONST $M.AEC_500.OFFSET_dL2PxFB $M.AEC_500.OFFSET_L_RatSqG+1;
.CONST $M.AEC_500.OFFSET_Exp_D $M.AEC_500.OFFSET_dL2PxFB+1;
.CONST $M.AEC_500.OFFSET_L2Pxt0 $M.AEC_500.OFFSET_Exp_D+1;
.CONST $M.AEC_500.OFFSET_DTC_dLpX $M.AEC_500.OFFSET_L2Pxt0+1;
.CONST $M.AEC_500.OFFSET_DTC_LpXt_prev $M.AEC_500.OFFSET_DTC_dLpX+1;


.CONST $M.AEC_500.OFFSET_tt_dtc $M.AEC_500.OFFSET_DTC_LpXt_prev+1;
.CONST $M.AEC_500.OFFSET_ct_init $M.AEC_500.OFFSET_tt_dtc+1;
.CONST $M.AEC_500.OFFSET_ct_Px $M.AEC_500.OFFSET_ct_init+1;
.CONST $M.AEC_500.OFFSET_tt_cng $M.AEC_500.OFFSET_ct_Px+1;
.CONST $M.AEC_500.OFFSET_CNG_offset $M.AEC_500.OFFSET_tt_cng+1;
.CONST $M.AEC_500.OFFSET_RER_func $M.AEC_500.OFFSET_CNG_offset+1;
.CONST $M.AEC_500.OFFSET_dgStartPtr $M.AEC_500.OFFSET_RER_func+1;

.CONST $M.AEC_500.OFFSET_dg_control_Freq_Bins $M.AEC_500.OFFSET_dgStartPtr+1;

.CONST $M.AEC_500.OFFSET_AEC_COUPLING $M.AEC_500.OFFSET_dg_control_Freq_Bins+1;
.CONST $M.AEC_500.OFFSET_HD_L_AECgain $M.AEC_500.OFFSET_AEC_COUPLING+1;

.CONST $M.AEC_500.OFFSET_LPXFB_RERDT $M.AEC_500.OFFSET_HD_L_AECgain+1;

.CONST $M.AEC_500.STRUCT_SIZE $M.AEC_500.OFFSET_LPXFB_RERDT+1;






.CONST $M.FDNLP_500.OFFSET_VSM_HB 0;
.CONST $M.FDNLP_500.OFFSET_VSM_LB $M.FDNLP_500.OFFSET_VSM_HB+1;
.CONST $M.FDNLP_500.OFFSET_VSM_MAX_ATT $M.FDNLP_500.OFFSET_VSM_LB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_HB $M.FDNLP_500.OFFSET_VSM_MAX_ATT+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_LB $M.FDNLP_500.OFFSET_FDNLP_HB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_MB $M.FDNLP_500.OFFSET_FDNLP_LB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_NBINS $M.FDNLP_500.OFFSET_FDNLP_MB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ATT $M.FDNLP_500.OFFSET_FDNLP_NBINS+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ATT_THRESH $M.FDNLP_500.OFFSET_FDNLP_ATT+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ECHO_THRESH $M.FDNLP_500.OFFSET_FDNLP_ATT_THRESH+1;
.CONST $M.FDNLP_500.STRUCT_SIZE $M.FDNLP_500.OFFSET_FDNLP_ECHO_THRESH+1;






.CONST $M.AEC_500_HF.OFFSET_D_REAL_PTR 0;


.CONST $M.AEC_500_HF.OFFSET_D_IMAG_PTR $M.AEC_500_HF.OFFSET_D_REAL_PTR+1;


.CONST $M.AEC_500_HF.OFFSET_NUM_FREQ_BINS $M.AEC_500_HF.OFFSET_D_IMAG_PTR+1;




.CONST $M.AEC_500_HF.OFFSET_HD_THRESH_GAIN $M.AEC_500_HF.OFFSET_NUM_FREQ_BINS+1;



.CONST $M.AEC_500_HF.OFFSET_CALLSTATE_PTR $M.AEC_500_HF.OFFSET_HD_THRESH_GAIN+1;


.CONST $M.AEC_500_HF.OFFSET_TIER2_THRESH $M.AEC_500_HF.OFFSET_CALLSTATE_PTR+1;


.CONST $M.AEC_500_HF.OFFSET_HC_TIER_STATE $M.AEC_500_HF.OFFSET_TIER2_THRESH+1;



.CONST $M.AEC_500_HF.OFFSET_PTR_RCV_DETECT $M.AEC_500_HF.OFFSET_HC_TIER_STATE+1;



.CONST $M.AEC_500_HF.OFFSET_PTR_TIER1_CONFIG $M.AEC_500_HF.OFFSET_PTR_RCV_DETECT+1;


.CONST $M.AEC_500_HF.OFFSET_PTR_TIER2_CONFIG $M.AEC_500_HF.OFFSET_PTR_TIER1_CONFIG+1;





.CONST $M.AEC_500_HF.HOWLING_CNTRL_FUNCPTR $M.AEC_500_HF.OFFSET_PTR_TIER2_CONFIG+1;




.CONST $M.AEC_500_HF.FDNLP_FUNCPTR $M.AEC_500_HF.HOWLING_CNTRL_FUNCPTR+1;




.CONST $M.AEC_500_HF.VSM_FUNCPTR $M.AEC_500_HF.FDNLP_FUNCPTR+1;





.CONST $M.AEC_500_HF.OFFSET_PTR_RatFE $M.AEC_500_HF.VSM_FUNCPTR+1;


.CONST $M.AEC_500_HF.OFFSET_PTR_SqGr $M.AEC_500_HF.OFFSET_PTR_RatFE+1;



.CONST $M.AEC_500_HF.OFFSET_SCRPTR_Attenuation $M.AEC_500_HF.OFFSET_PTR_SqGr+1;


.CONST $M.AEC_500_HF.OFFSET_SCRPTR_absGr $M.AEC_500_HF.OFFSET_SCRPTR_Attenuation+1;


.CONST $M.AEC_500_HF.OFFSET_SCRPTR_temp $M.AEC_500_HF.OFFSET_SCRPTR_absGr+1;


.CONST $M.AEC_500_HF.OFFSET_PTR_CUR_CONFIG $M.AEC_500_HF.OFFSET_SCRPTR_temp+1;
.CONST $M.AEC_500_HF.OFFSET_hd_ct_hold $M.AEC_500_HF.OFFSET_PTR_CUR_CONFIG+$M.FDNLP_500.STRUCT_SIZE;
.CONST $M.AEC_500_HF.OFFSET_hd_att $M.AEC_500_HF.OFFSET_hd_ct_hold+1;
.CONST $M.AEC_500_HF.OFFSET_G_vsm $M.AEC_500_HF.OFFSET_hd_att+1;
.CONST $M.AEC_500_HF.OFFSET_fdnlp_cont_test $M.AEC_500_HF.OFFSET_G_vsm+1;
.CONST $M.AEC_500_HF.OFFSET_mean_len $M.AEC_500_HF.OFFSET_fdnlp_cont_test+1;
.CONST $M.AEC_500_HF.OFFSET_Vad_ct_burst $M.AEC_500_HF.OFFSET_mean_len+1;
.CONST $M.AEC_500_HF.OFFSET_Vad_ct_hang $M.AEC_500_HF.OFFSET_Vad_ct_burst+1;

.CONST $M.AEC_500_HF.STRUCT_SIZE $M.AEC_500_HF.OFFSET_Vad_ct_hang+1;





.CONST $M.AEC_500.OFFSET_RER_VAR_THRESH $M.AEC_500.OFFSET_RER_SQGRDEV;


.CONST $M.AEC_500.L2TH_RERDT_OFF -20.0/128;
.CONST $M.AEC_500.RERDT_ADJUST 6.0/32;
.CONST $M.AEC_500.RERDT_POWER 1;





.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_E_REAL_PTR 0;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_E_IMAG_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_E_REAL_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_EXP_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_E_IMAG_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_REAL_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_D_EXP_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_IMAG_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_D_REAL_PTR+1;


.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt $M.TWOMIC_AEC.OFFSET_FNLMS_D_IMAG_PTR + 1;

.CONST $M.TWOMIC_AEC.OFFSET_PTR_MAIN_AEC $M.TWOMIC_AEC.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_BYPASS_AEC1 $M.TWOMIC_AEC.OFFSET_PTR_MAIN_AEC + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_Ga_real $M.TWOMIC_AEC.OFFSET_PTR_BYPASS_AEC1 + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_Ga_imag $M.TWOMIC_AEC.OFFSET_PTR_Ga_real + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_BExp_Ga $M.TWOMIC_AEC.OFFSET_PTR_Ga_imag + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_real $M.TWOMIC_AEC.OFFSET_PTR_BExp_Ga + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_imag $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_real + 1;

.CONST $M.TWOMIC_AEC.STRUCT_SIZE $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_imag + 1;
.linefile 18 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h" 1
.linefile 47 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h"
.CONST $FILTER_BANK_VERSION 0x030200;






   .CONST $M.filter_bank.Parameters.FRAME32 32;
   .CONST $M.filter_bank.Parameters.FRAME60 60;
   .CONST $M.filter_bank.Parameters.FRAME64 64;
   .CONST $M.filter_bank.Parameters.FRAME120 120;
   .CONST $M.filter_bank.Parameters.FRAME128 128;

   .CONST $M.filter_bank.Parameters.PROTO120 120;
   .CONST $M.filter_bank.Parameters.PROTO128 128;
   .CONST $M.filter_bank.Parameters.PROTO240 240;
   .CONST $M.filter_bank.Parameters.PROTO256 256;
   .CONST $M.filter_bank.Parameters.PROTO480 480;
   .CONST $M.filter_bank.Parameters.PROTO512 512;

   .CONST $M.filter_bank.Parameters.FFT128_SCALE 6;
   .CONST $M.filter_bank.Parameters.FFT256_SCALE 7;

   .CONST $M.filter_bank.Parameters.FFT128_NUM_BIN 65;
   .CONST $M.filter_bank.Parameters.FFT256_NUM_BIN 129;

   .CONST $M.filter_bank.Parameters.FFT128_BUFFLEN 64;
   .CONST $M.filter_bank.Parameters.FFT256_BUFFLEN 128;

   .CONST $M.filter_bank.Parameters.SPLIT_TABLELEN 63;
.linefile 91 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h"
   .CONST $M.filter_bank.Parameters.Q_DAT_IN 0;
   .CONST $M.filter_bank.Parameters.Q_DAT_OUT 0;





   .CONST $M.filter_bank.Parameters.FFT_EXTRA_SCALE 0;
   .CONST $M.filter_bank.Parameters.IFFT_EXTRA_SCALE 0;





   .CONST $M.filter_bank.CONST.MIN24 0x800000;





   .CONST $M.filter_bank.config.FRAME 0;
   .CONST $M.filter_bank.config.PROTO 1;
   .CONST $M.filter_bank.config.ZEROPADDED_PROTO 2;
   .CONST $M.filter_bank.config.FFT_SCALE 3;
   .CONST $M.filter_bank.config.PTR_PROTO 4;
   .CONST $M.filter_bank.config.STRUCT_SIZE 5;
.linefile 132 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h"
   .CONST $M.filter_bank.fft.NUM_POINTS_FIELD 0;



   .CONST $M.filter_bank.fft.REAL_ADDR_FIELD 1;



   .CONST $M.filter_bank.fft.IMAG_ADDR_FIELD 2;



   .CONST $M.filter_bank.fft.CBUF_ADDR_FIELD 3;


   .CONST $M.filter_bank.fft.CBUF_BITREV_ADDR_FIELD 4;


   .CONST $M.filter_bank.fft.PTR_FFTSPLIT 5;


   .CONST $M.filter_bank.fft.FFT_EXTRA_SCALE 6;


   .CONST $M.filter_bank.fft.IFFT_EXTRA_SCALE 7;


   .CONST $M.filter_bank.fft.Q_DAT_IN 8;


   .CONST $M.filter_bank.fft.Q_DAT_OUT 9;

   .CONST $M.filter_bank.fft.STRUC_SIZE 10;
.linefile 182 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h"
   .CONST $M.filter_bank.Parameters.OFFSET_CONFIG_OBJECT 0;


   .CONST $M.filter_bank.Parameters.OFFSET_PTR_FRAME 1;


   .CONST $M.filter_bank.Parameters.OFFSET_PTR_HISTORY 2;


   .CONST $M.filter_bank.Parameters.OFFSET_BEXP 3;


   .CONST $M.filter_bank.Parameters.OFFSET_PTR_BEXP 3;


   .CONST $M.filter_bank.Parameters.OFFSET_PTR_FFTREAL 4;


   .CONST $M.filter_bank.Parameters.OFFSET_PTR_FFTIMAG 5;


   .CONST $M.filter_bank.Parameters.OFFSET_DELAY_PTR 6;


   .CONST $M.filter_bank.Parameters.OFFSET_DELAY_BUF_BASE 7;


   .CONST $M.filter_bank.Parameters.OFFSET_DELAY_BUF_PTR 8;


   .CONST $M.filter_bank.Parameters.OFFSET_DELAY_BUF_LEN 9;

   .CONST $M.filter_bank.Parameters.ONE_CHNL_BLOCK_SIZE 10;
.linefile 232 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/filter_bank/filter_bank_library.h"
   .CONST $M.filter_bank.Parameters.OFFSET_CONFIG_OBJECT 0;



   .CONST $M.filter_bank.Parameters.OFFSET_CH1_PTR_FRAME 1;



   .CONST $M.filter_bank.Parameters.OFFSET_CH2_PTR_FRAME 2;


   .CONST $M.filter_bank.Parameters.OFFSET_CH1_PTR_HISTORY 3;


   .CONST $M.filter_bank.Parameters.OFFSET_CH2_PTR_HISTORY 4;


   .CONST $M.filter_bank.Parameters.OFFSET_CH1_BEXP 5;


   .CONST $M.filter_bank.Parameters.OFFSET_CH1_PTR_BEXP 5;


   .CONST $M.filter_bank.Parameters.OFFSET_CH2_BEXP 6;


   .CONST $M.filter_bank.Parameters.OFFSET_CH2_PTR_BEXP 6;



   .CONST $M.filter_bank.Parameters.OFFSET_CH1_PTR_FFTREAL 7;



   .CONST $M.filter_bank.Parameters.OFFSET_CH1_PTR_FFTIMAG 8;



   .CONST $M.filter_bank.Parameters.OFFSET_CH2_PTR_FFTREAL 9;



   .CONST $M.filter_bank.Parameters.OFFSET_CH2_PTR_FFTIMAG 10;



   .CONST $M.filter_bank.Parameters.OFFSET_CH2_DELAY_PTR 11;


   .CONST $M.filter_bank.Parameters.OFFSET_CH2_DELAY_BASE 12;



   .CONST $M.filter_bank.Parameters.OFFSET_CH2_DELAY_BUF_PTR 13;


   .CONST $M.filter_bank.Parameters.OFFSET_CH2_DELAY_BUF_LEN 14;


   .CONST $M.filter_bank.Parameters.TWO_CHNL_BLOCK_SIZE 15;
.linefile 19 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/harmonicity.h" 1
.linefile 14 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/harmonicity.h"
.CONST $harmonicity.WINDOW_LENGTH 30;
.CONST $harmonicity.DELAY_LENGTH 27;

.CONST $harmonicity.nb.FRAME_SIZE 60;
.CONST $harmonicity.nb.DELAY_START 53;
.CONST $harmonicity.nb.DECIMATION 2;

.CONST $harmonicity.wb.FRAME_SIZE 120;
.CONST $harmonicity.wb.DELAY_START 107;
.CONST $harmonicity.wb.DECIMATION 4;





.CONST $harmonicity.MODE_FIELD 0;
.CONST $harmonicity.INP_X_FIELD 1;
.CONST $harmonicity.FFT_WINDOW_SIZE_FIELD 2;
.CONST $harmonicity.FLAG_ON_FIELD 3;
.CONST $harmonicity.HARM_VALUE_FIELD 4;
.CONST $harmonicity.AMDF_MEM_START_FIELD 5;
.CONST $harmonicity.STRUC_SIZE ($harmonicity.AMDF_MEM_START_FIELD + $harmonicity.DELAY_LENGTH);





.CONST $harmonicity.mode.FRAME_SIZE 0;
.CONST $harmonicity.mode.DELAY_START 1;
.CONST $harmonicity.mode.DECIMATION 2;
.linefile 20 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h" 1
.linefile 27 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h"
.CONST $oms270.MAX_MIN_SEARCH_LENGTH 68;
.CONST $oms270.PBP.DIM_NB 25;
.CONST $oms270.PBP.DIM_WB 30;
.CONST $oms270.PBP.NUM_LINEAR_BAND 15;
.CONST $oms270.PBP.MS_BAND 2;
.CONST $oms270.PBP.NOISE_THRESHOLD 0.8;

.CONST $M.oms270.QUE_LENGTH ($oms270.MAX_MIN_SEARCH_LENGTH * $oms270.PBP.MS_BAND);
.CONST $M.oms270.narrow_band.STATE_LENGTH ($oms270.PBP.DIM_NB * 4 + 2 * $oms270.PBP.MS_BAND);
.CONST $M.oms270.wide_band.STATE_LENGTH ($oms270.PBP.DIM_WB * 4 + 2 * $oms270.PBP.MS_BAND);
.CONST $M.oms270.narrow_band.SCRATCH_LENGTH ($oms270.PBP.DIM_NB + 2 * ( 65-2-$oms270.PBP.NUM_LINEAR_BAND));
.CONST $M.oms270.wide_band.SCRATCH_LENGTH ($oms270.PBP.DIM_WB + 2 * (129-2-$oms270.PBP.NUM_LINEAR_BAND));
.CONST $M.oms270.NOISE_THRESHOLD ($oms270.PBP.NOISE_THRESHOLD);




.CONST $oms270.linear.DIM 65;
.CONST $oms270.linear.narrow_band.MS_BAND 2;
.CONST $oms270.linear.wide_band.MS_BAND 3;
.CONST $oms270.linear.NOISE_THRESHOLD 0.9;

.CONST $oms270.linear.narrow_band.QUE_LENGTH ($M.oms270.QUE_LENGTH);
.CONST $oms270.linear.wide_band.QUE_LENGTH ($oms270.MAX_MIN_SEARCH_LENGTH * $oms270.linear.wide_band.MS_BAND);
.CONST $oms270.linear.narrow_band.STATE_LENGTH ($oms270.linear.DIM * 2 + 2 * $oms270.linear.narrow_band.MS_BAND);
.CONST $oms270.linear.wide_band.STATE_LENGTH ($oms270.linear.DIM * 2 + 2 * $oms270.linear.wide_band.MS_BAND);
.CONST $oms270.linear.SCRATCH_LENGTH ($oms270.linear.DIM * 4 + $oms270.linear.wide_band.MS_BAND);




.CONST $dms100.DIM 65;
.CONST $dms100.MIN_SEARCH_LENGTH 34;
.CONST $dms100.MS_BAND 8;
.CONST $dms100.NOISE_THRESHOLD 0.8;

.CONST $dms100.QUE_LENGTH ($dms100.MIN_SEARCH_LENGTH * $dms100.MS_BAND);
.CONST $dms100.STATE_LENGTH ($dms100.DIM * 6 + $dms100.MS_BAND * 2);
.CONST $dms100.SCRATCH_LENGTH ($dms100.DIM * 4 + $dms100.MS_BAND);
.linefile 83 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h"
.CONST $M.oms270.PTR_MODE_FIELD 0;


.CONST $M.oms270.CONTROL_WORD_FIELD $M.oms270.PTR_MODE_FIELD + 1;


.CONST $M.oms270.BYPASS_BIT_MASK_FIELD $M.oms270.CONTROL_WORD_FIELD + 1;


.CONST $M.oms270.MIN_SEARCH_ON_FIELD $M.oms270.BYPASS_BIT_MASK_FIELD + 1;


.CONST $M.oms270.HARM_ON_FIELD $M.oms270.MIN_SEARCH_ON_FIELD + 1;


.CONST $M.oms270.MMSE_LSA_ON_FIELD $M.oms270.HARM_ON_FIELD + 1;


.CONST $M.oms270.FFT_WINDOW_SIZE_FIELD $M.oms270.MMSE_LSA_ON_FIELD + 1;


.CONST $M.oms270.PTR_INP_X_FIELD $M.oms270.FFT_WINDOW_SIZE_FIELD + 1;


.CONST $M.oms270.PTR_X_REAL_FIELD $M.oms270.PTR_INP_X_FIELD + 1;


.CONST $M.oms270.PTR_X_IMAG_FIELD $M.oms270.PTR_X_REAL_FIELD + 1;


.CONST $M.oms270.PTR_BEXP_X_FIELD $M.oms270.PTR_X_IMAG_FIELD + 1;


.CONST $M.oms270.PTR_Y_REAL_FIELD $M.oms270.PTR_BEXP_X_FIELD + 1;


.CONST $M.oms270.PTR_Y_IMAG_FIELD $M.oms270.PTR_Y_REAL_FIELD + 1;


.CONST $M.oms270.INITIAL_POWER_FIELD $M.oms270.PTR_Y_IMAG_FIELD + 1;


.CONST $M.oms270.LPX_QUEUE_START_FIELD $M.oms270.INITIAL_POWER_FIELD + 1;



.CONST $M.oms270.PTR_G_FIELD $M.oms270.LPX_QUEUE_START_FIELD + 1;


.CONST $M.oms270.PTR_LPXNZ_FIELD $M.oms270.PTR_G_FIELD + 1;


.CONST $M.oms270.PTR_STATE_FIELD $M.oms270.PTR_LPXNZ_FIELD + 1;


.CONST $M.oms270.PTR_SCRATCH_FIELD $M.oms270.PTR_STATE_FIELD + 1;


.CONST $M.oms270.ALFANZ_FIELD $M.oms270.PTR_SCRATCH_FIELD + 1;


.CONST $M.oms270.LALFAS_FIELD $M.oms270.ALFANZ_FIELD + 1;


.CONST $M.oms270.LALFAS1_FIELD $M.oms270.LALFAS_FIELD + 1;


.CONST $M.oms270.HARM_THRESH_FIELD $M.oms270.LALFAS1_FIELD + 1;


.CONST $M.oms270.VAD_THRESH_FIELD $M.oms270.HARM_THRESH_FIELD + 1;


.CONST $M.oms270.AGRESSIVENESS_FIELD $M.oms270.VAD_THRESH_FIELD + 1;


.CONST $M.oms270.PTR_TONE_FLAG_FIELD $M.oms270.AGRESSIVENESS_FIELD + 1;






.CONST $dms100.Y_FIELD 1 + $M.oms270.PTR_TONE_FLAG_FIELD;



.CONST $dms100.X_FIELD 1 + $dms100.Y_FIELD;



.CONST $dms100.D_FIELD 1 + $dms100.X_FIELD;



.CONST $dms100.PARAM_FIELD 1 + $dms100.D_FIELD;




.CONST $dms100.PTR_POWR_ADJUST_FIELD 1 + $dms100.PARAM_FIELD;



.CONST $dms100.PTR_DMS_MODE_FIELD 1 + $dms100.PTR_POWR_ADJUST_FIELD;



.CONST $dms100.INTERNAL_FIELD 1 + $dms100.PTR_DMS_MODE_FIELD;


.CONST $dms100.SPP_FIELD 0 + $dms100.INTERNAL_FIELD;
.CONST $dms100.LPDS_FIELD 1 + $dms100.SPP_FIELD;
.CONST $dms100.LPN_FIELD 1 + $dms100.LPDS_FIELD;
.CONST $dms100.VAD_T_LIKE_FIELD 1 + $dms100.LPN_FIELD;
.CONST $dms100.SNR_FIELD 1 + $dms100.VAD_T_LIKE_FIELD;


.CONST $dms100.MASTER_DMS_MODE_FIELD 1 + $dms100.SNR_FIELD;
.CONST $dms100.GSCHEME_FIELD 1 + $dms100.MASTER_DMS_MODE_FIELD;
.CONST $dms100.BYPASS_SPP_FIELD 1 + $dms100.GSCHEME_FIELD;
.CONST $dms100.BYPASS_GSMOOTH_FIELD 1 + $dms100.BYPASS_SPP_FIELD;
.CONST $dms100.BYPASS_NFLOOR_FIELD 1 + $dms100.BYPASS_GSMOOTH_FIELD;
.CONST $dms100.BYPASS_NLIFT_FIELD 1 + $dms100.BYPASS_NFLOOR_FIELD;


.CONST $dms100.VAD_VOICED_FIELD 1 + $dms100.BYPASS_NLIFT_FIELD;
.CONST $dms100.VAD_COUNT_FIELD 1 + $dms100.VAD_VOICED_FIELD;
.CONST $dms100.VAD_LIKE_MEAN_FIELD 1 + $dms100.VAD_COUNT_FIELD;
.CONST $dms100.DMS_MODE_FIELD 1 + $dms100.VAD_LIKE_MEAN_FIELD;


.CONST $M.oms270.DMS_COMMON_FIELD 1 + $dms100.DMS_MODE_FIELD;

.CONST $M.oms270.FUNC_MMS_LPXS_FIELD 0 + $M.oms270.DMS_COMMON_FIELD;
.CONST $M.oms270.FUNC_MMS_PROC_FIELD 1 + $M.oms270.DMS_COMMON_FIELD;
.CONST $M.oms270.PTR_HARM_VALUE_FIELD 2 + $M.oms270.DMS_COMMON_FIELD;
.CONST $M.oms270.LTILT_FIELD $M.oms270.PTR_HARM_VALUE_FIELD + 1;
.CONST $M.oms270.VOICED_FIELD $M.oms270.LTILT_FIELD + 1;
.CONST $M.oms270.MIN_SEARCH_COUNT_FIELD $M.oms270.VOICED_FIELD + 1;
.CONST $M.oms270.MIN_SEARCH_LENGTH_FIELD $M.oms270.MIN_SEARCH_COUNT_FIELD + 1;
.CONST $M.oms270.PTR_LPXS_FIELD $M.oms270.MIN_SEARCH_LENGTH_FIELD + 1;
.CONST $M.oms270.PTR_LPY_FIELD $M.oms270.PTR_LPXS_FIELD + 1;
.CONST $M.oms270.VOICED_COUNTER_FIELD $M.oms270.PTR_LPY_FIELD + 1;
.CONST $M.oms270.PTR_LPX_MIN_FIELD $M.oms270.VOICED_COUNTER_FIELD + 1;

.CONST $M.oms270.WIND_FIELD $M.oms270.PTR_LPX_MIN_FIELD + 1;
.CONST $M.oms270.WNR_OBJ_FIELD $M.oms270.WIND_FIELD + 1;
.CONST $M.oms270.FUNC_WIND_DETECT_FIELD $M.oms270.WNR_OBJ_FIELD + 1;
.CONST $M.oms270.FUNC_WIND_REDUCTION_FIELD $M.oms270.FUNC_WIND_DETECT_FIELD + 1;
.CONST $M.oms270.INITIALISED_FIELD $M.oms270.FUNC_WIND_REDUCTION_FIELD + 1;
.CONST $M.oms270.LIKE_MEAN_FIELD $M.oms270.INITIALISED_FIELD + 1;
.CONST $M.oms270.TEMP_FIELD $M.oms270.LIKE_MEAN_FIELD + 1;


.CONST $M.oms270.G_G_FIELD $M.oms270.TEMP_FIELD + 1;
.CONST $M.oms270.MS_LPN_FIELD $M.oms270.G_G_FIELD + 1;
.CONST $M.oms270.PTR_LPX_QUEUE_FIELD $M.oms270.MS_LPN_FIELD + 1;
.CONST $M.oms270.PTR_LPN_FIELD $M.oms270.PTR_LPX_QUEUE_FIELD + 1;


.CONST $M.oms270.SCRATCH_LPXT_FIELD $M.oms270.PTR_LPN_FIELD + 1;
.CONST $M.oms270.SCRATCH_LIKE_FIELD $M.oms270.SCRATCH_LPXT_FIELD + 1;
.CONST $M.oms270.SCRATCH_NZLIFT_FIELD $M.oms270.SCRATCH_LIKE_FIELD + 1;
.CONST $M.oms270.SCRATCH_LPNZLIFT_FIELD $M.oms270.SCRATCH_NZLIFT_FIELD + 1;
.CONST $M.oms270.SCRATCH_LTILT_FIELD $M.oms270.SCRATCH_LPNZLIFT_FIELD + 1;


.CONST $M.oms270.OMS_MODE_FLAG_FIELD $M.oms270.SCRATCH_LTILT_FIELD + 1;


.CONST $M.oms270.HARM_START_FIELD $M.oms270.OMS_MODE_FLAG_FIELD + 1;
.CONST $M.oms270.HAM_MODE_FIELD $M.oms270.HARM_START_FIELD + $harmonicity.MODE_FIELD;
.CONST $M.oms270.HAM_INP_X_FIELD $M.oms270.HARM_START_FIELD + $harmonicity.INP_X_FIELD;
.CONST $M.oms270.HAM_FFT_WINDOW_SIZE_FIELD $M.oms270.HARM_START_FIELD + $harmonicity.FFT_WINDOW_SIZE_FIELD;
.CONST $M.oms270.HAM_FLAG_ON_FIELD $M.oms270.HARM_START_FIELD + $harmonicity.FLAG_ON_FIELD;
.CONST $M.oms270.HARM_VALUE_FIELD $M.oms270.HARM_START_FIELD + $harmonicity.HARM_VALUE_FIELD;


.CONST $M.oms270.STRUC_SIZE $M.oms270.HARM_START_FIELD + $harmonicity.STRUC_SIZE;
.CONST $dms100.STRUC_SIZE $M.oms270.STRUC_SIZE;
.linefile 276 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h"
.CONST $M.oms270.wnr.FUNC_WNR_INIT_FIELD 0;


.CONST $M.oms270.wnr.PTR_WNR_PARAM_FIELD 1;


.CONST $M.oms270.wnr.PTR_RCVVAD_FLAG_FIELD 2;


.CONST $M.oms270.wnr.PTR_SNDVAD_FLAG_FIELD 3;


.CONST $M.oms270.wnr.SND_VAD_COUNT_FIELD 4;
.CONST $M.oms270.wnr.HOLD_FIELD 5;
.CONST $M.oms270.wnr.YWEI_FIELD 6;
.CONST $M.oms270.wnr.POWER_THRES_FIELD 7;
.CONST $M.oms270.wnr.POWER_LEVEL_FIELD 8;
.CONST $M.oms270.wnr.COUNT_FIELD 9;

.CONST $M.oms270.wnr.HIGH_BIN_FIELD 10;
.CONST $M.oms270.wnr.LOW_BIN_FIELD 11;
.CONST $M.oms270.wnr.ROLLOFF_IDX_FIELD 12;
.CONST $M.oms270.wnr.STRUC_SIZE 13;
.linefile 310 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h"
.CONST $M.oms270.param.WNR_AGRESSIVENESS_FIELD 0;


.CONST $M.oms270.param.WNR_POWER_THRESHOLD_FIELD 1;


.CONST $M.oms270.param.WNR_HOLD_FIELD 2;
.linefile 328 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/oms270/oms270_library.h"
.CONST $dms100.param.AGRESSIVENESS_FIELD 0;



.CONST $dms100.param.RESIDUAL_NFLOOR_FIELD 1;
.linefile 21 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ndvc100/ndvc100_library.h" 1
.linefile 38 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ndvc100/ndvc100_library.h"
   .CONST $NDVC_ALG1_0_0_VERSION 0x020000;


   .CONST $M.NDVC_Alg1_0_0.MAX_STEPS 8;
.linefile 61 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ndvc100/ndvc100_library.h"
.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_HYSTERESIS 0;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_ATK_TC 1;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_DEC_TC 2;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_NUMVOLSTEPS 3;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_MAXNOISELVL 4;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_MINNOISELVL 5;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_LB 6;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.OFFSET_NDVC_HB 7;


.CONST $M.NDVC_Alg1_0_0.PARAMETERS.BLOCKSIZE 8;







.CONST $M.NDVC_Alg1_0_0.OFFSET_CONTROL_WORD 0;


.CONST $M.NDVC_Alg1_0_0.OFFSET_BITMASK_BYPASS 1;


.CONST $M.NDVC_Alg1_0_0.OFFSET_MAXSTEPS 2;


.CONST $M.NDVC_Alg1_0_0.OFFSET_PTR_LPDNZ 3;


.CONST $M.NDVC_Alg1_0_0.OFFSET_PTR_PARAMS 4;


.CONST $M.NDVC_Alg1_0_0.OFFSET_CURVOLLEVEL 5;


.CONST $M.NDVC_Alg1_0_0.OFFSET_FILTSUMLPDNZ 6;


.CONST $M.NDVC_Alg1_0_0.OFFSET_NOISE_DELTA 7;


.CONST $M.NDVC_Alg1_0_0.OFFSET_INV_NUMBIN 8;


.CONST $M.NDVC_Alg1_0_0.OFFSET_NOISELVLTBL 9;


.CONST $M.NDVC_Alg1_0_0.BLOCK_SIZE 9;
.linefile 22 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/agc400/agc400_library.h" 1
.linefile 36 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/agc400/agc400_library.h"
.CONST $AGC400_VERSION 0x010000;
.linefile 50 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/agc400/agc400_library.h"
.CONST $M.agc400.Parameter.OFFSET_INITIAL_GAIN_FIELD 0;


.CONST $M.agc400.Parameter.OFFSET_AGC_TARGET_FIELD 1;


.CONST $M.agc400.Parameter.OFFSET_ATTACK_TC_FIELD 2;


.CONST $M.agc400.Parameter.OFFSET_DECAY_TC_FIELD 3;


.CONST $M.agc400.Parameter.OFFSET_ALPHA_A_90_FIELD 4;


.CONST $M.agc400.Parameter.OFFSET_ALPHA_D_90_FIELD 5;


.CONST $M.agc400.Parameter.OFFSET_G_MAX_FIELD 6;


.CONST $M.agc400.Parameter.OFFSET_START_COMP_FIELD 7;


.CONST $M.agc400.Parameter.OFFSET_COMP_FIELD 8;


.CONST $M.agc400.Parameter.OFFSET_INPUT_THRESHOLD_FIELD 9;


.CONST $M.agc400.Parameter.OFFSET_ATTACK_SPEED_FIELD 10;


.CONST $M.agc400.Parameter.OFFSET_ADAPT_THRESHOLD1_FIELD 11;


.CONST $M.agc400.Parameter.OFFSET_ADAPT_THRESHOLD2_FIELD 12;


.CONST $M.agc400.Parameter.OFFSET_G_MIN_FIELD 13;


.CONST $M.agc400.Parameter.STRUC_SIZE 14;







.CONST $M.agc400.OFFSET_SYS_CON_WORD_FIELD 0;


.CONST $M.agc400.OFFSET_BYPASS_BIT_MASK_FIELD 1;


.CONST $M.agc400.OFFSET_BYPASS_PERSIST_FIELD 2;


.CONST $M.agc400.OFFSET_PARAM_PTR_FIELD 3;


.CONST $M.agc400.OFFSET_PTR_INPUT_FIELD 4;


.CONST $M.agc400.OFFSET_PTR_OUTPUT_FIELD 5;


.CONST $M.agc400.OFFSET_PTR_VAD_VALUE_FIELD 6;


.CONST $M.agc400.OFFSET_HARD_LIMIT_FIELD 7;


.CONST $M.agc400.OFFSET_PTR_TONE_FLAG_FIELD 8;


.CONST $M.agc400.OFFSET_INPUT_LEVEL_FIELD 9;


.CONST $M.agc400.OFFSET_INPUT_LEVEL_MIN_FIELD 10;


.CONST $M.agc400.OFFSET_ONE_M_ATTACK_TC_FIELD 11;


.CONST $M.agc400.OFFSET_ONE_M_DECAY_TC_FIELD 12;


.CONST $M.agc400.OFFSET_ONE_M_ALPHA_A_90_FIELD 13;


.CONST $M.agc400.OFFSET_ONE_M_ALPHA_D_90_FIELD 14;


.CONST $M.agc400.OFFSET_G_MIN_FIELD 15;


.CONST $M.agc400.OFFSET_G_FIELD 16;


.CONST $M.agc400.OFFSET_G_REAL_FIELD 17;


.CONST $M.agc400.OFFSET_ONE_M_COMP_FIELD 18;


.CONST $M.agc400.OFFSET_PWR_SCALE_FIELD 19;


.CONST $M.agc400.OFFSET_FRAME_THRESHOLD_FIELD 20;


.CONST $M.agc400.OFFSET_FRAME_COUNTER_FIELD 21;


.CONST $M.agc400.OFFSET_PERSISTED_GAIN_FIELD 22;


.CONST $M.agc400.STRUC_SIZE 23;
.linefile 23 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/vad400/vad400_library.h" 1
.linefile 20 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/vad400/vad400_library.h"
.CONST $VAD400_VERSION 0x010000;
.linefile 33 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/vad400/vad400_library.h"
.CONST $M.vad400.Parameter.ATTACK_TC_FIELD 0;


.CONST $M.vad400.Parameter.DECAY_TC_FIELD 1;


.CONST $M.vad400.Parameter.ENVELOPE_TC_FIELD 2;


.CONST $M.vad400.Parameter.INIT_FRAME_THRESH_FIELD 3;


.CONST $M.vad400.Parameter.RATIO_FIELD 4;


.CONST $M.vad400.Parameter.MIN_SIGNAL_FIELD 5;


.CONST $M.vad400.Parameter.MIN_MAX_ENVELOPE_FIELD 6;


.CONST $M.vad400.Parameter.DELTA_THRESHOLD_FIELD 7;


.CONST $M.vad400.Parameter.COUNT_THRESHOLD_FIELD 8;


.CONST $M.vad400.Parameter.OBJECT_SIZE_FIELD 9;
.linefile 70 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/vad400/vad400_library.h"
.CONST $M.vad400.INPUT_PTR_FIELD 0;


.CONST $M.vad400.PARAM_PTR_FIELD 1;


.CONST $M.vad400.E_FILTER_FIELD 2;


.CONST $M.vad400.E_FILTER_MAX_FIELD 3;


.CONST $M.vad400.E_FILTER_MIN_FIELD 4;


.CONST $M.vad400.COUNTER_DELTA_FIELD 5;


.CONST $M.vad400.COUNTER_FIELD 6;


.CONST $M.vad400.FLAG_FIELD 7;


.CONST $M.vad400.OBJECT_SIZE_FIELD 8;
.linefile 24 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/AdapEq/AdapEq_library.h" 1
.linefile 11 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/AdapEq/AdapEq_library.h"
.CONST $ADAPEQ_VERSION 0x01000A;



.CONST $M.AdapEq.Num_AEQ_Bands 3;
.CONST $M.AdapEq.Bands_Buffer_Length ($M.AdapEq.Num_AEQ_Bands * 2);
.CONST $M.AdapEq.Scratch_Length 65;
.linefile 26 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/AdapEq/AdapEq_library.h"
.CONST $M.AdapEq.CONTROL_WORD_FIELD 0;


.CONST $M.AdapEq.BYPASS_BIT_MASK_FIELD $M.AdapEq.CONTROL_WORD_FIELD + 1;


.CONST $M.AdapEq.BEX_BIT_MASK_FIELD $M.AdapEq.BYPASS_BIT_MASK_FIELD + 1;


.CONST $M.AdapEq.NUM_FREQ_BINS $M.AdapEq.BEX_BIT_MASK_FIELD + 1;


.CONST $M.AdapEq.BEX_NOISE_LVL_FLAGS $M.AdapEq.NUM_FREQ_BINS + 1;


.CONST $M.AdapEq.PTR_X_REAL_FIELD $M.AdapEq.BEX_NOISE_LVL_FLAGS + 1;


.CONST $M.AdapEq.PTR_X_IMAG_FIELD $M.AdapEq.PTR_X_REAL_FIELD + 1;


.CONST $M.AdapEq.PTR_BEXP_X_FIELD $M.AdapEq.PTR_X_IMAG_FIELD + 1;


.CONST $M.AdapEq.PTR_Z_REAL_FIELD $M.AdapEq.PTR_BEXP_X_FIELD + 1;


.CONST $M.AdapEq.PTR_Z_IMAG_FIELD $M.AdapEq.PTR_Z_REAL_FIELD + 1;


.CONST $M.AdapEq.LOW_INDEX_FIELD $M.AdapEq.PTR_Z_IMAG_FIELD + 1;


.CONST $M.AdapEq.LOW_BW_FIELD $M.AdapEq.LOW_INDEX_FIELD + 1;


.CONST $M.AdapEq.LOG2_LOW_INDEX_DIF_FIELD $M.AdapEq.LOW_BW_FIELD + 1;


.CONST $M.AdapEq.MID_BW_FIELD $M.AdapEq.LOG2_LOW_INDEX_DIF_FIELD + 1;


.CONST $M.AdapEq.LOG2_MID_INDEX_DIF_FIELD $M.AdapEq.MID_BW_FIELD + 1;


.CONST $M.AdapEq.HIGH_BW_FIELD $M.AdapEq.LOG2_MID_INDEX_DIF_FIELD + 1;


.CONST $M.AdapEq.LOG2_HIGH_INDEX_DIF_FIELD $M.AdapEq.HIGH_BW_FIELD + 1;


.CONST $M.AdapEq.AEQ_EQ_COUNTER_FIELD $M.AdapEq.LOG2_HIGH_INDEX_DIF_FIELD + 1;


.CONST $M.AdapEq.AEQ_EQ_INIT_FRAME_FIELD $M.AdapEq.AEQ_EQ_COUNTER_FIELD + 1;

.CONST $M.AdapEq.AEQ_GAIN_LOW_FIELD $M.AdapEq.AEQ_EQ_INIT_FRAME_FIELD + 1;

.CONST $M.AdapEq.AEQ_GAIN_HIGH_FIELD $M.AdapEq.AEQ_GAIN_LOW_FIELD + 1;



.CONST $M.AdapEq.PTR_VAD_AGC_FIELD $M.AdapEq.AEQ_GAIN_HIGH_FIELD + 1;


.CONST $M.AdapEq.ALFA_A_FIELD $M.AdapEq.PTR_VAD_AGC_FIELD + 1;


.CONST $M.AdapEq.ONE_MINUS_ALFA_A_FIELD $M.AdapEq.ALFA_A_FIELD + 1;


.CONST $M.AdapEq.ALFA_D_FIELD $M.AdapEq.ONE_MINUS_ALFA_A_FIELD + 1;


.CONST $M.AdapEq.ONE_MINUS_ALFA_D_FIELD $M.AdapEq.ALFA_D_FIELD + 1;


.CONST $M.AdapEq.ALFA_ENV_FIELD $M.AdapEq.ONE_MINUS_ALFA_D_FIELD + 1;


.CONST $M.AdapEq.ONE_MINUS_ALFA_ENV_FIELD $M.AdapEq.ALFA_ENV_FIELD + 1;


.CONST $M.AdapEq.PTR_AEQ_BAND_PX_FIELD $M.AdapEq.ONE_MINUS_ALFA_ENV_FIELD + 1;


.CONST $M.AdapEq.STATE_FIELD $M.AdapEq.PTR_AEQ_BAND_PX_FIELD + 1;


.CONST $M.AdapEq.PTR_VOL_STEP_UP_FIELD $M.AdapEq.STATE_FIELD + 1;


.CONST $M.AdapEq.VOL_STEP_UP_TH1_FIELD $M.AdapEq.PTR_VOL_STEP_UP_FIELD + 1;


.CONST $M.AdapEq.VOL_STEP_UP_TH2_FIELD $M.AdapEq.VOL_STEP_UP_TH1_FIELD + 1;


.CONST $M.AdapEq.PTR_GOAL_LOW_FIELD $M.AdapEq.VOL_STEP_UP_TH2_FIELD + 1;


.CONST $M.AdapEq.PTR_GOAL_HIGH_FIELD $M.AdapEq.PTR_GOAL_LOW_FIELD + 1;


.CONST $M.AdapEq.PTR_BEX_ATT_TOTAL_FIELD $M.AdapEq.PTR_GOAL_HIGH_FIELD + 1;


.CONST $M.AdapEq.PTR_BEX_GOAL_HIGH2_FIELD $M.AdapEq.PTR_BEX_ATT_TOTAL_FIELD + 1;


.CONST $M.AdapEq.BEX_PASS_LOW_FIELD $M.AdapEq.PTR_BEX_GOAL_HIGH2_FIELD + 1;


.CONST $M.AdapEq.BEX_PASS_HIGH_FIELD $M.AdapEq.BEX_PASS_LOW_FIELD + 1;


.CONST $M.AdapEq.MID1_INDEX_FIELD $M.AdapEq.BEX_PASS_HIGH_FIELD + 1;


.CONST $M.AdapEq.MID2_INDEX_FIELD $M.AdapEq.MID1_INDEX_FIELD + 1;


.CONST $M.AdapEq.HIGH_INDEX_FIELD $M.AdapEq.MID2_INDEX_FIELD + 1;


.CONST $M.AdapEq.INV_AEQ_PASS_LOW_FIELD $M.AdapEq.HIGH_INDEX_FIELD + 1;


.CONST $M.AdapEq.INV_AEQ_PASS_HIGH_FIELD $M.AdapEq.INV_AEQ_PASS_LOW_FIELD + 1;


.CONST $M.AdapEq.AEQ_PASS_LOW_FIELD $M.AdapEq.INV_AEQ_PASS_HIGH_FIELD + 1;


.CONST $M.AdapEq.AEQ_PASS_HIGH_FIELD $M.AdapEq.AEQ_PASS_LOW_FIELD + 1;




.CONST $M.AdapEq.AEQ_POWER_TH_FIELD $M.AdapEq.AEQ_PASS_HIGH_FIELD + 1;


.CONST $M.AdapEq.AEQ_TONE_POWER_FIELD $M.AdapEq.AEQ_POWER_TH_FIELD + 1;


.CONST $M.AdapEq.AEQ_MIN_GAIN_TH_FIELD $M.AdapEq.AEQ_TONE_POWER_FIELD + 1;


.CONST $M.AdapEq.AEQ_MAX_GAIN_TH_FIELD $M.AdapEq.AEQ_MIN_GAIN_TH_FIELD + 1;


.CONST $M.AdapEq.AEQ_POWER_TEST_FIELD $M.AdapEq.AEQ_MAX_GAIN_TH_FIELD + 1;


.CONST $M.AdapEq.PTR_SCRATCH_G_FIELD $M.AdapEq.AEQ_POWER_TEST_FIELD + 1;


.CONST $M.AdapEq.STRUC_SIZE $M.AdapEq.PTR_SCRATCH_G_FIELD + 1;
.linefile 25 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf100/adf100_library.h" 1
.linefile 27 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf100/adf100_library.h"
.CONST $M.adf_alg_1_0_0_VERSION 0x010000;



.CONST $M.adf_alg_1_0_0.ADF_num_proc 55;
.CONST $M.adf_alg_1_0_0.Num_Taps 4;


.CONST $M.adf_alg_1_0_0.DATA_SIZE_DM1 (23 + 2*$M.adf_alg_1_0_0.Num_Taps)*$M.adf_alg_1_0_0.ADF_num_proc;

.CONST $M.adf_alg_1_0_0.DATA_SIZE_DM2 (19 + 2*$M.adf_alg_1_0_0.Num_Taps)*$M.adf_alg_1_0_0.ADF_num_proc + $M.adf_alg_1_0_0.Num_Taps+1;

.CONST $M.adf_alg_1_0_0.SCRATCH_SIZE_DM1 (5 * $M.adf_alg_1_0_0.ADF_num_proc);
.CONST $M.adf_alg_1_0_0.SCRATCH_SIZE_DM2 (1 * $M.adf_alg_1_0_0.ADF_num_proc);

.CONST $M.adf_alg_1_0_0.MGDC_param.Th0 3.98631371386483/128;
.CONST $M.adf_alg_1_0_0.MGDC_param.Th1 3.98631371386483/128;
.linefile 64 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf100/adf100_library.h"
.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_E_REAL_PTR 0;

.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_E_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_FNLMS_E_REAL_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_D_EXP_PTR $M.adf_alg_1_0_0.OFFSET_FNLMS_E_IMAG_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_D_REAL_PTR $M.adf_alg_1_0_0.OFFSET_FNLMS_D_EXP_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_D_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_FNLMS_D_REAL_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt $M.adf_alg_1_0_0.OFFSET_FNLMS_D_IMAG_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_RER_EXT_FUNC_PTR $M.adf_alg_1_0_0.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_D_REAL_PTR $M.adf_alg_1_0_0.OFFSET_RER_EXT_FUNC_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_D_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_RER_D_REAL_PTR +1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_PTR_Gr_imag $M.adf_alg_1_0_0.OFFSET_RER_D_IMAG_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_PTR_Gr_real $M.adf_alg_1_0_0.OFFSET_RER_PTR_Gr_imag+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_PTR_SqGr $M.adf_alg_1_0_0.OFFSET_RER_PTR_Gr_real+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_PTR_L2absGr $M.adf_alg_1_0_0.OFFSET_RER_PTR_SqGr+1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_PTR_LPwrD $M.adf_alg_1_0_0.OFFSET_RER_PTR_L2absGr +1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_SCRPTR_W_ri $M.adf_alg_1_0_0.OFFSET_RER_PTR_LPwrD +1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_SCRPTR_L_adaptR $M.adf_alg_1_0_0.OFFSET_RER_SCRPTR_W_ri +1;

.CONST $M.adf_alg_1_0_0.OFFSET_RER_SQGRDEV $M.adf_alg_1_0_0.OFFSET_RER_SCRPTR_L_adaptR +1;





.CONST $M.adf_alg_1_0_0.OFFSET_X0_REAL_PTR $M.adf_alg_1_0_0.OFFSET_RER_SQGRDEV+1;


.CONST $M.adf_alg_1_0_0.OFFSET_X0_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_X0_REAL_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_X0_EXP_PTR $M.adf_alg_1_0_0.OFFSET_X0_IMAG_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_ADF_LPx0 $M.adf_alg_1_0_0.OFFSET_X0_EXP_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_X1_REAL_PTR $M.adf_alg_1_0_0.OFFSET_ADF_LPx0+1;


.CONST $M.adf_alg_1_0_0.OFFSET_X1_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_X1_REAL_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_X1_EXP_PTR $M.adf_alg_1_0_0.OFFSET_X1_IMAG_PTR+1;

.CONST $M.adf_alg_1_0_0.OFFSET_ADF_LPx1 $M.adf_alg_1_0_0.OFFSET_X1_EXP_PTR+1;




.CONST $M.adf_alg_1_0_0.OFFSET_PTR_DM1data $M.adf_alg_1_0_0.OFFSET_ADF_LPx1+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PTR_DM2data $M.adf_alg_1_0_0.OFFSET_PTR_DM1data+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PTR_DM1const $M.adf_alg_1_0_0.OFFSET_PTR_DM2data+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PTR_DM1tables $M.adf_alg_1_0_0.OFFSET_PTR_DM1const+1;
.linefile 147 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf100/adf100_library.h"
.CONST $M.adf_alg_1_0_0.OFFSET_SCRATCH_DM1 $M.adf_alg_1_0_0.OFFSET_PTR_DM1tables+1;




.CONST $M.adf_alg_1_0_0.OFFSET_SCRATCH_DM2 $M.adf_alg_1_0_0.OFFSET_SCRATCH_DM1+1;




.CONST $M.adf_alg_1_0_0.OFFSET_OMS_G_PTR $M.adf_alg_1_0_0.OFFSET_SCRATCH_DM2+1;


.CONST $M.adf_alg_1_0_0.OFFSET_E_OUT_REAL_PTR $M.adf_alg_1_0_0.OFFSET_OMS_G_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_E_OUT_IMAG_PTR $M.adf_alg_1_0_0.OFFSET_E_OUT_REAL_PTR+1;




.CONST $M.adf_alg_1_0_0.OFFSET_POSTPROC_FUNCPTR $M.adf_alg_1_0_0.OFFSET_E_OUT_IMAG_PTR+1;



.CONST $M.adf_alg_1_0_0.OFFSET_L_POSTP_CTRL_PTR $M.adf_alg_1_0_0.OFFSET_POSTPROC_FUNCPTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_NUMFREQ_BINS $M.adf_alg_1_0_0.OFFSET_L_POSTP_CTRL_PTR+1;




.CONST $M.adf_alg_1_0_0.OFFSET_CONTROL $M.adf_alg_1_0_0.OFFSET_NUMFREQ_BINS+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_PREP $M.adf_alg_1_0_0.OFFSET_CONTROL+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_MGDC $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_PREP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_WIDE_MIC_ENA $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_MGDC+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_RPT_POSTP $M.adf_alg_1_0_0.OFFSET_BITMASK_WIDE_MIC_ENA+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_ADFPS $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_RPT_POSTP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_ADFRNR $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_ADFPS+1;



.CONST $M.adf_alg_1_0_0.OFFSET_PP_GAMMAP $M.adf_alg_1_0_0.OFFSET_BITMASK_BYPASS_ADFRNR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PP_THRES $M.adf_alg_1_0_0.OFFSET_PP_GAMMAP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PP_VAD_DETECT $M.adf_alg_1_0_0.OFFSET_PP_THRES+1;



.CONST $M.adf_alg_1_0_0.OFFSET_PP_VAD_THRES $M.adf_alg_1_0_0.OFFSET_PP_VAD_DETECT+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PP_CTRL_BIAS $M.adf_alg_1_0_0.OFFSET_PP_VAD_THRES+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PP_CTRL_TRANS $M.adf_alg_1_0_0.OFFSET_PP_CTRL_BIAS+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_ALFAD $M.adf_alg_1_0_0.OFFSET_PP_CTRL_TRANS+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_FRONTMICBIAS $M.adf_alg_1_0_0.OFFSET_MGDC_ALFAD+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_MAXCOMP $M.adf_alg_1_0_0.OFFSET_MGDC_FRONTMICBIAS+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_ADAPT_THRESH $M.adf_alg_1_0_0.OFFSET_MGDC_MAXCOMP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_K_LB $M.adf_alg_1_0_0.OFFSET_MGDC_ADAPT_THRESH+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_K_HB $M.adf_alg_1_0_0.OFFSET_MGDC_K_LB+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_MEAN_SCL_EXP $M.adf_alg_1_0_0.OFFSET_MGDC_K_HB+1;

.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_MEAN_SCL_MTS $M.adf_alg_1_0_0.OFFSET_MGDC_MEAN_SCL_EXP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_TH0 $M.adf_alg_1_0_0.OFFSET_MGDC_MEAN_SCL_MTS+1;


.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_TH1 $M.adf_alg_1_0_0.OFFSET_MGDC_TH0+1;


.CONST $M.adf_alg_1_0_0.OFFSET_VAD_RCV_FIELD $M.adf_alg_1_0_0.OFFSET_MGDC_TH1+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PTR_WIND_DETECT $M.adf_alg_1_0_0.OFFSET_VAD_RCV_FIELD+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PTR_ADF_HOLD $M.adf_alg_1_0_0.OFFSET_PTR_WIND_DETECT+1;


.CONST $M.adf_alg_1_0_0.OFFSET_DMSS_WEIGHT $M.adf_alg_1_0_0.OFFSET_PTR_ADF_HOLD+1;


.CONST $M.adf_alg_1_0_0.OFFSET_OMS_LPXNZ_PTR $M.adf_alg_1_0_0.OFFSET_DMSS_WEIGHT+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPS_ON $M.adf_alg_1_0_0.OFFSET_OMS_LPXNZ_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPS_OFF $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPS_ON+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_CLEAN $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPS_OFF+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_NOISY $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_CLEAN+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_POSTP $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_NOISY+1;


.CONST $M.adf_alg_1_0_0.OFFSET_TH_ADF_DLPZ $M.adf_alg_1_0_0.OFFSET_L2TH_ADFPSV_POSTP+1;


.CONST $M.adf_alg_1_0_0.OFFSET_PREP_DT_MIC $M.adf_alg_1_0_0.OFFSET_TH_ADF_DLPZ+1;


.CONST $M.adf_alg_1_0_0.OFFSET_SQRT_PREP_SUBFACTOR $M.adf_alg_1_0_0.OFFSET_PREP_DT_MIC+1;


.CONST $M.adf_alg_1_0_0.OFFSET_REPL_ADJUST $M.adf_alg_1_0_0.OFFSET_SQRT_PREP_SUBFACTOR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_REPL_POWER $M.adf_alg_1_0_0.OFFSET_REPL_ADJUST+1;
.linefile 307 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf100/adf100_library.h"
.CONST $M.adf_alg_1_0_0.OFFSET_RNR_ALFA $M.adf_alg_1_0_0.OFFSET_REPL_POWER+1;


.CONST $M.adf_alg_1_0_0.OFFSET_RNR_ADJUST $M.adf_alg_1_0_0.OFFSET_RNR_ALFA+1;


.CONST $M.adf_alg_1_0_0.OFFSET_RNR_BIAS $M.adf_alg_1_0_0.OFFSET_RNR_ADJUST+1;


.CONST $M.adf_alg_1_0_0.OFFSET_RNR_TRANS $M.adf_alg_1_0_0.OFFSET_RNR_BIAS+1;




.CONST $M.adf_alg_1_0_0.OFFSET_L2FBpXD $M.adf_alg_1_0_0.OFFSET_RNR_TRANS+1;




.CONST $M.adf_alg_1_0_0.OFFSET_INTERNAL_START $M.adf_alg_1_0_0.OFFSET_L2FBpXD+1;



.CONST $M.adf_alg_1_0_0.OFFSET_PTR_V0_real $M.adf_alg_1_0_0.OFFSET_INTERNAL_START+0;
.CONST $M.adf_alg_1_0_0.OFFSET_PTR_V0_imag $M.adf_alg_1_0_0.OFFSET_PTR_V0_real+1;
.CONST $M.adf_alg_1_0_0.OFFSET_V0_EXP_PTR $M.adf_alg_1_0_0.OFFSET_PTR_V0_imag+1;
.CONST $M.adf_alg_1_0_0.OFFSET_ADF_LPz0 $M.adf_alg_1_0_0.OFFSET_V0_EXP_PTR+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PTR_V1_real $M.adf_alg_1_0_0.OFFSET_ADF_LPz0+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PTR_V1_imag $M.adf_alg_1_0_0.OFFSET_PTR_V1_real+1;
.CONST $M.adf_alg_1_0_0.OFFSET_V1_EXP_PTR $M.adf_alg_1_0_0.OFFSET_PTR_V1_imag+1;
.CONST $M.adf_alg_1_0_0.OFFSET_ADF_LPz1 $M.adf_alg_1_0_0.OFFSET_V1_EXP_PTR+1;


.CONST $M.adf_alg_1_0_0.OFFSET_muAt $M.adf_alg_1_0_0.OFFSET_ADF_LPz1+1;


.CONST $M.adf_alg_1_0_0.OFFSET_ct_Px0 $M.adf_alg_1_0_0.OFFSET_muAt+1;
.CONST $M.adf_alg_1_0_0.OFFSET_dL2Px0FB $M.adf_alg_1_0_0.OFFSET_ct_Px0+1;
.CONST $M.adf_alg_1_0_0.OFFSET_L2Px0t0 $M.adf_alg_1_0_0.OFFSET_dL2Px0FB+1;

.CONST $M.adf_alg_1_0_0.OFFSET_ct_Px1 $M.adf_alg_1_0_0.OFFSET_L2Px0t0+1;
.CONST $M.adf_alg_1_0_0.OFFSET_dL2Px1FB $M.adf_alg_1_0_0.OFFSET_ct_Px1+1;
.CONST $M.adf_alg_1_0_0.OFFSET_L2Px1t0 $M.adf_alg_1_0_0.OFFSET_dL2Px1FB+1;

.CONST $M.adf_alg_1_0_0.OFFSET_ct_init $M.adf_alg_1_0_0.OFFSET_L2Px1t0+1;

.CONST $M.adf_alg_1_0_0.OFFSET_MGDCexp $M.adf_alg_1_0_0.OFFSET_ct_init+1;
.CONST $M.adf_alg_1_0_0.OFFSET_MGDCmts $M.adf_alg_1_0_0.OFFSET_MGDCexp+1;

.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_L2FBpXDst $M.adf_alg_1_0_0.OFFSET_MGDCmts+1;
.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_hold_adapt $M.adf_alg_1_0_0.OFFSET_MGDC_L2FBpXDst+1;
.CONST $M.adf_alg_1_0_0.OFFSET_MGDC_switch_output $M.adf_alg_1_0_0.OFFSET_MGDC_hold_adapt+1;
.CONST $M.adf_alg_1_0_0.OFFSET_adfps_option_func $M.adf_alg_1_0_0.OFFSET_MGDC_switch_output+1;
.CONST $M.adf_alg_1_0_0.OFFSET_adfps_mode $M.adf_alg_1_0_0.OFFSET_adfps_option_func+1;
.CONST $M.adf_alg_1_0_0.OFFSET_ADF_Diff_LPz $M.adf_alg_1_0_0.OFFSET_adfps_mode+1;

.CONST $M.adf_alg_1_0_0.OFFSET_PreP_func_ptr $M.adf_alg_1_0_0.OFFSET_ADF_Diff_LPz+1;

.CONST $M.adf_alg_1_0_0.OFFSET_PreP_sub_factor $M.adf_alg_1_0_0.OFFSET_PreP_func_ptr+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PreP_sub_factor_T $M.adf_alg_1_0_0.OFFSET_PreP_sub_factor+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PreP_G_mgdc_fmb $M.adf_alg_1_0_0.OFFSET_PreP_sub_factor_T+1;

.CONST $M.adf_alg_1_0_0.OFFSET_G_RatioX1X0 $M.adf_alg_1_0_0.OFFSET_PreP_G_mgdc_fmb+1;
.CONST $M.adf_alg_1_0_0.OFFSET_ADF_LALFALPZ $M.adf_alg_1_0_0.OFFSET_G_RatioX1X0+1;

.CONST $M.adf_alg_1_0_0.OFFSET_num_taps $M.adf_alg_1_0_0.OFFSET_ADF_LALFALPZ+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PP_kL $M.adf_alg_1_0_0.OFFSET_num_taps+1;
.CONST $M.adf_alg_1_0_0.OFFSET_PP_kH $M.adf_alg_1_0_0.OFFSET_PP_kL+1;
.CONST $M.adf_alg_1_0_0.OFFSET_compara_mn_factor $M.adf_alg_1_0_0.OFFSET_PP_kH+1;


.CONST $M.adf_alg_1_0_0.OFFSET_bypass_mgdc $M.adf_alg_1_0_0.OFFSET_compara_mn_factor+1;
.CONST $M.adf_alg_1_0_0.OFFSET_bypass_postp_rpt $M.adf_alg_1_0_0.OFFSET_bypass_mgdc+1;
.CONST $M.adf_alg_1_0_0.OFFSET_wide_mic_enabled $M.adf_alg_1_0_0.OFFSET_bypass_postp_rpt+1;


.CONST $M.adf_alg_1_0_0.OFFSET_L2Th_adfps $M.adf_alg_1_0_0.OFFSET_wide_mic_enabled+1;
.CONST $M.adf_alg_1_0_0.OFFSET_L2Th_adfps_alpha $M.adf_alg_1_0_0.OFFSET_L2Th_adfps+1;


.CONST $M.adf_alg_1_0_0.OFFSET_LpXfb_adfps $M.adf_alg_1_0_0.OFFSET_L2Th_adfps_alpha+1;
.CONST $M.adf_alg_1_0_0.OFFSET_LpXfb_adfps_alpha $M.adf_alg_1_0_0.OFFSET_LpXfb_adfps+1;


.CONST $M.adf_alg_1_0_0.OFFSET_LpVa $M.adf_alg_1_0_0.OFFSET_LpXfb_adfps_alpha+1;
.CONST $M.adf_alg_1_0_0.OFFSET_LpVa_alpha $M.adf_alg_1_0_0.OFFSET_LpVa+1;


.CONST $M.adf_alg_1_0_0.OFFSET_LpVp $M.adf_alg_1_0_0.OFFSET_LpVa_alpha+1;
.CONST $M.adf_alg_1_0_0.OFFSET_LpVp_alpha $M.adf_alg_1_0_0.OFFSET_LpVp+1;


.CONST $M.adf_alg_1_0_0.OFFSET_RNR_BYPASS_FLAG $M.adf_alg_1_0_0.OFFSET_LpVp_alpha+1;
.CONST $M.adf_alg_1_0_0.OFFSET_RNR_DIFF_DLPZ $M.adf_alg_1_0_0.OFFSET_RNR_BYPASS_FLAG+1;
.CONST $M.adf_alg_1_0_0.OFFSET_RNR_ADJUST_USED $M.adf_alg_1_0_0.OFFSET_RNR_DIFF_DLPZ+1;


.CONST $M.adf_alg_1_0_0.OFFSET_G_HB $M.adf_alg_1_0_0.OFFSET_RNR_ADJUST_USED+1;


.CONST $M.adf_alg_1_0_0.STRUCT_SIZE $M.adf_alg_1_0_0.OFFSET_G_HB+1;




.CONST $MAX_24 0x7fffff;
.CONST $MIN_24 0x800000;
.CONST $MIN_48_MSB 0x800000;
.CONST $MIN_48_LSB 0;
.CONST $MAX_48_MSB 0x7fffff;
.CONST $MAX_48_LSB 0xffffff;
.linefile 26 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ssr/ssr_library.h" 1
.linefile 16 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ssr/ssr_library.h"
.CONST $SSR_VERSION 0x010200;
.linefile 31 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/ssr/ssr_library.h"
.CONST $M.SSR.SAMP_FREQ 8000;
.CONST $M.SSR.FRAME_SIZE 128;
.CONST $M.SSR.FFT_SIZE $M.SSR.FRAME_SIZE;
.CONST $M.SSR.NUM_FILTERS 23;
.CONST $M.SSR.MFCC_ORDER 12;
.CONST $M.SSR.L2_FFTS2 6;
.CONST $M.SSR.ENORM 356;
.CONST $M.SSR.KLOG2 2839;
.CONST $M.SSR.MAX_REG 0x7FFFFF;
.CONST $M.SSR.MIN_REG 0x800000;

.CONST $M.SSR.NMODELS 5;
.CONST $M.SSR.NSTATES 5;
.CONST $M.SSR.NPARAMS ($M.SSR.MFCC_ORDER+1);
.CONST $M.SSR.DELTAWIN 2;
.CONST $M.SSR.OBS_SIZE ($M.SSR.NPARAMS*$M.SSR.DELTAWIN);
.CONST $M.SSR.REGRESS_COLS (2*$M.SSR.DELTAWIN+1);
.CONST $M.SSR.LZERO ($M.SSR.MIN_REG + (4*(1<<12)));
.CONST $M.SSR.DELTACONST (409);
.CONST $M.SSR.BEAMTHRESHOLD ($M.SSR.LZERO>>1);




.CONST $M.SSR.WORD_TOO_SHORT 7;
.CONST $M.SSR.MIN_FINAL_STATES 2;





.CONST $M.SSR.MIN_SUCC_ST 0;
.CONST $M.SSR.MIN_MAIN_ST 0;

.CONST $M.SSR.FORCE_UNCERT -327680;
.CONST $M.SSR.SCORE_BIAS 196608;
.CONST $M.SSR.UNCERT_POS 3;
.CONST $M.SSR.CANDIDATE_STRENGTH 2;

.CONST $M.SSR.NOISE_BASE (-24);
.CONST $M.SSR.UNCERT_OFFSET (-112);
.CONST $M.SSR.UTTERANCE_TIME_OUT 3000;





.CONST $M.SSR.VOICE_DISAPPEARED 4;
.CONST $M.SSR.MIN_VALID_WORD 18;




.CONST $M.SSR.LPDNZ_PAD 8192;
.CONST $M.SSR.L2_LPDNZ_TRANS 1;
.CONST $M.SSR.LPDNZ_MARGIN 3*(1<<12);

.CONST $M.SSR.MAX_AGGRESS 0x7FFFFF;




.CONST $M.SSR.A_CONFI_THR_Yes -6963;
.CONST $M.SSR.A_CONFI_THR_No -6144;




.CONST $M.SSR.SSR_STRUC.CBUFFER_IN_OFFSET 0;
.CONST $M.SSR.SSR_STRUC.NOISE_BASE_OFFSET $M.SSR.SSR_STRUC.CBUFFER_IN_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.UNCERT_OFFSET $M.SSR.SSR_STRUC.NOISE_BASE_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.TIME_OUT_OFFSET $M.SSR.SSR_STRUC.UNCERT_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.RECOGNISED_WORD_OFFSET $M.SSR.SSR_STRUC.TIME_OUT_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.UNCERT_FLAG_OFFSET $M.SSR.SSR_STRUC.RECOGNISED_WORD_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.FINISH_OFFSET $M.SSR.SSR_STRUC.UNCERT_FLAG_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.CONFIDENCE_SCORE_OFFSET $M.SSR.SSR_STRUC.FINISH_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.ASRDEC_PTR_OFFSET $M.SSR.SSR_STRUC.CONFIDENCE_SCORE_OFFSET + 1;

.CONST $M.SSR.SSR_STRUC.FFT_REAL_OFFSET $M.SSR.SSR_STRUC.ASRDEC_PTR_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.FFT_IMAG_OFFSET $M.SSR.SSR_STRUC.FFT_REAL_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.SCALE_FACTOR_OFFSET $M.SSR.SSR_STRUC.FFT_IMAG_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.VOICED_OFFSET $M.SSR.SSR_STRUC.SCALE_FACTOR_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.GAIN_OFFSET $M.SSR.SSR_STRUC.VOICED_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.LIKE_MEAN_OFFSET $M.SSR.SSR_STRUC.GAIN_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.LPX_NZ_OFFSET $M.SSR.SSR_STRUC.LIKE_MEAN_OFFSET + 1;
.CONST $M.SSR.SSR_STRUC.BLOCK_SIZE $M.SSR.SSR_STRUC.LPX_NZ_OFFSET + 1;




.CONST $M.SSR.HMMDEF.NAME_OFFSET 0;
.CONST $M.SSR.HMMDEF.NSTATES_OFFSET $M.SSR.HMMDEF.NAME_OFFSET + 1;
.CONST $M.SSR.HMMDEF.GMMS_OFFSET $M.SSR.HMMDEF.NSTATES_OFFSET + 1;
.CONST $M.SSR.HMMDEF.EMISSION_TYPE_OFFSET $M.SSR.HMMDEF.GMMS_OFFSET + 1;
.CONST $M.SSR.HMMDEF.START_PROB_OFFSET $M.SSR.HMMDEF.EMISSION_TYPE_OFFSET + 1;
.CONST $M.SSR.HMMDEF.END_PROB_OFFSET $M.SSR.HMMDEF.START_PROB_OFFSET + 1;
.CONST $M.SSR.HMMDEF.TRANSMAT_OFFSET $M.SSR.HMMDEF.END_PROB_OFFSET + 1;
.CONST $M.SSR.HMMDEF.TIDX_OFFSET $M.SSR.HMMDEF.TRANSMAT_OFFSET + 1;
.CONST $M.SSR.HMMDEF.PARTIAL_LIKE_OFFSET $M.SSR.HMMDEF.TIDX_OFFSET + 1;
.CONST $M.SSR.HMMDEF.MAX_LIKE_OFFSET $M.SSR.HMMDEF.PARTIAL_LIKE_OFFSET + 1;
.CONST $M.SSR.HMMDEF.MAX_STATE_OFFSET $M.SSR.HMMDEF.MAX_LIKE_OFFSET + 1;
.CONST $M.SSR.HMMDEF.BLOCK_SIZE $M.SSR.HMMDEF.MAX_STATE_OFFSET + 1;




.CONST $M.SSR.DECODER_STRUCT.HMM_SET_OFFSET 0;
.CONST $M.SSR.DECODER_STRUCT.FINISH_OFFSET $M.SSR.DECODER_STRUCT.HMM_SET_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.RESET_OFFSET $M.SSR.DECODER_STRUCT.FINISH_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.BEST_WORD_OFFSET $M.SSR.DECODER_STRUCT.RESET_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.BEST_SCORE_OFFSET $M.SSR.DECODER_STRUCT.BEST_WORD_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.BEST_STATE_OFFSET $M.SSR.DECODER_STRUCT.BEST_SCORE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.OBS_OFFSET $M.SSR.DECODER_STRUCT.BEST_STATE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.OBS_REGRESS_OFFSET $M.SSR.DECODER_STRUCT.OBS_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.LOG_ENERGY_OFFSET $M.SSR.DECODER_STRUCT.OBS_REGRESS_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.CONFIDENCE_SCORE_OFFSET $M.SSR.DECODER_STRUCT.LOG_ENERGY_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.NR_BEST_FRAMES_OFFSET $M.SSR.DECODER_STRUCT.CONFIDENCE_SCORE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.SUCC_STA_CNT_OFFSET $M.SSR.DECODER_STRUCT.NR_BEST_FRAMES_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.NR_MAIN_STATE_OFFSET $M.SSR.DECODER_STRUCT.SUCC_STA_CNT_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.FINISH_CNT_OFFSET $M.SSR.DECODER_STRUCT.NR_MAIN_STATE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.RELIABILITY_OFFSET $M.SSR.DECODER_STRUCT.FINISH_CNT_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.DECODER_STARTED_OFFSET $M.SSR.DECODER_STRUCT.RELIABILITY_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.FRAME_COUNTER_OFFSET $M.SSR.DECODER_STRUCT.DECODER_STARTED_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.VOICE_GONE_CNT_OFFSET $M.SSR.DECODER_STRUCT.FRAME_COUNTER_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.AFTER_RESET_CNT_OFFSET $M.SSR.DECODER_STRUCT.VOICE_GONE_CNT_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.SCORE_OFFSET $M.SSR.DECODER_STRUCT.AFTER_RESET_CNT_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.SUM_RELI_OFFSET $M.SSR.DECODER_STRUCT.SCORE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.NOISE_ESTIMATE_OFFSET $M.SSR.DECODER_STRUCT.SUM_RELI_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.NOISE_FRAME_COUNTER_OFFSET $M.SSR.DECODER_STRUCT.NOISE_ESTIMATE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.INITIALIZED_OFFSET $M.SSR.DECODER_STRUCT.NOISE_FRAME_COUNTER_OFFSET + 1;

.CONST $M.SSR.DECODER_STRUCT.FBANK_COEFFS_OFFSET $M.SSR.DECODER_STRUCT.INITIALIZED_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.MFC_COEFFS_OFFSET $M.SSR.DECODER_STRUCT.FBANK_COEFFS_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.PARTIAL_LIKE_OFFSET $M.SSR.DECODER_STRUCT.MFC_COEFFS_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.PARTIAL_LIKE_NEXT_OFFSET $M.SSR.DECODER_STRUCT.PARTIAL_LIKE_OFFSET + 1;
.CONST $M.SSR.DECODER_STRUCT.BLOCK_SIZE $M.SSR.DECODER_STRUCT.PARTIAL_LIKE_NEXT_OFFSET + 1;


.CONST $M.SSR.MIXTURE_STRUCT.MIX_ID_OFFSET 0;
.CONST $M.SSR.MIXTURE_STRUCT.PRIORS_OFFSET $M.SSR.MIXTURE_STRUCT.MIX_ID_OFFSET + 1;
.CONST $M.SSR.MIXTURE_STRUCT.GCONST_OFFSET $M.SSR.MIXTURE_STRUCT.PRIORS_OFFSET + 1;
.CONST $M.SSR.MIXTURE_STRUCT.MEANS_OFFSET $M.SSR.MIXTURE_STRUCT.GCONST_OFFSET + 1;
.CONST $M.SSR.MIXTURE_STRUCT.COVARS_OFFSET $M.SSR.MIXTURE_STRUCT.MEANS_OFFSET + 1;
.CONST $M.SSR.MIXTURE_STRUCT.BLOCK_SIZE_OFFSET $M.SSR.MIXTURE_STRUCT.COVARS_OFFSET + 1;


.CONST $M.SSR.STATEDEF.NMIX_OFFSET 0;
.CONST $M.SSR.STATEDEF.MIX_OFFSET $M.SSR.STATEDEF.NMIX_OFFSET + 1;
.CONST $M.SSR.STATEDEF.BLOCK_SIZE_OFFSET $M.SSR.STATEDEF.MIX_OFFSET + 1;




.CONST $M.SSR.OMS_STRUC.OMS_OBJ_OFFSET 0;
.CONST $M.SSR.OMS_STRUC.FFT_REAL_OFFSET $M.SSR.OMS_STRUC.OMS_OBJ_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.FFT_IMAG_OFFSET $M.SSR.OMS_STRUC.FFT_REAL_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.SCALE_FACTOR_OFFSET $M.SSR.OMS_STRUC.FFT_IMAG_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.VOICED_OFFSET $M.SSR.OMS_STRUC.SCALE_FACTOR_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.GAIN_OFFSET $M.SSR.OMS_STRUC.VOICED_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.LIKE_MEAN_OFFSET $M.SSR.OMS_STRUC.GAIN_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.LPX_NZ_OFFSET $M.SSR.OMS_STRUC.LIKE_MEAN_OFFSET + 1;
.CONST $M.SSR.OMS_STRUC.BLOCK_SIZE_OFFSET $M.SSR.OMS_STRUC.LPX_NZ_OFFSET + 1;
.linefile 27 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/Beamformer100/2micHF500_library.h" 1







.CONST $M.BEAMFORMER.BIN_L 2;
.CONST $M.BEAMFORMER.BIN_H 63;
.CONST $M.BEAMFORMER.PROCESSING_BINS ($M.BEAMFORMER.BIN_H - $M.BEAMFORMER.BIN_L + 1);


.CONST $M.AED.BIN_L 5;
.CONST $M.AED.BIN_H 59;
.CONST $M.AED.IDX_PROC ($M.AED.BIN_H - $M.AED.BIN_L + 1);
.CONST $M.AED.IDX_PROC_INV 0x0253C8;


.CONST $M.TWOCHANNEL_NC.BIN_L 5;
.CONST $M.TWOCHANNEL_NC.BIN_H 59;
.CONST $M.TWOCHANNEL_NC.NC_num_proc ($M.TWOCHANNEL_NC.BIN_H - $M.TWOCHANNEL_NC.BIN_L + 1);
.CONST $M.TWOCHANNEL_NC.Num_Taps 2;

.CONST $M.BEAMFORMER.OFFSET_X0_REAL_PTR 0;
.CONST $M.BEAMFORMER.OFFSET_X0_IMAG_PTR $M.BEAMFORMER.OFFSET_X0_REAL_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_BEXP_X0_PTR $M.BEAMFORMER.OFFSET_X0_IMAG_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_X1_REAL_PTR $M.BEAMFORMER.OFFSET_BEXP_X0_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_X1_IMAG_PTR $M.BEAMFORMER.OFFSET_X1_REAL_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_BEXP_X1_PTR $M.BEAMFORMER.OFFSET_X1_IMAG_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_Z_REAL_PTR $M.BEAMFORMER.OFFSET_BEXP_X1_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_Z_IMAG_PTR $M.BEAMFORMER.OFFSET_Z_REAL_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_MU_PTR $M.BEAMFORMER.OFFSET_Z_IMAG_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_BEAM_MODE $M.BEAMFORMER.OFFSET_MU_PTR + 1;
.CONST $M.BEAMFORMER.OFFSET_ELEMENT_D $M.BEAMFORMER.OFFSET_BEAM_MODE + 1;
.CONST $M.BEAMFORMER.OFFSET_DOA $M.BEAMFORMER.OFFSET_ELEMENT_D + 1;
.CONST $M.BEAMFORMER.OFFSET_PTR_DM1data $M.BEAMFORMER.OFFSET_DOA + 1;
.CONST $M.BEAMFORMER.OFFSET_SCRATCH_DM1 $M.BEAMFORMER.OFFSET_PTR_DM1data + 1;
.CONST $M.BEAMFORMER.OFFSET_SCRATCH_DM2 $M.BEAMFORMER.OFFSET_SCRATCH_DM1 + 1;
.CONST $M.BEAMFORMER.STRUC_SIZE $M.BEAMFORMER.OFFSET_SCRATCH_DM2 + 1;


.CONST $M.TWOMIC_HF_500.OFFSET_CONFIG 0;
.CONST $M.TWOMIC_HF_500.OFFSET_MIC_MODE $M.TWOMIC_HF_500.OFFSET_CONFIG + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_MGDC_CTRL $M.TWOMIC_HF_500.OFFSET_MIC_MODE + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_BF0_PTR $M.TWOMIC_HF_500.OFFSET_MGDC_CTRL + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_BF1_PTR $M.TWOMIC_HF_500.OFFSET_BF0_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_2MICAEC_PTR $M.TWOMIC_HF_500.OFFSET_BF1_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_AED_PTR $M.TWOMIC_HF_500.OFFSET_2MICAEC_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_2CHNC_PTR $M.TWOMIC_HF_500.OFFSET_AED_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_OMS_IN_PTR $M.TWOMIC_HF_500.OFFSET_2CHNC_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_OMS_OUT0_PTR $M.TWOMIC_HF_500.OFFSET_OMS_IN_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_OMS_OUT1_PTR $M.TWOMIC_HF_500.OFFSET_OMS_OUT0_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_NUM_BINS $M.TWOMIC_HF_500.OFFSET_OMS_OUT1_PTR + 1;

.CONST $M.TWOMIC_HF_500.OFFSET_X0_REAL_PTR $M.TWOMIC_HF_500.OFFSET_NUM_BINS + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_X0_IMAG_PTR $M.TWOMIC_HF_500.OFFSET_X0_REAL_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_BEXP_X0_PTR $M.TWOMIC_HF_500.OFFSET_X0_IMAG_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_X1_REAL_PTR $M.TWOMIC_HF_500.OFFSET_BEXP_X0_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_X1_IMAG_PTR $M.TWOMIC_HF_500.OFFSET_X1_REAL_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_BEXP_X1_PTR $M.TWOMIC_HF_500.OFFSET_X1_IMAG_PTR+ 1;

.CONST $M.TWOMIC_HF_500.OFFSET_Z0_REAL_PTR $M.TWOMIC_HF_500.OFFSET_BEXP_X1_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_Z0_IMAG_PTR $M.TWOMIC_HF_500.OFFSET_Z0_REAL_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_Z1_REAL_PTR $M.TWOMIC_HF_500.OFFSET_Z0_IMAG_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_Z1_IMAG_PTR $M.TWOMIC_HF_500.OFFSET_Z1_REAL_PTR + 1;

.CONST $M.TWOMIC_HF_500.OFFSET_TMP_LalfaLPz_PTR $M.TWOMIC_HF_500.OFFSET_Z1_IMAG_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_TMP_LPin0_PTR $M.TWOMIC_HF_500.OFFSET_TMP_LalfaLPz_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_TMP_LPin1_PTR $M.TWOMIC_HF_500.OFFSET_TMP_LPin0_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_TMP_LPout0_PTR $M.TWOMIC_HF_500.OFFSET_TMP_LPin1_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_TMP_LPout1_PTR $M.TWOMIC_HF_500.OFFSET_TMP_LPout0_PTR + 1;
.CONST $M.TWOMIC_HF_500.OFFSET_PTR_DM1data $M.TWOMIC_HF_500.OFFSET_TMP_LPout1_PTR + 1;
.CONST $M.TWOMIC_HF_500.STRUC_SIZE $M.TWOMIC_HF_500.OFFSET_PTR_DM1data + 1;




.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_E_REAL_PTR 0;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_E_IMAG_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_E_REAL_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_EXP_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_E_IMAG_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_REAL_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_D_EXP_PTR+1;

.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_D_IMAG_PTR $M.TWOMIC_AEC.OFFSET_FNLMS_D_REAL_PTR+1;


.CONST $M.TWOMIC_AEC.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt $M.TWOMIC_AEC.OFFSET_FNLMS_D_IMAG_PTR + 1;

.CONST $M.TWOMIC_AEC.OFFSET_PTR_MAIN_AEC $M.TWOMIC_AEC.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_BYPASS_AEC1 $M.TWOMIC_AEC.OFFSET_PTR_MAIN_AEC + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_Ga_real $M.TWOMIC_AEC.OFFSET_PTR_BYPASS_AEC1 + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_Ga_imag $M.TWOMIC_AEC.OFFSET_PTR_Ga_real + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_BExp_Ga $M.TWOMIC_AEC.OFFSET_PTR_Ga_imag + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_real $M.TWOMIC_AEC.OFFSET_PTR_BExp_Ga + 1;
.CONST $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_imag $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_real + 1;

.CONST $M.TWOMIC_AEC.STRUCT_SIZE $M.TWOMIC_AEC.OFFSET_PTR_RcvBuf_imag + 1;


.CONST $M.AED.OFFSET_G_OMS0 0;
.CONST $M.AED.OFFSET_VOICED_OMS0 $M.AED.OFFSET_G_OMS0 + 1;
.CONST $M.AED.OFFSET_G_OMS1 $M.AED.OFFSET_VOICED_OMS0 + 1;
.CONST $M.AED.OFFSET_VOICED_OMS1 $M.AED.OFFSET_G_OMS1 + 1;
.CONST $M.AED.OFFSET_VOICEFLAG $M.AED.OFFSET_VOICED_OMS1 + 1;
.CONST $M.AED.OFFSET_MODE $M.AED.OFFSET_VOICEFLAG + 1;
.CONST $M.AED.OFFSET_STATE_T $M.AED.OFFSET_MODE + 1;
.CONST $M.AED.OFFSET_VAD $M.AED.OFFSET_STATE_T + 1;
.CONST $M.AED.OFFSET_CHANNEL $M.AED.OFFSET_VAD + 1;
.CONST $M.AED.OFFSET_G_AED $M.AED.OFFSET_CHANNEL + 1;
.CONST $M.AED.OFFSET_Noise_Th $M.AED.OFFSET_G_AED + 1;
.CONST $M.AED.OFFSET_alphaA $M.AED.OFFSET_Noise_Th + 1;
.CONST $M.AED.OFFSET_alphaN $M.AED.OFFSET_alphaA + 1;
.CONST $M.AED.OFFSET_NR_defer_Count $M.AED.OFFSET_alphaN + 1;
.CONST $M.AED.OFFSET_NR_max_Count $M.AED.OFFSET_NR_defer_Count + 1;
.CONST $M.AED.OFFSET_NR_alpha $M.AED.OFFSET_NR_max_Count + 1;
.CONST $M.AED.OFFSET_S_ACTIVE_COUNT $M.AED.OFFSET_NR_alpha + 1;
.CONST $M.AED.OFFSET_S_ACTIVE_COUNT_DIV_6 $M.AED.OFFSET_S_ACTIVE_COUNT + 1;
.CONST $M.AED.OFFSET_PTR_DM1data $M.AED.OFFSET_S_ACTIVE_COUNT_DIV_6 + 1;
.CONST $M.AED.STRUC_SIZE $M.AED.OFFSET_PTR_DM1data + 1;


.CONST $M.TWOCHANNEL_NC.OFFSET_E_REAL_PTR 0;
.CONST $M.TWOCHANNEL_NC.OFFSET_E_IMAG_PTR $M.TWOCHANNEL_NC.OFFSET_E_REAL_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_BEXP_D_PTR $M.TWOCHANNEL_NC.OFFSET_E_IMAG_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_D_REAL_PTR $M.TWOCHANNEL_NC.OFFSET_BEXP_D_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_D_IMAG_PTR $M.TWOCHANNEL_NC.OFFSET_D_REAL_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_SCRPTR_Exp_Mts_adapt $M.TWOCHANNEL_NC.OFFSET_D_IMAG_PTR + 1;

.CONST $M.TWOCHANNEL_NC.OFFSET_X_REAL_PTR $M.TWOCHANNEL_NC.OFFSET_SCRPTR_Exp_Mts_adapt + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_X_IMAG_PTR $M.TWOCHANNEL_NC.OFFSET_X_REAL_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_BEXP_X_PTR $M.TWOCHANNEL_NC.OFFSET_X_IMAG_PTR + 1;


.CONST $M.TWOCHANNEL_NC.OFFSET_AED_DIFF_PTR $M.TWOCHANNEL_NC.OFFSET_BEXP_X_PTR+1;


.CONST $M.TWOCHANNEL_NC.OFFSET_PP_GAMMAP $M.TWOCHANNEL_NC.OFFSET_AED_DIFF_PTR + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_bypass_postp_rpt $M.TWOCHANNEL_NC.OFFSET_PP_GAMMAP + 1;
.CONST $M.TWOCHANNEL_NC.OFFSET_num_taps $M.TWOCHANNEL_NC.OFFSET_bypass_postp_rpt + 1;
.linefile 151 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/Beamformer100/2micHF500_library.h"
.CONST $M.TWOCHANNEL_NC.OFFSET_SCRATCH_DM1 $M.TWOCHANNEL_NC.OFFSET_num_taps+1;




.CONST $M.TWOCHANNEL_NC.OFFSET_SCRATCH_DM2 $M.TWOCHANNEL_NC.OFFSET_SCRATCH_DM1+1;




.CONST $M.TWOCHANNEL_NC.OFFSET_PTR_DM1data $M.TWOCHANNEL_NC.OFFSET_SCRATCH_DM2+1;


.CONST $M.TWOCHANNEL_NC.OFFSET_PTR_DM2data $M.TWOCHANNEL_NC.OFFSET_PTR_DM1data+1;


.CONST $M.TWOCHANNEL_NC.STRUC_SIZE $M.TWOCHANNEL_NC.OFFSET_PTR_DM2data + 1;

.CONST $M.TWOCHANNEL_NC.OFFSET_SCR2PTR_PP_LpXt $M.TWOCHANNEL_NC.OFFSET_SCRATCH_DM2;






.CONST $M.AED.OFFSET_DM1PTR_Diff $M.AED.OFFSET_PTR_DM1data;
.CONST $M.AED.DM1.Diff 0;
.CONST $M.AED.DM1.Difft $M.AED.DM1.Diff + $M.AED.IDX_PROC;
.CONST $M.AED.DM1.AED_control $M.AED.DM1.Difft + $M.AED.IDX_PROC;
.CONST $M.AED.DM1.state $M.AED.DM1.AED_control + $M.AED.IDX_PROC;
.CONST $M.AED.DM1.stateCount $M.AED.DM1.state + 1;
.CONST $M.AED.DM1.stateCountMax $M.AED.DM1.stateCount + 9;
.CONST $M.AED.DM1.noiseCount $M.AED.DM1.stateCountMax + 9;
.CONST $M.AED.DATA_SIZE_DM1 $M.AED.DM1.noiseCount + 1;



.CONST $M.TWOMIC_HF_500.OFFSET_DM1_phase_E0 $M.TWOMIC_HF_500.OFFSET_PTR_DM1data;
.CONST $M.TWOMIC_HF_500.DM1.Phase_E0 0;
.CONST $M.TWOMIC_HF_500.DM1.Phase_E1 $M.TWOMIC_HF_500.DM1.Phase_E0 + $M.BEAMFORMER.BIN_H;
.CONST $M.TWOMIC_HF_500.DATA_SIZE_DM1 $M.TWOMIC_HF_500.DM1.Phase_E1 + $M.BEAMFORMER.BIN_H;



.CONST $M.BEAMFORMER.OFFSET_DM1PTR_CC_real_imag $M.BEAMFORMER.OFFSET_PTR_DM1data;
.CONST $M.BEAMFORMER.DM1.CC_real_imag 0;
.CONST $M.BEAMFORMER.DM1.Phi_real_imag $M.BEAMFORMER.DM1.CC_real_imag + 2*$M.BEAMFORMER.PROCESSING_BINS;
.CONST $M.BEAMFORMER.DM1.TR $M.BEAMFORMER.DM1.Phi_real_imag + 2*$M.BEAMFORMER.PROCESSING_BINS;
.CONST $M.BEAMFORMER.DATA_SIZE_DM1 $M.BEAMFORMER.DM1.TR + $M.BEAMFORMER.PROCESSING_BINS;



.CONST $M.TWOCHANNEL_NC.OFFSET_DM1PTR_RcvBuf_real $M.TWOCHANNEL_NC.OFFSET_PTR_DM1data;
.CONST $M.TWOCHANNEL_NC.DM1.RcvBuf_real 0;
.CONST $M.TWOCHANNEL_NC.DM1.Gp_imag $M.TWOCHANNEL_NC.DM1.RcvBuf_real + $M.TWOCHANNEL_NC.NC_num_proc*$M.TWOCHANNEL_NC.Num_Taps;
.CONST $M.TWOCHANNEL_NC.DM1.LPwrXp $M.TWOCHANNEL_NC.DM1.Gp_imag + $M.TWOCHANNEL_NC.NC_num_proc*$M.TWOCHANNEL_NC.Num_Taps;
.CONST $M.TWOCHANNEL_NC.DM1.BExp_Gp $M.TWOCHANNEL_NC.DM1.LPwrXp + $M.TWOCHANNEL_NC.NC_num_proc;
.CONST $M.TWOCHANNEL_NC.DATA_SIZE_DM1 $M.TWOCHANNEL_NC.DM1.BExp_Gp + $M.TWOCHANNEL_NC.NC_num_proc;


.CONST $M.TWOCHANNEL_NC.OFFSET_DM2PTR_cRcvBuf_imag $M.TWOCHANNEL_NC.OFFSET_PTR_DM2data;
.CONST $M.TWOCHANNEL_NC.DM2.RcvBuf_imag 0;
.CONST $M.TWOCHANNEL_NC.DM2.Gp_real $M.TWOCHANNEL_NC.DM2.RcvBuf_imag + $M.TWOCHANNEL_NC.NC_num_proc*$M.TWOCHANNEL_NC.Num_Taps;
.CONST $M.TWOCHANNEL_NC.DM2.BExp_X_buf $M.TWOCHANNEL_NC.DM2.Gp_real + $M.TWOCHANNEL_NC.NC_num_proc*$M.TWOCHANNEL_NC.Num_Taps;
.CONST $M.TWOCHANNEL_NC.DATA_SIZE_DM2 $M.TWOCHANNEL_NC.DM2.BExp_X_buf + $M.TWOCHANNEL_NC.Num_Taps + 1;
.linefile 28 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf200/adf200_library.h" 1
.linefile 21 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf200/adf200_library.h"
.CONST $adf200_VERSION 0x020000;


.CONST $adf200.BIN_SKIPPED 9;
.CONST $adf200.ADF_num_proc 55;

.CONST $adf200.DATA_SIZE_DM1 (19 * $adf200.ADF_num_proc);
.CONST $adf200.DATA_SIZE_DM2 (13 * $adf200.ADF_num_proc);

.CONST $adf200.SCRATCH_SIZE_DM1 (5 * $adf200.ADF_num_proc);
.CONST $adf200.SCRATCH_SIZE_DM2 (1 * $adf200.ADF_num_proc);
.linefile 51 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf200/adf200_library.h"
.CONST $adf200.X0_FIELD 0;



.CONST $adf200.X1_FIELD 1;




.CONST $adf200.OFFSET_PTR_DM1data 2;



.CONST $adf200.OFFSET_PTR_DM2data 3;
.linefile 74 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf200/adf200_library.h"
.CONST $adf200.OFFSET_SCRATCH_DM1 4;




.CONST $adf200.OFFSET_SCRATCH_DM2 5;



.CONST $adf200.PTR_INTRATIO0_FIELD 6;



.CONST $adf200.PTR_INTRATIO1_FIELD 7;




.CONST $adf200.OFFSET_L_POSTP_CTRL_PTR 8;




.CONST $adf200.FUNC_APP_PREP_FIELD 9;



.CONST $adf200.FUNC_APP_PP_FIELD 10;

.CONST $adf200.OFFSET_INTERNAL_START 11;
.linefile 113 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/adf200/adf200_library.h"
.CONST $adf200.OFFSET_X0_REAL_PTR $adf200.OFFSET_INTERNAL_START+1;;
.CONST $adf200.OFFSET_X0_IMAG_PTR $adf200.OFFSET_X0_REAL_PTR+1;
.CONST $adf200.OFFSET_X0_EXP_PTR $adf200.OFFSET_X0_IMAG_PTR+1;
.CONST $adf200.OFFSET_X1_REAL_PTR $adf200.OFFSET_X0_EXP_PTR+1;
.CONST $adf200.OFFSET_X1_IMAG_PTR $adf200.OFFSET_X1_REAL_PTR+1;
.CONST $adf200.OFFSET_X1_EXP_PTR $adf200.OFFSET_X1_IMAG_PTR+1;
.CONST $adf200.OFFSET_Z0_REAL_PTR $adf200.OFFSET_X1_EXP_PTR+1;
.CONST $adf200.OFFSET_Z0_IMAG_PTR $adf200.OFFSET_Z0_REAL_PTR+1;
.CONST $adf200.OFFSET_Z1_REAL_PTR $adf200.OFFSET_Z0_IMAG_PTR+1;
.CONST $adf200.OFFSET_Z1_IMAG_PTR $adf200.OFFSET_Z1_REAL_PTR+1;


.CONST $adf200.OFFSET_muAt $adf200.OFFSET_Z1_IMAG_PTR+1;


.CONST $adf200.OFFSET_ct_Px0 $adf200.OFFSET_muAt+1;
.CONST $adf200.OFFSET_dL2Px0FB $adf200.OFFSET_ct_Px0+1;
.CONST $adf200.OFFSET_L2Px0t0 $adf200.OFFSET_dL2Px0FB+1;

.CONST $adf200.OFFSET_ct_Px1 $adf200.OFFSET_L2Px0t0+1;
.CONST $adf200.OFFSET_dL2Px1FB $adf200.OFFSET_ct_Px1+1;
.CONST $adf200.OFFSET_L2Px1t0 $adf200.OFFSET_dL2Px1FB+1;

.CONST $adf200.OFFSET_ct_init $adf200.OFFSET_L2Px1t0+1;

.CONST $adf200.OFFSET_ADF_LALFALPZ $adf200.OFFSET_ct_init+1;


.CONST $adf200.STRUCT_SIZE $adf200.OFFSET_ADF_LALFALPZ+1;




.CONST $MAX_24 0x7fffff;
.CONST $MIN_24 0x800000;
.CONST $MIN_48_MSB 0x800000;
.CONST $MIN_48_LSB 0;
.CONST $MAX_48_MSB 0x7fffff;
.CONST $MAX_48_LSB 0xffffff;
.linefile 29 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/mgdc100/mgdc100_library.h" 1
.linefile 18 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/mgdc100/mgdc100_library.h"
.CONST $mgdc100.X0_FIELD 0;



.CONST $mgdc100.X1_FIELD 1;



.CONST $mgdc100.PARAM_FIELD 2;



.CONST $mgdc100.PTR_NUMFREQ_BINS_FIELD 3;



.CONST $mgdc100.PTR_G_OMS_FIELD 4;



.CONST $mgdc100.FRONTMICBIAS_FIELD 5;




.CONST $mgdc100.PTR_MICMODE_FIELD 6;



.CONST $mgdc100.PTR_OMS_VAD_FIELD 7;



.CONST $mgdc100.L2FBPXD_FIELD 8;


.CONST $mgdc100.MAXCOMP_FIELD 9;
.CONST $mgdc100.TH0_FIELD 10;
.CONST $mgdc100.TH1_FIELD 11;
.CONST $mgdc100.L2FBPX0T_FIELD 12;
.CONST $mgdc100.L2FBPX1T_FIELD 13;
.CONST $mgdc100.L2FBPXDST_FIELD 14;
.CONST $mgdc100.EXP_GAIN_FIELD 15;
.CONST $mgdc100.MTS_GAIN_FIELD 16;
.CONST $mgdc100.MEAN_OMS_G_FIELD 17;
.CONST $mgdc100.HOLD_ADAPT_FIELD 18;
.CONST $mgdc100.SWITCH_OUTPUT_FIELD 19;
.CONST $mgdc100.MGDC_UPDATE_FIELD 20;

.CONST $mgdc100.STRUC_SIZE 21;
.linefile 78 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/mgdc100/mgdc100_library.h"
.CONST $mgdc100.param.MAXCOMP_FIELD 0;



.CONST $mgdc100.param.TH_FIELD 1;
.linefile 30 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/nc100/nc100_library.h" 1
.linefile 15 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/nc100/nc100_library.h"
.CONST $NC_VERSION 0x010000;





.CONST $nc100.BIN_SKIPPED 9;
.CONST $nc100.NUM_PROC 55;
.CONST $nc100.NUM_TAPS 2;
.CONST $nc100.DM1_DATA_SIZE ((2 + 2*$nc100.NUM_TAPS) * $nc100.NUM_PROC);
.CONST $nc100.DM2_DATA_SIZE ((0 + 2*$nc100.NUM_TAPS) * $nc100.NUM_PROC + $nc100.NUM_TAPS+1);
.CONST $nc100.DM1_SCRATCH_SIZE ((1 + 3*$nc100.NUM_PROC));
.linefile 35 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/nc100/nc100_library.h"
.CONST $nc100.X0_FIELD 0;



.CONST $nc100.X1_FIELD 1;



.CONST $nc100.DM1_DATA_FIELD 2;



.CONST $nc100.DM2_DATA_FIELD 3;



.CONST $nc100.DM1_SCRATCH_FIELD 4;




.CONST $nc100.NC_CTRL_FIELD 5;




.CONST $nc100.FUNC_APP_PREP_FIELD 6;



.CONST $nc100.FUNC_APP_PP_FIELD 7;



.CONST $nc100.RPTP_FLAG_FIELD 8;



.CONST $nc100.G_OMS_FIELD 9;




.CONST $nc100.FNLMS_FIELD 10;
.CONST $nc100.OFFSET_FNLMS_E_REAL_PTR 0 + $nc100.FNLMS_FIELD;
.CONST $nc100.OFFSET_FNLMS_E_IMAG_PTR 1 + $nc100.FNLMS_FIELD;
.CONST $nc100.OFFSET_FNLMS_D_EXP_PTR 2 + $nc100.FNLMS_FIELD;
.CONST $nc100.OFFSET_FNLMS_D_REAL_PTR 3 + $nc100.FNLMS_FIELD;
.CONST $nc100.OFFSET_FNLMS_D_IMAG_PTR 4 + $nc100.FNLMS_FIELD;

.CONST $nc100.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt 5 + $nc100.FNLMS_FIELD;
.CONST $nc100.FNLMS_END_FIELD $nc100.OFFSET_FNLMS_SCRPTR_Exp_Mts_adapt;


.CONST $nc100.STRUCT_SIZE 1 + $nc100.FNLMS_END_FIELD;
.linefile 31 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/asf100/asf100_library.h" 1
.linefile 14 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/asf100/asf100_library.h"
.CONST $asf100.BIN_SKIPPED 1;
.CONST $asf100.NUM_PROC 63;
.CONST $asf100.SCRATCH_SIZE_DM1 (6+5) * $asf100.NUM_PROC;
.CONST $asf100.SCRATCH_SIZE_DM2 (6+5) * $asf100.NUM_PROC;
.linefile 28 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/asf100/asf100_library.h"
.CONST $asf100.Z0_FIELD 0;



.CONST $asf100.Z1_FIELD 1;



.CONST $asf100.MODE_FIELD 2;



.CONST $asf100.PARAM_FIELD 3;



.CONST $asf100.POWER_ADJUST_FIELD 4;



.CONST $asf100.SCRATCH_DM1_FIELD 5;



.CONST $asf100.SCRATCH_DM2_FIELD 6;




.CONST $asf100.FUNC_APP_PREP_FIELD 7;




.CONST $asf100.FUNC_APP_PP_FIELD 8;



.CONST $asf100.BEAM_FUNC_FIELD 9;




.CONST $asf100.BEAM_MODE_FIELD 10;


.CONST $asf100.INTERNAL_START_FIELD 11;






.CONST $asf100.PX0N_FIELD 0 + $asf100.INTERNAL_START_FIELD;
.CONST $asf100.PX1N_FIELD 1 + $asf100.PX0N_FIELD;
.CONST $asf100.PXCRN_FIELD 1 + $asf100.PX1N_FIELD;
.CONST $asf100.PXCIN_FIELD 1 + $asf100.PXCRN_FIELD;
.CONST $asf100.COH_FIELD 1 + $asf100.PXCIN_FIELD;
.CONST $asf100.WNR_G_FIELD 1 + $asf100.COH_FIELD;
.CONST $asf100.BEAM_CC0_REAL_FIELD 1 + $asf100.WNR_G_FIELD;
.CONST $asf100.BEAM_CC0_IMAG_FIELD 1 + $asf100.BEAM_CC0_REAL_FIELD;
.CONST $asf100.BEAM_PHI0_REAL_FIELD 1 + $asf100.BEAM_CC0_IMAG_FIELD;
.CONST $asf100.BEAM_PHI0_IMAG_FIELD 1 + $asf100.BEAM_PHI0_REAL_FIELD;
.CONST $asf100.BEAM_FD_W0_REAL_FIELD 1 + $asf100.BEAM_PHI0_IMAG_FIELD;
.CONST $asf100.BEAM_FD_W0_IMAG_FIELD 1 + $asf100.BEAM_FD_W0_REAL_FIELD;
.CONST $asf100.BEAM_FD_W1_REAL_FIELD 1 + $asf100.BEAM_FD_W0_IMAG_FIELD;
.CONST $asf100.BEAM_FD_W1_IMAG_FIELD 1 + $asf100.BEAM_FD_W1_REAL_FIELD;
.CONST $asf100.BEAM_FW_W1_REAL_FIELD 1 + $asf100.BEAM_FD_W1_IMAG_FIELD;
.CONST $asf100.BEAM_FW_W1_IMAG_FIELD 1 + $asf100.BEAM_FW_W1_REAL_FIELD;
.CONST $asf100.BEAM_COMP_T_REAL_FIELD 1 + $asf100.BEAM_FW_W1_IMAG_FIELD;
.CONST $asf100.BEAM_COMP_T_IMAG_FIELD 1 + $asf100.BEAM_COMP_T_REAL_FIELD;
.CONST $asf100.BEAM_TR0_FIELD 1 + $asf100.BEAM_COMP_T_IMAG_FIELD;
.CONST $asf100.BEAM_TR1_FIELD 1 + $asf100.BEAM_TR0_FIELD;
.CONST $asf100.COH_COS_FIELD 1 + $asf100.BEAM_TR1_FIELD;
.CONST $asf100.COH_SIN_FIELD 1 + $asf100.COH_COS_FIELD;
.CONST $asf100.COH_G_FIELD 1 + $asf100.COH_SIN_FIELD;

.CONST $asf100.X0_REAL_FIELD 1 + $asf100.COH_G_FIELD;
.CONST $asf100.X0_IMAG_FIELD 1 + $asf100.X0_REAL_FIELD;
.CONST $asf100.X0_BEXP_FIELD 1 + $asf100.X0_IMAG_FIELD;
.CONST $asf100.X1_REAL_FIELD 1 + $asf100.X0_BEXP_FIELD;
.CONST $asf100.X1_IMAG_FIELD 1 + $asf100.X1_REAL_FIELD;
.CONST $asf100.X1_BEXP_FIELD 1 + $asf100.X1_IMAG_FIELD;
.CONST $asf100.X0_SAVED_REAL_FIELD 1 + $asf100.X1_BEXP_FIELD;
.CONST $asf100.X0_SAVED_IMAG_FIELD 1 + $asf100.X0_SAVED_REAL_FIELD;
.CONST $asf100.X0_SAVED_BEXP_FIELD 1 + $asf100.X0_SAVED_IMAG_FIELD;


.CONST $asf100.COH_IMAG_FIELD 1 + $asf100.X0_SAVED_BEXP_FIELD;



.CONST $asf100.SCRATCH_PXCRNT_FIELD 1 + $asf100.COH_IMAG_FIELD;
.CONST $asf100.SCRATCH_PXCINT_FIELD 1 + $asf100.SCRATCH_PXCRNT_FIELD;
.CONST $asf100.SCRATCH_PX0NT_FIELD 1 + $asf100.SCRATCH_PXCINT_FIELD;
.CONST $asf100.SCRATCH_PX1NT_FIELD 1 + $asf100.SCRATCH_PX0NT_FIELD;

.CONST $asf100.SCRATCH_LPX0T_FIELD 1 + $asf100.SCRATCH_PX1NT_FIELD;
.CONST $asf100.SCRATCH_LPX1T_FIELD 1 + $asf100.SCRATCH_LPX0T_FIELD;


.CONST $asf100.BYPASS_FLAG_WNR_FIELD 1 + $asf100.SCRATCH_LPX1T_FIELD;
.CONST $asf100.BYPASS_FLAG_COH_FIELD 1 + $asf100.BYPASS_FLAG_WNR_FIELD;
.CONST $asf100.BYPASS_FLAG_BF_FIELD 1 + $asf100.BYPASS_FLAG_COH_FIELD;




.CONST $asf100.wnr.G1_FIELD 1 + $asf100.BYPASS_FLAG_BF_FIELD;
.CONST $asf100.wnr.PHS_FACTOR_EXP_FIELD 1 + $asf100.wnr.G1_FIELD;
.CONST $asf100.wnr.PHS_FACTOR_LB_FIELD 1 + $asf100.wnr.PHS_FACTOR_EXP_FIELD;
.CONST $asf100.wnr.PHS_FACTOR_TR_FIELD 1 + $asf100.wnr.PHS_FACTOR_LB_FIELD;
.CONST $asf100.wnr.PHS_FACTOR_HB_FIELD 1 + $asf100.wnr.PHS_FACTOR_TR_FIELD;
.CONST $asf100.wnr.MEAN_PWR_FIELD 1 + $asf100.wnr.PHS_FACTOR_HB_FIELD;
.CONST $asf100.wnr.MEAN_G_FIELD 1 + $asf100.wnr.MEAN_PWR_FIELD;
.CONST $asf100.wnr.MEAN_CC0_FIELD 1 + $asf100.wnr.MEAN_G_FIELD;
.CONST $asf100.wnr.COH_ATK_FIELD 1 + $asf100.wnr.MEAN_CC0_FIELD;
.CONST $asf100.wnr.COH_DEC_FIELD 1 + $asf100.wnr.COH_ATK_FIELD;
.CONST $asf100.wnr.DETECT_FLAG_FIELD 1 + $asf100.wnr.COH_DEC_FIELD;
.CONST $asf100.wnr.COHERENCE_FIELD 1 + $asf100.wnr.DETECT_FLAG_FIELD;
.CONST $asf100.wnr.WIND_FIELD 1 + $asf100.wnr.COHERENCE_FIELD;
.CONST $asf100.WNROBJ_END_FIELD 0 + $asf100.wnr.WIND_FIELD;
.linefile 160 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/asf100/asf100_library.h"
.CONST $asf100.bf.SCRATCH_W0_REAL_FIELD 1 + $asf100.WNROBJ_END_FIELD;
.CONST $asf100.bf.SCRATCH_W0_IMAG_FIELD 1 + $asf100.bf.SCRATCH_W0_REAL_FIELD;
.CONST $asf100.bf.SCRATCH_W1_REAL_FIELD 1 + $asf100.bf.SCRATCH_W0_IMAG_FIELD;
.CONST $asf100.bf.SCRATCH_W1_IMAG_FIELD 1 + $asf100.bf.SCRATCH_W1_REAL_FIELD;
.CONST $asf100.bf.SCRATCH_Z0_FDSB_REAL_FIELD 1 + $asf100.bf.SCRATCH_W1_IMAG_FIELD;
.CONST $asf100.bf.SCRATCH_Z0_FDSB_IMAG_FIELD 1 + $asf100.bf.SCRATCH_Z0_FDSB_REAL_FIELD;
.CONST $asf100.bf.SCRATCH_BEXP_Z0_FDSB_FIELD 1 + $asf100.bf.SCRATCH_Z0_FDSB_IMAG_FIELD;

.CONST $asf100.bf.SCRATCH_PS0T_FIELD 1 + $asf100.bf.SCRATCH_BEXP_Z0_FDSB_FIELD;
.CONST $asf100.bf.SCRATCH_NPX0_FIELD 1 + $asf100.bf.SCRATCH_PS0T_FIELD;
.CONST $asf100.bf.SCRATCH_PS1T_FIELD 1 + $asf100.bf.SCRATCH_NPX0_FIELD;
.CONST $asf100.bf.SCRATCH_NEG_D_FIELD 1 + $asf100.bf.SCRATCH_PS1T_FIELD;
.CONST $asf100.bf.BEAM_FW_W0_REAL_FIELD 1 + $asf100.bf.SCRATCH_NEG_D_FIELD;
.CONST $asf100.bf.BEAM_TEMP_FIELD 1 + $asf100.bf.BEAM_FW_W0_REAL_FIELD;
.CONST $asf100.BF_END_FIELD 0 + $asf100.bf.BEAM_TEMP_FIELD;


.CONST $asf100.STRUC_SIZE 1 + $asf100.BF_END_FIELD;
.linefile 190 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/asf100/asf100_library.h"
.CONST $asf100.param.MIC_DIST_FIELD 0;




.CONST $asf100.wnr.param.GAIN_AGGR_FIELD 1;




.CONST $asf100.wnr.param.THRESH_SILENCE_FIELD 2;



.CONST $asf100.bf.param.BETA0_FIELD 3;



.CONST $asf100.bf.param.BETA1_FIELD 4;



.CONST $asf100.wnr.param.THRESH_PHASE_FIELD 5;



.CONST $asf100.wnr.param.THRESH_COHERENCE_FIELD 6;
.linefile 32 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/dmss/dmss_library.h" 1
.linefile 18 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/dmss/dmss_library.h"
.CONST $dmss.X0_FIELD 0;



.CONST $dmss.X1_FIELD 1;



.CONST $dmss.PTR_NUMBIN_FIELD 2;

.CONST $dmss.INTERNAL_START_FIELD 3;


.CONST $dmss.LPIN0_FIELD 0 + $dmss.INTERNAL_START_FIELD;
.CONST $dmss.LPIN1_FIELD 1 + $dmss.LPIN0_FIELD;
.CONST $dmss.LPOUT0_FIELD 1 + $dmss.LPIN1_FIELD;
.CONST $dmss.LPOUT1_FIELD 1 + $dmss.LPOUT0_FIELD;
.CONST $dmss.DIFF_LP_FIELD 1 + $dmss.LPOUT1_FIELD;

.CONST $dmss.STRUC_SIZE 1 + $dmss.DIFF_LP_FIELD;;







.CONST $dmss100.BIN_SKIPPED 1;
.CONST $dmss100.NUM_PROC 63;
.CONST $dmss.LP_INIT (-48<<16);
.CONST $dmss.LALFALPZ -5.64371240507421220/(1<<7);
.linefile 33 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h" 1
.linefile 22 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.Num_Primary_Taps 2;
.CONST $aec510.Num_Auxillary_Taps 0;

.CONST $aec510_HF.Num_Auxillary_Taps 3;
.CONST $aec510_HF.Num_Primary_Taps 8;

.CONST $aec510.RER_dim 64;

.CONST $aec510.fbc.nb.FILTER_SIZE 20;
.CONST $aec510.fbc.wb.FILTER_SIZE 40;
.CONST $aec510.fbc.PERD 1;
.linefile 42 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.Parameter.OFFSET_CNG_Q_ADJUST 0;


.CONST $aec510.Parameter.OFFSET_CNG_NOISE_COLOR 1;


.CONST $aec510.Parameter.OFFSET_DTC_AGRESSIVENESS 2;


.CONST $aec510.Parameter.OFFSET_MAX_LPWR_MARGIN 3;




.CONST $aec510.Parameter.OFFSET_ENABLE_AEC_REUSE 4;



.CONST $aec510.Parameter.OFFSET_AEC_REF_LPWR_HB 5;


.CONST $aec510.Parameter.OFFSET_RER_VAR_THRESH 6;


.CONST $aec510.Parameter.OFFSET_RER_AGGRESSIVENESS 7;


.CONST $aec510.Parameter.OFFSET_RER_WGT_SY 8;


.CONST $aec510.Parameter.OFFSET_RER_OFFSET_SY 9;


.CONST $aec510.Parameter.OFFSET_RER_POWER 10;


.CONST $aec510.Parameter.OFFSET_L2TH_RERDT_OFF 11;


.CONST $aec510.Parameter.OFFSET_RERDT_ADJUST 12;


.CONST $aec510.Parameter.OFFSET_RERDT_POWER 13;


.CONST $aec510.Parameter.OFFSET_FBC_TH_RER 14;
.linefile 103 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.MODE_FIELD 0;



.CONST $aec510.PARAM_FIELD 1;




.CONST $aec510.RER_AGGR_FIELD 2;



.CONST $aec510.OMS_G_FIELD 3;



.CONST $aec510.X_FIELD 4;



.CONST $aec510.XBUF_REAL_FIELD 5;



.CONST $aec510.XBUF_IMAG_FIELD 6;



.CONST $aec510.XBUF_BEXP_FIELD 7;



.CONST $aec510.PTR_FBC_OBJ_FIELD 8;



.CONST $aec510.D_FIELD 9;



.CONST $aec510.GA_REAL_FIELD 10;



.CONST $aec510.GA_IMAG_FIELD 11;



.CONST $aec510.GA_BEXP_FIELD 12;



.CONST $aec510.DM_OBJ_FIELD 13;



.CONST $aec510.LPWRX0_FIELD 14;



.CONST $aec510.LPWRX1_FIELD 15;



.CONST $aec510.RATFE_FIELD 16;



.CONST $aec510.RER_GR_IMAG_FIELD 17;



.CONST $aec510.RER_GR_REAL_FIELD 18;



.CONST $aec510.RER_SQGR_FIELD 19;



.CONST $aec510.RER_L2ABSGR_FIELD 20;



.CONST $aec510.RER_LPWRD_FIELD 21;



.CONST $aec510.CNG_OMS_G_FIELD 22;



.CONST $aec510.CNG_OMS_LPDNZ_FIELD 23;



.CONST $aec510.CNG_LPZNZ_FIELD 24;



.CONST $aec510.CNG_CUR_NZ_TABLE_FIELD 25;



.CONST $aec510.SCRPTR_LADAPTA_FIELD 26;



.CONST $aec510.SCRPTR_EXP_MTS_ADAPT_FIELD 27;



.CONST $aec510.SCRPTR_ATTENUATION_FIELD 28;



.CONST $aec510.SCRPTR_W_RI_FIELD 29;



.CONST $aec510.SCRPTR_LADAPTR_FIELD 30;



.CONST $aec510.SCRPTR_DTC_LIN_FIELD 31;



.CONST $aec510.SCRPTR_T_FIELD 32;




.CONST $aec510.SCRPTR_RERDT_DTC_FIELD 33;




.CONST $aec510.GB_REAL_FIELD 34;




.CONST $aec510.GB_IMAG_FIELD 35;




.CONST $aec510.GB_BEXP_FIELD 36;




.CONST $aec510.L_RATSQG_FIELD 37;





.CONST $aec510.HF_FLAG_FIELD 38;



.CONST $aec510.G_OMS_IN2_FIELD 1 + $aec510.HF_FLAG_FIELD;
.CONST $aec510.L2PXT_FIELD 1 + $aec510.G_OMS_IN2_FIELD;
.CONST $aec510.L2PDT_FIELD 1 + $aec510.L2PXT_FIELD;


.CONST $aec510.L_MUA_FIELD 1 + $aec510.L2PDT_FIELD;
.CONST $aec510.L_MUB_FIELD 1 + $aec510.L_MUA_FIELD;
.CONST $aec510.L_DTC_HFREQ_FEF_FIELD 1 + $aec510.L_MUB_FIELD;
.CONST $aec510.DTC_AVG_FIELD 1 + $aec510.L_DTC_HFREQ_FEF_FIELD;
.CONST $aec510.DTC_PROB_FIELD 1 + $aec510.DTC_AVG_FIELD;
.CONST $aec510.DTC_AVGRFE_FIELD 1 + $aec510.DTC_PROB_FIELD;
.CONST $aec510.DTC_STDRFE_FIELD 1 + $aec510.DTC_AVGRFE_FIELD;
.CONST $aec510.mn_L_RatSqGt 1 + $aec510.DTC_STDRFE_FIELD;

.CONST $aec510.OFFSET_L_RatSqG 1 + $aec510.mn_L_RatSqGt;
.CONST $aec510.OFFSET_dL2PxFB $aec510.OFFSET_L_RatSqG+1;
.CONST $aec510.OFFSET_L2Pxt0 $aec510.OFFSET_dL2PxFB+1;
.CONST $aec510.OFFSET_DTC_dLpX $aec510.OFFSET_L2Pxt0+1;
.CONST $aec510.OFFSET_DTC_LpXt_prev $aec510.OFFSET_DTC_dLpX+1;


.CONST $aec510.OFFSET_tt_dtc $aec510.OFFSET_DTC_LpXt_prev+1;
.CONST $aec510.OFFSET_ct_init $aec510.OFFSET_tt_dtc+1;
.CONST $aec510.OFFSET_ct_Px $aec510.OFFSET_ct_init+1;
.CONST $aec510.OFFSET_tt_cng $aec510.OFFSET_ct_Px+1;
.CONST $aec510.OFFSET_L_DTC $aec510.OFFSET_tt_cng+1;


.CONST $aec510.OFFSET_LPXFB_RERDT $aec510.OFFSET_L_DTC+1;
.CONST $aec510.RERDT_DTC_ACTIVE_FIELD $aec510.OFFSET_LPXFB_RERDT+1;


.CONST $aec510.OFFSET_CNG_offset $aec510.RERDT_DTC_ACTIVE_FIELD+1;


.CONST $aec510.OFFSET_AEC_COUPLING $aec510.OFFSET_CNG_offset+1;
.CONST $aec510.OFFSET_HD_L_AECgain $aec510.OFFSET_AEC_COUPLING+1;


.CONST $aec510.LPWRX_MARGIN_FIELD $aec510.OFFSET_HD_L_AECgain +1;
.CONST $aec510.MN_PWRX_DIFF_FIELD $aec510.LPWRX_MARGIN_FIELD +1;

.CONST $aec510.OFFSET_OMS_AGGRESSIVENESS $aec510.MN_PWRX_DIFF_FIELD +1;
.CONST $aec510.OFFSET_TEMP_FIELD $aec510.OFFSET_OMS_AGGRESSIVENESS +1;


.CONST $aec510.RER_BEXP_FIELD $aec510.OFFSET_TEMP_FIELD +1;
.CONST $aec510.RER_E_FIELD $aec510.RER_BEXP_FIELD +1;
.CONST $aec510.RER_L2PET_FIELD $aec510.RER_E_FIELD +1;
.CONST $aec510.OFFSET_PXRS_FIELD $aec510.RER_L2PET_FIELD +1;
.CONST $aec510.OFFSET_PXRD_FIELD $aec510.OFFSET_PXRS_FIELD +1;
.CONST $aec510.OFFSET_PDRS_FIELD $aec510.OFFSET_PXRD_FIELD +1;
.CONST $aec510.OFFSET_PDRD_FIELD $aec510.OFFSET_PDRS_FIELD +1;


.CONST $aec510.OFFSET_NUM_FREQ_BINS $aec510.OFFSET_PDRD_FIELD +1;
.CONST $aec510.OFFSET_LPWRX_MARGIN_OVFL $aec510.OFFSET_NUM_FREQ_BINS+1;
.CONST $aec510.OFFSET_LPWRX_MARGIN_SCL $aec510.OFFSET_LPWRX_MARGIN_OVFL+1;


.CONST $aec510.OFFSET_NUM_PRIMARY_TAPS $aec510.OFFSET_LPWRX_MARGIN_SCL+1;
.CONST $aec510.OFFSET_NUM_AUXILLARY_TAPS $aec510.OFFSET_NUM_PRIMARY_TAPS+1;
.CONST $aec510.OFFSET_AEC_L_MUA_ON $aec510.OFFSET_NUM_AUXILLARY_TAPS+1;
.CONST $aec510.OFFSET_AEC_L_MUB_ON $aec510.OFFSET_AEC_L_MUA_ON+1;
.CONST $aec510.OFFSET_AEC_ALFA_A $aec510.OFFSET_AEC_L_MUB_ON+1;
.CONST $aec510.OFFSET_AEC_L_ALFA_A $aec510.OFFSET_AEC_ALFA_A+1;
.CONST $aec510.OFFSET_DTC_scale_dLpX $aec510.OFFSET_AEC_L_ALFA_A+1;

.CONST $aec510.FLAG_BYPASS_CNG_FIELD 1 + $aec510.OFFSET_DTC_scale_dLpX;
.CONST $aec510.FLAG_BYPASS_RER_FIELD 1 + $aec510.FLAG_BYPASS_CNG_FIELD;
.CONST $aec510.FLAG_BYPASS_RERDT_FIELD 1 + $aec510.FLAG_BYPASS_RER_FIELD;
.CONST $aec510.FLAG_BYPASS_RERDEV_FIELD 1 + $aec510.FLAG_BYPASS_RERDT_FIELD;
.CONST $aec510.FLAG_BYPASS_RERCBA_FIELD 1 + $aec510.FLAG_BYPASS_RERDEV_FIELD;
.CONST $aec510.FLAG_BYPASS_FBC_FIELD 1 + $aec510.FLAG_BYPASS_RERCBA_FIELD;

.CONST $aec510.STRUCT_SIZE 1 + $aec510.FLAG_BYPASS_FBC_FIELD;
.linefile 355 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.dm.PTR_MIC_MODE_FIELD 0;



.CONST $aec510.dm.PTR_FBC1_OBJ_FIELD 1;



.CONST $aec510.dm.D1_FIELD 2;



.CONST $aec510.dm.GA1_REAL_FIELD 3;



.CONST $aec510.dm.GA1_IMAG_FIELD 4;



.CONST $aec510.dm.GA1_BEXP_FIELD 5;

.CONST $aec510.dm.STRUCT_SIZE 6;






.CONST $M.FDNLP_500.OFFSET_VSM_HB 0;
.CONST $M.FDNLP_500.OFFSET_VSM_LB $M.FDNLP_500.OFFSET_VSM_HB+1;
.CONST $M.FDNLP_500.OFFSET_VSM_MAX_ATT $M.FDNLP_500.OFFSET_VSM_LB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_HB $M.FDNLP_500.OFFSET_VSM_MAX_ATT+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_LB $M.FDNLP_500.OFFSET_FDNLP_HB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_MB $M.FDNLP_500.OFFSET_FDNLP_LB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_NBINS $M.FDNLP_500.OFFSET_FDNLP_MB+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ATT $M.FDNLP_500.OFFSET_FDNLP_NBINS+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ATT_THRESH $M.FDNLP_500.OFFSET_FDNLP_ATT+1;
.CONST $M.FDNLP_500.OFFSET_FDNLP_ECHO_THRESH $M.FDNLP_500.OFFSET_FDNLP_ATT_THRESH+1;
.CONST $M.FDNLP_500.STRUCT_SIZE $M.FDNLP_500.OFFSET_FDNLP_ECHO_THRESH+1;






.CONST $aec510.nlp.Parameter.OFFSET_HD_THRESH_GAIN 0;
.CONST $aec510.nlp.Parameter.OFFSET_TIER2_THRESH 1;
.CONST $aec510.nlp.Parameter.OFFSET_TIER1_CONFIG $aec510.nlp.Parameter.OFFSET_TIER2_THRESH + 1;
.CONST $aec510.nlp.Parameter.OFFSET_TIER2_CONFIG $aec510.nlp.Parameter.OFFSET_TIER1_CONFIG + $M.FDNLP_500.STRUCT_SIZE;

.CONST $aec510.nlp.Parameter.HF_OBJECT_SIZE $aec510.nlp.Parameter.OFFSET_TIER2_CONFIG + $M.FDNLP_500.STRUCT_SIZE;
.CONST $aec510.nlp.Parameter.HS_OBJECT_SIZE 2;
.linefile 418 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.nlp.AEC_OBJ_PTR 0;



.CONST $aec510.nlp.OFFSET_PARAM_PTR 1;




.CONST $aec510.nlp.OFFSET_CALLSTATE_PTR 2;



.CONST $aec510.nlp.OFFSET_PTR_RCV_DETECT 3;



.CONST $aec510.nlp.OFFSET_SCRPTR_Attenuation 4;



.CONST $aec510.nlp.OFFSET_SCRPTR 5;





.CONST $aec510.nlp.FDNLP_FUNCPTR 6;





.CONST $aec510.nlp.VSM_FUNCPTR 7;


.CONST $aec510.nlp.OFFSET_PTR_RatFE $aec510.nlp.VSM_FUNCPTR+1;
.CONST $aec510.nlp.OFFSET_PTR_SqGr $aec510.nlp.OFFSET_PTR_RatFE+1;
.CONST $aec510.nlp.OFFSET_PTR_L2ABSGR $aec510.nlp.OFFSET_PTR_SqGr+1;
.CONST $aec510.nlp.OFFSET_SCRPTR_absGr $aec510.nlp.OFFSET_PTR_L2ABSGR+1;
.CONST $aec510.nlp.OFFSET_SCRPTR_temp $aec510.nlp.OFFSET_SCRPTR_absGr+1;
.CONST $aec510.nlp.OFFSET_PTR_CUR_CONFIG $aec510.nlp.OFFSET_SCRPTR_temp+1;
.CONST $aec510.nlp.OFFSET_hd_ct_hold $aec510.nlp.OFFSET_PTR_CUR_CONFIG+$M.FDNLP_500.STRUCT_SIZE;
.CONST $aec510.nlp.OFFSET_hd_att $aec510.nlp.OFFSET_hd_ct_hold+1;
.CONST $aec510.nlp.OFFSET_G_vsm $aec510.nlp.OFFSET_hd_att+1;
.CONST $aec510.nlp.OFFSET_fdnlp_cont_test $aec510.nlp.OFFSET_G_vsm+1;
.CONST $aec510.nlp.OFFSET_mean_len $aec510.nlp.OFFSET_fdnlp_cont_test+1;
.CONST $aec510.nlp.OFFSET_Vad_ct_burst $aec510.nlp.OFFSET_mean_len+1;
.CONST $aec510.nlp.OFFSET_Vad_ct_hang $aec510.nlp.OFFSET_Vad_ct_burst+1;

.CONST $aec510.nlp.FLAG_BYPASS_HD_FIELD $aec510.nlp.OFFSET_Vad_ct_hang+1;
.CONST $aec510.nlp.OFFSET_HC_TIER_STATE $aec510.nlp.FLAG_BYPASS_HD_FIELD+1;
.CONST $aec510.nlp.OFFSET_NUM_FREQ_BINS $aec510.nlp.OFFSET_HC_TIER_STATE+1;
.CONST $aec510.nlp.OFFSET_D_REAL_PTR $aec510.nlp.OFFSET_NUM_FREQ_BINS+1;
.CONST $aec510.nlp.OFFSET_D_IMAG_PTR $aec510.nlp.OFFSET_D_REAL_PTR+1;

.CONST $aec510.nlp.STRUCT_SIZE $aec510.nlp.OFFSET_D_IMAG_PTR+1;
.linefile 485 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/aec510/aec510_library.h"
.CONST $aec510.fbc.STREAM_D_FIELD 0;
.CONST $aec510.fbc.STREAM_X_FIELD 1;
.CONST $aec510.fbc.PTR_VADX_FIELD 2;
.CONST $aec510.fbc.G_A_FIELD 3;
.CONST $aec510.fbc.G_B_FIELD 4;
.CONST $aec510.fbc.PERD_FIELD 5;


.CONST $aec510.fbc.FILTER_LENGTH_FIELD 6;
.CONST $aec510.fbc.FRAME_SIZE_FIELD 1 + $aec510.fbc.FILTER_LENGTH_FIELD;
.CONST $aec510.fbc.G_A_AMP_FIELD 1 + $aec510.fbc.FRAME_SIZE_FIELD;
.CONST $aec510.fbc.G_B_AMP_FIELD 1 + $aec510.fbc.G_A_AMP_FIELD;
.CONST $aec510.fbc.X_BUF_PWR_GW_FIELD 1 + $aec510.fbc.G_B_AMP_FIELD;
.CONST $aec510.fbc.X_BUF_PWR_MSW_FIELD 1 + $aec510.fbc.X_BUF_PWR_GW_FIELD;
.CONST $aec510.fbc.X_BUF_PWR_LSW_FIELD 1 + $aec510.fbc.X_BUF_PWR_MSW_FIELD;
.CONST $aec510.fbc.MU_MANTISA_FIELD 1 + $aec510.fbc.X_BUF_PWR_LSW_FIELD;
.CONST $aec510.fbc.MU_EXP_FIELD 1 + $aec510.fbc.MU_MANTISA_FIELD;
.CONST $aec510.fbc.MU2_MANTISA_FIELD 1 + $aec510.fbc.MU_EXP_FIELD;
.CONST $aec510.fbc.MU2_EXP_FIELD 1 + $aec510.fbc.MU2_MANTISA_FIELD;
.CONST $aec510.fbc.DERLE_AMP_FIELD 1 + $aec510.fbc.MU2_EXP_FIELD;
.CONST $aec510.fbc.DERLE_FIL_FIELD 1 + $aec510.fbc.DERLE_AMP_FIELD;
.CONST $aec510.fbc.ERLE_FOLD_FIELD 1 + $aec510.fbc.DERLE_FIL_FIELD;
.CONST $aec510.fbc.HD_FOLD_FIELD 1 + $aec510.fbc.ERLE_FOLD_FIELD;
.CONST $aec510.fbc.HD_FLAG_FIELD 1 + $aec510.fbc.HD_FOLD_FIELD;
.CONST $aec510.fbc.HD_CNTR_FIELD 1 + $aec510.fbc.HD_FLAG_FIELD;
.CONST $aec510.fbc.TH_CNTR_FIELD 1 + $aec510.fbc.HD_CNTR_FIELD;
.CONST $aec510.fbc.SIL_CNTR_FIELD 1 + $aec510.fbc.TH_CNTR_FIELD;
.CONST $aec510.fbc.DIVERGE_FLAG_FIELD 1 + $aec510.fbc.SIL_CNTR_FIELD;
.CONST $aec510.fbc.LRAT_0_FIELD 1 + $aec510.fbc.DIVERGE_FLAG_FIELD;
.CONST $aec510.fbc.LRAT_1_FIELD 1 + $aec510.fbc.LRAT_0_FIELD;
.CONST $aec510.fbc.LRAT_2_FIELD 1 + $aec510.fbc.LRAT_1_FIELD;
.CONST $aec510.fbc.L2P_IBUF_D_FIELD 1 + $aec510.fbc.LRAT_2_FIELD;
.CONST $aec510.fbc.L2P_OBUF_D_FIELD 1 + $aec510.fbc.L2P_IBUF_D_FIELD;
.CONST $aec510.fbc.L2P_OBUF_D_1_FIELD 1 + $aec510.fbc.L2P_OBUF_D_FIELD;
.CONST $aec510.fbc.L2P_OBUF_D_2_FIELD 1 + $aec510.fbc.L2P_OBUF_D_1_FIELD;
.CONST $aec510.fbc.L2_HD_GAIN_FIELD 1 + $aec510.fbc.L2P_OBUF_D_2_FIELD;
.CONST $aec510.fbc.HD_GAIN_FIELD 1 + $aec510.fbc.L2_HD_GAIN_FIELD;
.CONST $aec510.fbc.IBUF_D_PRE_PWR_FIELD 1 + $aec510.fbc.HD_GAIN_FIELD;
.CONST $aec510.fbc.OBUF_D_PRE_PWR_FIELD 1 + $aec510.fbc.IBUF_D_PRE_PWR_FIELD;
.CONST $aec510.fbc.L2P_PREP_FBC_FIELD 1 + $aec510.fbc.OBUF_D_PRE_PWR_FIELD;
.CONST $aec510.fbc.L2P_PWR_DIFFERENCE_FIELD 1 + $aec510.fbc.L2P_PREP_FBC_FIELD;
.CONST $aec510.fbc.TEMP0_FIELD 1 + $aec510.fbc.L2P_PWR_DIFFERENCE_FIELD;
.CONST $aec510.fbc.TEMP1_FIELD 1 + $aec510.fbc.TEMP0_FIELD;

.CONST $aec510.fbc.STRUCT_SIZE 1 + $aec510.fbc.TEMP1_FIELD;






.CONST $M.filter_bank.Parameters.OFFSET_DELAY_STREAM_PTR 6;
.CONST $M.filter_bank.Parameters.OFFSET_DELAY_PARAM_PTR 7;
.CONST $aec510.filter_bank.Parameters.ONE_CHNL_BLOCK_SIZE 8;
.linefile 34 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cvc_modules.h" 2
.linefile 22 "main.asm" 2
.linefile 1 "a2dp_low_latency_2mic.h" 1
.linefile 11 "a2dp_low_latency_2mic.h"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/a2dp_low_latency_2mic_config.h" 1
.linefile 12 "a2dp_low_latency_2mic.h" 2
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/a2dp_low_latency_2mic_library_gen.h" 1
.linefile 12 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/a2dp_low_latency_2mic_library_gen.h"
.CONST $A2DP_LOW_LATENCY_2MIC_SYSID 0xE103;


.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.SPKR_EQ_BYPASS 0x000400;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.EQFLAT 0x000200;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.USER_EQ_BYPASS 0x000100;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BASS_BOOST_BYPASS 0x000080;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.SPATIAL_BYPASS 0x000040;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.COMPANDER_BYPASS 0x000020;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.DITHER_BYPASS 0x000010;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.USER_EQ_SELECT 0x000007;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.CNGENA 0x200000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_SNDAGC 0x000800;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.SIDETONEENA 0x002000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.RERENA 0x000004;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.AECENA 0x000002;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.HDBYP 0x001000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_AGCPERSIST 0x008000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_MGDC 0x000002;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_SPP 0x000040;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_GSMOOTH 0x000080;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_NFLOOR 0x000100;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.GSCHEME 0x000200;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.DMSS_MODE 0x000001;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_ADF 0x000008;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_NC 0x000010;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_WNR 0x000004;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_DMS 0x000020;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_MGDCPERSIST 0x000400;


.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CUR_MODE_OFFSET 0;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.SYSCONTROL_OFFSET 1;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.FUNC_MIPS_OFFSET 2;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.DECODER_MIPS_OFFSET 3;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_PCMINL_OFFSET 4;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_PCMINR_OFFSET 5;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_DACL_OFFSET 6;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_DACR_OFFSET 7;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_SUB_OFFSET 8;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CUR_DACL_OFFSET 9;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.USER_EQ_BANK_OFFSET 10;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CONFIG_FLAG_OFFSET 11;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.DELAY 12;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_TYPE_OFFSET 13;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_FS_OFFSET 14;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_CHANNEL_MODE 15;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_STAT1 16;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_STAT2 17;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_STAT3 18;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_STAT4 19;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_STAT5 20;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.INTERFACE_TYPE 21;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.INPUT_RATE 22;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.OUTPUT_RATE 23;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CODEC_RATE 24;

.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CALL_STATE_OFFSET 25;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.SEC_STAT_OFFSET 26;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_ADC_LEFT_OFFSET 27;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_ADC_RIGHT_OFFSET 28;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_SCO_OUT_OFFSET 29;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_MIPS_OFFSET 30;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_AUX_OFFSET 31;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.CONNSTAT 32;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.SIDETONE_GAIN 33;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.VOLUME 34;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.PEAK_SIDETONE 35;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.SND_AGC_SPEECH_LVL 36;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.SND_AGC_GAIN 37;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.AEC_COUPLING_OFFSET 38;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.WNR_POWER 39;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.WNR_WIND_PHASE 40;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.WIND_FLAG 41;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.DSP_VOL_FLAG 42;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.DSP_VOL 43;
.CONST $M.A2DP_LOW_LATENCY_2MIC.STATUS.BLOCK_SIZE 44;


.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.STANDBY 0;
.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.PSTHRGH_LEFT 1;
.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.PSTHRGH_RIGHT 2;
.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.FULLPROC 3;
.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.LOWVOLUME 4;
.CONST $M.A2DP_LOW_LATENCY_2MIC.SYSMODE.MAX_MODES 5;


.CONST $M.A2DP_LOW_LATENCY_2MIC.CONTROL.DAC_OVERRIDE 0x8000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONTROL.CALLSTATE_OVERRIDE 0x4000;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CONTROL.MODE_OVERRIDE 0x2000;


.CONST $M.A2DP_LOW_LATENCY_2MIC.INTERFACE.UNUSED 0;
.CONST $M.A2DP_LOW_LATENCY_2MIC.INTERFACE.ANALOG 1;
.CONST $M.A2DP_LOW_LATENCY_2MIC.INTERFACE.I2S 2;


.CONST $M.A2DP_LOW_LATENCY_2MIC.CALLST.MUTE 0;
.CONST $M.A2DP_LOW_LATENCY_2MIC.CALLST.CONNECTED 1;


.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CONFIG 0;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ1_CONFIG 1;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_NUM_BANDS 2;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_MASTER_GAIN 3;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE1_TYPE 4;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE1_FC 5;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE1_GAIN 6;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE1_Q 7;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE2_TYPE 8;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE2_FC 9;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE2_GAIN 10;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE2_Q 11;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE3_TYPE 12;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE3_FC 13;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE3_GAIN 14;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE3_Q 15;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE4_TYPE 16;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE4_FC 17;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE4_GAIN 18;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE4_Q 19;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE5_TYPE 20;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE5_FC 21;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE5_GAIN 22;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE5_Q 23;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE6_TYPE 24;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE6_FC 25;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE6_GAIN 26;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE6_Q 27;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE7_TYPE 28;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE7_FC 29;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE7_GAIN 30;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE7_Q 31;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE8_TYPE 32;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE8_FC 33;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE8_GAIN 34;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE8_Q 35;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE9_TYPE 36;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE9_FC 37;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE9_GAIN 38;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE9_Q 39;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE10_TYPE 40;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE10_FC 41;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE10_GAIN 42;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SPKR_EQ_STAGE10_Q 43;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_NUM_BANDS 44;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_MASTER_GAIN 45;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_TYPE 46;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_FC 47;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_GAIN 48;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BOOST_EQ_Q 49;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ_NUM_BANKS 50;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_NUM_BANDS 51;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_MASTER_GAIN 52;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE1_TYPE 53;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE1_FC 54;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE1_GAIN 55;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE1_Q 56;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE2_TYPE 57;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE2_FC 58;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE2_GAIN 59;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE2_Q 60;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE3_TYPE 61;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE3_FC 62;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE3_GAIN 63;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE3_Q 64;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE4_TYPE 65;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE4_FC 66;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE4_GAIN 67;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE4_Q 68;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE5_TYPE 69;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE5_FC 70;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE5_GAIN 71;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ1_STAGE5_Q 72;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_NUM_BANDS 73;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_MAST_ERGAIN 74;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE1_TYPE 75;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE1_FC 76;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE1_GAIN 77;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE1_Q 78;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE2_TYPE 79;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE2_FC 80;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE2_GAIN 81;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE2_Q 82;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE3_TYPE 83;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE3_FC 84;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE3_GAIN 85;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE3_Q 86;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE4_TYPE 87;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE4_FC 88;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE4_GAIN 89;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE4_Q 90;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE5_TYPE 91;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE5_FC 92;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE5_GAIN 93;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ2_STAGE5_Q 94;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_NUM_BANDS 95;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_MASTER_GAIN 96;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE1_TYPE 97;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE1_FC 98;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE1_GAIN 99;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE1_Q 100;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE2_TYPE 101;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE2_FC 102;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE2_GAIN 103;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE2_Q 104;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE3_TYPE 105;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE3_FC 106;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE3_GAIN 107;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE3_Q 108;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE4_TYPE 109;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE4_FC 110;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE4_GAIN 111;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE4_Q 112;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE5_TYPE 113;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE5_FC 114;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE5_GAIN 115;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ3_STAGE5_Q 116;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_NUM_BANDS 117;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_MASTER_GAIN 118;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE1_TYPE 119;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE1_FC 120;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE1_GAIN 121;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE1_Q 122;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE2_TYPE 123;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE2_FC 124;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE2_GAIN 125;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE2_Q 126;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE3_TYPE 127;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE3_FC 128;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE3_GAIN 129;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE3_Q 130;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE4_TYPE 131;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE4_FC 132;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE4_GAIN 133;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE4_Q 134;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE5_TYPE 135;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE5_FC 136;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE5_GAIN 137;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ4_STAGE5_Q 138;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_NUM_BANDS 139;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_MASTER_GAIN 140;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE1_TYPE 141;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE1_FC 142;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE1_GAIN 143;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE1_Q 144;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE2_TYPE 145;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE2_FC 146;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE2_GAIN 147;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE2_Q 148;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE3_TYPE 149;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE3_FC 150;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE3_GAIN 151;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE3_Q 152;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE4_TYPE 153;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE4_FC 154;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE4_GAIN 155;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE4_Q 156;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE5_TYPE 157;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE5_FC 158;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE5_GAIN 159;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ5_STAGE5_Q 160;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_NUM_BANDS 161;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_MASTER_GAIN 162;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE1_TYPE 163;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE1_FC 164;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE1_GAIN 165;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE1_Q 166;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE2_TYPE 167;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE2_FC 168;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE2_GAIN 169;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE2_Q 170;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE3_TYPE 171;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE3_FC 172;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE3_GAIN 173;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE3_Q 174;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE4_TYPE 175;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE4_FC 176;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE4_GAIN 177;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE4_Q 178;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE5_TYPE 179;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE5_FC 180;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE5_GAIN 181;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_USER_EQ6_STAGE5_Q 182;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SDICONFIG 183;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DAC_GAIN_L 184;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DAC_GAIN_R 185;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TABLE_SIZE 186;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE0 187;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE1 188;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE2 189;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE3 190;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE4 191;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE5 192;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE6 193;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE7 194;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE8 195;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE9 196;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE10 197;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE11 198;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE12 199;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE13 200;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE14 201;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE15 202;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SB_TABLE16 203;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE0 204;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE1 205;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE2 206;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE3 207;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE4 208;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE5 209;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE6 210;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE7 211;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE8 212;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE9 213;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE10 214;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE11 215;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE12 216;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE13 217;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE14 218;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE15 219;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_SW_TABLE16 220;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE_SIZE 221;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE0 222;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE1 223;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE2 224;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE3 225;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE4 226;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE5 227;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SWAT_TRIM_TABLE6 228;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_CONFIG 229;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_A1 230;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_A2 231;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_A3 232;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_A4 233;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_A5 234;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_BASS_MANAGER_COEF_FREQ 235;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_S_EQ_B1 236;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_S_EQ_B0 237;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_S_EQ_A1 238;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP1_B2 239;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP1_B1 240;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP1_B0 241;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP2_B2 242;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP2_B1 243;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_L_AP2_B0 244;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP1_B2 245;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP1_B1 246;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP1_B0 247;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP2_B2 248;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP2_B1 249;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MELOD_EXPANSION_R_AP2_B0 250;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_THRESHOLD1 251;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_THRESHOLD1 252;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_THRESHOLD1 253;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_THRESHOLD1 254;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_EXPAND_RATIO1 255;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_LINEAR_RATIO1 256;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_COMPRESS_RATIO1 257;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_LIMIT_RATIO1 258;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_ATTACK_TC1 259;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_DECAY_TC1 260;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_ATTACK_TC1 261;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_DECAY_TC1 262;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_ATTACK_TC1 263;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_DECAY_TC1 264;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_ATTACK_TC1 265;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_DECAY_TC1 266;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MAKEUP_GAIN1 267;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_THRESHOLD2 268;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_THRESHOLD2 269;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_THRESHOLD2 270;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_THRESHOLD2 271;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_EXPAND_RATIO2 272;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_LINEAR_RATIO2 273;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_COMPRESS_RATIO2 274;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_LIMIT_RATIO2 275;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_ATTACK_TC2 276;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_EXPAND_DECAY_TC2 277;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_ATTACK_TC2 278;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LINEAR_DECAY_TC2 279;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_ATTACK_TC2 280;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_COMPRESS_DECAY_TC2 281;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_ATTACK_TC2 282;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LIMIT_DECAY_TC2 283;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MAKEUP_GAIN2 284;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DITHER_NOISE_SHAPE 285;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC1_CONFIG 286;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC2_CONFIG 287;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC3_CONFIG 288;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC4_CONFIG 289;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC5_CONFIG 290;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC6_CONFIG 291;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC7_CONFIG 292;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC8_CONFIG 293;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC9_CONFIG 294;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC10_CONFIG 295;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_HFK_CONFIG 296;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ADC_GAIN_LEFT 297;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ADC_GAIN_RIGHT 298;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_CONFIG 299;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_GAIN_EXP 300;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_GAIN_MANT 301;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B2 302;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B1 303;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B0 304;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A2 305;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A1 306;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B2 307;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B1 308;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B0 309;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A2 310;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A1 311;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B2 312;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B1 313;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B0 314;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A2 315;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A1 316;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B2 317;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B1 318;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B0 319;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A2 320;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A1 321;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B2 322;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B1 323;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B0 324;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A2 325;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A1 326;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE1 327;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE2 328;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE3 329;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE4 330;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE5 331;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE 332;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE1 333;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE2 334;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE3 335;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE4 336;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE5 337;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE6 338;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE7 339;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE8 340;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE9 341;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE10 342;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE11 343;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE12 344;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE13 345;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE14 346;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE15 347;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_CLIP_POINT 348;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_ADJUST_LIMIT 349;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_STF_SWITCH 350;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_STF_NOISE_LOW_THRES 351;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_STF_NOISE_HIGH_THRES 352;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_STF_GAIN_EXP 353;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_STF_GAIN_MANTISSA 354;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_CONFIG 355;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_GAIN_EXP 356;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_GAIN_MANT 357;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE1_B2 358;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE1_B1 359;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE1_B0 360;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE1_A2 361;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE1_A1 362;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE2_B2 363;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE2_B1 364;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE2_B0 365;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE2_A2 366;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE2_A1 367;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE3_B2 368;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE3_B1 369;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE3_B0 370;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE3_A2 371;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_STAGE3_A1 372;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_SCALE1 373;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_SCALE2 374;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ST_PEQ_SCALE3 375;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SNDGAIN_MANTISSA 376;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SNDGAIN_EXPONENT 377;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_PT_SNDGAIN_MANTISSA 378;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_PT_SNDGAIN_EXPONENT 379;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_G_INITIAL 380;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_TARGET 381;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_ATTACK_TC 382;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_DECAY_TC 383;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_A_90_PK 384;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_D_90_PK 385;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_G_MAX 386;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_START_COMP 387;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_COMP 388;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_INP_THRESH 389;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_SP_ATTACK 390;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_AD_THRESH1 391;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_AD_THRESH2 392;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_G_MIN 393;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_ECHO_HOLD_TIME 394;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_SND_AGC_NOISE_HOLD_TIME 395;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_ATTACK_TC 396;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_DECAY_TC 397;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_ENVELOPE_TC 398;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_INIT_FRAME_THRESH 399;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_RATIO 400;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_MIN_SIGNAL 401;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_MIN_MAX_ENVELOPE 402;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_DELTA_THRESHOLD 403;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RCV_VAD_COUNT_THRESHOLD 404;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ENABLE_AEC_REUSE 405;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DMSS_LPN_MIC 406;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DMSS_CONFIG 407;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASF_MIC_DISTANCE 408;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASF_WNR_AGGR 409;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASF_WNR_THRESHOLD 410;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASF_BETA0 411;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASF_BETA1 412;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_WNR_THRESH_PHASE 413;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_WNR_THRESH_COHERENCE 414;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MGDC_MAXCOMP 415;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_MGDC_TH 416;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ASR_OMS_AGGR 417;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DMS_AGGR 418;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_RESIDUAL_NFLOOR 419;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_LVMODE_THRES 420;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_REF_DELAY 421;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_ADCGAIN_SSR 422;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CNG_Q 423;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CNG_SHAPE 424;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DTC_AGGR 425;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_HD_THRESH_GAIN 426;

.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_0 427;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_1 428;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_2 429;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_3 430;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_4 431;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_5 432;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_6 433;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_7 434;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_8 435;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DSP_USER_9 436;
.CONST $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.STRUCT_SIZE 437;
.linefile 13 "a2dp_low_latency_2mic.h" 2

.CONST $AUDIO_IF_MASK (0x00ff);
.CONST $LOCAL_PLAYBACK_MASK (0x0100);

.CONST $cmpd100.OFFSET_CONTROL_WORD 0;
.CONST $cmpd100.OFFSET_ENABLE_BIT_MASK 1;
.CONST $cmpd100.OFFSET_INPUT_CH1_PTR 2;
.CONST $cmpd100.OFFSET_INPUT_CH2_PTR 3;
.CONST $cmpd100.OFFSET_OUTPUT_CH1_PTR 4;
.CONST $cmpd100.OFFSET_OUTPUT_CH2_PTR 5;
.CONST $cmpd100.OFFSET_MAKEUP_GAIN 6;
.CONST $cmpd100.OFFSET_GAIN_PTR 7;
.CONST $cmpd100.OFFSET_NEG_ONE 8;
.CONST $cmpd100.OFFSET_POW2_NEG4 9;
.CONST $cmpd100.OFFSET_EXPAND_THRESHOLD 10;
.CONST $cmpd100.OFFSET_LINEAR_THRESHOLD 11;
.CONST $cmpd100.OFFSET_COMPRESS_THRESHOLD 12;
.CONST $cmpd100.OFFSET_LIMIT_THRESHOLD 13;
.CONST $cmpd100.OFFSET_INV_EXPAND_RATIO 14;
.CONST $cmpd100.OFFSET_INV_LINEAR_RATIO 15;
.CONST $cmpd100.OFFSET_INV_COMPRESS_RATIO 16;
.CONST $cmpd100.OFFSET_INV_LIMIT_RATIO 17;
.CONST $cmpd100.OFFSET_EXPAND_CONSTANT 18;
.CONST $cmpd100.OFFSET_LINEAR_CONSTANT 19;
.CONST $cmpd100.OFFSET_COMPRESS_CONSTANT 20;
.CONST $cmpd100.OFFSET_EXPAND_ATTACK_TC 21;
.CONST $cmpd100.OFFSET_EXPAND_DECAY_TC 22;
.CONST $cmpd100.OFFSET_LINEAR_ATTACK_TC 23;
.CONST $cmpd100.OFFSET_LINEAR_DECAY_TC 24;
.CONST $cmpd100.OFFSET_COMPRESS_ATTACK_TC 25;
.CONST $cmpd100.OFFSET_COMPRESS_DECAY_TC 26;
.CONST $cmpd100.OFFSET_LIMIT_ATTACK_TC 27;
.CONST $cmpd100.OFFSET_LIMIT_DECAY_TC 28;
.CONST $cmpd100.OFFSET_HEADROOM_COMPENSATION 29;
.CONST $cmpd100.STRUC_SIZE 30;


.CONST $INVALID_IO -1;
.CONST $FASTSTREAM_IO 4;
.CONST $APTX_ACL_SPRINT_IO 7;


.CONST $FASTSTREAM_CODEC_CONFIG $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC1_CONFIG;
.CONST $APTX_ACL_SPRINT_CODEC_CONFIG $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_CODEC2_CONFIG;


.CONST $FASTSTREAM_CODEC_TYPE 0;
.CONST $APTX_ACL_SPRINT_CODEC_TYPE 1;






.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/flash.h" 1
.linefile 68 "a2dp_low_latency_2mic.h" 2

.CONST $CVC.BW.PARAM.SYS_FS 0;
.CONST $CVC.BW.PARAM.Num_Samples_Per_Frame 1;
.CONST $CVC.BW.PARAM.Num_FFT_Freq_Bins 2;
.CONST $CVC.BW.PARAM.Num_FFT_Window 3;

.CONST $CVC.BW.PARAM.OMS_MODE_OBJECT 5;
.CONST $CVC.BW.PARAM.AEC_LPWRX_MARGIN_OVFL 6;
.CONST $CVC.BW.PARAM.AEC_LPWRX_MARGIN_SCL 7;
.CONST $CVC.BW.PARAM.AEC_PTR_NZ_TABLES 8;
.CONST $CVC.BW.PARAM.VAD_PEQ_PARAM_PTR 9;
.CONST $CVC.BW.PARAM.DCBLOC_PEQ_PARAM_PTR 10;
.CONST $CVC.BW.PARAM.FB_CONFIG_RCV_ANALYSIS 11;
.CONST $CVC.BW.PARAM.FB_CONFIG_RCV_SYNTHESIS 12;
.CONST $CVC.BW.PARAM.FB_CONFIG_AEC 13;

.CONST $CVC.BW.PARAM.BANDWIDTDH_ID 14;
.CONST $CVC.BW.PARAM.ASF_MODE 15;
.CONST $CVC.BW.PARAM.DMS_MODE 16;
.CONST $M.CVC.vad_hold.PTR_VAD_FLAG_FIELD 0;
.CONST $M.CVC.vad_hold.PTR_EVENT_FLAG_FIELD 1;
.CONST $M.CVC.vad_hold.FLAG_FIELD 2;
.CONST $M.CVC.vad_hold.PTR_HOLD_TIME_FRAMES_FIELD 3;
.CONST $M.CVC.vad_hold.HOLD_COUNTDOWN_FIELD 4;
.CONST $M.CVC.vad_hold.STRUC_SIZE 5;
.linefile 115 "a2dp_low_latency_2mic.h"
   .CONST $M.CVC.Num_FFT_Freq_Bins 129;
   .CONST $M.CVC.Num_Samples_Per_Frame 120;
   .CONST $M.CVC.Num_FFT_Window 240;
   .CONST $M.CVC.DAC_Num_Samples_Per_Frame $M.CVC.Num_Samples_Per_Frame;
   .CONST $M.CVC.ADC_DAC_Num_SYNTHESIS_FB_HISTORY ($M.CVC.Num_FFT_Window + $M.CVC.Num_Samples_Per_Frame);
   .CONST $SAMPLE_RATE_DAC 16000;
   .CONST $SAMPLE_RATE 16000;
   .CONST $BLOCK_SIZE_ADC_DAC 120;
   .CONST $M.oms270.FFT_NUM_BIN $M.CVC.Num_FFT_Freq_Bins;
   .CONST $M.oms270.STATE_LENGTH $M.oms270.wide_band.STATE_LENGTH;
   .CONST $M.oms270.SCRATCH_LENGTH $M.oms270.wide_band.SCRATCH_LENGTH;
.linefile 161 "a2dp_low_latency_2mic.h"
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.DMSS_MODE $M.A2DP_LOW_LATENCY_2MIC.CONFIG.DMSS_MODE;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_MGDC $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_MGDC;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_WNR $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_WNR;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_ADF $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_ADF;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_NC $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_NC;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_DMS $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_DMS;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_SPP $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_SPP;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_NFLOOR $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_NFLOOR;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_GSMOOTH $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_GSMOOTH;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.GSCHEME $M.A2DP_LOW_LATENCY_2MIC.CONFIG.GSCHEME;
.CONST $M.A2DP_LOW_LATENCY_2MIC.DMSS_CONFIG.BYPASS_MGDCPERSIST $M.A2DP_LOW_LATENCY_2MIC.CONFIG.BYPASS_MGDCPERSIST;
.linefile 23 "main.asm" 2
.linefile 1 "user_eq.h" 1
.linefile 11 "user_eq.h"
.linefile 1 "C:/ADK4.0.0/kalimba/lib_sets/sdk/include/cbuffer.h" 1
.linefile 12 "user_eq.h" 2



    .const $user_eq.DEFINITION_TABLE_MAX_NUM_BANKS 0;
    .const $user_eq.DEFINITION_TABLE_MAX_NUM_BANDS 1;
    .const $user_eq.DEFINITION_TABLE_LEFT_DM_PTR 2;
    .const $user_eq.DEFINITION_TABLE_RIGHT_DM_PTR 3;
    .const $user_eq.DEFINITION_TABLE_COEFS_A_PTR 4;
    .const $user_eq.DEFINITION_TABLE_COEFS_B_PTR 5;

    .const $user_eq.DEFINITION_TABLE_SIZE 6;



    .const $user_eq.num_bands 0;
    .const $user_eq.pre_gain 1;



    .const $user_eq.filter_type.bypass 0;

    .const $user_eq.filter_type.lp_1 1;
    .const $user_eq.filter_type.hp_1 2;
    .const $user_eq.filter_type.ap_1 3;

    .const $user_eq.filter_type.ls_1 4;
    .const $user_eq.filter_type.hs_1 5;
    .const $user_eq.filter_type.tlt_1 6;

    .const $user_eq.filter_type.lp_2 7;
    .const $user_eq.filter_type.hp_2 8;
    .const $user_eq.filter_type.ap_2 9;

    .const $user_eq.filter_type.ls_2 10;
    .const $user_eq.filter_type.hs_2 11;
    .const $user_eq.filter_type.tlt_2 12;

    .const $user_eq.filter_type.peq 13;



    .const $user_eq.freq_param_scale 3;
    .const $user_eq.gain_param_scale 60;
    .const $user_eq.q_param_scale 12;


    .const $user_eq.gain_lo_gain_limit -2160;
    .const $user_eq.gain_hi_gain_limit 720;


    .const $user_eq.hi_nyquist_freq_limit 0.453515;






    .const $user_eq.xp_1_lo_freq_limit 1;
    .const $user_eq.xp_1_hi_freq_limit 60000;


    .const $user_eq.xp_2_lo_freq_limit 120;
    .const $user_eq.xp_2_hi_freq_limit 60000;
    .const $user_eq.xp_2_lo_q_limit 0x0400;
    .const $user_eq.xp_2_hi_q_limit 0x2000;


    .const $user_eq.shelf_1_lo_freq_limit 60;
    .const $user_eq.shelf_1_hi_freq_limit 60000;
    .const $user_eq.shelf_1_lo_gain_limit -720;
    .const $user_eq.shelf_1_hi_gain_limit 720;


    .const $user_eq.shelf_2_lo_freq_limit 120;
    .const $user_eq.shelf_2_hi_freq_limit 60000;
    .const $user_eq.shelf_2_lo_gain_limit -720;
    .const $user_eq.shelf_2_hi_gain_limit 720;
    .const $user_eq.shelf_2_lo_q_limit 0x0400;
    .const $user_eq.shelf_2_hi_q_limit 0x2000;


    .const $user_eq.peq_lo_freq_limit 60;
    .const $user_eq.peq_hi_freq_limit 60000;
    .const $user_eq.peq_lo_gain_limit -2160;
    .const $user_eq.peq_hi_gain_limit 720;
    .const $user_eq.peq_lo_q_limit 0x0400;
    .const $user_eq.peq_hi_q_limit 0x8000;



    .const $user_eq.GAIAMSG.SET_USER_PARAM 0x121a;
    .const $user_eq.GAIAMSG.GET_USER_PARAM 0x129a;
    .const $user_eq.GAIAMSG.SET_USER_GROUP_PARAM 0x121b;
    .const $user_eq.GAIAMSG.GET_USER_GROUP_PARAM 0x129b;

    .const $user_eq.GAIAMSG.SET_USER_PARAM_RESP 0x321a;
    .const $user_eq.GAIAMSG.GET_USER_PARAM_RESP 0x329a;
    .const $user_eq.GAIAMSG.SET_USER_GROUP_PARAM_RESP 0x321b;
    .const $user_eq.GAIAMSG.GET_USER_GROUP_PARAM_RESP 0x329b;
.linefile 24 "main.asm" 2
.linefile 35 "main.asm"
.MODULE $M.main;
   .CODESEGMENT MAIN_PM;
   .DATASEGMENT DM;

   .VAR set_plugin_message_struc[$message.STRUC_SIZE];
   .VAR set_dac_rate_message_struc[$message.STRUC_SIZE];
   .VAR set_codec_rate_message_struc[$message.STRUC_SIZE];
   .VAR set_tone_rate_message_struc[$message.STRUC_SIZE];
   .VAR aptx_ll_params1_message_struc[$message.STRUC_SIZE];
   .VAR aptx_ll_params2_message_struc[$message.STRUC_SIZE];
   .VAR set_eq_bank_message_struc[$message.STRUC_SIZE];
   .VAR latency_reporting_message_struc[$message.STRUC_SIZE];

   .VAR set_user_eq_param_message_struct[$message.STRUC_SIZE];
   .VAR get_user_eq_param_message_struct[$message.STRUC_SIZE];
   .VAR set_user_eq_group_param_message_struct[$message.STRUC_SIZE];
   .VAR get_user_eq_group_param_message_struct[$message.STRUC_SIZE];


$main:

   call $stack.initialise;

   call $interrupt.initialise;

   call $message.initialise;

   call $cbuffer.initialise;

   call $pskey.initialise;

   call $Security.Initialize;





   call $flash.init_dmconst;


   r1 = &set_eq_bank_message_struc;
   r2 = 0x1039;
   r3 = &$M.set_eq_bank.func;
   call $message.register_handler;


   r1 = &set_dac_rate_message_struc;
   r2 = 0x1070;
   r3 = &$M.set_dac_rate.func;
   call $message.register_handler;


   r1 = &set_codec_rate_message_struc;
   r2 = 0x1071;
   r3 = &$M.set_codec_rate.func;
   call $message.register_handler;


   r1 = &set_tone_rate_message_struc;
   r2 = 0x1072;
   r3 = &$M.set_tone_rate.func;
   call $message.register_handler;


   r1 = &set_plugin_message_struc;
   r2 = 0x1024;
   r3 = &$M.set_plugin.func;
   call $message.register_handler;
.linefile 128 "main.asm"
    r1 = set_user_eq_param_message_struct;
    r2 = $user_eq.GAIAMSG.SET_USER_PARAM;
    r3 = $M.a2dp_low_latency_msg.SetUserEqParamMsg.func;
    call $message.register_handler;

    r1 = get_user_eq_param_message_struct;
    r2 = $user_eq.GAIAMSG.GET_USER_PARAM;
    r3 = $M.a2dp_low_latency_msg.GetUserEqParamMsg.func;
    call $message.register_handler;

    r1 = set_user_eq_group_param_message_struct;
    r2 = $user_eq.GAIAMSG.SET_USER_GROUP_PARAM;
    r3 = $M.a2dp_low_latency_msg.SetUserEqGroupParamMsg.func;
    call $message.register_handler;

    r1 = get_user_eq_group_param_message_struct;
    r2 = $user_eq.GAIAMSG.GET_USER_GROUP_PARAM;
    r3 = $M.a2dp_low_latency_msg.GetUserEqGroupParamMsg.func;
    call $message.register_handler;



   call $spi_comm.initialize;
.linefile 159 "main.asm"
   r1 = &$M.message.send_ready_wait_for_go.go_from_vm_message_struc;
   r2 = $MESSAGE_GO;
   r3 = &$M.message.send_ready_wait_for_go.go_from_vm_handler;
   call $message.register_handler;


   r2 = Null OR $MESSAGE_KALIMBA_READY;
   call $message.send_short;


   call $SendProcStart;

   call $FrontEndStart;


vm_go_wait:
      Null = M[$M.message.send_ready_wait_for_go.go_from_vm];
   if Z jump vm_go_wait;


   call $ConfigureBackEnd;

   call $BackEndStart;


frame_loop:

   call $spi_comm.polled_service_routine;

   call $DecodeInput;

   M[$ARITHMETIC_MODE] = Null;


   call $ReceiveProcRun;

   call $SendProcRun;

   call $EncodeOutput;




   r0 = M[&$M.a2dp_out.encoder_codec_stream_struc + $codec.av_encode.MODE_FIELD];
   Null = r0 - $codec.SUCCESS;
   if Z jump frame_loop;

   r0 = M[&$M.a2dp_in.decoder_codec_stream_struc + $codec.av_decode.MODE_FIELD];
   Null = r0 - $codec.SUCCESS;
   if NZ call $SystemSleep;
   jump frame_loop;

.ENDMODULE;
.linefile 221 "main.asm"
.MODULE $M.Sleep;
   .CODESEGMENT SYSTEM_SLEEP_PM;
   .DATASEGMENT DM;

   .VAR TotalTime=0;
   .VAR LastUpdateTm=0;
   .VAR Mips=0;

$SystemSleep:


   r1 = 1;
   M[$frame_sync.sync_flag] = r1;

   r1 = M[$TIMER_TIME];
   r4 = M[$interrupt.total_time];

   r6 = M[$CLOCK_DIVIDE_RATE];

   r0 = $frame_sync.MAX_CLK_DIV_RATE;
   M[$CLOCK_DIVIDE_RATE] = r0;


jp_wait:
   Null = M[$frame_sync.sync_flag];
   if NZ jump jp_wait;


   M[$CLOCK_DIVIDE_RATE] = r6;


   r3 = M[$TIMER_TIME];
   r1 = r3 - r1;
   r4 = r4 - M[$interrupt.total_time];
   r1 = r1 + r4;
   r0 = M[&TotalTime];
   r1 = r1 + r0;
   M[&TotalTime]=r1;


   r0 = M[LastUpdateTm];
   r5 = r3 - r0;
   rMAC = 1000000;
   Null = r5 - rMAC;
   if NEG rts;


   rMAC = rMAC ASHIFT -1;
   Div = rMAC/r5;

   rMAC = r5 - r1;

   M[LastUpdateTm]=r3;

   M[&TotalTime]=Null;

   r3 = DivResult;
   rMAC = r3 * rMAC (frac);



   r3 = 0.008;
   rMAC = rMAC * r3 (frac);
   M[Mips]=rMAC;
   rts;

.ENDMODULE;
.linefile 297 "main.asm"
.MODULE $M.A2DP_LOW_LATENCY_2MIC.SystemReInitialize;
   .CODESEGMENT CVC_SYSTEM_REINITIALIZE_PM;
   .DATASEGMENT DM;

 func:

   M[$M.CVC_SYS.AlgReInit] = Null;
   M[$M.CVC_SYS.FrameCounter] = Null;



   M1 = 1;
   I0 = &$M.CVC.data.ParameterMap;

   r0 = M[I0,M1];
lp_param_copy:

      r1 = M[I0,M1];

      r0 = M[r0];

      M[r1] = r0, r0 = M[I0,M1];

      Null = r0;
   if NZ jump lp_param_copy;



   r1 = $M.AEC_500.CNG_G_ADJUST;
   r0 = M[&$M.CVC.data.CurParams + $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_HFK_CONFIG];
   Null = r0 AND $M.A2DP_LOW_LATENCY_2MIC.CONFIG.CNGENA;
   if Z r1 = Null;
   M[&$M.CVC.data.aec_dm1 + $M.AEC_500.OFFSET_CNG_G_ADJUST] = r1;


   r2 = r0 AND $M.A2DP_LOW_LATENCY_2MIC.CONFIG.RERENA;
   M[&$M.CVC.data.aec_dm1 + $M.AEC_500.OFFSET_RER_func] = r2;

   r0 = M[&$M.CVC.data.CurParams + $M.A2DP_LOW_LATENCY_2MIC.PARAMETERS.OFFSET_DMS_AGGR];
   M[&$M.CVC.data.aec_dm1 + $M.AEC_500.OFFSET_OMS_AGGRESSIVENESS] = r0;




   push rLink;


   r4 = &$M.CVC.data.ReInitializeTable;
   call $frame_sync.run_function_table;


   r4 = &$M.CVC.data.FilterResetTable;
   call $frame_sync.run_function_table;




   jump $pop_rLink_and_rts;

.ENDMODULE;
