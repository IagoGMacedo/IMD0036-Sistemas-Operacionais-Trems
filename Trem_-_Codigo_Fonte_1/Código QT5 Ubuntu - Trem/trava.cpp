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
    std::cout << "X da label "<<geometria.x() << "Y da label"<<geometria.y()<<std::endl;
    std::cout << "X parametro "<<x << "Y parametro"<<y<<std::endl;
    if(caminhoHorizontal){
        if(geometria.x() == x && (geometria.y() == y+20 || geometria.y() == y-20)){
            return true;
        }
    } else if(geometria.y() == y && (geometria.x() == x+20 || geometria.x()) == x-20){
        std::cout << "true" <<std::endl;
            return true;
        }
    return false;
}

std::pair<int, int> Trava::getEntradaTrava(){
    return this->entradaTrava;
}

std::pair<int,int> Trava::getSaidaTrava(){
    return this->saidaTrava;
}
