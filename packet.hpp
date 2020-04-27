#ifndef PACKET_HEADER
#define PACKET_HEADER

#include <vector>


// DataType - синоним для типа данных, содержащихся в пакете
// По условиям задачи этот тип - unsigned char
// Здесь этот тип изменён на знаковый char в целях совместимости
// со строковыми литералами
typedef char DataType;

// Класс, описывающий пакет данных
class Packet {

public:

	// Конструктор принимает обязательные параметры: 
	// buf: указатель на данные, помещаемые в пакет
	// size: объём данных
	// id: идентификатор пакета
	Packet(const DataType* buf, const size_t size, const size_t id) :
		// В списке инициализации передаём границы массива данных
		// конструктору контейнера vector
		id_(id), data_(buf, buf + size) {}
	
	// Метод получения идентификатора пакета
	const size_t get_id() const { return id_; }

	// Получение объёма данных в пакете
	const size_t get_size() const { return data_.size(); }
	
	// Получение указателя на начало массива данных
	const DataType* get_data() const { return data_.data(); }

private:
	
	// Идентификатор пакета
	const size_t id_;
	
	// Контейнер для хранения данных в пакете  
	std::vector<DataType> data_;
	
	// Запрет операции присваивания
	// Было бы особенно актуально в случае реализации хранилища данных
	// через указатели и динамическую память
	Packet operator=(const Packet& src);
};

#endif
