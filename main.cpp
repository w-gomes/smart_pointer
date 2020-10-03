#include <fmt/format.h>

#include "unique_ptr/unique_ptr.hpp"

struct ok {
  ok() { fmt::print("ok() default constructor.\n"); }
  ok(int v) : value(v) { fmt::print("ok(int) constructor.\n"); }
  ok(const ok &o) {
    fmt::print("ok(const ok &) copy constructor.\n");
    this->value = o.value;
  }
  ok &operator=(const ok &o) {
    fmt::print("ok(const ok &) copy assignment.\n");
    if (this == &o) return *this;
    this->value = o.value;
    return *this;
  }

  ok(ok &&o) noexcept {
    fmt::print("ok(ok &&) move constructor.\n");
    this->value = o.value;
  }
  ok &operator=(ok &&o) noexcept {
    fmt::print("ok(ok &&) move assignment.\n");
    if (this == &o) return *this;
    this->value = o.value;
    return *this;
  }

  int get_ok() const { return this->value; }

  ~ok() { fmt::print("~ok() destructor.\n"); }
  int value{};
};

int main() {
  tre::unique_ptr<ok> o = tre::make_unique<ok>(10);
  fmt::print("operator-> {}\n", o->get_ok());

  tre::unique_ptr<int> p(new int(10));
  int *ptr_p = p.get();
  fmt::print("ptr_p has {}.\n", *ptr_p);
  tre::unique_ptr<int> n(nullptr);
  tre::unique_ptr<int> m = std::move(p);
  int *ptr_test          = m.get();
  fmt::print("ptr_test has {}.\n", *ptr_test);

  tre::unique_ptr<int> null_ptr(nullptr);
  if (!null_ptr) {
    fmt::print("it's nullptr\n");
  }

  auto f_ptr = tre::make_unique<float>(10.0);
  if (f_ptr) fmt::print("f_ptr holds {}\n", *f_ptr);
  *f_ptr = 27.7;
  fmt::print("f_ptr holds {} now\n", *f_ptr);

  auto try_copy = tre::make_unique<char>('a');
  // the following won't work.
  // tre::unique_ptr<char> try_copy2 = try_copy;

  // the following won't work either.
  // tre::unique_ptr<char> try_assign;
  // try_assign = try_copy;

  // but move works.
  tre::unique_ptr<char> try_move = std::move(try_copy);
  tre::unique_ptr<char> try_move_assign;
  try_move_assign = std::move(try_move);

  // release
  auto released_ptr = tre::make_unique<int>(100);
  int *i_ptr        = released_ptr.release();

  assert(released_ptr.get() == nullptr);
  // why this isn't working?
  // assert(released_ptr == nullptr);

  return 0;
}

