/**
 * @file ItemTest.cpp
 * @author Evan Stanislaw
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <Bug.h>
#include <Level.h>



TEST(ItemTest, Construct) {
    Game game;

}

TEST(ItemTest, Getters){
    Game game;
    game.SetLevel(1);
    auto level = game.GetLevel();

    ASSERT_FALSE(level == nullptr);

    auto items = level->GetItems();

    auto images = game.GetImages();

    Item *item(reinterpret_cast<Item*>(level.get()));


    // Test initial values
    ASSERT_NEAR(0, item->GetX(), 0.0001);
    ASSERT_NEAR(0, item->GetY(), 0.0001);


}

