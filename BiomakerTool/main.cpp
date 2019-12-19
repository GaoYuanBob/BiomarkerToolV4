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
	// mkdir���ϲ�Ŀ¼������ʱ��������ʧ�ܡ����紴����c:\\test\test�������test�����ڣ���testҲ�������ˡ�Ŀ¼�Ѿ�����ʱ�᷵��false��
	// mkpath���ϲ�Ŀ¼������Ҳû��ϵ���Զ�һ�𴴽���Ŀ¼�Ѿ�����ʱ�᷵��true��
	dir.mkpath("./workspace");
	
	w.show();
	return a.exec();
}
