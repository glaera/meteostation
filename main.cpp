#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>

// recipies: arduino mega, BME280, Geekcreit® IIC I2C 2004 204 20 x 4 Character LCD Display Module Blue For Arduino
float temperature;
float humidity;
float pressure;

#define ALTITUDE 216.0 // Altitude in Sparta, Greece

Adafruit_BME280 bme; // I2C

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


void setup(void) {

  lcd.begin(20,4); 
  lcd.print("Reading sensors");

   bool status;
    
    // default settings
    status = bme.begin(0x76);  //The I2C address of the sensor I use is 0x76

    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}



float Celcius2Fahrenheit(float celsius)
{
  return celsius * 9 / 5 + 32;
}



float getTemperature()
{
  temperature = bme.readTemperature();
//  temperature = Celcius2Fahrenheit(temperature);
}


float getHumidity()
{
  humidity = bme.readHumidity();
}


float getPressure()
{
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;
}




void loop() {
  
 delay(2000);

 getPressure();
 getHumidity();
 getTemperature();
 
 lcd.clear(); 
 //Printing Temperature
 String temperatureString = String(temperature,1);
 lcd.print("T:"); 
 lcd.print(temperatureString);
 lcd.print((char)223);
 lcd.print("F ");
 
 //Printing Humidity
 String humidityString = String(humidity,0); 
 lcd.print("H: ");
 lcd.print(humidityString);
 lcd.print("%");
 
 //Printing Pressure
 lcd.setCursor(0,1);
 lcd.print("P: ");
 String pressureString = String(pressure,2);
 lcd.print(pressureString);
 lcd.print(" hPa");

}




