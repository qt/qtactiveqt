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

#include "filterwidget_p.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtGui/QFocusEvent>
#include <QtGui/QPalette>
#include <QtGui/QCursor>
#include <QtWidgets/QToolButton>
#include <QtGui/QPainter>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOption>

#include <QtCore/QDebug>
#include <QtCore/QPropertyAnimation>

enum { debugFilter = 0 };

/* XPM */
static const char *cleartext_xpm[] = {
"16 16 53 1",
"  c None",
". c #2B2B2B",
"+ c #2D2D2D",
"@ c #2F2F2F",
"# c #323232",
"$ c #373737",
"% c #3C3C3C",
"& c #3E3E3E",
"* c #363636",
"= c #404040",
"- c #494949",
"; c #4E4E4E",
"> c #525252",
", c #444444",
"' c #4F4F4F",
") c #9C9C9C",
"! c #6B6B6B",
"~ c #626262",
"{ c #333333",
"] c #414141",
"^ c #9B9B9B",
"/ c #FFFFFF",
"( c #E5E5E5",
"_ c #737373",
": c #3A3A3A",
"< c #4A4A4A",
"[ c #555555",
"} c #5D5D5D",
"| c #E0E0E0",
"1 c #E7E7E7",
"2 c #3F3F3F",
"3 c #5A5A5A",
"4 c #4B4B4B",
"5 c #E2E2E2",
"6 c #424242",
"7 c #5E5E5E",
"8 c #5B5B5B",
"9 c #505050",
"0 c #6A6A6A",
"a c #E3E3E3",
"b c #4D4D4D",
"c c #545454",
"d c #999999",
"e c #DEDEDE",
"f c #474747",
"g c #878787",
"h c #434343",
"i c #414140",
"j c #454545",
"k c #484848",
"l c #484949",
"m c #484748",
"n c #444544",
"                ",
"     .+@@+.     ",
"    #$%&&%$#    ",
"   *=-;>>;-=*   ",
"  $,')!~~!)',$  ",
" {]'^/(__(/^']{ ",
" :<[}|/11/|}[<: ",
" 2'3>45//54>3'2 ",
" 6>}785//587}>6 ",
" ]930a/||/a039] ",
" &bcd/e%%e/dcb& ",
"  f;6gh]ihg6;f  ",
"   -f=j99j=f-   ",
"    k<b99b<k    ",
"     jkl-mn     ",
"                "};

QT_BEGIN_NAMESPACE

HintLineEdit::HintLineEdit(QWidget *parent) :
    QLineEdit(parent),
    m_defaultFocusPolicy(focusPolicy()),
    m_refuseFocus(false)
{
}

IconButton::IconButton(QWidget *parent)
    : QToolButton(parent), m_fader(0)
{
    setCursor(Qt::ArrowCursor);
}

void IconButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Note isDown should really use the active state but in most styles
    // this has no proper feedback
    QIcon::Mode state = QIcon::Disabled;
    if (isEnabled())
        state = isDown() ? QIcon::Selected : QIcon::Normal;
    QPixmap iconpixmap = icon().pixmap(QSize(ICONBUTTON_SIZE, ICONBUTTON_SIZE),
                                       state, QIcon::Off);
    QRect pixmapRect = QRect(0, 0, iconpixmap.width(), iconpixmap.height());
    pixmapRect.moveCenter(rect().center());
    painter.setOpacity(m_fader);
    painter.drawPixmap(pixmapRect, iconpixmap);
}

void IconButton::animateShow(bool visible)
{
    if (visible) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
        animation->setDuration(160);
        animation->setEndValue(1.0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    } else {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
        animation->setDuration(160);
        animation->setEndValue(0.0);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

bool HintLineEdit::refuseFocus() const
{
    return m_refuseFocus;
}

void HintLineEdit::setRefuseFocus(bool v)
{
    if (v == m_refuseFocus)
        return;
    m_refuseFocus = v;
    setFocusPolicy(m_refuseFocus ? Qt::NoFocus : m_defaultFocusPolicy);
}

void HintLineEdit::mousePressEvent(QMouseEvent *e)
{
    if (debugFilter)
        qDebug() << Q_FUNC_INFO;
    // Explicitly focus on click.
    if (m_refuseFocus && !hasFocus())
        setFocus(Qt::OtherFocusReason);
    QLineEdit::mousePressEvent(e);
}

void HintLineEdit::focusInEvent(QFocusEvent *e)
{
    if (debugFilter)
        qDebug() << Q_FUNC_INFO;
    if (m_refuseFocus) {
        // Refuse the focus if the mouse is outside. In addition to the mouse
        // press logic, this prevents a re-focusing which occurs once
        // we actually have focus
        const Qt::FocusReason reason = e->reason();
        if (reason == Qt::ActiveWindowFocusReason || reason == Qt::PopupFocusReason) {
            const QPoint mousePos = mapFromGlobal(QCursor::pos());
            const bool refuse = !geometry().contains(mousePos);
            if (debugFilter)
                qDebug() << Q_FUNC_INFO << refuse;
            if (refuse) {
                e->ignore();
                return;
            }
        }
    }

    QLineEdit::focusInEvent(e);
}

// ------------------- FilterWidget
FilterWidget::FilterWidget(QWidget *parent, LayoutMode lm)  :
    QWidget(parent),
    m_editor(new HintLineEdit(this)),
    m_button(new IconButton(m_editor)),
    m_buttonwidth(0)
{
    m_editor->setPlaceholderText(tr("Filter"));

    // Let the style determine minimum height for our widget
    QSize size(ICONBUTTON_SIZE + 6, ICONBUTTON_SIZE + 2);

    // Note KDE does not reserve space for the highlight color
    if (style()->inherits("OxygenStyle"))
        size = size.expandedTo(QSize(24, 0));

    // Make room for clear icon
    QMargins margins = m_editor->textMargins();
    if (layoutDirection() == Qt::LeftToRight)
        margins.setRight(size.width());
    else
        margins.setLeft(size.width());

    m_editor->setTextMargins(margins);

    QHBoxLayout *l = new QHBoxLayout(this);
    l->setMargin(0);
    l->setSpacing(0);
    if (lm == LayoutAlignRight)
        l->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    l->addWidget(m_editor);

    // KDE has custom icons for this. Notice that icon namings are counter intuitive
    // If these icons are not available we use the freedesktop standard name before
    // falling back to a bundled resource
    QIcon icon = QIcon::fromTheme(layoutDirection() == Qt::LeftToRight ?
                     QStringLiteral("edit-clear-locationbar-rtl") :
                     QStringLiteral("edit-clear-locationbar-ltr"),
                     QIcon::fromTheme(QStringLiteral("edit-clear"),
                                      QIcon(QPixmap(cleartext_xpm))));
    Q_ASSERT(!icon.availableSizes().isEmpty());
    m_button->setIcon(icon);
    m_button->setToolTip(tr("Clear text"));
    connect(m_button, SIGNAL(clicked()), this, SLOT(reset()));
    connect(m_editor, SIGNAL(textChanged(QString)), this, SLOT(checkButton(QString)));
    connect(m_editor, SIGNAL(textEdited(QString)), this, SIGNAL(filterChanged(QString)));
}

QString FilterWidget::text() const
{
    return m_editor->text();
}

void FilterWidget::checkButton(const QString &text)
{
    if (m_oldText.isEmpty() || text.isEmpty())
        m_button->animateShow(!m_editor->text().isEmpty());
    m_oldText = text;
}

void FilterWidget::reset()
{
    if (debugFilter)
        qDebug() << Q_FUNC_INFO;

    if (!m_editor->text().isEmpty()) {
        // Editor has lost focus once this is pressed
        m_editor->clear();
        emit filterChanged(QString());
    }
}

void FilterWidget::resizeEvent(QResizeEvent *)
{
    QRect contentRect = m_editor->rect();
    if (layoutDirection() == Qt::LeftToRight) {
        const int iconoffset = m_editor->textMargins().right() + 4;
        m_button->setGeometry(contentRect.adjusted(m_editor->width() - iconoffset, 0, 0, 0));
    } else {
        const int iconoffset = m_editor->textMargins().left() + 4;
        m_button->setGeometry(contentRect.adjusted(0, 0, -m_editor->width() + iconoffset, 0));
    }
}

bool FilterWidget::refuseFocus() const
{
    return m_editor->refuseFocus();
}

void FilterWidget::setRefuseFocus(bool v)
{
    m_editor->setRefuseFocus(v);
}

QT_END_NAMESPACE
