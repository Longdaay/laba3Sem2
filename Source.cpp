////////////// Лабораторная работа № 4 - Бинарное дерево поиска
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

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
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

int checkdigit() // проверка на корректный ввод
{
	while (true)
	{
		int value;
		// вводим число, которое хотим представить в двоичной форме
		cin >> value; // число целое
		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			cout << "Недопустимое заданное число. Введите число правильно" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
			return value;
		}
	}
}

void gnomeSort(vector<int>& c) // при нахождении неотсортированной пары делается шаг назад, отсортированной - шаг вперед
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

Tree* deleteNode(Tree* root, int z) {   // корень поддерева, удаляемый ключ
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
	//Для начала поместим в очередь корень
	pushBack(q, root);

	while (q->size != 0) {
		Tree* tmp = (Tree*)popFront(q);
		cout << root->data << " ";
		//Если есть левый наследник, то помещаем его в очередь для дальнейшей обработки
		if (tmp->left) {
			pushBack(q, tmp->left);
		}
		//Если есть правый наследник, то помещаем его в очередь для дальнейшей обработки
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
	system("cls"); // очищаем консоль
	root = NULL;
	root_vec.clear();
	int size = 0;
	int index = 0;
	chrono::steady_clock sc;
	set<int> root_set;

	cout << "Введите количество элементов в дереве: ";
	size = checkdigit();
	if (size <= 0)
	{
		cout << "Количество элементов дерева не может быть отрицательным или нулевым. Нажмите любую клавишу, чтобы продолжить.";
		_getch();
		menu(root, root_vec);
	}
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	while (index <= size - 1)
	{
		int temp = (rand() % 200) - 100;
		if (fill_set(root_set, temp)) {
			insert(&root, temp);
			root_vec.push_back(temp);
			index++;
		}
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость создания дерева равна: " << time_span.count() << " секунд" << endl;

	cout << "Дерево успешно создано. Нажмите любую клавишу" << endl;
	_getch();
	fl_tree = TRUE;
	menu(root, root_vec);
}

void fill_root_self(Tree*& root, vector<int>& root_vec)
{
	system("cls"); // очищаем консоль
	root = NULL;
	root_vec.clear();
	int temp;
	int index = 0;
	chrono::steady_clock sc;
	bool fl_stop = TRUE;
	set <int> root_set;
	double summ_time = 0;
	cout << "Вводите числовые значения. Если хотите закончить, то введите любой нечисловой символ" << endl;
	
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // число целое

		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
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
				root_vec.push_back(temp); // для заполнения вектора 
			}
			else {
				SetColor(4, 0);
				cout << "Значение записано не будет. Такое значение уже есть в дереве" << endl;
				SetColor(7, 0);
			}
		}
		
	}
	cout << "Скорость создания дерева равна: " << summ_time << " секунд" << endl;

	cout << "Дерево успешно создано. Нажмите любую клавишу" << endl;
	_getch();
	fl_tree = TRUE;
	menu(root, root_vec);
}

void fill_root_from_file(Tree*& root, vector<int>& root_vec)
{
	system("cls"); // очищаем консоль
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
				cout << "Файл содержит некорректные числовые данные. Необходимо закрыть программу и ввести в текстовый файл данные корректно (между числовыми значениями пробел, посторонних знаков быть не должно)." << endl;
				cout << "Пример: 50 -3 45 14 0 4 10 1" << endl;
				cout << "Нажмите, чтобы закрыть программу" << endl;
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
		cout << "Файл открыть не удалось! Закройте программу и создайте в корневой папке программы файл file_root.txt для заполнения дерева через файл." << endl;
		cout << "Нажмите, чтобы закрыть программу" << endl;
		_getch();
		exit(3);
	}

	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	fin.close();
	if (RepeatValues.size() != 0) {
		cout << "Повторяющиеся элементы: "; for (const auto& token : RepeatValues) { cout << token << " "; } cout << endl;
	}
	cout << "Скорость создания дерева равна: " << time_span.count() << " секунд" << endl;

	cout << "Дерево успешно создано. Нажмите любую клавишу" << endl;
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
		if (level % 2 == 0) { // добавляем от 1 до 5
			int temp = (rand() % 5) + 1;
			cout << "Текущее число " << root->data << " будет умножено на " << temp << endl;
			root->data *= temp;
		}
		else {
			int value;
			cout << "Введите значение, на которое нужно уменьшить текущее число " << root->data << ": " << endl;
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
		cout << "Дерево имеет повторяющиеся узлы. Эти узлы были удалены" << endl;
		cout << "Повторяющиеся элементы: "; for (const auto& token : RepeatValues) { cout << token << " "; } cout << endl;
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

	cout << setw(50) << right << "Бинарное дерево:" << endl;
	printTree(root, 0, " ");
	cout << "Введите элемент, который необходимо удалить: ";
	value = checkdigit();
	auto start = sc.now();
	root = deleteNode(root, value);
	sizeTree(root);
	if (size_count == prev_count) {
		cout << "Значение не найдено. Нажмите любую клавишу, чтобы продолжить" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	auto start1 = sc.now();
	int fValue = Search_Binary(root_vec, 0, root_vec.size(), value);
	if (fValue == -1) {
		cout << "Значение не найдено. Нажмите любую клавишу, чтобы продолжить" << endl;
		_getch();
		menu(root, root_vec);
	}
	else
		root_vec.erase(root_vec.begin() + fValue);

	auto end1 = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // высчитываем время, затраченное на событие
	cout << "Скорость удаления узла равна: " << time_span.count() << " секунд" << endl;
	cout << "Скорость удаления элемента массива равна: " << time_span1.count() << " секунд" << endl;
	cout << "Узел успешно удален. Нажмите любую клавишу" << endl;
	if (!root) {
		SetColor(4, 0);
		cout << "Дерево было полностью удалено." << endl;
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
		cout << setw(50) << right << "Бинарное дерево:" << endl;
		printTree(root, 0, " ");
	}
	cout << "Введите значение элемента: ";
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
		cout << "Значение записано не будет. Такое значение уже есть в дереве" << endl;
		SetColor(7, 0);
		cout <<	"Нажмите любую клавишу, чтобы продолжить" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto start1 = sc.now();
	root_vec.push_back(value);
	auto end1 = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // высчитываем время, затраченное на событие

	cout << "Скорость вставки узла равна: " << time << " секунд" << endl;
	cout << "Скорость вставки элемента массива равна: " << time_span1.count() << " секунд" << endl;
	cout << "Узел успешно вставлен. Нажмите любую клавишу" << endl;
	_getch();
	menu(root, root_vec);
}

void find_node(Tree*& root, vector<int>& root_vec) {
	system("cls");

	int value;
	chrono::steady_clock sc;
	Tree* findTree = NULL;


	cout << setw(50) << right << "Бинарное дерево:" << endl;
	printTree(root, 0, " ");
	cout << "Введите элемент, который необходимо найти: ";
	value = checkdigit();
	auto start = sc.now();
	findTree = getTreeByValue(root, value);
	if (findTree == NULL) {
		cout << "Значение не найдено. Нажмите любую клавишу, чтобы продолжить" << endl;
		_getch();
		menu(root, root_vec);
	}
	else {
	/*	cout << setw(50) << right << "Бинарное дерево и значение " << findTree->data << ":" << endl;
		printTree_value(root, 0, " ", findTree->data);*/
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	auto start1 = sc.now();
	int fValue = Search_Binary(root_vec, 0, root_vec.size(), value);
	if (fValue == -1) {
		cout << "Значение не найдено. Нажмите любую клавишу, чтобы продолжить" << endl;
		_getch();
		menu(root, root_vec);
	}
	auto end1 = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // высчитываем время, затраченное на событие
	cout << "Скорость поиска узла равна: " << time_span.count() << " секунд" << endl;
	cout << "Скорость поиска элемента массива равна: " << time_span1.count() << " секунд" << endl;
	cout << "Узел успешно найден. Нажмите любую клавишу" << endl;
	_getch();
	menu(root, root_vec);
}

void individual(Tree*& root, vector<int>& root_vec) {
	system("cls");
	chrono::steady_clock sc;

	cout << setw(50) << right << "Индивидуальное задание" << endl;
	cout << setw(70) << right << "Уменьшить каждый нечетный элемент на значение, введенное пользователем." << endl;
	cout << setw(70) << right << "Каждый четный элемент умножьте на случайную величину в диапазоне от 1 до 5." << endl;
	SetColor(6, 0);
	cout << setw(55) << right << "Нажмите любую клавишу, чтобы начать.";
	SetColor(7, 0);
	_getch();
	cout << endl;

	cout << setw(50) << right << "Бинарное дерево:" << endl;
	printTree(root, 0, " "); cout << endl;
	auto start = sc.now();
	individual_ex(root, 0);
	root = getTreeNoRepeatValues(root);
	cout << setw(50) << right << "Измененное бинарное дерево:" << endl;
	printTree(root, 0, " "); cout << endl;
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость работы дерева равна: " << time_span.count() << " секунд" << endl;
	cout << "Преобразование успешно завершено. Нажмите любую клавишу" << endl;
	_getch();
	menu(root, root_vec);
}

///////////////// MENU ////////////////////

void print_alarm(Tree*& root, vector<int>& root_vec) {
	SetColor(4, 0);
	cout << endl << "Сперва необходимо создать дерево. Нажмите любую клавишу";
	SetColor(7, 0);
	_getch();
	submenu_create_tree(root, root_vec);
}

void subconf_pT_val(Tree*& root, vector<int>& root_vec) {
	if (subm_pT_count == 3)
		menu(root, root_vec);
	system("cls");
	cout << setw(50) << right << "Бинарное дерево:" << endl;
	printTree(root, 0, " "); cout << endl;
	switch (subm_pT_count) {
	case 0: {
		cout << "Прямой обход дерева: ";
		preOrderTravers(root);
		break;
	}
	case 1: {
		cout << "Обратный обход дерева обход дерева: ";
		postOrderTravers(root);
		break;
	}
	case 2: {
		cout << "Прямой обход дерева: ";
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
	cout << "Обход выполнен. Нажмите любую клавишу, чтобы вернуться в меню.";
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
			cout << setw(50) << right << "Бинарное дерево:" << endl;
			fout << setw(50) << right << "Бинарное дерево:" << endl;
			printTree(root, 0, " ");
			printTree_file(root, 0, " ", fout);
			cout << "Бинарное дерево было сохранено в файле tree.txt" << endl;
			cout << "Нажмите любую клавишу, чтобы вернуться в меню.";
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
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) { // если стрелки
		switch (k1) {
		case 0x48: // стрелка вверх
			subm_pT_count--;
			if (subm_pT_count < 0) subm_pT_count = 0;
			submenu_pass_tree(root, root_vec);
			break;

		case 0x50: // стрелка вниз
			subm_pT_count++;
			if (subm_pT_count > 3) subm_pT_count = 3;
			submenu_pass_tree(root, root_vec);
			break;
		case 0xD: // подтвердить
			subconf_pT_val(root, root_vec);
			break;
		default:
			submenu_pass_tree_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // стрелка вверх
		subm_pT_count--;
		if (subm_pT_count < 0) subm_pT_count = 0;
		submenu_pass_tree(root, root_vec);
		break;

	case 0x50: // стрелка вниз
		subm_pT_count++;
		if (subm_pT_count > 3) subm_pT_count = 3;
		submenu_pass_tree(root, root_vec);
		break;
	case 0xD: // подтвердить
		subconf_pT_val(root, root_vec);
		break;
	default:
		submenu_pass_tree_choice(root, root_vec);
	}
}

void submenu_create_tree_choice(Tree*& root, vector<int>& root_vec) {
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) { // если стрелки
		switch (k1) {
		case 0x48: // стрелка вверх
			subm_crT_count--;
			if (subm_crT_count < 0) subm_crT_count = 0;
			submenu_create_tree(root, root_vec);
			break;

		case 0x50: // стрелка вниз
			subm_crT_count++;
			if (subm_crT_count > 3) subm_crT_count = 3;
			submenu_create_tree(root, root_vec);
			break;
		case 0xD: // подтвердить
			subconf_crT_val(root, root_vec);
			break;
		default:
			submenu_create_tree_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // стрелка вверх
		subm_crT_count--;
		if (subm_crT_count < 0) subm_crT_count = 0;
		submenu_create_tree(root, root_vec);
		break;

	case 0x50: // стрелка вниз
		subm_crT_count++;
		if (subm_crT_count > 3) subm_crT_count = 3;
		submenu_create_tree(root, root_vec);
		break;
	case 0xD: // подтвердить
		subconf_crT_val(root, root_vec);
		break;
	default:
		submenu_create_tree_choice(root, root_vec);
	}
}

void menu_choice(Tree*& root, vector<int>&root_vec) {
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) { // если стрелки
		switch (k1) {
		case 0x48: // стрелка вверх
			m_count--;
			if (m_count < 0) m_count = 0;
			menu(root, root_vec);
			break;

		case 0x50: // стрелка вниз
			m_count++;
			if (m_count > 7) m_count = 7;
			menu(root, root_vec);
			break;
		case 0xD: // подтвердить
			conf_val(root, root_vec);
			break;
		default:
			menu_choice(root, root_vec);
		}
	}
	switch (k1) {
	case 0x48: // стрелка вверх
		m_count--;
		if (m_count < 0) m_count = 0;
		menu(root, root_vec);
		break;

	case 0x50: // стрелка вниз
		m_count++;
		if (m_count > 7) m_count = 7;
		menu(root, root_vec);
		break;
	case 0xD: // подтвердить
		conf_val(root, root_vec);
		break;
	default:
		menu_choice(root, root_vec);
	}
}

void submenu_pass_tree(Tree*& root, vector<int>& root_vec) {
	system("cls"); // очищаем консоль

	if (subm_pT_count == 0) {
		cout << right << "__ОБХОД ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Какой способ обхода дерева использовать?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "Прямой обход" << endl;
		SetColor(7, 0);
		cout << "Обратный обход" << endl;
		cout << "Обход в ширину дерева" << endl;
		cout << "Назад" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 1) {
		cout << right << "__ОБХОД ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Какой способ обхода дерева использовать?" << endl << endl;
		SetColor(7, 0);
		cout << "Прямой обход" << endl;
		SetColor(5, 0);
		cout << "Обратный обход" << endl;
		SetColor(7, 0);
		cout << "Обход в ширину дерева" << endl;
		cout << "Назад" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 2) {
		cout << right << "__ОБХОД ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Какой способ обхода дерева использовать?" << endl << endl;
		SetColor(7, 0);
		cout << "Прямой обход" << endl;
		cout << "Обратный обход" << endl;
		SetColor(5, 0);
		cout << "Обход в ширину дерева" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_pass_tree_choice(root, root_vec);
	}
	if (subm_pT_count == 3) {
		cout << right << "__ОБХОД ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Какой способ обхода дерева использовать?" << endl << endl;
		SetColor(7, 0);
		cout << "Прямой обход" << endl;
		cout << "Обратный обход" << endl;
		cout << "Обход в ширину дерева" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_pass_tree_choice(root, root_vec);
	}

}

void submenu_create_tree(Tree*& root, vector<int>& root_vec) {
	system("cls"); // очищаем консоль

	if (subm_crT_count == 0) {
		cout << right << "__СОЗДАНИЕ ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем дерево?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(7, 0);
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 1) {
		cout << right << "__СОЗДАНИЕ ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем дерево?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(5, 0);
		cout << "Вручную, заполняя значения" << endl;
		SetColor(7, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 2) {
		cout << right << "__СОЗДАНИЕ ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем дерево?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		SetColor(5, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_create_tree_choice(root, root_vec);
	}
	if (subm_crT_count == 3) {
		cout << right << "__СОЗДАНИЕ ДЕРЕВА__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем дерево?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_create_tree_choice(root, root_vec);
	}
}

void menu(Tree*& root, vector<int>& root_vec) {
	system("cls"); // очищаем консоль

	if (m_count == 0) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		SetColor(5, 0);
		cout << "Создать дерево" << endl;
		SetColor(7, 0);
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 1) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		SetColor(5, 0);
		cout << "Добавить элемент к дереву" << endl;
		SetColor(7, 0);
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 2) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		SetColor(5, 0);
		cout << "Удалить элемент дерева" << endl;
		SetColor(7, 0);
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 3) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		SetColor(5, 0);
		cout << "Получить элемент дерева" << endl;
		SetColor(7, 0);
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 4) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		SetColor(5, 0);
		cout << "Вывести дерево" << endl;
		SetColor(7, 0);
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 5) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		SetColor(5, 0);
		cout << "Обходы дерева" << endl;
		SetColor(7, 0);
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 6) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		SetColor(5, 0);
		cout << "Задание по варианту" << endl;
		SetColor(7, 0);
		cout << "Выход" << endl;
		menu_choice(root, root_vec);
	}
	if (m_count == 7) {
		cout << setw(15) << right << "__МЕНЮ__" << endl;
		cout << "Создать дерево" << endl;
		cout << "Добавить элемент к дереву" << endl;
		cout << "Удалить элемент дерева" << endl;
		cout << "Получить элемент дерева" << endl;
		cout << "Вывести дерево" << endl;
		cout << "Обходы дерева" << endl;
		cout << "Задание по варианту" << endl;
		SetColor(5, 0);
		cout << "Выход" << endl;
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