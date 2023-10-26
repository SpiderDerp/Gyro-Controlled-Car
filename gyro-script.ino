#include <Wire.h>

#include "SparkFun_BNO08x_Arduino_Library.h" // CTRL+Click here to get the library: http://librarymanager/All#SparkFun_BNO08x

#include <SoftwareSerial.h>

BNO08x myIMU;

int pin1 = 0;
int pin2 = 0;
int pin3 = 0;
int pin4 = 0;
int pin5 = 0;

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("BNO08x Read Example");

    //Replace with the actual pins you are using
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(pin5, OUTPUT);

    Wire.begin();

    if (myIMU.begin() == false) {
        Serial.println("BNO08x not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
        while (1)
        ;
    }
    Serial.println("BNO08x found!");

    // Wire.setClock(400000); //Increase I2C data rate to 400kHz

    setReports();

    Serial.println("Reading events");
    delay(100);
}

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (myIMU.enableGyro() == true) {
    Serial.println(F("Gyro enabled"));
    Serial.println(F("Output in form x, y, z, in radians per second"));
  } else {
    Serial.println("Could not enable gyro");
  }
}

void loop() {
  delay(10);

  if (myIMU.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  // Has a new event come in on the Sensor Hub Bus?
  if (myIMU.getSensorEvent() == true) {

    // is it the correct sensor data we want?
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_GYROSCOPE_CALIBRATED) {

        float x = myIMU.getGyroX();
        float y = myIMU.getGyroY();
        float z = myIMU.getGyroZ();
        bool Xp, Xn, Zp, Zn, XZ; 
        
        Serial.print(x, 2);
        Serial.print(F(","));
        Serial.print(y, 2);
        Serial.print(F(","));
        Serial.print(z, 2);

        Serial.println();

        Xp = x > 0;
        Xn = x < 0;
        Zp = z > 0;
        Zn = z < 0;
        XZ = x < z;

        if (Xp) {
            digitalWrite(pin1, HIGH);
        } else {
            digitalWrite(pin1, LOW);
        }

        if (Xn) {
            digitalWrite(pin2, HIGH);
        } else {
            digitalWrite(pin2, LOW);
        }

        if (Zp) {
            digitalWrite(pin3, HIGH);
        } else {
            digitalWrite(pin3, LOW);
        }

        if (Zn) {
            digitalWrite(pin4, HIGH);
        } else {
            digitalWrite(pin4, LOW);
        }

        if (XZ) {
            digitalWrite(pin5, HIGH);
        } else {
            digitalWrite(pin5, LOW);
        }
    }
  }
}