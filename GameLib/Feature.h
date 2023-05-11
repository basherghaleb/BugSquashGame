/**
 * @file Feature.h
 * @author Jared Bloch
 *
 * Feature Class
 */

#ifndef PROJECT1_GAMELIB_FEATURE_H
#define PROJECT1_GAMELIB_FEATURE_H

#include "Bug.h"

/**
 * Feature Class
 */
class Feature : public Bug {
private:

public:
    /// Default constructor (disabled)
    Feature() = delete;

    /// Copy constructor (disabled)
    Feature(const Feature &) = delete;

    /// Assignment operator
    void operator=(const Feature &) = delete;

    Feature(Level* level, std::shared_ptr<Item> program, std::vector<std::shared_ptr<wxImage>> images);

    void SetBugState(int x) override;
};

#endif //PROJECT1_GAMELIB_FEATURE_H
