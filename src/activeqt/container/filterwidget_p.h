/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the ActiveQt framework of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
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
