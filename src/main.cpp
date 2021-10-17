#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "analogWrite.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

DNSServer dnsServer;

AsyncWebServer server(80);

class CaptiveRequestHandler : public AsyncWebHandler {
public:
    CaptiveRequestHandler() {}

    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      //request->addInterestingHeader("ANY");
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      request->send(SPIFFS, "/redirect.html", "text/html", false);
    }
};

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  delay(2000);

  Serial.begin(115200);

  Serial.println("Started");

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //your other setup stuff...
  WiFi.softAP("tom-eduard", "tikkumolam2021");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  dnsServer.start(53, "*", WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/index.html", "text/html", false);
  });

  server.on("/assets/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/bootstrap.bundle.min.js", "text/javascript", false);
  });

  server.on("/assets/core.js", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/core.js", "text/javascript", false);
  });

  server.on("/assets/jquery-3.6.0.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/jquery-3.6.0.min.js", "text/javascript", false);
  });

  server.on("/assets/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/bootstrap.min.css", "text/css", false);
  });

  server.on("/assets/starter-template.css", HTTP_GET, [](AsyncWebServerRequest *request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/starter-template.css", "text/css", false);
  });

  server.on("/action", HTTP_POST,
            [](AsyncWebServerRequest *req) {},
            NULL,
            [](AsyncWebServerRequest *req, uint8_t *data, size_t len, size_t index, size_t total) {
                StaticJsonDocument<16> doc;

                DeserializationError error = deserializeJson(doc, data, len);

                if (error) {
                  Serial.print(F("deserializeJson() failed: "));
                  Serial.println(error.f_str());

                  req->send(422, "text/json", "'invalid'");
                  return;
                }

                String direction = doc["direction"];

                Serial.print("Direction: ");

                if (direction.equals("up")) {
                  Serial.println(direction);
                  req->send(200, "text/json", "true");

                  return;
                } else if (direction.equals("down")) {
                  Serial.println(direction);
                  req->send(200, "text/json", "true");

                  return;
                } else if (direction.equals("left")) {
                  Serial.println(direction);
                  req->send(200, "text/json", "true");

                  return;
                } else if (direction.equals("right")) {
                  Serial.println(direction);
                  req->send(200, "text/json", "true");

                  return;
                }

                Serial.println("invalid");
                req->send(422, "text/json", "false");
            });

  server.onNotFound(notFound);

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
}
