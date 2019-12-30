#pragma once

#include <QGraphicsRectItem>
#include <QPoint>

class GraphicsRectItem : public QGraphicsRectItem
{
	//Q_OBJECT
	
public:
	GraphicsRectItem(QPoint startPoint, int penType, QPoint localTopLeft=QPoint(-1,-1));
	~GraphicsRectItem() = default;
	enum { Type = 1000 + 1 };

	int type() const
	{
		return Type;
	}
	QPoint startPoint;
	QPoint localTopLeft;
	int penType;
	bool isCounted = false;
	Qt::CheckState check_state = Qt::Unchecked;

	int originScale = 1; // 创建时候的zt值
	int x_len, y_len;
};
