#include "project.h"

#include <chrono>
#include <filesystem>
#include <iostream>

#include <string>
#include <list>
#include <memory>
#include <stack>
#include <map>


namespace e {

using namespace std;

struct r {
    explicit r(string_view c)
        : command{c} {}
    r(string_view c, list<shared_ptr<r>>&& d)
        : command{c}, dependencies{move(d)} {}

    string command;
    list<shared_ptr<r>> dependencies;
    size_t dependants{0};
};

struct p {
    list<shared_ptr<r>> rules;

    void build()
    {
    }
};

auto spr(string_view c, list<shared_ptr<r>>&& d)
{
    return make_shared<r>(c, move(d));
}

void test()
{
    auto _r4 = spr("r4", {});
    auto _r3 = spr("r3", {});
    auto _r2 = spr("r2", {_r4});
    auto _r1 = spr("r1", {_r2, _r3});
    auto _r0 = spr("r0", {_r2});

    p _p; _p.rules = {_r0, _r1, _r2, _r3, _r4};
    _p.build();
}

} // namespace e


int main()
{
    try {
        mike::project p0{ "tests/a.mike.json" };
    }
    catch( const std::exception& e ) {
        std::cerr << e.what() << '\n';
    }
}
