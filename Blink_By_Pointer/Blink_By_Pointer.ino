void setup() 
{
  (*(volatile uint8_t*)(0x24))|=(1<<5);
}

void loop() 
{ 
  (*(volatile uint8_t*)(0x25))^=(1<<5);
  delay(500);
}
