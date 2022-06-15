/*Aula: https://www.youtube.com/watch?v=P7zbMjrBehg&t=28s */

//Bibliotecas 
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//Váriáveis globais
bool flagInicial = 1;

const char* ssid = "TCC"; // Identificador da rede
const char* password = "tccplaca1"; //senha

WiFiServer server (80); //Inicializa o servidor na porta 80 com o objeto server

void setup() {
  Serial.begin(115200);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  IPAddress staticIP(192, 168, 4, 2);//IP estático é exigido como parâmetro em WiFi.config
  IPAddress geteway(192, 168, 4, 1);//Gateway, IP que permite acesso ao Wemos
  IPAddress subnet(255, 255, 255, 0);//Subnet da rede

  WiFi.mode(WIFI_AP);//Deixa o Wemos no modo access point
  WiFi.softAP(ssid, password, 2, 0);//Identificados, senha, canal 2, não deixar a rede oculta 0
  WiFi.config(staticIP, geteway, subnet);//Configuração da rede

  server.begin();//Inicializar o servidor

  Serial.println("Server started");
  Serial.println(WiFi.softAPIP());//Imprime o gateway
  
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
}

void loop() {
 
  WiFiClient client = server.available();//Cria um objeto cliente e verifica se tem alguem disponível
  
  //Se não tiver cliente printa e retorna ao void loop
  if(!client){
    //Serial.println("Não tem cliente");
    //delay(2000);
    return;
  }

  //Enquanto o cliente não pedir nada printa e mantem no while. Se possivel usar millis e não delay
  while(!client.available()){
    //Serial.println("Tem cliente, aguardando requisição");
    delay(1);
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

  requisicao = requisicao.substring(requisicao.indexOf("/") + 1, requisicao.indexOf("HTTP") - 1);//Corta a string com o dado necessário para as decisões
  client.flush();//Limpa o client

  //-------------------------------Página html-----------------------------------------------------

  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"pt-BR\">");
  client.println("<head>");
    client.println("<meta charset=\"UTF-8\">");
    client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    client.println("<title>Interface de controle</title>");
    client.println("<link href=\"https://fonts.googleapis.com/css2?family=Ubuntu:wght 300&display=swap\" rel=\"stylesheet\">");
    client.println("<style>" );
      client.println("*{");
        client.println("margin: 0;");
        client.println("padding: 0;");
        client.println("box-sizing: border-box; font-family: 'Ubuntu', sans-serif;");
      client.println("}" );
      client.println("header");
      client.println("{");
        client.println("width: 100%;");
        client.println("background-color: mediumblue;");
        client.println("display: flex;");
        client.println("align-items: center;" );
      client.println("}");
      client.println("header .title");
      client.println("{");
        client.println("color: white;");
        client.println("font-size: 40px;");
        client.println("margin: auto;");
      client.println("}");
      client.println(".container");
      client.println("{");
        client.println("width: 100%;");
        client.println("max-width: 1300px;");
        client.println("margin: 0 auto;");
        client.println("display: flex;");
      client.println("}");
      client.println("section");
      client.println("{");
        client.println("background-color: rgb(29, 29, 37);");
        client.println("padding: 20px;");
      client.println("}");
      client.println("section .item-head");
      client.println("{");
        client.println("display: flex;");
        client.println("justify-content: space-between;");
      client.println("}");
      client.println("section .titulo");
      client.println("{");
        client.println("color: white;");
        client.println("font-size: 20px;");
      client.println("}");
      client.println(".on");
      client.println("{");
        client.println("font-size: 15px;");
        client.println("padding: 2px;");
        client.println("margin: auto;");
        client.println("background-color: rgb(20, 237, 20);");
      client.println("}");
      client.println(".off");
      client.println("{");
        client.println("font-size: 15px;");
        client.println("padding: 2px;");
        client.println("margin: auto;");
        client.println("background-color: rgb(237, 20, 20);");
      client.println("}");
      client.println("section .acoes");
      client.println("{");
        client.println("width: 100%;");
        client.println("padding-top: 20px;");
        client.println("display: flex;");
        client.println("justify-content: space-between;");
      client.println("}");
      client.println("section .acoes .avancar");
      client.println("{" );
        client.println("width: 50%;");
        client.println("height: 40px;");
        client.println("background-color: rgb(27, 163, 3);");
        client.println("display: flex;");
        client.println("justify-content: center;");
        client.println("align-items: center;");
        client.println("text-decoration: none;");
        client.println("font-size: 15px;");
        client.println("color: white;");
        client.println("margin-right: 10px;");
        client.println("transition: all 0.2s;");
      client.println("}");
      client.println("section .acoes .avancar:hover");
      client.println("{" );
        client.println("background-color: rgb(63, 155, 47);");
      client.println("}");
      client.println("section .acoes .pararavanco");
      client.println("{");
        client.println("width: 50%;");
        client.println("height: 40px;");
        client.println("background-color: rgb(163, 3, 3);");
        client.println("display: flex; justify-content: center;");
        client.println("align-items: center;");
        client.println("text-decoration: none;");
        client.println("font-size: 15px;");
        client.println("color: white;");
        client.println("margin-left: 10px;");
        client.println("transition: all 0.2s;" );
      client.println("}");
      client.println("section .acoes .pararavanco:hover");
      client.println("{");
        client.println("background-color: rgb(161, 55, 55);");
      client.println("}");
      client.println("section .acoes .recuar");
      client.println("{");
        client.println("width: 50%;"); 
        client.println("height: 40px;"); 
        client.println("background-color: rgb(27, 163, 3);"); 
        client.println("display: flex;");
        client.println("justify-content: center;"); 
        client.println("align-items: center;"); 
        client.println("text-decoration: none;"); 
        client.println("font-size: 15px;"); 
        client.println("color: white;"); 
        client.println("margin-right: 10px;"); 
        client.println("transition: all 0.2s;");
      client.println("}");
      client.println("section .acoes .recuar:hover");
      client.println("{");
        client.println("background-color: rgb(63, 155, 47);");
      client.println("}");
      client.println("section .acoes .pararrecuo");
      client.println("{");
        client.println("width: 50%;"); 
        client.println("height: 40px;"); 
        client.println("background-color: rgb(163, 3, 3);"); 
        client.println("display: flex;"); 
        client.println("justify-content: center;"); 
        client.println("align-items: center;"); 
        client.println("text-decoration: none;"); 
        client.println("font-size: 15px;"); 
        client.println("color: white;"); 
        client.println("margin-left: 10px;"); 
        client.println("transition: all 0.2s;");
      client.println("}");
      client.println("section .acoes .pararrecuo:hover");
      client.println("{");
        client.println("background-color: rgb(161, 55, 55);");
      client.println("}");
      client.println("footer");
      client.println("{");
        client.println("width: 100%;");
        client.println("margin-top: 66%;");
        client.println("background: mediumblue;");
        client.println("display: flex;");
      client.println("}");
      client.println("footer .rodape");
      client.println("{");
        client.println("width: 400px;");
        client.println("min-height: 132px;");
        client.println("padding: 20px;");
      client.println("}");
      client.println(".rodape h2");
      client.println("{");
        client.println("color: white;");
      client.println("}");
      client.println(".rodape ul h3");
      client.println("{");
        client.println("color: white;");
      client.println("}");  
      client.println("@media(max-width: 1000px)");
      client.println("{");
        client.println("header");
        client.println("{");
          client.println("justify-content: center;");
          client.println("flex-direction: column;");
          client.println("align-items: center;");
          client.println("padding:30px 10px 20px 10px;");
        client.println("}");
        client.println(".container");
        client.println("{");
          client.println("padding: 20px;");
          client.println("flex-direction: column;");
        client.println("}");
        client.println("section");
        client.println("{");
          client.println("width: 100%;");
          client.println("margin-bottom: 20px;");
        client.println("}");
        client.println("footer");
        client.println("{");
          client.println("padding: auto;");
          client.println("flex-direction: column;");
        client.println("}");
      client.println("}");
    client.println("</style>");
  client.println("</head>");
  client.println("<body>");
    client.println("<header>");
      client.println("<div class=\"title\">FACULDADE SENAI</div>");
    client.println("</header>");
    client.println("<div class=\"container\">");
      client.println("<section>");

  //Tomadas de decisões para o movimento.
      
      //Avanço---------------------------------------------------------------------------------------------
        client.println("<div class=\"item-head\">");
          client.println("<div class=\"titulo\">Avançar Macho 1</div>");
          if(requisicao == ""){
            client.println("<div class=\"movimento off\">Parado</div>");
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
          }
          else if(requisicao == "avancar"){
            client.println("<div class=\"movimento on\">Avançando</div>");
            digitalWrite(D1, HIGH);
            digitalWrite(D2, LOW);
            digitalWrite(D3, HIGH);
          }
          else if(requisicao == "parar"){
            client.println("<div class=\"movimento off\">Parado</div>");
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
          }
          else if(requisicao == "recuar"){
            client.println("<div class=\"movimento off\">Recuando</div>");
          }
          //client.println("<div class=\"movimento on\">Parado</div>");
        client.println("</div>");
        client.println("<div class=\"acoes\">");
          client.println("<a href=\"avancar\" class=\"avancar\">AVANÇAR</a>");
          client.println("<a href=\"parar\" class=\"pararavanco\">PARAR</a>");
        client.println("</div>");
      client.println("</section>");
      client.println("<section>");
      
      //Recuo---------------------------------------------------------------------------------------------
        client.println("<div class=\"item-head\">");
          client.println("<div class=\"titulo\">Recuar Macho 1</div>");
          if(requisicao == ""){
            client.println("<div class=\"movimento off\">Parado</div>");
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
          }
          else if(requisicao == "recuar"){
            client.println("<div class=\"movimento on\">Recuando</div>");
            digitalWrite(D1, LOW);
            digitalWrite(D2, HIGH);
            digitalWrite(D3, HIGH);
          }
          else if(requisicao == "parar"){
            client.println("<div class=\"movimento off\">Parado</div>");
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
          }
          else if(requisicao == "avancar"){
            client.println("<div class=\"movimento off\">Avançandogit</div>");
          }
          //client.println("<div class=\"movimento off\">Parado</div>");
        client.println("</div>");
        client.println("<div class=\"acoes\">");
          client.println("<a href=\"recuar\" class=\"recuar\">RECUAR</a>");
          client.println("<a href=\"parar\" class=\"pararrecuo\">PARAR</a>");
        client.println("</div>");
      client.println("</section>");
    client.println("</div>");
    client.println("<footer>");
      client.println("<div class=\"rodape\">");
        client.println("<h2>Trabalho de Conclusão de Curso</h2>");
        client.println("<ul>");
          client.println("<h3>Faculdade SENAI</h3>");
          client.println("<h3>Aluno: Eduardo Henrique</h3>");
          client.println("<h3>Aluno: Felipe Duarte</h3>");
        client.println(" </ul>");
      client.println("</div>");
    client.println("</footer>");
  client.println("</body>");
  client.println("</html>");
}
