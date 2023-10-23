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

    //Cria o trem com seu (ID, posição X, posição Y)
    /*
    trem1 = new Trem(1,150,30); // 60,30
    trem2 = new Trem(2,420,30); // 330,30
    trem3 = new Trem(3,10,150);
    trem4 = new Trem(4,280,150);
    trem5 = new Trem(5,550,150);
    */

    //declaração das travas
    Trava *trava1 =  new Trava(0, std::make_pair(420, 30), std::make_pair(420,150));
    Trava *trava2 =  new Trava(1, std::make_pair(150,150), std::make_pair(280,150));
    Trava *trava3 =  new Trava(2, std::make_pair(280,150), std::make_pair(420,150));
    Trava *trava4 =  new Trava(3, std::make_pair(420,150), std::make_pair(550,150));
    Trava *trava5 =  new Trava(4, std::make_pair(550,150), std::make_pair(690,150));
    Trava *trava6 =  new Trava(5, std::make_pair(280,150), std::make_pair(280,270));
    Trava *trava7 =  new Trava(6, std::make_pair(550,150), std::make_pair(550,270));
    std::vector<Trava*> travasT1;
    std::vector<Trava*> travasT2;
    std::vector<Trava*> travasT3;
    std::vector<Trava*> travasT4;
    std::vector<Trava*> travasT5;

    //travas do trem1
    travasT1.push_back(trava1);
    travasT1.push_back(trava2);
    travasT1.push_back(trava3);

    //travas do trem2
    travasT2.push_back(trava1);
    travasT2.push_back(trava4);
    travasT2.push_back(trava5);

    //travas do trem3
    travasT3.push_back(trava2);
    travasT3.push_back(trava6);

    //travas do trem4
    travasT4.push_back(trava3);
    travasT4.push_back(trava4);
    travasT4.push_back(trava6);
    travasT4.push_back(trava7);

    //travas do trem5
    travasT5.push_back(trava5);
    travasT5.push_back(trava7);


    //inicializando os semaforos e mutex
    for(int i = 0; i <7; i++){
        sem_init(&s[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);

    //inicializando os trems
    trem1 = new Trem(1,ui->label_trem1->x(),ui->label_trem1->y(), travasT1);
    trem2 = new Trem(2,ui->label_trem2->x(),ui->label_trem2->y(), travasT2);
    trem3 = new Trem(3,ui->label_trem3->x(),ui->label_trem3->y(), travasT3);
    trem4 = new Trem(4,ui->label_trem4->x(),ui->label_trem4->y(), travasT4);
    trem5 = new Trem(5,ui->label_trem5->x(),ui->label_trem5->y(), travasT5);






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
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
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

