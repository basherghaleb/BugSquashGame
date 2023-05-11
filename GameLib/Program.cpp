/**
 * @file Program.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Program.h"

using namespace std;

/// Program name font size
const int ProgramNameFontSize = 22;

/**
 * Constructor for the program
 * @param level
 * @param images
 */
Program::Program(Level *level, std::vector<std::shared_ptr<wxImage>> images) : Item(level)
{
    mProgramImage = images.at(11);
}

/**
 * Destructor
 */
Program::~Program()
{
}

/**
 * Draw the Game
 * @param graphics The grpahics context to draw on
 */
void Program::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mProgramBitmap.IsNull())
    {
        mProgramBitmap = graphics -> CreateBitmapFromImage(*mProgramImage);
    }

    graphics->DrawBitmap(mProgramBitmap, GetX()-mProgramImage->GetWidth()/2, GetY()-mProgramImage->GetHeight()/2, mProgramImage->GetWidth(), mProgramImage->GetHeight());

    wxFont font(ProgramNameFontSize,
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL);
	graphics->SetFont(font, *wxWHITE);

	double width = 0;
	double height = 0;

	graphics->GetTextExtent(mName, &width,&height);
	graphics->DrawText(mName, GetX()-width/2, GetY() -height/2);
}

/**
 * Save this program to an XML node
 * @param node The parent node we are going to be a child of
 */
void Program::XmlLoad(wxXmlNode *node)
{
    mName = node->GetAttribute(L"name", L"");
    Item::XmlLoad(node);
}