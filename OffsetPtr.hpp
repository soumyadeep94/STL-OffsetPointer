#pragma once
#include <atomic>
#include <cstddef>

template <typename T>
class OffsetPtr
{
private:
	std::atomic<std::ptrdiff_t> m_Offset;  //Offset from the base address
	static constexpr std::ptrdiff_t NULL_OFFSET = -1;  //Special value to indicate nullptr
public:
	OffsetPtr() noexcept : m_Offset(NULL_OFFSET){}
	OffsetPtr(T* base, T* ptr) noexcept {
		set(base, ptr);
	}

	OffsetPtr(const OffsetPtr& other) noexcept : m_Offset(other.m_Offset.load()) {}
	OffsetPtr(OffsetPtr&& other) noexcept : m_Offset(other.m_Offset.exchange(NULL_OFFSET)){}

	OffsetPtr& operator=(const OffsetPtr& other) noexcept {
		if (this != &other)
			m_Offset.store(other.m_Offset.load());
		return *this;
	}

	OffsetPtr& operator=(OffsetPtr&& other) noexcept {
		if (this != &other)
			m_Offset.store(other.m_Offset.exchange(NULL_OFFSET));
	}

	//Set the offset relative to the base pointer
	void set(T* base, T* ptr) noexcept {
		if (ptr == nullptr)
			m_Offset.store(NULL_OFFSET);
		else
			m_Offset.store(ptr - base);
	}

	//get the actual pointer
	T* get(T* base) const noexcept {
		auto off = m_Offset.load();
		if (off == NULL_OFFSET)
			return nullptr;
		return base + off;
	}

	//Conversion to bool
	explicit operator bool() const noexcept {
		return m_Offset.load() != NULL_OFFSET;
	}

	bool operator==(const OffsetPtr& other) const noexcept {
		return m_Offset.load() == other.m_Offset.load();
	}

	bool operator!=(const OffsetPtr& other) const noexcept {
		return !(*this == other);
	}
};