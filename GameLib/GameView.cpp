/**
 * @file GameView.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "GameView.h"
#include <sstream>
#include <wx/stdpaths.h>
#include <algorithm>
#include <wx/dcbuffer.h>
#include "ids.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Constructor
 */
GameView::GameView()
{

}

/**
 * Initialize the GameView class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
	Create(parent, wxID_ANY,
		   wxDefaultPosition, wxDefaultSize,
		   wxFULL_REPAINT_ON_RESIZE);

	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &GameView::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_DCLICK, &GameView::OnMouseDoubleClick, this);
    Bind(wxEVT_TIMER, &GameView::OnStart, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileLoadLevel0, this, IDM_LOADLEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileLoadLevel1, this, IDM_LOADLEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileLoadLevel2, this, IDM_LOADLEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileLoadLevel3, this, IDM_LOADLEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShrink, this, IDM_SHRINK);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);

	wxBrush background(*wxBLACK);
	dc.SetBackground(background);
	dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

	// Create a graphics context
	auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

	// Tell the game class to draw
	wxRect rect = GetRect();
	mGame.OnDraw(graphics, rect.GetWidth(), rect.GetHeight());

	// How big is this window
	auto size = GetClientRect();
	auto minDimension = min(size.GetWidth(), size.GetHeight());
	if(minDimension == 0)
	{
		// No reason to draw if the window is size zero
		// and this avoids any divide by zero errors
		return;
	}
    mGame.Update(elapsed);
}

/**
 * Refresh when the game starts
 * @param event
 */
void GameView::OnStart(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Command event handler for shrinking
 * @param event Command event
 */
void GameView::OnShrink(wxCommandEvent& event){

	mGame.SetShrink(!mGame.GetShrink());
}

/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
	mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle the double click event
 * @param event
 */
void GameView::OnMouseDoubleClick(wxMouseEvent& event)
{

    mGame.OnMouseDoubleClick(event.GetX(), event.GetY(), this);
}

/**
 * Menu handeler for Loading level 0
 * @param event Mouse event
 */
void GameView::OnFileLoadLevel0(wxCommandEvent &event)
{
    mGame.SetLevel(0);
}

/**
 * Menu handeler for Loading level 1
 * @param event Mouse event
 */
void GameView::OnFileLoadLevel1(wxCommandEvent &event)
{
    mGame.SetLevel(1);
}

/**
 * Menu handeler for Loading level 2
 * @param event Mouse event
 */
void GameView::OnFileLoadLevel2(wxCommandEvent &event)
{
    mGame.SetLevel(2);
}

/**
 * Menu handeler for Loading level 3
 * @param event Mouse event
 */
void GameView::OnFileLoadLevel3(wxCommandEvent &event)
{
    mGame.SetLevel(3);
}