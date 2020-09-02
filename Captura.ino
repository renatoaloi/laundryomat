bool filtro(unsigned long ini, unsigned long fim, int ms) {
  return (fim - ini > ms - 3 && fim - ini < ms + 3);
}

// interrupção do moedeiro
void moedeiro_int() {
    // Atualizando acumulador
    if (!digitalRead(MOEDEIRO_SINAL)) {
      m_time_captura_ini = millis();
      m_entrada = true;
      Capturando = true;
      captura_tick = millis() + TEMPO_CAPTURA;
    } else if (m_entrada) {
      m_time_captura_fim = millis();
      m_entrada = false;
    
      if (filtro(m_time_captura_ini, m_time_captura_fim, 50)
          || filtro(m_time_captura_ini, m_time_captura_fim, 100)) {
        Parcial += 0.25;
        HouveCapturaMoedeiro = true;
      }
    }
}


// interrupção do noteiro
void noteiro_int() {
    // Atualizando acumulador
    if (!digitalRead(NOTEIRO_SINAL)) {
      n_time_captura_ini = millis();
      n_entrada = true;
      Capturando = true;
      captura_tick = millis() + TEMPO_CAPTURA;
    } else if (n_entrada) {
      n_time_captura_fim = millis();
      n_entrada = false;
    
      if (filtro(n_time_captura_ini, n_time_captura_fim, 50)
          || filtro(n_time_captura_ini, n_time_captura_fim, 100)) {
        Parcial += 1.0;
        HouveCapturaNoteiro = true;
      }
    }
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
    
    // Atualizando parcial
    if (!Capturando) {
      if (HouveCapturaNoteiro || HouveCapturaMoedeiro) {

        Acumulador += Parcial;
        // atualizando o parcial, dentro do periodo de atualização
        Parcial = 0.0;

        if (HouveCapturaNoteiro) {
          // Desliga Capturando e captura
          HouveCapturaNoteiro = false;
          // adicionando uma nota no relatorio
          report.total_notas++;
        }
        else {
          // Desliga Capturando e captura
          HouveCapturaMoedeiro = false;
          // adicionando uma moeda no relatorio
          report.total_moedas++;
        }
        
        EEPROM_writeAnything(EEPROM_ADDR_1, report);
        atualiza_parcial();
      }
    }
    else 
      Capturando = false;
      
    
    update_tick(1);
  }
}
