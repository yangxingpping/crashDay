#include "SomeClass.h"
#include "asio.hpp"

using std::make_shared;
using std::move;

//------------------------------------------------------------------------------
SomeClass::SomeClass() {}
//------------------------------------------------------------------------------
SomeClass::~SomeClass() {}
//------------------------------------------------------------------------------
void SomeClass::set(int x)
{
    this->mVal = x;
}

void SomeClass::normalCrash() 
{ 
    auto a = mParent->_a;

}

void SomeClass::coroCrash() 
{ 

    asio::io_context ioc;
    asio::co_spawn(
        ioc,
        [this]() -> asio::awaitable<void>
        { 
            /*auto [s, r] = oneshot::create<void>();
            _hh = make_shared<oneshot::sender<void>>(move(s));*/
            co_await _ii->async_wait(asio::deferred);
            co_return;
        },
        asio::detached);
    ioc.run();
}

//------------------------------------------------------------------------------
int SomeClass::get()
{
    return this->mVal;
}
//------------------------------------------------------------------------------

#ifdef UNIT_TESTS
#include "catch.hpp"

TEST_CASE("SomeClass set and get")
{
    SomeClass some;
    some.set(5);
    REQUIRE(some.get() == 5);
    REQUIRE(some.get() != 2);
}

#endif
