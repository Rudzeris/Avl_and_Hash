#pragma once

template<class KeyType>
class UFuncForHash {
public:
	//virtual int operator()(const KeyType& key) = 0;
	virtual int GetHash(const KeyType& key) = 0;
};


bool SizeIsCorrect(int size) {
	if (size < 0)
		return false;
	return true;
}

template <class KeyType, class ValueType>
class Hash {
	UFuncForHash<KeyType>* hashFunction;

	struct Item {
		KeyType key;
		ValueType value;
		Item() :key{}, value{} {}
		Item(KeyType key, ValueType value) :
			key{ key }, value{ value } {}
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
		bool IsExists(const KeyType& key) {
			if (Empty())
				return false;
			for (int i = 0; i < size; i++)
				if (data[i].key == key)
					return true;
			return false;
		}
		ValueType Search(const KeyType& key) {
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
			data[size++] = { key,value };
		}
		void Print() const {
			if (Empty())
				return;
			for (int i = 0; i < size; i++) {
				data[i].Print();
				std::cout << " ";
			}
			std::cout << '\n';
		}
	};

	const int defaultSize = 20;

	Items* items;
	int maxSize;

	bool HashIsCorrect(UFuncForHash<KeyType>* hash) {
		if (hash == nullptr)
			return false;
		return true;
	}
public:
	Hash(int bufferSize) :
		maxSize{ SizeIsCorrect(bufferSize) ? bufferSize : defaultSize },
		items{ nullptr },
		hashFunction{ nullptr } {
		items = new Items[maxSize];
	}

	void SetHashFunction(UFuncForHash<KeyType>* newHashFunction) {
		if (!HashIsCorrect(newHashFunction))
		{
			std::cout << "Hash fuction is bad\n";
			return;
		}
		if (this->hashFunction != nullptr)
			delete this->hashFunction;
		this->hashFunction = newHashFunction;
	}

	void Push(const KeyType& key, const ValueType& value) {
		if (!HashIsCorrect(hashFunction))
		{
			std::cout << "Hash fuction is bad\n";
			return;
		}
		int index = hashFunction->GetHash(key) % maxSize;
		if (index < 0) index = maxSize + index;
		
		items[index].Push(key, value);

	}

	ValueType Search(const KeyType& key) {
		if (!HashIsCorrect(hashFunction))
		{
			std::cout << "Hash fuction is bad\n";
			return NULL;
		}
		int index = hashFunction->GetHash(key) % maxSize;
		if (index < 0) index = maxSize + index;

		if (items[index].IsExists(key))
			return items[index].Search(key);
		else
			return NULL;


	}

	void Print() {
		if (items) {
			for (int i = 0; i < maxSize; i++) {
				items[i].Print();
			}
		}
	}


};