#include "NaveEnemiga.h"

NaveEnemiga::NaveEnemiga(int x, int y, const char* sprite, int velocidad){
    crearNave(x, y, sprite);
    radio=getAltoImagen()/2;
    mVel = velocidad;
}

void NaveEnemiga::mover( NaveJugador* jugador ){

        setPosX(getPosX()-mVel);

        if( checkCollision( jugador , this ) ){
        setPosX(getPosX()+mVel);
        }

        /*if ( getPosX() - getRadio() < 0 ) {
            int posicionX = sdl.getScreenWidth();
            int posicionY = rand() % sdl.getScreenHeight();
            setPosX( posicionX );
            setPosY( posicionY );
        }

        //Esta comentado por ahora, porque la nave solo se mueve en el eje X
//    //Move the dot up or down
//    mPosY += mVelY;
//	desplazarColicionador();
//
//    //If the dot collided or went too far up or down
//    if( ( getPosY() - getColicionador().r < 0 ) || ( getPosY() + getColicionador().r > SCREEN_HEIGHT ) || checkCollision( getColicionador(), enemigo.getCollider() ) )
//    {
//        //Move back
//        mPosY -= mVelY;
//		desplazarColicionador();
//    }*/
}

void NaveEnemiga::renderizar(){
	gNaveTexture.render(getPosX() - getRadio(), getPosY() - getRadio());
}

int NaveEnemiga::getRadio(){
    return radio;
}

const char* NaveEnemiga::getImagen(){
    return imagen;
}

int NaveEnemiga::getAltoImagen(){
	return gNaveTexture.getHeight();
}

int NaveEnemiga::getAnchoImagen(){
	return gNaveTexture.getWidth();
}
