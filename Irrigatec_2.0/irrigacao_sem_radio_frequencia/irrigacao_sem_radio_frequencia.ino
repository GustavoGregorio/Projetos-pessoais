#include <Wire.h>
#include "RTClib.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>

RTC_DS1307 RTC;
unsigned int j;
unsigned int h;
int sensor_de_umidade = A0;
int sinal_digital_umidade = 0;
int saida = 2;
int valor_umidade=256; // Umidade
  // Definição dos pinos dos botões, luz do display e buzzer
#define bRetorna    4  // Os pinos analógicos podem ser
#define bEnter      5  // usados como digitais, bastando
#define bUp         7  
#define bDown       6

#define bRetorna0   90  // Valor de referência que a 
#define bEnter0     91  // função CheckButton() passa
#define bUp0        92  // indicando que um botão foi
#define bDown0      93  // solto

int hora_inicial = EEPROM.read(0);
int minuto_inicial = EEPROM.read(1);
int hora_final = EEPROM.read(2);
int minuto_final = EEPROM.read(3);

boolean aRetorna, aEnter, aUp, aDown;  // Grava o ultimo valor lidos nos botões.
// Utilizado pela função Checkbutton p/ identificar quando há uma alteração no estado do pino dos botões
char state=1;  // variável que guarda posição atual do menu
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  // Declaração do objeto tipo lcd
byte seta1[8] =      {0b00000,0b00000,0b00000,0b11111,0b11111,0b00000,0b00000,0b00000};//seta
byte seta2[8] =     {0b01000,0b00100,0b00010,0b11111,0b11111,0b00010,0b00100,0b01000};
byte cecidilha[8] = {0b1110, 0b10001, 0b10000, 0b10000, 0b10001, 0b1110, 0b100, 0b1000};//Ç
byte til[8] =       {0b1110, 0b0, 0b1110, 0b10001, 0b11111, 0b10001, 0b10001, 0b0};//~
    


 String ArrumandoZero(int i)
 {
   String ret;
   if (i < 10) ret += "0";
   ret += i;
   return ret;
 }

//============================================== SETUP
void setup()
{
  lcd.createChar(1, seta1);
  lcd.createChar(2, seta2);
  lcd.createChar(3, cecidilha);
  lcd.createChar(4, til);

  
  lcd.begin(20, 4);  // Iniciando a biblioteca do LCD
  Wire.begin();
  RTC.begin();
  
  h = 0;
  hora_inicial = hora_inicial;
  minuto_inicial = minuto_inicial; 
  hora_final = hora_final;
  minuto_final = minuto_final;
  
  pinMode(bRetorna,  INPUT);   // Botões
  pinMode(bEnter,INPUT);
  pinMode(bUp,    INPUT);
  pinMode(bDown,  INPUT);
  pinMode(saida, OUTPUT);
  
  digitalWrite(bRetorna,  LOW);  // Aciona o pull-up interno
  digitalWrite(bEnter, LOW);  // dos botões
  digitalWrite(bUp,    LOW);
  digitalWrite(bDown,  LOW);
  
    if (! RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}


void relogio(){
    DateTime now = RTC.now();
    String relogio_data;
    String relogio_hora;
    int dia = now.day();
    int mes = now.month();
    int ano = now.year();
    int hora = now.hour();
    int minuto = now.minute();
    int segundo = now.second();
  relogio_data += ArrumandoZero(dia);
  relogio_data += "/";
  relogio_data += ArrumandoZero(mes);
  relogio_data += "/";
  relogio_data += ano;
  relogio_hora += ArrumandoZero(hora);
  relogio_hora += ":";
  relogio_hora += ArrumandoZero(minuto);
  relogio_hora += ":";
  relogio_hora += ArrumandoZero(segundo);
    lcd.setCursor(0, 0);
    lcd.print("DATA:");
    lcd.setCursor(0, 1);
    lcd.print(relogio_data);
    lcd.setCursor(0, 2);
    lcd.print("HORA:");
    lcd.setCursor(0, 3);
    lcd.print(relogio_hora);
    lcd.print("  ");
}

void irrigacao_noturna(){
    DateTime now = RTC.now();
    String relogio_hora = "HORA ATUAL: ";
    int hora = now.hour();
    int minuto = now.minute();
    int segundo = now.second();  
    relogio_hora += ArrumandoZero(hora);
    relogio_hora += ":";
    relogio_hora += ArrumandoZero(minuto);
    relogio_hora += ":";
    relogio_hora += ArrumandoZero(segundo);
    sinal_digital_umidade = analogRead(sensor_de_umidade);
    char *msg;
   if((hora>=21 || hora<=6) && sinal_digital_umidade <= valor_umidade ){
    lcd.setCursor(0, 0);
    lcd.print("IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
    lcd.setCursor(0, 1);
    lcd.print(relogio_hora);
    lcd.setCursor(0, 2);
    lcd.print("--------------------");
    lcd.setCursor(0, 3);
    lcd.print("SITUA"); lcd.write(3); lcd.write(4); lcd.print("O: ");
    lcd.print("LIGADA    ");
    

   }
  else{
    lcd.setCursor(0, 0);
    lcd.print("IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
    lcd.setCursor(0, 1);
    lcd.print(relogio_hora);
    lcd.setCursor(0, 2);
    lcd.print("--------------------");
    lcd.setCursor(0, 3);
    lcd.print("SITUA"); lcd.write(3); lcd.write(4); lcd.print("O: ");
    lcd.print("DESLIGADA ");

   }  
}

void irrigacao_determinada_pelo_usuario(){
    DateTime now = RTC.now();
    String relogio_hora = "HORA ATUAL: ";
    int hora = now.hour();
    int minuto = now.minute();
    int segundo = now.second();  
    relogio_hora += ArrumandoZero(hora);
    relogio_hora += ":";
    relogio_hora += ArrumandoZero(minuto);
    relogio_hora += ":";
    relogio_hora += ArrumandoZero(segundo);
   sinal_digital_umidade = analogRead(sensor_de_umidade);
if(hora_inicial == hora && minuto_inicial == minuto){ 
h = 1;
}


if(h == 1 && sinal_digital_umidade <= valor_umidade){
    lcd.setCursor(0, 0);
    lcd.print(relogio_hora);
    lcd.setCursor(0, 1);
    lcd.print("INICIO:  ");
    lcd.print(ArrumandoZero(hora_inicial));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_inicial));
    lcd.setCursor(0, 2);
    lcd.print("FINAL:   ");
    lcd.print(ArrumandoZero(hora_final));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_final));
    lcd.setCursor(0, 3);
    lcd.print("SITUA"); lcd.write(3); lcd.write(4); lcd.print("O: ");
    lcd.print("LIGADA    ");
    digitalWrite(saida, HIGH);

}

else{
    lcd.setCursor(0, 0);
    lcd.print(relogio_hora);
    lcd.setCursor(0, 1);
    lcd.print("INICIO:  ");
    lcd.print(ArrumandoZero(hora_inicial));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_inicial));
    lcd.setCursor(0, 2);
    lcd.print("FINAL:   ");
    lcd.print(ArrumandoZero(hora_final));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_final));
    lcd.setCursor(0, 3);
    lcd.print("SITUA"); lcd.write(3); lcd.write(4); lcd.print("O: ");
    lcd.print("DESLIGADA");
    digitalWrite(saida, LOW);
}
  
  if(hora_final == hora && minuto_final == minuto){
    lcd.setCursor(0, 0);
    lcd.print(relogio_hora);
    lcd.setCursor(0, 1);
    lcd.print("INICIO:  ");
    lcd.print(ArrumandoZero(hora_inicial));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_inicial));
    lcd.setCursor(0, 2);
    lcd.print("FINAL:   ");
    lcd.print(ArrumandoZero(hora_final));
    lcd.print(":");
    lcd.print(ArrumandoZero(minuto_final));
    lcd.setCursor(0, 3);
    lcd.print("SITUA"); lcd.write(3); lcd.write(4); lcd.print("O: ");
    lcd.print("DESLIGADA");
     h = 0;
    digitalWrite(saida, LOW);
   
    }
}



//==============================================
//============================================== LOOP
void loop()
{
  switch (state) {  // Define checa qual tela atual
    
    case 1:          // executado quando na TELA 1
      switch (CheckButton()) {
        case bEnter:
           lcd.clear(); 
           for(j=0;j<18000;j++){
             Set_state(8);       
                switch (CheckButton()) {
                  case bRetorna:
                  j = 18000;
                  break;
                }
         delay(50);
        }
        lcd.clear(); Set_state(1);
      break;
        case bUp:
          Set_state(4);
          // antes de mudar de tela, é necessário limpar o 
        break;                       // display com a função lcd.clear()
        case bDown:
          Set_state(2);
        break;
        default:   // Caso nenhum botão tenha sido apertado, ela executa a set_state
          Set_state(1); // mesmo assim para atualizar o display.
      }
    break;
    
    case 2:          // executado quando na TELA 2
      switch (CheckButton()) {
        case bEnter:
          lcd.clear(); Set_state(9);
        break;
        case bUp:
          Set_state(1);
        break;
        case bDown:
          Set_state(3);
        break;
        default: 
          Set_state(2);
      }
    break;
    
    case 3:          // executado quando na TELA 3
      switch (CheckButton()) {
        case bEnter:
        lcd.clear(); Set_state(5);
        break;
        case bUp:
          Set_state(2);
        break;
        case bDown:
          Set_state(4);
        break;
        default: 
          Set_state(3);
      }
    break;
    
    case 4:          // executado quando na TELA 4
      switch (CheckButton()) {
        case bRetorna:
        break;
        case bEnter:
        break;
        case bUp: 
           Set_state(3);
        break;
        case bDown:
           Set_state(1);
        break;
        default: 
          Set_state(4);
      } 
      break;
       case 5:          // selecionando irrigação noturna (SIM)
      switch (CheckButton()) {
        case bRetorna:
        lcd.clear(); Set_state(3);
        break;
        case bEnter:
        lcd.clear(); Set_state(7);
        break;
        case bUp: 
        break;
        case bDown:
          lcd.clear(); Set_state(6);
        break;
        default: 
          Set_state(5);
      }
  break;
         case 6:          // selecionando irrigação noturna (NÃO)
      switch (CheckButton()) {
        case bRetorna:
         lcd.clear(); Set_state(3);
        break;
        case bEnter:
         lcd.clear(); Set_state(3);
        break;
        case bUp: 
          lcd.clear(); Set_state(5);
        break;
        case bDown:
          
        break;
        default: 
          Set_state(6);
      }
  break;
           case 7:          // SETANDO HORARIO PARA IRRIGAÇÃO NOTURNA
      switch (CheckButton()) {
        case bRetorna:
        lcd.clear(); Set_state(3);
        digitalWrite(saida, LOW);
        break;
        case bEnter:
        break;
        case bUp: 
        break;
        case bDown:
        break;
        default: 
          Set_state(7);
      }
  break;
       case 9:          // SETANDO DE  HORARIO DE INICIO DA IRRIGAÇÃO
      switch (CheckButton()) {
        case bRetorna:
         lcd.clear(); Set_state(2);
        break;
        case bUp:
        hora_inicial++;
        if(hora_inicial == 24){
          hora_inicial = 0;
        }
        break;
        case bDown:
        hora_inicial--;
        if(hora_inicial == -1){
        hora_inicial = 23;
        }
        break;
        case bEnter:
        EEPROM.write(0, hora_inicial);
        Set_state(10);
        break;
        default: 
          Set_state(9);
      }
  break;
  
     case 10:          // SETANDO DE  MINUTO DE INICIO DA IRRIGAÇÃO
      switch (CheckButton()) {
        case bRetorna:
        Set_state(9);
        break;
        case bUp:
        minuto_inicial++;
        if(minuto_inicial == 60){
          minuto_inicial = 0;
        }
        break;
        case bDown:
        minuto_inicial--;
        if(minuto_inicial == -1){
        minuto_inicial = 59;
        }
        break;
        case bEnter:
        EEPROM.write(1, minuto_inicial);
        lcd.clear(); Set_state(11);
        break;
        default: 
          Set_state(10);
      }
  break;
   case 11:          // SETANDO DE  HORARIO DE FIM DA IRRIGAÇÃO
      switch (CheckButton()) {
        case bRetorna:
         lcd.clear(); Set_state(10);
        break;
        case bUp:
        hora_final++;
        if(hora_final == 24){
          hora_final = 0;
        }
        break;
        case bDown:
        hora_final--;
        if(hora_final == -1){
        hora_final = 23;
        }
        break;
        case bEnter:
        EEPROM.write(2, hora_final);
        Set_state(12);
        break;
        default: 
          Set_state(11);
      }
  break;
     case 12:          // SETANDO DE  MINUTO DE FIM DA IRRIGAÇÃO
      switch (CheckButton()) {
        case bRetorna:
         Set_state(11);
        break;
        case bUp:
        minuto_final++;
        if(minuto_final == 60){
          minuto_final = 0;
        }
        break;
        case bDown:
        minuto_final--;
        if(minuto_final == -1){
        minuto_final = 59;
        }
        break;
        case bEnter:
        EEPROM.write(3, minuto_final);
        lcd.clear(); Set_state(13);
        break;
        default: 
          Set_state(12);
      }
  break;
       case 13:          
      switch (CheckButton()) {
        case bRetorna:
        lcd.clear(); Set_state(2);
        digitalWrite(saida, LOW);
        h = 0;
        break;
        case bUp:
        break;
        case bDown:
        break;
        case bEnter:
        break;
        default: 
          Set_state(13);
      }
  break;
    
    default: ;
  }
}
//============================================== FIM da função LOOP
//============================================== 

//============================================== CheckButton
char CheckButton() {
  if (aRetorna!=digitalRead(bRetorna)) {
    aRetorna=!aRetorna;
    if (aRetorna) return bRetorna0; else return bRetorna;
  } else
  if (aEnter!=digitalRead(bEnter)) {
    aEnter=!aEnter;
    if (aEnter) return bEnter0; else return bEnter;
  } else
  if (aUp!=digitalRead(bUp)) {
    aUp=!aUp;
    if (aUp) return bUp0; else return bUp;
  } else
  if (aDown!=digitalRead(bDown)) {
    aDown=!aDown;
    if (aDown) return bDown0; else return bDown;
  } else
    return 0;
}

//========================================================
//============================================== Set_state
void Set_state(char index) {
  state = index;  // Atualiza a variável state para a nova tela
    
  switch (state) {  // verifica qual a tela atual e exibe o conteúdo correspondente
    case 1: //==================== state 1
      lcd.setCursor(0,0);
      lcd.write(1);
      lcd.write(2);
      lcd.print("RELOGIO       ");
      lcd.setCursor(0,1);
      lcd.print("  SELEC HR DE IRRIG");
      lcd.setCursor(0,2);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
      lcd.setCursor(0,3);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O PERIODIC");
    break;
    
    case 2: //==================== state 2
    lcd.setCursor(0,0);
      lcd.print("  RELOGIO");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.write(2);
      lcd.print("SELEC HR DE IRRIG");
      lcd.setCursor(0,2);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
      lcd.setCursor(0,3);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O PERIODIC");
    break;
    
    case 3: //==================== state 3
      lcd.setCursor(0,0);
      lcd.print("  RELOGIO");
      lcd.setCursor(0,1);
      lcd.print("  SELEC HR DE IRRIG");
      lcd.setCursor(0,2);
      lcd.write(1);
      lcd.write(2);
      lcd.print("IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
      lcd.setCursor(0,3);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O PERIODIC");
    break;
    
    case 4: //==================== state 4
      lcd.setCursor(0,0);
      lcd.print("  RELOGIO");
      lcd.setCursor(0,1);
      lcd.print("  SELEC HR DE IRRIG");
      lcd.setCursor(0,2);
      lcd.print("  IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA");
      lcd.setCursor(0,3);
      lcd.write(1);
      lcd.write(2);
      lcd.print("IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O PERIODIC");
    break;

    case 5: //==================== state 5 IRRIGAÇAO NOTURNA "SIM"
      lcd.setCursor(0,0);
      lcd.print("  DESEJA INICIAR A ");
      lcd.setCursor(0,1);
      lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA ");
      lcd.setCursor(5,2);
      lcd.write(1);
      lcd.write(2);
      lcd.print("SIM");
      lcd.setCursor(7,3);
      lcd.print("NAO");
     break;
   
     case 6: //==================== state 5 IRRIGAÇAO NOTURNA "NÃO"
      lcd.setCursor(0,0);
      lcd.print("  DESEJA INICIAR A ");
      lcd.setCursor(0,1);
      lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4); lcd.print("O NOTURNA ");
      lcd.setCursor(7,2);
      lcd.print("SIM");
      lcd.setCursor(5,3);
      lcd.write(1);
      lcd.write(2);
      lcd.print("NAO");
     break;
   
     case 7: //==================== SETANDO HORARIO PARA IRRIGAÇÃO NOTURNA
        irrigacao_noturna();
     break; 
   
     case 8: //==================== TELA DO RELOGIO
         relogio();
     break;
  
    case 9: //==================== SETANDO HORARIO INICIAL PARA IRRIGAÇÃO (HORA)
      lcd.setCursor(0,0);
      lcd.print(" SELECINAR HORARIO");
      lcd.setCursor(0,1);
      lcd.print("INICIAL DA"); lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4);lcd.print("O");
      lcd.setCursor(0,2);
      lcd.print("INICIO: ");
      lcd.print("(");
      lcd.print(ArrumandoZero(hora_inicial));
      lcd.print(")");
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_inicial));
      lcd.setCursor(0,3);
      lcd.print("FINAL:");
      lcd.setCursor(8,3);
      lcd.print(ArrumandoZero(hora_final));
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_final));
    break;
  
    case 10: //==================== SETANDO HORARIO INICIAL PARA IRRIGAÇÃO (MINUTO)
      lcd.setCursor(0,0);
      lcd.print(" SELECINAR HORARIO");
      lcd.setCursor(0,1);
      lcd.print("INICIAL DA"); lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4);lcd.print("O");
      lcd.setCursor(0,2);
      lcd.print("INICIO: ");
      lcd.print(ArrumandoZero(hora_inicial));
      lcd.print(":");
      lcd.print("(");
      lcd.print(ArrumandoZero(minuto_inicial));
      lcd.print(")");
      lcd.setCursor(0,3);
      lcd.print("FINAL:");
      lcd.setCursor(8,3);
      lcd.print(ArrumandoZero(hora_final));
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_final));
  break;
  
   case 11: //==================== SETANDO HORARIO FINAL PARA IRRIGAÇÃO (HORA)
      lcd.setCursor(0,0);
      lcd.print(" SELECINAR HORARIO");
      lcd.setCursor(0,1);
      lcd.print(" FINAL DA"); lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4);lcd.print("O");
      lcd.setCursor(0,2);
      lcd.print("INICIO: ");
      lcd.print(ArrumandoZero(hora_inicial));
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_inicial));
      lcd.setCursor(0,3);
      lcd.print("FINAL:");
      lcd.setCursor(8,3);
      lcd.print("(");
      lcd.print(ArrumandoZero(hora_final));
      lcd.print(")");
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_final));
  break;
  
  case 12: //==================== SETANDO HORARIO FINAL PARA IRRIGAÇÃO (MINUTO)
      lcd.setCursor(0,0);
      lcd.print(" SELECINAR HORARIO");
      lcd.setCursor(0,1);
      lcd.print(" FINAL DA"); lcd.print(" IRRIGA"); lcd.write(3); lcd.write(4);lcd.print("O");
      lcd.setCursor(0,2);
      lcd.print("INICIO: ");
      lcd.print(ArrumandoZero(hora_inicial));
      lcd.print(":");
      lcd.print(ArrumandoZero(minuto_inicial));
      lcd.setCursor(0,3);
      lcd.print("FINAL:");
      lcd.setCursor(8,3);
      lcd.print(ArrumandoZero(hora_final));
      lcd.print(":");
      lcd.print("(");
      lcd.print(ArrumandoZero(minuto_final));
      lcd.print(")");
  break;
  
  case 13:
      irrigacao_determinada_pelo_usuario();
  break;
  }
}
