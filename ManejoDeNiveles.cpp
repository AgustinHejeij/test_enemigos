#include "ManejoDeNiveles.h"

#include <string>
#include <time.h>
#include <ctime>

#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"

ManejoDeNiveles::ManejoDeNiveles(){
    cargarNiveles();
}

void cerrarNiveles(list<Nivel*> niveles) {
    list<Nivel*>::iterator nivel;
    for(nivel = niveles.begin(); nivel != niveles.end(); nivel++){
        (*nivel) -> cerrar();
    }
}
void ManejoDeNiveles::procesar(){

    list<Nivel*>::iterator nivel;
    int i = 0;
    for(nivel = niveles.begin(); nivel != niveles.end(); nivel++){
        std::string nivel_actual = "nivel";
        i += 1;
        nivel_actual += std::to_string(i);
        (*nivel)->cargarNivel();
        if((*nivel)->procesar(nivel_actual.c_str())) {
            cerrarNiveles(niveles);
            break;
        }
        delay(5);
        (*nivel)->cerrar();
    }
}

void ManejoDeNiveles::delay(int seg){
    for(int i = time(NULL) + seg; time(NULL) != i; time(NULL));
}

void ManejoDeNiveles::cargarNiveles(){

    Nivel1* mapa1 = new Nivel1();
    Nivel2* mapa2 = new Nivel2();
    Nivel3* mapa3 = new Nivel3();

    niveles.push_back(mapa1);
    niveles.push_back(mapa2);
    niveles.push_back(mapa3);
}
