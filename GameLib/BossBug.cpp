/**
 * @file BossBug.cpp
 * @author mrazb
 */

#include "pch.h"
#include "BossBug.h"
#include <wx/gauge.h>

/// Number of sprite images
const int BossBugNumSpriteImages = 3;

/// X Center for the health bar
const int XCenter = 35;

/// Y Center for the health bar
const int YCenter = 130;

/// Health Ticks for the health bar
const int Health = 10;

/// Full width for the health bar
const int HealthFull = 100;

/// Height for the health bar
const int HealthBarHeight = 20;

/**
 * Constructor for the boss bug
 * @param level
 * @param program
 * @param images
 */
BossBug::BossBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images) : Bug(level, program, images, BossBugNumSpriteImages)
{
}

void BossBug::SetBugState(int x)
{
    if (x == 1 && mBossHealth > 1) {
        mBossHealth--;
    } else if (x == 1) {
        mBossHealth--;
        Bug::SetBugState(x);
    } else {
        Bug::SetBugState(x);
    }
}

void BossBug::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Bug::Draw(graphics);

    // Draw the health bar background
    if(mBossHealth > 0 && this->GetBugState() == 0)
    {
        graphics->SetBrush(*wxLIGHT_GREY_BRUSH);
        graphics->SetPen(*wxTRANSPARENT_PEN);
        graphics->DrawRectangle(GetX() - XCenter, GetY() - YCenter, HealthFull, HealthBarHeight);

        // Draw the health bar foreground
        graphics->SetBrush(*wxRED_BRUSH);
        graphics->SetPen(*wxTRANSPARENT_PEN);
        graphics->DrawRectangle(GetX() - XCenter, GetY() - YCenter,  mBossHealth * Health , HealthBarHeight);
    }


}

