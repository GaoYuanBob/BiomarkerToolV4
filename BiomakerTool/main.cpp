#include "BiomakerTool.h"
#include "CaptureGraphicsItem.h"

#include <QtWidgets/QApplication>
#include <QDir>

QVector<QRect> CaptureGraphicsItem::captureRects = QVector<QRect>();
int CaptureGraphicsItem::loadedNum = 0;

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	BiomakerTool w;

	//w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint);
	w.showMaximized();
	//w.setFixedSize(w.size());
	//w.setWindowFlags(Qt::Window);
	//w.layout()->setSizeConstraint(QLayout::SetFixedSize);
	w.setWindowTitle("Biomark Tool");
	w.setWindowIcon(QIcon("icon.bmp"));

	QDir dir;
	// mkdir：上层目录不存在时，创建会失败。比如创建“c:\\test\test”，如果test不存在，那test也创建不了。目录已经存在时会返回false。
	// mkpath：上层目录不存在也没关系，自动一起创建。目录已经存在时会返回true。
	dir.mkpath("./workspace");
	
	w.show();
	return a.exec();
}
