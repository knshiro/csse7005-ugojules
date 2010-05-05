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
#include "custompushbutton.h"

/**
*	@version 1.0
* 	This constructor calls setupUi() to setup the UI as created in the Qt designer.
*	It also takes care of setting the geometry of the button and connecting the clicked signal
*	of this button to the buttonClicked slot.
*	@param parent A pointer to a QWidget, which is the parent of this button
*	@param x An integer, specifying the x position of the button.
*	@param y An integer, specifying the y position of the button.
*	@param width An integer, specifying the width of the button.
*	@param heigth An integer, specifying the heigth the button.
*	@return Nothing 
*/
CustomPushButton::CustomPushButton(QWidget *parent, int x, int y, int width, int heigth) : QPushButton(parent)
{
	// The parent is set through the syntax ': QPushButton(parent)'
	// Position widget
	setGeometry(QRect(x, y, width, heigth));
	// Set AutoFillBackground to true in order to fill background with color 
	setAutoFillBackground(true);
	// Set drawState to Initialize
	drawState = "DO_NOTHING";
	// Connect clicked signal to appropriate slot 
	connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

/**
*	@version 1.0
* 	This slot is called whenever this button is clicked. It then emits a signal with the x and y 
*	coordinates of this button.
*	@return Nothing
*/
void CustomPushButton::buttonClicked()
{
	// Emit buttonClicked along with its position so that slot can decode which button was clicked
	emit buttonClicked(x(), y());
}

/**
*	@version 1.0
* 	This method sets the draw state of the button, which is used when customizing the appearance of the
*	buttons.
*	@param state A QString containing the drawState of this button
*	@return Nothing
*/
void CustomPushButton::setDrawState(QString state)
{
	drawState = state;
}

/**
*	@version 1.0
* 	This method reimplements the paintEvent slot of the QPushButton. It is implicity called whenever repaint
*	is called on a CustomPushButton. It will first call the base class QPushButton::paintEvent(event) to 
*	paint the button, then customize the button according to the current drawState.
*	@param event A QPaintEvent object, containing the paint event.
*	@return Nothing
*/
void CustomPushButton::paintEvent(QPaintEvent *event)
{
	// First paint the regular pushbutton, called initially to draw QPushButton
	QPushButton::paintEvent(event);
	// Then custom draw
	if(drawState == "DO_NOTHING")
	{
		// Do nothing, let parent paint whatever it needs to paint
	}
	else if(drawState == "YELLOW")
	{
		// Set appropriate color
		setPalette(QPalette(QColor(238, 238, 0)));
	}
	else if(drawState == "BLUE")
	{
		// Set appropriate color
		setPalette(QPalette(QColor(135, 206, 250)));
	}
	else if(drawState == "WHITE")
	{
		// Set appropriate color
		setPalette(QPalette(QColor(235, 235, 235)));
	}
	else if(drawState == "CROSS")
	{
		// Draw an X on the pushbutton, with blue background
		QPainter painter(this);
		QPen pen;
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(width()/5, height()/5, width() - (width()/5), height() - (height()/5));
		painter.drawLine(width() - (width()/5), height()/5, width()/5, height() - (height()/5));
		// Set light blue color
		setPalette(QPalette(QColor(135, 206, 250)));
	}
	else if(drawState == "CIRCLE")
	{
		// Draw an O on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setWidth(3);
		painter.setPen(pen);
		QRect rect(width()/6, height()/6, width() - (width()/3), height() - (height()/3));
		painter.drawEllipse(rect);
		// Set light purple color
		setPalette(QPalette(QColor(238, 169, 184)));	
	}
	else if(drawState == "ARROW_UP")
	{
		// Set appropriate color
		setPalette(QPalette(QColor(135, 206, 250)));
		// Draw an X on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(width()/2, height()/5, width()/2, height() - (height()/5));
		painter.drawLine(width()/2, height()/5, width()/5, height()/2);
		painter.drawLine(width()/2, height()/5, width() - (width()/5), height()/2);
	}
	else if(drawState == "ARROW_DOWN")
	{
		// Set appropriate color
		setPalette(QPalette(QColor(135, 206, 250)));
		// Draw an X on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawLine(width()/2, height()/5, width()/2, height() - (height()/5));
		painter.drawLine(width()/2, height() - (height()/5), width()/5, height()/2);
		painter.drawLine(width()/2, height() - (height()/5), width() - (width()/5), height()/2);
	}
	else if(drawState == "RECORDING")
	{
		// Draw a red circle on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::darkRed));
		pen.setWidth(4);
		painter.setPen(pen);
		painter.drawEllipse(10, 10, 10, 10);
		painter.fillRect(QRect(10, 10, 10, 10), QBrush(QColor(Qt::darkRed)));
	}
	else if(drawState == "PLAY")
	{
		// Draw a green triangle on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::darkGreen));
		pen.setWidth(2);
		painter.setPen(pen);
		QPainterPath path;
 		path.moveTo(10, 10);
 		path.lineTo(20, 15);
		path.lineTo(10, 20);
		path.lineTo(10, 10);
		painter.drawPath(path);
		painter.fillPath(path, QBrush(QColor(Qt::darkGreen)));
	}
	else if(drawState == "PAUSE")
	{
		// Draw two blue triangles pointing to the left on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::black));
		pen.setWidth(4);
		painter.setPen(pen);
		painter.drawLine(12, 10, 12, 20);
		painter.drawLine(18, 10, 18, 20);
	}
	else if(drawState == "STOP")
	{
		// Draw a red square on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::darkRed));
		pen.setWidth(2);
		painter.setPen(pen);
		QRect rect(10, 10, 10, 10);
		painter.drawRect(rect);
		painter.fillRect(rect, QBrush(QColor(Qt::darkRed)));
	}
	else if(drawState == "FORWARD")
	{
		// Draw two blue triangles pointing to the right on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::darkBlue));
		pen.setWidth(2);
		painter.setPen(pen);
		QPainterPath path;
 		path.moveTo(5, 10);
 		path.lineTo(15, 15);
		path.lineTo(5, 20);
		path.lineTo(5, 10);
		path.moveTo(15, 10);
		path.lineTo(25, 15);
		path.lineTo(15, 20);
		path.lineTo(15, 10);
		painter.drawPath(path);
		painter.fillPath(path, QBrush(QColor(Qt::darkBlue)));
	}
	else if(drawState == "REWIND")
	{
		// Draw two blue triangles pointing to the left on the pushbutton
		QPainter painter(this);
		QPen pen;
		pen.setColor(QColor(Qt::darkBlue));
		pen.setWidth(2);
		painter.setPen(pen);
		QPainterPath path;
 		path.moveTo(15, 10);
 		path.lineTo(15, 20);
		path.lineTo(5, 15);
		path.lineTo(15, 10);
		path.moveTo(25, 10);
		path.lineTo(25, 20);
		path.lineTo(15, 15);
		path.lineTo(25, 10);
		painter.drawPath(path);
		painter.fillPath(path, QBrush(QColor(Qt::darkBlue)));
	}
	else
	{
		// Undefined drawState, do nothing
	}
}

/**
*	@version 1.0
* 	This destructor does nothing.
*	@return Nothing 
*/
CustomPushButton::~CustomPushButton()
{
	// Do nothing for now
}


