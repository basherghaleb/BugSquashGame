/**
 * @file GarbageBug.h
 * @author Jared Bloch
 *
 * Garbage Bug Class
 */

#ifndef PROJECT1_GAMELIB_GARBAGEBUG_H
#define PROJECT1_GAMELIB_GARBAGEBUG_H

#include "Bug.h"

/**
 * Garbage Bug Class
 */
class GarbageBug : public Bug {
private:

public:
    /// Assignment operator
    void operator=(const GarbageBug &) = delete;

    GarbageBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images);
};

#endif //PROJECT1_GAMELIB_GARBAGEBUG_H
