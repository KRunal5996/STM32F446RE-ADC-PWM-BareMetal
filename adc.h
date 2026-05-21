#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_

void pa1_adc_init(void);
uint32_t ADC_read(void);
void strt_converstion(void);
#endif /* ADC_H_ */
