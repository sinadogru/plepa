#pragma once


namespace plepa {

class all;

namespace implementation {

template<typename T>
auto all_cast(all* x) -> T* {
	if (x && x->self_)
		if (auto impl = dynamic_cast<all::holder_impl<T>*>(x->self_))
			return &impl->data;
	return nullptr;
}

} // namespace implementation

} // namespace plepa
