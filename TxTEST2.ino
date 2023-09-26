// Librerías 
#include <Arduino.h>
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <DHT.h>

// Se define el pin digital donde se conecta el sensor de temperatura y humedad DHT11
#define DHTPIN 2
// Se de fine el tipo de sensor
#define DHTTYPE DHT11
// Se inicializa el sensor 
DHT dht(DHTPIN, DHTTYPE);
// Configurar pin del sensor de humedad de la tierra
const int sensorPin = A0;
// Se define pin digital al que está conectada la bomba de agua 
const int bomb_pin = 4;

RF24 radio(7, 8); // Asignación de la posición de los pines de control CE y CSN del módulo 
RF24Network network(radio);     // Incluir la radio en la red
const uint16_t node = 01;  // Id del nodo en formato octal 
const uint16_t node_RX = 00; // Nodo receptor 
unsigned long data[16]; 

void setup() {
  Serial.begin(9600);
  dht.begin(); // Se inicializa el sensor DHT11
  SPI.begin();
  radio.begin();
  network.begin(90, node);  //(canal, dirección del nodo)
  radio.setDataRate(RF24_250KBPS);
  pinMode(bomb_pin, OUTPUT); // Se inicializa pin de la bomba de agua como salida 
}

void loop() {
  delay(3000); // Se esperan 3 segundos cada que se manda un dato

  // Lectura de la humedad del DHT11
  float h = dht.readHumidity(); 
  // Lectura de la temperatura en grados Celcius
  float t = dht.readTemperature();
  // Leer el valor analógico del sendor HL 69
  int humt = analogRead(sensorPin);
  // Mapea el valor leído a un rango de humedad (ajusta los valores según tus resultados)
  int humt_map = map(humt, 0, 1023, 0, 100);

  // Se comprueba si ha habido algún error en la lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  network.update();
  data[0] = t;
  data[1] = h;
  data[2] = humt_map;
  RF24NetworkHeader header8(node_RX);
  bool ok = network.write(header8, &data, sizeof(data));  // Se envía la data

  // Dependiendo de un valor de umbral de humedad de la tierra se enciende la motobomba 
  if (data[2] < 35) { 
    digitalWrite(bomb_pin, HIGH); // Enciende la motobomba
  } 

  // Dependiendo de un valor de umbral de humedad de la tierra se apaga la motobomba 
  if (data[2] > 35) { 
    digitalWrite(bomb_pin, LOW); // Apaga la motobomba
  } 
}


