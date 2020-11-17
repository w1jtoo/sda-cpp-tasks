#include <stdlib.h>
#include <cassert>
#include <iomanip>
#include <stdexcept>

class DArray {
public:
	DArray(size_t size) {
		data = new int[size];
		this->size = size;
	}

	DArray(const DArray& other) : data(other.data), size(other.size) { }
	DArray(DArray&& other)
			noexcept: 
					data(std::move(other.data)),
					size(std::exchange(other.size, 0))
		{ }

	~DArray() {
		delete[] data;
	}

	int get(size_t index) const {
		if (index < 0 || index >= size) {
			throw std::invalid_argument("Out of range");
		}
		return data[index];
	}

	void set(size_t index, int value) {
		if (index < 0 || index >= size) {
			throw std::invalid_argument("Out of range");
		}
		data[index] = value;
	}

private:
	int* data;
	size_t size; 
};

int main(void) {
	auto arr = new DArray(3);
	for (int i = 0; i < 3; i++) {
		arr->set(i, i + 1);
	}

	for (int i=0; i < 3; i++) {
		assert(arr->get(i) == i + 1);
	}

	auto b = std::move(arr);
	for (int i = 0; i < 3; i++) {
		b->set(i, i + 1);
	}

	for (int i=0; i < 3; i++) {
		assert(b->get(i) == i + 1);
	}

	return 0;
}
