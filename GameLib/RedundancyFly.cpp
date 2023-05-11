/**
 * @file RedundancyFly.cpp
 * @author Jared Bloch
 */

#include "pch.h"
#include "RedundancyFly.h"
#include "Level.h"
#include <random>
#include <iostream>

using namespace std;

/// The bug base image
const std::wstring RedundancyFlyImageName = L"images/redundancy-fly-base.png";

/// The bug top image
const std::wstring RedundancyFlyTopImageName = L"images/redundancy-fly-top.png";

/// The left wing image
const std::wstring RedundancyFlyLeftWingImageName = L"images/redundancy-fly-lwing.png";

/// The right wing image
const std::wstring RedundancyFlyRightWingImageName = L"images/redundancy-fly-rwing.png";

/// The splat image
const std::wstring RedundancyFlySplatImageName = L"images/redundancy-fly-splat.png";


/// Wing flapping period in seconds
const double WingPeriod = 0.2;

/// Starting rotation angle for wings in radians
const double WingRotateStart = 0.0;

/// End rotation angle for wings in radians
const double WingRotateEnd = 0.7;

/// How many sets of wings does this bug have?
const int NumberOfSetsOfWings = 4;

/// Number of virtual pixels between each of the wing sets
const int WingSetXOffset = 12;

/// X position relative to center of bug for the first (back) wing set
const int FirstWingSetX = -36;

/// Y position relative to center of bug for the right wings. The negative
/// of this is the Y position for the left wings.
const int WingSetY = 5;


/**
 * The construtor for the redundancy fly
 * @param level
 * @param program
 * @param images
 * @param spawn
 * @param x
 * @param y
 * @param speed
 */
RedundancyFly::RedundancyFly(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images, bool spawn, double x, double y, double speed) : Bug(level, program, images, 0, x, y, speed)
{
    mSpawn = spawn;
	mRedundancyFlyImage = images.at(6);
	mRedundancyFlyTopImageName = images.at(7);
	mRedundancyFlyLeftWingImageName = images.at(8);
	mRedundancyFlyRightWingImageName = images.at(9);
    mRedundancyFlySplatImage = images.at(10);
}

/**
 * Draw function for the redundancy fly
 * @param graphics
 */
void RedundancyFly::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	if (mRedundancyFlyBitmapBase.IsNull())
	{
		mRedundancyFlyBitmapBase = graphics -> CreateBitmapFromImage(*mRedundancyFlyImage);
		mRedundancyFlyBitmapTop = graphics -> CreateBitmapFromImage(*mRedundancyFlyTopImageName);
		mRedundancyFlyBitmapLeft = graphics -> CreateBitmapFromImage(*mRedundancyFlyLeftWingImageName);
		mRedundancyFlyBitmapRight = graphics -> CreateBitmapFromImage(*mRedundancyFlyRightWingImageName);
        mRedundancyFlyBitmapSplat = graphics -> CreateBitmapFromImage(*mRedundancyFlySplatImage);
	}

    if(GetBugState() == 0)
	{
        graphics->PushState();  // Save the graphics state
        graphics->Translate(GetX(), GetY());
        if (GetIfStart()) {
            graphics->Rotate(GetAngle());
        }
        graphics->DrawBitmap(mRedundancyFlyBitmapBase, -mRedundancyFlyImage->GetWidth()/2, -mRedundancyFlyImage->GetHeight()/2, mRedundancyFlyImage->GetWidth(),mRedundancyFlyImage->GetHeight());
        graphics->PopState();   // Restore the graphics state

        //double t = 2 * fmod(GetDuration(), WingPeriod) / WingPeriod;
        //double angle = WingRotateStart + t * (WingRotateEnd - WingRotateStart);

        for (int i = 0; i<NumberOfSetsOfWings; i++)
		{
            graphics->PushState();  // Save the graphics state
            graphics->Translate(GetX(),GetY() );
            if (GetIfStart()) {
                graphics->Rotate(GetAngle());
            }

			// This is needed to draw the wing rotated wingsRotationAngle radians
			graphics->Rotate(-wingsRotationAngle);

			double oldX = (-mRedundancyFlyLeftWingImageName->GetWidth()/2)+FirstWingSetX-(-WingSetXOffset*i);
			double oldY = (-mRedundancyFlyLeftWingImageName->GetHeight()/2)-WingSetY;

			graphics->DrawBitmap(mRedundancyFlyBitmapLeft,oldX,oldY,mRedundancyFlyLeftWingImageName->GetWidth(),mRedundancyFlyLeftWingImageName->GetHeight());

            graphics->PopState();   // Restore the graphics state

            graphics->PushState();  // Save the graphics state
            graphics->Translate(GetX(),GetY());

            if (GetIfStart())
			{
                graphics->Rotate(GetAngle());
            }
			graphics->Rotate(wingsRotationAngle);
            graphics->DrawBitmap(mRedundancyFlyBitmapRight,(-mRedundancyFlyRightWingImageName->GetWidth()/2)+FirstWingSetX-(-WingSetXOffset*i),(-mRedundancyFlyRightWingImageName->GetHeight()/2)+WingSetY,mRedundancyFlyRightWingImageName->GetWidth(),mRedundancyFlyRightWingImageName->GetHeight());
            graphics->PopState();   // Restore the graphics state
        }

        graphics->PushState();  // Save the graphics state
        graphics->Translate(GetX(),GetY());
        if (GetIfStart())
		{
            graphics->Rotate(GetAngle());
        }
        graphics->DrawBitmap(mRedundancyFlyBitmapTop, -mRedundancyFlyTopImageName->GetWidth()/2, -mRedundancyFlyTopImageName->GetHeight()/2, mRedundancyFlyTopImageName->GetWidth(),mRedundancyFlyTopImageName->GetHeight());
        graphics->PopState();   // Restore the graphics state
    }
    else if (GetBugState() == 1)
    {
        graphics->PushState();  // Save the graphics state
        graphics->Translate(GetX(), GetY());
        graphics->Rotate(GetAngle());
        graphics->DrawBitmap(mRedundancyFlyBitmapSplat, -mRedundancyFlySplatImage->GetWidth()/2, -mRedundancyFlySplatImage->GetHeight()/2, mRedundancyFlySplatImage->GetWidth(),mRedundancyFlySplatImage->GetHeight());
        graphics->PopState();   // Restore the graphics state
    }
}
/**
 * Wings rotation angle update
 * Update rate is 0.12 radians per update call
 * The angle is oscillating between 0 and 0.7 radians
 * @param elapsed
 */
void RedundancyFly::Update(double elapsed)
{
    if(GetBugState() == 0)
    {
        Bug::Update(elapsed);

        if (wingsRotationAscendingPhase)
        {
            wingsRotationAngle += WingPeriod;
            if (wingsRotationAngle >= WingRotateEnd)
            {
                wingsRotationAscendingPhase = false;
            }
        }
        else {
            wingsRotationAngle -= WingPeriod;
            if (wingsRotationAngle <= WingRotateStart)
            {
                wingsRotationAscendingPhase = true;
            }
        }
    }
}

/**
 * Update the state of the fly
 * @param x
 */
void RedundancyFly::SetBugState(int x)
{
    if (x == 1 && !mSpawn) {
        Bug::SetBugState(6);
        GetLevel()->AddSpawn(GetProgram(), GetX(), GetY(), GetSpeed());
    } else {
        Bug::SetBugState(x);
    }
}


