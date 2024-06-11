#pragma once

template<class KeyType, class DataType>
class AVL {

	enum Rotate { rotateLeft, rotateRight, rotateNone };

	struct Item {
		KeyType key;
		DataType data;
		Item* left;
		Item* right;
		int height;
		Item(KeyType key, DataType data, int height = 0) :
			key{ key }, data{ data }, height{ height },
			left{ nullptr }, right{ nullptr } {}
		friend std::ostream& operator<< (std::ostream& _out, Item*& item) {
			if (item == nullptr)
				return _out;
			if (item->left) {
				_out << item->left;
			}
			for (int i = 0; i < item->height; i++) _out << '*';
#ifdef PrintKey
			_out << item->key << '\n';
#else 
			_out << item->data << '\n';
#endif
			if (item->left) {
				_out << item->right;
			}
			return _out;
		}
	};

	Item* root;

	// Добавление новой ветви
	void Add(Item*& item, const KeyType& key, const DataType& data) {
		if (item == nullptr)
			item = new Item(key, data);
		else if (key < item->key)
			Add(item->left, key, data);
		else if (key > item->key)
			Add(item->right, key, data);
		else item->data = data;

		switch (rotateInf(item)) {
		case rotateRight:
			RotateRight(item);
			break;
		case rotateLeft:
			RotateLeft(item);
			break;
		case rotateNone:
			item->height = getHeight(item);
			break;
		default:
			throw std::exception("rotateInf is invalid");
		}
	}
	// Вспомогательный метод для балансировки
	Rotate rotateInf(Item* item) const {
		if (item == nullptr)
			throw std::exception("rotateInf is invalid");

		int left = (item->left ? item->left->height : -1);
		int right = (item->right ? item->right->height : -1);

		return
			left - right == 2 ? rotateRight
			: right - left == 2 ? rotateLeft
			: rotateNone;
	}
	// Получить высоту для ветви
	int getHeight(Item* item) const {
		if (item == nullptr) return -1;

		int left = (item->left ? item->left->height : -1);
		int right = (item->right ? item->right->height : -1);

		return (left > right ? left : right) + 1;
	}
	// Очистка дерева
	void Clear(Item*& item) {
		if (item->left) {
			Clear(item->left);
		}
		if (item->right) {
			Clear(item->right);
		}
		delete item;
		item = nullptr;
	}

	// Левое вращение
	bool RotateLeft(Item*& a) {
#ifdef DEBUG
		std::cout << '[' << a->key << ':' << a->data << "] rotate left\n";
#endif
		Item* b = a->right;
		Item* l = a->left;

		if (abs(getHeight(b) - getHeight(l)) != 2)
			return false;

		Item* c = b->left;
		Item* r = b->right;

		if (getHeight(c) <= getHeight(r)) {
			// Малое левое вращение
			a->right = c;
			a->height = getHeight(a);
			b->left = a;
			a = b;
			a->height = getHeight(a);
		}
		else {
			// Большое левое вращение
			Item* m = c->left;
			Item* n = c->right;

			a->right = m;
			a->height = getHeight(a);

			b->left = n;
			b->height = getHeight(b);

			c->left = a;
			a = c;
			a->right = b;
			a->height = getHeight(a);
		}
		return true;
	}
	// Правое вращение
	bool RotateRight(Item*& a) {
#ifdef DEBUG
		std::cout << '[' << a->key << ':' << a->data << "] rotate right\n";
#endif
		Item* b = a->left;
		Item* r = a->right;

		if (abs(getHeight(b) - getHeight(r)) != 2)
			return false;

		Item* l = b->left;
		Item* c = b->right;

		if (getHeight(c) <= getHeight(l)) {
			a->left = c;
			a->height = getHeight(a);

			b->right = a;
			a = b;
			a->height = getHeight(a);
		}
		else {
			Item* m = c->left;
			Item* n = c->right;

			a->left = n;
			a->height = getHeight(a);

			b->right = m;
			b->height = getHeight(b);

			c->right = a;
			a = c;
			a->left = b;
			a->height = getHeight(a);
		}

		return true;
	}

	// Поиск ключа, начиная с item
	Item* Search(const KeyType& key, Item* item) {
		return
			item == nullptr ? nullptr :
			key < item->key ? Search(item->left) :
			key > item->key ? Search(item->right) :
			item;
	}

public:

	AVL() :root{ nullptr } { }

	// Копирования

	// Перемещение
	AVL(AVL& avl) :root{ avl.root } {
		avl.root = nullptr;
	}

	~AVL() {
		Clear();
	}

	// Добавление
	void Push(const KeyType& key, const DataType& data) {
#ifdef DEBUG
		std::cout << "Add: " << key << ":" << data << '\n';
#endif
		Add(root, key, data);
	}
	// Добавление пар
	void Push(const std::pair<const KeyType&, const DataType&>& _pair) {
		Push(_pair.first, _pair.second);
	}
	// Очистка
	void Clear() {
		Clear(root);
	}


	friend std::ostream& operator<<(std::ostream& _out, AVL<KeyType, DataType>& avl) {
		for (int i = 0; i < avl.root->height + 3; i++) _out << '/';
		_out << '\n';
		_out << avl.root;
		for (int i = 0; i < avl.root->height + 3; i++) _out << '/';
		return _out;
	}
};