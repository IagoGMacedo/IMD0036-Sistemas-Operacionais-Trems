#include "trava.h"

Trava::Trava(QRect p_geometria, bool p_caminhoHorizontal)
{
    geometria = p_geometria;
    caminhoLivre = true;
    caminhoHorizontal = p_caminhoHorizontal;

}

bool Trava::estaPerto(int x, int y){
    if(x == geometria.x()-10 || y == geometria.y()-10){
        return true;
    }
    return false;
}
