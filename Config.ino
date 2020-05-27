
byte idxMenuCfgAnt = 0;
byte idxMenuJumper = 0;
byte idxMenuCfg = 0;
byte idxMenuCfgFator = 0;
float fatorValor;
int fatorDuracao;
//byte temp = 1;

// Carrega configuracoes 
void configLoad()
{
  // Leitura da configuracao
  EEPROM_readAnything(100, configuration);
  
  // Verifica se ja existe valor gravado
  if (configuration.isNull) // || temp)
  {
    //temp = 0;
    // Caso nao exista, cria uma padrao
    configuration.isNull = 0;
    configuration.valor1 = 3.00;
    configuration.valor2 = 3.00;
    configuration.valor3 = 3.00;
    configuration.valor4 = 3.00;
    configuration.valor5 = 3.00;
    configuration.valor6 = 3.00;
    configuration.pulsos1 = 4;
    configuration.pulsos2 = 4;
    configuration.pulsos3 = 4;
    configuration.pulsos4 = 4;
    configuration.pulsos5 = 4;
    configuration.pulsos6 = 4;
    configuration.tempo = 2000;
    configuration.duracao = 600;
    configuration.fatorValor = 5;
    configuration.fatorDuracao = 2;
    // Grava valores padrao na EEPROM
    EEPROM_writeAnything(100, configuration);
  }
  
  // Carrega os valores nas variaveis globais
  valorCredito[0] = configuration.valor1;
  valorCredito[1] = configuration.valor2;
  valorCredito[2] = configuration.valor3;
  valorCredito[3] = configuration.valor4;
  valorCredito[4] = configuration.valor5;
  valorCredito[5] = configuration.valor6;
  qtdePulsos[0] = configuration.pulsos1;
  qtdePulsos[1] = configuration.pulsos2;
  qtdePulsos[2] = configuration.pulsos3;
  qtdePulsos[3] = configuration.pulsos4;
  qtdePulsos[4] = configuration.pulsos5;
  qtdePulsos[5] = configuration.pulsos6;
  TempoExibirErro = configuration.tempo;
  DuracaoPulso = configuration.duracao;
  fatorValor = getFatorValor(configuration.fatorValor);
  fatorDuracao = getFatorDuracao(configuration.fatorDuracao);
}

void jumperMenu()
{
  atualizaTelaJumper();
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (idxMenuJumper < 1) idxMenuJumper++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuJumper > 0) idxMenuJumper--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuJumper == 0)
      {
        configSetup();
      }
      else if (idxMenuJumper == 1)
      {
        reportShow();
      }
    }
    if (idxMenuCfgAnt != idxMenuJumper)
    {
      idxMenuCfgAnt = idxMenuJumper;
      atualizaTelaJumper();
    }
    delay(10);
  }
}

void configSetup()
{
  atualizaTelaConfig();
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (idxMenuCfg < 17) idxMenuCfg++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuCfg > 0) idxMenuCfg--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuCfg == 1)
      {
        configFator();
      }
      else if (idxMenuCfg == 2)
      {
        configFatorDuracao();
      }
      else if (idxMenuCfg == 3)
      {
        // config duracao pulsos
        configDuracao();
      }
      else if (idxMenuCfg == 4)
      {
        configValor(1);
      }
      else if (idxMenuCfg == 5)
      {
        configPulsos(1);
      }
      else if (idxMenuCfg == 6)
      {
        configValor(2);
      }
      else if (idxMenuCfg == 7)
      {
        configPulsos(2);
      }
      else if (idxMenuCfg == 8)
      {
        configValor(3);
      }
      else if (idxMenuCfg == 9)
      {
        configPulsos(3);
      }
      else if (idxMenuCfg == 10)
      {
        configValor(4);
      }
      else if (idxMenuCfg == 11)
      {
        configPulsos(4);
      }
      else if (idxMenuCfg == 12)
      {
        configValor(5);
      }
      else if (idxMenuCfg == 13)
      {
        configPulsos(5);
      }
      else if (idxMenuCfg == 14)
      {
        configValor(6);
      }
      else if (idxMenuCfg == 15)
      {
        configPulsos(6);
      }
      else if (idxMenuCfg == 16)
      {
        // Salvar EEPROM
        EEPROM_writeAnything(100, configuration);
        lcd.setCursor(0, 1);
        lcd.print("OK");
      }
      else if (idxMenuCfg == 17)
      {
        break;
      }
    }
    if (idxMenuCfgAnt != idxMenuCfg)
    {
      idxMenuCfgAnt = idxMenuCfg;
      atualizaTelaConfig();
    }
    delay(10);
  }
  jumperMenu();
}

void configFator()
{
  idxMenuCfgFator = configuration.fatorValor;
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (idxMenuCfgFator < 6) idxMenuCfgFator++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuCfgFator > 0) idxMenuCfgFator--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuCfgFator > 0 && idxMenuCfgFator <= 5)
      {
        configuration.fatorValor = idxMenuCfgFator;
        fatorValor = getFatorValor(configuration.fatorValor);
        atualizaTelaConfig();
        break;
      }
      else if (idxMenuCfgFator == 6)
      {
        atualizaTelaConfig();
        break;
      }
    }
    if (idxMenuCfgAnt != idxMenuCfgFator)
    {
      idxMenuCfgAnt = idxMenuCfgFator;
      atualizaTelaConfigFator();
    }
    delay(10);
  }
  return;
}

void configFatorDuracao()
{
  idxMenuCfgFator = configuration.fatorDuracao;
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (idxMenuCfgFator < 6) idxMenuCfgFator++;
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (idxMenuCfgFator > 0) idxMenuCfgFator--;
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      if (idxMenuCfgFator > 0 && idxMenuCfgFator <= 5)
      {
        configuration.fatorDuracao = idxMenuCfgFator;
        fatorDuracao = getFatorDuracao(configuration.fatorDuracao);
        atualizaTelaConfig();
        break;
      }
      else if (idxMenuCfgFator == 6)
      {
        atualizaTelaConfig();
        break;
      }
    }
    if (idxMenuCfgAnt != idxMenuCfgFator)
    {
      idxMenuCfgAnt = idxMenuCfgFator;
      atualizaTelaConfigFatorDuracao();
    }
    delay(10);
  }
  return;
}

void configDuracao()
{
  atualizaTelaConfigDuracao();
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      configuration.duracao += fatorDuracao;
      atualizaTelaConfigDuracao();
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      configuration.duracao -= fatorDuracao;
      atualizaTelaConfigDuracao();
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      atualizaTelaConfig();
      break;
    }
    delay(10);
  }
  return;
}

void configValor(byte produto)
{
  atualizaTelaConfigValor(produto);
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (produto == 1)
      {
        configuration.valor1 += fatorValor;
      }
      else if (produto == 2)
      {
        configuration.valor2 += fatorValor;
      }
      else if (produto == 3)
      {
        configuration.valor3 += fatorValor;
      }
      else if (produto == 4)
      {
        configuration.valor4 += fatorValor;
      }
      else if (produto == 5)
      {
        configuration.valor5 += fatorValor;
      }
      else if (produto == 6)
      {
        configuration.valor6 += fatorValor;
      }
      atualizaTelaConfigValor(produto);
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (produto == 1)
      {
        if (configuration.valor1 > 0)
          configuration.valor1 -= fatorValor;
      }
      else if (produto == 2)
      {
        if (configuration.valor2 > 0)
          configuration.valor2 -= fatorValor;
      }
      else if (produto == 3)
      {
        if (configuration.valor3 > 0)
          configuration.valor3 -= fatorValor;
      }
      else if (produto == 4)
      {
        if (configuration.valor4 > 0)
          configuration.valor4 -= fatorValor;
      }
      else if (produto == 5)
      {
        if (configuration.valor5 > 0)
          configuration.valor5 -= fatorValor;
      }
      else if (produto == 6)
      {
        if (configuration.valor6 > 0)
          configuration.valor6 -= fatorValor;
      }
      atualizaTelaConfigValor(produto);
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      atualizaTelaConfig();
      break;
    }
    delay(10);
  }
  return;
}

void configPulsos(byte produto)
{
  atualizaTelaConfigPulsos(produto);
  while(1)
  {
    if (verifica_botao(botaoMaquinas[0]))
    {
      if (produto == 1)
      {
        configuration.pulsos1 += 1;
      }
      else if (produto == 2)
      {
        configuration.pulsos2 += 1;
      }
      else if (produto == 3)
      {
        configuration.pulsos3 += 1;
      }
      else if (produto == 4)
      {
        configuration.pulsos4 += 1;
      }
      else if (produto == 5)
      {
        configuration.pulsos5 += 1;
      }
      else if (produto == 6)
      {
        configuration.pulsos6 += 1;
      }
      atualizaTelaConfigPulsos(produto);
    }
    else if (verifica_botao(botaoMaquinas[1]))
    {
      if (produto == 1)
      {
        if (configuration.pulsos1 > 0)
          configuration.pulsos1 -= 1;
      }
      else if (produto == 2)
      {
        if (configuration.pulsos2 > 0)
          configuration.pulsos2 -= 1;
      }
      else if (produto == 3)
      {
        if (configuration.pulsos3 > 0)
          configuration.pulsos3 -= 1;
      }
      else if (produto == 4)
      {
        if (configuration.pulsos4 > 0)
          configuration.pulsos4 -= 1;
      }
      else if (produto == 5)
      {
        if (configuration.pulsos5 > 0)
          configuration.pulsos5 -= 1;
      }
      else if (produto == 6)
      {
        if (configuration.pulsos6 > 0)
          configuration.pulsos6 -= 1;
      }
      atualizaTelaConfigPulsos(produto);
    }
    else if (verifica_botao(botaoMaquinas[2]))
    {
      atualizaTelaConfig();
      break;
    }
    delay(10);
  }
  return;
}

void atualizaTelaJumper()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (idxMenuJumper == 0)
  {
    lcd.print("MENU CONFIG");
  }
  else if (idxMenuJumper == 1)
  {
    lcd.print("MENU REPORT");
  }
}

void atualizaTelaConfig()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (idxMenuCfg == 0)
  {
    lcd.print("MENU CONFIG");
    lcd.setCursor(0, 1);
    lcd.print("SEL. OPCAO");
  }
  else if (idxMenuCfg == 1)
  {
    lcd.print("FATOR VALOR");
    lcd.setCursor(0, 1);
    lcd.print(getFatorValor(configuration.fatorValor));
  }
  else if (idxMenuCfg == 2)
  {
    lcd.print("FATOR DURACAO");
    lcd.setCursor(0, 1);
    lcd.print(getFatorDuracao(configuration.fatorDuracao));
  }
  else if (idxMenuCfg == 3)
  {
    lcd.print("DURACAO PULSO");
    lcd.setCursor(0, 1);
    lcd.print(configuration.duracao);
  }
  else if (idxMenuCfg == 4)
  {
    lcd.print("VALOR MAQUINA1");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor1);
  }
  else if (idxMenuCfg == 5)
  {
    lcd.print("PULSOS MAQUINA1");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos1);
  }
  else if (idxMenuCfg == 6)
  {
    lcd.print("VALOR MAQUINA2");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor2);
  }
  else if (idxMenuCfg == 7)
  {
    lcd.print("PULSOS MAQUINA2");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos2);
  }
  else if (idxMenuCfg == 8)
  {
    lcd.print("VALOR MAQUINA3");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor3);
  }
  else if (idxMenuCfg == 9)
  {
    lcd.print("PULSOS MAQUINA3");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos3);
  }
  else if (idxMenuCfg == 10)
  {
    lcd.print("VALOR MAQUINA4");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor4);
  }
  else if (idxMenuCfg == 11)
  {
    lcd.print("PULSOS MAQUINA4");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos4);
  }
  else if (idxMenuCfg == 12)
  {
    lcd.print("VALOR MAQUINA5");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor5);
  }
  else if (idxMenuCfg == 13)
  {
    lcd.print("PULSOS MAQUINA5");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos5);
  }
  else if (idxMenuCfg == 14)
  {
    lcd.print("VALOR MAQUINA6");
    lcd.setCursor(0, 1);
    lcd.print(configuration.valor6);
  }
  else if (idxMenuCfg == 15)
  {
    lcd.print("PULSOS MAQUINA6");
    lcd.setCursor(0, 1);
    lcd.print(configuration.pulsos6);
  }
  else if (idxMenuCfg == 16)
  {
    lcd.print("GRAVAR CONFIGS");
  }
  else 
  {
    lcd.print("VOLTAR");
  }
}

void atualizaTelaConfigFator()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (idxMenuCfgFator <= 5)
  {
    lcd.print("NOVO FATOR:");
    lcd.setCursor(0, 1);
    lcd.print(getFatorValor(idxMenuCfgFator));
  }
  else 
  {
    lcd.print("VOLTAR");
  }
}

void atualizaTelaConfigFatorDuracao()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (idxMenuCfgFator <= 5)
  {
    lcd.print("NOVO FATOR:");
    lcd.setCursor(0, 1);
    lcd.print(getFatorDuracao(idxMenuCfgFator));
  }
  else 
  {
    lcd.print("VOLTAR");
  }
}

void atualizaTelaConfigDuracao()
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  lcd.print("NOVA DURACAO");
  lcd.setCursor(0, 1);
  
  lcd.print(configuration.duracao);
  
}

void atualizaTelaConfigValor(byte produto)
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  lcd.print("NOVO VALOR MAQ");
  lcd.print(produto);
  lcd.setCursor(0, 1);
  if (produto == 1)
  {
    lcd.print(configuration.valor1);
  }
  else if (produto == 2)
  {
    lcd.print(configuration.valor2);
  }
  else if (produto == 3)
  {
    lcd.print(configuration.valor3);
  }
  else if (produto == 4)
  {
    lcd.print(configuration.valor4);
  }
  else if (produto == 5)
  {
    lcd.print(configuration.valor5);
  }
  else if (produto == 6)
  {
    lcd.print(configuration.valor6);
  }
}

void atualizaTelaConfigPulsos(byte produto)
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  lcd.print("QTDE PULSOS MAQ");
  lcd.print(produto);
  lcd.setCursor(0, 1);
  if (produto == 1)
  {
    lcd.print(configuration.pulsos1);
  }
  else if (produto == 2)
  {
    lcd.print(configuration.pulsos2);
  }
  else if (produto == 3)
  {
    lcd.print(configuration.pulsos3);
  }
  else if (produto == 4)
  {
    lcd.print(configuration.pulsos4);
  }
  else if (produto == 5)
  {
    lcd.print(configuration.pulsos5);
  }
  else if (produto == 6)
  {
    lcd.print(configuration.pulsos6);
  }
}

/*const char* getFatorValorLabel(byte fator)
{
  if (fator == 1)
  {
    return "0,05";
  }
  else if (fator == 2)
  {
    return "0,10";
  }
  else if (fator == 3)
  {
    return "0,25";
  }
  else if (fator == 4)
  {
    return "0,50";
  }
  else if (fator == 5)
  {
    return "1,00";
  }
  return "0,00";
}*/

float getFatorValor(byte fator)
{
  if (fator == 1)
  {
    return 0.05;
  }
  else if (fator == 2)
  {
    return 0.10;
  }
  else if (fator == 3)
  {
    return 0.25;
  }
  else if (fator == 4)
  {
    return 0.50;
  }
  else if (fator == 5)
  {
    return 1.00;
  }
  return 0.00;
}

int getFatorDuracao(byte fator)
{
  if (fator == 1)
  {
    return 50;
  }
  else if (fator == 2)
  {
    return 100;
  }
  else if (fator == 3)
  {
    return 250;
  }
  else if (fator == 4)
  {
    return 500;
  }
  else if (fator == 5)
  {
    return 1000;
  }
  return 0;
}
