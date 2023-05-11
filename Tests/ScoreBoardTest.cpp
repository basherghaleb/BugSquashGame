/**
 * @file ScoreBoardTest.cpp
 * @author Jared Bloch
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
#include <BugVisitor.h>


/**
 * TestVisitor Class for testing ScoreBoard
 */
class TestVisitor : public ItemVisitor
{
public:

	virtual void VisitBug(Bug* bug) override {
		int state = bug->GetBugState();
		if (state == 0) {
			mNumAlive++;
		} else if (state == 1) {
			mNumDead++;
		} else if (state == 2) {
			mNumMissed++;
		} else if (state == 3)
		{
			mNumOops++;
		}
	}

	virtual void VisitProgram(Program* program) override {}

	int mNumAlive = 0;
	int mNumDead = 0;
	int mNumMissed = 0;
	int mNumOops = 0;

};


/**
 * ScoreBoardTest Class for Level One
 */
class ScoreBoardTest : public ::testing::Test{

protected:

	void CreateFeatureAndSplat(int num){
		Game game;
		game.SetLevel(num);
		auto level = game.GetLevel();

		ASSERT_FALSE(level == nullptr);

		auto items = level->GetItems();

		auto images = game.GetImages();

		ASSERT_EQ(items.size(),13);
		ASSERT_EQ(images.size(),14);

		auto program = items[0];

		auto feature = items[5];



		feature->SetLocation(400,400);

		feature->HitTest(400,400,false,nullptr);

		TestVisitor visitor;
		level->Accept(&visitor);

		ASSERT_EQ(visitor.mNumAlive,11);
		ASSERT_EQ(visitor.mNumDead,0);
		ASSERT_EQ(visitor.mNumOops,1);
		ASSERT_EQ(visitor.mNumMissed,0);

	}
	void CreateGarbageAndSplat(int num){
		Game game;
		game.SetLevel(num);
		auto level = game.GetLevel();

		ASSERT_FALSE(level == nullptr);

		auto items = level->GetItems();

		auto images = game.GetImages();

		ASSERT_EQ(items.size(),13);
		ASSERT_EQ(images.size(),14);

		auto program = items[0];

		auto garbage = items[1];


		garbage->SetLocation(400,400);

		garbage->HitTest(400,400,false,nullptr);

		TestVisitor visitor;
		level->Accept(&visitor);

		ASSERT_EQ(visitor.mNumAlive,11);
		ASSERT_EQ(visitor.mNumDead,1);
		ASSERT_EQ(visitor.mNumOops,0);
		ASSERT_EQ(visitor.mNumMissed,0);

	}
	void CreateGarbageAndMiss(int num){
		Game game;
		game.SetLevel(num);
		auto level = game.GetLevel();

		ASSERT_FALSE(level == nullptr);

		auto items = level->GetItems();

		auto images = game.GetImages();

		ASSERT_EQ(items.size(),13);
		ASSERT_EQ(images.size(),14);

		auto program = items[0];

		ASSERT_EQ(program->GetX(),625);
		ASSERT_EQ(program->GetY(),500);

		auto garbage = items[1];

		garbage->SetLocation(625,500);

		garbage->Update(0.00001); ///> No HitTest so need to update based on location.


		TestVisitor visitor;
		level->Accept(&visitor);

		ASSERT_EQ(visitor.mNumAlive,11);
		ASSERT_EQ(visitor.mNumDead,0);
		ASSERT_EQ(visitor.mNumOops,0);
		ASSERT_EQ(visitor.mNumMissed,1);

	}
};

TEST_F(ScoreBoardTest,FeatureUpdate){
	CreateFeatureAndSplat(1);
	CreateGarbageAndSplat(1);
	CreateGarbageAndMiss(1);
}