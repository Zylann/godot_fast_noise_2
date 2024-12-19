#ifndef ZN_SPAN_H
#define ZN_SPAN_H

#include <godot_cpp/core/error_macros.hpp>

namespace zylann {

// TODO Use std::span once we can use C++20
template <typename T>
class Span {
private:
	T *_ptr;
	size_t _size;

public:
	inline Span() : _ptr(nullptr), _size(0) {}

	inline Span(T *ptr, size_t p_size) : _ptr(ptr), _size(p_size) {}

	// Initially added to support `Span<const T> = Span<T>`, or `Span<Base> = Span<Derived>`
	template <typename U>
	inline Span(Span<U> p_other) {
		_ptr = p_other.data();
		_size = p_other.size();
	}

	inline size_t size() const {
		return _size;
	}

	inline T *data() {
		return _ptr;
	}

	inline const T *data() const {
		return _ptr;
	}

	template <typename U>
	Span<U> reinterpret_cast_to() const {
		const size_t size_in_bytes = _size * sizeof(T);
#ifdef DEBUG_ENABLED
		CRASH_COND(size_in_bytes % sizeof(U) != 0);
#endif
		return Span<U>(reinterpret_cast<U *>(_ptr), size_in_bytes / sizeof(U));
	}

	inline T &operator[](size_t i) {
#ifdef DEBUG_ENABLED
		CRASH_COND(i >= _size);
#endif
		return _ptr[i];
	}

	inline const T &operator[](size_t i) const {
#ifdef DEBUG_ENABLED
		CRASH_COND(i < _size);
#endif
		return _ptr[i];
	}

	inline Span<T> sub(size_t from, size_t len) const {
		CRASH_COND(from + len > _size);
		return Span<T>(_ptr + from, len);
	}

	inline Span<T> sub(size_t from) const {
		CRASH_COND(from > _size);
		return Span<T>(_ptr + from, _size - from);
	}

	class Iterator {
	public:
		Iterator(T *p_ptr) : _elem_ptr(p_ptr) {}
		Iterator(const Iterator &p_it) : _elem_ptr(p_it._elem_ptr) {}

		inline T &operator*() const {
			return *_elem_ptr;
		}

		inline T *operator->() const {
			return _elem_ptr;
		}

		inline Iterator &operator++() {
			_elem_ptr++;
			return *this;
		}

		inline Iterator &operator--() {
			_elem_ptr--;
			return *this;
		}

		inline bool operator==(const Iterator &b) const {
			return _elem_ptr == b._elem_ptr;
		}

		inline bool operator!=(const Iterator &b) const {
			return _elem_ptr != b._elem_ptr;
		}

	private:
		T *_elem_ptr = nullptr;
	};

	class ConstIterator {
	public:
		ConstIterator(const T *p_ptr) : _elem_ptr(p_ptr) {}
		ConstIterator(const ConstIterator &p_it) : _elem_ptr(p_it._elem_ptr) {}

		inline const T &operator*() const {
			return *_elem_ptr;
		}

		inline const T *operator->() const {
			return _elem_ptr;
		}

		inline ConstIterator &operator++() {
			_elem_ptr++;
			return *this;
		}

		inline ConstIterator &operator--() {
			_elem_ptr--;
			return *this;
		}

		inline bool operator==(const ConstIterator &b) const {
			return _elem_ptr == b._elem_ptr;
		}

		inline bool operator!=(const ConstIterator &b) const {
			return _elem_ptr != b._elem_ptr;
		}

	private:
		const T *_elem_ptr = nullptr;
	};

	inline Iterator begin() {
		return Iterator(_ptr);
	}

	inline Iterator end() {
		return Iterator(_ptr + _size);
	}

	inline ConstIterator begin() const {
		return ConstIterator(_ptr);
	}

	inline ConstIterator end() const {
		return ConstIterator(_ptr + _size);
	}
};

} // namespace zylann

#endif // ZN_SPAN_H
