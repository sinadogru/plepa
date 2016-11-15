#pragma once
 
#include <memory>
#include <utility>
 
#include <plepa/maybe.h>


namespace plepa {
 
/*!
    TODO: Can we specialize for lvalue references?
          So we can hold reference to objects in plepa::all.
*/

class all;

namespace implementation {
template<typename T>
auto all_cast(all*) -> T*;
} // namespace implementation

class all {
public:
    template<typename T>
    all(const T& x) noexcept : self_{new holder_impl<T>{x}} {}
 
    ~all() noexcept
    {
        delete self_;
    }

private:
    struct holder {
        virtual ~holder() = default;
        virtual holder* clone() const = 0;
    };
 
    template<typename T>
    struct holder_impl : holder { 
        holder_impl(const T& x) : data{x} {}
 
        holder_impl(T&& x) : data{std::move(x)} {}
 
        holder* clone() const
        {
            return new holder_impl{data};
        }
 
        T data;
    };
 
    holder* self_;
 
    template<typename T>
    friend auto implementation::all_cast(all*) -> T*;
};

namespace implementation {
template<typename T>
auto all_cast(all* x) -> T* {
    if (x && x->self_)
        if (auto impl = dynamic_cast<all::holder_impl<T>*>(x->self_))
            return &impl->data;
    return nullptr;
}
} // namespace implementation


template<typename T>
std::enable_if_t<!std::is_reference<T>::value, maybe<T>> all_cast(all& x)
{
    if (auto p = implementation::all_cast<T>(&x))
        return *p;
    return nothing;
}

template<typename T>
std::enable_if_t<std::is_lvalue_reference<T>::value, maybe<T&>> all_cast(all& x)
{
    if (auto p = implementation::all_cast<std::remove_reference_t<T>>(&x))
        return *p;
    return nothing;
}

} // namespace plepa
