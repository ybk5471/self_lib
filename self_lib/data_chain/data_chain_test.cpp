#include <iostream>
#include "data_chain.hpp"

int main() {
	using namespace TestList;
	data_chain my_chain;
	char n1[10] = "abcdefghi";
	char n2[12] = "aaaaaaaaaaa";

	my_chain.write(n1, 10);
	my_chain.write(n2, 10);
	size_t buf_size = my_chain.read_size();
	while(buf_size) {
		char *buf = new char[buf_size];
		if (buf_size == my_chain.read(buf)) {
			std::cout << "buf content: ";
			for (int i = 0; i < buf_size; ++i) {
				std::cout << buf[i];
			}
			std::cout << std::endl;
		}
		delete []buf;
		buf_size = my_chain.read_size();
	}


	return 0;
}