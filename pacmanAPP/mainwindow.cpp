#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>


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

    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/Imagenes/background_level1_pacman (1)")));

    DrawTablero("tablero.txt");

    timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(animar()));
    connect(this,SIGNAL(aviso(int)),this,SLOT(aumentarScore()));

    timer->start(50);

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
            moverIz = false;
        }
        else personaje->moverL();
    }
    if(moverDe){
        if (Colision()){
            moverDe = false;
        }
        else personaje->moverR();
    }
    if(moverAr){
        if (Colision()){
            moverAr = false;
        }
        else personaje->moverU();
    }
    if(moverAb){
        if (Colision()){
            moverAb = false;
        }
        else personaje->moverD();
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
    if(evento->key() == Qt::Key_Z){
        moverAb = true;
        moverIz=false;
        moverDe=false;
        moverAr=false;
    }
    if(evento->key() == Qt::Key_A){
        moverIz = true;
        moverDe=false;
        moverAr=false;
        moverAb=false;
    }
    if(evento->key() == Qt::Key_S){
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

        pos = linea.find(":");
        numero = linea.substr(0, pos);
        _w = stoi(numero);
        linea.erase(0, pos + 1);

        _h = stoi(linea);

        Paredes.push_back(new QGraphicsRectItem(_x,_y,_w,_h));
        miEscena->addItem(Paredes.back());
    }
    tablero.close();
}

bool MainWindow::Colision()
{
    QList<QGraphicsRectItem*>::Iterator it;
    for (it=Paredes.begin(); it!=Paredes.end(); it++){
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
