/**
 * @file GarbageBug.cpp
 * @author Jared Bloch
 */

#include "pch.h"
#include "GarbageBug.h"

/// Number of sprite images
const int GarbageBugNumSpriteImages = 5;

/**
 * Constructor for the garbage bug
 * @param level
 * @param program
 * @param images
 */
GarbageBug::GarbageBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images) : Bug(level, program, images, GarbageBugNumSpriteImages)
{
}