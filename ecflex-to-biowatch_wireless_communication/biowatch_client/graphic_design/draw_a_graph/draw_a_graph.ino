#include <Wire.h> // I2C library
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GC9A01A.h"

#define TFT_DC 4 // SDA
#define TFT_CS 5 // SCL
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

// Hardware SPI on Feather or other boards
Adafruit_GC9A01A tft(TFT_CS, TFT_DC);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define LTBLUE 0xB6DF
#define LTTEAL 0xBF5F
#define LTGREEN 0xBFF7
#define LTCYAN 0xC7FF
#define LTRED 0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW 0xFFF8
#define LTORANGE 0xFE73
#define LTPINK 0xFDDF
#define LTPURPLE 0xCCFF
#define LTGREY 0xE71C

#define BLUE 0x001F
#define TEAL 0x0438
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00
#define PINK 0xF81F
#define PURPLE 0x8010
#define GREY 0xC618
#define WHITE 0xFFFF
#define BLACK 0x0000

#define DKBLUE 0x000D
#define DKTEAL 0x020C
#define DKGREEN 0x03E0
#define DKCYAN 0x03EF
#define DKRED 0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW 0x8400
#define DKORANGE 0x8200
#define DKPINK 0x9009
#define DKPURPLE 0x4010
#define DKGREY 0x4A49

int color = WHITE;

int xprev = 205;
int x0 = 205;
int x1 = 195;
int x2 = 185;
int x3 = 175;
int x4 = 165;
int x5 = 155;
int x6 = 145;
int x7 = 135;
int x8 = 125;
int x9 = 115;
int x10 = 105;
int x11 = 95;
int x12 = 85;
int x13 = 75;
int x14 = 65;
int x15 = 55;
int x16 = 45;
int x17 = 35;
int x18 = 25;

int yprev = 110; // yprev should be defined as the first sensor value received.
int y0y = 190;
int y1y = 110;
int y2y = 110;
int y3 = 110;
int y4 = 190;
int y5 = 190;
int y6 = 190;
int y7 = 190;
int y8 = 190;
int y9 = 190;
int y10 = 190;
int y11 = 190;
int y12 = 190;
int y13 = 190;
int y14 = 190;
int y15 = 190;
int y16 = 190;
int y17 = 190;
int y18 = 190;

int listx[19] = {x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18};
int listy[19] = {y0y, y1y, y2y, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18};

void setup()
{
  Serial.begin(115200);
  Serial.println("Start writting");
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  delay(10);

// Draw a white circle
  tft.drawCircle(120, 120, 120, WHITE);
  delay(20);
  tft.drawCircle(120, 120, 119, WHITE);
  delay(25);
  tft.drawCircle(120, 120, 118, WHITE);
  delay(30);
  tft.drawCircle(120, 120, 117, WHITE);
  delay(30);
  tft.drawCircle(120, 120, 116, WHITE);
  delay(30);
  tft.drawCircle(120, 120, 115, WHITE);
  delay(60);
  tft.drawCircle(120, 120, 114, BLACK);
  delay(30);
  tft.drawCircle(120, 120, 115, BLACK);
  delay(30);
  tft.drawCircle(120, 120, 116, BLACK);
  delay(30);
  tft.drawCircle(120, 120, 117, BLACK);
  delay(25);
  tft.drawCircle(120, 120, 118, BLACK);
  delay(20);
  tft.drawCircle(120, 120, 120, BLACK);
  delay(200);

  //  tft.drawPixel(x18, y18, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x17, y17, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x16, y16, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x15, y15, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x14, y14, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x13, y13, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x12, y12, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x11, y11, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x10, y10, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x9, y9, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x8, y8, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x7, y7, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x6, y6, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x5, y5, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x4, y4, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x3, y3, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x2, y2y, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x1, y1y, LTGREY);
  //  delay(80);
  //  tft.drawPixel(x0, y0y, LTGREY);
  //  delay(80);
  //  tft.drawPixel(xprev, yprev, LTGREY);
  //  delay(40);

  // Writte "DVIC" at the bottom of the screen
  tft.setCursor(108, 225);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.print("DVIC");
  delay(80);

  // Draw the 3 DVIC-left lines
  tft.drawFastHLine(75, 225, 30, DKGREY);
  tft.drawFastHLine(85, 228, 20, GREY);
  tft.drawPixel(84, 228, DKGREY);
  tft.drawFastHLine(98, 231, 7, WHITE);
  tft.drawPixel(97, 231, GREY);
  //  tft.drawPixel(96, 231, GREY);
  //  delay(60);

  // Draw the 3 DVIC-right lines
  tft.drawFastHLine(134, 225, 30, DKGREY);
  tft.drawFastHLine(134, 228, 20, GREY);
  tft.drawPixel(155, 225, DKGREY);
  tft.drawFastHLine(134, 231, 7, WHITE);
  tft.drawPixel(141, 231, GREY);
  delay(80);

  // Writte concentration unit
  tft.setCursor(136, 38);
  tft.setTextColor(LTGREY);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.print(" mM");

  //  tft.drawRect(25, 49, 190, 143, DKTEAL);     // Centered inner rectangle
  //  tft.drawRect(48, 24, 144, 192, DKGREY);     // Centered outer rectangle
  //  tft.drawRect(24, 48, 192, 144, DKGREY);     // Centered outer rectangle
  //  tft.drawRect(35, 35, 170, 170, DKMAGENTA);  // Large centered square, 0 pixel margin
  //  tft.drawRect(40, 40, 160, 160, DKGREY);     // Square centered with 10px margin
  //  tft.drawLine(48, 24, 192, 216, LTBLUE);    // Diagonal 1 of outer rectangle
  //  tft.drawLine(192, 24, 48, 216, LTBLUE);    // Diagonal 2 of outer rectangle
  //  tft.drawLine(0, 0, 240, 240, DKMAGENTA);     // Diagonal 1 of the large square
  //  tft.drawLine(0, 240, 240, 0, DKMAGENTA);     // Diagonal 2 of the large square
}

void loop()
{
  int listcg[] = {110, 105, 97, 86, 75, 79, 90, 100, 103, 107, 119, 126, 140, 158, 174, 176, 173, 164, 157, 150, 142, 131, 130, 128, 122, 117, 112, 110, 105, 97, 86, 77, 79, 90, 100, 103, 107, 119, 130, 147, 160, 180, 182, 176, 164, 157, 150, 142, 131, 130, 128, 122, 117, 112};
  for (int i = 0; i <= 52; i++)
  {                             // Update cg loop
    int cgreceived = listcg[i]; // Simulate a new value received
    Serial.print("cgreceived: ");
    Serial.println(cgreceived);

    // Shift the list from left to right to make room for the new y0 value
    shiftright(listy); 

    // Add y0 to the liste //
    listy[1] = converttopixel(cgreceived);

    Serial.print("The new y0 is: ");
    Serial.println(listy[0]);
    Serial.print("The new y1 is: ");
    Serial.println(listy[1]);
    Serial.print("The new y2 is: ");
    Serial.println(listy[2]);
    Serial.print("The new y3 is: ");
    Serial.println(listy[3]);

    color = WHITE;
    tft.fillRect(87, 23, 52, 21, BLACK); // Refresh the glucose concentration value printed

    tft.setCursor(87, 23);
    if (cgreceived >= 150) // High glycemia. Risk of hyperglycemic crisis
    { // 150 mMol
      color = RED;
    }
    if (cgreceived <= 100) // Low glycemia. Risk of hypoglycemic crisis
    { // 100 mMol
      color = TEAL;
    }
    tft.setTextColor(color); // color is WHITE by default
    tft.setTextSize(3);
    tft.setTextWrap(false);
    tft.print(String(cgreceived));

    for (int j = 1; j <= 19; j++)
    { // Draw pixel from x0 = 190 to x19 = 25
      color = WHITE;
      if (listy[j] <= 100)
      { // The 100th pixel correspond to 140mMol
        color = RED;
      }
      if (listy[j] >= 150)
      { // The 150th pixel correspond to 90mMol
        color = TEAL;
      }
      tft.drawPixel(listx[j], listy[j], color); // Draw pixel [xj,yj]

      tft.drawPixel(listx[j] + 1, listy[j], color); // Draw a diamond around pixel [xj,yj]
      tft.drawPixel(listx[j], listy[j] + 1, color);
      tft.drawPixel(listx[j] - 1, listy[j], color);
      tft.drawPixel(listx[j], listy[j] - 1, color);

      tft.drawPixel(listx[j] + 2, listy[j], color);
      tft.drawPixel(listx[j], listy[j] + 2, color);
      tft.drawPixel(listx[j] - 2, listy[j], color);
      tft.drawPixel(listx[j], listy[j] - 2, color);

      tft.drawPixel(listx[j] + 1, listy[j] + 1, color);
      tft.drawPixel(listx[j] - 1, listy[j] + 1, color);
      tft.drawPixel(listx[j] + 1, listy[j] - 1, color);
      tft.drawPixel(listx[j] - 1, listy[j] - 1, color);

      Serial.print("A l'itération ");
      Serial.print(i);
      Serial.print(", l'y du pixel ");
      Serial.print(j);
      Serial.print(" vaut: ");
      Serial.println(listy[j]);
    }
    // Calcul of yprev
    yprev = listy[1] + round((5 * (listy[1] - listy[2]) + 2 * (listy[2] - listy[3]) + listy[1] - listy[2]) / 8 + (listy[1] - listy[2]) / 2);

    if (yprev > 188)
    { // High limit to avoid going off screen
      yprev = 188;
    }
    if (yprev < 52)
    { // Low limit to avoid going off screen
      yprev = 52;
    }

    Serial.print("The new value of yprev is: ");
    Serial.println(yprev);

    tft.drawPixel(xprev, yprev, GREY); // Draw pixel [xprev, yprev]

    tft.drawPixel(xprev + 1, yprev, DKGREY);
    tft.drawPixel(xprev, yprev + 1, DKGREY);
    tft.drawPixel(xprev - 1, yprev, DKGREY);
    tft.drawPixel(xprev, yprev - 1, DKGREY);

    tft.drawPixel(xprev + 2, yprev, DKGREY);
    tft.drawPixel(xprev, yprev + 2, DKGREY);
    tft.drawPixel(xprev - 2, yprev, DKGREY);
    tft.drawPixel(xprev, yprev - 2, DKGREY);

    tft.drawPixel(xprev + 1, yprev + 1, DKGREY);
    tft.drawPixel(xprev - 1, yprev + 1, DKGREY);
    tft.drawPixel(xprev + 1, yprev - 1, DKGREY);
    tft.drawPixel(xprev - 1, yprev - 1, DKGREY);

    for (int k = 1; k <= 17; k++)
    { // Draw lines between all points
      color = WHITE;
      if (listy[k] <= 100)
      { // The 100th pixel correspond to 140mMol
        color = RED;
      }
      if (listy[k] >= 150)
      { // The 150th pixel correspond to 90mMol
        color = TEAL;
      }
      tft.drawLine(listx[k], listy[k], listx[k + 1], listy[k + 1], color);
      //      delay(25);
      tft.drawLine(listx[1], listy[1], xprev, yprev, DKGREY);
      tft.drawLine(listx[1], listy[1] - 1, xprev, yprev, DKGREY);
      tft.drawLine(listx[1], listy[1] + 1, xprev, yprev, DKGREY);
    }

    delay(2000); // Update frequency

    // Refresh graph after 2 seconds
    tft.fillRect(26, 50, 188, 141, BLACK); 
    tft.fillRect(23, 54, 5, 135, BLACK);
    tft.fillRect(25, 190, 190, 3, BLACK);
  }
}

// Shift right function
void shiftright(int list[])
{
  for (int i = 19; i >= 1; i--)
  {
    list[i] = list[i - 1];
  }
}

// Convert the value receive in graphical coordinates
int converttopixel(int cg)
{
  int y = 240 - (cg - 7);
  return y;
}
