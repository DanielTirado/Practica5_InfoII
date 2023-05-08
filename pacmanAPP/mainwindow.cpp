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

    personaje = new pacman(100,100,15);
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
    if(moverIz)
        personaje->moverL();
    if(moverDe)
        personaje->moverR();
    if(moverAr)
        personaje->moverU();
    if(moverAb)
        personaje->moverD();
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

void MainWindow::aumentarScore()
{
    score += 10;
    ui->lcdScore->display(score);
    std::cout<<score<<std::endl;
}
