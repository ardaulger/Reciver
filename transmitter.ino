#include <VirtualWire.h>
#define buton 3 
char *message;
int butonDeger;

void setup()
{
Serial.begin(9600);
pinMode(buton, INPUT);
vw_set_ptt_inverted(true);
vw_set_tx_pin(12);
vw_setup(5000); 
}
void loop()
{ 
butonDeger = digitalRead(buton);
if (butonDeger == HIGH)
{ 
  message = "1" ;
}   
else 
{
  message = "0" ;
} 
Serial.println(message);
vw_send((uint8_t *)message, strlen(message));
message = "0" ;
vw_wait_tx();
delay(100);


}