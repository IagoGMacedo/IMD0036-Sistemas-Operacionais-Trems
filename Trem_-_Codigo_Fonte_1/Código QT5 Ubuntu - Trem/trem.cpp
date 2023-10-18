#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    podeMover = true;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    int tamPercursoHoriz = this->x+270;
    int tamPercursoVert = this->y+120;
    int posInicialHoriz = x;
    int posInicialVert = y;
    while(true && podeMover){
        if (y == posInicialVert && x <tamPercursoHoriz)
            x+=10;
        else if (x == tamPercursoHoriz && y < tamPercursoVert)
            y+=10;
        else if (x > posInicialHoriz && y == tamPercursoVert)
            x-=10;
        else
            y-=10;
        emit updateGUI(ID, x,y);    //Emite um sinal
        msleep(velocidade);
    }
}

int Trem::getVelocidade(){
    return velocidade;
}

void Trem::setVelocidade(int vel){
    if(vel==200){
        podeMover = false;
    } else{
        velocidade = vel;
        podeMover = true;
    }

}






