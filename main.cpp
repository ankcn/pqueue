#include <iostream>
#include <cstring>
#include "pqueue.hpp"

using namespace std;

int main()
{
	Pqueue<1111, 22, 12345> que;

	const char* str = "First packet";
	que.push(str, strlen(str) + 1, 1);

	const char* txt = "new packet";
	que.push(txt, strlen(str) + 1, 2);

	size_t id;
	size_t size;
	char buf[22];

	que.pop(buf, 22, size, id);
	cout << "#" << id << ": " << buf << "(" << size << " bytes)" << endl;

	que.pop(buf, 22, size, id);
	cout << "#" << id << ": " << buf << "(" << size << " bytes)" << endl;	

	return 0;
}