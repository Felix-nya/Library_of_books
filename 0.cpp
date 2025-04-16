#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iomanip> 
#include <consoleapi.h>
using namespace std;

int pos_y = 6;

void gotoxy(short x, short y)
{
	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(term, position);
}

void ClearLine() {
	gotoxy(0, pos_y);
	cout << string(50, ' ');
	gotoxy(0, pos_y);
}

struct Node {
	string author;
	string name;
	Node* next;
	Node(string n, string i) : author(n), name(i), next(NULL) {}
};

typedef Node* PNode;

PNode CreateNode(string name, string i)
{
	return new Node(name, i);
}

void AddFirst(PNode NewNode, PNode &Head)
{
	NewNode->next = Head;
	Head = NewNode;
}

void AddAfter(PNode q, PNode NewNode) {
	NewNode->next = q->next;
	q->next = NewNode;
}

void AddLast(PNode NewNode, PNode &Head) {
	PNode q = Head;
	if (Head == NULL) {
		return AddFirst(NewNode, Head);
	}
	while (q->next) q = q->next;
	AddAfter(q, NewNode);
}

void DeleteNode(PNode OldNode, PNode &Head) {
	PNode q = Head;
	if (Head == OldNode) Head = OldNode->next;
	else {
		while (q && q->next != OldNode) q = q->next;
		if (q == NULL) return; 
		q->next = OldNode->next;
	}
	delete OldNode;
}

void showList(PNode &Head) {
	PNode q = Head;
	int n = 1;
	while (q) {
		cout << setw(4) << left << n << setw(30) << left << q->author << setw(50) << left << q->name << endl;
		q = q->next;
		n++;
	}
}

void DeleteList(PNode &Head) {
	PNode q = Head;
	PNode nextNode;

	while (q) {
		nextNode = q->next;
		delete q;
		q = nextNode;
	}
}

int score(PNode &Head) {
	int n = 0;
	PNode q = Head;
	while (q) {
		n += 1;
		q = q->next;
	}
	cout << "Количество элементов - " << n << endl;
	return n;
}

void Interface(PNode &Head) {
	cout << endl << setw(35) << left << "Управление на стрелочки" << setw(35) << left << "[A] - Для добавления в список" << setw(35) << left << "[E] - Для завершения программы" << endl;
	for (int i = 0; i < 119; i++) cout << "_";
	for (int i = 0; i < 2; i++) cout << endl;
	cout << setw(4) << left << "№" << setw(30) << left << "Автор" << setw(50) << left << "Название" << endl;
	for (int i = 0; i < 119; i++) cout << "_";
	cout << endl;
	showList(Head);
}

void Programm(PNode &Head) {
	char ch = '\0';
	Interface(Head);
	do {
		ch = _getch();
		if (ch == 'a' || ch == 'A' || ch == 'f' || ch == 'F' || ch == 'ф' || ch == 'Ф' || ch == 'а' || ch == 'А') {
			string aut, nam;
			cout << "Введите автора: ";
			getline(cin, aut);
			ClearLine();
			cout << "Введите название : ";
			getline(cin, nam);
			ClearLine();
			AddLast(CreateNode(aut, nam), Head);
			pos_y++;
		}
		gotoxy(0, 0);
		Interface(Head);
	} while (ch != 'у' && ch != 'У' && ch != 'e' && ch != 'E' && ch != 't' && ch != 'T' && ch != 'е' && ch != 'Е');
	DeleteList(Head);
}

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	PNode Head = NULL;
	Programm(Head);
	return 0;
}
