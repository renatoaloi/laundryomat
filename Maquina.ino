void aciona_maquina(int i)
{
  reportLog(i);
  Acumulador -= valorCredito[i];
  monta_tela(LIGANDO, i);
  delay(500);
  for (int j = 0; j < qtdePulsos[i]; j++)
  {
    digitalWrite(portaMaquinas[i], LOW);
    delay(DuracaoPulso);
    digitalWrite(portaMaquinas[i], HIGH);
    delay(DuracaoPulso);
  }
  delay(500);
  monta_tela(PRINCIPAL, 0.0);
  
  // Gravando o relatorio na EEPROM
  EEPROM_writeAnything(200, report);
}
