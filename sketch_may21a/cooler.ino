#include <WiFi.h>
#include <PubSubClient.h>
#include <Ultrasonic.h>

// Define pinos motor Esquedo
const int in1 = 15;
const int in2 = 2;

// Define pinos motor Direito
const int in3 = 21;
const int in4 = 22;

// Define pinos LED
const int ledG = 18;
const int ledR = 21;

// Define pinos do Sensor Ultrassônico
#define TRIGGER_PIN 4
#define ECHO_PIN 5

// Valor de referência para determinar se está cheio ou vazio
const float REFERENCE_DISTANCE = 10.0;  // Valor em centímetros

// Objeto do sensor ultrassônico
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

const char* ssid = " "; // Nome da Rede Wi-Fi
const char* password = " "; // Senha da Rede Wi-Fi
const char* mqtt_server = "broker.hivemq.com";  //BROKER MQTT da HiveMQ, que é público e gratuito

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];


// Função responsável por fazer a conexão da ESP32 ao Wi-Fi
void setup_wifi() {
  delay(10);
  
  Serial.println();
  Serial.print("Conectando à");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Função responsável por verificar as mensagens que vem pelo tópico que a ESP32 assina
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //Se receber a letra F, vai para frente
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

  //Se receber a letra T, vai para trás
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

  //Se receber a letra E, vai para esquerda
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

  //Se receber a letra D, vai para direita
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

// Função responsável por conectar ao Broker MQTT e assinar o Tópico.
void reconnect() {
  // Loop até se reconectar
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    //Cria um client ID aleatório
    String clientId = "TIAGO_MQTT";
    clientId += String(random(0xffff), HEX);
    // Tenta se conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");

      client.subscribe("tiagosilva/carrinho"); //aqui que assinamos o tópico
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Espera 5 segundos até conectar novamente
      delay(5000);
    }
  }
}

void setup() {
  
  Serial.begin(115200); //inicia a comunicação serial

 //define os pinos dos leds e dos motores como saída
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);

  setup_wifi(); //chama a função de conexão ao Wi-Fi

  client.setServer(mqtt_server, 1883); //define o broker e a porta a serem usados
  client.setCallback(callback); //define a função responsáve por receber os comandos
}

void loop() {

  float distance = ultrasonic.read(); //faz a leitura da distância através do sensor Ultrassônico

  //exibe no monitor serial a distância medida
  Serial.print("Distancia em CM: ");
  Serial.println(distance);

 /* Comparação da distância medida pelo sensor Ultrassônico com a medida de referência.
    Caso a medida real seja menor, publica no tópico a mensagem "Cooler Cheio", apaga o LED vermelho e acende o LED Verde.
    Caso a medida real seja maior ou igual, publica no tópico a mensagem "Cooler Vazio", acende o LED vermelho e apaga o LED Verde.
 */
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

  //caso o MQTT se desconecte, chama a função de conexão
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
