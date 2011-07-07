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

#ifndef ABSTRACTPASSKEYCHANGER_H
#define ABSTRACTPASSKEYCHANGER_H

#include <QtCore/QObject>

class QWidget;

class AbstractPasskeyChanger : public QObject
{
	Q_OBJECT

public:
	explicit AbstractPasskeyChanger (QObject *parent = 0)
	: QObject (parent), isCreateBackups_ (true)
	{}
	virtual ~AbstractPasskeyChanger() {}

	QWidget *settingsWidget () const {
		return settingsWidget_p ();
	}

	QByteArray saveState () const {
		return saveState_p ();
	}

	bool restoreState (const QByteArray &state) {
		return restoreState_p (state);
	}

	bool isReady () const {
		return isReady_p ();
	}

	bool changePasskey (const QString &oldPasskey, const QString &newPasskey) {
		return !oldPasskey.isEmpty()
			   && !newPasskey.isEmpty()
			   && changePasskey_p (oldPasskey, newPasskey);
	}

	QString id () const {
		return id_p ();
	}

	QString name () const {
		return name_p ();
	}

	bool isCreateBackups () const {
		return isCreateBackups_;
	}

	void setCreateBackups (bool value) {
		isCreateBackups_ = value;
	}

Q_SIGNALS:
	void stateChanged (bool isReady);
	void configurationComplete ();

private:
	AbstractPasskeyChanger (const AbstractPasskeyChanger &other);
	AbstractPasskeyChanger &operator= (const AbstractPasskeyChanger &other);

private:
	virtual QWidget *settingsWidget_p () const = 0;
	virtual QByteArray saveState_p () const = 0;
	virtual bool restoreState_p (const QByteArray &state) = 0;
	virtual bool isReady_p () const = 0;
	virtual bool changePasskey_p (const QString &oldPasskey, const QString &newPasskey) = 0;
	virtual QString id_p () const = 0;
	virtual QString name_p () const = 0;

protected:
	bool isCreateBackups_;
};

#endif // ABSTRACTPASSKEYCHANGER_H
