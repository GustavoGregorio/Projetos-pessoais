int analogpin[6]={A0,A1,A2,A3,A4,A5};
int estado[6]={0,0,0,0,0,0};
int flag_0 = 1 ,flag_1 = 1, flag_2 = 1, flag_3 = 1, flag_4 = 1, flag_5 = 1;
int led = 13;
int led_flag;
int threshold = 70;
int tempo = 0;
int tempo1 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
 // for(int i = 0; i < 7; i++){
  //  pinMode(analogpin[i], INPUT); 
//  }
  
  digitalWrite(led, LOW); 
}


void loop() {
  lerBotao();
  funcFlag();
 
  if(Serial.available()){
  led_flag = Serial.read();
    if(led_flag == 'a')
    digitalWrite(led, HIGH);
    if(led_flag == 'b')
    digitalWrite(led, LOW);
  }
       
  /*Manda mensagem na serial ao apertar o botao*/
  if(estado[0] > threshold && flag_0 == 0 && (millis() - tempo) > 50){
    Serial.write("1\n");
    estado[0] = 0;
    flag_0 = 1;
  }

    if(estado[1] > 50 && flag_1 == 0 && (millis() - tempo) > 50){
    Serial.write("2\n");
    estado[1] = 0;
    flag_1 = 1;
  }
    /*
    if(estado_2 > threshold && flag_2 == 0){
    Serial.write("3\n");
    flag_2 = 1;
  }
    if(estado_3 > threshold && flag_3 == 0){
    Serial.write("4\n");
    flag_3 = 1;
  }
  */
}

void lerBotao(void){
  for(int i = 0; i < 6; i++){
    estado[i] = analogRead(analogpin[i]); 
  }
  delay(10);
}

void funcFlag(void){
  if (estado[0] == 0 && flag_0 == 1){ 
    tempo = millis();
    flag_0 = 0;
  }    

  if (estado[1] == 0  && flag_1 == 1){ 
    tempo1 = millis();
    flag_1 = 0;
  }
  /*
  if (estado_2 < threshold  && flag_2 == 1){ 
    flag_2 = 0;
  }
  if (estado_3 < threshold  && flag_3 == 1){ 
    flag_3 = 0;
  }
  */
}
