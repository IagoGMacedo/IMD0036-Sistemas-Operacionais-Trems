#include "trava.h"
#include <iostream>
#include <utility>

Trava::Trava(int id, std::pair<int,int> entrada, std::pair<int,int> saida){
    idTrava = id;
    idTremPercorrendo = -1;
    entradaTrava = entrada;
    saidaTrava = saida;

}

int Trava::estaPerto(int x, int y, bool sentidoNormal){
    //std::cout << "X da entrada "<< entradaTrava.first << "Y da entrada"<<entradaTrava.second<<std::endl;
    //std::cout << "X da saida "<< saidaTrava.first << "Y da saida"<<saidaTrava.second<<std::endl;
    //std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;
    //std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;

    //entrando por cima ou por baixo
    std::cout << y << std::endl;
    std::cout << x << std::endl;
    if((x == entradaTrava.first - 20 && y == entradaTrava.second) || (x == saidaTrava.first + 20 && y == saidaTrava.second)|| (x == entradaTrava.first && y == entradaTrava.second + 20)){
        std::cout << "y:"<<y<<" ytrava: "<< entradaTrava.second<<std::endl;
        return 1;
    }
    //saindo por cima ou por baixo
    if(((x == entradaTrava.first && y == entradaTrava.second) && sentidoNormal == false)||((x == saidaTrava.first && y == saidaTrava.second) && sentidoNormal == true)){
        //std::cout <<"saindo"<<std::endl;
        //std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;
        return 2;
    }
    //longe do semaforo
    return 0;
}

std::pair<int, int> Trava::getEntradaTrava(){
    return this->entradaTrava;
}

std::pair<int,int> Trava::getSaidaTrava(){
    return this->saidaTrava;
}

int Trava::getId(){
    return this->idTrava;
}
