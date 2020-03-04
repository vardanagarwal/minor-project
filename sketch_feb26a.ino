double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}

int plant_index(String plant)
{
  if(plant=='cotton')
    return(0);
  else if(plant=='maize')
    return(1);
  else if(plant=='millet')
    return(2);
  else if(plant=='groundnut')
    return(3);
  else if(plant=='sorghum')  
    return(4);
  else
    return(-1);

}

float find_kc(int days_passed, float kc_ini, float kc_dev, float kc_mid, float kc_end, byte g_ini, byte g_dev, byte g_mid, byte g_end, float ET)
{
  float kc = 0.0;
   if(days_passed <= g_ini)
    kc = kc_ini*ET;  
   else if(days_passed <= (g_ini+g_dev))
    kc = kc_dev*ET;
   else if(days_passed <= (g_ini+g_dev+g_mid))
    kc = kc_mid*ET;
   else if(days_passed >= (g_ini+g_dev+g_mid+g_end))
    kc = kc_end*ET;

   return (kc);
}


#include <dht11.h>
#define DHT11PIN 4
#define SOILPIN A0

String plant = "cotton"; //cotton or maize or millet or groundnut or sorghum
int index = plant_index(plant);

float ET[] = {7.861669, 11.097850, 11.188744, 14.553114, 15.196926, 16.673455, 14.218546, 13.019239, 12.932587, 11.118871, 10.195709, 6.683616};//precomputed values from Tmean and p

float kc_ini[]={0.45,0.4,0.35,0.45,0.35};
float kc_dev[]={0.75,0.8,0.7,0.75,0.75};
float kc_mid[]={1.15,1.15,1.1,1.05,1.1};
float kc_end[]={0.75,0.7,0.65,0.7,0.65};

byte g_ini[]={30,20,15,25,20};
byte g_dev[]={50,35,25,35,30};
byte g_mid[]={55,40,40,45,40};
byte g_end[]={45,30,25,25,30};

dht11 DHT11;
int soil_moisture = 0;

void setup()
{
  Serial.begin(9600);
 
}

void loop()
{
  // Starting of code for DHT Sensor
  int chk = DHT11.read(DHT11PIN);
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;

  Serial.print("Humidity (%): ");
  Serial.println(humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println(temperature, 2);

  Serial.print("Dew point (C): ");
  Serial.println(dewPoint(temperature, humidity), 2);
  //End of code of DHT Sensor
  
  soil_moisture = analogRead(SOILPIN);
  Serial.print("Soil moisture level: ");
  Serial.println(soil_moisture);
  
  int month = 3; // obtained by rtc sensor
  int days_passed = 0; // obtained by rtc sensor

  int kc = find_kc(days_passed, kc_ini[index], kc_dev[index], kc_mid[index], kc_end[index], g_ini[index], g_dev[index], g_mid[index], g_end[index], ET[month]);
  Serial.println(" ");
  delay(2000);
}
