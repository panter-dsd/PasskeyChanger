#include <QtCore/QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
		: QMainWindow (parent), ui_ (new Ui::MainWindow)
{
	ui_->setupUi (this);

}

MainWindow::~MainWindow ()
{
}

void MainWindow::changeEvent (QEvent* e)
{
	QMainWindow::changeEvent (e);

	switch (e->type()) {

		case QEvent::LanguageChange:
			ui_->retranslateUi (this);
			break;

		default:
			break;
	}
}
