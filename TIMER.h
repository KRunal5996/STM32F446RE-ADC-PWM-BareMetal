

#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIE	(1U<<0)
//void tim2_1hz_init(void);

void pa0pwm_tim2_init(void);
//void led_control(void);
void adc1_init(void);
uint32_t adc1_read1(void);
#endif /* TIMER_H_ */
