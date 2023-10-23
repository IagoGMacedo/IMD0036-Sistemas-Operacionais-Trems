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

Trem::Trem(int ID, int x, int y, std::vector<Trava*> p_vetorTravas, std::vector<int> p_vetorIdTravas){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    velocidadeNaoZerada = true;
    vetorTravas = p_vetorTravas;
    sentidoNormal = false;
    this->vetorIdTravas = p_vetorIdTravas;
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
    for(int i = 0; i < vetorIdTravas.size(); i++){
        result[vetorTravas[vetorIdTravas[i]]->estaPerto(this->x, this->y, this->sentidoNormal)] += 1;
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
    for(int i = 0; i < vetorIdTravas.size(); i++){
        std::pair<int, int> entrada = vetorTravas[vetorIdTravas[i]]->getEntradaTrava();
        std::pair<int, int> saida = vetorTravas[vetorIdTravas[i]]->getSaidaTrava();
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
    std::cout <<"pelo menos entrei no metodo sair"<<std::endl;
    int indice;
    for(int i = 0; i < vetorIdTravas.size(); i++){
        std::pair<int, int> entrada = vetorTravas[vetorIdTravas[i]]->getEntradaTrava();
        std::pair<int, int> saida = vetorTravas[vetorIdTravas[i]]->getSaidaTrava();
        //x == entrada.first && y == entrada.second + 20
        if(((x == entrada.first && y == entrada.second) && sentidoNormal == false)||((x == saida.first && y == saida.second) && sentidoNormal == true)){
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
        velocidadeNaoZerada = false;
    } else{
        velocidade = vel;
        velocidadeNaoZerada = true;
    }

}






