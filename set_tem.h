#pragma once

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
class set_tem : public QWidget
{
	Q_OBJECT

public:
	set_tem(QWidget *parent = nullptr);
	~set_tem();
	void set_temperature(float v);  //设置温度
	float get_temperature();  //得到温度

private:
public slots:
    void slipmove();
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
signals:
    void toggled(bool);
    void sendProValue(float);
private:
    float set_value;
    float value_max;
    float value_min;
    float value;
    float step;
    bool changed;

    QTimer* t;
    float slip_value;
    float save_value;

    double center_x;
    double center_y;
    float diameter3;

    double x1;
    double y1;

    bool ispress = false;
};
