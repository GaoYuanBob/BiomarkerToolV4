#pragma once

#include "CaptureGraphicsItem.h"
#include "GraphicsRectItem.h"

#include <QGraphicsView>
#include <QKeyEvent>
#include <CaptureLabel.h>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

Q_DECLARE_METATYPE(QMouseEvent*);

class LocalGraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	LocalGraphicsView(QWidget *parent = nullptr);
	~LocalGraphicsView() = default;
	void updateImage(QPoint startPoint, QPixmap& pixmap);
	void setRectLoadedState(bool state);
	void setRectSelectedState(GraphicsRectItem* rect_item);

	void setTiffSize(int tiffWidth, int tiffHeight, int sceneWidth, int sceneHeight);
	void setStartPoint(const QPointF& start_point);
	bool inBoundingBox(QPoint startPos);
	QPen& getPen(int penIndex) {
		if (penIndex == 1)	return this->redPen;
		if (penIndex == 2)	return this->greenPen;
		if (penIndex == 3) 	return this->bluePen;
		if (penIndex == 4) 	return this->yellowPen;
		return this->blackPen;
	}
	
	QPen& getOldDotPen(GraphicsRectItem* item) {
		const QPen oldPen = item->pen();
		if (oldPen.color() == Qt::red)	  return this->redDotPen;
		if (oldPen.color() == Qt::green)  return this->greenDotPen;
		if (oldPen.color() == Qt::blue)   return this->blueDotPen;
		if (oldPen.color() == Qt::yellow) return this->yellowDotPen;
		return this->blackDotPen;
	}
	
	QPen& getOldPen(GraphicsRectItem* item) {
		const QPen oldPen = item->pen();
		if (oldPen.color() == Qt::red)    return this->redPen;
		if (oldPen.color() == Qt::green)  return this->greenPen;
		if (oldPen.color() == Qt::blue)   return this->bluePen;
		if (oldPen.color() == Qt::yellow) return this->yellowPen;
		return this->blackPen;
	}

	void setNavigationWindowSize(int windowWidth, int windowHeight, float sclarFactor);
	
protected:
	// 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
	// 平移
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void localPloygonMousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	// 放大/缩小
	void wheelEvent(QWheelEvent *event) override;
	
public slots:
	void setZoomIn() {
		qDebug() << "Zoom in button pressed!";
		if (!isZoomIn) {
			isZoomIn = true;
			//this->scale(2, 2);
			this->scale(2, 2);
			emit sendZoomInState(isZoomIn);
			update();
		}
	}
	
	void setZoomOut(){
		qDebug() << "Zoom out button pressed!";
		if (isZoomIn) {
			isZoomIn = false;
			this->scale(0.5, 0.5);
			emit sendZoomInState(isZoomIn);
			update();
		}
	}
	void setRedPen(){
		this->penIndex = 1; 
		emit sendPenType(penIndex);
		update();
	}
	void setGreenPen(){
		this->penIndex = 2; 
		emit sendPenType(penIndex);
		update();
	}
	void setBluePen(){
		this->penIndex = 3;
		emit sendPenType(penIndex);
		update();
	}
	void setYellowPen(){
		this->penIndex = 4; 
		emit sendPenType(penIndex);
		update();
	}
	void setBlackPen(){
		this->penIndex = 5; 
		emit sendPenType(penIndex);
		update();
	}
	
public slots:
	void zoomIn();  // 放大
	void zoomOut();  // 缩小
	//void zoom(float scaleFactor); // 缩放 - scaleFactor：缩放的比例因子
	//void translate(QPointF delta);  // 平移
	//
	void circleMouseMoveEvent(QMouseEvent* event);
	void circleMousePressEvent(QMouseEvent* event);
	
	void circleMouseReleaseEvent(QMouseEvent* event);
	void ploygonMouseMoveEvent(QMouseEvent* event);
	int getRectCountInPolygon(QPainterPath graphics_path);
	void updateMarkerNumber();
	void updataCircleMarkerNumber();
	void updatePolygonMarkerNumber();
	void ploygonMousePressEvent(QMouseEvent* event);
	
	void ploygonMouseReleaseEvent(QMouseEvent* event);

	void setCircleDrawState(bool state) { this->is_circle_draw = state; }
	void setRegionState(bool state) { this->is_region_painting_set = state; }
	void getRemovePolygon(QGraphicsPathItem* item);
	void setNewPolygon(QPainterPath painter_path, double factor);
	void setNewPolygon(QPainterPath painter_path, double width_factor, double height_factor);
	void setNewPolygonFromGlobalGraphicsView(QGraphicsPathItem*& item);

	void updateZTinLocalView(int _zt) {
		zt = _zt;
	}

Q_SIGNALS:
	void startPointChanged(QPointF);
	void sendWheelUpState(bool);
	void sendZoomInState(bool);
	void sendRedLabelNumbers(int);
	void sendGreenLabelNumbers(int);
	void sendBlueLabelNumbers(int);
	void sendYellowLabelNumbers(int);
	void sendBlackLabelNumbers(int);
	//设置导航视图的透明颜色，发送该items
	void sendGraphicsItems(QList<QGraphicsItem*>&);
	void sendMakerNumber(QVector<QVector<int>>* zoomOutMakerNumber, QVector<QVector<int>>* zoomInMakerNumber);
	void sendPenType(int);
	void signal_SendCurrentRectItem(QGraphicsItem* item);
	void signal_SendCheckedState(GraphicsRectItem* item, int i);

	void sendShapeNumberMap(const QMap<QGraphicsEllipseItem*, int>& is, const QMap<QGraphicsPathItem*, int>& map);
	void sendSelectedShape(const QMap<QGraphicsEllipseItem*, int>& circle_number_map, const QMap<QGraphicsPathItem*, int>& polygon_number_map, QGraphicsItem* selectedItem);
	void sendPolygon(QGraphicsPathItem* cur_ploygon, const QPoint& point);
	void sendCircle(QGraphicsEllipseItem* cur_circle, const QPoint& point);
	void sendLocalPolygon(const QVector<QPointF>& vector, QGraphicsPathItem* path_item);
	
private:
	Qt::MouseButton m_translateButton;  // 平移按钮
	qreal m_translateSpeed;  // 平移速度
	qreal m_zoomDelta = 0.1;  // 缩放的增量
	bool m_bMouseTranslate;  // 平移标识
	QPoint m_lastMousePos;  // 鼠标最后按下的位置
	qreal m_scale;  // 缩放值
	
	int tiffWidth, tiffHeight;
	int sceneWidth, sceneHeight;
	int xOffset = 20, yOffset = 20;
	
	QPoint oldPoint;
	
	CaptureGraphicsItem* captureGraphicsItem;
	
	GraphicsRectItem* rectItem;
	QPointF rectTopLeft;
	QPoint oldStartPoint;
	QPixmap *oldPixmap;
	QGraphicsPixmapItem *pixmapItem;
	QPoint dragStartPoint, dragEndPoint;
	QPointF selectedRectTopLeft;
	bool isRectSeleted;
	GraphicsRectItem *selectedRectItem;
	QRect boundingBox;
	bool isZoomIn;
	QRect tiffRec;
	
	int penIndex;

	QPen redPen, greenPen, bluePen, yellowPen, blackPen;
	QPen redDotPen, greenDotPen, blueDotPen, yellowDotPen, blackDotPen;

	int navigationWindowWidth, navigationWindowHeight;
	float navigationScalarFactor;
	bool is_rect_item_loaded_from_file = false;

	//Debug 20190725
	bool is_control_key_push = false;
	QMap<QGraphicsPathItem*, int> ploygon_number_map;
	QMap<QGraphicsEllipseItem*, int> circle_number_map;

	QPainterPath cur_paint_path;
	QGraphicsPathItem *cur_ploygon, *selected_ploygon;
	QGraphicsEllipseItem *cur_circle, *selected_circle;
	
	int point_count = 0;
	QPointF start_point;
	bool is_ploygon_selected;
	int clicked_polygon_type;

	bool is_circle_draw = false;
	QList<QGraphicsEllipseItem*> circle_items;
	QPen circle_pen;
	QBrush circle_brush;
	bool is_circle_selected;

	int mouse_button_type = -1;
	QPointF old_top_left, old_point;

	//Debug 20190726
	bool is_region_painting_set = false;
	QVector<QPointF> polygon_region;

	int zt = 1;	// Zoom Times

public:
	QGraphicsScene* graphicsScene;
	QPoint startPoint;	// 绘制窗口的左上角在TIFF图像中的位置
	QVector<QVector<int>> zoomOutMakerNumber[5], zoomInMakerNumber[5];

	int redLabelNumber = 0, greenLabelNumber = 0, blueLabelNumber = 0, yellowLabelNumber = 0, blackLabelNumber = 0;
};
