#HARDWARE 

#1 ESP32
 
O ESP32 é um microcontrolador, ele pode ser usado em diversos projetos de IoT (Internet das Coisas), robótica, automação residencial e outros projetos que envolvem conexão com a internet. É utilizado para receber comandos enviados pelo usuário através da internet e processos de acordo com o código e também utilizados para controlar os motores. O ESP32 é capaz de se conectar nas redes através de Wi-Fi e é dele que vem a conexão fornecida ao robô para  comunicação com sensores como é feita no sensor de distância ultrassónico serve como atuador MQTT.

#2 MOTORES

 
São usados motores que operam com fonte de alimentação de 12 Vcc. Estas são máquinas elétricas rotativas que convertem energia direta energia elétrica atual em energia mecânica. Os motores utilizados são de 30 rpm de velocidade de operação, serão usados nas rodas 



 
#3 SENSOR INFRAVERMELHO

 
Um sensor infravermelho é usado para detectar e determinar a natureza e aspectos dos arredores, emitindo infravermelho radiação. Este sensor tem a capacidade de emitir infravermelho radiação e detecta a radiação refletida que está sendo refletida por um objeto ou pelo ambiente. O intervalo é entre 2 cm a 30 cm e a tensão de operação é em torno 3v a 5v. Este sensor infravermelho é conectado ao robô para detectar arestas presentes em seu caminho. Será usado na tampa principal.

#4 COOLER E RODAS
  
Rodas de 6 polegadas serão a parte que trará movimento ao nosso robo. O Cooler é o corpo da nossa criação.


#5 RESISTOR

 

Componentes eletrônicos cuja principal função é limitar o fluxo de cargas elétricas por meio da conversão da energia elétrica em energia térmica. Os resistores são geralmente feitos a partir de materiais dielétricos, de grande resistência elétrica.

#6 LED
 

O LED é um componente eletrônico semicondutor, ou seja, um diodo emissor de luz ( L.E.D = Light emitter diode ), mesma tecnologia utilizada nos chips dos computadores, que tem a propriedade de transformar energia elétrica em luz.

#7 PONTE   H
 

Ponte H é um circuito de eletrônica de potência do tipo chopper de classe E, e, portanto, pode determinar o sentido da corrente, a polaridade da tensão e a tensão em um dado sistema ou componente. 
Aplicativos de software e serviços online

#SOFTWARES

#Arduino  IDE -
É um software de código aberto usado para escrever códigos e carregá-lo para a placa Arduino ou para placa ESP32 no nosso caso.

 
#MQTT Dashboard - 
O MQTT Dash é um app grátis para Android que possibilita criar dashboards com foco em Automação residencial. Ele possui diversos widgets prontos para usar e configurar para sua aplicação MQTT no seu smartphone ou tablet Android.

 
#MQTT Box - 
O MQTTBox é uma ferramenta de desenvolvedor que facilita o monitoramento do seu servidor MQTT. Você pode assinar e publicar tópicos usando o MQTTBox, bem como criar um dispositivo MQTT virtual para teste e depuração. Foi utilizado no projeto principalmente para testar o código e comunicação MQTT antes de efetivamente transferir o código para a placa ESP32.


#Protocolos de comunicação
A comunicação do COOLERBOT via MQTT broker é feita da seguinte maneira: utilizando o Arduino IDE a publicação e o recebimento de dados são feitos através do servidor broker ("broker.hivemq.com") que é um servidor gratuito. O Publisher (tiagosilva/carrinho) transmite a mensagem, o Subscriber que é o inscrito, recebe a mensagem é o receptor. O Subscriber (tiagosilva/carrinho) recebe os comandos de direção do carrinho e responde, o (tiagosilva/cooler) recebe os sinais do sensor do cooler e responde. 
