#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char* ssid = "1614";
const char* password = "QWERTY12345";
AsyncWebServer server(80); // HTTP server on port 80

Servo servo;  // create servo object to control a servo
int servoPin = 13; // GPIO pin for servo control
int pos =0;    // variable to store the servo position

bool isLightOn = false; // State of the light


void setup() {
    Serial.begin(115200);

	// Set up WiFi
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

	Serial.println("");
	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());

	// SPIFFS
	if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
 	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/app.html", "text/html");
    });

	// Servos
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo.setPeriodHertz(50);    // standard 50 hz servo
	servo.attach(servoPin, 500, 2400);

	// Routes
    server.on("/toggle-light", HTTP_GET, [](AsyncWebServerRequest *request){
        isLightOn = !isLightOn; // Toggle the state
        if(isLightOn) {
            servo.write(25); // Open position
			delay(1000);
			servo.write(85); // Open position
        } else {
            servo.write(145); // Close position
			delay(1000);
			servo.write(85); // Close position
        }
        request->send(200, "text/plain", isLightOn ? "Light On" : "Light Off");
    });



    // Start the server
    server.begin();
}

void loop() {
    // Nothing needed here for the web server
}

