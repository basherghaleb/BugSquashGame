/**
 * @file Feature.cpp
 * @author Jared Bloch
 */

#include "pch.h"
#include "Feature.h"

using namespace std;

/// Number of sprite images
const int FeatureNumSpriteImages = 7;

/**
 * Constructor for the feature class
 * @param level
 * @param program
 * @param images
 */
Feature::Feature(Level *level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images) : Bug(level, program, images, FeatureNumSpriteImages)
{
}

/**
 * Set the state of the bug
 * @param x number relating to the state
 */
void Feature::SetBugState(int x)
{
    if (x == 1)
    {
        Bug::SetBugState(3);
    } else if (x == 2)
    {
        Bug::SetBugState(4);
    }
}
