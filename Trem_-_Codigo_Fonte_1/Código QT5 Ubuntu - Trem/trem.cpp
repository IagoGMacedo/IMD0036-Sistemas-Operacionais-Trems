#include "trem.h"
#include <QtCore>
#include <iostream>
#include <semaphore.h>
#include <utility>
//Construtor
sem_t s[7];
sem_t mutex;
sem_t duo[3];
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
    velocidadeNaoZerada = true;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        while(velocidadeNaoZerada){
            switch(ID){
                    case 1:     //Trem 1
                        if (y == 30 && x <420){
                            x+=10;
                            if (x == 400){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[1]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[0]);
                            }
                        }
                        else if (x == 420 && y < 150){
                            y+=10;
                            if (y == 130){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[0]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[2]);
                            }
                        }
                        else if (x > 150 && y == 150){
                            x-=10;
                            if(x == 400){
                               sem_wait(&mutex);
                               sem_post(&s[0]);
                               sem_post(&duo[1]);
                               sem_post(&mutex);
                            }
                            if(x == 300){
                               sem_wait(&mutex);
                               sem_post(&mutex);
                               sem_wait(&s[1]);
                            }
                            if(x == 260){
                               sem_wait(&mutex);
                               sem_post(&s[2]);
                               sem_post(&duo[0]);
                               sem_post(&mutex);
                            }
                        }
                        else{
                            y-=10;
                            if(y == 130){
                               sem_wait(&mutex);
                               sem_post(&s[1]);
                               sem_post(&mutex);
                            }
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 2: //Trem 2
                        if (y == 30 && x <690){
                            x+=10;
                            if(x == 440){
                               sem_wait(&mutex);
                               sem_post(&s[0]);
                               sem_post(&mutex);
                            }
                        }
                        else if (x == 690 && y < 150){
                            y+=10;
                            if(y == 130){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[2]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[4]);
                            }
                        }
                        else if (x > 420 && y == 150){
                            x-=10;
                            if(x == 570){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[1]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[3]);
                            }
                            if(x == 530){
                               sem_wait(&mutex);
                               sem_post(&s[4]);
                               sem_post(&duo[2]);
                               sem_post(&mutex);
                            }
                            if(x == 440){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[0]);
                            }
                        }
                        else{
                            y-=10;
                            if(y == 130){
                               sem_wait(&mutex);
                               sem_post(&s[3]);
                               sem_post(&duo[1]);
                               sem_post(&mutex);
                            }
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 3:     //Trem 3
                        if (y == 150 && x < 280){
                            x+=10;
                            if(x == 130){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[0]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[1]);
                            }
                            if(x == 260){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[5]);
                            }
                        }
                        else if (x == 280 && y < 270){
                            y+=10;
                            if(y == 170){
                                sem_wait(&mutex);
                                sem_post(&s[1]);
                                sem_post(&duo[0]);
                                sem_post(&mutex);
                            }
                        }
                        else if (x > 10 && y == 270){
                            x-=10;
                            if(x == 260){
                                sem_wait(&mutex);
                                sem_post(&s[5]);
                                sem_post(&mutex);
                            }
                        }
                        else{
                            y-=10;
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 4:     //Trem 4
                        if (y == 150 && x < 550){
                            x+=10;
                            if(x == 300){
                                sem_wait(&mutex);
                                sem_post(&s[5]);
                                sem_post(&duo[0]);
                                sem_post(&mutex);
                            }
                            if(x == 400){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[3]);
                            }
                            if(x == 440){
                                sem_wait(&mutex);
                                sem_post(&s[2]);
                                sem_post(&duo[1]);
                                sem_post(&mutex);
                            }
                            if(x == 530){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[6]);
                            }

                        }
                        else if (x == 550 && y < 270){
                            y+=10;
                            if(y == 170){
                                sem_wait(&mutex);
                                sem_post(&s[3]);
                                sem_post(&duo[2]);
                                sem_post(&mutex);
                            }
                        }
                        else if (x > 280 && y == 270){
                            x-=10;
                            if(x == 530){
                                sem_wait(&mutex);
                                sem_post(&s[6]);
                                sem_post(&mutex);
                            }
                            if(x == 300){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[0]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[1]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[2]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[5]);
                            }
                        }
                        else{
                            y-=10;
                            if(y == 170){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[2]);
                            }
                        }
                        emit updateGUI(ID, x,y);    //Emite um sinal
                        break;
                    case 5:     //Trem 5
                        if (y == 150 && x < 820){
                            x+=10;
                            if(x == 570){
                                sem_wait(&mutex);
                                sem_post(&s[6]);
                                sem_post(&duo[2]);
                                sem_post(&mutex);
                            }
                            if(x == 710){
                                sem_wait(&mutex);
                                sem_post(&s[4]);
                                sem_post(&mutex);
                            }
                        }
                        else if (x == 820 && y < 270){
                            y+=10;
                        }
                        else if (x > 550 && y == 270){
                            x-=10;
                            if(x == 570){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&duo[2]);
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[6]);
                            }
                        }
                        else{
                            y-=10;
                            if(y == 170){
                                sem_wait(&mutex);
                                sem_post(&mutex);
                                sem_wait(&s[4]);
                            }
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






