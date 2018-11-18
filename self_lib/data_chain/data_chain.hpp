#pragma once
#include <cstddef>

namespace TestList {

struct chain_node;
class data_chain {
public:
	data_chain();

	~data_chain();
	int count() const {
		return m_count;
	}

	///@note: fifo
	size_t read(void *buf);
	size_t read_size() const;
	bool write(void *buf, size_t len);

private:
	chain_node *m_header;
	chain_node *m_tail;
	int m_count;
};

} /* namespace TestList */







