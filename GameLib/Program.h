/**
 * @file Program.h
 * @author Evan Stanislaw
 *
 *
 */



#ifndef PROJECT1_PROGRAM_H
#define PROJECT1_PROGRAM_H

#include "Item.h"

/**
 * Class for the program
 */
class Program : public Item
{
private:
    ///Name of the program
    std::wstring mName;

    /// The underlying image
    std::shared_ptr<wxImage> mProgramImage;

    /// The bitmap we can display
    wxGraphicsBitmap mProgramBitmap;

public:
	Program(Level* level, std::vector<std::shared_ptr<wxImage>> images);

    ~Program();

    /// Default constructor (disabled)
    Program() = delete;

    /// Copy constructor (disabled)
    Program(const Program &) = delete;

    /// Assignment operator
    void operator=(const Program &) = delete;

    void XmlLoad(wxXmlNode *node) override;

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Accepting the item visitor
     * @param visitor
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitProgram(this); }
};

#endif //PROJECT1_PROGRAM_H
