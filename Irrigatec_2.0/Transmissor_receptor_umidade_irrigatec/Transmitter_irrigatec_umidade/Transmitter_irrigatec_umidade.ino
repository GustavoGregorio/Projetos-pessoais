 
#include <VirtualWire.h>
int sensor_de_umidade = A5;
int sinal_digital_umidade = 0;
int valor_umidade = 256;
int saida = 9;

void setup()
{
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000);
pinMode(saida, OUTPUT);
}

void loop()
{
sinal_digital_umidade = analogRead(sensor_de_umidade);
if(sinal_digital_umidade < valor_umidade){
    char *msg = "1"; // LIGADA 
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    digitalWrite(saida, HIGH);
    
}
if(sinal_digital_umidade > valor_umidade){
    char *msg = "0"; // DESLIGADA 
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
   digitalWrite(saida, LOW); 
}

}

