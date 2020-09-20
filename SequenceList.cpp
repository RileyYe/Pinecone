#pragma once
#include <iterator>
#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H
/*
** Used C++17 ( if constexpr () )
** Partly support Microsoft STL algorithm.
**
** Support : 
**	iterator, fill(), at(), operator[], insert(), find(), find_if()
**	size(), empty()
*/
namespace rileyye
{

	template <typename T, size_t Size>
	class Sequence_list_const_iterator
	{
	public:
		// type alias...
		using iterator_category = ::std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
	private:
		pointer _Ptr; // beginning of this array
	public:
		constexpr explicit Sequence_list_const_iterator(pointer _Parg, size_t _Off = 0) noexcept : _Ptr{ _Parg + _Off } {}
		constexpr Sequence_list_const_iterator() noexcept : _Ptr{} {}
		constexpr reference operator*() const noexcept {
			return *_Ptr;
		}
		constexpr pointer operator->() const noexcept {
			return _Ptr;
		}
		constexpr Sequence_list_const_iterator& operator++() noexcept {
			++_Ptr;
			return *this;
		}
		constexpr Sequence_list_const_iterator& operator--() noexcept {
			--_Ptr;
			return *this;
		}
		constexpr Sequence_list_const_iterator operator++(int) noexcept {
			Sequence_list_const_iterator _Temp = *this;
			++_Ptr;
			return _Temp;
		}
		constexpr Sequence_list_const_iterator operator--(int) noexcept {
			Sequence_list_const_iterator _Temp = *this;
			--_Ptr;
			return _Temp;
		}
		constexpr Sequence_list_const_iterator& operator+=(const ptrdiff_t _Off) noexcept {
			_Ptr += _Off;
			return *this;
		}
		constexpr Sequence_list_const_iterator operator+(const ptrdiff_t _Off) noexcept {
			return Sequence_list_const_iterator{ _Ptr + _Off };
		}
		constexpr Sequence_list_const_iterator& operator-=(const ptrdiff_t _Off) noexcept {
			_Ptr -= _Off;
			return *this;
		}
		constexpr Sequence_list_const_iterator operator-(const ptrdiff_t _Off) noexcept {
			return Sequence_list_const_iterator{ _Ptr - _Off };
		}
		constexpr ptrdiff_t operator-(const Sequence_list_const_iterator& _Right) const noexcept {
			return _Ptr - _Right._Ptr;
		}
		constexpr reference operator[](const ptrdiff_t _Off) const noexcept {
			return _Ptr[_Off];
		}
		constexpr bool operator==(const Sequence_list_const_iterator& _Right) const noexcept {
			return _Ptr == _Right._Ptr;
		}
		constexpr bool operator!=(const Sequence_list_const_iterator& _Right) const noexcept {
			return !(*this == _Right);
		}
		constexpr bool operator<(const Sequence_list_const_iterator& _Right) const noexcept {
			return _Ptr < _Right._Ptr;
		}
		constexpr bool operator>(const Sequence_list_const_iterator& _Right) const noexcept {
			return _Ptr > _Right._Ptr;
		}
		constexpr bool operator<=(const Sequence_list_const_iterator& _Right) const noexcept {
			return !(_Right < *this);
		}
		constexpr bool operator>=(const Sequence_list_const_iterator& _Right) const noexcept {
			return !(*this < _Right);
		}
		constexpr pointer _Unwrapped() const noexcept {
			return _Ptr;
		}
		constexpr void _Seek_to(pointer _It) noexcept {
			_Ptr = _It;
		}
		constexpr pointer unwrap() const noexcept {
			return _Ptr;
		}
		constexpr operator void* () {
			return (void*)_Ptr;
		}
	};

	template <class T, size_t Size>
	constexpr Sequence_list_const_iterator<T, Size> operator+
		(const ptrdiff_t _Off, Sequence_list_const_iterator<T, Size> _Next)
		noexcept {
		return _Next += _Off;
	}

	template <class T, size_t Size>
	class Sequence_list_iterator : public Sequence_list_const_iterator<T, Size> {
	public:
		using _Mybase = Sequence_list_const_iterator<T, Size>;
		using iterator_category = ::std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		constexpr Sequence_list_iterator() noexcept {}

		constexpr explicit Sequence_list_iterator(pointer _Parg, size_t _Off = 0) noexcept : _Mybase(_Parg, _Off) {}

		constexpr reference operator*() const noexcept {
			return const_cast<reference>(_Mybase::operator*());
		}

		constexpr pointer operator->() const noexcept {
			return const_cast<pointer>(_Mybase::operator->());
		}

		constexpr Sequence_list_iterator& operator++() noexcept {
			_Mybase::operator++();
			return *this;
		}

		constexpr Sequence_list_iterator operator++(int) noexcept {
			Sequence_list_iterator _Temp = *this;
			_Mybase::operator++();
			return _Temp;
		}

		constexpr Sequence_list_iterator& operator--() noexcept {
			_Mybase::operator--();
			return *this;
		}

		constexpr Sequence_list_iterator operator--(int) noexcept {
			Sequence_list_iterator _Temp = *this;
			_Mybase::operator--();
			return _Temp;
		}

		constexpr Sequence_list_iterator& operator+=(const ptrdiff_t _Off) noexcept {
			_Mybase::operator+=(_Off);
			return *this;
		}

		constexpr Sequence_list_iterator operator+(const ptrdiff_t _Off) const noexcept {
			Sequence_list_iterator _Temp = *this;
			return _Temp += _Off;
		}

		constexpr Sequence_list_iterator& operator-=(const ptrdiff_t _Off) noexcept {
			_Mybase::operator-=(_Off);
			return *this;
		}

		using _Mybase::operator-;

		constexpr Sequence_list_iterator operator-(const ptrdiff_t _Off) const noexcept {
			Sequence_list_iterator _Temp = *this;
			return _Temp -= _Off;
		}

		constexpr reference operator[](const ptrdiff_t _Off) const noexcept {
			return const_cast<reference>(_Mybase::operator[](_Off));
		}

		constexpr pointer _Unwrapped() const noexcept {
			return const_cast<pointer>(_Mybase::_Unwrapped());
		}
	};

	template <class T, size_t Size>
	constexpr Sequence_list_iterator<T, Size> operator+(
		const ptrdiff_t Off, Sequence_list_iterator<T, Size> Next) noexcept {
		return Next += Off;
	}

	template <typename T, size_t Size>
	class SequenceList
	{
	private:
		T Elems[Size];
	public:
		using value_type = T;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;

		using iterator = Sequence_list_iterator<value_type, Size>;
		using const_iterator = Sequence_list_const_iterator<value_type, Size>;

		using reverse_iterator = ::std::reverse_iterator<iterator>;
		using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;
	private:
		mutable iterator last_valid = iterator(Elems);
	public:
		SequenceList(::std::initializer_list<T> Init) noexcept : last_valid(iterator(Elems)) {
			if (Init.size()) {
				for (size_t i = 0; i != Size; ++i) {
					Elems[i] = *(Init.begin() + i);
					++last_valid;
				}
			}
			else {
			}
		}
		constexpr iterator insert(iterator Pos, const T& Val) {
			if (Pos > iterator(Elems + Size) || Pos < begin()) /* iterator out of range for sure */ {
				throw ::std::out_of_range("Iterator Wrong Range");
			}

			if (last_valid == iterator(Elems + Size)) {
				if (Pos == iterator(Elems + Size)) {  // last elem
					*--Pos = Val;
					return Pos;
				}
				else {
					::std::copy_backward(Pos, --end(), end());
					*Pos = Val;
					return Pos;
				}
			}
			else {
				if (Pos == last_valid) {
					++last_valid;
					*Pos = Val;
					return Pos;
				}
				else {
					++last_valid;
					::std::copy_backward(Pos, last_valid, --end());
					*Pos = Val;
					return Pos;
				}
			}

		}
		constexpr iterator insert(size_t Pos, const T& Val) {
			return this->insert(iterator(Elems + Pos), Val);
		}
		constexpr void erase(iterator First, iterator Last) {
			auto first = First;
			if constexpr (!::std::is_pod_v<T>) { // 若非 plain old data，需逐次调用 destructor
				for (; First != Last; ++First) {
					First->~T();
				}
				std::copy_n(First, last_valid - Last, first); // 拷贝擦除位置后的 data
				last_valid = first + (last_valid - Last); // 重设置 end() 
			}
			else { // 若为 plain old data
				::std::memset(First, 0xCC, sizeof(T) * (Last - First)); // 直接销毁数据
				::std::memcpy(first, Last, sizeof(T) * (last_valid - Last)); // 拷贝擦除位置后的 data
				last_valid = first + (last_valid - Last); // 重设置 end() 
			}
		}
		constexpr void erase(size_type index, size_type num) {
			this->erase(iterator(Elems + index), iterator(Elems + index + num ));
		}
		template <typename Predicate>
		constexpr iterator find_if(iterator&& First, iterator&& Last, Predicate&& Pred) {
			for (; First != Last; ++First) {
				if (Pred(*First)) {
					break;
				}
			}
			return First;
		}
		constexpr iterator find(iterator&& First, iterator&& Last, const T& Val) {
			for (; First != Last; ++First) {
				if (*First == Val) {
					break;
				}
			}
			return First;
		}
		constexpr iterator begin() noexcept {
			return iterator{ Elems, 0 };
		}
		constexpr iterator end() noexcept {
			return last_valid;
		}
		constexpr reverse_iterator rbegin() noexcept {
			return reverse_iterator(end());
		}
		constexpr reverse_iterator rend() noexcept {
			return reverse_iterator(begin());
		}
		constexpr const_iterator cbegin() noexcept {
			return const_iterator(begin());
		}
		constexpr const_iterator cend() noexcept {
			return const_iterator(end());
		}
		constexpr const_reverse_iterator crbegin() noexcept {
			return const_reverse_iterator(rbegin());
		}
		constexpr const_reverse_iterator crend() noexcept {
			return const_reverse_iterator(rend());
		}
		void swap(SequenceList& _Other) noexcept(::std::_Is_nothrow_swappable<value_type>::value) {
			::std::_Swap_ranges_unchecked(Elems, Elems + Size, _Other.Elems);
		}
		constexpr void fill(const value_type& _Val) {
			::std::fill_n(Elems, Size, _Val);
		}
		constexpr reference operator[](size_type _Pos) noexcept {
			return Elems[_Pos];
		}
		constexpr const_reference operator[](size_type _Pos) const noexcept {
			return Elems[_Pos];
		}
		constexpr bool empty() const noexcept {
			return false;
		}
		constexpr size_type max_size() const noexcept {
			return Size;
		}
		constexpr size_type size() noexcept {
			return last_valid - this->begin();
		}
		constexpr reference at(size_type _Pos) {
			if (_Pos >= Size) {
				throw ::std::out_of_range("Out Of Range!");
			}
			else {
				return Elems[_Pos];
			}
		}
		constexpr const_reference at(size_type _Pos) const {
			if (_Pos >= Size) {
				throw ::std::out_of_range("Out Of Range!");
			}
			else {
				return Elems[_Pos];
			}
		}
		constexpr pointer _Unchecked_begin() noexcept {
			return Elems;
		}
		constexpr const_pointer _Unchecked_begin() const noexcept {
			return Elems;
		}
		constexpr pointer _Unchecked_end() noexcept {
			return Elems + Size;
		}
		constexpr const_pointer _Unchecked_end() const noexcept {
			return Elems + Size;
		}
	};
}
#endif
