/**
 * @file HitTest.cpp
 * @author Basher Ghaleb
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

//TEST(HitTest, HiTest)
//{
//	Game game;
//	Bug bug(&game);
//
//	bug.SetLocation(100, 200);
//}