#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 40 // Pino utilizado para controle do LED azul
#define led_verde 48 // Pino utilizado para controle do LED verde
#define led_vermelho 36 // Pino utilizado para controle do LED vermelho
#define led_amarelo 1 // Pino utilizado para controle do LED amarelo

const int buttonPin = 18;  // Número do pino do botão
int buttonState = 0;  // Variável para ler o estado do botão

const int ldrPin = 4;  // Número do pino do sensor LDR
int threshold = 600;   // Limite para detecção de luz ambiente

void setup() {

  // Configuração inicial dos pinos para controle dos LEDs como OUTPUTs (saídas) do ESP32
  pinMode(led_azul, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(buttonPin, INPUT); // Inicializa o pino do botão como entrada

  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para depuração via interface serial entre ESP e computador com taxa de 9600 baud

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) { 
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Confirmando que o ESP32 agora está conectado ao WiFi

  // Verifica o estado do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if (WiFi.status() == WL_CONNECTED) { // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do resultado da requisição HTTP

    if (httpResponseCode > 0) {
      Serial.print("Código de resposta HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } 
    else {
      Serial.print("Código de erro: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } 
  else {
    Serial.println("WiFi desconectado");
  }
}

void loop() {
  int ldrstatus = analogRead(ldrPin);

  if (ldrstatus <= threshold) {
    Serial.print("Está escuro, ligando o LED. Leitura LDR: ");
    Serial.println(ldrstatus);
    digitalWrite(led_amarelo, HIGH);
    delay(1000);
    digitalWrite(led_amarelo, LOW);
    delay(1000);

  } else {
    Serial.print("Está claro, desligando o LED. Leitura LDR: ");
    Serial.println(ldrstatus);
    verde 3
    digitalWrite(led_verde, HIGH);
    delay(3000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_vermelho, HIGH);
    delay(5000);
    digitalWrite(led_vermelho, LOW);
  }
}
