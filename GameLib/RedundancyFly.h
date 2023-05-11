/**
 * @file RedundancyFly.h
 * @author Jared Bloch
 *
 * Redundancy Fly Class
 */

#ifndef PROJECT1_GAMELIB_REDUNDANCYFLY_H
#define PROJECT1_GAMELIB_REDUNDANCYFLY_H

#include "Bug.h"

/**
 * Redundancy Fly Class
 */
class RedundancyFly : public Bug {
	/// The underlying image
	std::shared_ptr<wxImage> mRedundancyFlyImage;
    ///The top image
    std::shared_ptr<wxImage> mRedundancyFlyTopImageName;
    ///The left wing image
    std::shared_ptr<wxImage> mRedundancyFlyLeftWingImageName;
    ///The right wing image
    std::shared_ptr<wxImage> mRedundancyFlyRightWingImageName;
    ///The fly splat image
    std::shared_ptr<wxImage> mRedundancyFlySplatImage;

	/// The bitmap we can display
	wxGraphicsBitmap mRedundancyFlyBitmapBase;
    ///The bitmap for the top image
	wxGraphicsBitmap mRedundancyFlyBitmapTop;
    ///The bitmap for the right wing
	wxGraphicsBitmap mRedundancyFlyBitmapRight;
    ///The bitmap for the left wing
	wxGraphicsBitmap mRedundancyFlyBitmapLeft;
    ///The bitmap for the splat
    wxGraphicsBitmap mRedundancyFlyBitmapSplat;

    ///The number of active sprites
	int mActiveSprite = 6;

    ///The rotation angle of the wings
	double wingsRotationAngle = 0;  // Oscillates between 0 and 40 degrees
    ///If the wings are ascending
	bool wingsRotationAscendingPhase = true;
    ///If the fly is in the game
    bool mSpawn;

    ///The vector containing images
    std::vector<std::shared_ptr<wxImage>> mImages;

public:
	/// Default constructor (disabled)
	RedundancyFly() = delete;

	/// Copy constructor (disabled)
	RedundancyFly(const RedundancyFly &) = delete;

	/// Assignment operator
	void operator=(const RedundancyFly &) = delete;

	RedundancyFly(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images, bool spawn = false, double x = 0, double y = 0, double speed = 0);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	void Update(double elapsed) override;

    void SetBugState(int x) override;
};

#endif //PROJECT1_GAMELIB_REDUNDANCYFLY_H
