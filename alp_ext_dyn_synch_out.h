
/***********************************************************************************/
/**                                                                               **/
/**   Project:      alp      (ALP DLL)                                            **/
/**   Filename:     alp_ext_dyn_synch_out.h : Header-File for ALP extensions      **/
/**                                                                               **/
/***********************************************************************************/
/**                                                                               **/
/**   � 2023 ViALUX GmbH. All rights reserved.                                    **/
/**                                                                               **/
/***********************************************************************************/
/**                                                                               **/
/**     DYN_SYNCH_OUT: This extension generates an adjusted version of            **/
/**     ALP Synch Out pulses. The standard frame synch out pin of V-Modules       **/
/**     sends a pulse out for each displayed frame.                               **/
/**     The DYN_SYNCH_OUT pin pulses once over a number of frames (period).       **/
/**     The pulse width is configurable by means of frames.                       **/
/**                                                                               **/
/***********************************************************************************/
/**                                                                               **/
/**   Version:        1                                                           **/
/**                                                                               **/
/***********************************************************************************/



#ifndef _ALP_EXT_DYN_SYNCH_OUT__INCLUDED
#define _ALP_EXT_DYN_SYNCH_OUT__INCLUDED


/* /////////////////////////////////////////////////////////////////////////// */
/*  AlpDevControl - ControlTypes & ControlValues */

#define ALP_DEV_GPIO5_PIN_MUX                2062L
#define ALP_GPIO_STATIC_LOW						0
#define ALP_GPIO_STATIC_HIGH					1
#define ALP_GPIO_DYN_SYNCH_OUT_ACTIVE_LOW		16 // see also ALP_SEQ_DYN_SYNCH_OUT_PERIOD
#define ALP_GPIO_DYN_SYNCH_OUT_ACTIVE_HIGH		17 // see also ALP_SEQ_DYN_SYNCH_OUT_PERIOD

/* /////////////////////////////////////////////////////////////////////////// */
/*  AlpSeqControl - ControlTypes & ControlValues */

#define ALP_SEQ_DYN_SYNCH_OUT_PERIOD         2150L
#define ALP_SEQ_DYN_SYNCH_OUT_PULSEWIDTH     2151L

#endif /* _ALP_EXT_DYN_SYNCH_OUT__INCLUDED */
