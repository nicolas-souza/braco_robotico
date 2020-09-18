#define botao_pullup 8
#define botao_pulldown 2
#define led_pullup 13
#define led_pulldown 7

void setup()
{
	pinMode(botao_pullup, INPUT);
  	pinMode(botao_pulldown, INPUT);
  	pinMode(led_pullup, OUTPUT);
  	pinMode(led_pulldown, OUTPUT);
}

void loop()
{
  digitalWrite(led_pullup, digitalRead(botao_pullup));
  digitalWrite(led_pulldown, digitalRead(botao_pulldown));
  
}