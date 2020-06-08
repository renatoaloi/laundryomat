// interrupção do moedeiro
void moedeiro_int() {

    // Capturando pagamento
    Capturando = true;

    // Atualizando acumulador
    Acumulador += 0.25;

    // atualizando o parcial, dentro do periodo de atualização
    Parcial += 0.25;

    // adicionando uma moeda no relatorio
    report.total_moedas++;
}

// interrupção do noteiro
void noteiro_int() {

    // Capturando pagamento
    Capturando = true;

    // Atualizando acumulador
    Acumulador += 1.0;
    
    // atualizando o parcial, dentro do periodo de atualização
    Parcial += 1.0;

    // adicionando uma nota no relatorio
    report.total_notas++;
}

// atualiza dados parciais do LCD
void atualiza_parcial() {
  monta_tela(PARCIAL, Parcial);
}

void update_tick() {
  captura_tick = millis() + 1000;
}

void captura_check() {
  if (captura_tick < millis()) {
    // Verificando se tem que atualizar parcial
    if (Capturando) {
      // 
      Capturando = false;
      
      // Atualizando parcial
      atualiza_parcial();
      
      // Gravando o relatorio na EEPROM
      EEPROM_writeAnything(EEPROM_ADDR_1, report);
    }
    update_tick();
  }
}
