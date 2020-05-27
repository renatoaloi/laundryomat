void verifica_valor_moedeiro(float *ret) {
  if (bufferMoedeiro[0] == 0x90 && bufferMoedeiro[1] == 0x06 && bufferMoedeiro[2] == 0x12)
  {
    if (bufferMoedeiro[3] == 0x02 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xAD)
    {
      *ret = 0.1f;
      report.moeda10o++;
    }
    else if (bufferMoedeiro[3] == 0x01 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xAC)
    {
      *ret = 0.1f;
      report.moeda10n++;
    }
    else if (bufferMoedeiro[3] == 0x03 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xAE)
    {
      *ret = 0.25f;
      report.moeda25++;
    }
    else if (bufferMoedeiro[3] == 0x04 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xAF)
    {
      *ret = 0.5f;
      report.moeda50o++;
    }
    else if (bufferMoedeiro[3] == 0x06 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xB1)
    {
      *ret = 0.5f;
      report.moeda50n++;
    }
    else if (bufferMoedeiro[3] == 0x07 && bufferMoedeiro[4] == 0x03 && bufferMoedeiro[5] == 0xB2)
    {
      *ret = 1.0f;
      report.moeda1++;
    }
  }
}
