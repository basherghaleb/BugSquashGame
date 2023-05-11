/**
 * @file Game.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "BugVisitor.h"
#include <iostream>
#include <wx/dcbuffer.h>

using namespace std;

/// Scale to shrink to when in shrink mode
const double ShrinkScale = 0.75;

/// Game area in virtual pixels
const int Width = 1250;

/// Game area height in virtual pixels
const int Height = 1000;

/// Level 0 file
const std::wstring level0 = L"data/level0.xml";

/// Level 1 file
const std::wstring level1 = L"data/level1.xml";

/// Level 2 file
const std::wstring level2 = L"data/level2.xml";

/// Level 3 file
const std::wstring level3 = L"data/level3.xml";

/// The bug sprite image index 0
const std::wstring GarbageBugSpriteImageName = L"images/blue-maize-bug.png";

/// The splat image index 1
const std::wstring GarbageBugSplatImageName = L"images/blue-maize-splat.png";

/// The bug sprite image index 2
const std::wstring NullBugSpriteImageName = L"images/scarlet-gray-bug.png";

/// The splat image index 3
const std::wstring NullBugSplatImageName = L"images/scarlet-gray-splat.png";

/// The feature sprite image index 4
const std::wstring FeatureImageName = L"images/feature.png";

/// The splat image index 5
const std::wstring FeatureSplatImageName = L"images/feature-splat.png";

/// The bug base image index 6
const std::wstring RedundancyFlyImageName = L"images/redundancy-fly-base.png";

/// The bug top image index 7
const std::wstring RedundancyFlyTopImageName = L"images/redundancy-fly-top.png";

/// The left wing image index 8
const std::wstring RedundancyFlyLeftWingImageName = L"images/redundancy-fly-lwing.png";

/// The right wing image index 9
const std::wstring RedundancyFlyRightWingImageName = L"images/redundancy-fly-rwing.png";

/// The splat image index 10
const std::wstring RedundancyFlySplatImageName = L"images/redundancy-fly-splat.png";

/// Program image filename index 11
const std::wstring ProgramImage = L"images/laptop.png";

/// The bug sprite image index 12
const std::wstring BossBugSpriteImageName = L"images/boss-bug.png";

/// The splat image index 13
const std::wstring BossBugSplatImageName = L"images/boss-bug-splat.png";

/**
 * Game Constructor
 * creates all the images and holds them in a image vector
 */
Game::Game()
{
    mImages.push_back(make_shared<wxImage>(GarbageBugSpriteImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(GarbageBugSplatImageName, wxBITMAP_TYPE_ANY));

    mImages.push_back(make_shared<wxImage>(NullBugSpriteImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(NullBugSplatImageName, wxBITMAP_TYPE_ANY));

    mImages.push_back(make_shared<wxImage>(FeatureImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(FeatureSplatImageName, wxBITMAP_TYPE_ANY));

    mImages.push_back(make_shared<wxImage>(RedundancyFlyImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(RedundancyFlyTopImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(RedundancyFlyLeftWingImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(RedundancyFlyRightWingImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(RedundancyFlySplatImageName, wxBITMAP_TYPE_ANY));

    mImages.push_back(make_shared<wxImage>(ProgramImage, wxBITMAP_TYPE_ANY));

    mImages.push_back(make_shared<wxImage>(BossBugSpriteImageName, wxBITMAP_TYPE_ANY));
    mImages.push_back(make_shared<wxImage>(BossBugSplatImageName, wxBITMAP_TYPE_ANY));

    mLevels.emplace_back(level0);
    mLevels.emplace_back(level1);
    mLevels.emplace_back(level2);
    mLevels.emplace_back(level3);
    mCurrentLevel = make_shared<Level>(this, mLevels.at(0), mImages);
}

/**
 * Draw the game area
 * @param graphics The graphics context to draw on
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
	//
	// Automatic Scaling
	//
	auto scaleX = double(width) / double(Width);
	auto scaleY = double(height) / double(Height);
	mScale = std::min(scaleX, scaleY);

	if(mShrank)
	{
		mScale *= ShrinkScale;
	}

	mXOffset = (width - Width * mScale) / 2;
	mYOffset = (height - Height * mScale) / 2;

	graphics->PushState();

	graphics->Translate(mXOffset, mYOffset);
	graphics->Scale(mScale, mScale);

	if (!mShrank)
	{
		graphics->Clip(0,0,Width,Height);
	}

	// From here on you are drawing virtual pixels
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(0, 0, Width, Height);

    // Your drawing code goes here
    mCurrentLevel->Draw(graphics);

	/* Scoreboard Draw */
	mScoreBoard.Draw(graphics);

	graphics->PopState();
}

/**
* Handle a mouse click
* Update boolean when bugs are clicked
* Update Fixed Scoreboard when bugs are clicked
* Update Missed Scoreboard when bugs aren't clicked
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	mCurrentLevel->HitTest(oX, oY, false);
}

/**
 * * Handle a mouse double click
 * Update boolean when bugs are clicked
 * Update Fixed Scoreboard when bugs are clicked
 * Update Missed Scoreboard when bugs aren't clicked
 * @param x X location clicked on
 * @param y Y location clicked on
 * @param w Window to pop up
 */
void Game::OnMouseDoubleClick(int x, int y, wxWindow* w)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;
    mCurrentLevel->HitTest(oX, oY, true);
}


/**
 * Update the game
 * @param elapsed
 */
void Game::Update(double elapsed)
{
    if (!mPause)
    {
        BugVisitor visitor;
        mCurrentLevel->Accept(&visitor);
        mScoreBoard.UpdateFixed(visitor.GetNumDead());
        mScoreBoard.UpdateMissed(visitor.GetmNumMissed());
        mScoreBoard.UpdateOops(visitor.GetNumOops());
        mCurrentLevel->Update(elapsed);
        if(mCurrentLevel->LevelDone())
        {
            if(mCurrentLevelNum < 3)
            {
                this->SetLevel(mCurrentLevelNum + 1);
            } else {
                this->SetLevel(mCurrentLevelNum);
            }
        }
    }
}

/**
 * Set the current level for the game
 * @param level
 */
void Game::SetLevel(int level)
{
    mCurrentLevelNum = level;
    mCurrentLevel = make_shared<Level>(this, mLevels.at(level), mImages);
}