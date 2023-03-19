#include <Wire.h>
#include <Adafruit_BMP3XX.h>
#include <SD.h>

Adafruit_BMP3XX bmp; // create BMP388 object
File dataFile;       // create file object for writing data

void setup()
{
    Serial.begin(115200);

    if (!SD.begin())
    {
        Serial.println("SD card initialization failed!");
        return;
    }
    Serial.println("SD card initialization done.");

    if (!bmp.begin())
    {
        Serial.println("Could not find a valid BMP388 sensor, check wiring!");
        while (1)
            ;
    }
    Serial.println("BMP388 sensor initialization done.");

    dataFile = SD.open("data.txt", FILE_WRITE); // open file for writing
    if (!dataFile)
    {
        Serial.println("Error opening data.txt for writing.");
        return;
    }
    Serial.println("data.txt opened for writing.");
    dataFile.println("Altitude (m),Pressure (Pa),Temperature (C)"); // write header
}

void loop()
{
    float altitude = bmp.readAltitude(1013.25); // read altitude
    float pressure = bmp.readPressure();        // read pressure
    float temperature = bmp.readTemperature();  // read temperature

    Serial.print("Altitude = ");
    Serial.print(altitude, 2);
    Serial.print(" metres, Pressure = ");
    Serial.print(pressure, 2);
    Serial.print(" Pa, Temperature = ");
    Serial.print(temperature, 2);
    Serial.println(" C");

    dataFile.print(altitude, 2);
    dataFile.print(",");
    dataFile.print(pressure, 2);
    dataFile.print(",");
    dataFile.println(temperature, 2);

    delay(1000); // wait for 1 second
}
