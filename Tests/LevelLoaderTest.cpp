/**
 * @file LevelLoaderTest.cpp
 * @author Basher Ghaleb
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Level.h>
#include <string>
#include <wx/xml/xml.h>

using namespace std;


/// Level 0 file
const std::wstring level0 = L"data/level0.xml";
/// Level 1 file
const std::wstring level1 = L"data/level1.xml";

/// Level 2 file
const std::wstring level2 = L"data/level2.xml";

/// Level 3 file
const std::wstring level3 = L"data/level3.xml";

/** Mock class for testing the class Level */
class LevelLoader : public Level
{
public:

	LevelLoader(Game *game, const wxXmlDocument filename, std::vector<std::shared_ptr<wxImage>> images) : Level(game, filename, images){}
};


TEST(LevelLoader, NumProgramsLevel0)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(0);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumPrograms(), 1);
    ASSERT_EQ(levelLoader.GetLevelName(), L"Level Zero");
}

TEST(LevelLoader, NumProgramsLevel1)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(1);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumPrograms(), 1);
    ASSERT_EQ(levelLoader.GetLevelName(), L"Single Team");
}

TEST(LevelLoader, NumProgramsLevel2)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(2);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumPrograms(), 3);
    ASSERT_EQ(levelLoader.GetLevelName(), L"Many Teams");
}

TEST(LevelLoader, NumProgramsLevel3)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(3);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumPrograms(), 2);
    ASSERT_EQ(levelLoader.GetLevelName(), L"Boss Level");
}



TEST(LevelLoader, NumBugsLevel0)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(0);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumBugs(), 7);
}

TEST(LevelLoader, NumBugsLevel1)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(1);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumBugs(), 12);
}

TEST(LevelLoader, NumBugsLevel2)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(2);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumBugs(), 24);
}

TEST(LevelLoader, NumBugsLevel3)
{
	Game game;
	auto images = game.GetImages();
	auto filename = game.GetLevelDocument(3);
	LevelLoader levelLoader = LevelLoader(&game, filename, images);

	ASSERT_EQ(levelLoader.GetNumBugs(), 23);
}


