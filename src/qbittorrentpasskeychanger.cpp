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

#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

#include <QtGui/QLineEdit>

#ifdef Q_OS_WIN
#include <QtGui/QDesktopServices>
#endif //Q_OS_WIN

#include "qbittorrentpasskeychanger.h"

const QString defaultPath =
#ifdef Q_OS_UNIX
	QDir::homePath () + "/.local/share/data/qBittorrent/BT_backup/";
#else //Q_OS_UNIX
#ifdef Q_OS_WIN
	QDesktopServices::storageLocation (QDesktopServices::ApplicationsLocation)
	+ "/Local/qBittorrent/BT_backup/";
#else //Q_OS_WIN
	QDir::homePath ();
#endif //Q_OS_WIN
#endif //Q_OS_UNIX

QBittorrentPasskeyChanger::QBittorrentPasskeyChanger (QObject *parent)
	: TorrentDirPasskeyChanger (parent)
{
	QStringList fileMask;
	fileMask << "*.torrent" << "*.fastresume";
	setFileMask (fileMask);

	setDefaultDir (defaultPath);
	pathEdit_->setText (defaultPath);

	disableTrackerExchangeOption ();
}

void QBittorrentPasskeyChanger::disableTrackerExchangeOption ()
{
	QSettings settings ("qBittorrent", "qBittorrent");
	settings.setValue ("Preferences/Advanced/TrackerExchange", false);
}
