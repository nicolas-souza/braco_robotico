/*=====================================================================*/

/*Nicolas de Souza - Bacharelando em Engenharia de Controle e Automação*/

/*=====================================================================*/

#include <Servo.h>

//valores de funcionamento de um servo
#define MAX 180
#define MIN 0

//SERVOS
#define pin_servo_base 2
#define pin_servo_amplitude 3
#define pin_servo_garra_base 4
#define pin_servo_garra 5

//JOYSTICK
#define pin_base A0 
#define pin_amplitude  A1 

//BOTÕES
#define subir_garra_base 10 //botão azul
#define descer_garra_base 9 //botão amarelo
#define garra 8 //botão vermelho

//Instanciando objetos
Servo servo_base, servo_amplitude, servo_base_garra, servo_garra;

//Valores para controlar o braço
int valor_base = 0; 
int valor_amplitude = 0;
int valor_base_garra = 0;
bool valor_garra = HIGH;
int bot_garra = 0;

void setup(){

  pinMode(subir_garra_base,INPUT_PULLUP);
  pinMode(descer_garra_base,INPUT_PULLUP);
  pinMode(garra,INPUT_PULLUP);

  servo_base.attach(pin_servo_base);
  servo_amplitude.attach(pin_servo_amplitude); 
  servo_base_garra.attach(pin_servo_garra_base); 
  servo_garra.attach(pin_servo_garra); 

  /*

  Retire o comentário para definir uma posição inicial
  servo_amplitude.write(180);
  servo_base.write(90);
  servo_garra.write(90);

  */
  
}

int controle (int verificar, int max_pos, int min_pos){
  if (verificar > max_pos ){
    return max_pos;
  }else if ( verificar < min_pos){
    return min_pos;
  }
  return verificar;
}

void loop(){
    
  //Leituras do Joystick    
    if((analogRead(pin_amplitude)) < 200){ 
      Serial.println("PRA CIMA");
      valor_amplitude -= 10;

    }else if((analogRead(pin_amplitude)) > 600){ 
      Serial.println("PRA BAIXO");
      valor_amplitude += 10; 

    }else if((analogRead(pin_base)) < 200){ 
      Serial.println("ESQUERDA");
      valor_base += 10; 

    }else if((analogRead(pin_base)) > 600){ 
      Serial.println("DIREITA");
      valor_base -= 10; 

    }

  //Leitura dos Botões 
    //Controle Garra
    bot_garra = 0; 
    while(!digitalRead(garra)){ 
      bot_garra = 1; 
      delay(10);   
    }
    //Controle Base da Garra 
    if (!digitalRead(descer_garra_base)){
      valor_base_garra -= 5;

    }else if (!digitalRead(subir_garra_base)){
      valor_base_garra += 5;
    
    }

  //Controle dos valores para manter dentro do intervalo
    valor_amplitude = controle(valor_amplitude, 180,70);
    valor_base = controle(valor_base, MAX, MIN);
    valor_base_garra = controle(valor_base_garra, MAX, MIN);

  //Atualização dos servos  
    servo_amplitude.write(valor_amplitude);
    servo_base_garra.write(valor_base_garra);
    servo_base.write(valor_base);

    if (bot_garra){
      valor_garra = !valor_garra;
    }
    if (valor_garra){
      servo_garra.write(50);
    } else {
      servo_garra.write(90);
    }

    delay(50); 
}