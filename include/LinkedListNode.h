#pragma once

template <typename T>
struct LinkedListNode {
	T* data = nullptr;
	LinkedListNode* next = nullptr;
	explicit LinkedListNode(T* value) : data(value), next(nullptr) {}
};