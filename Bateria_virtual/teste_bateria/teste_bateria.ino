int botao_cima = 2, botao_baixo = 3, botao_direita = 4, botao_esquerda = 5;
int cima = 0, baixo = 0, direita = 0, esquerda = 0;
int flag_cima = 1,flag_baixo = 1,flag_direita = 1,flag_esquerda = 1;
int led = 13;
int led_flag;

void setup() {
  Serial.begin(9600);
  pinMode(botao_cima, INPUT);
  pinMode(botao_baixo, INPUT);
  pinMode(botao_direita, INPUT); 
  pinMode(botao_esquerda, INPUT);
  pinMode(led, OUTPUT);
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
  if(direita == HIGH && flag_direita == 0){
    Serial.write("1\n");
    flag_direita = 1;
  }
    if(esquerda == HIGH && flag_esquerda == 0){
    Serial.write("2\n");
    flag_esquerda = 1;
  }
    if(cima == HIGH && flag_cima == 0){
    Serial.write("3\n");
    flag_cima = 1;
  }
    if(baixo == HIGH && flag_baixo == 0){
    Serial.write("4\n");
    flag_baixo = 1;
  }
  
}

void lerBotao(void){
  cima = digitalRead(botao_cima);
  baixo = digitalRead(botao_baixo);
  direita = digitalRead(botao_direita);
  esquerda = digitalRead(botao_esquerda);
  delay(10);
}

void funcFlag(void){
  if (cima == LOW && flag_cima == 1){ 
    flag_cima = 0;
  }                   
  if (baixo == LOW && flag_baixo == 1){ 
    flag_baixo = 0;
  }
  if (direita == LOW && flag_direita == 1){ 
    flag_direita = 0;
  }
  if (esquerda == LOW && flag_esquerda == 1){ 
    flag_esquerda = 0;
  }
}


