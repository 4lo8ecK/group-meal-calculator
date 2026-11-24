#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <foodcalc/foodcalc.h>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QMainWindow win;
	win.resize(1280, 720);
	win.setWindowTitle("Просто проверка этой фигни");
	
	auto* layout = new QVBoxLayout(&win); 
	auto* lbl = new QLabel("Проверка работоспособности этой херни", &win);
	// auto* btn = new QPushButton("Пшёл нах, сука", &win);
	// btn->resize(30, 6);

	layout->addWidget(lbl, 1, Qt::AlignCenter);
	// layout->addWidget(btn, 1);

	win.show();
	return app.exec();
}