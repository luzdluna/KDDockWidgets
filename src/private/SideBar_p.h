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

#ifndef KD_SIDEBAR_P_H
#define KD_SIDEBAR_P_H

#include "docks_export.h"
#include "QWidgetAdapter.h"

namespace KDDockWidgets {

class DockWidgetBase;

class DOCKS_EXPORT SideBar : public QWidgetAdapter
{
    Q_OBJECT
public:
    explicit SideBar(Qt::Orientation orientation, QWidgetOrQuick *parent = nullptr);

    void addDockWidget(DockWidgetBase *dw);
    void removeDockWidget(DockWidgetBase *dw);
    bool contains(DockWidgetBase *) const;

    /// @brief Returns this side bar's orientation
    Qt::Orientation orientation() const;

    /// @brief returns if this side bar has vertical orientation
    bool isVertical() const { return m_orientation == Qt::Vertical; }

    /// @brief returns whether there's no dock widgets
    bool isEmpty() const;

protected:
    virtual void addDockWidget_Impl(DockWidgetBase *dock) = 0;
    virtual void removeDockWidget_Impl(DockWidgetBase *dock) = 0;

    void onButtonClicked(DockWidgetBase *dw);

private:
    void updateSize();

    QVector<DockWidgetBase *> m_dockWidgets;
    const Qt::Orientation m_orientation;
};

}

#endif
