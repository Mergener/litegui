#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <deque>

#include "event.h"
using namespace litegui;

using IntEvent = CallableEvent<int>;

TEST_CASE("Event system basic functionality") {
    IntEvent ev;
    std::vector<int> results;

    auto ref1 = ev.add_handler([&](int x) { results.push_back(x + 1); });
    auto ref2 = ev.add_handler([&](int x) { results.push_back(x + 2); });

    ev.call(5);

    CHECK(results.size() == 2);
    CHECK(results[0] == 6); // 5 + 1
    CHECK(results[1] == 7); // 5 + 2
}

TEST_CASE("HandlerRef unregisters manually") {
    IntEvent ev;
    std::vector<int> results;

    auto ref = ev.add_handler([&](int x) { results.push_back(x); });

    ev.call(10);
    CHECK(results == std::vector<int>{10});

    ref.unregister();
    ev.call(20);
    CHECK(results == std::vector<int>{10}); // No change
}

TEST_CASE("ScopedHandlerRef unregisters automatically") {
    IntEvent ev;
    std::vector<int> results;

    {
        auto ref = ev.add_handler([&](int x) { results.push_back(x); });
        auto scoped = ref.scoped();

        ev.call(3);
        CHECK(results == std::vector<int>{3});
    }

    ev.call(4);
    CHECK(results == std::vector<int>{3}); // Scoped handler removed
}

TEST_CASE("HandlerRef::alive reflects registration state") {
    IntEvent ev;
    auto ref = ev.add_handler([](int) {});

    CHECK(ref.alive());
    ref.unregister();
    CHECK(!ref.alive());
}

TEST_CASE("Multiple ScopedHandlerRefs unregister correctly") {
    IntEvent ev;
    std::vector<int> values;

    {
        auto ref1 = ev.add_handler([&](int x) { values.push_back(x * 1); });
        auto scoped1 = ref1.scoped();

        auto ref2 = ev.add_handler([&](int x) { values.push_back(x * 2); });
        auto scoped2 = ref2.scoped();

        ev.call(2);
        CHECK(values == std::vector<int>{2, 4});
    }

    values.clear();
    ev.call(3);
    CHECK(values.empty()); // All handlers unregistered
}

TEST_CASE("Calling event with no handlers does nothing") {
    IntEvent ev;
    CHECK_NOTHROW(ev.call(42)); // Should not crash or throw
}

TEST_CASE("Calling unregister twice is safe") {
    IntEvent ev;
    auto ref = ev.add_handler([](int) {});
    ref.unregister();
    CHECK(!ref.alive());
    // Second call should be a no-op
    CHECK_NOTHROW(ref.unregister());
    CHECK(!ref.alive());
}

TEST_CASE("Handler execution order matches registration order") {
    IntEvent ev;
    std::vector<int> results;

    ev.add_handler([&](int x) { results.push_back(x + 1); });
    ev.add_handler([&](int x) { results.push_back(x + 2); });
    ev.add_handler([&](int x) { results.push_back(x + 3); });

    ev.call(1);
    CHECK(results == std::vector<int>{2, 3, 4});
}

TEST_CASE("Reusing HandlerRef after unregister has no effect") {
    IntEvent ev;
    std::vector<int> results;

    auto ref = ev.add_handler([&](int x) { results.push_back(x); });
    ref.unregister();
    CHECK(!ref.alive());

    ev.call(99);
    CHECK(results.empty());

    // Reassigning to a new handler
    ref = ev.add_handler([&](int x) { results.push_back(x * 2); });
    CHECK(ref.alive());

    ev.call(10);
    CHECK(results == std::vector<int>{20});
}

