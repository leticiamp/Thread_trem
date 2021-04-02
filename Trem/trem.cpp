#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void Trem::setVelocidade(int novaVelocidade) {
    this->velocidade = novaVelocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <330) {
                if (x == 300) { //Entrada na regiao critica
                    emit status(ID, true);
                    this->terminate();
                }
                x+=10;
            }
            else if (x == 330 && y < 150) {
                y+=10;
            }
            else if (x > 60 && y == 150) {
                if (x == 160) { //Saida da regiao critica
                    emit status(ID, false);
                }
                x-=10;
            }
            else {
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <600) {
                if (x == 570) { //Entrada na regiao critica
                    emit status(ID, true);
                    this->terminate();
                }
                if (x == 360) { //Saida na regiao critica
                    emit status(ID, false);
                }
                x+=10;
            }
            else if (x == 600 && y < 150) {
                y+=10;
            }
            else if (x > 330 && y == 150) {
                x-=10;
            }
            else {
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: // Trem 3
            if(y == 30 && x < 870) {
                if (x == 630) { //Saida na regiao critica
                    emit status(ID, false);
                }
                x += 10;
            }
            else if (x == 870 && y < 150) {
                y += 10;
            }
            else if (x > 600 && y == 150) {
                if (x == 760) { //Entrada na regiao critica
                    emit status(ID, true);
                    this->terminate();
                }
                x-=10;
            }
            else {
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: // Trem 4
            if(y == 150 && x < 460) {
                x += 10;
            }
            else if (x == 460 && y < 270) {
                y += 10;
            }
            else if (x > 190 && y == 270) {
                if (x == 430) { //Saida na regiao critica
                    emit status(ID, false);
                }
                x-=10;
            }
            else {
                if (x == 190 && y == 180) { //Entrada na regiao critica
                    emit status(ID, true);
                    this->terminate();
                }
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: // Trem 5
            if(y == 150 && x < 730) {
                x += 10;
            }
            else if (x == 730 && y < 270) {
                if (y == 180) { //Saida na regiao critica
                    emit status(ID, false);
                }
                y += 10;
            }
            else if (x > 460 && y == 270) {
                if (x == 490) { //Entrada na regiao critica
                    emit status(ID, true);
                    this->terminate();

                }
                x-=10;
            }
            else {
                y-=10;
            }
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




