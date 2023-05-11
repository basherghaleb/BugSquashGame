/**
 * @file Item.h
 * @author Evan Stanislaw
 *
 *
 */

#pragma once

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include "ItemVisitor.h"

class Level;

/**
 * Class to add items into
 * the game
 */
class Item
{
private:
    /// The game this item is contained in
    Level *mLevel;

    /// Item location in the game
    double  mX;     ///< X location for the center of the item
    double  mY;     ///< Y location for the center of the item

    /// The underlying image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display
    wxGraphicsBitmap mItemBitmap;

protected:
    Item(Level *level, double x = 0, double y = 0);

public:
    ~Item();


    /// Assignment operator
    void operator=(const Item &) = delete;

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Draw this item
     * @param graphics
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * Update the current item
     * @param elapsed
     */
    virtual void Update(double elapsed) {}

    /**
     * Check if the item was hit
     * @param x position
     * @param y position
     * @param double_clicked if clicked true
     * @param w window
     * @return
     */
	virtual bool HitTest(double x, double y, bool double_clicked, wxWindow* w){return false;}

    /**
     * Accept a visitor
      * @param visitor The visitor we accept
      */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * Get the current level of the game
     * @return
     */
    Level* GetLevel() {return mLevel;}
};

#endif //PROJECT1_ITEM_H
