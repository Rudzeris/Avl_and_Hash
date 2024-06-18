#pragma once

template<class KeyType>
class UFuncForHash {
public:
	virtual int operator()(const KeyType& key) const = 0;
};


bool SizeIsCorrect(int size) {
	if (size < 0)
		return false;
	return true;
}

template <class KeyType, class ValueType, class UFunc>
class Hash {
	UFunc hashFunction;

	struct Item {
		KeyType key;
		ValueType value;
		bool isEmpty;
		Item() :key{}, value{}, isEmpty{ true } {}
		Item(KeyType key, ValueType value) :
			key{ key }, value{ value }, isEmpty{ false } {}
		void Print() const {
			std::cout << "[" << key << ':' << value << ']';
		}
	};
	struct Items {
		Item* data;
		int size;
		int maxSize;
		Items() : maxSize{ 2 }, size{ 0 }, data{ nullptr } {
			data = new Item[maxSize];
		}
		bool Full() const {
			return maxSize <= size;
		}
		bool Empty() const {
			return size == 0;
		}
		bool IsExists(const KeyType& key) const {
			if (Empty())
				return false;
			for (int i = 0; i < size; i++)
				if (data[i].key == key)
					return true;
			return false;
		}
		ValueType Search(const KeyType& key) const {
			if (Empty())
				throw "Search";
			for (int i = 0; i < size; i++)
				if (data[i].key == key)
					return data[i].value;
			throw "Search";
		}
		void Resize() {
			if (!Full())
				return;
			maxSize *= 2;
			Item* newData = new Item[maxSize];
			for (int i = 0; i < size; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		void Push(const KeyType& key, const ValueType& value) {
			if (IsExists(key))
				return;
			Resize();
			int i = 0;
			for (i = 0; i < size; i++)
				if (data[i].isEmpty)
					break;
			
			data[i] = { key,value };

			if (size == i)
				size++;
		}
		bool Pop(const KeyType& key) {
			bool remove = false;
			for (int i = 0; i < size; i++)
				if (data[i].key == key && !data[i].isEmpty)
				{
					data[i].isEmpty = true;
					remove = true;
				}
			return remove;
		}
		void Print() const {
			if (Empty())
				return;
			for (int i = 0; i < size; i++) {
				if (data[i].isEmpty)
					continue;
				data[i].Print();
				std::cout << " ";
			}
			std::cout << '\n';
		}
	};

	const int defaultSize = 20;

	Items* items;
	int maxSize;

	int GetIndex(const KeyType& key) const {
		return hashFunction(key) % maxSize;
	}
public:
	Hash(int bufferSize) :
		maxSize{ SizeIsCorrect(bufferSize) ? bufferSize : defaultSize },
		items{ nullptr } {
		items = new Items[maxSize];
	}

	void Push(const KeyType& key, const ValueType& value) {
		int index = GetIndex(key);
		while (index < 0) index = (maxSize + index) % maxSize;
		
		items[index].Push(key, value);
	}

	void Pop(const KeyType& key) {
		int index = GetIndex(key);
		while (index < 0) index = (maxSize + index)%maxSize;
		
		items[index].Pop(key);
	}

	ValueType Search(const KeyType& key) const {

		int index = GetIndex(key);
		if (index < 0) index = maxSize + index;

		if (items[index].IsExists(key))
			return items[index].Search(key);
		else
			return NULL;
	}

	void Print() const {
		if (items) {
			for (int i = 0; i < maxSize; i++) {
				items[i].Print();
			}
		}
	}
};