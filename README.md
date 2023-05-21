# COOLER
Esse é o projeto de um cooler robo feito com uma ESP32. Ele pode se locomover, e através do sensor acoplado em sua tampa, e seus leds ele avisa quando está cheio ou vazio.   
______________________________________________________________________________________
O COOLERBOT tem como objetivo principal transportar e manter as bebidas ou alimentos em baixa temperatura, e através do seu sensor de distância acoplado em sua tampa ele tem a capacidade de informar se o cooler está cheio, ou vazio. Quando a luz verde que está na parte superior da tampa estiver acesa o cooler está comunicando que está cheio. Quando a luz vermelha estiver acesa ele está comunicando que está vazio.
Ele através das suas rodas acopladas no carrinho na parte de baixo do cooler que são ativadas de acordo com o comando do celular, funcionam pelos seus motores um na roda direita e outro na roda esquerda. Uma roda na parte da frente sem nenhum motor serve para fazer a movimentação para outras direções além de para trás e para frente. O celular conectado a rede, e utilizando o aplicativo MQTT Dashboard faz o comando dos movimentos, ele responde a placa ESP32 que funciona wifi e em modo bluetooth.
Utilizando a comunicação via Broker MQTT você conecta o seu aparelho celular para exercer comandos para movimentar o COOLERBOT, tendo as opções para frente, ré, direita e esquerda. Na mesma interface em que você comanda os movimentos e ações do COOLERBOT, também é possível ver a resposta do sensor infravermelho dentro da tampa do nosso cooler, que avisa enviando a mensagem “Cooler cheio” quando esta cheio , e a mensagem de “Cooler vazio” quando esta vazio e abaixo dos 10.0 cm que é a distancia estabelecida de acordo com o tamanho do cooler.
Como o COOLERBOT é MQTT broker enquanto ele estiver sendo alimentado por energia, vai estar ativo na rede na qual ele foi configurado e vai receber as informações do nosso sensor infravermelho e vai responder aos comandos que são enviados aos atuadores que são os dois motores ligados em suas rodas.

Instalação
Todos os arquivos deste projeto estão contidos no sketch_may21a/cooler.ino. Abra o diretório e clique no arquivo cooler.ino. O Arduino IDE deve abrir com todos os arquivos desse diretório.


Você precisa instalar o MQTT Dashboard para conectar ao CoolerBot e criar os seus proprios botões utilizando as informações MQTT de Publish e Subscribe.

Configuração de pinos
A maioria dos componentes deste robô são conectados por meio de pinos de E/S digital. Esses pinos podem ser alterados ajustando e configurando de acordo com as funções desejadas

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


Certifique-se de que os seguintes pinos estejam conectados às portas corretamente.

Configure a sua rede e o sensor de distancia dessa maneira.
// Valor de referência para determinar se está cheio ou vazio
const float REFERENCE_DISTANCE = 10.0;  // Valor em centímetros

// Objeto do sensor ultrassônico
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

const char* ssid = "NOME DA SUA REDE";
const char* password = " SUA SENHA";
const char* mqtt_server = "broker.hivemq.com";  //BROKER MQTT (Que é um servidor universal)

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

Configure os comando dessa maneira para que os sensores e cada movimento do COOLERBOT funcionem corretamente

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //Se recebeu F vai para frente
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

  //Se recebeu T vai para trás
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

  //Se recebeu E vai para esquerda
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

  //Se recebeu D vai para direita
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

Executando o código

Apos ter feito todas as configurações e o COOLERBOT estiver na rede faça cada um dos testes de movimento através do MQTT Dashboard e se houver alguma duvida ou problema poste que tentarei ajudar.   
