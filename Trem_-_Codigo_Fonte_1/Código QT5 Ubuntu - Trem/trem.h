#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <vector>
#include <semaphore.h>
extern sem_t s[7];
extern sem_t mutex;
extern sem_t duo[3];
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

   bool velocidadeNaoZerada; //Diz se o trem tem velocidade o suficiente para se mover
   bool sentidoNormal; //se o modo em que ele se movimenta irá leva-lo para entrada ou saida de uma "trava"
};

#endif // TREM_H
