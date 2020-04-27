// Тест модуля pqueue

#include <iostream>
#include <vector>
#include <string>
#include "pqueue.hpp"


using namespace std;


int main()
{
	// Массив строк, которые будут использованы в качестве входных данных 
	// при формировании пакетов в очереди
	const vector<string> stih = {
		"I think that I shall never see",
		"A graph more lovely than a tree.",
		"A tree whose crucial property",
		"Is loop-free connectivity.",
		"A tree that must be sure to span",
		"So packets can reach every LAN.",
		"First, the root must be selected.",
		"By ID, it is elected.",
		"Least-cost paths from root are traced.",
		"In the tree, these paths are placed.",
		"A mesh is made by folks like me,",
		"Then bridges find a spanning tree."
	};

	// Объявляем очередь пакетов
	Pqueue<100, 20, 1000> que;
	size_t id = 99;

	// Перебираем строки, добавляем в очередь новый пакет,
	// содержащий текущую строку
	for (const auto& i : stih)
		que.push(i.c_str(), i.length() + 1, ++id);

	// Буфер для получения данных из пакетов
	const size_t BUF_SIZE = 80;
	char buf[BUF_SIZE];
	size_t size;

	// Извлекаем пакеты из очереди, пока очередь не пуста
	while (que.pop(buf, BUF_SIZE, size, id))
		cout << "#" << id << ", " << size << " bytes:\t" << buf << endl;

	return 0;
}
