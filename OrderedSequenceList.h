#pragma once
#include "SequenceList.h"
#include <algorithm>
#include <vector>
#ifndef ORDERED_SEQUENCE_LIST
#define ORDERED_SEQUENCE_LIST
namespace rileyye {
	template <typename T,size_t Size, typename Pred>
	struct OrderedSequenceList : public rileyye::SequenceList<T, Size>
	{
		OrderedSequenceList(::std::initializer_list<T> init) : SequenceList<T, Size>(init) {
			size_t range = init.size();
			if (range > Size) {
				range = Size;
			}
			std::vector<T> container{ init.begin(), init.begin() + range };
			std::sort(container.begin(), container.end(), Pred());
			std::copy(container.begin(), container.end(), this->begin());
		}
		typename SequenceList<T, Size>::iterator ordered_insert(const T& val) {
			auto iter = this->begin();
			for (; iter != this->end(); ++iter) {
				if (Pred()(val, *iter)) {
					break;
				}
			}
			this->insert(iter, val);
			return iter;
		}
	};

}
#endif

