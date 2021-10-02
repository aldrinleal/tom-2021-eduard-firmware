#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "analogWrite.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

DNSServer dnsServer;

AsyncWebServer server(80);

class CaptiveRequestHandler : public AsyncWebHandler {
public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request){
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
  if(!SPIFFS.begin(true)){
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

  server.on("/assets/bootstrap.bundle.min.js", [](AsyncWebServerRequest* request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/bootstrap.bundle.min.js", "text/javascript", false);
  });
  
  server.on("/assets/core.js", [](AsyncWebServerRequest* request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/core.js", "text/javascript", false);
  });

  server.on("/assets/bootstrap.min.css", [](AsyncWebServerRequest* request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/bootstrap.min.css", "text/css", false);
  });

  server.on("/assets/starter-template.css", [](AsyncWebServerRequest* request) {
      Serial.println(request->url());
      request->send(SPIFFS, "/assets/starter-template.css", "text/css", false);
  });

  server.onNotFound(notFound);

  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
}
