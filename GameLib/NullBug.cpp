/**
 * @file NullBug.cpp
 * @author Jared Bloch
 */
#include "pch.h"
#include "NullBug.h"

/// Number of sprite images
const int NullBugNumSpriteImages = 6;

/**
 * Constructor for the null bug
 * @param level
 * @param program
 * @param images
 */
NullBug::NullBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images) : Bug(level, program, images, NullBugNumSpriteImages)
{
}