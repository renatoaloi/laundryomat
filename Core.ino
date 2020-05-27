void _core() {
  // Verificando se recebeu dados da entrada
  if (confere_entrada())
  {
    float valor = verifica_valor();
    if (valor > 0.0)
    {
      Acumulador += valor;
      monta_tela(PARCIAL, valor);
    }
  }
  // Verificando se o Acumulador
  // atingiu o valor de credito
  checkAcc();
  delay(10);
}
