/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "multisplitter.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QDebug>

using namespace Layouting;

MultiSplitter::MultiSplitter()
    : QQuickItem()
    , Layouting::Widget_quick(this)
    , m_rootContainer(new ItemContainer(this))
{
    onSizeChanged();
    connect(this, &QQuickItem::widthChanged, this, &MultiSplitter::onSizeChanged);
    connect(this, &QQuickItem::heightChanged, this, &MultiSplitter::onSizeChanged);
}

void MultiSplitter::addItem(const QString &filename, Layouting::Item::Location loc)
{
    QQmlEngine *engine = qmlEngine(this);
    if (!engine)
        return;

    QQmlComponent component(engine, filename);
    auto qquickitem = qobject_cast<QQuickItem*>(component.create());
    if (!qquickitem) {
        qWarning() << Q_FUNC_INFO << component.errorString();
        return;
    }

    auto item = new Item(this);
    auto wrapper = new Layouting::Widget_quick(qquickitem); // TODO: How to delete the wrapper
    item->setGuestWidget(wrapper);

    m_rootContainer->insertItem(item, loc);
}

void MultiSplitter::onSizeChanged()
{
    m_rootContainer->setSize_recursive(QQuickItem::size().toSize().expandedTo(m_rootContainer->minSize()));
}
