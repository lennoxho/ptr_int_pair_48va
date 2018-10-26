#include "ptr_int_pair_48va_test.h"

#include <set>
#include <vector>

TEST_CASE("default constructed") {
    GIVEN("int bool pair") {
        constexpr ptr_int_pair_48va<int, bool> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == false);
    }

    GIVEN("int char pair") {
        constexpr ptr_int_pair_48va<int, char> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 0);
    }

    GIVEN("int short pair") {
        constexpr ptr_int_pair_48va<int, short> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 0);
    }

    GIVEN("int* bool pair") {
        constexpr ptr_int_pair_48va<int*, short> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 0);
    }

    GIVEN("const int bool pair") {
        constexpr ptr_int_pair_48va<const int, bool> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == false);
    }
    
    GIVEN("string bool pair") {
        constexpr ptr_int_pair_48va<std::string, bool> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == false);
    }
}

TEST_CASE("constructed with pointer") {
    GIVEN("int bool pair") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 1);
        CHECK(p.integer() == false);
    }

    GIVEN("int char pair") {
        int x = 2;
        ptr_int_pair_48va<int, char> p{ &x };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 2);
        CHECK(p.integer() == 0);
    }

    GIVEN("int short pair") {
        int x = 3;
        ptr_int_pair_48va<int, short> p{ &x };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 3);
        CHECK(p.integer() == 0);
    }

    GIVEN("int* bool pair") {
        int x = 4;
        int* x_ptr = &x;
        ptr_int_pair_48va<int*, short> p{ &x_ptr };

        CHECK(p.pointer() == &x_ptr);
        CHECK(**p.pointer() == 4);
        CHECK(p.integer() == 0);
    }

    GIVEN("const int bool pair") {
        const int x = 5;
        ptr_int_pair_48va<const int, bool> p{ &x };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 5);
        CHECK(p.integer() == false);
    }

    GIVEN("string bool pair") {
        std::string str = "foo";
        ptr_int_pair_48va<std::string, bool> p{ &str };

        CHECK(p.pointer() == &str);
        CHECK(*p.pointer() == "foo");
        CHECK(p.integer() == false);
    }
}

TEST_CASE("constructed with pointer and int") {
    GIVEN("int bool pair") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, true };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 1);
        CHECK(p.integer() == true);
    }

    GIVEN("int char pair") {
        int x = 2;
        ptr_int_pair_48va<int, char> p{ &x, 'z' };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 2);
        CHECK(p.integer() == 'z');
    }

    GIVEN("int short pair") {
        int x = 3;
        ptr_int_pair_48va<int, short> p{ &x, 256 };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 3);
        CHECK(p.integer() == 256);
    }

    GIVEN("int* bool pair") {
        int x = 4;
        int* x_ptr = &x;
        ptr_int_pair_48va<int*, short> p{ &x_ptr, 11 };

        CHECK(p.pointer() == &x_ptr);
        CHECK(**p.pointer() == 4);
        CHECK(p.integer() == 11);
    }

    GIVEN("const int bool pair") {
        const int x = 5;
        ptr_int_pair_48va<const int, bool> p{ &x, true };

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 5);
        CHECK(p.integer() == true);
    }

    GIVEN("string bool pair") {
        std::string str = "foo";
        ptr_int_pair_48va<std::string, bool> p{ &str, true };

        CHECK(p.pointer() == &str);
        CHECK(*p.pointer() == "foo");
        CHECK(p.integer() == true);
    }
}

TEST_CASE("pointer bit extension") {
    std::uintptr_t ptr_raw = ~(std::uintptr_t{0});
    char* ptr = reinterpret_cast<char*>(ptr_raw);
    
    SECTION("sanity check layout") {
        unsigned char* ptr_layout = reinterpret_cast<unsigned char*>(&ptr);
        REQUIRE(ptr_layout[0] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[1] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[2] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[3] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[4] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[5] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[6] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[7] == std::numeric_limits<std::uint8_t>::max());
    }
    
    ptr_int_pair_48va<char, short> p;
    REQUIRE(p.pointer() == nullptr);
    REQUIRE(p.integer() == 0);

    p.pointer(ptr);
    REQUIRE(p.pointer() == ptr);
    REQUIRE(p.integer() == 0);

    SECTION("sanity check layout with payload") {
        unsigned char* ptr_layout = reinterpret_cast<unsigned char*>(&p);
        REQUIRE(ptr_layout[0] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[1] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[2] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[3] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[4] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[5] == std::numeric_limits<std::uint8_t>::max());
        REQUIRE(ptr_layout[6] == 0);
        REQUIRE(ptr_layout[7] == 0);
    }

    p.integer(2);
    REQUIRE(p.pointer() == ptr);
    REQUIRE(p.integer() == 2);
}

TEST_CASE("copy constructed") {
    GIVEN("int bool pair") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, true };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 1);
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 1);
        CHECK(q.integer() == true);
    }

    GIVEN("int char pair") {
        int x = 2;
        ptr_int_pair_48va<int, char> p{ &x, 'z' };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 2);
        CHECK(p.integer() == 'z');

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 2);
        CHECK(q.integer() == 'z');
    }

    GIVEN("int short pair") {
        int x = 3;
        ptr_int_pair_48va<int, short> p{ &x, 256 };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 3);
        CHECK(p.integer() == 256);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 3);
        CHECK(q.integer() == 256);
    }

    GIVEN("int* bool pair") {
        int x = 4;
        int* x_ptr = &x;
        ptr_int_pair_48va<int*, short> p{ &x_ptr, 11 };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &x_ptr);
        CHECK(**p.pointer() == 4);
        CHECK(p.integer() == 11);

        CHECK(q.pointer() == &x_ptr);
        CHECK(**q.pointer() == 4);
        CHECK(q.integer() == 11);
    }

    GIVEN("const int bool pair") {
        const int x = 5;
        ptr_int_pair_48va<const int, bool> p{ &x, true };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 5);
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 5);
        CHECK(q.integer() == true);
    }

    GIVEN("string bool pair") {
        std::string str = "foo";
        ptr_int_pair_48va<std::string, bool> p{ &str, true };
        auto q{ p };

        CHECK(q == p);

        CHECK(p.pointer() == &str);
        CHECK(*p.pointer() == "foo");
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &str);
        CHECK(*q.pointer() == "foo");
        CHECK(q.integer() == true);
    }
}

TEST_CASE("assignment") {
    GIVEN("int bool pair") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, true };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 1);
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 1);
        CHECK(q.integer() == true);
    }

    GIVEN("int char pair") {
        int x = 2;
        ptr_int_pair_48va<int, char> p{ &x, 'z' };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 2);
        CHECK(p.integer() == 'z');

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 2);
        CHECK(q.integer() == 'z');
    }

    GIVEN("int short pair") {
        int x = 3;
        ptr_int_pair_48va<int, short> p{ &x, 256 };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 3);
        CHECK(p.integer() == 256);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 3);
        CHECK(q.integer() == 256);
    }

    GIVEN("int* bool pair") {
        int x = 4;
        int* x_ptr = &x;
        ptr_int_pair_48va<int*, short> p{ &x_ptr, 11 };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &x_ptr);
        CHECK(**p.pointer() == 4);
        CHECK(p.integer() == 11);

        CHECK(q.pointer() == &x_ptr);
        CHECK(**q.pointer() == 4);
        CHECK(q.integer() == 11);
    }

    GIVEN("const int bool pair") {
        const int x = 5;
        ptr_int_pair_48va<const int, bool> p{ &x, true };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 5);
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &x);
        CHECK(*q.pointer() == 5);
        CHECK(q.integer() == true);
    }

    GIVEN("string bool pair") {
        std::string str = "foo";
        ptr_int_pair_48va<std::string, bool> p{ &str, true };
        auto q = p;

        CHECK(q == p);

        CHECK(p.pointer() == &str);
        CHECK(*p.pointer() == "foo");
        CHECK(p.integer() == true);

        CHECK(q.pointer() == &str);
        CHECK(*q.pointer() == "foo");
        CHECK(q.integer() == true);
    }
}

TEST_CASE("inequality") {
    GIVEN("int bool pair") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, true };
        ptr_int_pair_48va<int, bool> q;

        CHECK(p != q);
    }

    GIVEN("int char pair") {
        int x = 2;
        ptr_int_pair_48va<int, char> p{ &x, 'z' };
        ptr_int_pair_48va<int, char> q;

        CHECK(p != q);
    }

    GIVEN("int short pair") {
        int x = 3;
        ptr_int_pair_48va<int, short> p{ &x, 256 };
        ptr_int_pair_48va<int, short> q;

        CHECK(p != q);
    }

    GIVEN("int* bool pair") {
        int x = 4;
        int* x_ptr = &x;
        ptr_int_pair_48va<int*, short> p{ &x_ptr, 11 };
        ptr_int_pair_48va<int*, short> q;

        CHECK(p != q);
    }

    GIVEN("const int bool pair") {
        const int x = 5;
        ptr_int_pair_48va<const int, bool> p{ &x, true };
        ptr_int_pair_48va<const int, bool> q;

        CHECK(p != q);
    }

    GIVEN("string bool pair") {
        std::string str = "foo";
        ptr_int_pair_48va<std::string, bool> p{ &str, true };
        ptr_int_pair_48va<std::string, bool> q;

        CHECK(p != q);
    }
}

TEST_CASE("less than") {
    using namespace use_ptr_int_pair_48va_logical_lt;

    GIVEN("int bool pair 1") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, false };
        ptr_int_pair_48va<int, bool> q{ &x, true };

        // Need to do this because CHECK will delegate the comparison 
        // to a function that is out of the current namespace scope.
        bool lt = p < q;
        CHECK(lt);
    }

    GIVEN("int bool pair 2") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x + 1, true };

        bool lt = p < q;
        CHECK(lt);
    }

    GIVEN("int bool pair 3") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, false };
        ptr_int_pair_48va<int, bool> q{ x + 1, true };

        bool lt = p < q;
        CHECK(lt);
    }

    GIVEN("int bool pair 4") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x + 1, false };

        bool lt = p < q;
        CHECK(lt);
    }

    GIVEN("int bool pair 5") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x, false };

        bool lt = p < q;
        CHECK_FALSE(lt);
    }

    GIVEN("int bool pair 6") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x +1 , false };
        ptr_int_pair_48va<int, bool> q{ x, false };

        bool lt = p < q;
        CHECK_FALSE(lt);
    }

    GIVEN("int bool pair 6") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x + 1 , true };
        ptr_int_pair_48va<int, bool> q{ x, false };

        bool lt = p < q;
        CHECK_FALSE(lt);
    }
}

//
// TODO: modifiers
//

TEST_CASE("modifiers") {
    GIVEN("int bool pair") {
        ptr_int_pair_48va<int, bool> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == false);

        int x = 77;
        p.pointer(&x);
        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 77);

        p.integer(true);
        CHECK(p.pointer() == &x);
        CHECK(*p.pointer() == 77);
        CHECK(p.integer() == true);

        int y = 200;
        p.pointer(&y);
        CHECK(p.pointer() == &y);
        CHECK(*p.pointer() == 200);
        CHECK(p.integer() == true);
    }

    GIVEN("string short pair") {
        ptr_int_pair_48va<std::string, short> p;

        CHECK(p.pointer() == nullptr);
        CHECK(p.integer() == 0);

        std::string str_1 = "honey";
        p.pointer(&str_1);
        CHECK(p.pointer() == &str_1);
        CHECK(*p.pointer() == str_1);

        p.integer(std::numeric_limits<short>::max());
        CHECK(p.pointer() == &str_1);
        CHECK(*p.pointer() == str_1);
        CHECK(p.integer() == std::numeric_limits<short>::max());

        std::string str_2 = "booboo";
        p.pointer(&str_2);
        CHECK(p.pointer() == &str_2);
        CHECK(*p.pointer() == str_2);
        CHECK(p.integer() == std::numeric_limits<short>::max());

        p.integer(std::numeric_limits<short>::min());
        CHECK(p.pointer() == &str_2);
        CHECK(*p.pointer() == str_2);
        CHECK(p.integer() == std::numeric_limits<short>::min());
    }
}

//
// Containers
//

// Big buffer to make sure both high bit cases are addressed.

TEST_CASE("containers") {
    GIVEN("vector") {
        std::vector<ptr_int_pair_48va<int, short>> vec;
        REQUIRE(vec.empty());

        const std::size_t initial_size = 4;
        vec.resize(initial_size);
        CHECK(std::all_of(vec.begin(), vec.end(), 
              [](const auto &p) { return p.integer() == 0 && p.pointer() == nullptr; }));

        int x;
        short y = 45;
        for (auto &p : vec) {
            p.pointer(&x);
            p.integer(45);
        }

        CHECK(std::all_of(vec.begin(), vec.end(),
              [&](const auto &p) { return p.integer() == y && p.pointer() == &x; }));

        auto vec_addr_before = vec.data();
        vec.resize(vec.capacity() + 1);
        REQUIRE(vec.data() != vec_addr_before);

        CHECK(std::all_of(vec.begin(), vec.begin() + initial_size,
              [&](const auto &p) { return p.integer() == y && p.pointer() == &x; }));

        CHECK(std::all_of(vec.begin() + initial_size, vec.end(),
              [](const auto &p) { return p.integer() == 0 && p.pointer() == nullptr; }));

        WHEN("copy") {
            auto vec_copy = vec;
            REQUIRE(vec_copy.data() != vec.data());
            CHECK(vec_copy == vec);

            WHEN("move") {
                auto vec_addr_before = vec.data();
                auto vec_move{ std::move(vec) };
                REQUIRE(vec.empty());
                REQUIRE(vec_move.data() == vec_addr_before);

                CHECK(std::all_of(vec_move.begin(), vec_move.begin() + initial_size,
                      [&](const auto &p) { return p.integer() == y && p.pointer() == &x; }));

                CHECK(std::all_of(vec_move.begin() + initial_size, vec_move.end(),
                      [](const auto &p) { return p.integer() == 0 && p.pointer() == nullptr; }));
            }
        }
    }

    GIVEN("set") {
        WHEN("logical comparators") {
            std::set<ptr_int_pair_48va<int, short>, ptr_int_pair_48va<int, short>::logical_comparator> s;
            REQUIRE(s.empty());

            CHECK(s.emplace().second);
            REQUIRE(s.size() == 1);
            CHECK(s.begin()->pointer() == nullptr);
            CHECK(s.begin()->integer() == 0);

            CHECK(!s.emplace().second);
            REQUIRE(s.size() == 1);

            int x[2];
            CHECK(s.emplace(x + 1).second);
            REQUIRE(s.size() == 2);

            auto iter = s.find(ptr_int_pair_48va<int, short>{ x + 1 });
            REQUIRE(iter != s.end());
            CHECK(iter->pointer() == x + 1);
            CHECK(iter->integer() == 0);

            CHECK(s.emplace(x, 42).second);
            REQUIRE(s.size() == 3);

            iter = s.find(ptr_int_pair_48va<int, short>{ x, 42 });
            REQUIRE(iter != s.end());
            CHECK(iter->pointer() == x);
            CHECK(iter->integer() == 42);

            std::vector<ptr_int_pair_48va<int, short>> expected = { ptr_int_pair_48va<int, short>{},
                                                                    ptr_int_pair_48va<int, short>{ x, 42 },
                                                                    ptr_int_pair_48va<int, short>{ x + 1 } };
            CHECK(std::equal(s.begin(), s.end(), expected.begin()));
        }

        WHEN("opaque comparators ") {
            std::set<ptr_int_pair_48va<int, short>, ptr_int_pair_48va<int, short>::opaque_comparator> s;
            REQUIRE(s.empty());

            CHECK(s.emplace().second);
            REQUIRE(s.size() == 1);
            CHECK(s.begin()->pointer() == nullptr);
            CHECK(s.begin()->integer() == 0);

            CHECK(!s.emplace().second);
            REQUIRE(s.size() == 1);

            int x[2];
            CHECK(s.emplace(x + 1).second);
            REQUIRE(s.size() == 2);

            auto iter = s.find(ptr_int_pair_48va<int, short>{ x + 1 });
            REQUIRE(iter != s.end());
            CHECK(iter->pointer() == x + 1);
            CHECK(iter->integer() == 0);

            CHECK(s.emplace(x, 42).second);
            REQUIRE(s.size() == 3);

            iter = s.find(ptr_int_pair_48va<int, short>{ x, 42 });
            REQUIRE(iter != s.end());
            CHECK(iter->pointer() == x);
            CHECK(iter->integer() == 42);

            std::vector<ptr_int_pair_48va<int, short>> expected = { ptr_int_pair_48va<int, short>{},
                                                                    ptr_int_pair_48va<int, short>{ x + 1 },
                                                                    ptr_int_pair_48va<int, short>{ x, 42 } };
            CHECK(std::equal(s.begin(), s.end(), expected.begin()));
        }
    }
}