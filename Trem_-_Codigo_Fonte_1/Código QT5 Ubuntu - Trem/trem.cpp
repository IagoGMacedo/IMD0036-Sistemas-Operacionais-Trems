#include "trem.h"
#include <QtCore>
#include <iostream>
#include <semaphore.h>
#include <utility>

sem_t s[7];
sem_t mutex;


//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    saindo = 1;
    velocidade = 100;
    podeMover = true;
}

Trem::Trem(int ID, int x, int y, std::vector<Trava*> trava, std::vector<int> minhasTravas){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    podeMover = true;
    objetosTrava = trava;
    this->minhasTravas = minhasTravas;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    /*
    int tamPercursoHoriz = this->x+270;
    int tamPercursoVert = this->y+120;
    int posInicialHoriz = x;
    int posInicialVert = y;
    */
    while(true){
        while(checkPossoMover()){
            /*
            if (y == posInicialVert && x <tamPercursoHoriz)
                x+=10;
            else if (x == tamPercursoHoriz && y < tamPercursoVert)
                y+=10;
            else if (x > posInicialHoriz && y == tamPercursoVert)
                x-=10;
            else
                y-=10;
            */
            switch(ID){
                    case 1:     //Trem 1
                        if (y == 30 && x <420){
                            saindo = 0;
                            x+=10;
                        }
                        else if (x == 420 && y < 150){
                            y+=10;
                            saindo = 1;
                        }
                        else if (x > 150 && y == 150){
                            x-=10;
                            saindo = 1;
                        }
                        else{
                            y-=10;
                            saindo = 0;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 2: //Trem 2
                        if (y == 30 && x <690){
                            x+=10;
                            saindo = 0;
                        }
                        else if (x == 690 && y < 150){
                            y+=10;
                            saindo = 1;
                        }
                        else if (x > 420 && y == 150){
                            x-=10;
                            saindo = 1;
                        }
                        else{
                            y-=10;
                            saindo = 0;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    default:
                        break;
                    }
            emit updateGUI(ID, x,y);    //Emite um sinal
            msleep(velocidade);
        }
    }
}

bool Trem::checkPossoMover(){
    if(podeMover){
        switch(verificaAndar(objetosTrava)){
        case 0:
            return true;
            break;
        case 1:
            //sem_wait(&mutex);
            break;
        case 2:
            break;
        case 3:
            break;
       }
    }
    return false;
}

int Trem::verificaAndar(std::vector<Trava *> travas){
    int result[3]= {0, 0, 0};
    for(int i = 0; i < minhasTravas.size(); i++){
        result[travas[minhasTravas[i]]->estaPerto(this->x, this->y)] += 1;
    }
    if(result[1] > 0 && result[2] > 0){
        return 3;
    }
    if(result[1] > 0){
        return 1;
    }
    if(result[2] > 0){
        return 2;
    }
    return 0;
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






