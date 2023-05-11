/**
 * @file MainFrame.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Game.h"
#include "MainFrame.h"
#include "ScoreBoard.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Bug Squash",wxDefaultPosition,  wxSize( 1000, 800 ));

    // Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer( wxVERTICAL );

	// Create the view class object as a child of MainFrame
	auto mGameView = new GameView();
	mGameView->Initialize(this);

	// Add it to the sizer
	sizer->Add(mGameView,1, wxEXPAND | wxALL );

	// Set the sizer for this frame
	SetSizer( sizer );

	// Layout (place) the child windows.
	Layout();

	auto menuBar = new wxMenuBar( );
	auto fileMenu = new wxMenu();
    auto shrinkMenu = new wxMenu();
	auto helpMenu = new wxMenu();
    auto loadMenu = new wxMenu();

    //Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShrink, mGameView, IDM_SHRINK);
    //Bind(wxEVT_UPDATE_UI, &GameView::OnShrinkUpdateUI, mGameView, IDM_SHRINK);

	menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(loadMenu, L"&Level");
    menuBar->Append(shrinkMenu, L"&Shrink");
    menuBar->Append(helpMenu, L"&Help");
	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	SetMenuBar( menuBar );

	CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    loadMenu->Append(IDM_LOADLEVEL0, "Level 0" , L"Open Level 0");
    loadMenu->Append(IDM_LOADLEVEL1, "Level 1" , L"Open Level 1");
    loadMenu->Append(IDM_LOADLEVEL2, "Level 2" , L"Open Level 2");
    loadMenu->Append(IDM_LOADLEVEL3, "Level 3" , L"Open Level 3");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnHelp, this, wxID_ABOUT);

    shrinkMenu->Append(IDM_SHRINK, "Shrink" , L"Shrink the Game");
    //Bind Shrinking
    //Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShrink, mGameView, IDM_SHRINK);
    //Bind(wxEVT_UPDATE_UI, &GameView::OnShrinkUpdateUI, mGameView, IDM_SHRINK);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    mGameView->Stop();
    Destroy();
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnHelp(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Bug Squash Game!",
            L"About Bug Squash",
            wxOK,
            this);
}