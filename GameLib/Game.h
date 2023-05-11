/**
 * @file Game.h
 * @author Evan Stanislaw
 *
 *
 */


#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "ScoreBoard.h"
#include "Item.h"

class Level;

/**
 * Game Class
 */
class Game {
private:
    ///The current level the game is on
    std::shared_ptr<Level> mCurrentLevel;

    ///The number representing the level
    int mCurrentLevelNum = 0;

    ///The vector containing all game levels
    std::vector<wxXmlDocument> mLevels;

    ///The vector containing all game images
    std::vector<std::shared_ptr<wxImage>> mImages;

    ///If the screen should be shrunk
	bool mShrank = false;

    ///X location of the screen
	double mXOffset = 0;

    ///Y location of the screen
	double mYOffset = 0;

    ///How much to scale the screen by
	double mScale = 0;

    ///If the app should be paused during fat bug pop up
    bool mPause = false;

    ///List of items in the game
	std::vector<std::shared_ptr<Item>> mItems;

    ///The current scoreboard
	ScoreBoard mScoreBoard;

    ///The splat item
	std::shared_ptr<Item> mSplatItem;

public:
	Game();
	void OnLeftDown(int x, int y);
    void OnMouseDoubleClick(int x, int y, wxWindow* = nullptr);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Update(double elapsed);
    void SetLevel(int level);

    /**
     * Sets pause when pop up menu appears
     * @param pause
     */
    void SetPause(bool pause){mPause = pause;}

    /**
     * Set the shrink
     * @param shrink
     */
	void SetShrink(bool shrink){mShrank = shrink;}

    /**
     * Get the shrink
     * @return shrink bool
     */
	bool GetShrink(){return mShrank;}

    /**
     * Get the current level
     * @return current level
     */
	std::shared_ptr<Level> GetLevel(){return mCurrentLevel;}

	/**
	 * Getter for the current level XML document
	 * @param num Level document needed
	 * @return Document needed
	 */
	wxXmlDocument GetLevelDocument(int num){return mLevels.at(num);}

	/**
	 * Getter for Images
	 * @return vector of Images
	 */
	std::vector<std::shared_ptr<wxImage>> GetImages(){return mImages;}
};

#endif //PROJECT1_GAME_H
