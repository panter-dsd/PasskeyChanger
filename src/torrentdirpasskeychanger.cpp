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

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QFileDialog>

#include "torrentdirpasskeychanger.h"

TorrentDirPasskeyChanger::TorrentDirPasskeyChanger (QObject *parent)
	: TorrentFilePasskeyChanger (parent)
{
	pathLabel_->setText (tr ("Dir with torrent file"));

	fileMask_ << "*.torrent";
}

bool TorrentDirPasskeyChanger::isReady_p () const
{
	const QString path = pathEdit_->text ();

	return !path.isEmpty ()
		   && !QDir (path).entryList (fileMask_, QDir::Files).isEmpty();
}

bool TorrentDirPasskeyChanger::changePasskey_p (const QString &oldPasskey, const QString &newPasskey)
{
	const QString path = pathEdit_->text ();

	if (path.isEmpty () || !QFile::exists (path)
			|| oldPasskey.isEmpty() || newPasskey.isEmpty()
			|| oldPasskey.size () != newPasskey.size ()) {
		return false;
	}

	foreach (const QFileInfo &fi,
		QDir (path).entryInfoList (fileMask_, QDir::Files)) {
		if (!changeFilePasskey (fi.absoluteFilePath(), oldPasskey, newPasskey)) {
			return false;
		}
	}

	return true;
}

void TorrentDirPasskeyChanger::getFilePath ()
{
	const QString fileName = QFileDialog::getExistingDirectory (settingsWidget_,
							 tr ("Dir with torrents"),
							 defaultDir_);

	if (!fileName.isEmpty ()) {
		pathEdit_->setText (fileName);
		defaultDir_ = fileName;

		const bool isReady_ = isReady ();
		emit stateChanged (isReady_);

		if (isReady_) {
			emit configurationComplete ();
		}
	}
}

