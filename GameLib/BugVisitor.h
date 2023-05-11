/**
 * @file BugVisitor.h
 * @author mrazb
 *
 *
 */

#ifndef PROJECT1_BUGVISITOR_H
#define PROJECT1_BUGVISITOR_H

#include "ItemVisitor.h"
#include "Bug.h"

/**
 * Class for the bug visitor
 */
class BugVisitor : public ItemVisitor {
private:
    /// Alive counter
    int mNumAlive = 0;

    /// Missed counter
    int mNumMissed = 0;

    /// Oops counter
    int mNumOops = 0;

    /// Dead counter
    int mNumDead = 0;
public:
    /**
     * Get the number of Alive
     * @return Number of Alive
     */
    int GetNumAlive() const { return mNumAlive; }

    /**
     * Get the number of Missed
     * @return Number of Missed
     */
    int GetmNumMissed() const { return mNumMissed; }

    /**
     * Get the number of Oops
     * @return Number of Oops
     */
    int GetNumOops() const { return mNumOops; }

    /**
     * Get the number of Dead
     * @return Number of Dead
     */
    int GetNumDead() const { return mNumDead; }

    void VisitBug(Bug* bug);
};

#endif //PROJECT1_BUGVISITOR_H
