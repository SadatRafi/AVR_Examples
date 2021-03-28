//This code explains how to use pointers to write desired values in a specific address of AVR Microcontroller
//Boared used :Arduino Nano
//MCU: ATMEGA328P
//Compiler Arduino IDE

void setup() 
{
  (*(volatile uint8_t*)(0x24))|=(1<<5);
  //Writing 1 to bit 5 of DDRB (For Arduino Pin 13)
}

void loop() 
{ 
  (*(volatile uint8_t*)(0x25))^=(1<<5);
  //Writing 1 to bit 5 of PORTB (Arduino Pin 13)
  delay(500);
}
