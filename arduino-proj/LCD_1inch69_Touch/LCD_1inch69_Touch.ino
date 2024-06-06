#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"
#include "CST816S.h"
// #include <SPI.h>
// #include <SD.h>

#define TOUCH_IRQ 3
CST816S touch(-1, -1, 4, TOUCH_IRQ);	// sda, scl, rst, irq
void drawSadness(){
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, LBBLUE);
    Paint_Clear(LBBLUE);

    // Draw two black circles for the eyes
    Paint_DrawCircle(80, 100, 10, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(160, 100, 10, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw a black arc for the frown
    // Paint_DrawLine(95, 165, 105, 155, BLACK, DOT_PIXEL_6X6, LINE_STYLE_SOLID);
    // Paint_DrawLine(105, 155, 135, 155, BLACK, DOT_PIXEL_6X6, LINE_STYLE_SOLID);
    // Paint_DrawLine(135, 155, 145, 165, BLACK, DOT_PIXEL_6X6, LINE_STYLE_SOLID);
    
    Paint_DrawLine(85, 165, 95, 155, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(95, 155, 145, 155, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(145, 155, 155, 165, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);

    // Draw the text "Sadness" at the bottom of the face
    Paint_DrawString_EN(90, 200, "Sad", &Font24, WHITE, BLACK);
}
void drawJoy(){
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, GREEN);
    Paint_Clear(GREEN);

    Paint_DrawCircle(80, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(160, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw a black arc for the smile
    Paint_DrawLine(95, 155, 105, 165, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(105, 165, 135, 165, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(135, 165, 145, 155, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);

    // Draw the text "Joy" at the bottom of the face
    Paint_DrawString_EN(95, 200, "Joy", &Font24, WHITE, BLACK);
}
void drawAnger(){
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, RED);
    Paint_Clear(RED);

    // Draw two separate thick, downward-slanting eyebrows
    Paint_DrawLine(80, 80, 110, 100, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(130, 100, 160, 80, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);

    // Draw two small black circles for the eyes
    Paint_DrawCircle(100, 110, 10, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(140, 110, 10, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw a sharply curved downward mouth
    Paint_DrawLine(90, 170, 120, 150, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    // Paint_DrawLine(120, 150, 140, 150, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(120, 150, 150, 170, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);

    // Draw the text "Anger" at the bottom of the face
    Paint_DrawString_EN(80, 200, "Anger", &Font24, WHITE, BLACK);
}

void drawFear(){
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, GRAY);
    Paint_Clear(GRAY);

    // Draw two large black circles for the eyes

    Paint_DrawCircle(100, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(140, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw smaller white circles inside the eyes to represent dilated pupils
    Paint_DrawCircle(105, 100, 10, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(135, 100, 10, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw a wavy mouth that curves downwards at both ends
    Paint_DrawLine(85, 160, 110, 150, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(110, 150, 130, 160, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(130, 160, 150, 150, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);
    Paint_DrawLine(150, 150, 170, 160, BLACK, DOT_PIXEL_4X4, LINE_STYLE_SOLID);


    // Draw the text "Fear" at the bottom of the face
    Paint_DrawString_EN(90, 200, "Fear", &Font24, WHITE, BLACK);
}
void drawSurprise(){
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, YELLOW);
    Paint_Clear(YELLOW);

    // Draw two large white circles for the eyes with black outlines
    Paint_DrawCircle(80, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawCircle(160, 100, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawCircle(80, 100, 15, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(160, 100, 15, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw two smaller black circles inside the eyes for the pupils
    Paint_DrawCircle(80, 100, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawCircle(160, 100, 5, BLACK, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    // Draw an open mouth in an 'O' shape
    Paint_DrawCircle(120, 140, 20, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);

    // Draw the text "Surprise" at the bottom of the face
    Paint_DrawString_EN(55, 200, "Surprise", &Font24, WHITE, BLACK);
}
const int bufferSize = 128; // Adjust the size as needed
byte buffer[bufferSize];
void setup()
{
    Config_Init();
    touch.begin();
    
    // if (!SD.begin(4)) {
    //   Serial.println("initialization failed!");
    //   return;
    // }
    // Serial.println("initialization done.");

    attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ), touchISR, RISING);
    LCD_Init();

    LCD_SetBacklight(100);
    
//UNO has limited memory and demo can only be run individually  UNO内存有限，demo只能单个运行 
    // Demo1(); 
    // Demo2();
    // Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    // Paint_Clear(WHITE);
    
}


void loop()
{
    drawJoy();
    delay(5000);
    drawSurprise();
    delay(5000);
    drawAnger();
    delay(5000);
    drawFear();
    delay(5000);
    drawSadness(); 
    delay(5000);
}

void touchISR(void)
{
  touch.handleISR();
}

void drawJoyEmoji() {
  
  // Set text size and color
    Paint_DrawRectangle(0, 0, Paint.Width, Paint.Height, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    
    // Draw face (circle)
    Paint_DrawCircle(Paint.Width / 2, Paint.Height / 2, Paint.Height / 3, YELLOW, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    
    // Draw eyes (circles)
    Paint_DrawCircle(Paint.Width / 2 - 20, Paint.Height / 2 - 20, 10, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(Paint.Width / 2 + 20, Paint.Height / 2 - 20, 10, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    
    // Draw mouth (arc)
    Paint_DrawLine(Paint.Width / 2 - 30, Paint.Height / 2 + 20, Paint.Width / 2 + 30, Paint.Height / 2 + 20, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(Paint.Width / 2 - 30, Paint.Height / 2 + 21, Paint.Width / 2 + 30, Paint.Height / 2 + 21, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

}

void Demo1(void)
{
#if 1
    // Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, WHITE);
    // Paint_Clear(WHITE);
    // Paint_DrawImage(gImage_70X70, 80, 50, 160, 128); 
    
    // // File imgFile = SD.open("joy.png", FILE_READ); // Replace with your image file name
    
    // // // Check if the image file is available
    // // if (!imgFile) {
    // //   Serial.println("Image file not found!");
    // //   return;
    // // }

    // // int bytesRead;
    // // int x = 0, y = 0; // Start coordinates for the image
    // // while ((bytesRead = imgFile.read(buffer, bufferSize)) > 0) {
    // //   for (int i = 0; i < bytesRead; i += 2) { // 2 bytes per pixel
    // //     // Combine two bytes to form one pixel color (assuming 16-bit color)
    // //     uint16_t color = buffer[i] << 8 | buffer[i + 1];
        
    // //     // Draw the pixel at the current position
    // //     Paint_SetPixel(x, y, color);
        
    // //     // Move to the next pixel
    // //     x++;
    // //     if (x >= LCD_WIDTH) {
    // //       x = 0;
    // //       y++;
    // //     }
    // //   }
    // // }
    
    // // // Close the file
    // // imgFile.close();
    // delay(3000);
#endif
}

void Demo2(void)
{
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);

  Paint_DrawString_EN(35, 90, "Gesture test", &Font20, BLACK, WHITE);
  Paint_DrawString_EN(10, 120, "Complete as prompted", &Font16, BLACK, WHITE);
  DEV_Delay_ms(500);
  Paint_ClearWindows(10,90,230,137,WHITE);
  Paint_DrawString_EN(105, 120, "UP", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != SWIPE_UP){
    touch.available();
    DEV_Delay_ms(10);
  } 
  Paint_ClearWindows(105,120,160,155,WHITE);

  Paint_DrawString_EN(85, 120, "DOWN", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != SWIPE_DOWN){
    touch.available();
    DEV_Delay_ms(10);
  } 
  Paint_ClearWindows(85,120,160,155,WHITE);

  Paint_DrawString_EN(85, 120, "LEFT", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != SWIPE_LEFT){
    touch.available();
    DEV_Delay_ms(10);
  } 
  Paint_ClearWindows(85,120,160,155,WHITE);

  Paint_DrawString_EN(80, 120, "RIGHT", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != SWIPE_RIGHT){
    touch.available();
    DEV_Delay_ms(10); 
  } 
  Paint_ClearWindows(80,120,165,155,WHITE);

  Paint_DrawString_EN(40, 120, "Long Press", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != LONG_PRESS){
    touch.available();
    DEV_Delay_ms(10);
  } 
  Paint_ClearWindows(40,120,220,155,WHITE);

  Paint_DrawString_EN(15, 120, "Double Click", &Font24, BLUE, CYAN);
  while(touch.data.gestureID != DOUBLE_CLICK){   
    touch.available();
    Serial.println( touch.data.gestureID );
    DEV_Delay_ms(10);
  } 
  Paint_ClearWindows(15,120,240,155,WHITE);
  Paint_DrawPoint(120,140, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
}
  
/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

// #include <SPI.h>
// #include <SD.h>

// File myFile;

// void setup() {
//   // Open serial communications and wait for port to open:
//   Serial.begin(9600);
//   while (!Serial) {
//     ; // wait for serial port to connect. Needed for native USB port only
//   }


//   Serial.print("Initializing SD card...");

//   if (!SD.begin(4)) {
//     Serial.println("initialization failed!");
//     while (1);
//   }
//   Serial.println("initialization done.");

//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   myFile = SD.open("test.txt", FILE_WRITE);

//   // if the file opened okay, write to it:
//   if (myFile) {
//     Serial.print("Writing to test.txt...");
//     myFile.println("testing 1, 2, 3.");
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
//   if (SD.exists("joy-c.bin")) //check for existing or duplicate file names
//    {
//     Serial.println("File exists");
//    }
//    else
//   Serial.println("File does not exist");

//   // re-open the file for reading:
//   myFile = SD.open("test.txt");
//   if (myFile) {
//     Serial.println("test.txt:");

//     // read from the file until there's nothing else in it:
//     while (myFile.available()) {
//       Serial.write(myFile.read());
//     }
//     // close the file:
//     myFile.close();
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
// }

// void loop() {
//   // nothing happens after setup
// }



