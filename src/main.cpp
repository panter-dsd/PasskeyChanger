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

#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtGui/QApplication>

#include "mainwindow.h"

const QString appName = "PasskeyChanger";
const QString version = "0.0.1.0";

int main (int argc, char **argv)
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));

	QApplication app (argc, argv);

	QCoreApplication::addLibraryPath (app.applicationDirPath () + "/plugins/");

	app.setOrganizationDomain ("panter.dsd");
	app.setOrganizationName ("PanteR");
	app.setApplicationVersion (version);
	app.setApplicationName (appName);

// 	QTranslator translator;
// 	translator.load (":/share/translations/VolnaSettings_"
// 					 + QLocale::system().name()
// 					 + ".qm");
// 	app.installTranslator (&translator);

	app.setQuitOnLastWindowClosed (true);

	MainWindow w;
	w.setWindowTitle (app.applicationName () + " " + app.applicationVersion ());
	w.show ();

	return app.exec ();
}
