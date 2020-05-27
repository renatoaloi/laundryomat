
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
    report.moeda10o = 0;
    report.moeda10n = 0;
    report.moeda25 = 0;
    report.moeda50o = 0;
    report.moeda50n = 0;
    report.moeda1 = 0;
    report.nota2 = 0;
    report.nota5 = 0;
    report.nota10 = 0;
    report.nota20 = 0;
    report.nota50 = 0;
    report.nota100 = 0;
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
      if (idxMenuReport < 24) idxMenuReport++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuReport > 0) idxMenuReport--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuReport == 24)
      {
        break;
      }
      else if (idxMenuReport == 23)
      {
        report.isNull = 0;
        report.maq1 = 0;
        report.maq2 = 0;
        report.maq3 = 0;
        report.maq4 = 0;
        report.maq5 = 0;
        report.maq6 = 0;
        report.moeda10o = 0;
        report.moeda10n = 0;
        report.moeda25 = 0;
        report.moeda50o = 0;
        report.moeda50n = 0;
        report.moeda1 = 0;
        report.nota2 = 0;
        report.nota5 = 0;
        report.nota10 = 0;
        report.nota20 = 0;
        report.nota50 = 0;
        report.nota100 = 0;
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
    lcd.print("MOEDA .10 OLD");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda10o);
  }
  else if (idxMenuReport == 2)
  {
    lcd.print("MOEDA .10 NEW");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda10n);
  }
  else if (idxMenuReport == 3)
  {
    lcd.print("MOEDA .25");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda25);
  }
  else if (idxMenuReport == 4)
  {
    lcd.print("MOEDA .50 OLD");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda50o);
  }
  else if (idxMenuReport == 5)
  {
    lcd.print("MOEDA .50 NEW");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda50n);
  }
  else if (idxMenuReport == 6)
  {
    lcd.print("MOEDA 1 REAL");
    lcd.setCursor(0, 1);
    lcd.print(report.moeda1);
  }
  else if (idxMenuReport == 7)
  {
    lcd.print("TOTAL MOEDAS");
    lcd.setCursor(0, 1);
    unsigned long totalMoedas = report.moeda10o + report.moeda10n + report.moeda25 
      + report.moeda50o + report.moeda50n + report.moeda1;
    lcd.print(totalMoedas);
  }
  else if (idxMenuReport == 8)
  {
    lcd.print("NOTA 2 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota2);
  }
  else if (idxMenuReport == 9)
  {
    lcd.print("NOTA 5 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota5);
  }
  else if (idxMenuReport == 10)
  {
    lcd.print("NOTA 10 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota10);
  }
  else if (idxMenuReport == 11)
  {
    lcd.print("NOTA 20 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota20);
  }
  else if (idxMenuReport == 12)
  {
    lcd.print("NOTA 50 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota50);
  }
  else if (idxMenuReport == 13)
  {
    lcd.print("NOTA 100 REAIS");
    lcd.setCursor(0, 1);
    lcd.print(report.nota100);
  }
  else if (idxMenuReport == 14)
  {
    lcd.print("TOTAL NOTAS");
    lcd.setCursor(0, 1);
    unsigned long totalNotas = report.nota2 + report.nota5 + report.nota10 
      + report.nota20 + report.nota50 + report.nota100;
    lcd.print(totalNotas);
  }
  else if (idxMenuReport == 15)
  {
    lcd.print("TOTAL VALOR");
    lcd.setCursor(0, 1);
    float totalValor = 0;
    totalValor += (report.moeda10o * .1);
    totalValor += (report.moeda10n * .1);
    totalValor += (report.moeda25 * .25);
    totalValor += (report.moeda50o * .5);
    totalValor += (report.moeda50n * .5);
    totalValor += (report.moeda10o * .1);
    totalValor += (report.moeda1 * 1);
    totalValor += (report.nota2 * 2);
    totalValor += (report.nota5 * 5);
    totalValor += (report.nota10 * 10);
    totalValor += (report.nota20 * 20);
    totalValor += (report.nota50 * 50);
    totalValor += (report.nota100 * 100);
    lcd.print(totalValor);
  }
  else if (idxMenuReport == 16)
  {
    lcd.print("MAQUINA1");
    lcd.setCursor(0, 1);
    lcd.print(report.maq1);
  }
  else if (idxMenuReport == 17)
  {
    lcd.print("MAQUINA2");
    lcd.setCursor(0, 1);
    lcd.print(report.maq2);
  }
  else if (idxMenuReport == 18)
  {
    lcd.print("MAQUINA3");
    lcd.setCursor(0, 1);
    lcd.print(report.maq3);
  }
  else if (idxMenuReport == 19)
  {
    lcd.print("MAQUINA4");
    lcd.setCursor(0, 1);
    lcd.print(report.maq4);
  }
  else if (idxMenuReport == 20)
  {
    lcd.print("MAQUINA5");
    lcd.setCursor(0, 1);
    lcd.print(report.maq5);
  }
  else if (idxMenuReport == 21)
  {
    lcd.print("MAQUINA6");
    lcd.setCursor(0, 1);
    lcd.print(report.maq6);
  }
  else if (idxMenuReport == 22)
  {
    lcd.print("TOTAL MAQUINAS");
    lcd.setCursor(0, 1);
    unsigned long totalMaquinas = report.maq1 + report.maq2 + report.maq3
                    + report.maq4 + report.maq5 + report.maq6;
    lcd.print(totalMaquinas);
  }
  else if (idxMenuReport == 23)
  {
    lcd.print("ZERAR CONTADORES");
  }
  else 
  {
    lcd.print("VOLTAR");
  }
}

