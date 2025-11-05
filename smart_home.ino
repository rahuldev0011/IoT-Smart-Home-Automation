#include <ESP8266WiFi.h>

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

WiFiServer server(80);

int relay1 = D1;
int relay2 = D2;

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  if (req.indexOf("/light1on") != -1) digitalWrite(relay1, LOW);
  if (req.indexOf("/light1off") != -1) digitalWrite(relay1, HIGH);
  if (req.indexOf("/light2on") != -1) digitalWrite(relay2, LOW);
  if (req.indexOf("/light2off") != -1) digitalWrite(relay2, HIGH);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html><body>");
  client.println("<h2>Smart Home Control</h2>");
  client.println("<a href=\"/light1on\">Light 1 ON</a><br>");
  client.println("<a href=\"/light1off\">Light 1 OFF</a><br>");
  client.println("<a href=\"/light2on\">Light 2 ON</a><br>");
  client.println("<a href=\"/light2off\">Light 2 OFF</a><br>");
  client.println("</body></html>");
  client.stop();
}
