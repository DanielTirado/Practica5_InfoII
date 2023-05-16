#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class pacman : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
private:
    int posx, posy, radio;
public:
    pacman();
    pacman(int x, int y, int r);
    QRectF boundingRect() const;

    QTimer *timer;
    QPixmap *pixmap;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void moverU();
    void moverD();
    void moverL();
    void moverR();

    int velocidad;

    float fila, columnas;

signals:

public slots:
    void Actualizacion();
};

#endif // PACMAN_H
