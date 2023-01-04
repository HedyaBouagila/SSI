#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST"systeme-de-gestion-d-inc-8a840-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "wp4yKOKmNgJA21ujXbkig3rl64z4LeBFbBbbwiyy"
#define WIFI_SSID "hedya"
#define WIFI_PASSWORD "hedya1999"

String flame_status;
String gaz_status;

int flame_sensor = D1;
int gaz_sensor =D2;
int marwha = D3;
int pompe = D4;  

void setup()
{
  WiFi.begin(WIFI_SSID , WIFI_PASSWORD);
  Serial.print("connecting to");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected to: ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  pinMode(D1, INPUT); // capteur l flame
  pinMode(D2, INPUT);  // capteur l gaz
  pinMode(D3, OUTPUT);  // l marw7a
  pinMode(D4, OUTPUT);  // l pompe
  
  digitalWrite(D3, LOW); //mrwha
  digitalWrite(D4, LOW); //pompe

  Serial.begin(115200);
  
}
void loop() 
{
  flame_sensor= digitalRead(D1);
  gaz_sensor= digitalRead(D2);

   
  if (flame_sensor== 0)

    {
    digitalWrite(D4, HIGH);
    flame_status="Alert Fire Detected";
    Serial.println("Alert Fire Detected !");  
    }
  else
      {
      digitalWrite(D4, LOW);
      flame_status="No_Fire";
      }
  delay(1000);


  if (gaz_sensor== 0)

    {
    digitalWrite(D3, HIGH);
    gaz_status="Alert Gaz Detected !";
    Serial.println("Alert Gaz Detected !");  
    }
  else
      {
      digitalWrite(D3, LOW);
      gaz_status="No_Gaz ";
      }
  Firebase.setString("FIRE", flame_status);
  Firebase.setString("GAZ", gaz_status);
  delay(1000);
  
}