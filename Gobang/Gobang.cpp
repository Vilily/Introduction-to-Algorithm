#include "Gobang.h"
#include <qpainter.h>
#include <qevent.h>
#include <qdebug.h>
#include <qpen>

Gobang::Gobang(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    QPoint point(100, 100);
    drawChessman(game.getPlayerOne(), &point);
    // ���� pixmap
    //QPixmap pixmap = QPixmap(100, 100);
    //pixmap.fill(Qt::gray);
    //QPainter painter(&pixmap);
    //painter.drawRect(10, 10, 80, 80);
    //painter.drawText(20, 30, "Hello World");

    // ʹ�� pixmap
    //ui.label->setPixmap(pixmap);
}

/**
* @brief ������¼���Ӧ
* @param event  ����¼�
*
* @return void
*/
void Gobang::mousePressEvent(QMouseEvent* event)
{
    qDebug() << event->x() << " " << event->y() << "\n";
}


/**
* @brief    ��������
* @param player �¸ò������
* @param point  ���Ƹò������������
*
* @return void
*/
void Gobang::drawChessman(Player* player, QPoint* point)
{
    this->update();
}


/**
* @brief    ��ͼ�¼�����
* @param event  ��ͼ�¼�
* @return void
*/
void Gobang::paintEvent(QPaintEvent* event)
{
    QPainter painter(this->ui.board);
    QPen pen;

    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter.drawEllipse(100, 100, 10, 10);
}
// 31 43, 92