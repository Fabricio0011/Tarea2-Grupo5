void main() {
    ANSEL  = 0;           // Desactivar canales analógicos
    ANSELH = 0;

    TRISB = 0xFF;         // Puerto B completo como entrada (RB0 y RB1 leen al ATmega)

    // Configurar oscilador interno a 8MHz en el PIC
    OSCCON = 0x71;        // 0b01110001

    // Inicializar la librería Sound en el pin RD0
    Sound_Init(&PORTD, 0);

    while(1) {
        // Leemos las señales en los pines RB0 y RB1
        unsigned char comando = PORTB & 0x03;

        if (comando == 1) {
            // 1. SONIDO CLICK (Botones, secuencia y dificultades)
            Sound_Play(880, 50);   // Tono agudo y rápido
            while((PORTB & 0x03) == 1); // Espera que la línea se limpie
        }
        else if (comando == 2) {
            // 2. SONIDO GAME OVER (Melodía lúgubre descendente)
            Sound_Play(392, 180);  // Sol4
            Sound_Play(349, 180);  // Fa4
            Sound_Play(311, 220);  // Re#4
            Sound_Play(246, 450);  // Si3
            while((PORTB & 0x03) == 2);
        }
        else if (comando == 3) {
            // 3. SONIDO GANÓ EL JUEGO / START (Fanfarria alegre ascendente)
            Sound_Play(523, 90);   // Do5
            Sound_Play(659, 90);   // Mi5
            Sound_Play(784, 90);   // Sol5
            Sound_Play(1046, 250); // Do6
            while((PORTB & 0x03) == 3);
        }
    }
}
