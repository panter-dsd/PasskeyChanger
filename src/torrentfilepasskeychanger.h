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

#ifndef TORRENTFILEPASSKEYCHANGER_H
#define TORRENTFILEPASSKEYCHANGER_H

#include "abstractpasskeychanger.h"

class QLabel;
class QLineEdit;
class QToolButton;

class TorrentFilePasskeyChanger : public AbstractPasskeyChanger
{
	Q_OBJECT

public:
	TorrentFilePasskeyChanger (QObject *parent = 0);
	virtual ~TorrentFilePasskeyChanger();

protected:
	bool changeFilePasskey (const QString &fileName,
							const QString &oldPasskey,
							const QString &newPasskey);

private:
	TorrentFilePasskeyChanger (const TorrentFilePasskeyChanger &other);
	TorrentFilePasskeyChanger &operator= (const TorrentFilePasskeyChanger &other);

	void backupFile (const QString &fileName) const;

private:
	virtual QWidget *settingsWidget_p () const;
	virtual QByteArray saveState_p () const;
	virtual bool restoreState_p (const QByteArray &state);
	virtual bool isReady_p () const;
	virtual bool changePasskey_p (const QString &oldPasskey, const QString &newPasskey);
	virtual QString id_p () const {
		return "TorrentFilePasskeyChanger";
	}

	virtual QString name_p () const {
		return tr ("Torrent file");
	}

private Q_SLOTS:
	virtual void getFilePath ();

protected:
	QString defaultDir_;

	QWidget *settingsWidget_;
	QLabel *pathLabel_;
	QLineEdit *pathEdit_;
	QToolButton *pathButton_;
};

#endif // TORRENTFILEPASSKEYCHANGER_H
