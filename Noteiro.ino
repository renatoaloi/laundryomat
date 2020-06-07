// interrupção do noteiro
void noteiro_int() {
    Acumulador += 1.0;
    monta_tela(PARCIAL, 1.0);

    // adicionando uma nota no relatorio
    report.total_notas++;

    // Gravando o relatorio na EEPROM
    EEPROM_writeAnything(200, report);
}
