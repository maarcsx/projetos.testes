#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t NUM_LINHAS = 4;
const uint8_t NUM_COLUNAS = 3;

char teclas[NUM_LINHAS][NUM_COLUNAS] = {
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'},
  { '*', '0', '#'}
};

uint8_t pinosLinhas[NUM_LINHAS] = {32, 33, 25, 26};
uint8_t pinosColunas[NUM_COLUNAS] = {27, 14, 12};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, NUM_LINHAS, NUM_COLUNAS);

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pinoRELE[] = {16, 4, 0, 2};
bool estados[] = {LOW, LOW, LOW, LOW};

// --- CONTROLE DE NAVEGAÇÃO ---
int telaAtual = 0; // 0: Menu Principal, 1: Manual, 2: Sensores, 3: Config

void mostrarMenuPrincipal() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("> MENU PRINCIPAL <");
  lcd.setCursor(0, 1); lcd.print("1 - Modo Manual");
  lcd.setCursor(0, 2); lcd.print("2 - Temp/Umid");
}

void desenharInterfaceManual()
{
  lcd.clear();
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    lcd.print("R");
    lcd.print(i + 1);
    lcd.print(": ");
    lcd.print(estados[i] ? "LIGADO   " : "DESLIGADO");
  }
  lcd.setCursor(14, 3); lcd.print("* SAIR");
}

void teste()
{
  lcd.clear();
  for (int a = 0; a < 4; a++)
  {
    lcd.setCursor(0, a);
    lcd.print("Versao: ");
    lcd.print(": ");
    lcd.print(a + 1);
  }
  lcd.setCursor(14, 3);
  lcd.print("* SAIR");
}
void setup() {
  Wire.begin(21, 22);
  for (int i = 0; i < 4; i++) pinMode(pinoRELE[i], OUTPUT);
  lcd.init();
  lcd.backlight();
  mostrarMenuPrincipal();
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla) {
    // --- LÓGICA DE NAVEGAÇÃO ---
    if (telaAtual == 0)
    {
      if (tecla == '1')
      {
        telaAtual = 1;
        desenharInterfaceManual();
      }
      else if (tecla == '2')
      {
        telaAtual = 2;
        teste();
      }
    }

    // --- VOLTAR PARA O MENU (Tecla *) ---
    else if (tecla == '*')
    {
      telaAtual = 0;
      mostrarMenuPrincipal();
    }

    // --- LÓGICA DENTRO DO MODO MANUAL ---
    else if (telaAtual == 1)
    {
      int indice = tecla - '1';
      if (indice >= 0 && indice <= 3)
      {
        estados[indice] = !estados[indice];
        digitalWrite(pinoRELE[indice], estados[indice]);

        // Atualiza apenas a linha sem dar clear
        lcd.setCursor(4, indice);
        lcd.print(estados[indice] ? "LIGADO   " : "DESLIGADO");
      }
      if (tecla == '#')
      {
        for (int i = 0; i < 4; i++)
        {
          estados[i] = LOW;
          digitalWrite(pinoRELE[i], LOW);
        }
        desenharInterfaceManual();
      }
    }
  }
}