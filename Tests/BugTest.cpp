/**
 * @file BugTest.cpp
 * @author Renee Stanislaw
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>
#include <Level.h>
#include <GarbageBug.h>
#include <Feature.h>
#include <NullBug.h>
#include <RedundancyFly.h>
#include <Bug.h>
#include <wx/filename.h>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/xml/xml.h>

/// Level 0 file
const std::wstring level0 = L"data/level0.xml";
/// Level 1 file
const std::wstring level1 = L"data/level1.xml";

/// Level 2 file
const std::wstring level2 = L"data/level2.xml";

/// Level 3 file
const std::wstring level3 = L"data/level3.xml";

/**
 *  Bug Test Class
 */
class BugTest : public ::testing::Test{

private:
	 std::shared_ptr<Bug> mBug;

public:
	/**
	 * Creates a Bug
	 * @param num What level Bug is on
	 */
	void CreateBug(int num){

		if (num == 0)
		{
			Game game;
			game.SetLevel(num);
			auto level = game.GetLevel();

			ASSERT_FALSE(level == nullptr);

			auto items = level->GetItems();

			auto images = game.GetImages();

			ASSERT_EQ(items.size(),8);
			ASSERT_EQ(images.size(),14);

			mBug = std::make_shared<Bug>(level.get(), items[0], images);

		}

		if (num == 1)
		{
			Game game;
			game.SetLevel(num);
			auto level = game.GetLevel();

			ASSERT_FALSE(level == nullptr);

			auto items = level->GetItems();

			auto images = game.GetImages();

			ASSERT_EQ(items.size(),13);
			ASSERT_EQ(images.size(),14);

			mBug = std::make_shared<Bug>(level.get(), items[0], images);

		}

		if (num == 2)
		{
			Game game;
			game.SetLevel(num);
			auto level = game.GetLevel();

			ASSERT_FALSE(level == nullptr);

			auto items = level->GetItems();

			auto images = game.GetImages();

			ASSERT_EQ(items.size(),27);
			ASSERT_EQ(images.size(),14);

			mBug = std::make_shared<Bug>(level.get(), items[0], images);
		}

		if (num == 3)
		{
			Game game;
			game.SetLevel(num);
			auto level = game.GetLevel();

			ASSERT_FALSE(level == nullptr);

			auto items = level->GetItems();

			auto images = game.GetImages();

			ASSERT_EQ(items.size(),25);
			ASSERT_EQ(images.size(),14);

			mBug = std::make_shared<Bug>(level.get(), items[0], images);
		}

	}
protected:

	/**
	 * Tests Bug on whatever level is entered
	 * @param num the level to test
	 */
	void BugsToLevel(int num){

		CreateBug(num);
		mBug->SetLocation(200,200);
		mBug->HitTest(200, 200, false,nullptr);

		ASSERT_EQ(mBug->GetBugState(),1);

		CreateBug(num);

		mBug->SetLocation(200,200);
		mBug->HitTest(800, 800, false,nullptr);

		ASSERT_FALSE(mBug->GetBugState() == 1);
	}




};

TEST(RedundancyFlyTest, Construct){
	Game game;
	RedundancyFly redundancyFly(Level * level, std::shared_ptr<Item> program, Game game);
}

TEST(FeatureTest, Construct){
	Game game;
	Feature feature(Level * level, std::shared_ptr<Item> program, Game game);
}


TEST(GarbageBugTest, Construct){
	Game game;
	GarbageBug garbageBug(Level * level, std::shared_ptr<Item> program, Game game);
}

TEST(NullBugTest, Construct){
	Game game;
	NullBug nullBug(Level * level, std::shared_ptr<Item> program, Game game);
}


TEST_F(BugTest, GettersSetters){
	Game game;
	game.SetLevel(1);
	auto level = game.GetLevel();

	ASSERT_FALSE(level == nullptr);

	auto items = level->GetItems();

	auto images = game.GetImages();

	ASSERT_EQ(items.size(),13);
	ASSERT_EQ(images.size(),14);

	Bug bug(level.get(), items[0], images);


	// Test initial values
	ASSERT_NEAR(0, bug.GetX(), 0.0001);
	ASSERT_NEAR(0, bug.GetY(), 0.0001);

	// Test SetLocation, GetX, and GetY
	bug.SetLocation(10.5, 17.2);
	ASSERT_NEAR(10.5, bug.GetX(), 0.0001);
	ASSERT_NEAR(17.2, bug.GetY(), 0.0001);

	// Test a second with with different values
	bug.SetLocation(-72, -107);
	ASSERT_NEAR(-72, bug.GetX(), 0.0001);
	ASSERT_NEAR(-107, bug.GetY(), 0.0001);


}
TEST_F(BugTest,LevelTest)
{

	BugsToLevel(0);
	BugsToLevel(1);
	BugsToLevel(2);
	BugsToLevel(3);
}


