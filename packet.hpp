#ifndef PACKET_HEADER
#define PACKET_HEADER

#include <vector>

typedef char DataType;

class Packet {
public:
	Packet(const DataType* buf, const size_t size, const size_t id) :
		id_(id), data_(buf, buf + size) {}
	const size_t get_id() const { return id_; }
	const size_t get_size() const { return data_.size(); }
	const DataType* get_data() const { return data_.data(); }
private:
	const size_t id_;
	std::vector<DataType> data_;
	Packet operator=(const Packet& src);
};

#endif
