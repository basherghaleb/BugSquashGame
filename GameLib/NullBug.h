/**
 * @file NullBug.h
 * @author Jared Bloch
 *
 * Null Bug Class
 */

#ifndef PROJECT1_GAMELIB_NULLBUG_H
#define PROJECT1_GAMELIB_NULLBUG_H

#include "Bug.h"

/**
 * Null Bug Class
 */
class NullBug : public Bug {
private:

public:
    /// Default constructor (disabled)
    NullBug() = delete;

    /// Copy constructor (disabled)
    NullBug(const NullBug &) = delete;

    /// Assignment operator
    void operator=(const NullBug &) = delete;

    NullBug(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images);
};

#endif //PROJECT1_GAMELIB_NULLBUG_H
