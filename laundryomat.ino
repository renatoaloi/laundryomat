#include <LiquidCrystal.h>
#include <math.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

#define PRINCIPAL       1
#define LIGANDO         2
#define PARCIAL         3
#define CONFIRMA        4
#define ERRO            99
#define LCD_D7          1
#define LCD_D6_CONFIG   0
#define MOEDEIRO_SINAL  2
#define NOTEIRO_SINAL   3
#define EEPROM_ADDR_1   300
#define EEPROM_ADDR_2   400
#define TEMPO_CAPTURA   500
#define TEMPO_NOTEIRO   10
#define TEMPO_MOEDEIRO  10
#define TOTAL_SINAIS    3

struct config_t
{
  byte isNull;
  float valor1;
  float valor2;
  float valor3;
  float valor4;
  float valor5;
  float valor6;
  int pulsos1;
  int pulsos2;
  int pulsos3;
  int pulsos4;
  int pulsos5;
  int pulsos6;
  int tempo;
  byte fatorValor;
  int fatorDuracao;
  int duracao;
} configuration;

struct report_t
{
  byte isNull;
  unsigned long maq1;
  unsigned long maq2;
  unsigned long maq3;
  unsigned long maq4;
  unsigned long maq5;
  unsigned long maq6;
  unsigned long total_moedas;
  unsigned long total_notas;
} report;

LiquidCrystal lcd(12, 11, 5, 4, LCD_D6_CONFIG, LCD_D7);

byte bufferMoedeiro[6];
byte bufferNoteiro[3];

volatile bool Capturando;
volatile float ValorCaptura;

float Acumulador;
float Parcial;
bool HouveCaptura;
int ContaSinalMoedeiro;
int ContaSinalNoteiro;
unsigned long captura_tick;
unsigned long noteiro_tick;
unsigned long moedeiro_tick;
byte modo_debug = 0;

//------------------------------------------------------------
// Configurar aqui o valor do credito
// para liberar o acionamento das maquinas
//float ValorCredito = 3.00;
//                       Maq1, Maq2, Maq3, Maq4, Maq5, Maq6
float valorCredito[6]; // = { 7.00, 7.00, 7.00, 7.00, 7.00, 7.00 };
//------------------------------------------------------------
// Configurar aqui a duracao do pulso
// de acionamento da maquina (em ms)
int   DuracaoPulso; // = 100; // ms
//------------------------------------------------------------
// Configurar aqui a quantidade de pulsos
// de credito da maquina
//int   QtdePulsos = 4;
//                  Maq1, Maq2, Maq3, Maq4, Maq5, Maq6
int qtdePulsos[6]; // = { 1,    1,    1,    1,    1,    1 };
//------------------------------------------------------------
// Configurar aqui o tempo de exibicao 
// do erro de credito incompleto
int   TempoExibirErro; // = 2000; // ms
//------------------------------------------------------------

char strAcumulado[7]   = "TOTAL:";
char strCifrao[3]      = "R$";
char strParcial[9]     = "PARCIAL:";
char strLigando[9]     = "LIGANDO ";
String strConfirma     = "CONFIRMA ";
String strInterrog     = "?";
char strInsira[16]     = "INSIRA VALOR...";
char strErroLinha1[13] = "NAO ATINGIU ";
char strErroLinha2[17] = "VALOR: "; // DE CREDITO";
String strMaquinas[]   = { "LAV. 1", "LAV. 2", "LAV. 3",
                           "SEC. 1", "SEC. 2", "SEC. 3" };

byte portaMaquinas[] = { 14, 15, 16, 17, 18, 19 };
byte botaoMaquinas[] = { 13, 10,  9,  8,  7,  6 };

void setup()
{
  _setup();
}

void loop()
{
  _core();
}
