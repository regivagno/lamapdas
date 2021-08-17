Acionamento de Rele ESP8266 - Adafruit IO
 * Por: Regivagno Paixão
 * OBS: Essa programação é uma adaptacao de um programa de Fábio Souza

//Equivalencia das saidas Digitais entre NodeMCU e ESP8266 (na IDE do Arduino)
NodeMCU - ESP8266
D0 = 16;
D1 = 5;
D2 = 4;
D3 = 0;
D4 = 2;
D5 = 14;
D6 = 12;
D7 = 13;
D8 = 15;
D9 = 3;
D10 = 1;

/************************ Configurações do Adafruit IO *******************************/
//Insira seu nome de usuário e chave. Você encontra essas informações acessando
//sua conta no Adafruit IO
#define IO_USERNAME "regivagno"
#define IO_KEY "Regi@3022"
 
/********************* Configuração do WIFI **************************************/
 
//Insira o SSID e Senha da rede WIFI a qual você irá conectar
#define WIFI_SSID "Regi Gesilene 2.4G"
#define WIFI_PASS "22041991"
 
 
/***************Configurações do comunicaçaão************/
#include "AdafruitIO_WiFi.h"
 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
 
/************************ Mapeamento de IO *******************************/
#define RELE1 4   //pino de saida para acionamento da Lampada L1
#define RELE2 0   //pino de saida para acionamento da Lampada L2
#define RELE3 2   //pino de saida para acionamento da Lampada L3
#define RELE4 14   //pino de saida para acionamento da Lampada L4
#define RELE5 12   //pino de saida para acionamento da Lampada L5

 
/************************ Configuração dos tópicos *******************************/
 
// configura o tópico "fs_embarcados/feeds/minha-casa"
AdafruitIO_Feed *feedRele1 = io.feed("minha-casa");
 
 
/************************ Função setup *******************************/
 
void setup() {
 
  //configura pino da Lampada como saída
  pinMode(RELE1,OUTPUT);
  pinMode(RELE2,OUTPUT);
  pinMode(RELE3,OUTPUT);
  pinMode(RELE4,OUTPUT);
  pinMode(RELE5,OUTPUT);
 
  // configura comunicação serial
  Serial.begin(115200);
 
  // Aguarda serial monitor
  while(! Serial);
 
  conectaBroker(); //função para conectar ao broker
 
 
}
 
/************************ Função loop *******************************/
 
void loop() {
 
  // processa as mensagens e mantêm a conexão ativa
  byte state = io.run();
 
  //verifica se está conectado
  if(state == AIO_NET_DISCONNECTED | state == AIO_DISCONNECTED){
    conectaBroker(); //função para conectar ao broker
  }
 
}
 
/****** Função de tratamento dos dados recebidos em L1***************/
 
void handleRele1(AdafruitIO_Data *data) {
 
  // Mensagem
  Serial.print("Recebido  <- ");
  Serial.print(data->feedName());
  Serial.print(" : ");
  Serial.println(data->value());
 
  //Aciona saída conforme dado recebido
  if(data->isTrue())
    digitalWrite(RELE1, HIGH);
    digitalWrite(RELE2, HIGH);
    digitalWrite(RELE3, HIGH);
    digitalWrite(RELE4, HIGH);
    digitalWrite(RELE5, HIGH);
  else
    digitalWrite(RELE1, LOW);
    digitalWrite(RELE2, LOW);
    digitalWrite(RELE3, LOW);
    digitalWrite(RELE4, LOW);
    digitalWrite(RELE5, LOW);
}
 
 
/****** Função para conectar ao WIFI e Broker***************/
 
void conectaBroker(){
 
  //mensagem inicial
  Serial.print("Conectando ao Adafruit IO");
 
  // chama função de conexão io.adafruit.com
  io.connect();
 
   // instancia um novo handler para recepção da mensagem do feed Rele
  feedRele1->onMessage(handleRele1);
 
  // Aguarda conexação ser estabelecida
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  // Conectado
  Serial.println();
  Serial.println(io.statusText());
 
  // certifique-se de que todos os feeds obtenham seus valores atuais imediatamente
  feedRele1->get();
}
