/**
 * @file Item.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Item.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{
}

/**
 * Constructor for the level
 * @param level current level
 * @param x location
 * @param y location
 */
Item::Item(Level *level, double x, double y)
{
    mLevel = level;
    mX = x;
    mY = y;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
}

