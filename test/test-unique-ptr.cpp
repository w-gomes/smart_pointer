#include <utility>

#include "catch2/catch.hpp"
#include "unique_ptr.hpp"

TEST_CASE("creating unique_ptr with no value") {
  tre::unique_ptr<int> ptr;
  REQUIRE(ptr.get() == nullptr);
}

TEST_CASE("creating unique_ptr with value") {
  SECTION("nullptr constructor") {
    tre::unique_ptr<int> ptr(nullptr);
    REQUIRE(ptr.get() == nullptr);
  }

  SECTION("pointer constructor") {
    tre::unique_ptr<int> ptr1(new int(42));
    REQUIRE(*(ptr1.get()) == 42);
    REQUIRE(*ptr1 == 42);

    int *x = new int(42);
    tre::unique_ptr<int> ptr2(x);
    REQUIRE(*(ptr2.get()) == 42);
    REQUIRE(*ptr2 == 42);
  }

  SECTION("using make_unique") {
    tre::unique_ptr<int> ptr = tre::make_unique<int>(42);
    REQUIRE(*(ptr.get()) == 42);
    REQUIRE(*ptr == 42);

    auto ptr2 = tre::make_unique<int>(42);
    REQUIRE(*(ptr2.get()) == 42);
    REQUIRE(*ptr2 == 42);
  }
}

TEST_CASE("Moving unique_ptr") {
  SECTION("Move constructor") {
    auto ptr1 = tre::make_unique<int>(42);
    tre::unique_ptr<int> ptr2(std::move(ptr1));

    REQUIRE(ptr1.get() == nullptr);
    REQUIRE(*ptr2 == 42);
  }

  SECTION("Move assignment") {
    auto ptr1 = tre::make_unique<int>(42);
    tre::unique_ptr<int> ptr2;
    ptr2 = std::move(ptr1);

    REQUIRE(ptr1.get() == nullptr);
    REQUIRE(*ptr2 == 42);
  }
}

TEST_CASE("getting a pointer to owned object using get()") {
  auto ptr      = tre::make_unique<int>(42);
  auto *raw_ptr = ptr.get();

  REQUIRE(*raw_ptr == *ptr);
}

TEST_CASE("releasing owned object with release()") {
  auto ptr        = tre::make_unique<int>(42);
  auto *new_owner = ptr.release();

  REQUIRE(ptr.get() == nullptr);
  REQUIRE(new_owner != nullptr);
  REQUIRE(*new_owner == 42);
}

TEST_CASE("change the owned value of a unique_ptr object with reset()") {
  SECTION("replace a unique_ptr with another value") {
    auto ptr      = tre::make_unique<int>(42);
    auto *raw_ptr = new int(27);
    ptr.reset(raw_ptr);

    REQUIRE(*ptr == 27);
  }

  SECTION("Resets a unique_ptr") {
    auto ptr = tre::make_unique<int>(42);
    ptr.reset(nullptr);
    REQUIRE(ptr.get() == nullptr);
  }
}
