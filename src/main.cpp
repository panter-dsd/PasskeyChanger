#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtGui/QApplication>

#include "mainwindow.h"

const QString appName = "PasskeyChanger";
const QString version = "0.0.0.0";

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
