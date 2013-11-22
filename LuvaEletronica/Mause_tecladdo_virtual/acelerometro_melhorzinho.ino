  int xValue, yValue, zValue;
  int led = 13;
  int led_flag;
  int flag = 0;
void setup() {
 Serial.begin(9600);
 pinMode(led, OUTPUT);
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
 
void loop() {
    led_flag = Serial.read();
    if(led_flag == 'a' || flag == 1){
    digitalWrite(led, HIGH);
    xValue = analogRead(A5); 
    yValue = analogRead(A4);
    xValue = map(xValue, 150, 480, 0, 1400);
    yValue = map(yValue, 170, 450, 0, 750);
    String X = ArrumandoZeroX(xValue);
    String Y = ArrumandoZeroY(yValue);
    Serial.print(X);
    Serial.println(Y);
    flag = 1;
    delay(20);
    }
      if(led_flag == 'b'){
          digitalWrite(led, LOW); 
          flag = 0;
    }
}

