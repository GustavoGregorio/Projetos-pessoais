int inputAccX[100],inputAccY[100];
long resultAccX, resultAccY,resultAccZ;
long xValue, yValue;
int led = 13;
int led_flag; 
int flag = 0;
int botao[8] = {12, 11, 10, 9, 8, 7, 6, 5};
int estado_botao[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
void setup() {
 Serial.begin(9600);
 pinMode(led, OUTPUT);
 for (int count = 0; count < 7; count++)
 {
   pinMode(botao[count], INPUT);
 }
 digitalWrite(led, LOW);
}

 String ArrumandoZeroX(int i)
 {
   String ret;
   if (i < 1000){ 
   ret += "0";
   }
   if (i < 100){
   ret += "0";
   }
   if (i < 10){
   ret += "0";
   }
   ret += i;
   return ret;
 }
 
  String ArrumandoZeroY(int i)
 {
   String ret;
   if (i < 100){ 
   ret += "0";
   }
   if (i < 10){ 
   ret += "0";
   } 
   ret += i;
   return ret;
 }
 
 int calibrateAccX()
{
  for(int i=0;i<100;i++)
  {
    inputAccX[i] = analogRead(A5);
  }
  for(int i=0;i<100;i++)
  {
    resultAccX += inputAccX[i];
  }
  resultAccX = resultAccX/100;
  return resultAccX;
}

int calibrateAccY()
{
  for(int i=0;i<100;i++)
  {
    inputAccY[i] = analogRead(A4);
  }
  for(int i=0;i<100;i++)
  {
    resultAccY += inputAccY[i];
  }
  resultAccY = resultAccY/100;
  return resultAccY;
}
 
int ler_botao(int botao)
{
   return digitalRead(botao);
}
void loop() {
    led_flag = Serial.read();
    if(led_flag == 'a' || flag == 1){
    digitalWrite(led, HIGH);
    xValue = calibrateAccX();
    if (xValue < 220)
      xValue = 220;
    if (xValue > 430)
      xValue = 430;
     yValue = calibrateAccY();
     if (yValue < 240)
      yValue = 240;
     if (yValue > 410)
      yValue = 410;
     xValue = map(xValue, 220, 430, 0, 1366);
     yValue = map(yValue, 240, 410, 0, 768);
     String X = ArrumandoZeroX(xValue);
     String Y = ArrumandoZeroY(yValue);
    Serial.print(X);
    Serial.print(Y);
    for(int count = 0; count < 3; count++)
    {
    estado_botao[count]= ler_botao(botao[count]);
    Serial.print(estado_botao[count]);
    }
   Serial.println(""); 
    flag = 1;
    delay(20);
    }
      if(led_flag == 'b'){
          digitalWrite(led, LOW); 
          flag = 0;
    }
}

