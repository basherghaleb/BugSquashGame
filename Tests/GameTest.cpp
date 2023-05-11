/**
 * @file GameTest.cpp
 * @author Evan Stanislaw
 * used to test functionalities of the game
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

using namespace std;

/// Level 0 file
const std::wstring level0 = L"data/level0.xml";

/// Level 1 file
const std::wstring level1 = L"data/level1.xml";

/// Level 2 file
const std::wstring level2 = L"data/level2.xml";

/// Level 3 file
const std::wstring level3 = L"data/level3.xml";

class GameTest : public ::testing::Test
{
protected:

	/**
	* Read a file into a wstring and return it.
	* @param filename Name of the file to read
	* @return File contents
	*/
	wstring ReadFile(const wxString &filename)
	{
		ifstream t(filename.ToStdString());
		wstring str((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

		return str;
	}

    void TestGame(wxString filename)
    {
        auto xml = ReadFile(filename);
        cout << xml << endl;
    }

};

//TEST_F(GameTest, Construct)
//{
//	Game game;
//}
//
//TEST_F(GameTest, SimpleLoad)
//{
//
//}


