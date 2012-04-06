#include "TextureDisplay.h"
#include <QtCore/QVector>
#include <QtGui/QBrush>
#include <QtGui/QPainter>

TextureDisplay::TextureDisplay()
{
	addItem(&triangle);
}

TextureDisplay::TextureDisplay( qreal x, qreal y, qreal width, qreal height, QObject * parent)
:QGraphicsScene (x, y, width, height, parent)
{
	addItem(&triangle);
	addItem(&p1);
	addItem(&p2);
	addItem(&p3);
	p1.setFlag(QGraphicsItem::ItemIsMovable);
	p2.setFlag(QGraphicsItem::ItemIsMovable);
	p3.setFlag(QGraphicsItem::ItemIsMovable);
}

void TextureDisplay::setTexture(QString &file, QPointF &t1, QPointF &t2, QPointF &t3)
{
	background.load(file);

	QVector<QPointF> v;
	QPointF t1b(t1.x() -0.5, 0.5-t1.y());
	QPointF t2b(t2.x() -0.5, 0.5-t2.y());
	QPointF t3b(t3.x() -0.5, 0.5-t3.y());
	v.append(t1b*128);
	v.append(t2b*128);
	v.append(t3b*128);	
	QPolygonF p(v);
	//QPolygonF p2 = triangle.mapFromScene(p);
	triangle.setPolygon(p);

	update(); 
}

void TextureDisplay::setCoordinates(QPointF &t1, QPointF &t2, QPointF &t3)
{
	QVector<QPointF> v;
	QPointF t1b(t1.x() -0.5, 0.5-t1.y());
	QPointF t2b(t2.x() -0.5, 0.5-t2.y());
	QPointF t3b(t3.x() -0.5, 0.5-t3.y());
	v.append(t1b*128);
	v.append(t2b*128);
	v.append(t3b*128);	
	QPolygonF p(v);
	//QPolygonF p2 = triangle.mapFromScene(p);
	triangle.setPolygon(p);

	update(); 
}


void TextureDisplay::drawBackground ( QPainter * painter, const QRectF & rect )
{
	painter->drawImage(rect, background);
}

void TextureDisplay::newTexture(QString& file)
{
	background.load(file);
	update(); 
}
