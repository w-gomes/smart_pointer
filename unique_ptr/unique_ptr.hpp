#include <cassert>  // assert()
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace tre {

template <typename Type, typename Deleter = std::default_delete<Type>>
class unique_ptr {
 public:
  using element_type = Type;
  using deleter_type = Deleter;

  // constructors, move constructor and move assignment
  constexpr unique_ptr() noexcept = default;
  constexpr unique_ptr(std::nullptr_t nullptr_t) noexcept {
    this->object_ = nullptr_t;
  }

  explicit unique_ptr(Type *p) noexcept { this->object_ = p; }

  unique_ptr(unique_ptr &&other) noexcept {
    this->object_ = other.object_;
    other.object_ = nullptr;
  }

  unique_ptr &operator=(unique_ptr &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    unique_ptr temp(std::move(other));
    this->swap(temp);
    return *this;
  }

  // Copy and copy assignment are disabled.
  unique_ptr(const unique_ptr &other) = delete;
  unique_ptr &operator=(const unique_ptr &o) = delete;

  // destructor
  ~unique_ptr() { this->deleter(this->object_); }

  // Modifiers
  element_type *release() noexcept {
    // checks if unique_ptr holds any object.
    if (this->object_ == nullptr) {
      return nullptr;
    }

    element_type *temp = this->object_;
    this->object_      = nullptr;
    assert(this->object_ != temp);

    return temp;
  }

  void reset(element_type *new_object) noexcept {
    this->deleter(this->object_);
    this->object_ = new_object;
  }

  // swap
  constexpr void swap(unique_ptr &other) noexcept {
    using std::swap;
    swap(this->object_, other.object_);
  }

  // Observers...
  element_type *get() const noexcept {
    // is this test necessary...?
    return this->object_ == nullptr ? nullptr : this->object_;
  }

  // operators overload...
  element_type *operator->() const noexcept { return this->get(); }

  typename std::add_lvalue_reference_t<Type> operator*() const {
    if (this->object_ == nullptr)
      throw std::domain_error("Error: can't derefence a nullptr.../n");
    return *(this->get());
  }

  explicit operator bool() const noexcept {
    return this->object_ == nullptr ? false : true;
  }

 private:
  element_type *object_{nullptr};
  deleter_type deleter{};
};

// swap for template types
// add concept for is_move_constructible and is_swappable...
template <typename T>
void swap(unique_ptr<T> &lhs, unique_ptr<T> &rhs) {
  lhs.swap(rhs);
}

template <typename Type, typename... Args>
unique_ptr<Type> make_unique(Args &&... args) {
  return unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

}  // namespace tre
