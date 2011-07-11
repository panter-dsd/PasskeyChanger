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

#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>

#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QIcon>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QPalette>
#include <QtGui/QToolButton>
#include <QtGui/QStyle>

#include "aboutdialog.h"

AboutDialog::AboutDialog (QWidget *parent, Qt::WFlags f)
	: QDialog (parent, f)
{
	resize (400, 300);

	iconLabel_ = new QLabel (this);
	iconLabel_->setPixmap (QApplication::windowIcon().pixmap (QSize (64, 64)));
	iconLabel_->setSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed);

	aboutLabel_ = new QLabel (this);

	const QDateTime createdDateTime = QFileInfo (QApplication::applicationFilePath()).created ();
	aboutLabel_->setText ("<h2>"
						 + QApplication::applicationName()
						 + " "
						 + QApplication::applicationVersion()
						 + "</h2>"
						 + "<p>"
						 + tr ("Compiled %1 in %2").arg (createdDateTime.toString ("dd.MM.yyyy")).arg (createdDateTime.toString ("hh:mm:ss")));

	closeButton_ = new QToolButton (this);
	closeButton_->setText (tr ("Close"));
	closeButton_->setIcon (style()->standardIcon (QStyle::SP_DialogCloseButton));
	closeButton_->setAutoRaise (true);
	closeButton_->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);
	connect (closeButton_, SIGNAL (clicked()), SLOT (close()));

	QHBoxLayout *pictureAndTextLayout = new QHBoxLayout();
	pictureAndTextLayout->addWidget (iconLabel_);
	pictureAndTextLayout->addWidget (aboutLabel_);
	pictureAndTextLayout->addWidget (closeButton_);

//Tabs
	tabWidget_ = new QTabWidget (this);

	QPalette palette = QApplication::palette();
	palette.setColor (QPalette::Base, palette.color (QPalette::Button));
//Copyright
	copyrightView_ = new QTextEdit (this);
	copyrightView_->setReadOnly (true);
	copyrightView_->setWordWrapMode (QTextOption::NoWrap);
	copyrightView_->setTextInteractionFlags (Qt::TextBrowserInteraction);
	copyrightView_->setPalette (palette);

	tabWidget_->addTab (copyrightView_, tr ("Copyright"));

//Thanks
	thanksView_ = new QTextEdit (this);
	thanksView_->setReadOnly (true);
	thanksView_->setWordWrapMode (QTextOption::NoWrap);
	thanksView_->setTextInteractionFlags (Qt::TextBrowserInteraction);
	thanksView_->setPalette (palette);

	tabWidget_->addTab (thanksView_, tr ("Thanks"));

//License
	licenseView_ = new QTextEdit (this);
	licenseView_->setReadOnly (true);
	licenseView_->setWordWrapMode (QTextOption::NoWrap);
	licenseView_->setTextInteractionFlags (Qt::TextBrowserInteraction);
	licenseView_->setPalette (palette);

	tabWidget_->addTab (licenseView_, tr ("License"));

//Main layout
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout (pictureAndTextLayout);
	mainLayout->addWidget (tabWidget_);

	setLayout (mainLayout);
}

void AboutDialog::setLicenseText (const QString &text)
{
	licenseView_->setText (text);
}

void AboutDialog::printCopyright()
{
	const QString text = "<b>" + tr ("Author") + "</b>: %1"
						 + "<p>"
						 + "<b>" + tr ("e-mail") + "</b>: <a href=\"%2\">%2"
						 + "<p>"
						 + "<b>" + tr ("phone") + "</b>: %3"
						 + "<p>"
						 + "<b>" + tr ("License") + "</b>: %4";

	copyrightView_->setText (text.arg (author_).arg (mail_).arg (phone_).arg (license_));
}

void AboutDialog::printThanks ()
{
	const QString text = "<b>" + tr ("Name") + "</b>: %1"
						 + "<BR><b>" + tr ("e-mail") + "</b>: <a href=\"%2\">%2</a>"
						 + "<BR><b>" + tr ("Work type") + "</b>: %3";

	thanksView_->clear();

	foreach (const QStringList & l, thanks_) {
		thanksView_->append (text.arg (l[0]).arg (l[1]).arg (l[2]));
	}
}
