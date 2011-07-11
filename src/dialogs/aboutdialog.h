/********************************************************************
* Copyright (C) PanteR
*-------------------------------------------------------------------
*
* POCSLabComplex is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* POCSLabComplex is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Panther Commander; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:		POCSLabComplex
* Author:		PanteR
* Contact:		panter.dsd@gmail.com
*******************************************************************/

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
		m_author = author;
		printCopyright();
	}

	void setMail (const QString &mail) {
		m_mail = mail;
		printCopyright();
	}

	void setPhone (const QString &phone) {
		m_phone = phone;
		printCopyright();
	}

	void setLicense (const QString &license) {
		m_license = license;
		printCopyright();
	}

	void addThanks (const QString &name, const QString &email, const QString &typeWork) {
		QStringList l;
		l << name << email << typeWork;
		m_thanks << l;
		printThanks ();
	}

private:
	void printCopyright();
	void printThanks ();

private:
	QLabel *iconLabel;
	QLabel *aboutLabel;
	QToolButton *closeButton;

	QTabWidget *tabWidget;

	QTextEdit *copyrightView;
	QTextEdit *thanksView;
	QTextEdit *licenseView;

	QString m_author;
	QString m_mail;
	QString m_phone;
	QString m_license;

	QList<QStringList> m_thanks;
};

#endif //ABOUTDIALOG_H
