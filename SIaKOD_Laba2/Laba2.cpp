#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
const int m = 55; // Кол-во элементов
const int n = 4; // Размерность
const int t = m * 1.5 + 1; // Размер таблицы
const int start = pow(10, n - 1);
const int end1 = pow(10, n) - 1;
int sum_count = 0;

int hash_func(int x) {
	int hash = 0;
	while (x > 0) {
		hash += x % 10;
		x /= 10;
	}
	return hash % t;
}

void print_table(int arr[t]) {
	cout << "Хеш-таблица:\n";
	cout << '[';
	for (int i = 0; i < t; i++) {
		if (i == t - 1) { printf("%d : %d]\n", i, arr[i]); }
		else { printf("%d : %d, ", i, arr[i]); }
	}

	int k = 0;
	for (int i = 0; i < t; i++) {
		if (arr[i] != -1) k += 1;
	}
	float alpha = static_cast<float>(k) / t;
	printf("Коэффициент заполнения таблицы: %f\n", alpha);
	float average_steps = static_cast<float>(sum_count) / m;
	printf("Среднее число шагов для размещения: %f\n", average_steps);
}

int enter_elem() {
	int elem = 0;
	cout << "Введите элемент: ";
	cin >> elem;
	while (elem < start || elem > end1) {
		cout << "Введённый элемент должен быть четырёхзначным положительным числом\nВведите элемент: ";
		cin >> elem;
	}
	return elem;
}

int find_elem(int arr[t], int elem) {
	int hash = hash_func(elem);
	if (arr[hash] == -1) {
		return -1;
	}
	else if (arr[hash] == elem) {
		return hash;
	}
	else {
		int a = 0;
		int b = 1;
		int count = 0;
		while (count < t) {
			count += 1;
			a = static_cast<int> (hash + pow(b, 2)) % t;
			if (arr[a] == -1) {
				return -1;
			}
			else if (arr[a] == elem) {
				return a;
			}
			b += 1;
		}
		if (count == t) {
			return -2;
		}
	}
}

void delete_elem(int arr[t], int elem) {
	int index = find_elem(arr, elem);
	if (index == -1) {
		cout << "Элемента в таблице нет\n";
	}
	else if (index == -2) { printf("Превышено максимальное количество итераций (%d)\n", t); }
	else {
		int elem = arr[index];
		arr[index] = -2;
		printf("Удалён элемент %d с индексом %d\n", elem, index);
	}
}

void add_elem(int arr[t], int elem) {
	int index = find_elem(arr, elem);
	if (index != -1 && index != -2) { printf("Элемент %d уже есть в таблице под индексом %d\n", elem, index); }
	else if (index == -2) { printf("Превышено максимальное количество итераций (%d)\n", t); }
	else {
		int hash = hash_func(elem);
		int count = 1;
		if (arr[hash] == -1 || arr[hash] == -2) {
			arr[hash] = elem;
			printf("Элемент %d добавлен в таблицу по индексу %d\n", elem, hash);
		}
		else {
			int a = 0;
			int b = 1;
			while (count < t) { // Квадратичное опробывание
				count += 1;
				a = static_cast<int> (hash + pow(b, 2)) % t;
				if (arr[a] == -1 || arr[a] == -2) {
					arr[a] = elem;
					printf("Элемент %d добавлен в таблицу по индексу %d\n", elem, a);
					break;
				}
				b += 1;
			}
			if (count >= t) { // Линейное опробывание
				a = hash;
				b = 1;
				while (true) {
					count += 1;
					a = (hash + b) % t;
					if (arr[a] == -1 || arr[a] == -2) {
						arr[a] = elem;
						printf("Элемент %d добавлен в таблицу по индексу %d\n", elem, a);
						break;
					}
				}
			}
		}

		sum_count += count;
	}
}

void replace_elem(int arr[t]) {
	int elem = enter_elem();
	int index = find_elem(arr, elem);
	while (index == -1) {
		cout << "Такого элемента нет в таблице\n";
		elem = enter_elem();
		index = find_elem(arr, elem);
	}
	delete_elem(arr, elem);
	int newElem = enter_elem();
	int newIndex = find_elem(arr, newElem);
	while (newIndex != -1) {
		cout << "Такой элемент уже есть в таблице\n";
		newElem = enter_elem();
		newIndex = find_elem(arr, newElem);
	}
	add_elem(arr, newElem);
	/*
	int index = find_elem(arr, elem);
	if (index == -1) {
		cout << "Элемента в таблице нет\n";
	}
	else if (index == -2) { printf("Превышено максимальное количество итераций (%d)\n", t); }
	else {
		delete_elem(arr, elem);
		int newElem = enter_elem();
		int newIndex = find_elem(arr, newElem);
		if (newIndex == -1) {
			arr[index] = newElem;
			printf("Элемент %d добавлен в таблицу по индексу %d\n", newElem, index);
		}
		else if (newIndex == -2) { printf("Превышено максимальное количество итераций (%d)\n", t); }
		else {
			cout << "Элемент уже есть в таблице\n";
		}
		print_table(arr);
	}
	*/
}

int main() {
	setlocale(LC_ALL, "Russian");
	int arr[t];
	int arrForTest[m];
	for (int i = 0; i < t; i++) {
		arr[i] = -1; // Начальное значение
	}
	for (int i = 0; i < m; i++) {
		arrForTest[i] = -1;
	}

	srand(time(0));
	int x = 0;
	cout << "Сгенерированные ключи:\n";
	cout << '[';
	for (int i = 0; i < m; i++) {
		while (true) { // Проверка на дубликаты
			x = rand() % (end1 - start + 1) + start;
			if (find(begin(arrForTest), end(arrForTest), x) == end(arrForTest)) { break; }
		}
		for (int p = 0; p < m; p++) {
			if (arrForTest[p] == -1) {
				arrForTest[p] = x;
				break;
			}
		}

		if (i == m - 1) { printf("%d]\n", x); }
		else { printf("%d, ", x); }
		int hash = hash_func(x);

		int count = 1;
		if (arr[hash] == -1) {
			arr[hash] = x;
		}
		else {
			int a = 0;
			int b = 1;
			while (count < t) { // Квадратичное опробывание
				count += 1;
				a = static_cast<int> (hash + pow(b, 2)) % t;
				if (arr[a] == -1) {
					arr[a] = x;
					break;
				}
				b += 1;
			}
			if (count >= t) { // Линейное опробывание
				a = hash;
				b = 1;
				while (true) {
					count += 1;
					a = (hash + b) % t;
					if (arr[a] == -1) {
						arr[a] = x;
						break;
					}
				}
			}
		}

		sum_count += count;
	}

	print_table(arr);

	cout << "\nВыберите нужный вариант: \n1 - Найти элемент\n2 - Удалить элемент\n3 - Добавить новый элемент\n4 - Заменить элемент\n5 - Завершить работу программы\n";
	int key = 0;
	while (true) {
		cin >> key;
		while (key < 1 || key > 5) {
			cout << "Введённое значение некорректно\n";
			cin >> key;
		}
		switch (key) {
		case 1: {
			int elem = enter_elem();
			int index = find_elem(arr, elem);
			if (index == -1) { cout << "Элемента в таблице нет\n"; }
			else if (index == -2) { printf("Превышено максимальное количество итераций (%d)\n", t); }
			else { printf("Найден элемент %d с индексом %d\n", arr[index], index); }
			break;
		}
		case 2: {
			int elem = enter_elem();
			delete_elem(arr, elem);
			print_table(arr);
			break;
		}
		case 3: {
			cout << "\nВыберите нужный вариант: \n1 - Ввести элемент с клавиатуры\n2 - Сгенерировать элемент\n";
			int j = 0;
			cin >> j;
			while (j < 1 || j > 2) {
				cout << "Введённое значение некорректно\n";
				cin >> j;
			}
			int elem = 0;
			switch (j) {
			case 1:
				elem = enter_elem();
				break;
			case 2:
				elem = rand() % (end1 - start + 1) + start;
				break;
			}
			add_elem(arr, elem);
			print_table(arr);
			break;
		}
		case 4:
			replace_elem(arr);
			print_table(arr);
			break;
		case 5:
			return 0;
		}
	}
	return 0;
}