//This code explains how to use pointers to read register values of AVR Microcontroller
//Boared used :Arduino Nano
//MCU: ATMEGA328P
//Compiler Arduino IDE

uint8_t k;

void setup() 
{
  DDRB |= 0xFF;
  Serial.begin(9600);
}

void loop() 
{ 
  PORTB ^= 0x10;                     //Decimal 16 or 0
  k = (*(volatile uint8_t*)(0x23));  //Reading the PIN Register Value
  k &= 0x10;                         //Eliminating all except PB5
  
  Serial.println(k);                  
  delay(1000);
}
