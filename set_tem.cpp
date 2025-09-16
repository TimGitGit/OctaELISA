#include "set_tem.h"
#pragma execution_character_set("utf-8")
#include <QPen>
#include <QDebug>
#include <math.h>
set_tem::set_tem(QWidget *parent)
	: QWidget(parent), set_value(10), value_max(10), value_min(0), value(0), step(1)

{
    t = new QTimer(this);
    slip_value = set_value;
    save_value = slip_value;

    connect(t, SIGNAL(timeout()), this, SLOT(slipmove()));
    t->setInterval(10);
}

set_tem::~set_tem()
{}
void set_tem::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    int diameter1;
    int diameter2;

    diameter1 = qMin(width(), height()) * 2 / 5;
    center_x = width() / 2;
    center_y = height() / 2;
    diameter2 = diameter1 * 0.94;
    diameter3 = diameter1 * 0.5;
    QRectF rectf1(center_x - diameter1, center_y - diameter1, 2 * diameter1, 2 * diameter1);
    QRectF rectf2(center_x - diameter2, center_y - diameter2, 2 * diameter2, 2 * diameter2);
    float du_angle = set_value * 180 / (value_max - value_min);
    float angle = du_angle * 3.141596 / 180;
    float r = diameter1 / 2 + diameter2 / 2;
    x1 = center_x - r * cos(angle);
    y1 = center_y - r * sin(angle);
    QRectF rectf3(x1 - diameter3 / 2, y1 - diameter3 / 2, diameter3, diameter3);
    QRectF rectf4(x1 - diameter3 / 2 - 3, y1 - diameter3 / 2 - 3, diameter3 + 6, diameter3 + 6);

    QConicalGradient  qconicalgradient(center_x, center_y, 360);  //背景颜色渐变
    qconicalgradient.setColorAt(0, QColor(255, 14, 143));
    qconicalgradient.setColorAt(0.3, QColor(254, 62, 43));
    qconicalgradient.setColorAt(0.3, QColor(205, 46, 210));
    qconicalgradient.setColorAt(0.5, QColor(61, 160, 254));
    qconicalgradient.setColorAt(0.7, QColor(205, 46, 210));
    qconicalgradient.setColorAt(0.8, QColor(254, 62, 43));
    qconicalgradient.setColorAt(1, QColor(255, 14, 143));

    QRadialGradient qradialgradient(x1, y1, diameter3, x1, y1);
    qradialgradient.setColorAt(0, QColor(0, 0, 0, 255));
    qradialgradient.setColorAt(1, QColor(0, 0, 0, 0));



    painter.setPen(Qt::NoPen);
    painter.setBrush(qconicalgradient);
    painter.drawEllipse(rectf1);

    painter.setBrush(QColor(45, 42, 60));
    painter.drawEllipse(rectf2);

    painter.setBrush(qradialgradient);
    painter.drawEllipse(rectf4);

    painter.setBrush(QColor(248, 248, 255));
    painter.drawEllipse(rectf3);



    QPen pen;
    pen.setColor(QColor(89, 89, 89));
    painter.setFont(QFont("Microsoft Yahei", diameter3 * 0.2, QFont::Bold));
    painter.setPen(pen);
    painter.drawText(rectf3, Qt::AlignCenter, QString("%1").arg(abs(set_value)));

    pen.setColor(QColor(248, 248, 255));
    value = QString::number(value, 'f', 0).toFloat();
    painter.setFont(QFont("Microsoft Yahei", diameter2 * 0.3, QFont::Bold));
    painter.setPen(pen);
    painter.drawText(rectf2, Qt::AlignCenter, QString("%1μL").arg(set_value));
}
void set_tem::mousePressEvent(QMouseEvent* e) {

    //if (isEnabled()) {

        if (e->button() == Qt::LeftButton) {
            e->accept();
            float d = sqrt(pow((e->x() - x1), 2) + pow((e->y() - y1), 2));
            if (d < diameter3 / 2) {
                ispress = true;
            }

        }


    //}
}

void set_tem::mouseMoveEvent(QMouseEvent* e) {
    //if (isEnabled()) {
        if (ispress) {
            e->accept();
            float angle;
            if (center_y == e->y() || center_x == e->x()) {
                if (center_y == e->y()) {
                    if (center_x < e->x()) {
                        angle = 180;
                    }
                    else {
                        angle = 0;
                    }
                }
                if (center_x == e->x()) {
                    if (center_y < e->y())
                        angle = 270;
                    else
                        angle = 90;
                }
            }
            else {
                float y0 = center_y - e->y();
                float x0 = center_x - e->x();
                float k = y0 / x0;
                angle = atan(k) * 180.0 / 3.1415926;

                angle = angle + 180;
                if (e->y() < center_y && e->x() < center_x) {
                    angle = angle - 180;
                }
                else if (e->y() > center_y && e->x() < center_x) {
                    angle = angle + 180;
                }
            }
            slip_value = angle * (value_max - value_min) / 180;


            t->start(1);

        }

    //}

}
void set_tem::mouseReleaseEvent(QMouseEvent* e) {
    //if (isEnabled()) {
        if ((e->type() == QMouseEvent::MouseButtonRelease) && (e->button() == Qt::LeftButton)) {
            ispress = false;
        }
    //}
}
void set_tem::slipmove() {
    if (abs(slip_value - save_value) < 0.0001) {
        changed = true;
        emit toggled(changed);
        changed = false;
        t->stop();
    }
    else {
        step = (slip_value - save_value) / 10;
        save_value = save_value + step;
        set_value = QString::number(save_value, 'f', 0).toFloat();
        emit sendProValue(set_value);
        update();
    }
}
float set_tem::get_temperature() {   //得到温度
    return abs(set_value);
}
void set_tem::set_temperature(float v) {//设置温度
    set_value = v;
    update();
}

