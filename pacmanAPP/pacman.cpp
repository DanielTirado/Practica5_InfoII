#include "pacman.h"

pacman::pacman()
{
}

pacman::pacman(int x, int y, int r)
{
    this->posx=x;
    this->posy=y;
    this->radio=r;
    velocidad=1;
    setPos(posx, posy);

    timer = new QTimer();

    fila = 0;
    columnas = 0;

    pixmap = new QPixmap(":/Imagenes/sprites_pacman.png");

    timer->start(100);

    connect(timer,&QTimer::timeout,this,&pacman::Actualizacion);
}

QRectF pacman::boundingRect() const
{
    return QRectF(posx,posy,2*radio,2*radio);
}

void pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(posx,posy,*pixmap,columnas,fila,2*radio,2*radio);

}

void pacman::moverU()
{
    fila = 78;
    posy = posy-velocidad;
    setPos(posx, posy);

}

void pacman::moverD()
{
    fila = 56;
    posy = posy+velocidad;
    setPos(posx, posy);
}

void pacman::moverL()
{
    fila = 0;
    posx = posx-velocidad;
    setPos(posx, posy);
}

void pacman::moverR()
{
    fila = 26;
    posx = posx+velocidad;
    setPos(posx, posy);
}

void pacman::Actualizacion()
{
    columnas += 26;
    if (columnas >= 52){
        columnas = 0;}
}
