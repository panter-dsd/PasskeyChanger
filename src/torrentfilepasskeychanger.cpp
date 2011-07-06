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
#include <QtCore/QDataStream>

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QFileDialog>

#include "torrentfilepasskeychanger.h"

TorrentFilePasskeyChanger::TorrentFilePasskeyChanger (QObject *parent)
	: AbstractPasskeyChanger (parent), defaultDir_ (QDir::homePath ())
{
	settingsWidget_ = new QWidget ();

	pathLabel_ = new QLabel (tr ("Path to torrent file"), settingsWidget_);

	pathEdit_ = new QLineEdit (settingsWidget_);

	pathButton_ = new QToolButton (settingsWidget_);
	pathButton_->setText ("...");
	connect (pathButton_, SIGNAL (clicked (bool)), SLOT (getFilePath()));

	QHBoxLayout *layout = new QHBoxLayout ();
	layout->addWidget (pathLabel_);
	layout->addWidget (pathEdit_);
	layout->addWidget (pathButton_);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout (layout);
	mainLayout->addSpacerItem (new QSpacerItem (0,
		0,
		QSizePolicy::Preferred,
		QSizePolicy::Expanding));
	settingsWidget_->setLayout (mainLayout);
}

TorrentFilePasskeyChanger::~TorrentFilePasskeyChanger()
{

}

QWidget *TorrentFilePasskeyChanger::settingsWidget_p () const
{
	return settingsWidget_;
}

QByteArray TorrentFilePasskeyChanger::saveState_p () const
{
	QByteArray state;
	QDataStream stream (&state, QIODevice::WriteOnly);
	stream << defaultDir_;

	return state;
}

bool TorrentFilePasskeyChanger::restoreState_p (const QByteArray &state)
{
	QDataStream stream (state);

	QString path;
	stream >> path;

	if (!path.isEmpty()) {
		defaultDir_ = path;
	}

	return !path.isEmpty ();
}

bool TorrentFilePasskeyChanger::isReady_p () const
{

}

bool TorrentFilePasskeyChanger::changePasskey_p (const QString &oldPasskey, const QString &newPasskey)
{
	const QString fileName = pathEdit_->text ();

	if (fileName.isEmpty () || !QFile::exists (fileName)
			|| oldPasskey.isEmpty() || newPasskey.isEmpty()
			|| oldPasskey.size () != newPasskey.size ()) {
		return false;
	}

	const QByteArray oldPasskey_ = oldPasskey.toUtf8();

	const QByteArray newPasskey_ = newPasskey.toUtf8();

	QFile file (fileName);

	if (!file.open (QIODevice::ReadWrite)) {
		return false;
	}

	QByteArray data = file.readAll ();
	data.replace (oldPasskey_, newPasskey_);
	file.seek (0);
	file.write (data);
	file.close();

	return true;
}

void TorrentFilePasskeyChanger::getFilePath ()
{
	const QString fileName = QFileDialog::getOpenFileName (settingsWidget_,
							 tr ("Open torrent file"),
							 defaultDir_,
							 tr ("Torrent files (*.torrent)"));

	if (!fileName.isEmpty ()) {
		pathEdit_->setText (fileName);
		defaultDir_ = QDir (fileName).absolutePath ();
	}
}
