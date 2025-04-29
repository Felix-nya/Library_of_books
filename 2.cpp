#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iomanip> 
#include <consoleapi.h>
using namespace std;

void setFullscreen() {
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void gotoxy(short x, short y)
{
	HANDLE term = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(term, position);
}

void ClearLine(int line) {
	gotoxy(0, line);
	cout << string(237, ' ');
	gotoxy(0, line);
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

void DeleteNode(int n, PNode &Head) {
	PNode q = Head;
	PNode j = nullptr;
	if (n == 1) { 
		j = Head;
		Head = q->next; 
	}
	else {
		int i = 2;
		while (q) {
			if (i == n) {
				j = q->next;
				q->next = j->next;
				break;
			}
			q = q->next;
			i++;
		}
	}
	delete j;
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

int Size_of_List(PNode& Head) {
	PNode q = Head;
	int k = 0;
	while (q) {
		q = q->next;
		k++;
	}
	return k;
}

void Interface(PNode &Head) {
	gotoxy(0, 1);
	cout << setw(40) << left << "[A] - Для добавления в список" << setw(40) << left << "[D] - Для удаления произведения" << setw(40) << left << "[E] - Для завершения программы";
	gotoxy(0, 3);
	cout << setw(40) << left << "[S] - Для поиска по названию" << setw(40) << left << "[P] - Для удаления всего списка" << setw(40) << left << "[E] - Для завершения программы";
	gotoxy(0, 4);
	for (int i = 0; i < 237; i++) cout << "_";
	gotoxy(0, 6);
	cout << setw(4) << left << "№" << setw(30) << left << "Автор" << setw(50) << left << "Название";
	gotoxy(0, 7);
	for (int i = 0; i < 237; i++) cout << "_";
	gotoxy(0, 8);
	showList(Head);
}

int Testi(string n) {
	int l = n.length();
	for (int i = 0; i < l; i++) {
		if (!(n[i] == '/0' || n[i] == '0' || n[i] == '1' || n[i] == '2' || n[i] == '3' || n[i] == '4' || n[i] == '5' || n[i] == '6' || n[i] == '7' || n[i] == '8' || n[i] == '9')) {
			return 0;
		}
	}
	return 1;
}

void Programm(PNode &Head) {
	char ch = '\0';
	int position_curs = 8;
	Interface(Head);
	do {
		ch = _getch();
		if (ch == 'a' || ch == 'A' || ch == 'ф' || ch == 'Ф') {
			string aut, nam;
			cout << "Введите автора: ";
			getline(cin, aut);
			ClearLine(position_curs);
			cout << "Введите название : ";
			getline(cin, nam);
			ClearLine(position_curs);
			AddLast(CreateNode(aut, nam), Head);
			position_curs++;
		}
		else if ((ch == 'd' || ch == 'D' || ch == 'в' || ch == 'В') && Size_of_List(Head) > 0) {
			int number;
			string num;
			cout << "Введите номер для удаления: ";
			getline(cin, num);
			ClearLine(position_curs);
			if (!Testi(num)) continue;
			number = stoi(num);
			if (number > Size_of_List(Head)) {
				continue;
			}
			else {
				DeleteNode(number, Head);
				position_curs--;
				ClearLine(position_curs);
			}
		}
		gotoxy(0, 8);
		showList(Head);
	} while (ch != 'у' && ch != 'У' && ch != 'e' && ch != 'E');
	DeleteList(Head);
}

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	PNode Head = NULL;
	setFullscreen();
	Programm(Head);
	return 0;
}
