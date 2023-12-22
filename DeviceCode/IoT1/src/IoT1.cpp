// Koden er sammensat af bme680_example.cpp, SEN-GP2Y1014AU.ino og CCS811_test.cpp
// Koden blev opbygget ved at lave et "default" particle projekt og derefter
// Arbejde på et få en sensor inkorporeret ind i koden af gangen indtil alle 3 virkede.
// Der er lavet nogle få ændringer i nogle af librariesne for at få projektet til at
// kompilere og fungere korrekt.

// Kendte problemer: Når waqi bliver published kommer hele json objectet ikke med.
// Mulig løsning: Del api'ets svar op i et array af strings og publish i bider.

#include "Adafruit_BME680.h"
#include "Adafruit_CCS811.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1010.00)

Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

Adafruit_CCS811 ccs;

double temperatureInC = 0;
double relativeHumidity = 0;
double pressureHpa = 0;
double gasResistanceKOhms = 0;
double approxAltitudeInM = 0;

double CO2 = 0;
double TVOC = 0;

int ledPower = 2;
double dustDensity;
int sensorValue;
double voltage;

String ResultData;

void myHandler(const char *event, const char *data) {
  ResultData = data;
}

void setup() {

  // Subscribe to the integration response event
  Particle.subscribe("hook-response/waqi", myHandler, MY_DEVICES);

  if (!bme.begin()) {
    Particle.publish("Log", "Could not find a valid BME680 sensor, check wiring!");
  } else {
    Particle.publish("Log", "bme.begin() success =)");
    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms

    Particle.variable("temperature", &temperatureInC, DOUBLE);
    Particle.variable("humidity", &relativeHumidity, DOUBLE);
    Particle.variable("pressure", &pressureHpa, DOUBLE);
    Particle.variable("gas", &gasResistanceKOhms, DOUBLE);
    Particle.variable("altitude", &approxAltitudeInM, DOUBLE);
  }

Serial.begin(9600);
 pinMode(ledPower,OUTPUT);
  Serial.println("CCS811 test");

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());

  Particle.variable("CO2", &CO2, DOUBLE);
  Particle.variable("TVOC", &TVOC, DOUBLE);

}

void loop() {

  if (! bme.performReading()) {
    Particle.publish("Log", "Failed to perform reading :(");
  } else {
    temperatureInC = bme.temperature;
    relativeHumidity = bme.humidity;
    pressureHpa = bme.pressure / 100.0;
    gasResistanceKOhms = bme.gas_resistance / 1000.0;
    approxAltitudeInM = bme.readAltitude(SEALEVELPRESSURE_HPA);

    String data = String::format(
      "{"
        "\"temperatureInC\":%.2f,"
        "\"humidityPercentage\":%.2f,"
        "\"pressureHpa\":%.2f,"
        "\"gasResistanceKOhms\":%.2f"
        "\"approxAltitudeInM\":%.2f"
      "}",
      temperatureInC,
      relativeHumidity,
      pressureHpa,
      gasResistanceKOhms,
      approxAltitudeInM);

    Particle.publish("Sensor1", data, 60, PRIVATE);
  }

if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    CO2 = ccs.geteCO2();
    TVOC = ccs.getTVOC();

    String data2 = String::format(
      "{"
        "\"CO2\":%.2f,"
        "\"TVOC\":%.2f"
      "}",
      CO2,
      TVOC);

    Particle.publish("Sensor2", data2, 60, PRIVATE);
    }
    else{
      Serial.println("ERROR!");
    }
  }

// set the LED pin low
    digitalWrite(ledPower,LOW);

    delayMicroseconds(180); // delay about 180us
    // read the analog pin
    sensorValue = analogRead(A0); // needs about 100 us
    delayMicroseconds(30);    //delay about 30 us

    // set the LED pin high
    digitalWrite(ledPower,HIGH);
    delayMicroseconds(9680);  // filling out the rest of the pulse cycle

    // Convert analog value to voltage
    voltage = sensorValue * (5.0 / 1023.0);
  
    // calculate dust density
    if ( voltage <= 0.9) dustDensity = 0.0;
    if (voltage < 3.5 && voltage > 0.9) dustDensity = -0.0127*pow(voltage, 2.0) + 0.2225*voltage - 0.1819;
    if (voltage >= 3.5) dustDensity = 40.0*pow(voltage, 2.0) - 280.8*voltage + 493.28;
    if (dustDensity >= 0.8) dustDensity = 0.8;

    // print the measured and calculated data
    Serial.println("Voltage:\t" + String(voltage) + " V\tDust Density:\t" + String(dustDensity)+ " mg/m^3");
    String data3 = String::format(
      "{Voltage:\t" + String(voltage) + " V\tDust Density:\t" + String(dustDensity) + " mg/m^3}");

    Particle.publish("Sensor3", data3, 60, PRIVATE);
    // Get some data
  String resdata = ResultData;
  // Trigger the integration
  Particle.publish("waqi", resdata, PRIVATE);

  // Wait 60 seconds
  delay(60000);
}