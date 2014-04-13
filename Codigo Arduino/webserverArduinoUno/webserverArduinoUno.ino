#include <EtherCard.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(6, 7); // Pines donde va el Bluetooth HC-05
static byte mymac[] = {0x1C,0xDD,0xDD,0x00,0x00,0x1C};
static byte myip[] = {192,168,3,150};
byte Ethernet::buffer[700];

const int ledPin = 2;    //Led de testeo Botton  ON OFF
boolean ledStatus;
char* on = "ON";
char* off = "OFF";

char* statusLabel;
char* buttonLabel;
char* fw = "Adelante";
char* bLabelFw;
char* bc = "Atras";
char* bLabelBc;
char* lf = "Izquierda";
char* bLabelLf;
char* rg = "Derecha";
char* bLabelRg;
void setup () {
 
  Serial.begin(9600);
  Serial.println("Control ShareRobot001");
  BTSerial.begin(38400); // HC-05 default speed in AT command more
  
//    if (Serial.available())
  
  
  if (!ether.begin(sizeof Ethernet::buffer, mymac))
    Serial.println( "Failed to access Ethernet controller");
 else
   Serial.println("Ethernet controller initialized");
 
  if (!ether.staticSetup(myip))
    Serial.println("Failed to set IP address");
  Serial.println();
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  ledStatus = false;
}
  
void loop() {
 
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if(pos) {
    
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) {
      Serial.println("Received ON command");
      ledStatus = true;
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=OFF") != 0) {
      Serial.println("Received OFF command");
      ledStatus = false;
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=Adelante") != 0) {
      Serial.println("Received Fw command");
      BTSerial.write("w");
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=Atras") != 0) {
      Serial.println("Received Bc command");
      BTSerial.write("s");      
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=Izquierda") != 0) {
      Serial.println("Received Lf command");
      BTSerial.write("a");
    }
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=Derecha") != 0) {
      Serial.println("Received Rg command");
      BTSerial.write("d");      
    }
    if(ledStatus) {
      digitalWrite(ledPin, HIGH);
      statusLabel = on;
      buttonLabel = off;
    } else {
      digitalWrite(ledPin, LOW);
      statusLabel = off;
      buttonLabel = on;
    }
      
    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
      "<html><head><title>SHARING ROBOT 001</title></head>"
      "<body bgcolor=gray><br><br><br><div align=center>"
      "<p>Control Robot 001</p><br>"
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a><br>"
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a>"
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a><br>"
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a><br><br><br>"
      "<a href=\"/?status=$S\"><input type=\"button\" value=\"$S\"></a><br>"
      "</div><br>"
      "<div align=center> Control LED: $S </div></body></html>"      
      ),fw,fw,lf,lf,rg,rg,bc,bc, buttonLabel, buttonLabel,statusLabel);
      
    ether.httpServerReply(bfill.position());
  }
}

