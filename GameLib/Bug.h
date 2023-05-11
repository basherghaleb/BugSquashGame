/**
 * @file Bug.h
 * @author Evan Stanislaw
 *
 *
 */

#ifndef PROJECT1_BUG_H
#define PROJECT1_BUG_H

#include "Item.h"
class Level;

/**
 * Main class for bugs
 */
class Bug : public Item
{
private:
    /// The underlying image
    std::shared_ptr<wxImage> mItemImage;

    /// The bitmap we can display
    wxGraphicsBitmap mItemBitmap;

	/// The underlying image
	std::shared_ptr<wxImage> mSplatImage;

	/// The bitmap we can display
	wxGraphicsBitmap mSplatBitmap;

    /// Bug speed in pixels per second
    double mSpeed = 0;

    /// Start time of the bug
    double mStart = 0;

    /// Angle of the bug
    double mAngle;

    ///Number of sprite images
    int mNumSpriteImages;
    ///The amount of active sprites
    int mActiveSprite;

    ///Duration of the game
    double mDuration = 0;

    ///The program associated with the bug
    std::shared_ptr<Item> mProgram;

    ///Time spent on the level
    double mTimeSpent = 0;

    ///If the bug is a fat bug
    bool mFat = false;

    ///Code associated with the fat bug
    wxString mCode = "";

    ///How to fix the fat bug's code
    wxString mCodeFix = "";

    /// Bug state is how the bug is
    ///0 = alive
    ///1 = dead
    ///2 = missed
    ///3 = feature dead
    ///4 = feature missed
    ///5 = Redundancy Bug Base Dead
    int mBugState = 0;

public:
	Bug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images, int NumSpriteImages = 0, double x = 0, double y = 0, double speed = 0);

	~Bug();

    /**
     * Get the speed of the bug
     * @return speed
     */
    double GetSpeed() const { return mSpeed; }

    /**
     * Get the angle of the bug
     * @return
     */
    double GetAngle() const {return mAngle;}

    /**
     * Get the program associated with the bug
     * @return
     */
    std::shared_ptr<Item> GetProgram() {return mProgram;}

    /**
     * Update function for the bug
     * @param elapsed
     */
    void Update(double elapsed) override;

    /**
     * Draw function for the bug
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void XmlLoad(wxXmlNode *node) override;

    bool HitTest(double x, double y, bool double_clicked, wxWindow* w) override;

    /**
     * Get the state of the bug
     * @return
     */
    int GetBugState() const {return mBugState;}

    /**
     * Set the state of the bug
     * @param x
     */
    virtual void SetBugState(int x) {mBugState = x;}

    /**
     * Find if the level has just started
     * @return
     */
    bool GetIfStart() const {return mTimeSpent >= mStart;}

    /**
     * Accept for the bug visitor
     * @param visitor
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitBug(this); }

};

#endif //PROJECT1_BUG_H
