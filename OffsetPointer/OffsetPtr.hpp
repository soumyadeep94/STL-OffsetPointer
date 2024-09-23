#pragma once
#include <atomic>
#include <cstddef>

template <typename T>
class OffsetPtr
{
private:
	std::atomic<std::ptrdiff_t> offset;
	static constexpr std::ptrdiff_t NULL_OFFSET = -1;
public:
	OffsetPtr() noexcept : offset(NULL_OFFSET){}
	OffsetPtr(T* base, T* ptr) noexcept {
		set(base, ptr);
	}

	OffsetPtr(const OffsetPtr& other) noexcept : offset(other.offset.load()) {}
	OffsetPtr(OffsetPtr&& other) noexcept : offset(other.offset.exchange(NULL_OFFSET)){}

	OffsetPtr& operator=(const OffsetPtr& other) noexcept {
		if (this != &other)
			offset.store(other.offset.load());
		return *this;
	}

	OffsetPtr& operator=(OffsetPtr&& other) noexcept {
		if (this != &other)
			offset.store(other.offset.exchange(NULL_OFFSET));
	}

	void set(T* base, T* ptr) noexcept {
		if (ptr == nullptr)
			offset.store(NULL_OFFSET);
		else
			offset.store(ptr - base);
	}

	T* get(T* base) const noexcept {
		auto off = offset.load();
		if (off == NULL_OFFSET)
			return nullptr;
		return base + off;
	}

	explicit operator bool() const noexcept {
		return offset.load() != NULL_OFFSET;
	}

	bool operator==(const OffsetPtr& other) const noexcept {
		return offset.load() == other.offset.load();
	}

	bool operator!=(const OffsetPtr& other) const noexcept {
		return !(*this == other);
	}
};