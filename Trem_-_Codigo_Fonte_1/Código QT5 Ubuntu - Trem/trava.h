#ifndef TRAVA_H
#define TRAVA_H
#include <QtWidgets>
#include <QMutex>

class Trava: public QMutex{
public:
    bool caminhoHorizontal; //indica se o caminho é horizontal ou vertical
    Trava(QRect p_geometria, bool p_caminhoHorizontal);
    QRect geometria;
    bool caminhoLivre;
    int idTremPercorrendo; //caso tenha algum trem percorrendo, fica nesse id aqui
    //bool checkCaminhoLivre(int idTrem); //verifica se o caminho está livre, recebe o id do trem que deseja passar
    //Trem objetosTrems[2]; //vetor de trems que podem passar por aquela trava

    bool estaPerto(int x, int y); //função que diz se o trem está na eminencia de entrar ou não
};

#endif // TRAVA_H
