// interrupção do moedeiro
void moedeiro_int() {
    Acumulador += 0.25;
    monta_tela(PARCIAL, 0.25);

    // adicionando uma moeda no relatorio
    report.total_moedas++;
    
    // Gravando o relatorio na EEPROM
    EEPROM_writeAnything(200, report);
}
