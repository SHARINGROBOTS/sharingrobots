/*----------------------------------------------------- 
Author:  luisBPS
Date: 2014 abril 12
Description:

Programa de recepcion de ordenes por BLuetooth

-----------------------------------------------------*/

u8 val;                                 // data from the serial port
int i; 
void setup()
{
    pinMode(USERLED, OUTPUT);           
    Serial.begin(9600);                 
    
    delay(1000);  
}
 
void loop()
{
    toggle(USERLED);
    digitalWrite(10,HIGH);
    if ( Serial.available() )
        val = Serial.read();            
 
    if ( val == 'w' )  {                 
        for (i=0 ;i<10 ;i++){
                digitalWrite(13, HIGH);    
                digitalWrite(15, HIGH);    
                delay(10);
                digitalWrite(13, LOW);    
                digitalWrite(15, LOW);    
                delay(20);
            }
        }
    if ( val == 's'  )  {                 
        for (i=0 ;i<10 ;i++){
                digitalWrite(14, HIGH);    
                digitalWrite(16, HIGH);    
                delay(10);
                digitalWrite(14, LOW);    
                digitalWrite(16, LOW);    
                delay(20);
            }
        }         
               
    if ( val == 'a' )  {            
            for (i=0 ;i<20 ;i++){
                digitalWrite(13, HIGH);    
                digitalWrite(16, HIGH);    
                delay(7);
                digitalWrite(13, LOW);    
                digitalWrite(16, LOW);    
                delay(7);
            }         
        }       
    if ( val == 'd' )  {                 
                for (i=0 ;i<20 ;i++){
                digitalWrite(14, HIGH);    
                digitalWrite(15, HIGH);    
                delay(7);
                digitalWrite(14, LOW);    
                digitalWrite(15, LOW);    
                delay(7);
            }         
        }       
    Serial.flush();
    delay(50);
    val = 0;
                       
}