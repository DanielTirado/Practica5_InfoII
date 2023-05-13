#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    miEscena = new QGraphicsScene(0,0,420,466);
    ui->graphicsView->setScene(miEscena);

    personaje = new pacman(100,172,13);
    miEscena->addItem(personaje);

    score = 0;

    moverIz=false;
    moverDe=false;
    moverAr=false;
    moverAb=false;

    //ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/Imagenes/background_level1_pacman (1)")));

    DrawTablero("tablero.txt");

    timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(animar()));
    connect(this,SIGNAL(aviso(int)),this,SLOT(aumentarScore()));

    timer->start(15);

}

MainWindow::~MainWindow()
{
    delete miEscena;
    delete ui;

}

void MainWindow::animar()
{
    if(moverIz){
        if (Colision()){
            personaje->moverR();
            moverIz = false;
        }
        else personaje->moverL();
    }
    if(moverDe){
        if (Colision()){
            personaje->moverL();
            moverDe = false;
        }
        else personaje->moverR();
    }
    if(moverAr){
        if (Colision()){
            personaje->moverD();
            moverAr = false;
        }
        else personaje->moverU();
    }
    if(moverAb){
        if (Colision()){
            personaje->moverU();
            moverAb = false;
        }
        else personaje->moverD();
    }

    QList<QGraphicsRectItem*>::Iterator it;
    for (it=puntos.begin(); it!=puntos.end(); it++){
        if(personaje->collidesWithItem(*it)){

            if ((*it)->isVisible()){
                (*it)->hide();
                emit aviso(9);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key() == Qt::Key_W){
        moverAr = true;
        moverIz=false;
        moverDe=false;
        moverAb=false;
    }
    else if(evento->key() == Qt::Key_S){
        moverAb = true;
        moverIz=false;
        moverDe=false;
        moverAr=false;
    }
    else if(evento->key() == Qt::Key_A){
        moverIz = true;
        moverDe=false;
        moverAr=false;
        moverAb=false;
    }
    else if(evento->key() == Qt::Key_D){
        moverDe = true;
        moverAr=false;
        moverAb=false;
        moverIz=false;
    }
}

void MainWindow::DrawTablero(string fuenteFile)
{
    ifstream tablero;
    string linea;
    int _x, _y, _w, _h;

    tablero.open(fuenteFile);

    for (int NumL=0; NumL < 51; NumL++){
        getline(tablero,linea);

        int pos = 0;

        string numero;

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _x = stoi(numero);
        linea.erase(0, pos + 1);

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _y = stoi(numero);
        linea.erase(0, pos + 1);

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _w = stoi(numero);
        linea.erase(0, pos + 1);

        _h = stoi(linea);

        paredes.push_back(new QGraphicsRectItem(_x,_y,_w,_h));
        miEscena->addItem(paredes.back());
    }

    while (tablero.good()){
        getline(tablero,linea);

        int pos = 0;

        string numero;

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _x = stoi(numero);
        linea.erase(0, pos + 1);

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _y = stoi(numero);
        linea.erase(0, pos + 1);

        puntos.push_back(new QGraphicsRectItem(_x,_y, 5, 5));
        miEscena->addItem(puntos.back());

    }
    tablero.close();
}

bool MainWindow::Colision()
{
    QList<QGraphicsRectItem*>::Iterator it;
    for (it=paredes.begin(); it!=paredes.end(); it++){
        if(personaje->collidesWithItem(*it)){
            return true;
        }
    }
    return false;
}

void MainWindow::aumentarScore()
{
    score += 10;
    ui->lcdScore->display(score);
    std::cout<<score<<std::endl;
}
