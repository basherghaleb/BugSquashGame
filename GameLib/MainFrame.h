/**
 * @file MainFrame.h
 * @author Jared Bloch
 *
 *
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H

#include "ScoreBoard.h"


class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    ///Reference to the game view
	GameView *mGameView;
    void OnExit(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);

public:
    void Initialize();
};

#endif //PROJECT1_MAINFRAME_H
