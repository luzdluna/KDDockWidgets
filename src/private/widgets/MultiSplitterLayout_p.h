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

/**
 * @file
 * @brief A class to layout widgets in any place relative to another widget.
 *
 * Widgets can be inserted to the left,right,top,bottom in relation to another widget or in relation
 * to the window. Each two neighbour widgets have a separator in between, which the user can use
 * to resize.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_MULTISPLITTER_LAYOUT_P_H
#define KD_MULTISPLITTER_LAYOUT_P_H


#include "multisplitter/Separator_p.h"
#include "docks_export.h"
#include "KDDockWidgets.h"
#include "LayoutSaver_p.h"
#include "QWidgetAdapter.h"

#include <QPointer>

namespace Layouting {
class Item;
class Separator;
class Widget_qwidget;
}

namespace KDDockWidgets {

class MultiSplitter;
class Frame;

namespace Debug {
class DebugWindow;
}

/**
 * MultiSplitterLayout is simply a wrapper around Layouting::Item in which the hosted widgets are
 * of class KDDockWidgets::Frame. The stuff in Layouting:: being agnostic and generic, not specific
 * to KDDW.
 *
 * A MultiSplitter is like a QSplitter but supports mixing vertical and horizontal splitters in
 * any combination.
 *
 * It supports adding a widget to the left/top/bottom/right of the whole MultiSplitter or adding
 * relative to a single widget.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS MultiSplitterLayout : public QObject // clazy:exclude=ctor-missing-parent-argument
{
    Q_OBJECT
public:
    /**
     * @brief Constructor. MultiSplitterLayout is created by MultiSplitter only.
     */
    explicit MultiSplitterLayout(MultiSplitter *parent);
    ~MultiSplitterLayout() override;

    /**
     * @brief returns the widget that this layout manages
     */
    MultiSplitter *multiSplitter() const;

    /**
     * @brief Adds a widget to this MultiSplitter.
     */
    void addWidget(QWidgetOrQuick *widget, KDDockWidgets::Location location,
                   Frame *relativeTo = nullptr, DefaultSizeMode = DefaultSizeMode::Fair, AddingOption option = {});

    /**
     * Adds an entire MultiSplitter into this layout. The donor MultiSplitter will be deleted
     * after all its Frames are stolen. All added Frames will preserve their original layout, so,
     * if widgetFoo was at the left of widgetBar when in the donor splitter, then it will still be at left
     * of widgetBar when the whole splitter is dropped into this one.
     */
    void addMultiSplitter(MultiSplitter *splitter, KDDockWidgets::Location location,
                          Frame *relativeTo = nullptr);

    /**
     * @brief Removes an item from this MultiSplitter.
     */
    void removeItem(Layouting::Item *item);

    /**
     * @brief Returns true if this layout contains the specified item.
     */
    bool contains(const Layouting::Item *) const;

    /**
     * @brief  Returns true if this layout contains the specified frame.
     */
    bool contains(const Frame *) const;

    /**
     * @brief Returns the number of Item objects in this layout.
     * This includes non-visible (placeholder) Items too.
     * @sa visibleCount
     */
    int count() const;

    /**
     * @brief Returns the number of visible Items in this layout.
     * Which is @ref count minus @ref placeholderCount
     * @sa count
     */
    int visibleCount() const;

    /**
     * @brief Returns the number of placeholder items in this layout.
     * This is the same as @ref count minus @ref visibleCount
     * @sa count, visibleCount
     */
    int placeholderCount() const;

    /**
     * @brief The list of items in this layout.
     */
    const QVector<Layouting::Item*> items() const;

    /**
     * @brief Returns the root container item
     */
    Layouting::ItemContainer *rootItem() const;

    /**
     * Called by the indicators, so they draw the drop rubber band at the correct place.
     * The rect for the rubberband when dropping a widget at the specified location.
     * Excludes the Separator thickness, result is actually smaller than what needed. In other words,
     * the result will be exactly the same as the geometry the widget will get.
     */
    QRect rectForDrop(const QWidgetOrQuick *widget, KDDockWidgets::Location location, const Layouting::Item *relativeTo) const;

    bool deserialize(const LayoutSaver::MultiSplitterLayout &);
    LayoutSaver::MultiSplitterLayout serialize() const;

    ///@brief returns the list of separators
    QVector<Layouting::Separator*> separators() const;

    /**
     * @brief Updates the min size of this layout.
     */
    void updateSizeConstraints();

    /**
     * @brief setter for the contents size
     * The "contents size" is just the size() of this layout. However, since resizing
     * QWidgets is async and we need it to be sync. As sometimes adding widgets will increase
     * the MultiSplitterLayout size (due to widget's min-size constraints).
     */
    void setSize(QSize);

    /**
     * @brief returns the contents width.
     * Usually it's the same width as the respective parent MultiSplitter.
     */
    int width() const { return size().width(); }

    /**
     * @brief returns the contents height.
     * Usually it's the same height as the respective parent MultiSplitter.
     */
    int height() const { return size().height(); }

    /**
     * @brief returns the layout's minimum size
     * @ref setMinimumSize
     */
    QSize minimumSize() const;

    /**
     * @brief getter for the size
     */
    QSize size() const;

    /// @brief Runs some sanity checks. Returns true if everything is OK
    bool checkSanity() const;

    /// @brief dumps the layout to stderr
    void dumpDebug() const;

    /**
     * @brief returns the Item that holds @p frame in this layout
     */
    Layouting::Item *itemForFrame(const Frame *frame) const;

    /**
     * @brief Returns a list of Frame objects contained in this layout
     */
    QList<Frame*> frames() const;

    /// @brief restores the dockwidget @p dw to its previous position
    void restorePlaceholder(DockWidgetBase *dw, Layouting::Item *, int tabIndex);

    /// @brief See docs for MainWindowBase::layoutEqually()
    void layoutEqually();

    /// @brief overload that just resizes widgets within a sub-tree
    void layoutEqually(Layouting::ItemContainer *);

Q_SIGNALS:
    void visibleWidgetCountChanged(int count);

    ///@brief emitted when the size changes
    ///@sa size
    void sizeChanged(QSize sz);

    ///@brief emitted when the minimumSize changes
    ///@sa minimumSize
    void minimumSizeChanged(QSize);

private:
    friend class TestDocks;

    /**
     * @brief returns the frames contained in @p frameOrMultiSplitter
     * If frameOrMultiSplitter is a Frame, it returns a list of 1 element, with that frame
     * If frameOrMultiSplitter is a MultiSplitterLayout then it returns a list of all frames it contains
     */
    QList<Frame*> framesFrom(QWidgetOrQuick *frameOrMultiSplitter) const;


    // For debug/hardening
    bool validateInputs(QWidgetOrQuick *widget, KDDockWidgets::Location location,
                        const Frame *relativeToFrame, AddingOption option) const;

    /**
     * @brief Removes unneeded placeholder items when adding new frames.
     *
     * A floating frame A might have a placeholder in the main window (for example to remember its position on the Left),
     * but then the user might attach it to the right, so the left placeholder is no longer need.
     * Right before adding the frame to the right we remove the left placeholder, otherwise it's unrefed while we're adding
     * causing a segfault. So what this does is making the unrefing happen a bit earlier.
     */
    void unrefOldPlaceholders(const QList<Frame*> &framesBeingAdded) const;

    /**
     * @brief setter for the minimum size
     * @ref minimumSize
     */
    void setMinimumSize(QSize);

    void setRootItem(Layouting::ItemContainer *);

    /**
     * @brief Like @ref availableLengthForDrop but just returns the total available width or height (depending on @p orientation)
     * So no need to receive any location.
     * @param orientation If Qt::Vertical then returns the available height. Width otherwise.
     */
    int availableLengthForOrientation(Qt::Orientation orientation) const;

    /**
     * @brief Equivalent to @ref availableLengthForOrientation but returns for both orientations.
     * width is for Qt::Vertical.
     */
    QSize availableSize() const;

    MultiSplitter *const m_multiSplitter;
    Layouting::ItemContainer *m_rootItem = nullptr;
};

}

#endif
