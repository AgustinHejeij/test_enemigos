#include "Nivel.h"
#include "NaveJugador.h"
#include "NaveEnemiga.h"
#include "Temporizador.h"

Nivel::Nivel(){}

int current_time_nanoseconds(){
    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);
    return tm.tv_nsec;
}

int Nivel::get_width(){
    srand( current_time_nanoseconds() * 1000000000);
    return rand() % (sdl.getScreenWidth()-100);
}

int Nivel::get_height(){
    srand( current_time_nanoseconds() * 1000000000);
    return rand() % sdl.getScreenHeight();
}

double distanceSquared( int x1, int y1, int x2, int y2 ){
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

bool checkCollision(NaveEnemiga* enemigo, list<NaveEnemiga*> naves) {

    list<NaveEnemiga*>::iterator pos;

    pos = naves.begin();
    while(pos != naves.end()) {
        if(enemigo -> checkCollisionEnemigos( enemigo , *pos )) return true;
        pos++;
    }
    naves.push_back(enemigo);
    return false;
}

list<NaveEnemiga*> Nivel::crear_enemigos(const char* nivel){
        int cantidad = 0;
        list<NaveEnemiga*> enemigos;
        list<NaveEnemiga*>naves_aux;

        int cantidad_enemigos_1 = json.get_cantidad_enemigo(nivel, "cantidad_enemigo_1");
        std::string enemigo1 = json.get_sprite_nave("enemigas", "enemigo1");
        const char* sEnemigo1 = enemigo1.c_str();

        for( int j=0; j<= 6; j+=1) {

            for(int i = 1; i <= (int)cantidad_enemigos_1/6; i++){
                cantidad+=1;
                if(cantidad > cantidad_enemigos_1) break;
                NaveEnemiga* enemigo = new NaveEnemiga(800 + 750*j + get_width() % 750, get_height(), sEnemigo1, 1);
                while(checkCollision(enemigo, naves_aux)) {
                    enemigo -> cerrarNave();
                    enemigo = new NaveEnemiga(800 + 750*j + get_width() % 750, get_height(), sEnemigo1, 1);
                }
                logger.debug("Se creó una nave enemiga 1");
                enemigos.push_back(enemigo);
            }
        }

        cantidad = 0;
        int cantidad_enemigos_2 = json.get_cantidad_enemigo(nivel, "cantidad_enemigo_2");
        std::string enemigo2 = json.get_sprite_nave("enemigas", "enemigo2");
        const char* sEnemigo2 = enemigo2.c_str();

        for( int j=0; j<= 6; j+=1) {
            for(int i = 1; i <= (int)cantidad_enemigos_2/6; i++){
                cantidad+=1;
                if(cantidad > cantidad_enemigos_2) break;
                NaveEnemiga* enemigo = new NaveEnemiga(800 + 750*j + get_width() % 750, get_height(), sEnemigo2, 1);
                while(checkCollision(enemigo, naves_aux)) {
                    enemigo -> cerrarNave();
                    enemigo = new NaveEnemiga(800 + 750*j + get_width() % 750, get_height(), sEnemigo2, 1);
                }
                logger.debug("Se creó una nave enemiga 2");
                enemigos.push_back(enemigo);
            }
        }

        cantidad = 0;
        naves_aux.clear();
        if(naves_aux.empty()) printf("se vacio");

        int cantidad_enemigos_3 = json.get_cantidad_enemigo(nivel, "cantidad_enemigo_3");
        std::string enemigo3 = json.get_sprite_nave("enemigas", "enemigo3");
        const char* sEnemigo3 = enemigo3.c_str();

        for( int j=1; j<= 6; j+=1) {

            for(int i = 1; i <= (int)cantidad_enemigos_3/6; i++){

                cantidad+=1;
                if(cantidad > cantidad_enemigos_3) break;
                NaveEnemiga* enemigo = new NaveEnemiga(-750*j+get_width()%750, get_height(), sEnemigo3, -1);
                while(checkCollision(enemigo, naves_aux)) {
                    enemigo -> cerrarNave();
                    enemigo = new NaveEnemiga(-750*j+get_width()%750, get_height(), sEnemigo3, -1);
                }
                logger.debug("Se creó una nave enemiga 3");
                enemigos.push_back(enemigo);

            }

        }

        cantidad = 0;
        int cantidad_enemigos_4 = json.get_cantidad_enemigo(nivel, "cantidad_enemigo_4");
        std::string enemigo4 = json.get_sprite_nave("enemigas", "enemigo4");
        const char* sEnemigo4 = enemigo4.c_str();

        for( int j=1; j<= 6; j+=1) {

            for(int i = 1; i <= (int)cantidad_enemigos_4/6; i++){
                cantidad+=1;
                if(cantidad > cantidad_enemigos_4) break;
                NaveEnemiga* enemigo = new NaveEnemiga(-750*j+get_width()%750, get_height(), sEnemigo4, 1);
                while(checkCollision(enemigo, naves_aux)) {
                    enemigo -> cerrarNave();
                    enemigo = new NaveEnemiga(-750*j+get_width()%750, get_height(), sEnemigo4, 1);
                }
                logger.debug("Se creó una nave enemiga 3");
                enemigos.push_back(enemigo);
            }
        }

        return enemigos;
}

bool Nivel::procesar(const char* nivel){

	    bool quit = false;
	    bool fin_mapa = false;

	    //Inicializo el temporizador. La duracion de cada nivel podriamos tomarla del archivo Json
	    Temporizador temporizador;
	    temporizador.iniciar();

        NaveJugador* jugador = new NaveJugador( sdl.getScreenWidth() / 4, sdl.getScreenWidth() / 4);
        logger.debug("Se creó a la nave del jugador");

        list<NaveEnemiga*> enemigos = crear_enemigos(nivel);

	    logger.info("Se creó el arreglo de enemigos");

	    // Mientras que siga corriendo la app               //Puse solo 5 segundos para probar
	    while( usuarioNoRequieraSalir(quit)  && (temporizador.transcurridoEnSegundos() <= 5) ) {
		    while( hayEventos() ){
		         if( eventoEsSalir() ) quit = true;
			      jugador->handleEvent( e );
			 }

			jugador->mover(enemigos);

            SDL_SetRenderDrawColor( sdl.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( sdl.getRenderer() );
			fin_mapa = renderBackground();

			if(!fin_mapa){
                 //Scroll background
                jugador->renderizar();

                //Todo este bloque deberiamos declararlo en otro lado
                list<NaveEnemiga*>::iterator pos;
                for(pos = enemigos.begin(); pos != enemigos.end(); pos++){
                    (*pos)->mover( jugador );
                    (*pos)->renderizar();
                }
                //Hasta aca
			}
			SDL_RenderPresent( sdl.getRenderer() );

        }

        // CIERRA LAS NAVES
        jugador->cerrarNave();
        list<NaveEnemiga*>::iterator pos;
        for(pos = enemigos.begin(); pos != enemigos.end(); pos++){
            (*pos)->cerrarNave();
        }
        logger.info("Finalizó el nivel");
        gFinNivel.render(0,0);
        SDL_RenderPresent( sdl.getRenderer() );
        logger.info("Se renderizo el final del nivel");

        return quit;
}

void Nivel::cerrar(){}

void Nivel::cargarNivel(){}

bool Nivel::renderBackground(){return true;}
