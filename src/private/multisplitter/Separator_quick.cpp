/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "Widget_quick.h"
#include "Separator_quick.h"
#include "Logging_p.h"


using namespace Layouting;

namespace Layouting {
// TODO: Finish rubberband
class RubberBand : public QQuickItem
                 , public Layouting::Widget_quick
{

public:
    RubberBand(Layouting::Widget *parent)
        : QQuickItem(parent ? qobject_cast<QQuickItem*>(parent->asQObject()) : nullptr)
        , Layouting::Widget_quick(this) {
    }
};

}

SeparatorQuick::SeparatorQuick(Layouting::Widget *parent)
    : QQuickItem(qobject_cast<QQuickItem*>(parent->asQObject()))
    , Separator(parent)
    , Layouting::Widget_quick(this)
{
}

Layouting::Widget *SeparatorQuick::createRubberBand(Layouting::Widget *parent)
{
    if (!parent) {
        qWarning() << Q_FUNC_INFO << "Parent is required";
        return nullptr;
    }

    return new Layouting::Widget_quick(new RubberBand(parent));
}

Widget *SeparatorQuick::asWidget()
{
    return this;
}
