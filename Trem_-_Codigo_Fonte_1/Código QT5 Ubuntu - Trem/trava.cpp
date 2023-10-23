#include "trava.h"
#include <iostream>
#include <utility>

Trava::Trava(QRect p_geometria, bool p_caminhoHorizontal, std::pair<int,int> entrada, std::pair<int,int> saida){
    geometria = p_geometria;
    caminhoHorizontal = p_caminhoHorizontal;
    idTremPercorrendo = -1;
    entradaTrava = entrada;
    saidaTrava = saida;

}

int Trava::estaPerto(int x, int y, bool saindo){
    //std::cout << "X da entrada "<< entradaTrava.first << "Y da entrada"<<entradaTrava.second<<std::endl;
    //std::cout << "X da saida "<< saidaTrava.first << "Y da saida"<<saidaTrava.second<<std::endl;
    //std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;
    //std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;

    //entrando por cima ou por baixo
    if((x == entradaTrava.first - 20 && y == entradaTrava.second) || (x == saidaTrava.first + 20 && y == saidaTrava.second)){
        //std::cout << "true com - 20 "<<y<<std::endl;
        return 1;
    }
    //saindo por cima ou por baixo
    if(((x == entradaTrava.first && y == entradaTrava.second) || (x == saidaTrava.first && y == saidaTrava.second)) && saindo == true){
        std::cout <<"saindo"<<std::endl;
        std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;
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
