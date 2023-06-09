const float voltageReference = 3.3; // la tension d'alimentation est de 4,5 à 5,5V. Normalement 5V.
const int model = 2; // entrer le numéro de modèle (voir ci-dessous)
const int acs712Pin = 25;     // ACS712 analog input pin
const int voltagePin =26 ;    // Voltage divider analog input pin



const float QOV = 0.8 * voltageReference; // définir la tension de sortie de repos à 0,5V
void setup()
{
  Serial.begin(112500); // Initialiser le moniteur série
pinMode(25,INPUT);
pinMode(26,INPUT);
}
float getCurrent()

{
  float voltage;
  float voltage_raw = (voltageReference/ 4095.0) * analogRead(acs712Pin); // Lire la tension du capteur
  voltage = voltage_raw - QOV; // 0,000 est une valeur pour mettre la tension à zéro en l'absence de courant
  float current = voltage;

  return current;

  return current;
}

float getVoltage()
{
  
  int i = 0;
  float Vout = 0.00;
float Vin = 0.00;
float R1 = 100000.00;
float R2 = 10000.00;
  while (i < 10)
  {
    Vout = (analogRead(voltagePin) *voltageReference ) / 4096.00;
    Vin += (Vout * (R2 + R1)) / R2;
    i++;
  }
  Vin = Vin / 10;
  return Vin;
}




void loop()
{
  Serial.print("Current: ");
  Serial.print(abs(getCurrent()));
  Serial.print(" A\t");
  Serial.print("Voltage: ");
  Serial.print(getVoltage());
  Serial.println(" V");
  delay(1000);
}
