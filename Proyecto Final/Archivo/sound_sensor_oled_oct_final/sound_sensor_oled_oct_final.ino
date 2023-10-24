
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 

int sound =A0;
 
const int sampleWindow = 50;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 

 
void setup() 
{
   Serial.begin(115200);                                    //Serial comms for debugging
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);              //OLED display start
   display.display();                                     //show buffer
   display.clearDisplay();                                //clear buffer
   display.setTextSize(2);                                //Set text size to 1 (1-6)
   display.setTextColor(WHITE);                           //Set text color to WHITE (no choice lol)
   display.setCursor(0,0);                                //cursor to upper left corner
   display.println("Sound");
   
    display.setCursor(67,0);
    display.println("Meter");               //write title
   display.display();                                     //show title
   delay(2000);                                           //wait 2 seconds
 
   
}
//--------------------------------------------------------------------------------------------
 //                                         MAIN LOOP
 //--------------------------------------------------------------------------------------------
  
void loop() 
{
   unsigned long startMillis= millis();                   // Start of sample window
   float peakToPeak = 0;                                  // peak-to-peak level
 
   unsigned int signalMax = 0;                            //minimum value
   unsigned int signalMin = 1024;                         //maximum value

                                                          // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);                             //get reading from microphone
      if (sample < 1024)                                  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;                           // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;                           // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
   float db = map(peakToPeak,000,460,40,90);             //calibrate for deciBels
   display.setCursor(8,25);                                //cursor to upper left
   display.setTextSize(2);                                //set text size to 2
   display.print(db);                                     //write calibrated deciBels
   display.print(" dB");
    display.setCursor(3,48); 
   display.setTextSize(1); 
   display.print("Analog Reading");
   
    display.setCursor(95,48);
  
     display.print(analogRead(sound));
   int r = map(db,0,80,1,120);                           //set bar graph for width of screen
   display.fillRoundRect(1, 1, r, 15, 0, WHITE);         //draw bar graph with a width of r
   display.display();                                     //show all that we just wrote & drew
   display.clearDisplay();                                //clear the display

   
}
