#ifndef TRAVA_H
#define TRAVA_H
#include <QtWidgets>
#include <QMutex>
#include <utility>

class Trava: public QMutex{
public:
    bool caminhoHorizontal; //indica se o caminho é horizontal ou vertical
    std::pair<int, int> entradaTrava;
    std::pair<int, int> saidaTrava;
    Trava(QRect p_geometria, bool p_caminhoHorizontal, std::pair<int,int> entrada, std::pair<int,int> saida);
    QRect geometria;
    int idTremPercorrendo; //caso tenha algum trem percorrendo, fica nesse id aqui
    //bool checkCaminhoLivre(int idTrem); //verifica se o caminho está livre, recebe o id do trem que deseja passar
    //Trem objetosTrems[2]; //vetor de trems que podem passar por aquela trava

    int estaPerto(int x, int y); //função que diz se o trem está na eminencia de entrar ou não
    std::pair<int, int> getEntradaTrava();
    std::pair<int, int> getSaidaTrava();
};

#endif // TRAVA_H
