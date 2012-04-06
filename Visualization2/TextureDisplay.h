#pragma once

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsPolygonItem>
#include <QtCore/QPointF>
#include <QtCore/QString>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsSceneDragDropEvent>

class TextureDisplay : public QGraphicsScene
{

	Q_OBJECT

public:
	TextureDisplay();
	TextureDisplay( qreal x, qreal y, qreal width, qreal height, QObject * parent = 0 );

public slots:
	void setTexture(QString& file, QPointF& t1, QPointF& t2, QPointF& t3);
	void newTexture(QString& file);
	void setCoordinates(QPointF &t1, QPointF &t2, QPointF &t3);

signals:
	void newTextures(QPointF & t1, QPointF &t2, QPointF &t3);

protected:
	void drawBackground ( QPainter * painter, const QRectF & rect );
	//void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

private:
	QGraphicsPolygonItem triangle;
	QImage background;
	QGraphicsEllipseItem p1,p2, p3;
	
};