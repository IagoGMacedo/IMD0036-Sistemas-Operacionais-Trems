#include "trava.h"
#include <iostream>
#include <utility>

Trava::Trava(QRect p_geometria, bool p_caminhoHorizontal, std::pair<int,int> entrada, std::pair<int,int> saida){
    geometria = p_geometria;
    caminhoLivre = true;
    caminhoHorizontal = p_caminhoHorizontal;
    idTremPercorrendo = -1;
    entradaTrava = entrada;
    saidaTrava = saida;

}

bool Trava::estaPerto(int x, int y){
    std::cout << "X da entrada "<< entradaTrava.first << "Y da entrada"<<entradaTrava.second<<std::endl;
    std::cout << "X da saida "<< saidaTrava.first << "Y da saida"<<saidaTrava.second<<std::endl;
    std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;
    std::cout << "X parametro: "<<x << "Y parametro: "<<y<<std::endl;

    //vertical
    if(x == entradaTrava.first - 20 && y == entradaTrava.second){
        std::cout << "true com - 20 "<<y<<std::endl;
        return true;
    }
    if(x == saidaTrava.first + 20 && y == entradaTrava.second){
        std::cout << "true com + 20 "<<y<<std::endl;
        return true;
    }
    std::cout << "false"<<y<<std::endl;
    return false;
}

std::pair<int, int> Trava::getEntradaTrava(){
    return this->entradaTrava;
}

std::pair<int,int> Trava::getSaidaTrava(){
    return this->saidaTrava;
}
