void _setup() {
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
  // Configurando porta do RX
  pinMode(RXPIN, INPUT);
  digitalWrite(RXPIN, HIGH);
  // Configurando o Acumulador
  Acumulador = 0;
  // Iniciando Serial 
  Serial.begin(9600);
  
  
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
  if (!digitalRead(RXPIN))
  {
    jumperMenu();
    return;
  }
  
  // Tudo iniciado, montando tela principal
  monta_tela(PRINCIPAL, 0.0);
}
