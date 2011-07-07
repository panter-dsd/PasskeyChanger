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
#include <QtCore/QSettings>

#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>

#include "abstractpasskeychanger.h"
#include "torrentfilepasskeychanger.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_LINUX
//const QString defaultPath = QDir::homePath () + "/.local/share/data/qBittorrent/BT_backup/";
#endif

MainWindow::MainWindow (QWidget *parent)
	: QMainWindow (parent), ui_ (new Ui::MainWindow), currentChanger_ (0)
{
	ui_->setupUi (this);

	connect (ui_->pluginsComboBox,
			 SIGNAL (currentIndexChanged (int)),
			 SLOT (pageChanged (int)));
	connect (ui_->oldPasskeyEdit_,
			 SIGNAL (textChanged (QString)),
			 SLOT (passkeyTextChanged (QString)));
	connect (ui_->newPasskeyEdit_,
			 SIGNAL (textChanged (QString)),
			 SLOT (passkeyTextChanged (QString)));
	connect (ui_->createBackupsEdit_,
			 SIGNAL (stateChanged(int)),
			 SLOT (createBackupChanged(int)));
	connect (ui_->startButton_, SIGNAL (clicked()), SLOT (start()));

	initAbstractPasskeyChangers ();
	initSettingWidgets ();

	loadSettings ();
}

MainWindow::~MainWindow ()
{
	saveSettings ();
}

void MainWindow::changeEvent (QEvent *e)
{
	QMainWindow::changeEvent (e);

	switch (e->type()) {

		case QEvent::LanguageChange:
			ui_->retranslateUi (this);
			break;

		default:
			break;
	}
}

void MainWindow::initAbstractPasskeyChangers ()
{
	abstractPasskeyChangers_.push_back (new TorrentFilePasskeyChanger (this));
}

void MainWindow::initSettingWidgets ()
{
	for (AbstractPasskeyChangers::const_iterator it = abstractPasskeyChangers_.constBegin (),
			end = abstractPasskeyChangers_.constEnd(); it != end; ++it) {
		ui_->pluginsStack->addWidget ( (*it)->settingsWidget ());
		ui_->pluginsComboBox->addItem ( (*it)->name ());
	}

	ui_->pluginsComboBox->setCurrentIndex (0);
}

void MainWindow::start ()
{
	q_check_ptr (currentChanger_);

	const bool result = currentChanger_->changePasskey (ui_->oldPasskeyEdit_->text (),
														ui_->newPasskeyEdit_->text ());
	QMessageBox::information (this, "", result ? tr ("Complite") : tr ("Error"));
}

void MainWindow::loadSettings()
{
	QSettings settings;
	settings.beginGroup ("PLUGINS");

	for (AbstractPasskeyChangers::const_iterator it = abstractPasskeyChangers_.constBegin (),
			end = abstractPasskeyChangers_.constEnd(); it != end; ++it) {
		(*it)->restoreState (settings.value ( (*it)->id()).toByteArray());
	}

	settings.endGroup();

	settings.beginGroup ("GLOBAL");

	ui_->oldPasskeyEdit_->setText (settings.value ("OldPaskey").toString ());
	ui_->newPasskeyEdit_->setText (settings.value ("NewPaskey").toString ());
	ui_->createBackupsEdit_->setCheckState (settings.value ("CreateBackup", true).toBool()
											? Qt::Checked : Qt::Unchecked);

	settings.endGroup();
}

void MainWindow::saveSettings() const
{
	QSettings settings;
	settings.beginGroup ("PLUGINS");

	for (AbstractPasskeyChangers::const_iterator it = abstractPasskeyChangers_.constBegin (),
			end = abstractPasskeyChangers_.constEnd(); it != end; ++it) {
		settings.setValue ( (*it)->id(), (*it)->saveState());
	}

	settings.endGroup();

	settings.beginGroup ("GLOBAL");

	settings.setValue ("OldPaskey", ui_->oldPasskeyEdit_->text ());
	settings.setValue ("NewPaskey", ui_->newPasskeyEdit_->text ());
	settings.setValue ("CreateBackup", ui_->createBackupsEdit_->isChecked ());

	settings.endGroup();
}

void MainWindow::connectPasskeyChanger (AbstractPasskeyChanger *passkeyChanger)
{
	Q_ASSERT (passkeyChanger);

	connect (passkeyChanger,
			 SIGNAL (stateChanged (bool)),
			 SLOT (stateChanged (bool)));
	connect (passkeyChanger,
			 SIGNAL (configurationComplete()),
			 SLOT (configurationComplete()));
}

void MainWindow::disconnectPasskeyChanger (AbstractPasskeyChanger *passkeyChanger) const
{
	Q_ASSERT (passkeyChanger);

	disconnect (passkeyChanger,
				SIGNAL (stateChanged (bool)),
				this,
				SLOT (stateChanged (bool)));
	disconnect (passkeyChanger,
				SIGNAL (configurationComplete()),
				this,
				SLOT (configurationComplete()));
}

void MainWindow::pageChanged (int pageNumber)
{
	if (pageNumber < 0 || pageNumber > abstractPasskeyChangers_.size ()) {
		return;
	}

	AbstractPasskeyChanger *changer = abstractPasskeyChangers_ [pageNumber];

	if (currentChanger_) {
		disconnectPasskeyChanger (currentChanger_);
	}

	ui_->startButton_->setEnabled (changer && changer->isReady ());
	currentChanger_ = changer;

	if (currentChanger_) {
		connectPasskeyChanger (currentChanger_);
		currentChanger_->setCreateBackups (ui_->createBackupsEdit_->isChecked ());
	}
}

void MainWindow::stateChanged (bool isReady)
{
	const QString &oldPasskey = ui_->oldPasskeyEdit_->text ();
	const QString &newPasskey = ui_->newPasskeyEdit_->text ();

	ui_->startButton_->setEnabled (isReady
								   && !oldPasskey.isEmpty()
								   && !newPasskey.isEmpty()
								   && oldPasskey.size() == newPasskey.size());
}

void MainWindow::configurationComplete ()
{

}

void MainWindow::passkeyTextChanged (const QString &text)
{
	stateChanged (currentChanger_ && currentChanger_->isReady());
}

void MainWindow::createBackupChanged (int value)
{
	if (currentChanger_) {
		currentChanger_->setCreateBackups (value == Qt::Checked);
	}
}
