////////////// ������������ ������ � 4 - �������� ������ ������
#include <iostream>
#include <conio.h>
#include <set>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

int m_count = 0;
int subm_crT_count = 0;
int subm_pT_count = 0;
int size_count = 0;

bool fl_tree = FALSE;

void SetColor(int text, int bg) //������� ����� �����, ������ �� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Tree;

typedef struct _Nodes {
	void* value;
	struct _Nodes* next;
	struct _Nodes* prev;
} _Node;

typedef struct _DblLinkedList {
	size_t size;
	_Node* head;
	_Node* tail;
} DblLinkedList;

///////////////////////// PROTOTYPES //////////////////////////

void menu(Tree*& root, vector<int>& root_vec);
void submenu_create_tree(Tree*& root, vector<int>& root_vec);
void submenu_pass_tree(Tree*& root, vector<int>& root_vec);
void menu_choice(Tree*& root, vector<int>& root_vec);
void submenu_create_tree_choice(Tree*& root, vector<int>& root_vec);
void submenu_pass_tree_choice(Tree*& root, vector<int>& root_vec);
void conf_val(Tree*& root, vector<int>& root_vec);
void subconf_crT_val(Tree*& root, vector<int>& root_vec);

///////////////////////// PROTOTYPES //////////////////////////

///////////////////////// CHECK ////////////////////

int checkdigit() // �������� �� ���������� ����
{
	while (true)
	{
		int value;
		// ������ �����, ������� ����� ����������� � �������� �����
		cin >> value; // ����� �����
		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			cout << "������������ �������� �����. ������� ����� ���������" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			return value;
		}
	}
}

void gnomeSort(vector<int>& c) // ��� ���������� ����������������� ���� �������� ��� �����, ��������������� - ��� ������
{
	int index = 0;

	while (index < c.size()) {
		if (index == 0)
			index++;
		if (c[index] >= c[index - 1])
			index++;
		else {
			swap(c[index], c[index - 1]);
			index--;
		}
	}
	return;
}

int Search_Binary(vector<int>& digits_array, int left, int right, int key) {
	if(digits_array.size() != 1)
		gnomeSort(digits_array);
	bool counter = 1;
	int midd = 0;
	while (counter == 1) {
		midd = (left + right) / 2;

		if (key < digits_array[midd])       
			right = midd - 1;      
		else if (key > digits_array[midd])
			left = midd + 1;
		else
			return midd;  

		if (left > right)
			counter = 0;
	}
	return -1;
}

///////////////////////// CHECK ////////////////////

///////////////////////// QUEUE ////////////////////

DblLinkedList* createDblLinkedList() {
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteDblLinkedList(DblLinkedList** list) {
	_Node* tmp = (*list)->head;
	_Node* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

void* popFront(DblLinkedList* list) {
	_Node* prev;
	void* tmp;
	if (list->head == NULL) {
		exit(2);
	}

	prev = list->head;
	list->head = list->head->next;
	if (list->head) {
		list->head->prev = NULL;
	}
	if (prev == list->tail) {
		list->tail = NULL;
	}
	tmp = prev->value;
	free(prev);

	list->size--;
	return tmp;
}

void pushBack(DblLinkedList* list, void* value) {
	_Node* tmp = (_Node*)malloc(sizeof(_Node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

///////////////////////// QUEUE ////////////////////

///////////////////////// TREE /////////////////////

Tree* getFreeTree(int value, Tree* parent) {
	Tree* tmp = (Tree*)malloc(sizeof(Tree));
	tmp->left = tmp->right = NULL;
	tmp->data = value;
	tmp->parent = parent;
	return tmp;
}


void insert(Tree** head, int value) {
	Tree* tmp = NULL;
	Tree* ins = NULL;
	if (*head == NULL) {
		*head = getFreeTree(value, NULL);
		return;
	}

	tmp = *head;
	while (tmp) {
		if (value > tmp->data) {
			if (tmp->right) {
				tmp = tmp->right;
				continue;
			}
			else {
				tmp->right = getFreeTree(value, tmp);
				return;
			}
		}
		else if (value < tmp->data) {
			if (tmp->left) {
				tmp = tmp->left;
				continue;
			}
			else {
				tmp->left = getFreeTree(value, tmp);
				return;
			}
		}
		else {
			cout << value <<  " EQUAL " << tmp->data << endl;
			exit(2);
		}
	}
}

Tree* getMinTree(Tree* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

Tree* getMaxTree(Tree* root) {
	while (root->right) {
		root = root->right;
	}
	return root;
}

Tree* getTreeByValue(Tree* root, int value) {
	while (root) {
		if (root->data > value) {
			root = root->left;
			continue;
		}
		else if (root->data < value) {
			root = root->right;
			continue;
		}
		else {
			return root;
		}
	}
	return NULL;
}

void sizeTree(Tree* root) {
	if (root) {
		size_count++;
		sizeTree(root->left);
		sizeTree(root->right);
	}
}

Tree* deleteNode(Tree* root, int z) {   // ������ ���������, ��������� ����
	if (root == NULL)
		return root;
	if (z < root->data)
		root->left = deleteNode(root->left, z);
	else if (z > root->data)
		root->right = deleteNode(root->right, z);
	else if (root->left != NULL and root->right != NULL) {
		root->data = getMinTree(root->right)->data;
		root->right = deleteNode(root->right, root->data);
	}
	else {
		if (root->left != NULL)
			root = root->left;
		else if (root->right != NULL)
			root = root->right;
		else
			root = NULL;
	}
	return root;
	/////////////////////////////
}

void widthValue(int step, string object) {
	for (int i = 0; i <= step - 1; i++) {
		cout << "     ";
	}
	if (object == "right")
		cout << ".--->";
	else if (object == "left")
		cout << "`--->";
	else
		cout << "  -->";
}

void widthValue_file(int step, string object, ofstream& fout) {
	for (int i = 0; i <= step - 1; i++) {
		fout << "     ";
	}
	if (object == "right")
		fout << ".--->";
	else if (object == "left")
		fout << "`--->";
	else
		fout << "  -->";
}

///////////////////////// TREE /////////////////////

void printColorData(int current_data, int data) {
	if (current_data == data) {
		SetColor(2, 0);
		cout << current_data << endl;
		SetColor(7, 0);
	}
	else
		cout << current_data << endl;
}

void printTree_value(Tree* root, int step, string object, int value) {
	if (root->right) {
		printTree_value(root->right, step + 1, "right", value);
		widthValue(step, object);
		printColorData(root->data, value);
	}
	if (!root->right && root->left) {
		widthValue(step, object);
		printColorData(root->data, value);
		printTree_value(root->left, step + 1, "left", value);
		return;
	}
	if (root->left) {
		printTree_value(root->left, step + 1, "left", value);
		return;
	}
	if (root->right && !root->left)
		return;
	widthValue(step, object);
	printColorData(root->data, value);

}

void printTree(Tree* root, int step, string object) {
	if (root->right) {
		printTree(root->right, step + 1, "right");
		widthValue(step, object);
		cout << root->data << endl;
	}
	if (!root->right && root->left) {
		widthValue(step, object);
		cout << root->data << endl;
		printTree(root->left, step + 1, "left");
		return;
	}
	if (root->left) {
		printTree(root->left, step + 1, "left");
		return;
	}
	if (root->right && !root->left)
		return;
	widthValue(step, object);
	cout << root->data << endl;

}

void printTree_file(Tree* root, int step, string object, ofstream& fout) {
	if (root->right) {
		printTree_file(root->right, step + 1, "right", fout);
		widthValue_file(step, object, fout);
		fout << root->data << endl;
	}
	if (!root->right && root->left) {
		widthValue_file(step, object, fout);
		fout << root->data << endl;
		printTree_file(root->left, step + 1, "left", fout);
		return;
	}
	if (root->left) {
		printTree_file(root->left, step + 1, "left", fout);
		return;
	}
	if (root->right && !root->left)
		return;
	widthValue_file(step, object, fout);
	fout << root->data << endl;
}

void preOrderTravers(Tree* root) {
	if (root) {
		cout << root->data << " ";
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}

void postOrderTravers(Tree* root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		cout << root->data << " ";
	}
}

void breadthFirst(Tree* root) {
	DblLinkedList* q = createDblLinkedList();
	//��� ������ �������� � ������� ������
	pushBack(q, root);

	while (q->size != 0) {
		Tree* tmp = (Tree*)popFront(q);
		cout << root->data << " ";
		//���� ���� ����� ���������, �� �������� ��� � ������� ��� ���������� ���������
		if (tmp->left) {
			pushBack(q, tmp->left);
		}
		//���� ���� ������ ���������, �� �������� ��� � ������� ��� ���������� ���������
		if (tmp->right) {
			pushBack(q, tmp->right);
		}
	}
	deleteDblLinkedList(&q);
}

///////////////////////////// FILL /////////////////////

bool fill_set(set<int>& root_set, int value) {
	int temp, temp_value;
	temp = root_set.size();
	root_set.insert(value);
	if (temp != root_set.size())
		return TRUE;
	else
		return FALSE;
}

void fill_root_random(Tree*& root, vector<int>& root_vec) {
	system("cls"); // ������� �������
	root = NULL;
	root_vec.clear();
	int size = 0;
	int index = 0;
	chrono::steady_clock sc;
	set<int> root_set;

	cout << "������� ���������� ��������� � ������: ";
	size = checkdigit();
	if (size <= 0)
	{
		cout << "���������� ��������� ������ �� ����� ���� ������������� ��� �������. ������� ����� �������, ����� ����������.";
		_getch();
		menu(root, root_vec);
	}
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	while (index <= size - 1)
	{
		int temp = (rand() % 200) - 100;
		if (fill_set(root_set, temp)) {
			insert(&root, temp);
			root_vec.push_back(temp);
			index++;
		}
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "������ ������� �������. ������� ����� �������" << endl;
	_getch();
	fl_tree = TRUE;
	menu(root, root_vec);
}

void fill_root_self(Tree*& root, vector<int>& root_vec)
{
	system("cls"); // ������� �������
	root = NULL;
	root_vec.clear();
	int temp;
	int index = 0;
	chrono::steady_clock sc;
	bool fl_stop = TRUE;
	set <int> root_set;
	double summ_time = 0;
	cout << "������� �������� ��������. ���� ������ ���������, �� ������� ����� ���������� ������" << endl;
	
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // ����� �����

		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			fl_stop = FALSE;
		}
		else
		{
			cin.ignore(32767, '\n');
			if (fill_set(root_set, temp)) {
				auto start = sc.now();     
				insert(&root, temp);
				auto end = sc.now();      
				auto time_span = static_cast<chrono::duration<double>>(end - start);   
				summ_time += time_span.count();
				index++;
				root_vec.push_back(temp); // ��� ���������� ������� 
			}
			else {
				SetColor(4, 0);
				cout << "�������� �������� �� �����. ����� �������� ��� ���� � ������" << endl;
				SetColor(7, 0);
			}
		}
		
	}
	cout << "�������� �������� ������ �����: " << summ_time << " ������" << endl;

	cout << "������ ������� �������. ������� ����� �������" << endl;
	_getch();
	fl_tree = TRUE;
	menu(root, root_vec);
}

void fill_root_from_file(Tree*& root, vector<int>& root_vec)
{
	system("cls"); // ������� �������
	root = NULL;
	root_vec.clear();
	ifstream fin;
	chrono::steady_clock sc;
	set <int> root_set;
	vector<int> RepeatValues;

	fin.open("file_root.txt");
	auto start = sc.now();
	if (fin.is_open()) {
		int temp = 0;
		while (!fin.eof()) {
			fin >> temp;
			if (fin.fail()) {
				fin.clear();
				fin.ignore(32767, '\n');
				cout << "���� �������� ������������ �������� ������. ���������� ������� ��������� � ������ � ��������� ���� ������ ��������� (����� ��������� ���������� ������, ����������� ������ ���� �� ������)." << endl;
				cout << "������: 50 -3 45 14 0 4 10 1" << endl;
				cout << "�������, ����� ������� ���������" << endl;
				_getch();
				exit(3);
			}
			else {
				if (fill_set(root_set, temp)) {
					insert(&root, temp);
					root_vec.push_back(temp);
				}
				else
					RepeatValues.push_back(temp);
			}
		}
	}
	else {
		cout << "���� ������� �� �������! �������� ��������� � �������� � �������� ����� ��������� ���� file_root.txt ��� ���������� ������ ����� ����." << endl;
		cout << "�������, ����� ������� ���������" << endl;
		_getch();
		exit(3);
	}

	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	fin.close();
	if (RepeatValues.size() != 0) {
		cout << "������������� ��������: "; for (const auto& token : RepeatValues) { cout << token << " "; } cout << endl;
	}
	cout << "�������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "������ ������� �������. ������� ����� �������" << endl;
	_getch();
	fl_tree = TRUE;
	menu(root, root_vec);
}

void fill_root(vector<int>& arr, Tree* &root) {
	for (int i = 0; i < arr.size(); i++) {
		insert(&root, arr[i]);
	}
}

void individual_ex(Tree*& root, int level) {
	if (root) {
		if (level % 2 == 0) { // ��������� �� 1 �� 5
			int temp = (rand() % 5) + 1;
			cout << "������� ����� " << root->data << " ����� �������� �� " << temp << endl;
			root->data *= temp;
		}
		else {
			int value;
			cout << "������� ��������, �� ������� ����� ��������� ������� ����� " << root->data << ": " << endl;
			value = checkdigit();
			root->data -= value;
		}
		individual_ex(root->left, level + 1);
		individual_ex(root->right, level + 1);
	}
}

void fill_set_via_Tree(Tree*& root, set<int>& arr) {
	if (root) {
		arr.insert(root->data);
		fill_set_via_Tree(root->right, arr);
		fill_set_via_Tree(root->left, arr);
	}
}

void fill_vec_via_Tree(Tree*& root, vector<int>& arr) {
	if (root) {
		arr.push_back(root->data);
		fill_vec_via_Tree(root->right, arr);
		fill_vec_via_Tree(root->left, arr);
	}
}

///////////////////////////// FILL /////////////////////

Tree* getTreeNoRepeatValues(Tree*& root) {
	Tree* tmp = NULL;
	set <int> TreeVal;
	vector <int> numbers_unic;
	vector<int> CopyTree;
	fill_vec_via_Tree(root, CopyTree);
	vector <int> RepeatValues;

	for (int i = 0; i < CopyTree.size(); i++) {
		int temp = TreeVal.size();
		int temp_value = CopyTree[i];
		TreeVal.insert(temp_value);
		if (temp != TreeVal.size())
			numbers_unic.push_back(temp_value);
		else
			RepeatValues.push_back(temp_value);
	}
	if (CopyTree.size() != numbers_unic.size()) {
		cout << "������ ����� ������������� ����. ��� ���� ���� �������" << endl;
		cout << "������������� ��������: "; for (const auto& token : RepeatValues) { cout << token << " "; } cout << endl;
		fill_root(numbers_unic, tmp);
		return tmp;
	}
	return root;
}

void delete_node(Tree*& root, vector<int>& root_vec) {
	system("cls");

	int value;
	int prev_count ;
	chrono::steady_clock sc;

	size_count = 0;
	sizeTree(root);
	prev_count = size_count;
	size_count = 0;

	cout << setw(50) << right << "�������� ������:" << endl;
	printTree(root, 0, " ");
	cout << "������� �������, ������� ���������� �������: ";
	value = checkdigit();
	auto start = sc.now();
	root = deleteNode(root, value);
	sizeTree(root);
	if (size_count == prev_count) {
		cout << "�������� �� �������. ������� ����� �������, ����� ����������" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	auto start1 = sc.now();
	int fValue = Search_Binary(root_vec, 0, root_vec.size(), value);
	if (fValue == -1) {
		cout << "�������� �� �������. ������� ����� �������, ����� ����������" << endl;
		_getch();
		menu(root, root_vec);
	}
	else
		root_vec.erase(root_vec.begin() + fValue);

	auto end1 = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ���� �����: " << time_span.count() << " ������" << endl;
	cout << "�������� �������� �������� ������� �����: " << time_span1.count() << " ������" << endl;
	cout << "���� ������� ������. ������� ����� �������" << endl;
	if (!root) {
		SetColor(4, 0);
		cout << "������ ���� ��������� �������." << endl;
		SetColor(7, 0);
		fl_tree = FALSE;
	}
	_getch();
	menu(root, root_vec);
}

void insert_node(Tree*& root, vector<int>& root_vec) {
	system("cls");

	int value;
	chrono::steady_clock sc;
	set<int> root_set;
	double time = 0;

	fill_set_via_Tree(root, root_set);
	if (root) {
		cout << setw(50) << right << "�������� ������:" << endl;
		printTree(root, 0, " ");
	}
	cout << "������� �������� ��������: ";
	value = checkdigit();
	if (fill_set(root_set, value)) {
		auto start = sc.now();
		insert(&root, value);
		auto end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - start);
		time += time_span.count();
	}
	else {
		SetColor(4, 0);
		cout << "�������� �������� �� �����. ����� �������� ��� ���� � ������" << endl;
		SetColor(7, 0);
		cout <<	"������� ����� �������, ����� ����������" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto start1 = sc.now();
	root_vec.push_back(value);
	auto end1 = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // ����������� �����, ����������� �� �������

	cout << "�������� ������� ���� �����: " << time << " ������" << endl;
	cout << "�������� ������� �������� ������� �����: " << time_span1.count() << " ������" << endl;
	cout << "���� ������� ��������. ������� ����� �������" << endl;
	_getch();
	menu(root, root_vec);
}

void find_node(Tree*& root, vector<int>& root_vec) {
	system("cls");

	int value;
	chrono::steady_clock sc;
	Tree* findTree = NULL;


	cout << setw(50) << right << "�������� ������:" << endl;
	printTree(root, 0, " ");
	cout << "������� �������, ������� ���������� �����: ";
	value = checkdigit();
	auto start = sc.now();
	findTree = getTreeByValue(root, value);
	if (findTree == NULL) {
		cout << "�������� �� �������. ������� ����� �������, ����� ����������" << endl;
		_getch();
		menu(root, root_vec);
	}
	else {
	/*	cout << setw(50) << right << "�������� ������ � �������� " << findTree->data << ":" << endl;
		printTree_value(root, 0, " ", findTree->data);*/
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	auto start1 = sc.now();
	int fValue = Search_Binary(root_vec, 0, root_vec.size(), value);
	if (fValue == -1) {
		cout << "�������� �� �������. ������� ����� �������, ����� ����������" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto end1 = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // ����������� �����, ����������� �� �������
	cout << "�������� ������ ���� �����: " << time_span.count() << " ������" << endl;
	cout << "�������� ������ �������� ������� �����: " << time_span1.count() << " ������" << endl;
	cout << "���� ������� ������. ������� ����� �������" << endl;
	_getch();
	menu(root, root_vec);
}

void individual(Tree*& root, vector<int>& root_vec) {
	system("cls");
	chrono::steady_clock sc;

	cout << setw(50) << right << "�������������� �������" << endl;
	cout << setw(70) << right << "��������� ������ �������� ������� �� ��������, ��������� �������������." << endl;
	cout << setw(70) << right << "������ ������ ������� �������� �� ��������� �������� � ��������� �� 1 �� 5." << endl;
	SetColor(6, 0);
	cout << setw(55) << right << "������� ����� �������, ����� ������.";
	SetColor(7, 0);
	_getch();
	cout << endl;

	cout << setw(50) << right << "�������� ������:" << endl;
	printTree(root, 0, " "); cout << endl;
	auto start = sc.now();
	individual_ex(root, 0);
	root = getTreeNoRepeatValues(root);
	cout << setw(50) << right << "���������� �������� ������:" << endl;
	printTree(root, 0, " "); cout << endl;
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� ������ ������ �����: " << time_span.count() << " ������" << endl;
	cout << "�������������� ������� ���������. ������� ����� �������" << endl;
	_getch();
	menu(root, root_vec);
}

///////////////// MENU ////////////////////

void print_alarm(Tree*& root, vector<int>& root_vec) {
	SetColor(4, 0);
	cout << endl << "������ ���������� ������� ������. ������� ����� �������";
	SetColor(7, 0);
	_getch();
	submenu_create_tree(root, root_vec);
}

void subconf_pT_val(Tree*& root, vector<int>& root_vec) {
	if (subm_pT_count == 3)
		menu(root, root_vec);
	system("cls");
	cout << setw(50) << right << "�������� ������:" << endl;
	printTree(root, 0, " "); cout << endl;
	switch (subm_pT_count) {
	case 0: {
		cout << "������ ����� ������: ";
		preOrderTravers(root);
		break;
	}
	case 1: {
		cout << "�������� ����� ������ ����� ������: ";
		postOrderTravers(root);
		break;
	}
	case 2: {
		cout << "������ ����� ������: ";
		breadthFirst(root);
		break;
	}
	case 3:
		menu(root, root_vec);
		break;
	default:
		break;
	}
	cout << endl;
	SetColor(2, 0);
	cout << "����� ��������. ������� ����� �������, ����� ��������� � ����.";
	SetColor(7, 0);
	_getch();
	menu(root, root_vec);
}

void subconf_crT_val(Tree*& root, vector<int>& root_vec) {
	switch (subm_crT_count) {
	case 0:
		fill_root_random(root, root_vec);
		break;
	case 1:
		fill_root_self(root, root_vec);
		break;
	case 2:
		fill_root_from_file(root, root_vec);
		break;
	case 3:
		menu(root, root_vec);
		break;
	default:
		break;
	}
}

void conf_val(Tree*& root, vector<int>& root_vec) {
	switch (m_count) {
	case 0:
		submenu_create_tree(root, root_vec);
		break;
	case 1:
		insert_node(root, root_vec);
		break;
	case 2:
		if (fl_tree)
			delete_node(root,root_vec);
		else
			print_alarm(root, root_vec);
		break;
	case 3:
		if (fl_tree)
			find_node(root, root_vec);
		else
			print_alarm(root, root_vec);
		break;
	case 4:
		if (fl_tree) {
			ofstream fout;
			fout.open("tree.txt", ios::trunc);
			system("cls");
			cout << setw(50) << right << "�������� ������:" << endl;
			fout << setw(50) << right << "�������� ������:" << endl;
			printTree(root, 0, " ");
			printTree_file(root, 0, " ", fout);
			cout << "�������� ������ ���� ��������� � ����� tree.txt" << endl;
			cout << "������� ����� �������, ����� ��������� � ����.";
			_getch();
			fout.close();
		}
		else
			print_alarm(root, root_vec);
		break;
	case 5:
		if (fl_tree)
			submenu_pass_tree(root, root_vec);
		else
			print_alarm(root, root_vec);
		break;
	case 6:
		if (fl_tree)
			individual(root, root_vec);
		else
			print_alarm(root, root_vec);
		break;
	case 7:
		SetColor(0, 0);
		exit(0);
		break;
	default:
		break;
	}
	menu(root, root_vec);
}

void submenu_pass_tree_choice(Tree*& root, vector<int>& root_vec) {
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) { // ���� �������
		switch (k1) {
		case 0x48: // ������� �����
			subm_pT_count--;
			if (subm_pT_count < 0) subm_pT_count = 0;
			submenu_pass_tree(root, root_vec);
			break;

		case 0x50: // ������� ����
			subm_pT_count++;
			if (subm_pT_count > 3) subm_pT_count = 3;
			submenu_pass_tree(root, root_vec);
			break;
		case 0xD: // �����������
			subconf_pT_val(root, root_vec);
			break;
		default:
			submenu_pass_tree_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // ������� �����
		subm_pT_count--;
		if (subm_pT_count < 0) subm_pT_count = 0;
		submenu_pass_tree(root, root_vec);
		break;

	case 0x50: // ������� ����
		subm_pT_count++;
		if (subm_pT_count > 3) subm_pT_count = 3;
		submenu_pass_tree(root, root_vec);
		break;
	case 0xD: // �����������
		subconf_pT_val(root, root_vec);
		break;
	default:
		submenu_pass_tree_choice(root, root_vec);
	}
}

void submenu_create_tree_choice(Tree*& root, vector<int>& root_vec) {
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) { // ���� �������
		switch (k1) {
		case 0x48: // ������� �����
			subm_crT_count--;
			if (subm_crT_count < 0) subm_crT_count = 0;
			submenu_create_tree(root, root_vec);
			break;

		case 0x50: // ������� ����
			subm_crT_count++;
			if (subm_crT_count > 3) subm_crT_count = 3;
			submenu_create_tree(root, root_vec);
			break;
		case 0xD: // �����������
			subconf_crT_val(root, root_vec);
			break;
		default:
			submenu_create_tree_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // ������� �����
		subm_crT_count--;
		if (subm_crT_count < 0) subm_crT_count = 0;
		submenu_create_tree(root, root_vec);
		break;

	case 0x50: // ������� ����
		subm_crT_count++;
		if (subm_crT_count > 3) subm_crT_count = 3;
		submenu_create_tree(root, root_vec);
		break;
	case 0xD: // �����������
		subconf_crT_val(root, root_vec);
		break;
	default:
		submenu_create_tree_choice(root, root_vec);
	}
}

void menu_choice(Tree*& root, vector<int>&root_vec) {
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) { // ���� �������
		switch (k1) {
		case 0x48: // ������� �����
			m_count--;
			if (m_count < 0) m_count = 0;
			menu(root, root_vec);
			break;

		case 0x50: // ������� ����
			m_count++;
			if (m_count > 7) m_count = 7;
			menu(root, root_vec);
			break;
		case 0xD: // �����������
			conf_val(root, root_vec);
			break;
		default:
			menu_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // ������� �����
		m_count--;
		if (m_count < 0) m_count = 0;
		menu(root, root_vec);
		break;

	case 0x50: // ������� ����
		m_count++;
		if (m_count > 7) m_count = 7;
		menu(root, root_vec);
		break;
	case 0xD: // �����������
		conf_val(root, root_vec);
		break;
	default:
		menu_choice(root, root_vec);
	}
}

void submenu_pass_tree(Tree*& root, vector<int>& root_vec) {
	system("cls"); // ������� �������

	if (subm_pT_count == 0) {
		cout << right << "__����� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������ ������ ������ ������������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "������ �����" << endl;
		SetColor(7, 0);
		cout << "�������� �����" << endl;
		cout << "����� � ������ ������" << endl;
		cout << "�����" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 1) {
		cout << right << "__����� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������ ������ ������ ������������?" << endl << endl;
		SetColor(7, 0);
		cout << "������ �����" << endl;
		SetColor(5, 0);
		cout << "�������� �����" << endl;
		SetColor(7, 0);
		cout << "����� � ������ ������" << endl;
		cout << "�����" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 2) {
		cout << right << "__����� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������ ������ ������ ������������?" << endl << endl;
		SetColor(7, 0);
		cout << "������ �����" << endl;
		cout << "�������� �����" << endl;
		SetColor(5, 0);
		cout << "����� � ������ ������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 3) {
		cout << right << "__����� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������ ������ ������ ������������?" << endl << endl;
		SetColor(7, 0);
		cout << "������ �����" << endl;
		cout << "�������� �����" << endl;
		cout << "����� � ������ ������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_pass_tree_choice(root, root_vec);
	}

}

void submenu_create_tree(Tree*& root, vector<int>& root_vec) {
	system("cls"); // ������� �������

	if (subm_crT_count == 0) {
		cout << right << "__�������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(7, 0);
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 1) {
		cout << right << "__�������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(5, 0);
		cout << "�������, �������� ��������" << endl;
		SetColor(7, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 2) {
		cout << right << "__�������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		SetColor(5, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 3) {
		cout << right << "__�������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_create_tree_choice(root, root_vec);
	}
}

void menu(Tree*& root, vector<int>& root_vec) {
	system("cls"); // ������� �������

	if (m_count == 0) {
		cout << setw(15) << right << "__����__" << endl;
		SetColor(5, 0);
		cout << "������� ������" << endl;
		SetColor(7, 0);
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 1) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		SetColor(5, 0);
		cout << "�������� ������� � ������" << endl;
		SetColor(7, 0);
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 2) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		SetColor(5, 0);
		cout << "������� ������� ������" << endl;
		SetColor(7, 0);
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 3) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		SetColor(5, 0);
		cout << "�������� ������� ������" << endl;
		SetColor(7, 0);
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 4) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		SetColor(5, 0);
		cout << "������� ������" << endl;
		SetColor(7, 0);
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 5) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		SetColor(5, 0);
		cout << "������ ������" << endl;
		SetColor(7, 0);
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 6) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		SetColor(5, 0);
		cout << "������� �� ��������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 7) {
		cout << setw(15) << right << "__����__" << endl;
		cout << "������� ������" << endl;
		cout << "�������� ������� � ������" << endl;
		cout << "������� ������� ������" << endl;
		cout << "�������� ������� ������" << endl;
		cout << "������� ������" << endl;
		cout << "������ ������" << endl;
		cout << "������� �� ��������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		menu_choice(root, root_vec);
	}
}

///////////////// MENU ////////////////////

int main() {
	setlocale(0, "");
	srand(time(NULL));
	Tree* root = NULL;
	vector<int> root_vec;

	menu(root, root_vec);

	_getch();
	return 0;
}