#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QKeyEvent>
#include <string>
#include <QTimer>
#include <QPainter>
#include <iostream>

#include <pacman.h>
#include <QList>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void aviso(int);

public slots:
    void animar();
    void aumentarScore();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* miEscena;

    pacman *personaje;
    QTimer *timer;

    int score;

    bool moverIz;
    bool moverDe;
    bool moverAr;
    bool moverAb;

    QList<QGraphicsRectItem*>paredes;
    QList<QGraphicsEllipseItem*>puntos;

    void keyPressEvent(QKeyEvent *evento);
    void DrawTablero(string fuenteFile);
    bool Colision();

};

#endif // MAINWINDOW_H
