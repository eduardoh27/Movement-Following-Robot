/*
Ejemplo grafica xy en movimiento con escala en pantalla 
OLED 128x64 I2C con el driver SSD1306.

Este ejemplo es de dominio publico hagan lo que quieran con el :D
Autor: Sergio A. Yañez M.
Año: 2020
Tutorial para el canal AQUILES VAESA 
youtube.com/aqulesvaesa

***** CONEXIONES *****

DISPLAY - ARDUINO
    GND = GND
    VCC = 5V ó 3.3V
    SCL = A5
    SDA = A4

POT.  - ARDUINO 
    1 = GND
    2 = A0
    3 = 5V

Importante!!! necesitas instalar estas librerias:
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_SSD1306

*/


#include <SPI.h>
#include <Wire.h>
#include "imagenes.h"
#include <Adafruit_SSD1306.h>  // incluye la libreria de adafruit para el driver del display OLED
#include <Adafruit_GFX.h>  // incluye la libreria de adafruit para gestionar los efectos graficos de manera facil

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3D

//Adafruit_SSD1306 display(128, 64);  // declara la resolucion del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };




int anteriorMillis = 0;
int tiempo = 0;
float valorAnalogico = 0;
float voltaje = 0;
float graficaVoltaje = 0;

int x[128]; //buffer de la grafica 
int y[128]; //buffer secundario de la grafica 


void setup(){        
          
  Serial.begin(9600);

  delay(100);  // se da una espera de 100ms para que el display inicie correctamente
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicia la comunicacion I2C con el display que tiene la direccion 0x3C
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds


  // Clear the buffer
  display.clearDisplay();
  
  
  display.setRotation(0);  // se escoje la orientacion del display puede ser 0 o 2
  display.dim(true); //dejamos el brillo en maximo
  display.setTextColor(WHITE);
  display.setTextSize(1);  // ajusta el tamaño de texto en el minimo valor


  //animacion inicial
  for(int i=0;i<1;i++){
    display.clearDisplay();  // limpia el buffer del display
    display.drawBitmap(0,0,imagen, 128, 64, 1); // despliega imagen
    display.display(); // muestra la informacion del buffer en la pantalla 
    delay(3000); //pausa 
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(0,0,imagen, 128, 64, 0); // despliega imagen en negativo
    display.display(); // muestra la informacion del buffer en la pantalla 
    delay(1000); //pausa 
    display.clearDisplay(); //limpia buffer
    display.display(); //muestra el buffer limpio
  }

  //llenamos las matrices con un valor fuera del rango de medicion >1023
  for(int i=127;i>=0;i--){
    x[i]=9999;
  }
  for(int i=127;i>=0;i--){
    y[i]=9999;
  }
} 

/*
void loop(){

  display.clearDisplay(); //limpia el buffer del display
  
  //dibuja escala
  display.setCursor(0, 0); 
  display.print(F("5V")); 
  display.setCursor(0, 11);   
  display.print(F("4V"));
  display.setCursor(0, 22); 
  display.print(F("3V"));
  display.setCursor(0, 32);  
  display.print(F("2V"));      
  display.setCursor(0, 43); 
  display.print(F("1V")); 

  display.drawLine(15, 0, 25, 0, WHITE);
  display.drawLine(15, 11, 25, 11, WHITE);
  display.drawLine(15, 22, 25, 22, WHITE);
  display.drawLine(15, 32, 25, 32, WHITE);
  display.drawLine(15, 43, 25, 43, WHITE);
  //dibuja eje X y Y 
  display.drawLine(0, 53, 127, 53, WHITE);
  display.drawLine(25, 53, 25, 0, WHITE);
 
  valorAnalogico = analogRead(A0); //lee el valor analogico del pin A0
  voltaje=(valorAnalogico*5)/1024; //calcula el valor en voltaje
  graficaVoltaje=map(valorAnalogico,0,1023,53,0); //escala el valor analogico a un pixel imprimible en pantalla

  x[127]=graficaVoltaje; //asigna el valor escalado a el ultimo dato de la matriz
  
  for(int i=127;i>=25;i--){ 
      display.drawPixel(i, x[i], WHITE); //dibuja punto a punto el contenido de x
      y[i-1]=x[i]; //guarda la informacion desplazada una posicion temporalmente en y
    }
  //imprime el voltaje en texto  
  display.setCursor(25, 57); 
  display.print(voltaje);
  display.print(F(" v    "));

  //imprime el tiempo que se tarda en tomar y mostrar cada dato
  tiempo = millis()-anteriorMillis;
  display.print(tiempo);
  anteriorMillis = millis();
  display.print(F(" ms"));
    
  display.display(); //despliega la informacion del buffer en la pantalla
  
  //delay(60); //pausa opcional

  for(int i=127;i>=0;i--){
    x[i]=y[i]; //envia los datos desplazados de vuelta a la variable x
  }
}
*/

void loop() {
}
