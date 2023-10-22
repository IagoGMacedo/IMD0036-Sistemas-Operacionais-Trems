#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <vector>
#include "trava.h"

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    Trem(int,int,int, std::vector<Trava*>, std::vector<int>);
    void run();         //função a ser executada pela thread
    int getVelocidade();
    void setVelocidade(int vel);


//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   bool podeMover; //Diz se o trem tem velocidade o suficiente para se mover
   bool saindo; //se o modo em que ele se movimenta irá leva-lo para entrada ou saida de uma "trava"
   std::vector<int> minhasTravas;
   bool checkPossoMover(); //função que analisará cada trava e ver se o trem pode se mexer
   int verificaAndar(std::vector<Trava*> travas);
   void sairTrava(int x, int y);
   void entrarTrava(int x, int y);

   int quantidadeTravas; //diz quantas travas esse trem possui
   std::vector<Trava*> objetosTrava;

};

#endif // TREM_H
