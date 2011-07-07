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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
class MainWindow;
}

class AbstractPasskeyChanger;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow (QWidget *parent = 0);
	virtual ~MainWindow ();

protected:
	void changeEvent (QEvent *e);

private:
	void initAbstractPasskeyChangers ();
	void initSettingWidgets ();

	void loadSettings ();
	void saveSettings () const;

	void connectPasskeyChanger (AbstractPasskeyChanger *passkeyChanger);
	void disconnectPasskeyChanger (AbstractPasskeyChanger *passkeyChanger) const;

private Q_SLOTS:
	void start ();
	void pageChanged (int pageNumber);

	void stateChanged (bool isReady);
	void configurationComplete ();

	void passkeyTextChanged (const QString &text);

	void createBackupChanged (int value);

private:
	Ui::MainWindow *ui_;
	typedef QVector <AbstractPasskeyChanger*> AbstractPasskeyChangers;
	AbstractPasskeyChangers abstractPasskeyChangers_;
	AbstractPasskeyChanger *currentChanger_;
};

#endif // MAINWINDOW_H
