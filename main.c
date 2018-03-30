#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MIN 50
#define MAX 200
#define MIDDLE (uint8_t) (MIN + MAX)/2

#define MOTOR PB0

volatile unsigned int TICK;	// 100KHz pulse
uint8_t PULSE;	// Servo pulse variable


void goToSleep(void)
{
    cli();
    sleep_enable(); 
    GIMSK |= (1 << INT0);
    sei();
    PORTB &= ~(1 << PB3);
    sleep_mode(); // Put the device to sleep
    PORTB |= (1 << PB3);
}

ISR(INT0_vect)
{
	sleep_disable();
	GIMSK &= ~(1 << INT0);
}

ISR(TIM0_COMPA_vect)	// 100 KHz interrupt frequency
{
	if(TICK >= 2000)	// One servo frame (20ms) completed
	{
		TICK = 0;
	}

	TICK = TICK + 1;
	if(TICK <= PULSE)	// Generate servo pulse
	{
		PORTB |= (1 << MOTOR);	// Servo pulse high
	}
	
	else
	{
		PORTB &= ~(1 << MOTOR);	// Servo pulse low
	}	
} 


void SystemInit(void)
{
	TICK = 0;
	
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB1);
	
	GIMSK |= (1 << INT0);
	
	TCCR0A |= (1 << WGM01); // Configure timer 1 for CTC mode
	TIMSK0 |= (1 << OCIE0A); // Enable CTC interrupt
	OCR0A = 95; // Set CTC compare value
	TCCR0B |= (1 << CS00); // No prescaler
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	sei();
}

int main (void)
{
	SystemInit();

	DDRB |= (1 << PB3);
	
	uint8_t n_mins, i;

	while(1)
	{
		goToSleep();
		
		n_mins = 0;
		
		while(n_mins < 100)
		{
			for(i = 0; i < 5; i++)
			{
				while(~PINB & (1 << PB1))
				{
					PULSE = MAX;
					_delay_ms(10);
					n_mins = 0;
				}
			}
			
			PULSE = MIN;
			
			n_mins += 1;
			_delay_ms(10);
		}
	}
	
	return 1;
}
