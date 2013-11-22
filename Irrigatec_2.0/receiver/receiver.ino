// receiver.pde
// o recepitor usa o pino 11 do arduino
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <LiquidCrystal.h>
// LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
void setup()
{
 
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");
   // lcd.begin(20, 4);
   
    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
   // vw_set_rx_pin(2);
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

 pinMode(4, OUTPUT);
}

void loop()
{
   

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
     
        digitalWrite(13, true); // Flash a light to show received good message
 //Message with a good checksum received, dump it.
     /*
     lcd.setCursor(0, 1);
     lcd.print("Chegou: ");
     lcd.setCursor(0, 2);
     lcd.print(buf[i], DEC);
     lcd.print("      ");
     */
        if(buf[i] == '1'){
        digitalWrite(4, HIGH);
        
      }
            
        if(buf[i] == '0'){
        digitalWrite(4, LOW);
 
       }
	    
        digitalWrite(13, false);
    }
}
