/**
 * @file BugSquashApp.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "BugSquashApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool BugSquashApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}