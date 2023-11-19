#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "logger.h"

const char* ssid     = "Langkau-Gast";
const char* password = "";
const String server_url = "https://intranet.langkau-network.de/esp/test.php";

LoggingUtils::Logger logger(LoggingUtils::TRACE);
void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    logger.log("");
    logger.log("----------");
    logger.log("Booting...");

    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    logger.debug("Turned LED off");

    logger.log("Finished!");
    logger.log("");
    WiFi.begin(ssid, password);
    logger.debug("Connecting to:");
    logger.debug("SSID: " + String(ssid));
    logger.debug("with password: " + String(password));

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        logger.debug("Trying connection to WiFi... (" + String(++i) + ")");
    }
    logger.debug(String("IP-Adress: ") + WiFi.localIP().toString().c_str());
    logger.info("WiFi Connection established!");
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED on by making the voltage LOW
    logger.debug("Turned LED on");
}

void loop() {
    delay(10000);
    logger.debug("Sending request to Server");
    WiFiClientSecure client;
    client.setInsecure(); // Nur für Testzwecke, nicht für den Produktiveinsatz empfohlen
    HTTPClient http;
    http.begin(client, server_url); // Verwende WiFiClientSecure für HTTPS
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();
    logger.debug("HTTP Code: " + String(httpCode));
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            logger.info("Response: " + payload);
        }
    } else {
        logger.info("Error on HTTP request: " + String(http.errorToString(httpCode).c_str()));
    }
    http.end();
}