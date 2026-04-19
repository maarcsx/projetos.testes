#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Endereço comum do LCD I2C é 0x27 ou 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinoBOTAO [] = {32, 33, 25, 26};
const int pinoRELE [] = {16, 4, 0, 2};
const int pinoLED [] = {19, 18, 5, 17};
bool estados [] = {LOW, LOW, LOW, LOW};

int valor = 0;

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinoBOTAO [i], INPUT_PULLUP);
    pinMode(pinoRELE [i], OUTPUT);
    pinMode(pinoLED [i], OUTPUT);
  }
  Serial.begin(115200);

  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Aguarde 1s ...");
  Serial.println("Aguarde 1s ...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Sistema OK!");
  Serial.println("Sistema OK!");
  lcd.clear();
}

void loop()
{
  // 1. Detecta qual botão foi pressionado
  if (digitalRead(pinoBOTAO[0]) == LOW) {
    valor = 1;
    delay(250);
  }
  if (digitalRead(pinoBOTAO[1]) == LOW) {
    valor = 2;
    delay(250);
  }
  if (digitalRead(pinoBOTAO[2]) == LOW) {
    valor = 3;
    delay(250);
  }
  if (digitalRead(pinoBOTAO[3]) == LOW) {
    valor = 4;
    delay(250);
  }

  // 2. O Switch inverte o estado APENAS UMA VEZ
  switch (valor)
  {
    case 1:
      estados [0] = !estados [0];
      valor = 0; // MUITO IMPORTANTE: Reseta para não entrar aqui de novo sem apertar
      break;

    case 2:
      estados [1] = !estados [1];
      valor = 0;
      break;

    case 3:
      estados [2] = !estados [2];
      valor = 0;
      break;

    case 4:
      estados [3] = !estados [3];
      valor = 0;
      break;
  }

  digitalWrite(pinoRELE [0], estados [0]);
  digitalWrite(pinoLED [0], estados [0]);

  digitalWrite(pinoRELE [1], estados [1]);
  digitalWrite(pinoLED [1], estados [1]);

  digitalWrite(pinoRELE [2], estados [2]);
  digitalWrite(pinoLED [2], estados [2]);

  digitalWrite(pinoRELE [3], estados [3]);
  digitalWrite(pinoLED [3], estados [3]);
}