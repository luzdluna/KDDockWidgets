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

#include "SideBarWidget_p.h"
#include "DockWidgetBase.h"

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QAbstractButton>

using namespace KDDockWidgets;

SideBarWidget::SideBarWidget(Qt::Orientation orientation, QWidget *parent)
    : SideBar(orientation, parent)
    , m_layout(isVertical() ? static_cast<QBoxLayout*>(new QVBoxLayout(this))
                            : static_cast<QBoxLayout*>(new QHBoxLayout(this))) // stupid ternary operator requires static_cast
{
    QMargins margins = m_layout->contentsMargins();

    if (isVertical()) {
        margins.setLeft(0);
        margins.setRight(0);
    } else {
        margins.setTop(0);
        margins.setBottom(0);
    }

    m_layout->setContentsMargins(margins);
    m_layout->addStretch();
}

void SideBarWidget::addDockWidget_Impl(DockWidgetBase *dw)
{
    auto button = createButton();
    button->setText(dw->title());
    connect(dw, &DockWidgetBase::titleChanged, button, &QToolButton::setText);
    connect(dw, &QObject::destroyed, button, &QObject::deleteLater);
    connect(button, &QAbstractButton::clicked, this, [this, dw] {
        onButtonClicked(dw);
    });

    const int count = m_layout->count();
    m_layout->insertWidget(count - 1, button);
}

void SideBarWidget::removeDockWidget_Impl(DockWidgetBase *)
{
    // Nothing is needed. Button is removed automatically.
}

QAbstractButton *SideBarWidget::createButton()
{
    return new QToolButton(this);
}
