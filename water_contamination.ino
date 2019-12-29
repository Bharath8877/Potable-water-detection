#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[] = "your auth key";
char ssid[] = "wifi ssid";
char pass[] = "password";
int a=A0;
int val;

void setup()
{
  pinMode(led,OUTPUT);
  
  // Debug console
  Serial.begin(9600);
  timer.setInterval(500,tur);
  Blynk.begin(auth, ssid, pass);
  
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
void tur()
{
    val=analogRead(a);
    Serial.println(val);
    float turval = val*(5.0/1024.0);
    
    Serial.print("Turbidity value: ");
    Serial.println(turval);
    //Serial.println("%");
    //Serial.println(100-5/1*1000);
    Blynk.virtualWrite(V0, turval);

    if(turval==5.0)
    {
      Serial.println("Clean water");
      Blynk.notify("Water is clean");
    } 
    if(turval<4.0)
    {
      Serial.println("Water is contaminated!");
      Blynk.notify("Water is contaminated!");
    }

}
void loop()
{
  Blynk.run();
  timer.run();
}
