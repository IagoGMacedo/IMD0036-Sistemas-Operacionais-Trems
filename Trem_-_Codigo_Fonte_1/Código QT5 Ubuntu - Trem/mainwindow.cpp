#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include <utility>
#include <semaphore.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Cria os trens com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,ui->label_trem1->x(),ui->label_trem1->y());
    trem2 = new Trem(2,ui->label_trem2->x(),ui->label_trem2->y());
    trem3 = new Trem(3,ui->label_trem3->x(),ui->label_trem3->y());
    trem4 = new Trem(4,ui->label_trem4->x(),ui->label_trem4->y());
    trem5 = new Trem(5,ui->label_trem5->x(),ui->label_trem5->y());


    //inicializando os semaforos e mutex

    //semaforos das 7 regiões criticas
    for(int i = 0; i <7; i++){
        sem_init(&s[i], 0, 1);
    }

    //semaforo mutex
    sem_init(&mutex, 0, 1);

    //semaforos para as intersecções
    for(int i = 0; i <3; i++){
        sem_init(&duo[i], 0, 2);
    }


    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    //inicializando os trens
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    //encerrando os trens
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();

    //encerrando todos os semaforos
    for(int i = 0; i <7; i++){
        sem_destroy(&s[i]);
    }
    sem_destroy(&mutex);
    for(int i = 0; i <3; i++){
        sem_destroy(&duo[i]);
    }

    delete ui;
}

void MainWindow::on_sliderTrem1_valueChanged(int value)
{
    trem1->setVelocidade(200-value);
}

void MainWindow::on_sliderTrem2_valueChanged(int value)
{
    trem2->setVelocidade(200-value);
}


void MainWindow::on_sliderTrem3_valueChanged(int value)
{
    trem3->setVelocidade(200-value);
}

void MainWindow::on_sliderTrem4_valueChanged(int value)
{
    trem4->setVelocidade(200-value);
}


void MainWindow::on_sliderTrem5_valueChanged(int value)
{
    trem5->setVelocidade(200-value);
}

