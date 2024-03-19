#include <stdio.h>
#include <string.h>
//#include <DHT.h>

//String Apikey = "YYHMW3240HI0KL4J";

#define DEBUG true

#define LTE_PWRKEY_PIN 32



#define Sensor_PIN 3  //D3-DHT11
#define SerialUSB Serial


//DHT  dht(Sensor_PIN,DHT11);



void setup()
{
    SerialUSB.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, 16, 17);
     pinMode(LTE_PWRKEY_PIN, OUTPUT);
    digitalWrite(LTE_PWRKEY_PIN, HIGH);
    delay(2000);
    digitalWrite(LTE_PWRKEY_PIN, LOW);
    delay(5000);


    sendData("AT+CCID", 3000, DEBUG);
    sendData("AT+CREG?", 3000, DEBUG);
    sendData("AT+CGATT=1", 1000, DEBUG);
    sendData("AT+CGACT=1,1", 1000, DEBUG);
    sendData("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\"", 1000, DEBUG);

    //sendData("AT+CIPSTART=\"TCP\",\"www.mirocast.com\",80", 2000, DEBUG);
    SerialUSB.println("4G HTTP Test Begin!");

  //  dht.begin();
    delay(1000);
}

void loop()
{
    //--------Get temperature and humidity-------------
    float h = 32.45;
    float t = 98.21;

    //-----------HTTP---------------------
    String http_str = "AT+HTTPPARA=\"URL\",\"https://iot-997w.onrender.com/addvalues?temperature=" + String(t) + "&humidity=" + String(h) + "\"\r\n";
    SerialUSB.println(http_str);

    sendData("AT+HTTPINIT\r\n", 2000, DEBUG);
    sendData(http_str, 2000, DEBUG);
    sendData("AT+HTTPACTION=0\r\n", 3000, DEBUG);
    sendData("AT+HTTPTERM\r\n", 3000, DEBUG);

    delay(5000);   

}
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial1.println(command);
  
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    SerialUSB.print(response);
  }
  return response;
}