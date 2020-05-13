#include <cstddef>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace chbm {
	template <class T>
	class vector {

	public:
		using value_t = T;
		using reference = value_t&;
		using const_reference = const value_t&;
		using iterator = value_t*;
		using size_type = std::size_t;

	private:
		std::unique_ptr<value_t[]> elems {};
		size_type nb_elems {};
		size_type cap {};

	public:
		vector() = default;

		vector(size_type capacity) : elems{ new value_t[capacity] }, cap{ capacity } {}

		vector(size_type capacity, const_reference val) :
			elems{ new value_t[capacity] },
			nb_elems{ capacity },
			cap{ capacity } {
				std::fill(begin(), end(), val);
		}

		vector(vector &&other) = default;

		vector& operator=(vector &&other) = default;

		~vector() = default;

		iterator begin() {
			return elems.get();
		}

		iterator end() {
			return begin() + size();
		}

		size_type size() {
			return nb_elems;
		}

		size_type capacity() {
			return cap;
		}

		void reserve(size_type new_cap) {
			using namespace std;

			unique_ptr<value_t[]> new_elems { new value_t[new_cap] };
			move(begin(), end(), new_elems.get());
			cap = new_cap;

			swap(new_elems, elems);
		}

		reference operator[](size_type index) {
			return elems[index];
		}

		bool full() {
			return size() == capacity();
		}

		void push_back(const_reference val) {
			if (full()) expand();

			elems[size()] = val;
			++nb_elems;
		}

		void push_back(T&& val) {
			if (full()) expand();

			elems[size()] = std::move(val);
			++nb_elems;
		}

		void push_front(value_t val) {
			if (full()) expand();

			std::move_backward(begin(), end(), end() + 1);
			elems[size_type {}] = val;
			++nb_elems;
		}

		void pop_back() {
			elems[nb_elems].~value_t();
			--nb_elems;
		}

		void pop_front() {
			elems[size_type {}].~value_t();
			std::move(begin() + 1, end(), begin());
			--nb_elems;
		}

		void insert(iterator pos, const_reference val) {
			if (full()) {
				const size_type dist = std::distance(begin(), pos);
				expand();
				pos = begin() + dist;
			}

			std::move(pos, end(), pos + 1);
			*pos = val;
			++nb_elems;
		}

		reference at(size_type pos) {
			if (pos > size()) throw std::out_of_range("Out of range");

			return elems[pos];
		}

	private:
		void expand() {
			reserve(capacity() ? capacity() * 2 : 64);
		}
	};
}