#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,60,90);
    trem2 = new Trem(2,460,30);
    trem3 = new Trem(3,870,90);
    trem4 = new Trem(4,330,270);
    trem5 = new Trem(5,600,270);

    listaSolicitacoes1 = new QQueue<int>;
    listaSolicitacoes2 = new QQueue<int>;
    listaSolicitacoes3 = new QQueue<int>;
    listaSolicitacoes4 = new QQueue<int>;
    listaSolicitacoes5 = new QQueue<int>;
    listaSolicitacoes6 = new QQueue<int>;
    listaSolicitacoes7 = new QQueue<int>;

    trilho1Livre = true;
    trilho2Livre = true;
    trilho3Livre = true;
    trilho4Livre = true;
    trilho5Livre = true;
    trilho6Livre = true;
    trilho7Livre = true;

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

    // Atribuindo um sinal a uma funcao
    connect(trem1,SIGNAL(status(int,bool)),SLOT(signalProcessing(int,bool)));
    connect(trem2,SIGNAL(status(int,bool)),SLOT(signalProcessing(int,bool)));
    connect(trem3,SIGNAL(status(int,bool)),SLOT(signalProcessing(int,bool)));
    connect(trem4,SIGNAL(status(int,bool)),SLOT(signalProcessing(int,bool)));
    connect(trem5,SIGNAL(status(int,bool)),SLOT(signalProcessing(int,bool)));

}

void MainWindow::signalProcessing(int ID, bool flag) {

    switch(ID){

    case 1:
        if (flag == true) {
            qInfo() << "Trem 1 entrou";
            // Colocando o T1 na lista de solicitacoes do trilho critico
            listaSolicitacoes1->enqueue(ID);
            listaSolicitacoes3->enqueue(ID);
        } else {
            qInfo() << "Trem 1 saiu";
            // Libera os trilhos
            trilho1Livre = true;
            trilho3Livre = true;
            // Removendo o T1 na lista de solicitacoes do trilho critico
            listaSolicitacoes1->removeAt(listaSolicitacoes1->indexOf(1));
            listaSolicitacoes3->removeAt(listaSolicitacoes3->indexOf(1));
        }
        break;
    case 2:
        if (flag == true) {
            qInfo() << "Trem 2 entrou";
            listaSolicitacoes2->enqueue(ID);
            listaSolicitacoes5->enqueue(ID);
            listaSolicitacoes4->enqueue(ID);
            listaSolicitacoes1->enqueue(ID);
        } else {
            qInfo() << "Trem 2 saiu";
            trilho2Livre = true;
            trilho5Livre = true;
            trilho4Livre = true;
            trilho1Livre = true;
            listaSolicitacoes2->removeAt(listaSolicitacoes2->indexOf(2));
            listaSolicitacoes5->removeAt(listaSolicitacoes5->indexOf(2));
            listaSolicitacoes4->removeAt(listaSolicitacoes4->indexOf(2));
            listaSolicitacoes1->removeAt(listaSolicitacoes1->indexOf(2));
        }
        break;
    case 3:
        if (flag == true) {
            qInfo() << "Trem 3 entrou";
            listaSolicitacoes6->enqueue(ID);
            listaSolicitacoes2->enqueue(ID);
        } else {
            qInfo() << "Trem 3 saiu";
            trilho2Livre = true;
            trilho6Livre = true;
            listaSolicitacoes6->removeAt(listaSolicitacoes6->indexOf(3));
            listaSolicitacoes2->removeAt(listaSolicitacoes2->indexOf(3));
        }
        break;
    case 4:
        if (flag == true) {
            qInfo() << "Trem 4 entrou";
            listaSolicitacoes3->enqueue(ID);
            listaSolicitacoes4->enqueue(ID);
            listaSolicitacoes7->enqueue(ID);
        } else {
            qInfo() << "Trem 4 saiu";
            trilho3Livre = true;
            trilho4Livre = true;
            trilho7Livre = true;
            listaSolicitacoes3->removeAt(listaSolicitacoes3->indexOf(4));
            listaSolicitacoes4->removeAt(listaSolicitacoes4->indexOf(4));
            listaSolicitacoes7->removeAt(listaSolicitacoes7->indexOf(4));
        }
        break;
    case 5:
        if (flag == true) {
            qInfo() << "Trem 5 entrou";
            listaSolicitacoes7->enqueue(ID);
            listaSolicitacoes5->enqueue(ID);
            listaSolicitacoes6->enqueue(ID);
        } else {
            qInfo() << "Trem 5 saiu";
            trilho7Livre = true;
            trilho5Livre = true;
            trilho6Livre = true;
            listaSolicitacoes7->removeAt(listaSolicitacoes7->indexOf(5));
            listaSolicitacoes5->removeAt(listaSolicitacoes5->indexOf(5));
            listaSolicitacoes6->removeAt(listaSolicitacoes6->indexOf(5));
        }
        break;
    }
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
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }

    prioridadeT1 = listaSolicitacoes1->indexOf(1) + listaSolicitacoes3->indexOf(1);
    prioridadeT2 = listaSolicitacoes2->indexOf(2) + listaSolicitacoes5->indexOf(2) + listaSolicitacoes4->indexOf(2) + listaSolicitacoes1->indexOf(2);
    prioridadeT3 = listaSolicitacoes6->indexOf(3) + listaSolicitacoes2->indexOf(3);
    prioridadeT4 = listaSolicitacoes3->indexOf(4) + listaSolicitacoes4->indexOf(4) + listaSolicitacoes7->indexOf(4);
    prioridadeT5 = listaSolicitacoes7->indexOf(5) + listaSolicitacoes5->indexOf(5) + listaSolicitacoes6->indexOf(5);

    // Verifica qual trem tem prioridade para voltar a andar
    if (prioridadeT1 <= prioridadeT2 && prioridadeT1 <= prioridadeT3 && prioridadeT1 <= prioridadeT4 && prioridadeT1 <= prioridadeT5 && trilho1Livre && trilho3Livre) {
        trilho1Livre = false;
        trilho3Livre = false;
        trem1->start();
    }
    if (prioridadeT2 <= prioridadeT1 && prioridadeT2 <= prioridadeT3 && prioridadeT2 <= prioridadeT4 && prioridadeT2 <= prioridadeT5 && trilho2Livre && trilho5Livre && trilho4Livre && trilho1Livre) {
        trilho2Livre = false;
        trilho5Livre = false;
        trilho4Livre = false;
        trilho1Livre = false;
        trem2->start();
    }
    if (prioridadeT3 <= prioridadeT2 && prioridadeT3 <= prioridadeT1 && prioridadeT3 <= prioridadeT4 && prioridadeT3 <= prioridadeT5 && trilho2Livre && trilho6Livre) {
        trilho2Livre = false;
        trilho6Livre = false;
        trem3->start();
    }
    if (prioridadeT4 <= prioridadeT2 && prioridadeT4 <= prioridadeT3 && prioridadeT4 <= prioridadeT1 && prioridadeT4 <= prioridadeT5 && trilho3Livre && trilho4Livre && trilho7Livre) {
        trilho3Livre = false;
        trilho4Livre = false;
        trilho7Livre = false;
        trem4->start();
    }
    if (prioridadeT5 <= prioridadeT2 && prioridadeT5 <= prioridadeT3 && prioridadeT5 <= prioridadeT4 && prioridadeT5 <= prioridadeT1 && trilho7Livre && trilho5Livre && trilho6Livre) {
        trilho7Livre = false;
        trilho5Livre = false;
        trilho6Livre = false;
        trem5->start();
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

void MainWindow::on_velocidade_t1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}

void MainWindow::on_velocidade_t2_valueChanged(int value)
{
    trem2->setVelocidade(value);
}

void MainWindow::on_velocidade_t3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}

void MainWindow::on_velocidade_t4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}

void MainWindow::on_velocidade_t5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}
