#include <Wire.h>

// Define the unique number for the arduino slave
#define SLAVE_ADDRESS 0x08

/*
 * The max value for the soil moisture sensor,
 * the value that it will be when it's out of soil and in the air
 */
#define AIR_VALUE 459

/*
 * The min value for the soil moisture sensor,
 * the value that it will be when it's in pure water (i.e. a cup of water)
 */
#define WATER_VALUE 182

// AOUT pin on sensor
#define SOIL_PIN A0

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Serial.begin(9600); // serial port setup
  Wire.onRequest(sendSoilMoistureData);
}

void loop() {
   
}

// Get the soil moisture analogue reading
int getSoilMoisture(){
  int soilMoisture = analogRead(SOIL_PIN);
  return soilMoisture; 
}

// Get the soil mositre reading as a percentage
int getSoilMoisturePercentage(int soilMoisture){
  int soilMoisturePercentage = map(soilMoisture,AIR_VALUE,WATER_VALUE,0,100);
  return soilMoisturePercentage;
}

// Print the soil moisture reading
void printSoilMoistureValue(int soilMoisture){
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println();
}

// Print the soil moisture reading as a percentage
void printSoilMoisturePercentageValue(int soilMoisturePercentage){
  Serial.print("Percentage: ");
  Serial.print(soilMoisturePercentage);
  Serial.print("%");
  Serial.println();
}

// Data to send when requested by master
void sendSoilMoistureData()
{
  // Get the analog soil moisture value
  int soilMoisture = getSoilMoisture();

  // Convert the analogue reading to a percentage
  int soilMoisturePercentage = getSoilMoisturePercentage(soilMoisture);

  // Print the soil moisture value
  printSoilMoistureValue(soilMoisture);
  
  // Print the percentage reading
  printSoilMoisturePercentageValue(soilMoisturePercentage);
  
  Wire.write(soilMoisturePercentage);
}
