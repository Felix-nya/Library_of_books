#include <iostream>
#include <cstdio>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iomanip> 
#include <cstdlib>
using namespace std;

struct Node {
	string author;
	string name;
	Node* next;
	Node(string n, string i) : author(n), name(i), next(NULL){}
};

typedef Node* PNode;

PNode Head = NULL;

PNode CreateNode(string name, string i)
{
	return new Node(name, i);
}

void AddFirst(PNode NewNode)
{
	NewNode->next = Head;
	Head = NewNode;
}

void AddAfter(PNode q, PNode NewNode) {
	NewNode->next = q->next;
	q->next = NewNode;
}

void AddLast(PNode NewNode) {
	PNode q = Head;
	if (Head == NULL) {
		AddFirst(NewNode);
		return;
	}
	while (q->next) q = q->next;
	AddAfter(q, NewNode);
}

void DeleteNode(PNode OldNode) {
	PNode q = Head;
	if (Head == OldNode) Head = OldNode->next;
	else {
		while (q && q->next != OldNode) q = q->next;
		if (q == NULL) return;
		q->next = OldNode->next;
	}
	delete OldNode;
}

void showList() {
	PNode q = Head;
	int n = 1;
	while (q) {
		cout << setw(4) << left << n << setw(30) << left << q->author  << setw(50) << left << q->name << endl;
		q = q->next;
		n++;
	}
}

void DeleteList() {
	PNode q = Head;
	PNode nextNode;

	while (q) {
		nextNode = q->next;
		delete q;
		q = nextNode;
	}
	Head = NULL;
}

void score() {
	int n = 0;
	PNode q = Head;
	while (q) {
		n += 1;
		q = q->next;
	}
	cout << "Количество элементов - " << n << endl;
}

void Interface() {
	cout << endl << setw(35) << left << "Управление на стрелочки" << setw(35) << left << "[A] - Для добавления в список" << setw(35) << left << "[E] - Для завершения программы" << endl;
	for (int i = 0; i < 119; i++) cout << "_";
	for (int i = 0; i < 2; i++) cout << endl;
	cout << setw(4) << left << "№" << setw(30) << left << "Автор" << setw(50) << left << "Название" << endl;
	for (int i = 0; i < 119; i++) cout << "_";
	cout << endl;
	showList();
}

void Programm() {
	char ch = '\0';
	Interface();
	do {
		ch = _getch();
		if (ch == 'a' || ch == 'A' || ch == 'f' || ch == 'F' || ch == 'ф' || ch == 'Ф' || ch == 'а' || ch == 'А') {
			string aut, nam;
			cout << "Введите автора: ";
			getline(cin, aut);
			cout << "Введите название : ";
			getline(cin, nam);
			AddLast(CreateNode(aut, nam));
		}
		system("cls");
		Interface();
	} while (ch != 'у' && ch != 'У' && ch != 'e' && ch != 'E' && ch != 't' && ch != 'T' && ch != 'е' && ch != 'Е');
}

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*AddLast(CreateNode("Пушкин", "Евгений Онегин"));
	AddLast(CreateNode("Есенин", "Берёза"));
	AddLast(CreateNode("Грибоедов", "Горе от ума"));
	Interface();*/
	Programm();
	return 0;
}
