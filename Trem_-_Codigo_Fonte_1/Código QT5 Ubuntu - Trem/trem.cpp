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
    sentidoNormal = false;
    velocidade = 100;
    velocidadeNaoZerada = true;
}

Trem::Trem(int ID, int x, int y, std::vector<Trava*> p_vetorTravas){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    velocidadeNaoZerada = true;
    vetorTravas = p_vetorTravas;
    sentidoNormal = false;
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
                            sentidoNormal = true;
                            x+=10;
                        }
                        else if (x == 420 && y < 150){
                            y+=10;
                            sentidoNormal= true;
                        }
                        else if (x > 150 && y == 150){
                            x-=10;
                            sentidoNormal = false;
                        }
                        else{
                            y-=10;
                            sentidoNormal = false;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 2: //Trem 2
                        if (y == 30 && x <690){
                            x+=10;
                            sentidoNormal = true;
                        }
                        else if (x == 690 && y < 150){
                            y+=10;
                            sentidoNormal = true;
                        }
                        else if (x > 420 && y == 150){
                            x-=10;
                            sentidoNormal = false;
                        }
                        else{
                            y-=10;
                            sentidoNormal = false;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 3:     //Trem 3
                        if (y == 150 && x < 280){
                            sentidoNormal = true;
                            x+=10;
                        }
                        else if (x == 280 && y < 270){
                            y+=10;
                            sentidoNormal= true;
                        }
                        else if (x > 10 && y == 270){
                            x-=10;
                            sentidoNormal = false;
                        }
                        else{
                            y-=10;
                            sentidoNormal = false;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 4:     //Trem 4
                        if (y == 150 && x < 550){
                            sentidoNormal = true;
                            x+=10;
                        }
                        else if (x == 550 && y < 270){
                            y+=10;
                            sentidoNormal= true;
                        }
                        else if (x > 280 && y == 270){
                            x-=10;
                            sentidoNormal = false;
                        }
                        else{
                            y-=10;
                            sentidoNormal = false;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 5:     //Trem 5
                        if (y == 150 && x < 820){
                            sentidoNormal = true;
                            x+=10;
                        }
                        else if (x == 820 && y < 270){
                            y+=10;
                            sentidoNormal= true;
                        }
                        else if (x > 550 && y == 270){
                            x-=10;
                            sentidoNormal = false;
                        }
                        else{
                            y-=10;
                            sentidoNormal = false;
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
    if(velocidadeNaoZerada){
        int estadoPosicao = verificaAndar();
        std::cout <<"estado posicao: "<<estadoPosicao <<std::endl;
        if (estadoPosicao == 0){
            return true;
        }
        else if(estadoPosicao == 1){
            sem_wait(&mutex);
            entrarTrava(x,y);
        }
        else if(estadoPosicao == 2){
            sem_wait(&mutex);
            sairTrava(x,y);
        }
        else if(estadoPosicao == 3){

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

int Trem::verificaAndar(){
    int result[3]= {0, 0, 0};
    for(int i = 0; i < vetorTravas.size(); i++){
        result[vetorTravas[i]->estaPerto(this->x, this->y, this->sentidoNormal)] += 1;
    }
    for(int i =0;i<3;i++){
        std::cout<<"result"<<i<<": "<<result[i]<<", ";
    }
    std::cout<<""<<std::endl;
    if(result[1] > 0){
        //entrando
        //saindo = true; //entrei no trilho, proximo passo é sair
        return 1;
    }
    if(result[2] > 0){
        //saindo
         //saindo = false;
        return 2; //estou saindo, então depois vou ENTRAR
    }
    if(result[1] > 0 && result[2] > 0){
        //saindo de uma trava e entrando em outra
        return 3;
    }
    return 0;
}
void Trem::entrarTrava(int x, int y){
    int indice;
    for(int i = 0; i < vetorTravas.size(); i++){
        std::pair<int, int> entrada = vetorTravas[i]->getEntradaTrava();
        std::pair<int, int> saida = vetorTravas[i]->getSaidaTrava();
        if((x == entrada.first - 20 && y == entrada.second) || (x == saida.first + 20 && y == saida.second)){
            indice = vetorTravas[i]->getId();
            break;
        }
    }

    sem_post(&mutex);
    sem_wait(&s[indice]);
}
void Trem::sairTrava(int x, int y){
    std::cout <<"pelo menos entrei no metodo sair"<<std::endl;
    int indice;
    for(int i = 0; i < vetorTravas.size(); i++){
        std::pair<int, int> entrada = vetorTravas[i]->getEntradaTrava();
        std::pair<int, int> saida = vetorTravas[i]->getSaidaTrava();
        //x == entrada.first && y == entrada.second + 20
        if(((x == entrada.first && y == entrada.second) && sentidoNormal == false)||((x == saida.first && y == saida.second) && sentidoNormal == true)){
            indice = vetorTravas[i]->getId();;
            break;
        }
    }
    sem_post(&mutex);
    sem_post(&s[indice]);
}

int Trem::getVelocidade(){
    return velocidade;
}

void Trem::setVelocidade(int vel){
    if(vel==200){
        velocidadeNaoZerada = false;
    } else{
        velocidade = vel;
        velocidadeNaoZerada = true;
    }

}






