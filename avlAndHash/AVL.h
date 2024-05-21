#pragma once

template<class keyType, class dataType>
class AVL {
	struct Item {
		keyType key;
		dataType data;
		Item* left;
		Item* right;
		Item(key, data) :
			key{ key }, data{ data }, 
			left{ nullptr }, right{ nullptr } {}
	};
	
	Item* begin;

	void Add(Item*& item, keyType key, dataType data) {
		if (!item)
			item = new Item(key, data);
		if (key < item->key)
			Add(item->left);
	}

public:

	AVL() :begin{ nullptr } { }

	// Копирования

	// Перемещение
	AVL(AVL& avl) :begin{ avl.begin } {
		avl.begin = nullptr;
	}
	
	~AVL() {
		Clear();
	}

	// Добавление
	void Push(keyType key, dataType data) {
		
	}

	// Получение / удаление
	dataType Pop(keyType key) {

	}

	// Очистка дерева
	void Clear(Item*& item = begin) {
		if (item->left) {
			Clear(item->left);
		}
		if (item->right) {
			Clear(item->right);
		}
		delete item;
		item = nullptr;
	}
};