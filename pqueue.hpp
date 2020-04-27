#ifndef PQUEUE_HEADER
#define PQUEUE_HEADER


#include <deque>
#include <cstring>
#include "packet.hpp"


// Шаблон класса, описывающего очередь пакетов
// Параметры шаблона:
// MAX_LEN - максимальная длина данных в пакете
// MAX_CNT - максимальное количество пакетов в очереди
// MAX_SIZE - максимальный общий объём данных всех пакетов в очереди
template <const size_t MAX_LEN, const size_t MAX_CNT, const size_t MAX_SIZE>
class Pqueue {

public:

	// Конструктор по умолчанию
	Pqueue() : total_(0) {}
	
	// Получение количества пакетов в очереди
	const size_t get_packet_count() const { return fifo_.size(); }

	// Добавление пакета в очередь
	bool push(const DataType* data, const size_t data_count,
		const size_t packet_id);

	// Извлечение пакета из очереди
	bool pop(DataType* buffer, const size_t buffer_size,
		size_t& data_count, size_t& packet_id);

private:

	// Макимальная длина данных в пакете
	static const size_t max_packet_length_ = MAX_LEN;
	
	// Максимальное количество пакетов в очереди
	static const size_t max_packet_count_ = MAX_CNT;
	
	// Максимальный общий объём данных всех пакетов в очереди
	static const size_t max_queue_size_ = MAX_SIZE;
	
	// Контейнер пакетов
	std::deque<Packet> fifo_;
	
	// Счётчик общего объёма данных всех пакетов в очереди
	size_t total_;
	
};


// push - Добавление пакета в очередь
// data: указатель на входные данные 
// data_count: объём входных данных
// packet_id: идентификатор пакета
template <const size_t L, const size_t C, const size_t S>
bool Pqueue<L, C, S>::push(const DataType* data, const size_t data_count,
	const size_t packet_id)
{
	// Проверка, не превышен ли какой-нибудь лимит
	if (data_count > max_packet_length_ || 
		get_packet_count() >= max_packet_count_ || 
		total_ + data_count > max_queue_size_)
		return false;
	
	// Создаём в конце очереди новый пакет на основе массива данных
	fifo_.emplace_back(data, data_count, packet_id);
	
	// Увеличиваем счётчик размера всех данных в очереди
	total_ += data_count;
	
	return true;
}


// Извлечение пакета из очереди
// buffer: указатель на буфер для копирования данных пакета
// buffer_size: размер буфера
// data_count: ссылка на объём данных, полученных из пакета
// packet_id: ссылка на идентификатор пакета
// Возвращает true в случае извлечения данных из пакета,
// false - когда очередь пуста
template <const size_t L, const size_t C, const size_t S>
bool Pqueue<L, C, S>::pop(DataType* buffer, const size_t buffer_size,
	size_t& data_count, size_t& packet_id)
{
	// Проверяем, не пуста ли очередь
	if (! get_packet_count())
		return false;

	// Ярлык на первый пакет в очереди
	const Packet pkt = fifo_.front();
	
	// Получаем идентификатор пакета
	packet_id = pkt.get_id();
	
	// Узнаём размер данных в пакете
	const size_t packet_size = pkt.get_size();

	// Определяем сколько данных надо скопировать из пакета в буфер,
	// в зависимости от того, превышает ли объём данных в пакете
	// размер переданного буфера
	data_count = (buffer_size < packet_size) ? buffer_size : packet_size;
	
	// Копируем данные из пакета в буфер
	std::memcpy(buffer, pkt.get_data(), data_count);

	// Уменьшаем счётчик всех данных в очереди
	total_ -= packet_size;
	
	// Удаляем из очереди первый пакет
	fifo_.pop_front();

	return true;
}


#endif
