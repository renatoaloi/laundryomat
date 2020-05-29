
byte idxMenuReportAnt = 0;
byte idxMenuReport = 0;

void reportLoad()
{
  // Leitura da configuracao
  EEPROM_readAnything(200, report);
  
  // Verifica se ja existe valor gravado
  if (report.isNull)
  {
    report.isNull = 0;
    report.maq1 = 0;
    report.maq2 = 0;
    report.maq3 = 0;
    report.maq4 = 0;
    report.maq5 = 0;
    report.maq6 = 0;
    report.total_moedas = 0;
    report.total_notas = 0;
    EEPROM_writeAnything(200, report);
  }
}

void reportShow()
{
  atualizaTelaReport();
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (idxMenuReport < 12) idxMenuReport++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuReport > 0) idxMenuReport--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuReport == 12)
      {
        break;
      }
      else if (idxMenuReport == 11)
      {
        report.isNull = 0;
        report.maq1 = 0;
        report.maq2 = 0;
        report.maq3 = 0;
        report.maq4 = 0;
        report.maq5 = 0;
        report.maq6 = 0;
        report.total_moedas = 0;
        report.total_notas = 0;
        EEPROM_writeAnything(200, report);
        lcd.setCursor(0, 1);
        lcd.print("OK");
      }
    }
    if (idxMenuReportAnt != idxMenuReport)
    {
      idxMenuReportAnt = idxMenuReport;
      atualizaTelaReport();
    }
    delay(10);
  }
  jumperMenu();
}

void reportLog(int i)
{
  if (i == 0)
    report.maq1++;
  else if (i == 1)
    report.maq2++;
  else if (i == 2)
    report.maq3++;
  else if (i == 3)
    report.maq4++;
  else if (i == 4)
    report.maq5++;
  else if (i == 5)
    report.maq6++;
}

void atualizaTelaReport()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (idxMenuReport == 0)
  {
    lcd.print("MENU REPORT");
    lcd.setCursor(0, 1);
    lcd.print("SEL. OPCAO");
  }
  else if (idxMenuReport == 1)
  {
    lcd.print("TOTAL MOEDAS");
    lcd.setCursor(0, 1);
    unsigned long totalMoedas = report.total_moedas;
    lcd.print(totalMoedas);
  }
  else if (idxMenuReport == 2)
  {
    lcd.print("TOTAL NOTAS");
    lcd.setCursor(0, 1);
    unsigned long totalNotas = report.total_notas;
    lcd.print(totalNotas);
  }
  else if (idxMenuReport == 3)
  {
    lcd.print("TOTAL VALOR");
    lcd.setCursor(0, 1);
    float totalValor = 0;
    totalValor += (report.total_moedas * .25);
    totalValor += (report.total_notas * 1);
    lcd.print(totalValor);
  }
  else if (idxMenuReport == 4)
  {
    lcd.print("MAQUINA1");
    lcd.setCursor(0, 1);
    lcd.print(report.maq1);
  }
  else if (idxMenuReport == 5)
  {
    lcd.print("MAQUINA2");
    lcd.setCursor(0, 1);
    lcd.print(report.maq2);
  }
  else if (idxMenuReport == 6)
  {
    lcd.print("MAQUINA3");
    lcd.setCursor(0, 1);
    lcd.print(report.maq3);
  }
  else if (idxMenuReport == 7)
  {
    lcd.print("MAQUINA4");
    lcd.setCursor(0, 1);
    lcd.print(report.maq4);
  }
  else if (idxMenuReport == 8)
  {
    lcd.print("MAQUINA5");
    lcd.setCursor(0, 1);
    lcd.print(report.maq5);
  }
  else if (idxMenuReport == 9)
  {
    lcd.print("MAQUINA6");
    lcd.setCursor(0, 1);
    lcd.print(report.maq6);
  }
  else if (idxMenuReport == 10)
  {
    lcd.print("TOTAL MAQUINAS");
    lcd.setCursor(0, 1);
    unsigned long totalMaquinas = report.maq1 + report.maq2 + report.maq3
                    + report.maq4 + report.maq5 + report.maq6;
    lcd.print(totalMaquinas);
  }
  else if (idxMenuReport == 11)
  {
    lcd.print("ZERAR CONTADORES");
  }
  else 
  {
    lcd.print("VOLTAR");
  }
}
