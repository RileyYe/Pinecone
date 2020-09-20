#pragma once
#include <memory>
#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
namespace rileyye {
	template <typename T>
	struct forward_list_node {
		using pointer = T*;
		using value_type = T;
		using reference = T&;
		using node_pointer = forward_list_node*;
		value_type value_;
		node_pointer next_;
		forward_list_node(const value_type& val = value_type(), node_pointer next = nullptr) : 
			value_(val), next_(next)
		{}
	};
	template <typename forward_list_node>
	struct forward_list_iterator{
		using value_type = forward_list_node;
		using reference = forward_list_node&;
		using pointer = forward_list_node*;		
		using self = forward_list_iterator;
	private:
		mutable pointer ptr_;
	public:
		forward_list_iterator(pointer ptr) : ptr_(ptr) {}
		typename value_type::reference operator*() {
			return ptr_->value_;
		}
		typename value_type::pointer operator->() {
			return &(ptr_->value_);
		}
		self& operator++() {			ptr_ = ptr_->next_;
			return *this;
		}
		self operator++(int) {
			auto temp_ = *this;
			++* this;
			return temp_;
		}
		void __advance_without_side_effects() {
			ptr_ = ptr_->next_;
		}
		bool operator==(const self& another) const {
			return ptr_ == another.ptr_;
		}
		bool operator!=(const self& another) const {
			return !(*this == another);
		}
		operator pointer() {
			return ptr_;
		}
		pointer& unwrap() const {
			return ptr_;
		}
	};

	template <typename T>
	struct forward_list {
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator = forward_list_iterator<forward_list_node<T>>;
		using size_type = size_t;
	private:
		forward_list_node<T> head_;
		size_type size_;
	public:
		forward_list() : size_(0) {

		}
		forward_list(const T& val) : size_(1) {
			head_.next_ = new forward_list_node<T>(val);
		}
		forward_list(::std::initializer_list<value_type> init) : size_(init.size()) {
			for (auto iter = init.end()-1; iter >= init.begin(); --iter ) {
				push_front(*iter);
			}
		}
		// insert after pos, because forward_list only supports forward_iterator
		iterator insert(iterator pos, const value_type& val) {
			pos.unwrap()->next_ = new forward_list_node<T>(val, pos.unwrap()->next_);
			++size_;
			return iterator(pos.unwrap()->next_);
		}
		iterator erase(iterator first, iterator last) {
			for (; first != last; ) {
				typename iterator::pointer current_ = first;
				first = iterator(first.unwrap()->next_);
				delete current_;
				--size_;
			}
			head_.next_ = first;
			return first;
		}
		// push_back 极度消耗性能，如需push_back应该使用双向链表 rileyye::list
		[[deprecated]] void push_back(const value_type& val) {}
		// pop_back 极度消耗性能，如需pop_back应该使用双向链表 rileyye::list
		[[deprecated]] void pop_back(const value_type& val) {}
		void push_front(const value_type& val) {
			head_.next_ = new forward_list_node<T>(val, head_.next_);
			++size_;
		}
		void pop_front() {
			auto cut_ = head_.next_;
			head_.next_ = cut_->next_;
			delete cut_;
			--size_;
		}
		iterator begin() const {
			return iterator(head_.next_);
		}
		iterator end() const {
			return iterator(nullptr);
		}
		size_type size() const {
			return size_;
		}

		void reverse() {
			typename iterator::pointer node = head_.next_;
			typename iterator::pointer new_head = nullptr;
			if (node == nullptr) {
				return;
			}
			while (node != nullptr) {
				auto temp = node->next_;
				node->next_ = new_head;
				new_head = node;
				node = temp;
			}
			head_.next_ = new_head;
		}

		// 未设计 struct forward_list_const_iterator， 故没有使用 const forward_list<T>&
		bool operator<(forward_list<T>& another) {
			if (this->size() == 0) {
				return false;
			}
			if (another.size() == 0) {
				return true;
			}
			else {
				for (auto iter = begin(), iter2 = another.begin(); iter != end() && iter2 != another.end(); ++iter, ++iter2) {
					if (*iter > * iter2) {
						return false;
					}
				}
				return true;
			}
		}

		~forward_list() {
			iterator iter = begin();
			for (; iter != end(); ) {
				typename iterator::pointer current_ = iter;
				iter = iterator(iter.unwrap()->next_);
				delete current_;
			}
		}
	};

}
#endif // !FORWARD_LIST_H
