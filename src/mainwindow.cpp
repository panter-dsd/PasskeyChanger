#include <QtCore/QDebug>
#include <QtCore/QFile>

#include <QtGui/QFileDialog>
#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
		: QMainWindow (parent), ui_ (new Ui::MainWindow)
{
	ui_->setupUi (this);

	connect (ui_->pathToTorrentsButton_, SIGNAL (clicked()),
			 this, SLOT (setPathToTorrents()));
	connect (ui_->startButton_, SIGNAL (clicked()),
			 this, SLOT (start()));
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

void MainWindow::setPathToTorrents ()
{
	const QString dir = QFileDialog::getExistingDirectory (this,
						tr ("Dir with torrents"),
						QDir::homePath () + "/.local/share/data/qBittorrent/BT_backup/");

	if (!dir.isEmpty ()) {
		ui_->pathToTorrentsEdit_->setText (dir);
	}
}

void MainWindow::start ()
{
	const QString path = ui_->pathToTorrentsEdit_->text ();
	const QByteArray oldPasskey = ui_->oldPasskeyEdit_->text ().toUtf8();
	const QByteArray newPasskey = ui_->newPasskeyEdit_->text ().toUtf8();

	if (path.isEmpty () || oldPasskey.isEmpty() || newPasskey.isEmpty()) {
		return;
	}

	QDir dir (path);

	if (!dir.exists ()) {
		return;
	}

	const QStringList list = dir.entryList (QDir::Files);

	QProgressDialog d (this);

	d.setRange (0, list.size ());

	for (QStringList::const_iterator it = list.constBegin(),
			end = list.constEnd (); it != end; ++it) {
		d.setValue (d.value() + 1);
		QFile file (dir.absoluteFilePath (*it));

		if (!file.open (QIODevice::ReadWrite)) {
			continue;
		}

		QByteArray data = file.readAll ();
		data.replace (oldPasskey, newPasskey);
		file.seek (0);
		file.write (data);
		file.close();
	}

	QMessageBox::information (this, "", tr ("Complite"));
}

