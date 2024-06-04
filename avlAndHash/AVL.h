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
			_out << "{K: " << item->key << ", D: " << item->data << "}";
			if (item->left) {
				_out << item->right;
			}
			return _out;
		}
	};

	Item* begin;

	void Add(Item*& item, KeyType key, DataType data) {
		if (!item)
			item = new Item(key, data);
		if (key < item->key)
			Add(item->left);
	}

	// ������� ������
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
public:

	AVL() :begin{ nullptr } { }

	// �����������

	// �����������
	AVL(AVL& avl) :begin{ avl.begin } {
		avl.begin = nullptr;
	}

	~AVL() {
		Clear();
	}

	// ����������
	void Push(const KeyType& key, const DataType& data) {
		if (begin == nullptr) {
			begin = new Item(key, data);
			return;
		}

		Item* ptr = begin;
		bool added = false;
		while (!added)
		{
			if (key < ptr->key) {
				if (ptr->left)
					ptr = ptr->left;
				else {
					ptr->left = new Item(key, data);
					added = true;
				}
			}
			else
				if (key == ptr->key) {
					ptr->data = data;
					added = true;
				}
				else
					if (ptr->right)
						ptr = ptr->right;
					else
					{
						ptr->right = new Item(key, data);
						added = true;
					}
		}
	}
	void Push(const std::pair<const KeyType&, const DataType&>& _pair) {
		Push(_pair.first, _pair.second);
	}
	// ��������� / ��������
	void Pop(const KeyType& key) {
		//DataType r;
		if (begin->key == key) {
			//r = begin->data;
			Item* item = begin;
			if (begin->left == nullptr)
				begin = begin->right;
			else
				begin = begin->left;
			delete item;
			//return r;
		}
		Item* item = Search(key, begin);
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
		// TODO: �������� ������ � ��������� �����

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
		Clear(begin);
	}

	// ����� ������
	void Print(const Item*& item) const {
		if (item) {
			Print(item->left);
			std::cout << item << ' ';
			Print(item->right);
		}
	}

	// ������ ������
	int Height(const Item*& item) {
		const Item* ptr = item;
		int left = Height(ptr->left);
		int rigth = Height(ptr->rigth);
		return 1 + (left > rigth ? left : rigth);
	}

	friend std::ostream& operator<<(std::ostream& _out, AVL<KeyType, DataType>& avl) {
		_out << avl.begin;
		return _out;
	}
};