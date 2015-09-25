//************************************************************************************************************
// FILE: tpm.c
//
// DESCRIPTION
//
// AUTHOR
// Sean E Slamka (sslamka@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
// Web: http://www.devlang.com
//************************************************************************************************************

#include "tpm.h"




//Configures one of the TPM timers to implement a busy delay loop
//that continuously polls TPM_SC[TOF] to delay for
//exactly p_delay_us microseconds, where 1 <= p_delay_us <= 1000.
void tpm_busy_delay_us(uint32_t p_delay_us)
{ 	
	// Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
	SIM_SOPT2 |= 0b00000011000000000000000000000000;
	// Initialize TPM0_SC to: clear TOF (in case it was set); to disable the TPM counter; and to divide
	//MCGIRCLK by 2.
	TPM_SC(0) = 0b00000001;
	// Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
	TPM_CNT(0) &= 0;
	// Write p_delay_us - 1 to TPM0_MOD[MOD].
	TPM_MOD(0) &= (p_delay_us - 1);
	// Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; to clear CSOT
	// which will cause the counter to begin counting immediately after it is enabled.
	TPM_CONF(0) = 0;
	// At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
	while (~TPM_SC(0) & TPM_SC_TOF_MASK) 
	//{
	//}
	// Write to TPM0_SC[TOF] to clear the timer overflow flag.
	TPM_SC(0) |= 1 << 7;
	//p_delay_us += p_delay_us;
}



void tpm_busy_delay_ms(uint32_t p_delay_ms)
{
	// Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
	SIM_SOPT2 |= 0x03000000;
	// Initialize TPM0_SC to: clear TOF (in case it was set); to disable the TPM counter; and to divide
	// MCGIRCLK by 2.
	TPM0_SC = 0b10000001;
	// Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
	TPM0_CNT = 0x0;
	// Write 999 to TPM0_MOD[MOD] to cause TOF to be set after 1000 us have elapsed.
	TPM0_MOD = 999;
	// Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; to clear CSOT
	// which will cause the counter to begin counting immediately after it is enabled.
	TPM0_CONF = 0x0;
	for(int i = 0; p_delay_ms; i++)
	{
	// At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
	while (~TPM0_SC & TPM_SC_TOF_MASK) {}
	// Write to TPM0_SC[TOF] to clear the timer overflow flag
	TPM0_SC |= (1 << 7);
	}

	uint32_t x = 2;
	p_delay_ms = x + p_delay_ms;
}
