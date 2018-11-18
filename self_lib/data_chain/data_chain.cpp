#include <iostream>
#include <cstring>

#include "data_chain.hpp"

namespace TestList {

struct chain_node {
	void *buf;
	size_t len;
	chain_node *next;
};

data_chain::data_chain() : m_count(0) {
	chain_node *root = new chain_node();
	root -> buf = nullptr;
	root -> len = 0;
	root -> next = nullptr;
	m_header = root;
	m_tail = root;
}

data_chain::~data_chain() {
	while (m_header -> next) {
		chain_node *tmp = m_header -> next;
		delete [](char *)(tmp -> buf);
		m_header -> next = tmp -> next;
		delete tmp;
		--m_count;
	}
	delete m_header;
}

///@note: fifo
size_t data_chain::read(void *buf) {
	if (m_header -> next) {
		chain_node *first = m_header -> next;
		memcpy(buf, first -> buf, first -> len);
		size_t read_len = first -> len;
		delete [](char *)(first -> buf);
		m_header -> next = first -> next;
		delete first;
		--m_count;
		return read_len;
	} else {
		std::cout << "list is empty!" << std::endl;
		return 0;
	}
}

size_t data_chain::read_size() const {
	if (m_header -> next) {
		return m_header -> next -> len;
	} else {
		std::cout << "list is empty!" << std::endl;
		return 0;
	}
}

bool data_chain::write(void *buf, size_t len) {
	chain_node *node = new chain_node();
	char *tmp_buf = new char[len];
	memcpy(tmp_buf, buf, len);
	node -> buf = tmp_buf;
	node -> len = len;
	node -> next = nullptr;
	m_tail -> next = node;
	m_tail = node;
	++m_count;
	return true;
}

} /* namespace TestList */







