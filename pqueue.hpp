#ifndef PQUEUE_HEADER
#define PQUEUE_HEADER


#include <deque>
#include <cstring>
#include "packet.hpp"


template <const size_t MAX_LEN, const size_t MAX_CNT, const size_t MAX_SIZE> class Pqueue {
public:
	Pqueue() : total_(0) {}
	const size_t get_packet_count() const { return fifo_.size(); }
	bool push(const DataType* data, const size_t data_count, const size_t packet_id);
	bool pop(DataType* buffer, const size_t buffer_size, size_t& data_count, size_t& packet_id);
private:
	static const size_t max_packet_length_ = MAX_LEN;
	static const size_t max_packet_count_ = MAX_CNT;
	static const size_t max_queue_size_ = MAX_SIZE;
	std::deque<Packet> fifo_;
	size_t total_;
};


template <const size_t L, const size_t C, const size_t S>
bool Pqueue<L, C, S>::push(const DataType* data, const size_t data_count, const size_t packet_id)
{
	if (data_count > max_packet_length_ || 
		get_packet_count() >= max_packet_count_ || 
		total_ + data_count > max_queue_size_)
		return false;
	fifo_.emplace_back(data, data_count, packet_id);
	total_ += data_count;
	return true;
}


template <const size_t L, const size_t C, const size_t S>
bool Pqueue<L, C, S>::pop(DataType* buffer, const size_t buffer_size, size_t& data_count, size_t& packet_id)
{
	if (! get_packet_count())
		return false;
	
	const Packet pkt = fifo_.front();
	packet_id = pkt.get_id();
	const size_t packet_size = pkt.get_size();
	data_count = (buffer_size < packet_size) ? buffer_size : packet_size;
	std::memcpy(buffer, pkt.get_data(), data_count);
	total_ -= packet_size;
	fifo_.pop_front();

	return true;
}


#endif
