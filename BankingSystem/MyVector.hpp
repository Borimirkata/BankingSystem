#pragma once

#include <iostream>
namespace
{
	const size_t DEFAULT_CAP = 8;
}
template <typename T>
class MyVector
{
	T* data;
	size_t size = 0;
	size_t capacity = DEFAULT_CAP;

	void copyFrom(const MyVector<T>& other);
	void free();
	void moveFrom(MyVector<T>&& other);
	void resize(size_t newCap);

public:
	MyVector();
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other);
	~MyVector<T>();

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const T& _data);
	void push_back(T&& _data);
	void pop_back();
	void insert(const T& _data, unsigned idx);
	void insert(T&& _data, unsigned idx);
	void erase(unsigned idx);
	void clear();

	bool empty() const;
	T& operator[](const size_t idx);
	const T& operator[](const size_t idx) const;

};
template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
void MyVector<T>::free()
{
	delete[] data;
	data = nullptr;
	capacity = size = 0;
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.capacity = other.size = 0;
}

template <typename T>
void MyVector<T>::resize(size_t newCap)
{
	capacity = newCap;
	T* temp = new T[newCap];
	for (int i = 0; i < size; i++) {
		temp[i] = std::move(data[i]);
	}
	delete[] data;
	data = temp;
}

template <typename T>
MyVector<T>::MyVector()
{
	data = nullptr;
	size = capacity = 0;
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector<T>()
{
	free();
}


template <typename T>
size_t MyVector<T>::getSize() const
{
	return size;
}

template <typename T>
size_t MyVector<T>::getCapacity() const
{
	return capacity;
}


template <typename T>
void MyVector<T>::push_back(const T& _data)
{
	if (capacity == 0) {
		resize(DEFAULT_CAP);
	}
	if (size == capacity) {
		resize(2 * capacity);
	}
	data[size++] = _data;
}

template <typename T>
void MyVector<T>::push_back(T&& _data)
{
	if (capacity == 0) {
		resize(DEFAULT_CAP);
	}
	if (size == capacity) {
		resize(2 * capacity);
	}
	data[size++] = std::move(_data);
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (empty()) {
		throw std::exception("Empty vector");
	}

	size--;
}

template <typename T>
void MyVector<T>::insert(const T& _data, unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity) {
		resize(2 * capacity);
	}

	size++;
	for (int i = size - 1; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}
	data[idx] = _data;
}

template <typename T>
void MyVector<T>::insert(T&& _data, unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity) {
		resize(2 * capacity);
	}

	size++;
	for (int i = size - 1; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}
	data[idx] = std::move(_data);
}
template <typename T>
void MyVector<T>::erase(unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	for (int i = idx; i < size - 1; i++) {
		data[i] = std::move(data[i + 1]);
	}
	size--;
	if (size == capacity / 4) {
		resize(capacity / 2);
	}
}

template <typename T>
void MyVector<T>::clear()
{
	delete[] data;
	size = 0;
	capacity = DEFAULT_CAP;
	data = new T[capacity];
}


template <typename T>
bool MyVector<T>::empty() const
{
	return size == 0;
}

template <typename T>
T& MyVector<T>::operator[](const size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}

template <typename T>
const T& MyVector<T>::operator[](const size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}
