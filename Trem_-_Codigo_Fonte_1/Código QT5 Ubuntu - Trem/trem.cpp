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

Trem::Trem(int ID, int x, int y, std::vector<Trava*> trava){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    podeMover = true;
    objetosTrava = trava;
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
            for(Trava* trava : objetosTrava){
                std::cout << "id da trava: "<< trava->idTremPercorrendo<<std::endl;
            }
        }
    }
}

bool Trem::checkPossoMover(){
    if(podeMover){
        //QMutex mutex;
        //mutex.lock();
        for(Trava* trava : objetosTrava){

            std::cout <<"caminho está livre: "<< trava->caminhoLivre <<std::endl;
            std::cout <<"id trava: "<< trava->idTremPercorrendo << std::endl;
            std::cout <<"id trem: "<< this->ID << std::endl;
            if(trava->estaPerto(x,y)){
                std::cout << "eu sou a thread "<<ID<<"X: "<<x<<" Y"<<y<<std::endl;
                //std::cout << trava->caminhoLivre << " " << trava->idTremPercorrendo <<" " << ID << std::endl;
                if(!trava->caminhoLivre){
                    return false;
                }else{
                    std::cout << "entrei aqui: "<<this->ID <<std::endl;
                    trava->caminhoLivre = false;
                    trava->idTremPercorrendo = ID;
                    CheckSaindo(trava);
                }
            }
            //mutex.unlock();
        }
        return true;
    }
    return false;

}

int Trem::verificaAndar(std::vector<Trava *> travas){
    for(Trava* trava : travas){
        trava->getEntradaTrava();
    }
    return 0;
}

void Trem::CheckSaindo(Trava* trava){
    if(trava->geometria.x() == x+10 || trava->geometria.y() == y+10 ||  trava->geometria.x() == x-10 || trava->geometria.y() == y-10){
       trava->caminhoLivre = true;
       trava->idTremPercorrendo = 0;
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






