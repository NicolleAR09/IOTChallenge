//Librerias 
#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h> // La biblioteca SPI es para dispositivos que utilizan el protocolo SPI para la comunicación


RF24 radio(7, 8); // Asignación de la posición de los pines de control CE y CSN del módulo 
RF24Network network(radio); // Se incluye el radio en la red.
const uint16_t node = 00; // La dirección de los nodos se pone en formato octal. 
unsigned long data[16]; //Número de variables 


//Se inicializan las variables 
unsigned long data11; 
unsigned long data12;
unsigned long data13;


void setup() {
Serial.begin(9600);
SPI.begin();
radio.begin();
network.begin(90, node); //(canal, dirección del nodo)
radio.setDataRate(RF24_250KBPS); //Se establece la velocidad de transmisión 
}


void loop() {

network.update();

// Ciclo donde se revisa que esten llegando paquetes de datos 
while ( network.available() ) { 
  RF24NetworkHeader header;

  // Se lee la información que llega 
  network.read(header, &data, sizeof(data)); 

  //Condición para obtener la información adquirida del nodo 1
  if (header.from_node == 1) { 
    data11= data[0]; 
    data12= data[1];
    data13= data[2];
    Serial.print("     ");
    //Serial.print(",");
    Serial.print("N1");
    //Serial.print(",");
    Serial.print("                   ");
    Serial.print(data11);
    //Serial.print(",");
    Serial.print("                           ");
    Serial.print(data12);
    //Serial.print(",");
    Serial.print("                            ");
    Serial.print(data13);
    Serial.print(",");
    Serial.println();
    

    // Dependiendo de un valor de umbral de humedad de la tierra se enciende la motobomba 
  if (data[2] < 35) { 
    //Serial.println("Se enciende la motobomba"); // Enciende la motobomba
  } 

  // Dependiendo de un valor de umbral de humedad de la tierra se apaga la motobomba 
  if (data[2] > 35) { 
    //Serial.println("Se apaga la motobomba"); // Apaga la motobomba
  } 

  //Serial.println("                   ");

 
  }


}
}


