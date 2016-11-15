#pragma once
 
#include <memory>
#include <utility>
 
#include <plepa/maybe.h>


namespace plepa {
 
/*!
    TODO: Can we specialize for lvalue references?
          So we can hold reference to objects in plepa::all.
*/

class unkown;

namespace implementation {
template<typename T>
auto unknown_cast(unkown*) -> T*;
} // namespace implementation

class unkown {
public:
    template<typename T>
    unkown(const T& x) noexcept : self_{new content_holder<T>{x}} {}
 
    ~unkown() noexcept
    {
        delete self_;
    }

private:
    struct holder {
        virtual ~holder() = default;
        virtual holder* clone() const = 0;
    };
 
    template<typename T>
    struct content_holder : holder {
        content_holder(const T& x) : content{x} {}
 
        content_holder(T&& x) : content{std::move(x)} {}
 
        holder* clone() const
        {
            return new content_holder{content};
        }
 
        T content;
    };
 
    holder* self_;
 
    template<typename T>
    friend auto implementation::unknown_cast(unkown*) -> T*;
};

namespace implementation {
template<typename T>
auto unknown_cast(unkown* x) -> T* {
    if (x && x->self_)
        if (auto holder = dynamic_cast<unkown::content_holder<T>*>(x->self_))
            return &holder->content;
    return nullptr;
}
} // namespace implementation


template<typename T>
std::enable_if_t<!std::is_reference<T>::value, maybe<T>> unknown_cast(unkown& x)
{
    if (auto p = implementation::unknown_cast<T>(&x))
        return *p;
    return nothing;
}

template<typename T>
std::enable_if_t<std::is_lvalue_reference<T>::value, maybe<T&>> unknown_cast(unkown& x)
{
    if (auto p = implementation::unknown_cast<std::remove_reference_t<T>>(&x))
        return *p;
    return nothing;
}

} // namespace plepa
