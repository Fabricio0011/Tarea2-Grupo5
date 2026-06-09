#define F_CPU 8000000UL  //Definición de la frecuencia de trabajo del microcontrolador
#include <avr/io.h>
#include <util/delay.h>


#define ARRIBA      1
#define ABAJO       2
#define IZQUIERDA   3
#define DERECHA     4

//Arreglo que contiene la activación de cada fila de la matriz 8x8.
unsigned char posicion[8]={1,2,4,8,16,32,64,128};

unsigned char flecha_izquierda[8]={
  0xE7,
  0xC3,
  0x81,
  0x00,
  0xE7,
  0xE7,
  0xE7,
  0xFF
};
unsigned char flecha_derecha[8]={
  0xE7,
  0xE7,
  0xE7,
  0x00,
  0x81,
  0xC3,
  0xE7,
  0xFF
};
unsigned char flecha_abajo[8]={
  0xFF,
  0xCF,
  0x8F,
  0x1,
  0x1,
  0x8F,
  0xCF,
  0xFF
};
unsigned char flecha_arriba[8]={
  0xFF,
  0xF3,
  0xF1,
  0x80,
  0x80,
  0xF1,
  0xF3,
  0xFF
};
unsigned char correcto[8]={
  0xFF,
  0xFF,
  0xF7,
  0xE3,
  0xC9,
  0x9C,
  0xBE,
  0xFF
};
unsigned char error[8]={
  0xFF,
  0xBD,
  0xDB,
  0xE7,
  0xE7,
  0xDB,
  0xBD,
  0xFF
};

uint8_t secuencia[4] = {
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

uint8_t respuesta[4];

void mostrar_patron(unsigned char patron[8]){
    for(int z=0; z<60; z++){
        for(int fila=0; fila<8; fila++){
            PORTD = posicion[fila];
            PORTB = patron[fila];
            _delay_ms(0.06);
        }
    }
}


void mostrar_secuencia(uint8_t cantidad){
    for(uint8_t i=0; i<cantidad; i++){
        switch(secuencia[i]){
            case ARRIBA:
                mostrar_patron(flecha_arriba);
                break;

            case ABAJO:
                mostrar_patron(flecha_abajo);
                break;

            case IZQUIERDA:
                mostrar_patron(flecha_izquierda);
                break;

            case DERECHA:
                mostrar_patron(flecha_derecha);
                break;
        }
        _delay_ms(300);
    }
}

uint8_t verificar(uint8_t cantidad){
    for(uint8_t i=0;i<cantidad;i++){
        if(respuesta[i] != secuencia[i]){
            return 0;
        }
    }

    return 1;
}

int main(){

  DDRB = 0xFF; //configuramos como salida al puerto B
  DDRD = 0XFF; //configuramos como salida al puerto D

  PORTC |= (1<<PC0);
  PORTC |= (1<<PC1);
  PORTC |= (1<<PC2);
  PORTC |= (1<<PC3);

  while(1){

    mostrar_secuencia(4);
    uint8_t indice = 0;
    while(indice < 4){
      if(!(PINC & (1<<PC0))){
        respuesta[indice] = ARRIBA;
        indice++;
        mostrar_patron(flecha_arriba);
        while(!(PINC & (1<<PC0)));
        _delay_ms(100);
      }
      else if(!(PINC & (1<<PC1))){
        respuesta[indice] = ABAJO;
        indice++;
        mostrar_patron(flecha_abajo);
        while(!(PINC & (1<<PC1)));
        _delay_ms(100);
      }
      else if(!(PINC & (1<<PC2))){
        respuesta[indice] = IZQUIERDA;
        indice++;
        mostrar_patron(flecha_izquierda);
        while(!(PINC & (1<<PC2)));
        _delay_ms(100);
      }
      else if(!(PINC & (1<<PC3))){
        respuesta[indice] = DERECHA;
        indice++;
        mostrar_patron(flecha_derecha);        
        while(!(PINC & (1<<PC3)));
        _delay_ms(100);
      }
    }
    if(verificar(4)){
      mostrar_patron(correcto);
    }
    else{
      mostrar_patron(error);
    }
    _delay_ms(1000);
  }
    
  
  
}
