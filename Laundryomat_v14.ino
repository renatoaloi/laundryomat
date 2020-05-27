#include <LiquidCrystal.h>
#include <math.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"

#define PRINCIPAL 1
#define LIGANDO   2
#define PARCIAL   3
#define CONFIRMA  4
#define ERRO      99
#define DEBUG     1
#define RXPIN     0

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
  unsigned long moeda10o;
  unsigned long moeda10n;
  unsigned long moeda25;
  unsigned long moeda50o;
  unsigned long moeda50n;
  unsigned long moeda1;
  unsigned long nota2;
  unsigned long nota5;
  unsigned long nota10;
  unsigned long nota20;
  unsigned long nota50;
  unsigned long nota100;
} report;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte bufferMoedeiro[6];
byte bufferNoteiro[3];
float Acumulador;
byte modo_debug = 0;

//------------------------------------------------------------
// Configurar aqui o valor do credito
// para liberar o acionamento das maquinas
//float ValorCredito = 3.00;
//                       Maq1, Maq2, Maq3, Maq4, Maq5, Maq6
float valorCredito[6]; // = { 3.00, 3.00, 3.00, 3.00, 3.00, 3.00 };
//------------------------------------------------------------
// Configurar aqui a duracao do pulso
// de acionamento da maquina (em ms)
int   DuracaoPulso; // = 600; // ms
//------------------------------------------------------------
// Configurar aqui a quantidade de pulsos
// de credito da maquina
//int   QtdePulsos = 4;
//                  Maq1, Maq2, Maq3, Maq4, Maq5, Maq6
int qtdePulsos[6]; // = { 4,    4,    4,    4,    4,    4 };
//------------------------------------------------------------
// Configurar aqui o tempo de exibicao 
// do erro de credito incompleto
int   TempoExibirErro; // = 2000; // ms
//------------------------------------------------------------

char strAcumulado[7]  = "TOTAL:";
char strCifrao[3]     = "R$";
char strParcial[9]    = "PARCIAL:";
char strLigando[9]    = "LIGANDO ";
String strConfirma   = "CONFIRMA ";
String strInterrog   = "?";
char strInsira[16]     = "INSIRA VALOR...";
char strErroLinha1[13] = "NAO ATINGIU ";
char strErroLinha2[17] = "VALOR: "; // DE CREDITO";
String strMaquinas[] = { "LAV. 1", "LAV. 2", "LAV. 3",
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
