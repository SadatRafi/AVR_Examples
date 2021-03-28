//This code explains how to use pointers to write desired values in a specific address of AVR Microcontroller
//Boared used :Arduino Nano
//MCU: ATMEGA328P
//Compiler Arduino IDE

void setup() 
{
  (*(volatile uint8_t*)(0x24))|=(1<<5);
}

void loop() 
{ 
  (*(volatile uint8_t*)(0x25))^=(1<<5);
  delay(500);
}
