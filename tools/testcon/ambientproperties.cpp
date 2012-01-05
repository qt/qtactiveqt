/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "ambientproperties.h"

#include <QtWidgets>

QT_BEGIN_NAMESPACE

AmbientProperties::AmbientProperties(QWidget *parent)
: QDialog(parent), container(0)
{
    setupUi(this);

    connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));
}

void AmbientProperties::setControl(QWidget *widget)
{
    container = widget;

    QColor c = container->palette().color(container->backgroundRole());
    QPalette p = backSample->palette(); p.setColor(backSample->backgroundRole(), c); backSample->setPalette(p);

    c = container->palette().color(container->foregroundRole());
    p = foreSample->palette(); p.setColor(foreSample->backgroundRole(), c); foreSample->setPalette(p);

    fontSample->setFont( container->font() );
    buttonEnabled->setChecked( container->isEnabled() );
    enabledSample->setEnabled( container->isEnabled() );
}

void AmbientProperties::on_buttonBackground_clicked()
{
    const QColor c = QColorDialog::getColor(backSample->palette().color(backSample->backgroundRole()), this);
    QPalette p = backSample->palette();
    p.setColor(backSample->backgroundRole(), c);
    backSample->setPalette(p);

    p = container->palette();
    p.setColor(container->backgroundRole(), c);
    container->setPalette(p);

    foreach (QWidget *widget, mdiAreaWidgets()) {
        p = widget->palette();
        p.setColor(widget->backgroundRole(), c);
        widget->setPalette(p);
	}
}

void AmbientProperties::on_buttonForeground_clicked()
{
    const QColor c = QColorDialog::getColor(foreSample->palette().color(foreSample->backgroundRole()), this);

    QPalette p = foreSample->palette();
    p.setColor(foreSample->backgroundRole(), c);
    foreSample->setPalette(p);

    p = container->palette();
    p.setColor(container->foregroundRole(), c);
    container->setPalette(p);

    foreach (QWidget *widget, mdiAreaWidgets()) {
        p = widget->palette();
        p.setColor(widget->foregroundRole(), c);
        widget->setPalette(p);
    }
}

void AmbientProperties::on_buttonFont_clicked()
{
    bool ok;
    QFont f = QFontDialog::getFont( &ok, fontSample->font(), this );
    if ( !ok )
	return;
    fontSample->setFont( f );
    container->setFont( f );

    foreach (QWidget *widget, mdiAreaWidgets())
        widget->setFont( f );
}

void AmbientProperties::on_buttonEnabled_toggled(bool on)
{
    enabledSample->setEnabled( on );
    container->setEnabled( on );
}

QWidgetList AmbientProperties::mdiAreaWidgets() const
{
    QWidgetList result;
    if (QMdiArea *mdiArea = qobject_cast<QMdiArea*>(container))
        foreach (QMdiSubWindow *subWindow, mdiArea->subWindowList())
            result.push_back(subWindow->widget());
    return result;
}

QT_END_NAMESPACE
