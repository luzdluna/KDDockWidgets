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

#include "SideBar_p.h"
#include "DockWidgetBase.h"

#include <QDebug>

using namespace KDDockWidgets;

SideBar::SideBar(Qt::Orientation orientation, QWidgetOrQuick *parent)
    : QWidgetAdapter(parent)
    , m_orientation(orientation)
{
    updateSize();
}

void SideBar::addDockWidget(DockWidgetBase *dw)
{
    if (!dw)
        return;

    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Already contains dock widget" << dw->title();
        return;
    }

    connect(dw, &QObject::destroyed, this, [this, dw] {
        removeDockWidget(dw);
    });

    m_dockWidgets << dw;
    addDockWidget_Impl(dw);
    updateSize();
}

void SideBar::removeDockWidget(DockWidgetBase *dw)
{
    if (!m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Doesn't contain dock widget" << dw->title();
        return;
    }

    m_dockWidgets.removeOne(dw);
    removeDockWidget_Impl(dw);
    updateSize();
}

bool SideBar::contains(DockWidgetBase *dw) const
{
    return m_dockWidgets.contains(dw);
}

void SideBar::onButtonClicked(DockWidgetBase *dw)
{
    dw->show();
    dw->setFloating(true);
}

void SideBar::updateSize()
{
    const int thickness = isEmpty() ? 0 : 30;
    if (isVertical()) {
        setFixedWidth(thickness);
    } else {
        setFixedHeight(thickness);
    }
}

Qt::Orientation SideBar::orientation() const
{
    return m_orientation;
}

bool SideBar::isEmpty() const
{
    return m_dockWidgets.isEmpty();
}
