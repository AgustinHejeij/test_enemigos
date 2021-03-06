#ifndef NIVEL_H
#define NIVEL_H

#include <list>
#include "NaveEnemiga.h"
#include "Escenario.h"
#include "TextureW.h"

class Nivel: public Escenario {

    public:

        Nivel();
        int get_width();
        int get_height();
        list<NaveEnemiga*> crear_enemigos(const char* nivel);
        bool procesar(const char* nivel);
        virtual void cerrar();
        virtual void cargarNivel();
        virtual bool renderBackground();

        protected:

        TextureW gFinNivel;
};

#endif
