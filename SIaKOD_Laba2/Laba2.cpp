#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
const int m = 55; // ���-�� ���������
const int n = 4; // �����������
const int t = m * 1.5 + 1; // ������ �������
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
	cout << "���-�������:\n";
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
	printf("����������� ���������� �������: %f\n", alpha);
	float average_steps = static_cast<float>(sum_count) / m;
	printf("������� ����� ����� ��� ����������: %f\n", average_steps);
}

int enter_elem() {
	int elem = 0;
	cout << "������� �������: ";
	cin >> elem;
	while (elem < start || elem > end1) {
		cout << "�������� ������� ������ ���� ������������� ������������� ������\n������� �������: ";
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
		cout << "�������� � ������� ���\n";
	}
	else if (index == -2) { printf("��������� ������������ ���������� �������� (%d)\n", t); }
	else {
		int elem = arr[index];
		arr[index] = -2;
		printf("����� ������� %d � �������� %d\n", elem, index);
	}
}

void add_elem(int arr[t], int elem) {
	int index = find_elem(arr, elem);
	if (index != -1 && index != -2) { printf("������� %d ��� ���� � ������� ��� �������� %d\n", elem, index); }
	else if (index == -2) { printf("��������� ������������ ���������� �������� (%d)\n", t); }
	else {
		int hash = hash_func(elem);
		int count = 1;
		if (arr[hash] == -1 || arr[hash] == -2) {
			arr[hash] = elem;
			printf("������� %d �������� � ������� �� ������� %d\n", elem, hash);
		}
		else {
			int a = 0;
			int b = 1;
			while (count < t) { // ������������ �����������
				count += 1;
				a = static_cast<int> (hash + pow(b, 2)) % t;
				if (arr[a] == -1 || arr[a] == -2) {
					arr[a] = elem;
					printf("������� %d �������� � ������� �� ������� %d\n", elem, a);
					break;
				}
				b += 1;
			}
			if (count >= t) { // �������� �����������
				a = hash;
				b = 1;
				while (true) {
					count += 1;
					a = (hash + b) % t;
					if (arr[a] == -1 || arr[a] == -2) {
						arr[a] = elem;
						printf("������� %d �������� � ������� �� ������� %d\n", elem, a);
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
		cout << "������ �������� ��� � �������\n";
		elem = enter_elem();
		index = find_elem(arr, elem);
	}
	delete_elem(arr, elem);
	int newElem = enter_elem();
	int newIndex = find_elem(arr, newElem);
	while (newIndex != -1) {
		cout << "����� ������� ��� ���� � �������\n";
		newElem = enter_elem();
		newIndex = find_elem(arr, newElem);
	}
	add_elem(arr, newElem);
	/*
	int index = find_elem(arr, elem);
	if (index == -1) {
		cout << "�������� � ������� ���\n";
	}
	else if (index == -2) { printf("��������� ������������ ���������� �������� (%d)\n", t); }
	else {
		delete_elem(arr, elem);
		int newElem = enter_elem();
		int newIndex = find_elem(arr, newElem);
		if (newIndex == -1) {
			arr[index] = newElem;
			printf("������� %d �������� � ������� �� ������� %d\n", newElem, index);
		}
		else if (newIndex == -2) { printf("��������� ������������ ���������� �������� (%d)\n", t); }
		else {
			cout << "������� ��� ���� � �������\n";
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
		arr[i] = -1; // ��������� ��������
	}
	for (int i = 0; i < m; i++) {
		arrForTest[i] = -1;
	}

	srand(time(0));
	int x = 0;
	cout << "��������������� �����:\n";
	cout << '[';
	for (int i = 0; i < m; i++) {
		while (true) { // �������� �� ���������
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
			while (count < t) { // ������������ �����������
				count += 1;
				a = static_cast<int> (hash + pow(b, 2)) % t;
				if (arr[a] == -1) {
					arr[a] = x;
					break;
				}
				b += 1;
			}
			if (count >= t) { // �������� �����������
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

	cout << "\n�������� ������ �������: \n1 - ����� �������\n2 - ������� �������\n3 - �������� ����� �������\n4 - �������� �������\n5 - ��������� ������ ���������\n";
	int key = 0;
	while (true) {
		cin >> key;
		while (key < 1 || key > 5) {
			cout << "�������� �������� �����������\n";
			cin >> key;
		}
		switch (key) {
		case 1: {
			int elem = enter_elem();
			int index = find_elem(arr, elem);
			if (index == -1) { cout << "�������� � ������� ���\n"; }
			else if (index == -2) { printf("��������� ������������ ���������� �������� (%d)\n", t); }
			else { printf("������ ������� %d � �������� %d\n", arr[index], index); }
			break;
		}
		case 2: {
			int elem = enter_elem();
			delete_elem(arr, elem);
			print_table(arr);
			break;
		}
		case 3: {
			cout << "\n�������� ������ �������: \n1 - ������ ������� � ����������\n2 - ������������� �������\n";
			int j = 0;
			cin >> j;
			while (j < 1 || j > 2) {
				cout << "�������� �������� �����������\n";
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