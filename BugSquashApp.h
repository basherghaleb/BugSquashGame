/**
 * @file BugSquashApp.h
 * @author Evan Stanislaw
 *
 *
 */

#ifndef PROJECT1_BUGSQUASHAPP_H
#define PROJECT1_BUGSQUASHAPP_H

#include <wx/wx.h>

/**
 * Class to initalize the bug squash app
 */
class BugSquashApp : public wxApp
{
private:

public:
    ///Initialization of the Bug Squash App
    virtual bool OnInit();
};

#endif //PROJECT1_BUGSQUASHAPP_H
