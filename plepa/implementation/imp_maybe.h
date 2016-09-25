#pragma once

#include <type_traits>


namespace plepa {

namespace implementation {

template<typename T>
class maybe_storage {

public:
	auto address() 		{ return (void*)&data_; }
	auto address() const { return (void*)&data_; }

	auto type_address() { return reinterpret_cast<T*>(address()); }
	auto type_address() const { return reinterpret_cast<const T*>(address()); }

	std::aligned_storage_t<sizeof(T)> data_;
};

} // namespace implementation

} // namespace plepa