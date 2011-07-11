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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

class QLabel;
class QTabWidget;
class QTextEdit;
class QToolButton;

#include <QtGui/QDialog>

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog (QWidget *parent = 0, Qt::WFlags f = Qt::WindowSystemMenuHint);
	virtual ~AboutDialog()
	{}

	void setLicenseText (const QString &text);

	void setAuthor (const QString &author) {
		author_ = author;
		printCopyright();
	}

	void setMail (const QString &mail) {
		mail_ = mail;
		printCopyright();
	}

	void setPhone (const QString &phone) {
		phone_ = phone;
		printCopyright();
	}

	void setLicense (const QString &license) {
		license_ = license;
		printCopyright();
	}

	void addThanks (const QString &name, const QString &email, const QString &typeWork) {
		QStringList l;
		l << name << email << typeWork;
		thanks_ << l;
		printThanks ();
	}

private:
	void printCopyright();
	void printThanks ();

private:
	QLabel *iconLabel_;
	QLabel *aboutLabel_;
	QToolButton *closeButton_;

	QTabWidget *tabWidget_;

	QTextEdit *copyrightView_;
	QTextEdit *thanksView_;
	QTextEdit *licenseView_;

	QString author_;
	QString mail_;
	QString phone_;
	QString license_;

	QList<QStringList> thanks_;
};

#endif //ABOUTDIALOG_H
