//************************************************************************************************************
// FILE: tpm.h
//
// DESCRIPTION
//
// AUTHOR
// Sean E Slamka (sslamka@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
// Web: http://www.devlang.com
//************************************************************************************************************

#ifndef TPM_H_
#define TPM_H_

#include "global.h" // Access to int data types and includes mkl46z.h
#define TPM_SC(x) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000))
#define TPM_CNT(x) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x04))
#define TPM_MOD(x) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x08))
#define TPM_CSC(x, n) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x0C + (n) * 0x08))
#define TPM_CV(x, n) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x10 + (n) * 0x08 + 0x04))
#define TPM_STATUS(x) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x50))
#define TPM_CONF(x) (*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x84))


void tpm_busy_delay_us(uint32_t p_delay_us);
void tpm_busy_delay_ms(uint32_t p_delay_ms);




#endif /* TPM_H_ */
