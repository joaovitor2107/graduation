#include <SoftwareSerial.h>

// Pinos do Arduino
const int pirPin = 9;        // Pino conectado ao OUT do sensor PIR
const int buzzerPin = 8;     // Pino conectado ao buzzer
const int mc38Pin = 3;       // Pino conectado ao sensor MC38

unsigned long lastTriggerTime = 0;  // Para controlar o tempo entre detecções do PIR
const unsigned long debounceTime = 5000;  // Tempo mínimo entre alertas (5 segundos)

SoftwareSerial BTSerial(10, 11); // RX, TX do HC-05

void setup() {
  pinMode(pirPin, INPUT);    // Configura o PIR como entrada
  pinMode(mc38Pin, INPUT_PULLUP); // Configura o MC38 como entrada com pull-up interno
  pinMode(buzzerPin, OUTPUT); // Configura o buzzer como saída
  
  Serial.begin(9600);        // Inicializa a comunicação serial para debug
  BTSerial.begin(9600);      // Inicializa a comunicação Bluetooth
}

void loop() {
  int pirState = digitalRead(pirPin);  // Lê o estado do PIR
  int mc38State = digitalRead(mc38Pin); // Lê o estado do MC38
  unsigned long currentTime = millis();
  
  if (pirState == HIGH && (currentTime - lastTriggerTime > debounceTime) && mc38State == HIGH) {
    Serial.println("Movimento detectado! Porta/janela aberta");
    BTSerial.println("ALERTA: Intruso detectado!");  // Envia mensagem via Bluetooth
    
    digitalWrite(buzzerPin, HIGH);  // Ativa o buzzer
    delay(500);
    digitalWrite(buzzerPin, LOW);  // Desativa o buzzer
    lastTriggerTime = currentTime; // Atualiza o último tempo de ativação
  }

  delay(100);  // Pequena pausa para estabilidade
}
