// interrupção do moedeiro
void moedeiro_int() {
    // Atualizando acumulador
    ValorCaptura += 0.25;
}

// interrupção do noteiro
void noteiro_int() {
    // Atualizando acumulador
    ValorCaptura += 1.0;
}

// atualiza dados parciais do LCD
void atualiza_parcial() {
  monta_tela(PARCIAL, Parcial);
}

void update_tick(int i) {
  switch (i) {
    case 1: captura_tick = millis() + TEMPO_CAPTURA; break;
    case 2: noteiro_tick = millis() + TEMPO_NOTEIRO; break;
    case 3: moedeiro_tick = millis() + TEMPO_MOEDEIRO; break;
  }
}

void captura_check() {
  if (captura_tick < millis()) {
    // Verificando se tem que atualizar parcial
    if (Capturando) {
      // 
      Capturando = false;
      HouveCaptura = true;
      
      // Atualizando parcial
      atualiza_parcial();
      
      // Gravando o relatorio na EEPROM
      EEPROM_writeAnything(EEPROM_ADDR_1, report);
    }
    else {
      // Zerando o parcial
      if (HouveCaptura) {
        HouveCaptura = false;
        Parcial = 0;
      }
    }
    update_tick(1);
  }
}

void noteiro_check() {

  if (noteiro_tick < millis())
  {
    if (digitalRead(NOTEIRO_SINAL) == LOW) { // tem que ficar em LOW pelo menos por 10ms x 3 pra filtrar ruido
      // Incrementando contador de sinais
      ContaSinalNoteiro++;
    }

    if (ContaSinalNoteiro >= TOTAL_SINAIS)
    {
      // Zerando contador de sinais
      ContaSinalNoteiro = 0;
      
      // Capturando pagamento
      Capturando = true;
      
      // Atualizando acumulador
      Acumulador += ValorCaptura;
    
      // atualizando o parcial, dentro do periodo de atualização
      Parcial += ValorCaptura;
    
      // adicionando uma nota no relatorio
      report.total_notas++;
    }
  }
  
  update_tick(2);
}

void moedeiro_check() {

  if (moedeiro_tick < millis()) 
  {
    if(digitalRead(MOEDEIRO_SINAL) == LOW) { // tem que ficar em LOW pelo menos por 10ms x 3 pra filtrar ruido
      // Incrementando contador de sinais
      ContaSinalMoedeiro++;
    }

    if (ContaSinalMoedeiro >= TOTAL_SINAIS)
    {
      // Zerando contador de sinais
      ContaSinalMoedeiro = 0;
      
      // Capturando pagamento
      Capturando = true;
      
      // Atualizando acumulador
      Acumulador += ValorCaptura;
    
      // atualizando o parcial, dentro do periodo de atualização
      Parcial += ValorCaptura;
    
      // adicionando uma moeda no relatorio
      report.total_moedas++;
    }
  }
    
  update_tick(3);
}
