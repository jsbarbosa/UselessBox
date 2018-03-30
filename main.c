#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LEFT PB3
#define RIGHT PB4

void goToSleep(void)
{
	
    // Set sleep enable (SE) bit:
    sleep_enable();
 
    // Put the device to sleep:
    sleep_mode();
}

ISR(INT0_vect)
{
	sleep_disable();
	
	PORTB |= (1 << LEFT);
	
	_delay_ms(100);
}

void SystemInit(void)
{
	GIMSK |= (1 << INT0);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sei();
}

int main(void)
{
	uint8_t pos;
	
	DDRB |= (1 << LEFT) | (1 << RIGHT);
	PORTB |= (1 << PB1) | (1 << PB0); 
	
	SystemInit();

	while (1)
	{
		goToSleep();
		
		pos = 0;
		
		while (pos < 5)
		{
			if (PINB & (1 << PB1))
			{
				pos += 1;
			}
			_delay_ms(10);
		}
		
		PORTB &= ~(1 << LEFT);
		
		while (PINB & (1 << PB0))
		{
			PORTB |= (1 << RIGHT); 
		}
		PORTB &= ~(1 << RIGHT);
	}
	
	return 1;
}
