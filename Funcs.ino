
byte verifica_botao(byte botao)
{
  if (!digitalRead(botao))
  {
    unsigned long tempo = millis() + 150;
    while(tempo > millis())
    {
     if (digitalRead(botao)) return LOW;
    } 
    return HIGH;
  } 
  else 
    return LOW;
}

void checkAcc() {
  for (int i = 0; i < 6; i++)
  {
    if ((Acumulador + .01) >= valorCredito[i])
    {
      if (verifica_botao(botaoMaquinas[i]))
      {
        boolean confirma = false;
        boolean erro = false;
        monta_tela(CONFIRMA, i);
        delay(500);
        while (!confirma && !erro)
        {
          for (int j = 0; j < 6; j++)
          {
            if (verifica_botao(botaoMaquinas[j]))
            {
              if (j == i)
              {
                confirma = true;
              }
              else
              {
                i = j;
                if ((Acumulador + .01) >= valorCredito[i])
                {
                  monta_tela(CONFIRMA, i);
                }
                else
                {
                  monta_tela(ERRO, i);
                  delay(TempoExibirErro);
                  monta_tela(PRINCIPAL, Acumulador);
                  erro = true;
                }
              }
              break;
            }
          }
        }
        if (confirma) aciona_maquina(i);
        break;
      }
    }
    else
    {
      if (verifica_botao(botaoMaquinas[i]))
      {
        monta_tela(ERRO, i);
        
        unsigned long tempo = millis() + TempoExibirErro;
        int contador = 0;
        while (tempo > millis())
        {
          if (verifica_botao(botaoMaquinas[i]))
          {
            contador++;
          }
        }
        
        if (contador >= 10)
        {
          limpa_display(1);
          lcd.setCursor(0, 1);
          lcd.print("OK");
          EEPROM_writeAnything(200, report);
          delay(TempoExibirErro);
        }
        
        monta_tela(PRINCIPAL, Acumulador);
        break;
      }
    }
  }
}
