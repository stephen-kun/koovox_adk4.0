// *****************************************************************************
// Copyright Cambridge Silicon Radio Limited 2005 - 2015.        http://www.csr.com
// Part of ADK 4.0
//
// $Change: 2317643 $  $DateTime: 2015/07/10 11:14:28 $
// *****************************************************************************

// C stubs for "sbcdec" library
// These obey the C compiler calling convention (see documentation)
// Comments show the syntax to call the routine also see matching header file
#ifndef SBC_WBS_ONLY

.MODULE $M.sbcdec_c_stubs;
   .CODESEGMENT SBCDEC_C_STUBS_PM;


// sbcdec_frame_decode(int *decoder_struc_pointer);
$_sbcdec_frame_decode:
   pushm <r4, r5, r6, r7, r9, r10, rLink>;
   pushm <I0, I1, I4, I5, I6, I7, M0, M1, M2, M3, L0, L1, L4, L5>;
   r8 = r0;
   call $sbcdec.frame_decode;
   pushm <I0, I1, I4, I5, I6, I7, M0, M1, M2, M3, L0, L1, L4, L5>;
   popm <r4, r5, r6, r7, r9, r10, rLink>;
   rts;

.ENDMODULE;
#endif

