/**
 * @file Level.cpp
 * @author Evan Stanislaw
 */

#include "pch.h"
#include "Level.h"
#include "Item.h"
#include "Game.h"
#include "GarbageBug.h"
#include "Feature.h"
#include "NullBug.h"
#include "RedundancyFly.h"
#include "BossBug.h"
#include "ItemVisitor.h"
#include "BugVisitor.h"
#include <memory>

using namespace std;

///Minimum position
const double MinNeg = -200;
///Maximum position
const double MaxPos = 200;
///Min number of redundancy fly bugs
const int MinSpawn = 3;
///Max number of redundancy fly bugs
const int MaxSpawn = 6;

/**
 * Constructor for the level
 * @param game
 * @param xmlDoc
 * @param images
 */
Level::Level(Game* game, const wxXmlDocument& xmlDoc, std::vector<std::shared_ptr<wxImage>> images)
{
    mGame = game;
    mImages = images;
    Load(xmlDoc);
    std::random_device rd;
    mRandom.seed(rd());
}

/**
 * Opens and reads the XML files for the levels
 * @param xmlDoc
 */
void Level::Load(const wxXmlDocument& xmlDoc)
{
    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    mLevelName = root->GetAttribute("level");
    // Traverse the children of the root
    // node of the XML document in memory!!!!

    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"program")
        {
			this->numPrograms+=1;
            XmlItem(child);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Level::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> base_item;
    shared_ptr<Item> item;

    base_item = make_shared<Program>(this, mImages);
    mItems.push_back(base_item);
    std::rotate(mItems.rbegin(), mItems.rbegin() + 1, mItems.rend());
    base_item->XmlLoad(node);

    auto child = node->GetChildren();

    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"bug")
        {
			this->numBugs += 1;

            // We have an item. What type?
            auto type = child->GetAttribute(L"type");
            if (type == L"garbage"){
                item = make_shared<GarbageBug>(this, base_item, mImages);
            }else if(type == L"null"){
                item = make_shared<NullBug>(this, base_item, mImages);
            }else if(type == L"redundancy"){
                item = make_shared<RedundancyFly>(this, base_item, mImages);
            }else if(type == L"boss"){
                item = make_shared<BossBug>(this, base_item, mImages);
            }
        }else if(name == L"feature"){
			this->numBugs += 1;
            item = make_shared<Feature>(this, base_item, mImages);
        }

        if (item != nullptr)
        {
            mItems.push_back(item);
            item->XmlLoad(child);
        }
    }
}

/**
 * Draw function for the level
 * @param graphics
 */
void Level::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    //check if it is playing or not
    if(mStartGame)
    {
        wxFont bigFont(wxSize(0, 105),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
        graphics->SetFont(bigFont, wxColour(255, 0, 10));

        double wid = 0;
        double hit = 0;

        graphics->GetTextExtent(L"Program Name", &wid, &hit);
        graphics->DrawText(mLevelName, wid/2, 325 + hit/2);
    }else if(mEndGame) {
        wxFont bigFont(wxSize(0, 105),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
        graphics->SetFont(bigFont, wxColour(255, 0, 10));

        double wid = 0;
        double hit = 0;

        graphics->GetTextExtent(L"End Game", &wid, &hit);
        graphics->DrawText(L"Level Complete", wid/2, 325+hit/2);
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Level::Update(double elapsed)
{
    mLevelTime = mLevelTime + elapsed;
    //after a certain time change from start to playing to end
    if(mLevelTime >= 3)
    {
        mStartGame = false;
        mMainGame = true;
    }
    if (!mNewItems.empty())
    {
        mItems.insert(mItems.end(), mNewItems.begin(), mNewItems.end());
        mNewItems.clear();
    }
    for (auto item : mItems)
    {
        if(mMainGame){
            item->Update(elapsed);
        }
    }
    BugVisitor visitor;
    this->Accept(&visitor);
    if(visitor.GetNumAlive() == 0)
    {
        mMainGame = false;
        mEndGame = true;
        mEndTime = mEndTime + elapsed;

        //Change the level
        if(mEndTime > 2)
        {
            mEndGame = false;
            mChangeLevel = true;
        }
    }
}

/**
 * Test to see if an item was clicked on
 * @param x
 * @param y
 * @param double_clicked
 * @param w
 */
void Level::HitTest(double x, double y, bool double_clicked, wxWindow* w)
{
    if (mMainGame)
    {
        for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
        {
            if ((*i)->HitTest(x, y, double_clicked, w))
            {
                break;
            }
        }
    }
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */

void Level::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Add a bug to the level
 * @param program
 * @param x
 * @param y
 * @param speed
 */
void Level::AddSpawn(shared_ptr<Item> program, double x, double y, double speed)
{
    shared_ptr<Item> spawn;

    uniform_real_distribution<> spawn_distribution(MinSpawn, MaxSpawn);
    int NumSpawn = spawn_distribution(GetRandom());

    for (int i = 0; i<NumSpawn; i++)
    {
        uniform_real_distribution<> distributionX(MinNeg, MaxPos);
        double offsetX = distributionX(GetRandom());

        uniform_real_distribution<> distributionY(MinNeg, MaxPos);
        double offsetY = distributionX(GetRandom());

        spawn = make_shared<RedundancyFly>(this, program, mImages, true, x+offsetX, y+offsetY, speed);
        mNewItems.push_back(spawn);
    }
}
