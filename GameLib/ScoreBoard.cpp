/**
 * @file ScoreBoard.cpp
 * @author Jared Bloch
 */

#include "pch.h"
#include "ScoreBoard.h"

/// Score font size to use
const int ScoreSize = 85;

/// Lable for score font size to use
const int LabelSize = 40;

/// The font color to use
const wxColour FontColor = wxColour(0, 200, 200);

/// Size of the area we are going to draw on in pixels
constexpr static double Size = 1250;

/// Left score X location. The right score is
/// the width minus this value.
const int LeftScoreX = 150;

/// Left score X label location
const int LeftScoreLabelX = LeftScoreX -30;

/// Middle score X label location
const int MiddleScoreLabelX = Size/2 -60;

/// Right score X label location
const int RightScoreLabelX = Size - LeftScoreX - 30;

/// Score Y location
const int ScoreY = 20;

/// Score label Y location
const int ScoreLabelY = 100;

/**
 * Constructor
 */
ScoreBoard::ScoreBoard(){

}

/**
 * Draw function for the scoreboard
 * @param graphics
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	//
	// Draw some text
	//
	wxFont scoreFont(wxSize(0, ScoreSize),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_BOLD);

	wxFont labelFont(wxSize(0, LabelSize),
					 wxFONTFAMILY_SWISS,
					 wxFONTSTYLE_NORMAL,
					 wxFONTWEIGHT_BOLD);

	graphics->SetFont(scoreFont, FontColor);

	graphics->DrawText(std::to_wstring(mFixed), LeftScoreX, ScoreY);
	graphics->DrawText(std::to_wstring(mMissed), Size/2 - 20, ScoreY);
	graphics->DrawText(std::to_wstring(mOops), Size - LeftScoreX, ScoreY);

	graphics->SetFont(labelFont, FontColor);
	graphics->DrawText(L"Fixed", LeftScoreLabelX , ScoreLabelY);
	graphics->DrawText(L"Missed", MiddleScoreLabelX, ScoreLabelY);
	graphics->DrawText(L"Oops", RightScoreLabelX, ScoreLabelY);
}

/**
 * Increment the number of fixed by x
 * @param x
 */
void ScoreBoard::UpdateFixed(int x)
{
	mFixed = x;
}

/**
 * Increment the number of missed by x
 * @param x
 */
void ScoreBoard::UpdateMissed(int x)
{
	mMissed = x;
}


/**
 * Increment the number of oops by x
 * @param x
 */
void ScoreBoard::UpdateOops(int x)
{
	mOops = x;
}