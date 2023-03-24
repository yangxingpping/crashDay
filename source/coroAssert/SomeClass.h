#pragma once
#include <string>
#include <vector>

#include <memory>

#include "oneshot.hpp"

using std::shared_ptr;

/**
 * Empty BaseClass, just to show how it looks in doxygen.
 *
 *  Here is some graph:
 *
 *  \startuml
 *    Sender->Receiver  : Command()
 *    Sender<--Receiver : Ack()
 *  \enduml
 *
 *  How you like it?
 *
 */
class BaseClass
{
  public:
    BaseClass()
    {
        mPointer = new int(5);
    };

    ~BaseClass() {};
    void freePtr()
    {
        delete mPointer;
    };
    int* mPointer;
    
};

/**
 * Empty data class, just to show how it looks in doxygen.
 */
class Data
{
  public:
    Data() {};
    ~Data() {};
    int func()
    {
        int i = _a;
        return ++i;
    }
    int _a {0};
};

/**
 * SomeClass description. This is a test class ment to show
 * how to create, build, use and document classes from other files.
 *
 * \warning beware, this is how warning looks like.
 */
class SomeClass : public BaseClass
{
    int mVal {0}; ///< Stores the value
    std::vector<Data> mData;
    std::vector<std::string> mStrings;

  public:
    SomeClass(); ///< Creates empty SomeClass
    ~SomeClass();

    Data* mParent {nullptr};

    shared_ptr<oneshot::sender<void>> _hh {nullptr};
    shared_ptr<oneshot::receiver<void>> _ii {nullptr};

    /**
     * Sets the value
     * @param x input value
     */
    void set(int x);

    void normalCrash();

    void coroCrash();

    /**
     * get the value
     * @return current value
     */
    int get();
};
