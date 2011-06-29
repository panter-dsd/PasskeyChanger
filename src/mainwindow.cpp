/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  panter.dsd <panter.dsd@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QDebug>
#include <QtCore/QFile>

#include <QtGui/QFileDialog>
#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_LINUX
const QString defaultPath = QDir::homePath () + "/.local/share/data/qBittorrent/BT_backup/";
#endif

MainWindow::MainWindow (QWidget *parent)
	: QMainWindow (parent), ui_ (new Ui::MainWindow)
{
	ui_->setupUi (this);

	connect (ui_->pathToTorrentsButton_, SIGNAL (clicked()),
			 this, SLOT (setPathToTorrents()));
	connect (ui_->startButton_, SIGNAL (clicked()),
			 this, SLOT (start()));

	if (QFile::exists (defaultPath)) {
		ui_->pathToTorrentsEdit_->setText (defaultPath);
	}
}

MainWindow::~MainWindow ()
{
}

void MainWindow::changeEvent (QEvent *e)
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
						defaultPath);

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

