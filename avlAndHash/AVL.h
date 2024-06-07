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
		item->height = maxHeight(item)+1;
	}
	// Добавление существующей ветви
	void Add(Item*& item, Item* added) {
		if (item == nullptr)
			item = added;
		else if (added->key < item->key)
			Add(item->left, added);
		else if (added->key > item->key)
			Add(item->rigth, added);
		item->height = maxHeight(item);
	}
	int maxHeight(Item* item) const {
		if (item == nullptr) return -1;
		int left = (item->left ? item->left->height : -1);
		int right = (item->right ? item->right->height : -1);
		return (left > right ? left : right);
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

	void Print(Item* item,const char* symbol) const {
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

	void RotateLeft() {

	}

	// Вывод дерева
	void Print(const char* symbol = " ") const {
		Print(root,symbol);
	}

	friend std::ostream& operator<<(std::ostream& _out, AVL<KeyType, DataType>& avl) {
		for (int i = 0; i < avl.root->height+3; i++) _out << '/';
		_out << '\n';
		_out << avl.root;
		for (int i = 0; i < avl.root->height+3; i++) _out << '/';
		return _out;
	}
};