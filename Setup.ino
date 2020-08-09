void _setup() {

  // Configurando interrupções dos sinais
  pinMode(MOEDEIRO_SINAL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MOEDEIRO_SINAL), moedeiro_int, FALLING);
  pinMode(NOTEIRO_SINAL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NOTEIRO_SINAL), noteiro_int, FALLING);

  // Configurando Display
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  lcd.print("INICIANDO...");
  
  // Configurando portas dos botoes
  for (int i = 0; i < 6; i++)
  {
    pinMode(botaoMaquinas[i], INPUT);
    digitalWrite(botaoMaquinas[i], HIGH);
  }

  // Serial DESLIGADA!
  // Configurando porta do RX
  pinMode(LCD_D6_CONFIG, INPUT);
  digitalWrite(LCD_D6_CONFIG, HIGH);
  // Iniciando Serial 
  // Serial.begin(9600);

  // Configurando o Acumulador
  Acumulador = 0;
  ValorCaptura = 0;
  ContaSinalMoedeiro = 0;
  ContaSinalNoteiro = 0;

  // Configurando o parcial
  Parcial = 0;

  // Flag pra sinalizar captura de pagamento
  Capturando = false;
  HouveCaptura = false;

  // Temporizador de atualização da captura de pagamento
  for (int i = 1; i <= 3; i++) 
    update_tick(i);
  
  // Esperando 5 segundos
  delay(5000);
  // Configurando portas de saidas depois de 5 segundos
  for (int i = 0; i < 6; i++)
  {
    pinMode(portaMaquinas[i], OUTPUT);
    digitalWrite(portaMaquinas[i], HIGH);
  }
  
  // Carregando valores do relatorio
  reportLoad();
  // Carregando configuracoes
  configLoad();
  // Verificando jumper de configuracao
  if (!digitalRead(LCD_D6_CONFIG))
  {
    delay(5000);
    //  lcd(12, 11, 5, 4, LCD_D6_CONFIG, LCD_D7);
    lcd.init(1, 12, 255, 11, 5, 4, LCD_D6_CONFIG, LCD_D7, 0, 0, 0, 0);
    jumperMenu();
    return;
  }
  
  // Tudo iniciado, montando tela principal
  monta_tela(PRINCIPAL, 0.0);
}
