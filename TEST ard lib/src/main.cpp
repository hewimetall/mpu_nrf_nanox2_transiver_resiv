#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <avr/interrupt.h>

void SPI_MasterInit(void)
{
        /* Set MOSI and SCK output, all others input */
        DDRB = (1<<DDB5)|(1<<DD_SCK);
        /* Enable SPI, Master, set clock rate fck/16 */
        SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
        /* Start transmission */
        SPDR = cData;
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)));
}
int main( void )
{
        DDRB |= (1<<PB5);     // устанавливаем вывод PB5 как выход
        while(1) {
                PORTB &= ~(1<<PB5); // устанавливаем низкий уровень на выводе PB5
                _delay_ms(10); // ждем 1000 миллисекунд
                PORTB |= (1<<PB5); // устанавливаем высокий уровень на выводе PB5
                _delay_ms(100); // снова ждем 1000 миллисекунд
        }

        return 0;
}
