#include <WiFi.h>
// Replace with your network credentials
const float voltageReference = 3.3; // la tension d'alimentation est de 4,5 à 5,5V. Normalement 5V.
const int model = 2; // entrer le numéro de modèle (voir ci-dessous)
const int acs712Pin = 25;     // ACS712 analog input pin
const int voltagePin =26 ;    // Voltage divider analog input pin
float Temperature=0.00;
float puissance=0.00;
// Constantes pour le calcul de la tension
const float QOV = 0.8 * voltageReference; // définir la tension de sortie de repos à 0,5V

// Constantes pour le modèle ACS712
const char* ssid = "Anas";
const char* password = "pin.OUT23";
// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
// Auxiliary variables to store the current output state

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
void setup() {
  Serial.begin(112500); // Initialiser le moniteur série
pinMode(25,INPUT);
pinMode(26,INPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
}
float getCurrent()
{
  float voltage;
  float voltage_raw = (voltageReference/ 4095.0) * analogRead(acs712Pin); // Lire la tension du capteur
  voltage = voltage_raw - QOV; // 0,000 est une valeur pour mettre la tension à zéro en l'absence de courant
  float current = voltage;

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

void loop(){
    Serial.print("Current: ");
  Serial.print(abs(getCurrent()));
  Serial.print(" A\t");
  Serial.print("Voltage: ");
  Serial.print(getVoltage());
  Serial.println(" V");
  delay(1000);
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
             client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();  
             client.println("<HTML>");
           client.println("<HEAD>");
            client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");   
           client.println("</HEAD>");
           client.println("<BODY>");
            // turns the GPIOs on and off
                       client.println("<center>");
                client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            // Web Page Heading
        
            // If the output12State is off, it displays the ON button      
              client.println("<p><a href=\"/12/on\"><button class=\"button\">systeme de supervision des panneaux solaire</button></a></p>");

           client.println("<hr />");  //horizontal line
           client.println("<br />");  //line break
           client.println("<H2></H2>");
    
           
           client.println("</center>");
      client.println("<br />"); 
   client.println("<br />");
    client.println("<br />");
 float Vin= (analogRead(26)*voltageReference /4096);
client.print("<a href=\"/?buttonon\"\">Pannel Voltage:</a>");
client.println (getVoltage(););
client.println (" V");
  client.println("<br />"); 
   client.println("<br />");
    client.println("<br />");
  
client.print("<a href=\"/?button3on\"\">Pannel Current:</a>");
client.println (getCurrent());
client.println ("  A ");
 client.println("<br />"); 
   client.println("<br />");
    client.println("<br />");
     client.print("<a href=\"/?button4on\"\">Pannel Power:</a>");
client.println (puissance);
client.println (" W ");
 client.println("<br />"); 
   client.println("<br />");
    client.println("<br />");
  client.println("</h1>");  
         client.println("<br />");     
           client.println("<br />"); 
            client.println("<h1>Cree par Anas Andaloussi</h1>");  
           client.println("<br />"); 
             client.println("<h1><b>Encadre par Madame HASSNA</b><h1>"); 
   delay(1);
           //stopping client
           client.stop();
  

  }

  
}
      }
    }
  }

}
