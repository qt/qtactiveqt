/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the ActiveQt framework of the Qt Toolkit
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtGui/QColor>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class QToolButton;

/* Note: This a copy of the filter widget found in the qtools repository
 * which was modified to contain cleartext.png as inline XPM image data
 * and to have LayoutAlignNone as default parameter in the constructor to
 * to suit the QAxSelect dialog's needs.
 *
 * This widget should never have initial focus
 * (ie, be the first widget of a dialog, otherwise the hint cannot be displayed.
 * For situations, where it is the only focusable control (widget box),
 * there is a special "refuseFocus()" mode, in which it clears the focus
 * policy and focuses explicitly on click (note that setting Qt::ClickFocus
 * is not sufficient for that as an ActivationFocus will occur). */

#define ICONBUTTON_SIZE 16

class HintLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit HintLineEdit(QWidget *parent = 0);

    bool refuseFocus() const;
    void setRefuseFocus(bool v);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void focusInEvent(QFocusEvent *e);

private:
    const Qt::FocusPolicy m_defaultFocusPolicy;
    bool m_refuseFocus;
};

// IconButton: This is a simple helper class that represents clickable icons

class IconButton: public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    IconButton(QWidget *parent);
    void paintEvent(QPaintEvent *event);
    float fader() { return m_fader; }
    void setFader(float value) { m_fader = value; update(); }
    void animateShow(bool visible);

private:
    float m_fader;
};

// FilterWidget: For filtering item views, with reset button Uses HintLineEdit.

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    enum LayoutMode {
        // For use in toolbars: Expand to the right
        LayoutAlignRight,
        // No special alignment
        LayoutAlignNone
    };

    explicit FilterWidget(QWidget *parent = 0, LayoutMode lm = LayoutAlignNone);

    QString text() const;
    void resizeEvent(QResizeEvent *);
    bool refuseFocus() const; // see HintLineEdit
    void setRefuseFocus(bool v);

signals:
    void filterChanged(const QString &);

public slots:
    void reset();

private slots:
    void checkButton(const QString &text);

private:
    HintLineEdit *m_editor;
    IconButton *m_button;
    int m_buttonwidth;
    QString m_oldText;
};

QT_END_NAMESPACE

#endif
