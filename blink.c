#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/sleep.h>

#define LED      PB1
#define LED_DDR  DDRB
#define LED_PORT PORTB

#define DELAYTIME 1000

#define setBit(sfr, bit)     (_SFR_BYTE(sfr) |= (1 << bit))
#define clearBit(sfr, bit)   (_SFR_BYTE(sfr) &= ~(1 << bit))
#define toggleBit(sfr, bit)  (_SFR_BYTE(sfr) ^= (1 << bit))

ISR(INT0_vect) {
    setBit(LED_PORT, LED);
    _delay_ms(DELAYTIME);
    clearBit(LED_PORT, LED);
    _delay_ms(DELAYTIME);
}

int main(void) {

    /* Input or output + pull ups */
    clearBit(DDRB, PB2);
    setBit(PORTB, PB2);

    /* Setting up registers */
    setBit(GIMSK, INT0);	// external interrupt enable
    clearBit(MCUCR, ISC00);
    clearBit(MCUCR, ISC01);
    //setBit(PCMSK, PCINT3);	// turn on interrupts on pins PB0, PB1, &amp; PB4


    sei();                 // enables interrupts

    setBit(LED_DDR, LED);                      /* set LED pin for output */
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_all_disable();

    // Mainloop
    while (1) {
	sleep_mode();
	/* setBit(LED_PORT, LED); */
	/* _delay_ms(DELAYTIME); */
	/* clearBit(LED_PORT, LED); */
	/* _delay_ms(DELAYTIME); */
    }
    return (0);                                          /* end mainloop */
}
