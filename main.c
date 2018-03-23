#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


void PortyInit()
{
    DDRA &= ~(1<<DDA0); // wejscie ADC0; 
	
	DDRD |= 1<<DDD0;
	DDRD |= 1<<DDD1;
	DDRD |= 1<<DDD2;
	DDRD |= 1<<DDD3;
	DDRD |= 1<<DDD4;
	DDRD |= 1<<DDD5;
	DDRD |= 1<<DDD6;        // 1111 1111 ; wyprowadzenia portu D jako wyjscie dla diod led od PD0 do PD8, osiem diod
	DDRD |= 1<<DDD7;
	
    DDRC |= (1<<PORTC0);  //wyjscie buzzera
}

void ADC_Init()
{

	
		ADCSRA |= (1<<ADEN); // wlaczenie adc
		ADCSRA |= (1<<ADPS2);
		ADCSRA |= (1<<ADPS1);
		ADCSRA |= (1<<ADPS0);  // preskaler dzielacy czestotliwosc przez 128
			
		ADMUX |= (1<<REFS1);
		ADMUX |= (1<<REFS0);  //pomiar wzgledem AVCC
		ADMUX |= (1<<ADLAR);  //8 bit 
	
}

unsigned int ADC_Odczyt()
{
	ADCSRA |= (1<<ADSC);            // pojedyncza konwersja
	while(ADCSRA & (1<<ADSC));      //czeka na zakoñczenie konwersji-czekamy az na bicie ADSC pojawi sie '0'
	
	return ADCH; //rejestrgdzie jeste wartosc z naszego przetwornika; 
}
int main(void)
{
	PortyInit();
	
	ADC_Init();
					 
    while(1)
    {
       int value_adc =  ADC_Odczyt();					//wartosc z przetwornika adch bo 8 bit ustawilismy
	   int temp =  (value_adc * 0.01 * 1000 ) / 10;  
	    //10 mV = 1c z dokumentacji lm35
		//2.56V/255=0.01V wartoœæ*0.01=.. V 
		
	    if( temp > 30)   // jeœli temperatura jest powy¿ej 30 stopni ustawiamy PC0 w stan wysoki- czyli w³¹czenie siê buzzera w przeciwnym razie PC0 stan niski
	   PORTC |= (1<<PORTC0); 
	   else  
	   PORTC &= ~(1<<PORTC0);
		 
		
		 
		if( temp > 0 && temp <=6)
		{
			PORTD |= 1<<PORTD0;  // zapalenie pierwszej diody (PD0) stan wysoki
			PORTD &= ~(1<<PORTD1);
			PORTD &= ~(1<<PORTD2);
			PORTD &= ~(1<<PORTD3);
			PORTD &= ~(1<<PORTD4);
			PORTD &= ~(1<<PORTD5);
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 6 && temp <=12)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1; // 2 diody
			PORTD &= ~(1<<PORTD2);
			PORTD &= ~(1<<PORTD3);
			PORTD &= ~(1<<PORTD4);
			PORTD &= ~(1<<PORTD5);
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 12 && temp <=18)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2; // 3 diody
			PORTD &= ~(1<<PORTD3);
			PORTD &= ~(1<<PORTD4);
			PORTD &= ~(1<<PORTD5);
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 18 && temp <=24)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3; // 4 diody
			PORTD &= ~(1<<PORTD4);
			PORTD &= ~(1<<PORTD5);
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 24 && temp <=30)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3 | 1<<PORTD4; //5 diod
			PORTD &= ~(1<<PORTD5);
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 30 && temp <=36)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3 | 1<<PORTD4 | 1<<PORTD5; //6 diod
			PORTD &= ~(1<<PORTD6);
			PORTD &= ~(1<<PORTD7);
		}
		else if( temp > 36 && temp <=42)
		{
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3 | 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD6; //7 diod
			PORTD &= ~(1<<PORTD7);
		}
		else
			PORTD |= 1<<PORTD0 | 1<<PORTD1 | 1<<PORTD2 | 1<<PORTD3 | 1<<PORTD4 | 1<<PORTD5 | 1<<PORTD6 | 1<<PORTD7;	 //8 diod
								
    }
}
