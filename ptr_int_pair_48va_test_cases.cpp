#include "ptr_int_pair_48va_test.h"

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
    GIVEN("int bool pair 1") {
        int x = 1;
        ptr_int_pair_48va<int, bool> p{ &x, false };
        ptr_int_pair_48va<int, bool> q{ &x, true };

        CHECK(p < q);
    }

    GIVEN("int bool pair 2") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x + 1, true };

        CHECK(p < q);
    }

    GIVEN("int bool pair 3") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, false };
        ptr_int_pair_48va<int, bool> q{ x + 1, true };

        CHECK(p < q);
    }

    GIVEN("int bool pair 4") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x + 1, false };

        CHECK(p < q);
    }

    GIVEN("int bool pair 5") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x, true };
        ptr_int_pair_48va<int, bool> q{ x, false };

        CHECK_FALSE(p < q);
    }

    GIVEN("int bool pair 6") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x +1 , false };
        ptr_int_pair_48va<int, bool> q{ x, false };

        CHECK_FALSE(p < q);
    }

    GIVEN("int bool pair 6") {
        int x[2];
        ptr_int_pair_48va<int, bool> p{ x + 1 , true };
        ptr_int_pair_48va<int, bool> q{ x, false };

        CHECK_FALSE(p < q);
    }
}

//
// TODO: modifiers
//