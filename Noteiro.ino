void verifica_valor_noteiro(float *ret) {
  if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x01)
  {
    *ret = 2.0f;
    report.nota2++;
  }
  else if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x02)
  {
    *ret = 5.0f;
    report.nota5++;
  }
  else if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x03)
  {
    *ret = 10.0f;
    report.nota10++;
  }
  else if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x04)
  {
    *ret = 20.0f;
    report.nota20++;
  }
  else if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x05)
  {
    *ret = 50.0f;
    report.nota50++;
  }
  else if (bufferNoteiro[0] == 0x78 && bufferNoteiro[1] == 0x79 && bufferNoteiro[2] == 0x06)
  {
    *ret = 100.0f;
    report.nota100++;
  }
}
