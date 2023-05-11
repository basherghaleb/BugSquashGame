/**
 * @file ItemVisitor.h
 * @author mrazb
 *
 *
 */

#ifndef PROJECT1_ITEMVISITOR_H
#define PROJECT1_ITEMVISITOR_H

class Bug;
class Program;

/**
 * Class for the item visitor
 */
class ItemVisitor {
protected:
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit each of the bugs
     * @param bug
     */
    virtual void VisitBug(Bug* bug) {}

    /**
     * Visit each of the programs
     * @param program
     */
    virtual void VisitProgram(Program* program) {}

};

#endif //PROJECT1_ITEMVISITOR_H
