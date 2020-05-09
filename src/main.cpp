#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <utility>
#include "vector.hpp"

size_t gid {};
class shouter {
	private:
	size_t id;
	public:
	shouter() : id{ gid++ }{
		std::cout << "Shouter " << id << " created" << std::endl;
	}

	~shouter() {
		std::cout << "Shouter " << id << " destructed" << std::endl;
	}
};

const std::string separator = std::string(50, '=');
void print_test_header(const char* title) {
	using namespace std;
	cout << endl << separator << endl;
	cout << title;
	cout << endl << separator << endl;
}

void test_push_back() {
	print_test_header("Test push_back");
	chbm::vector<int> vec = chbm::vector<int>();
	for (size_t i = 0; i < 10; ++i) {
		vec.push_back(i);
	}

	for (auto x: vec) {
		std::cout << x << std::endl;
	}
}

void test_push_front() {
	print_test_header("Test push_front");
	chbm::vector<int> vec = chbm::vector<int>();
	for (size_t i = 0; i < 10; ++i) {
		vec.push_front(i);
	}

	for (size_t i = 0; i < 10; ++i) {
		std::cout << "Index #" << i << " Contains: " << vec[i] << std::endl;
	}
}

void test_pop_back() {
	print_test_header("Test pop_back");
	chbm::vector<std::unique_ptr<shouter>> vec = chbm::vector<std::unique_ptr<shouter>>();
	for (size_t i = 0; i < 10; ++i) {
		vec.push_back(std::move(std::unique_ptr<shouter> { new shouter()}));
	}

	for (size_t i = 0; i < 10; ++i) {
		std::cout << "pop_back(" << i << ")" << std::endl;
		vec.pop_back();
	}
}

void test_pop_front() {
	print_test_header("Test pop_front");
	gid = 0;
	chbm::vector<std::unique_ptr<shouter>> vec = chbm::vector<std::unique_ptr<shouter>>();
	for (size_t i = 0; i < 10; ++i) {
		vec.push_back(std::move(std::unique_ptr<shouter> { new shouter()}));
	}

	for (size_t i = 0; i < 10; ++i) {
		std::cout << "pop_front(" << i << ")" << std::endl;
		vec.pop_front();
	}
}

void test_insert() {
	print_test_header("Test insert");
	chbm::vector<int> vec = chbm::vector<int>(10, -1);
	vec.insert(vec.begin() + 1, 420);
	for (auto x: vec) {
		std::cout << x << std::endl;
	}
}


int main() {
	test_push_back();
	test_push_front();
	test_pop_back();
	test_pop_front();
	test_insert();
}