#pragma once
//main
//P-веорятность добавления
//Q-вероятность извлечения
//p<P, то добавляем жлемент
//q<Q, то извлекаем элемент
//имимтатор загрузки многопроцессорной вычислительной системы
#include <iostream>
#include <string>

const int MAX_QUEUE_SIZE = 10000;

template <class T>
class TQueue
{
	T* pMem;
	int size, head, tail, cntr;
public:
	TQueue(int _size = 10);
	~TQueue();
	TQueue(const TQueue& q);

	TQueue& operator =(const TQueue<T>& q);
	bool operator == (const TQueue& q) const;
	bool operator != (const TQueue& q) const;

	int GetTail() { return tail; };
	int GetHead() { return head; };
	int GetSize() { return size; };
	int GetCntr() { return cntr; };

	bool empty() const;
	bool full() const;
	void push(T val);
	T pop();
	T front();                          
	T back();
	void clear();

	friend std::ostream& operator<<(std::ostream& os, const TQueue& q) {
		for (int i = q.head; i < q.head + q.cntr; i++)
			os << q.pMem[i % (q.size)] << " ";
		return os;
	}
};

template<class T>
TQueue<T>::TQueue(int _size)
{
	size = _size;
	head = 0;
	tail = -1;
	cntr = 0;
	pMem = new T[size];
}

template<class T>
TQueue<T>::~TQueue()
{
	delete[] pMem;
}

template<class T>
TQueue<T>::TQueue(const TQueue& q)
{
	if (size<0 || size>MAX_QUEUE_SIZE) throw - 1;
	if (q.empty()) std::runtime_error ("queue is empty");
	size = q.size;
	head = q.head;
	tail = q.tail;
	cntr = q.cntr;
	pMem = new T[size];
	if (tail >= head) {
		for (int i = head; i <= tail; i++) {
			pMem[i] = q.pMem[i];
		}
	}
	else {
		for(int i = head; i < size; i++) {
			pMem[i] = q.pMem[i];
		}
		for (int i = 0; i <= tail; i++) {
			pMem[i] = q.pMem[i];
		}
	}

}

template<class T>
TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
	if (size<0 || size>MAX_QUEUE_SIZE) throw - 1;
	if (this != &q) {
		if (size != q.size) {
			size = q.size;
			delete[] pMem;
			pMem = new T[size];
		}
		head = q.head;
		tail = q.tail;
		cntr = q.cntr;
		if (tail >= head) {
			for (int i = head; i <= tail; i++) {
				pMem[i] = q.pMem[i];
			}
		}
		else {
			for (int i = head; i < size; i++) {
				pMem[i] = q.pMem[i];
			}
			for (int i = 0; i <= tail; i++) {
				pMem[i] = q.pMem[i];
			}
		}
	}
	return *this;
}

template<class T>
bool TQueue<T>::operator==(const TQueue& object) const
{
	if (cntr != object.cntr) {
		return false;
	}
	else {
		TQueue this_tmp = *this;
		TQueue obj_tmp = object;
		while (!this_tmp.empty()) {
			if (this_tmp.front() != obj_tmp.front()) {
				return false;
			}
			this_tmp.pop();
			obj_tmp.pop();
		}
	}
	return true;
}

template<class T>
bool TQueue<T>::operator!=(const TQueue& q) const
{
	return !(*this == q);
}

template<class T>
bool TQueue<T>::empty() const
{
	return cntr == 0;
}

template<class T>
bool TQueue<T>::full() const
{
	return cntr == size;
}

template<class T>
T TQueue<T>::front()
{
	if (this->empty())
	{
		throw std::exception(); 
	}
	return pMem[head];
}

template<class T>
T TQueue<T>::back()
{
	if (this->empty())
	{
		throw std::exception(); 
	}
	return pMem[tail]; 
}

template<class T>
void TQueue<T>::push(T val)
{
	if(full()) {
		throw - 1;
	}
	if (tail == size - 1) {
		tail = 0;
	}
	else {
		tail++;
	}
	pMem[tail] = val;
	cntr++;
}

template<class T>
T TQueue<T>::pop()
{
	if (empty()) {
		throw - 1;
	}
	int ind = head;
	if (head == size - 1) {
		head = 0;
	}
	else {
		head++;
	}
	cntr--;


	return pMem[ind];
}

template<class T>
void TQueue<T>::clear()
{
	head = 0;
	tail = -1;
	cntr = 0;
}
