float convertir_float(string cad) {
    float numero = 0;
    float decimal = 0;
    float divisor = 1;
    bool parte_decimal = false;

    for (int i = 0; i < cad.length(); i++) {

        if (cad[i] == '.') {
            parte_decimal = true;
            continue;
        }

        if (!parte_decimal) {
            // Parte entera
            numero = numero * 10 + (cad[i] - '0');
        }
        else {
            // Parte decimal
            divisor *= 10; 
            decimal = decimal + (cad[i] - '0') / divisor;
        }
    }

    return numero + decimal;
}

int convertir_entero(string cad) {
    int n = 0;
    for (int i = 0; i < cad.length(); i++) {
        n = n * 10 + (cad[i] - '0');
    }
    return n;
}