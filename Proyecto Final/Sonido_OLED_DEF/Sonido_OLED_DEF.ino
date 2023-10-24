
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
Adafruit_SSD1306 _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ANALOG_INPUT_PIN = A0;
const int MIN_ANALOG_INPUT = 0;
const int MAX_ANALOG_INPUT = 1023;
const int DELAY_LOOP_MS = 5; 

// Se define la estructura de datos a utilizar: buffer circular (cola circular)
int _circularBuffer[SCREEN_WIDTH]; 
int _curWriteIndex = 0; 


boolean _drawStatusBar = true; 
int _graphHeight = SCREEN_HEIGHT;

void setup() {
  Serial.begin(9600);

  if (!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Se inicializa y se prueba la pantalla
  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(WHITE, BLACK);
  _display.setCursor(0, 0);
  _display.println("Screen initialized!");
  _display.display();
  delay(500);
  _display.clearDisplay();

  if(_drawStatusBar){
    _graphHeight = SCREEN_HEIGHT - 10;
  }

}

void loop() {

  _display.clearDisplay();

  // Se lee y se guarda el valor análogo
  int analogVal = analogRead(ANALOG_INPUT_PIN);
  // Se inserta el valor en la estructura de datos
  _circularBuffer[_curWriteIndex++] = analogVal;

  if(_curWriteIndex >= _display.width()){
    _curWriteIndex = 0;
  }
  
  if(_drawStatusBar){
    drawStatusBar(analogVal);
  }
  
  // Dibuja el diagrama de barrascon base en los valores analógicos almacenados en la estrucutura de datos
  int xPos = 0; 
  for (int i = _curWriteIndex; i < _display.width(); i++){
    int analogVal = _circularBuffer[i];
    drawLine(xPos, analogVal);
    xPos++;
  }
  
  for(int i = 0; i < _curWriteIndex; i++){
    int analogVal = _circularBuffer[i];
    drawLine(xPos, analogVal);
    xPos++;;
  }
  
  _display.display();
}

/**
 * Dibuja la línea en la dada la posición x y el valor análogo
 */
void drawLine(int xPos, int analogVal){
  int lineHeight = map(analogVal, MIN_ANALOG_INPUT, MAX_ANALOG_INPUT, 0, _graphHeight);
  int yPos = _display.height() - lineHeight;
  _display.drawFastVLine(xPos, yPos, lineHeight, SSD1306_WHITE);
}


/**
 * Dibuja la barra en la parte superior con el valor analógico   
 */
void drawStatusBar(int analogVal) {

   // Resetea la barra dibujando negro
  _display.fillRect(0, 0, _display.width(), 8, SSD1306_BLACK); 
  
  // Imprime el valor analógico en la esquina superior izquierda
  _display.setCursor(0, 0);
  _display.print(analogVal);

}
