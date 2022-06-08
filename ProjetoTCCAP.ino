/*Aula: https://www.youtube.com/watch?v=P7zbMjrBehg&t=28s */

//Bibliotecas 
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char* ssid = "TCC"; // Identificador da rede
const char* password = "tccplaca1"; //senha

WiFiServer server (80); //Inicializa o servidor na porta 80 com o objeto server

void setup() {
  Serial.begin(115200);

  IPAddress staticIP(192, 168, 4, 2);//IP estático é exigido como parâmetro em WiFi.config
  IPAddress geteway(192, 168, 4, 1);//Gateway, IP que permite acesso ao Wemos
  IPAddress subnet(255, 255, 255, 0);//Subnet da rede

  WiFi.mode(WIFI_AP);//Deixa o Wemos no modo access point
  WiFi.softAP(ssid, password, 2, 0);//Identificados, senha, canal 2, não deixar a rede oculta 0
  WiFi.config(staticIP, geteway, subnet);//Configuração da rede

  server.begin();//Inicializar o servidor

  Serial.println("Server started");
  Serial.println(WiFi.softAPIP());//Imprime o gateway
  

}

void loop() {
 
  WiFiClient client = server.available();//Cria um objeto cliente e verifica se tem alguem disponível
  
  //Se não tiver cliente printa e retorna ao void loop
  if(!client){
    Serial.println("Não tem cliente");
    delay(2000);
    return;
  }

  //Enquanto o cliente não pedir nada printa e mantem no while. Se possivel usar millis e não delay
  while(!client.available()){
    Serial.println("Tem cliente, aguardando requisição");
    delay(2000);
  }

  String requisicao = client.readStringUntil('\r');//Lê tudo o que o cliente enviou
  /*Teste de tratamento da requisição ensinado na aula onde o link está na linha 1 do código
  Serial.println(requisicao.indexOf("/") + 1); retorna o valor do índice da string + 1
  Serial.println(requisicao.indexOf("HTTP") - 1); retorna o valor do índice string - 1
  Serial.println(requisicao.substring(requisicao.indexOf("/") + 1, requisicao.indexOf("HTTP") - 1));*/
  
  /* Teste de tratamento da requisição utilizando o exemplo com APPInventor 
  requisicao.remove(0, 5);
  requisicao.remove(requisicao.length()-9, 9);
  Serial.println(requisicao);*/
  
  //Serial.println(requisicao);//192.168.4.1/ligar -> GET /ligar HTTP/1.1   192.168.4.1 -> GET / HTTP/1.1

  requisição = requisicao.substring(requisicao.indexOf("/") + 1, requisicao.indexOf("HTTP") - 1);//Corta a string com o dado necessário para as decisões
  client.flush();//Limpa o client












  
   

}
