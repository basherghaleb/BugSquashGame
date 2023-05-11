/**
 * @file GameView.h
 * @author Evan Stanislaw
 *
 *
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include "Game.h"
#include "ScoreBoard.h"
#include "Item.h"

/**
 * View class for the Bug Squash Game
 */
class GameView : public wxWindow
{
private:
	void OnPaint(wxPaintEvent& event);
    void OnStart(wxTimerEvent &event);

    /// The game we are viewing
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;
public:
	GameView();
	void Initialize(wxFrame* parent);
	void OnShrink(wxCommandEvent& event);
	void OnLeftDown(wxMouseEvent &event);
    void OnMouseDoubleClick(wxMouseEvent& event);
    void OnFileLoadLevel0(wxCommandEvent &event);
    void OnFileLoadLevel1(wxCommandEvent &event);
    void OnFileLoadLevel2(wxCommandEvent &event);
    void OnFileLoadLevel3(wxCommandEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}
};

#endif //PROJECT1_GAMEVIEW_H
