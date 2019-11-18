/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KD_SIDEBARWIDGET_P_H
#define KD_SIDEBARWIDGET_P_H


#include "../../docks_export.h"
#include "../SideBar_p.h"

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DockWidget;
class Frame;

class DOCKS_EXPORT SideBarWidget : public SideBar
{
    Q_OBJECT
public:
    explicit SideBarWidget(Qt::Orientation orientation, QWidget *parent);

protected:
    void addDockWidget_Impl(DockWidgetBase *dock) override;
    void removeDockWidget_Impl(DockWidgetBase *dock) override;

    // virtual so users can provide their own buttons
    virtual QAbstractButton* createButton();

private:
    QBoxLayout *const m_layout;
};

}

#endif
