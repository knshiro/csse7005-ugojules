/***************************************************************************
 *   Copyright (C) 2008 by Egil Anonsen
 *   eanonsen@hotmail.com
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QtGui>

/**
*	@author Egil Anonsen
*	@version 1.0
* 	This class is used to create push buttons with customized appearance.
*	It is used to paint arrows, crosses, and a number of other symbols used in the
*	application. It inherits from QPushButton, and reimplements the paintEvent(..) method.
*/
class CustomPushButton : public QPushButton
{
	Q_OBJECT
	
	public:
   		CustomPushButton(QWidget *parent, int x, int y, int width, int heigth);
		void setDrawState(QString state);
		~CustomPushButton();

	signals:
		void buttonClicked(int, int);

	private slots:
		void buttonClicked();

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		QString drawState;
};

#endif
