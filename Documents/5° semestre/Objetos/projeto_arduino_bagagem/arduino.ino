#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
int temp=0,i;
SoftwareSerial ss(RXPin, TXPin);
String stringVal = "";
void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  lcd.begin(16,2);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  lcd.print("Mapeando bagagem");
  lcd.setCursor(0,1);
  lcd.print("    System      ");
  delay(2000);
  gsm_init();
  lcd.clear();  
  Serial.println("AT+CNMI=2,2,0,0,0");
  lcd.print("GPS Initializing");
  lcd.setCursor(0,1);
  lcd.print("  Sem sinal GPS  "); 
  delay(2000);
  lcd.clear();
  lcd.print("GPS Encontrado");
  lcd.setCursor(0,1);
  lcd.print("GPS pronto");
  delay(2000);
  lcd.clear();
  temp=0;
}

void loop()
{ 
serialEvent();

      while(temp)
      {
        while (ss.available() > 0)
        {
          gps.encode(ss.read());
                if (gps.location.isUpdated())
                {
                 temp=0;
                 digitalWrite(13,HIGH);
                 tracking();
                } 
          if(!temp)
          break;  
        }
      }
      digitalWrite(13,LOW);
}
void serialEvent()
{
  while(Serial.available()>0)
  { 
    if(Serial.find("Bagagem"))
    {
      temp=1;
      break;
    }
    else
    {
    temp=0;
    }
  }
}
void gsm_init()
{
  lcd.clear();
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    delay(1);
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  lcd.clear();
  lcd.print("Modulo Connectado..");
  delay(1000);
  lcd.clear();
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }
  lcd.clear();
    delay(1000);
  lcd.clear();
  lcd.print("Procurando Rede..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }
  lcd.clear();
  lcd.print("Rede Encontrada..");
  
  delay(1000);
  lcd.clear();
}
void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"8825737586\"");   
  delay(400);
}
void send_data(String message)
{
  Serial.print(message);
 delay(200);
}
void send_sms()
{
  Serial.write(26);
}
void lcd_status()
{
  lcd.clear();
  lcd.print("Mensagem enviada");
  delay(2000);
  lcd.clear();
  lcd.print("Sistema pronto");
  return;
}
void tracking()
{
    init_sms();
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("\n Longitude: ");
    Serial.println(gps.location.lng(), 6);
    send_sms();
    delay(2000);
    lcd_status();
}
