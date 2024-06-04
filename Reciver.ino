#include <VirtualWire.h>

#define LED1_PIN 7
#define LED2_PIN 13
#define BUZZER_PIN 2
#define SWITCH_PIN 8

const int COUNTDOWN_TIME = 5; 
const int BUZZER_FREQUENCY = 1000; // Buzzer frekansı (Hz)

char message[VW_MAX_MESSAGE_LEN]; // Mesaj için tampon

void setup() 
{
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, OUTPUT);

  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(11); 
  vw_setup(5000);
  vw_rx_start();

  // Başlangıç durumu
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(SWITCH_PIN, HIGH);
} 

void loop() 
{ 
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) 
  {
    // Mesajın geçerliliğini kontrol et
    if (buflen > 0 && buflen < VW_MAX_MESSAGE_LEN) 
    {
      // Gelen mesajı tampon dizisine kopyala
      memcpy(message, buf, buflen);
      message[buflen] = '\0'; // Mesajın sonuna null karakter ekle

      Serial.println(message); // Mesajı seri porta yazdır

      // Mesaj içeriğine göre işlem yap
      if (message[0] == '0') 
      {
        noTone(BUZZER_PIN);
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(SWITCH_PIN, HIGH);
      } 
      else if (message[0] == '1')
      {
        // Geri sayım süresi boyunca buzzer çal
        for (int i = COUNTDOWN_TIME; i > 0; i--) 
        {
          tone(BUZZER_PIN, BUZZER_FREQUENCY); 
          delay(500);             
          noTone(BUZZER_PIN);
          delay(500);            
        }

        // Buzzer uyarı süresi
        for (int i = 0; i < 10; i++) 
        {
          tone(BUZZER_PIN, BUZZER_FREQUENCY);  
          delay(200 - i * 15);   
          noTone(BUZZER_PIN);
          delay(200 - i * 15); 
        }

        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(SWITCH_PIN, LOW);
        delay(2000);
      }
    }
  }
}
