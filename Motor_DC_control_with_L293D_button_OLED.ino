/* Este programa activa el movimiento de un motor de CC a través de un CI L293D.
Durante 4 segundos gira en un sentido y durante otros 4 gira en el otro; así sucesivamente.
El led del pin 13 en se enciende en un sentido de giro y se apaga en el otro.*/

// Written by PLÉYADES IT

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int GiroHora = 2;         // --> pin 2 L293D (Input 1)
int GiroAntiHora = 3;     // --> pin 7 L293D (Input 2)
int BotonCambioGiro = 4;  // Botón/interruptor cambia sentido giro motor
int SpeedPin = 5;         // --> pin 1 L293D (Enable 1, 2)
int SpeedMotor = 0;
int SpeedPercentage = 0;
const int PotIn = A7;
int PotValor = 0;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();           // Borra el display

  pinMode(GiroHora, OUTPUT);
  digitalWrite(GiroHora, LOW);
  pinMode(GiroAntiHora, OUTPUT);
  digitalWrite(GiroAntiHora,LOW);
  pinMode(BotonCambioGiro, INPUT_PULLUP);
  pinMode(SpeedPin, OUTPUT);
  digitalWrite(SpeedPin, LOW);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,13);     //Horizontal x vertical
  display.print("Pleyades");
  display.setCursor(55,42);
  display.print("IT");
  display.display();
  delay(1800);
  display.clearDisplay();
  display.setCursor(18,0);
  display.print("DC MOTOR");
  display.setTextSize(1);
  display.setCursor(25,27);
  display.print("controlled by");
  display.setTextSize(2);
  display.setCursor(18,49);
  display.print("L293D IC");
  display.display();
  delay(1800);
  display.clearDisplay();
}

void loop()
{
  if (digitalRead(BotonCambioGiro) == LOW)
  {
    digitalWrite(GiroHora, LOW);
    digitalWrite(GiroAntiHora, HIGH);
    display.drawRect(70, 50, 31, 5, WHITE);
    display.drawTriangle(100, 44, 115, 52, 100, 60, WHITE);
  }
  if (digitalRead(BotonCambioGiro) == HIGH)
  {
    digitalWrite(GiroHora, HIGH);
    digitalWrite(GiroAntiHora, LOW);
    display.drawRect(20, 50, 30, 5, WHITE);   // (upperLeftX, upperLeftY, width, height, color)
    display.drawTriangle(20, 45, 5, 52, 20, 60, WHITE);  // (poin1X, point1Y, point2X, point2Y, point3X, point3Y, color)
  }

  PotValor = analogRead(PotIn);
  SpeedMotor = map(PotValor, 0, 1024, 0, 255);
  analogWrite(SpeedPin, SpeedMotor);
  SpeedPercentage = map(PotValor, 0, 1024, 0, 100);

  display.setTextSize(2);
  display.setCursor(0,0);     //Horizontal x vertical
  display.print("SPEED: " + String(SpeedPercentage) + "%");
  display.setTextSize(1);
  display.setCursor(0,27);
  display.print("DC Motor direction:");
  display.display();
  display.clearDisplay();
}