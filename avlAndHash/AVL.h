#pragma once

template<class KeyType, class DataType>
class AVL {
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
			_out << item->key << '\n';
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
		int rt = rotateInf(item);
		if (rt == 2)
			RotateRight(item);
		else if (rt == -2)
			RotateLeft(item);
		else
			item->height = getHeight(item);
	}

	int rotateInf(Item* item) const {
		if (item == nullptr)
			return 0;

		int left = (item->left ? item->left->height : -1);
		int right = (item->right ? item->right->height : -1);

		return left - right;
	}

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

	void Print(Item* item, const char* symbol) const {
		if (item) {
			Print(item->left, symbol);
			for (int i = 0; i < item->height; i++) std::cout << symbol;
			std::cout << item->data << '\n';
			Print(item->right, symbol);
		}
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
		std::cout << "Add: " << key << ":" << data << '\n';
		Add(root, key, data);
	}

	void Push(const std::pair<const KeyType&, const DataType&>& _pair) {
		Push(_pair.first, _pair.second);
	}
	// Удаление
	void Pop(const KeyType& key) {
		//DataType r;
		// Начало
		if (root->key == key) {
			//r = begin->data;
			Item* item = root;
			if (root->left == nullptr)
				root = root->right;
			else
				root = root->left;
			delete item;
			//return r;
		}
		// Ищем "до" ветвь
		Item* item = Search(key, root);
		if (item == nullptr)
			return;

		Item* del;
		Item* ptr;
		bool bLeft = false;
		if (item->left->key == key) {
			del = item->left;
			bLeft = true;
		}
		else
			del = item->right;

		Item* left = del->left;
		Item* right = del->right;
		// TODO: Сравнить высоты и поставить верно

		if (bLeft)
		{
			item->left = right;
			ptr = right;
		}
		else {
			item->right = left;
			ptr = left;
		}

		bool added = false;
		while (!added)
		{
			if (left->key < ptr->key) {
				if (ptr->left)
					ptr = ptr->left;
				else {
					ptr->left = left;
					added = true;
				}
			}
			else
				if (ptr->right)
					ptr = ptr->right;
				else
				{
					ptr->right = left;
					added = true;
				}
		}

		delete del;

	}

	Item* Search(const KeyType& key, Item* item) {
		if (item == nullptr)
			return nullptr;

		if (item->left != nullptr)
			if (key == item->left->key)
				return item;
		if (item->right != nullptr)
			if (key == item->right->key)
				return item;

		if (key > item->key)
			return Search(key, item->right);
		else
			return Search(key, item->left);
	}

	void Clear() {
		Clear(root);
	}
	// Левое вращение
	bool RotateLeft(Item*& a) {
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

	// Вывод дерева
	void Print(const char* symbol = " ") const {
		Print(root, symbol);
	}

	friend std::ostream& operator<<(std::ostream& _out, AVL<KeyType, DataType>& avl) {
		for (int i = 0; i < avl.root->height + 3; i++) _out << '/';
		_out << '\n';
		_out << avl.root;
		for (int i = 0; i < avl.root->height + 3; i++) _out << '/';
		return _out;
	}
};