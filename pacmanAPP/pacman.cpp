#include "pacman.h"

pacman::pacman()
{
}

pacman::pacman(int x, int y, int r)
{
    this->posx=x;
    this->posy=y;
    this->radio=r;
    velocidad=3;
    setPos(posx, posy);
}

QRectF pacman::boundingRect() const
{
    return QRectF(posx,posy,2*radio,2*radio);
}

void pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/Imagenes/img_pacman_01");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void pacman::moverU()
{
    posy = posy-velocidad;
    setPos(posx, posy);
}

void pacman::moverD()
{
    posy = posy+velocidad;
    setPos(posx, posy);
}

void pacman::moverL()
{
    posx = posx-velocidad;
    setPos(posx, posy);
}

void pacman::moverR()
{
    posx = posx+velocidad;
    setPos(posx, posy);
}
