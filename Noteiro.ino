// interrupção do noteiro
void noteiro_int() {
    Acumulador += 1.00f;
    monta_tela(PARCIAL, 1.00f);

    // Gravando o relatorio na EEPROM
    EEPROM_writeAnything(200, report);
}
