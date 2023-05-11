/**
 * @file BugVisitor.cpp
 * @author mrazb
 */
#include "pch.h"
#include "BugVisitor.h"

/**
 * Visit the bugs in the level
 * @param bug
 */
void BugVisitor::VisitBug(Bug* bug)
{
    int state = bug->GetBugState();
    if (state == 0) {
        mNumAlive++;
    } else if (state == 1) {
        mNumDead++;
    } else if (state == 2) {
        mNumMissed++;
    } else if (state == 3) {
        mNumOops++;
    }
}
