#include <cassert>
#include <iostream>

#include <plepa/implementation/imp_maybe.h>


namespace plepa {

class nothing_t {};
nothing_t nothing;
 
class just_t {};
just_t just;
 
template<typename T>
class maybe {
public:
    maybe() : empty_{true} {}
    maybe(const nothing_t&) : empty_{true} {}
 
    maybe(const T& x) : empty_{false} 
    { construct(x); }
    maybe(T&& x) : empty_{false} 
    { construct(std::move(x)); }
 
    explicit operator bool () const {
        return !empty();
    }
 
    T& operator*() { assert(!empty()); return ref(); }
    const T& operator*() const { assert(!empty()); return ref(); }
 
private:
    void construct(const T& x) {
        ::new (ptr()) T{x};
    }
    void construct(T&& x) {
        ::new (ptr()) T{std::move(x)};
    }
 
    bool empty() const { return empty_; }
 
    auto ptr() { return object_.type_address(); }
    auto ptr() const { return object_.type_address(); }
    auto& ref() { return *ptr(); }
    auto& ref() const { return *ptr(); }
 
    implementation::maybe_storage<T> object_;
    bool empty_;
};

template<typename T>
class maybe<T&> {
public:
    maybe() : object_{nullptr} {}
    maybe(const nothing_t&) : object_{nullptr} {}
 
    maybe(T& x) noexcept : object_{std::addressof(x)} {}
    maybe(T&& x) = delete;
 
    explicit operator bool () const {
        return !empty();
    }
 
    T& operator*() { assert(!empty()); return ref(); }
    const T& operator*() const { assert(!empty()); return ref(); }
 
private:
    bool empty() const { return !object_; }
 
    auto ptr() { return object_; }
    auto ptr() const { return object_; }
    auto& ref() { return *ptr(); }
    auto& ref() const { return *ptr(); }
 
    T* object_;
};
 
template<typename T>
bool operator==(const maybe<T>& m, const nothing_t&) {
    return !(bool)m;
}
 
template<typename T>
bool operator==(const maybe<T>& m, const just_t&) {
    return !(m == nothing);
}

} // namespace plepa

 
