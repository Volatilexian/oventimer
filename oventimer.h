#ifndef OVENTIMER_H
#define OVENTIMER_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class OvenTimer : public QWidget
{
    Q_OBJECT
    
public:
    OvenTimer(QWidget *parent = 0);
    ~OvenTimer();

    void setDuration(int secs);
    int duration() const;
    void draw(QPainter *painter);

signals:
    void timeout();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QDateTime finishTime;
    QTimer *updateTimer;
    QTimer *finishTimer;
};

#endif // OVENTIMER_H
