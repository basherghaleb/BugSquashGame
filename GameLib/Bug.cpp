/**
 * @file Bug.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Bug.h"
#include "Game.h"
#include "Item.h"
#include "Level.h"
#include "ScoreBoard.h"
#include <cmath>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/regex.h>

using namespace std;

///Hit range for the bug
const int BugHitRange = 50;

///Fat bug scale
const double FatScale = 1.25;

/**
 * Constructor for the bug
 * @param level the bug is on
 * @param program program it is going toward
 * @param images the images
 * @param NumSpriteImages
 * @param x location
 * @param y location
 * @param speed
 */
Bug::Bug(Level *level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images, int NumSpriteImages, double x, double y, double speed) : Item(level, x, y)
{
    mNumSpriteImages = NumSpriteImages;
    if (mNumSpriteImages == 5) {
        mItemImage = images.at(0);
        mSplatImage = images.at(1);
        mNumSpriteImages++;
    } else if (mNumSpriteImages == 6) {
        mItemImage = images.at(2);
        mSplatImage = images.at(3);
        mNumSpriteImages++;
    } else if (mNumSpriteImages == 7) {
        mItemImage = images.at(4);
        mSplatImage = images.at(5);
    } else if (mNumSpriteImages == 3)
    {
        mItemImage = images.at(12);
        mSplatImage = images.at(13);
    }
    mActiveSprite = NumSpriteImages - 1;
    mSpeed = speed;
    mProgram = program;
    if (mSpeed != 0) {
        mAngle = atan2(mProgram->GetY()-y, mProgram->GetX()-x);
    }
}

/**
 * Destructor
 */
Bug::~Bug()
{
}

/**
 * update to move bug
 * @param elapsed
 */
void Bug::Update(double elapsed)
{
    mTimeSpent = mTimeSpent + elapsed;
    if(GetIfStart() && mBugState == 0)
    {
        if (mDuration <= 0) {
            if (mActiveSprite >= mNumSpriteImages - 2) {
                mActiveSprite = 0;
            } else {
                mActiveSprite = mActiveSprite + 1;
            }
            mDuration = 3/mSpeed;
        } else {
            mDuration = mDuration - elapsed;
        }

        double newX = GetX() + elapsed  * mSpeed * cos(mAngle);
        double newY = GetY() + elapsed  * mSpeed * sin(mAngle);

        double differenceX = mProgram->GetX() - newX;
        double differenceY = mProgram->GetY() - newY;

        if(std::abs(differenceX) < 10 && std::abs(differenceY) < 10)
        {
            SetLocation(mProgram->GetX(), mProgram->GetY());
            SetBugState(2);
        }
        else
        {
            SetLocation(newX, newY);
        }
    }
}

/**
 * draws the bug depending on the state
 * @param graphics
 */
void Bug::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mItemBitmap.IsNull())
    {
        mItemBitmap = graphics -> CreateBitmapFromImage(*mItemImage);
        mSplatBitmap = graphics -> CreateBitmapFromImage(*mSplatImage);
    }

    if (mBugState == 1 || mBugState == 3)
    {
        double wid = mSplatImage->GetWidth();
        double hit = mSplatImage->GetHeight();
        graphics->PushState();  // Save the graphics state
        graphics->Translate(GetX(), GetY());
        graphics->Rotate(mAngle);
        if (mFat) {
            graphics->Scale(FatScale, FatScale);
        }
        graphics->DrawBitmap(mSplatBitmap, -wid/2, -hit/2, mSplatImage->GetWidth(), mSplatImage->GetHeight());
        graphics->PopState();   // Restore the graphics state
    }
    else if (mBugState == 0)
    {
        double wid = mItemImage->GetWidth();
        double hit = mItemImage->GetHeight();
        double spriteHeight = hit/mNumSpriteImages;
        graphics->PushState();  // Save the graphics state
        graphics->Translate(GetX(), GetY());
        if (mFat) {
            graphics->Scale(FatScale, FatScale);
        }
        if (GetIfStart()) {
            graphics->Rotate(mAngle);
        }
        graphics->Clip(-wid/2, -spriteHeight/2, wid, spriteHeight);
        graphics->DrawBitmap(mItemBitmap, -wid/2, (mActiveSprite * -spriteHeight)-spriteHeight/2, mItemImage->GetWidth(), mItemImage->GetHeight());
        graphics->PopState();   // Restore the graphics state
    }
}

/**
 * Save this bug to an XML node
 * @param node The parent node we are going to be a child of
 */
void Bug::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    node->GetAttribute(L"speed", L"0").ToDouble(&mSpeed);
    node->GetAttribute(L"start", L"0").ToDouble(&mStart);
    mAngle = atan2(mProgram->GetY()-GetY(), mProgram->GetX()-GetX());
    auto code = node->GetChildren();
    if (code !=nullptr)
    {
        mFat = true;

		auto codeNode = code->GetChildren();

		// mCode is always broken
		mCode = codeNode->GetContent();

		// To fix mCode, the user needs to insert the pass attribute
		mCodeFix = code->GetAttribute(L"pass", L"");
    }
}

/**
 * Test to see if we clicked the bug
 * @param x location
 * @param y location
 * @param double_clicked if actually clicked
 * @param w window
 * @return
 */
bool Bug::HitTest(double x, double y, bool double_clicked, wxWindow* w)
{
    if (GetBugState() == 0)
    {
        double dx = x - GetX();
        double dy = y - GetY();

        if (sqrt(dx * dx + dy * dy) < BugHitRange)
        {
            if (!mFat && !double_clicked) {
                SetBugState(1);
                return true;
            } else if (mFat && double_clicked) {

				wxDialog dlg = wxDialog( w, wxID_ANY, "Fix Code");

				wxBoxSizer *top_sizer = new wxBoxSizer( wxVERTICAL );
				// create text ctrl with minimal size 100x60 that is horizontally and
				// vertically stretchable with a border width of 10
                wxTextCtrl *new_code = new wxTextCtrl( &dlg, -1, mCode, wxDefaultPosition, wxSize(600,500), wxTE_MULTILINE);
				top_sizer->Add(new_code);

				wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
				//create two buttons that are horizontally unstretchable,
				// with an all-around border with a width of 10 and implicit top alignment
				button_sizer->Add(
					new wxButton( &dlg, wxID_OK, "OK" ));
				top_sizer->Add(
					button_sizer,
					wxSizerFlags(0).Center() );
				dlg.SetSizerAndFit(top_sizer);

                GetLevel()->GetGame()->SetPause(true);
				dlg.ShowModal();

                wxRegEx rxg(mCodeFix);
				wxMessageBox(mCodeFix);

                if (rxg.Matches(new_code->GetValue())) {
                    SetBugState(1);
                }

				dlg.Destroy();
                GetLevel()->GetGame()->SetPause(false);

                return true;
            }

        }
    }
    return false;
}