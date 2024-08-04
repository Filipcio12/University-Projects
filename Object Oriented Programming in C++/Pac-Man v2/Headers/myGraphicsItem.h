#pragma once

#include <QGraphicsPixmapItem>
#include <QRectF>

class myGraphicsItem : public QGraphicsPixmapItem {
  public:
	void setCenter(double x, double y)
	{
		QRectF rect = this->boundingRect();
		x -= rect.width() / 2;
		y -= rect.height() / 2;
		this->setPos(x, y);
	}

	double getCenterX() const
	{
		QRectF rect = this->boundingRect();
		double x = this->x();
		return (x + rect.width() / 2);
	}

	double getCenterY() const
	{
		QRectF rect = this->boundingRect();
		double y = this->y();
		return (y + rect.height() / 2);
	}

	double x2() const
	{
		QRectF rect = this->boundingRect();
		return (this->x() + rect.width());
	}

	double y2() const
	{
		QRectF rect = this->boundingRect();
		return (this->y() + rect.height());
	}
};
