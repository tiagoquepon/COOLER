#include <WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>

// Define pinos motor A
const int in1 = 15;
const int in2 = 2;

// Define pinos motor B
const int in3 = 21;
const int in4 = 22;

// Define pinos LED
const int ledG = 18;
const int ledR = 21;

#define TRIGGER_PIN 4
#define ECHO_PIN 5

// Valor de referência para determinar se está cheio ou vazio
const float REFERENCE_DISTANCE = 10.0;  // Valor em centímetros

// Objeto do sensor ultrassônico
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

const char* ssid = "Dom";
const char* password = "dom131006";
const char* mqtt_server = "broker.hivemq.com";  //BROKER MQTT

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //para frente
  if ((char)payload[0] == 'F') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  //para trás
  if ((char)payload[0] == 'T') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  //para esquerda
  if ((char)payload[0] == 'E') {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  //para direita
  if ((char)payload[0] == 'D') {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "TIAGO_MQTT";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");

      client.subscribe("tiagosilva/carrinho");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  float distance = ultrasonic.read();

  Serial.print("Distance in CM: ");
  Serial.println(distance);

  if (distance < REFERENCE_DISTANCE) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    Serial.println("Cooler Cheio");
    snprintf(msg, MSG_BUFFER_SIZE, "Cooler Cheio");
    client.publish("tiagosilva/cooler", msg);
  } else {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    Serial.println("Cooler Vazio");
    snprintf(msg, MSG_BUFFER_SIZE, "Cooler Vazio");
    client.publish("tiagosilva/cooler", msg);
  }

  delay(1000);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}