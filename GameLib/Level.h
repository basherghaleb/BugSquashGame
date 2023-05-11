/**
 * @file Level.h
 * @author Evan Stanislaw
 *
 * Level Class
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H

#include <random>
#include "Program.h"
#include "GarbageBug.h"

class Item;
class Game;

/**
 * Level Class
 */
class Level {
private:
	/// All of the items to populate our game
	std::vector<std::shared_ptr<Item>> mItems;
    ///All of the new items in the level
    std::vector<std::shared_ptr<Item>> mNewItems;
    ///All of the images in the level
    std::vector<std::shared_ptr<wxImage>> mImages;

    /// Random number generator
    std::mt19937 mRandom;

    ///Number of bugs in the level
	int numBugs = 0;
    ///Number of programs in the level
	int numPrograms = 0;

    ///Reference to the current game
	Game *mGame;

    ///Filename of the bug
    std::wstring mFilename;

    ///Program of the level
    std::wstring mLevelName;

    ///If the game has just started
    bool mStartGame = true;
    ///If the game is being played
    bool mMainGame = false;
    ///If the end screen should appear
    bool mEndGame = false;
    ///If the level should be changed
    bool mChangeLevel = false;

    ///Time in the level
    double mLevelTime = 0;
    ///Time in which the level ends
    double mEndTime = 0;

public:

    /// Assignment operator
    void operator=(const Level &) = delete;

    Level(Game* game, const wxXmlDocument& xmlDoc, std::vector<std::shared_ptr<wxImage>> images);
    void XmlItem(wxXmlNode *node);
    void Load(const wxXmlDocument& xmlDoc);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Update(double elapsed);
    void HitTest(double x, double y, bool double_clicked, wxWindow* w = nullptr);
    void Accept(ItemVisitor* visitor);
    void AddSpawn(std::shared_ptr<Item> program, double x, double y, double speed);

    /**
     * Clear the game data.
     *
     * Deletes all known items in the game.
     */
    void Clear(){mItems.clear();}

    /**
     * Get the number of bugs
     * @return
     */
	int GetNumBugs(){return numBugs;}

    /**
     * Get the number of programs
     * @return
     */
	int GetNumPrograms(){return numPrograms;}

    /**
     * Get a random number
     * @return
     */
    std::mt19937 &GetRandom() {return mRandom;}

    /**
     * Get the program
     * @return
     */
    std::wstring GetLevelName() { return mLevelName;}

    /**
     * Indicate that the current level is over
     * @return
     */
    bool LevelDone() {return mChangeLevel;}

    /**
     * Get all of the items in the level
     * @return
     */
	std::vector<std::shared_ptr<Item>> GetItems(){return mItems;}

    /**
     * Returns game level is associated with
     * @return
     */
    Game* GetGame() {return mGame;}
};

#endif //PROJECT1_LEVEL_H

