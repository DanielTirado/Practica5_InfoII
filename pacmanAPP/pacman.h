#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>
#include <QPainter>

class pacman : public QGraphicsItem
{
    int posx, posy, radio;
public:
    pacman();
    pacman(int x, int y, int r);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
        const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moverU();
    void moverD();
    void moverL();
    void moverR();
    void choque(char dir);
    int velocidad;
};

#endif // PACMAN_H
