/**
 * @file BossBug.h
 * @author mrazb
 *
 *
 */

#ifndef PROJECT1_BOSSBUG_H
#define PROJECT1_BOSSBUG_H

#include "Bug.h"

/**
 * Class for the Boss bug
 */
class BossBug : public Bug {
private:

    ///Starting health for the boss
    int mBossHealth = 10;

public:
    /// Assignment operator
    void operator=(const BossBug &) = delete;

    BossBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images);

    /**
     * Change the state of the boss bug
     * @param x int representing the health
     */
    void SetBugState (int x) override;

    /**
     * Draw function for the boss bug
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
};

#endif //PROJECT1_BOSSBUG_H
