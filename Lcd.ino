void limpa_display(int linha)
{
  lcd.setCursor(0, linha);
  lcd.print("                ");
}

void monta_tela(byte tipo, float valor)
{
  lcd.begin(16, 2);
  limpa_display(0);
  limpa_display(1);
  lcd.setCursor(0, 0);
  
  if (tipo == PARCIAL)
  {
    lcd.setCursor(0, 0);
    lcd.print(strAcumulado);
    lcd.setCursor(9, 0);
    lcd.print(strCifrao);
    lcd.print(converte_valor(Acumulador));
    lcd.setCursor(0, 1);
    lcd.print(strParcial);
    lcd.setCursor(9, 1);
    lcd.print(strCifrao);
    lcd.print(converte_valor(valor));
  }
  else if (tipo == PRINCIPAL)
  {
    lcd.setCursor(0, 0);
    lcd.print(strAcumulado);
    lcd.setCursor(9, 0);
    lcd.print(strCifrao);
    lcd.print(converte_valor(Acumulador));
    lcd.setCursor(0, 1);
    lcd.print(strInsira);
  }
  else if (tipo == LIGANDO)
  {
    lcd.setCursor(0, 0);
    lcd.print(strAcumulado);
    lcd.setCursor(9, 0);
    lcd.print(strCifrao);
    lcd.print(converte_valor(Acumulador));
    lcd.setCursor(0, 1);
    lcd.print(strLigando);
    lcd.setCursor(8, 1);
    lcd.print(strMaquinas[(int)valor]);
  }
  else if (tipo == CONFIRMA)
  {
    lcd.setCursor(0, 0);
    lcd.print(strAcumulado);
    lcd.setCursor(9, 0);
    lcd.print(strCifrao);
    lcd.print(converte_valor(Acumulador));
    lcd.setCursor(0, 1);
    lcd.print(strConfirma);
    lcd.setCursor(9, 1);
    lcd.print(strMaquinas[(int)valor]);
    lcd.setCursor(15, 1);
    lcd.print(strInterrog);
  }
  else if (tipo == ERRO)
  {
    lcd.setCursor(0, 0);
    lcd.print(strErroLinha1);
    lcd.setCursor(0, 1);
    lcd.print(strErroLinha2);
    lcd.setCursor(9, 1);
    lcd.print(strCifrao);
    lcd.print(converte_valor(valorCredito[(int)valor]));
  }
}

String converte_valor(float valor)
{
  if (valor > 0.00)
  {
    char buffer[10];
    dtostrf(valor, 1, 2, buffer);
    String ret = buffer;
    ret.replace(".", ",");
    return ret; 
  }
  else
  {
    return "0,00";
  }
}
