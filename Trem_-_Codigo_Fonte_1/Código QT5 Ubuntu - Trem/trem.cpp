#include "trem.h"
#include <QtCore>
#include <iostream>
#include <semaphore.h>
#include <utility>
//Construtor
sem_t s[7];
sem_t mutex;
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
    saindo = 0;
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
                            saindo = false;
                            x+=10;
                        }
                        else if (x == 420 && y < 150){
                            y+=10;
                            saindo = true;
                        }
                        else if (x > 150 && y == 150){
                            x-=10;
                            saindo = true;
                        }
                        else{
                            y-=10;
                            saindo = false;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 2: //Trem 2
                        if (y == 30 && x <690){
                            x+=10;
                            saindo = false;
                        }
                        else if (x == 690 && y < 150){
                            y+=10;
                            saindo = true;
                        }
                        else if (x > 420 && y == 150){
                            x-=10;
                            saindo = true;
                        }
                        else{
                            y-=10;
                            saindo = false;
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
        int verificar = verificaAndar(objetosTrava);
        if (verificar == 0){
            return true;
        }
        else if(verificar == 1){
            sem_wait(&mutex);
            entrarTrava(x,y);
        }
        else if(verificar == 2){
            sem_wait(&mutex);
            sairTrava(x,y);
        }
        else if(verificar == 3){

        }
        return true;
        /*
        switch(verificaAndar(objetosTrava)){
        case 0:
            return true;
            break;
        case 1:
            sem_wait(&mutex);
            entrarTrava(x,y);
            sem_post(&mutex);
        case 2:
            sem_wait(&mutex);
            sairTrava(x,y);
            sem_post(&mutex);
            break;
        case 3:
            break;
       }
        return true;
       */
    }
    return false;
}

int Trem::verificaAndar(std::vector<Trava *> travas){
    int result[3]= {0, 0, 0};
    for(int i = 0; i < minhasTravas.size(); i++){
        result[travas[minhasTravas[i]]->estaPerto(this->x, this->y, this->saindo)] += 1;
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
void Trem::entrarTrava(int x, int y){
    int indice;
    for(int i = 0; i < minhasTravas.size(); i++){
        std::pair<int, int> entrada = objetosTrava[minhasTravas[i]]->getEntradaTrava();
        std::pair<int, int> saida = objetosTrava[minhasTravas[i]]->getSaidaTrava();
        if((x == entrada.first - 20 && y == entrada.second) || (x == saida.first + 20 && y == saida.second)){
            indice = i;
            break;
        }
    }
    int semValue;
    sem_post(&mutex);
    sem_wait(&s[0]);
    if (sem_getvalue(&s[0], &semValue) == 0) {
            std::cout << "O valor em entrada é: "<< semValue << std::endl;
        } else {
            std::cout << "Erro em entrada" << std::endl;
        }
}
void Trem::sairTrava(int x, int y){
    int indice;
    for(int i = 0; i < minhasTravas.size(); i++){
        std::pair<int, int> entrada = objetosTrava[minhasTravas[i]]->getEntradaTrava();
        std::pair<int, int> saida = objetosTrava[minhasTravas[i]]->getSaidaTrava();
        //x == entrada.first && y == entrada.second + 20
        if(((x == entrada.first && y == entrada.second) || (x == saida.first && y == saida.second)) && saindo == true){
            indice = i;
            break;
        }
    }
    int semValue;
    sem_post(&mutex);
    sem_post(&s[0]);
    if (sem_getvalue(&s[0], &semValue) == 0) {
            std::cout << "O valor em saida é: "<< semValue << std::endl;
        } else {
            std::cout << "Erro em saida" << std::endl;
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






