#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trem.h"
#include <QDebug>
#include <QQueue>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void updateInterface(int,int,int);
    void signalProcessing(int, bool);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_velocidade_t1_valueChanged(int value);

    void on_velocidade_t2_valueChanged(int value);

    void on_velocidade_t3_valueChanged(int value);

    void on_velocidade_t4_valueChanged(int value);

    void on_velocidade_t5_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    //Cria os objetos TREM's
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;

    // Prioridade de cada trem
    int prioridadeT1;
    int prioridadeT2;
    int prioridadeT3;
    int prioridadeT4;
    int prioridadeT5;

    // Lista de solicitacoes aos trilhos criticos por cada trem
    QQueue<int>* listaSolicitacoes1;
    QQueue<int>* listaSolicitacoes2;
    QQueue<int>* listaSolicitacoes3;
    QQueue<int>* listaSolicitacoes4;
    QQueue<int>* listaSolicitacoes5;
    QQueue<int>* listaSolicitacoes6;
    QQueue<int>* listaSolicitacoes7;
};

#endif // MAINWINDOW_H
