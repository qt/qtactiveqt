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

#include "qaxselect.h"

#ifndef QT_NO_WIN_ACTIVEQT
#include "ui_qaxselect.h"

#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QItemSelectionModel>
#include <QtWidgets/QPushButton>

#include <qt_windows.h>

QT_BEGIN_NAMESPACE

class ControlList : public QAbstractListModel
{
public:
    ControlList(QObject *parent=0)
    : QAbstractListModel(parent)
    {
        HKEY classes_key;
        RegOpenKeyEx(HKEY_CLASSES_ROOT, L"CLSID", 0, KEY_READ, &classes_key);
        if (!classes_key)
            return;

        DWORD index = 0;
        LONG result = 0;
        wchar_t buffer[256];
        DWORD szBuffer = sizeof(buffer) / sizeof(wchar_t);
        FILETIME ft;
        do {
            result = RegEnumKeyEx(classes_key, index, buffer, &szBuffer, 0, 0, 0, &ft);
            szBuffer = sizeof(buffer) / sizeof(wchar_t);
            if (result == ERROR_SUCCESS) {
                HKEY sub_key;
                QString clsid = QString::fromWCharArray(buffer);
                const QString key = clsid + QStringLiteral("\\Control");
                result = RegOpenKeyEx(classes_key, reinterpret_cast<const wchar_t *>(key.utf16()), 0, KEY_READ, &sub_key);
                if (result == ERROR_SUCCESS) {
                    RegCloseKey(sub_key);
                    RegistryQueryValue(classes_key, buffer, (LPBYTE)buffer, &szBuffer);
                    QString name = QString::fromWCharArray(buffer);

                    controls << name;
                    clsids.insert(name, clsid);
                }
                result = ERROR_SUCCESS;
            }
            szBuffer = sizeof(buffer) / sizeof(wchar_t);
            ++index;
        } while (result == ERROR_SUCCESS);
        RegCloseKey(classes_key);
        controls.sort();
    }

    LONG RegistryQueryValue(HKEY hKey, LPCWSTR lpSubKey, LPBYTE lpData, LPDWORD lpcbData)
    {
        LONG ret = ERROR_FILE_NOT_FOUND;
        HKEY hSubKey = NULL;
        RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hSubKey);
        if (hSubKey) {
            ret = RegQueryValueEx(hSubKey, 0, 0, 0, lpData, lpcbData);
            RegCloseKey(hSubKey);
        }
        return ret;
    }

    int rowCount(const QModelIndex & = QModelIndex()) const { return controls.count(); }
    QVariant data(const QModelIndex &index, int role) const;

private:
    QStringList controls;
    QMap<QString, QString> clsids;
};

QVariant ControlList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return controls.at(index.row());
    if (role == Qt::UserRole)
        return clsids.value(controls.at(index.row()));

    return QVariant();
}

class QAxSelectPrivate {
public:
    inline QString clsidAt(const QModelIndex &index) const
    {
        if (index.isValid()) {
            const QModelIndex sourceIndex = filterModel->mapToSource(index);
            if (sourceIndex.isValid())
                return sourceIndex.data(Qt::UserRole).toString();
        }
        return QString();
    }

    inline QPushButton *okButton() const { return selectUi.buttonBox->button(QDialogButtonBox::Ok); }

    inline void setOkButtonEnabled(bool enabled) { okButton()->setEnabled(enabled); }

    Ui::QAxSelect selectUi;
    QSortFilterProxyModel *filterModel;
};

/*!
    \class QAxSelect
    \brief The QAxSelect class provides a selection dialog for registered COM components.

    \inmodule QAxContainer

    QAxSelect dialog can be used to provide users with a way to browse the registered COM
    components of the system and select one. The CLSID of the selected component can
    then be used in the application to e.g. initialize a QAxWidget:

    \snippet src_activeqt_container_qaxselect.cpp 0

    \sa QAxWidget, {ActiveQt Framework}
*/

/*!
    Constructs a QAxSelect object. Dialog parent widget and window flags can be
    optionally specified with \a parent and \a flags parameters, respectively.
*/
QAxSelect::QAxSelect(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
    , d(new QAxSelectPrivate)
{
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
    d->selectUi.setupUi(this);
    d->setOkButtonEnabled(false);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    d->filterModel = new QSortFilterProxyModel(this);
    d->filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    d->filterModel->setSourceModel(new ControlList(this));
    d->selectUi.ActiveXList->setModel(d->filterModel);

    connect(d->selectUi.ActiveXList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(onActiveXListCurrentChanged(QModelIndex)));
    connect(d->selectUi.ActiveXList, SIGNAL(activated(QModelIndex)),
            this, SLOT(onActiveXListActivated()));

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    d->selectUi.ActiveXList->setFocus();

    connect(d->selectUi.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(d->selectUi.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(d->selectUi.filterLineEdit, SIGNAL(filterChanged(QString)),
            this, SLOT(onFilterLineEditChanged(QString)));
}

/*!
    Destroys the QAxSelect object.
*/
QAxSelect::~QAxSelect()
{
}

/*!
    \fn QString QAxSelect::clsid() const

    Returns the CLSID of the selected COM component.
*/
QString QAxSelect::clsid() const
{
    return d->selectUi.ActiveX->text().trimmed();
}

void QAxSelect::onActiveXListCurrentChanged(const QModelIndex &index)
{
    const QString newClsid = d->clsidAt(index);
    d->selectUi.ActiveX->setText(newClsid);
    d->setOkButtonEnabled(!newClsid.isEmpty());
}

void QAxSelect::onActiveXListActivated()
{
    if (!clsid().isEmpty())
        d->okButton()->animateClick();
}

void QAxSelect::onFilterLineEditChanged(const QString &text)
{
    d->filterModel->setFilterFixedString(text);
}

QT_END_NAMESPACE
#endif // QT_NO_WIN_ACTIVEQT
