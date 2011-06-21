#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow (QWidget *parent = 0);
	virtual ~MainWindow ();

protected:
	void changeEvent (QEvent* e);

private Q_SLOTS:
	void setPathToTorrents ();
	void start ();

private:
	Ui::MainWindow *ui_;
};

#endif // MAINWINDOW_H
