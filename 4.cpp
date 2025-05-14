#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iomanip> 
#include <consoleapi.h>
#include <fstream>
#include <sstream>
using namespace std;

int Console_wide() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int wide = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return wide;
}

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
	cout << string(Console_wide(), ' ');
	gotoxy(0, line);
}

struct Node {
	string author;
	string name;
	int date;
	string lists;
	Node* next;
	Node(string aut, string name, int date, string lists) : author(aut), name(name), date(date), lists(lists), next(NULL) {}
};

typedef Node* PNode;

PNode CreateNode(string aut, string name, int date, string lists)
{
	return new Node(aut, name, date, lists);
}

void AddFirst(PNode NewNode, PNode& Head)
{
	NewNode->next = Head;
	Head = NewNode;
}

void AddAfter(PNode q, PNode NewNode) {
	NewNode->next = q->next;
	q->next = NewNode;
}

void AddLast(PNode NewNode, PNode& Head) {
	PNode q = Head;
	if (Head == NULL) {
		return AddFirst(NewNode, Head);
	}
	while (q->next) q = q->next;
	AddAfter(q, NewNode);
}

void DeleteNode(int n, PNode& Head) {
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

void showList(int cursor, PNode& Head) {
	PNode q = Head;
	int n = 1;
	while (q) {
		if (n == cursor) {
			cout << setw(2) << left << "=>" << setw(4) << left << n << setw(30) << left << q->author << setw(50) << left << q->name << setw(30) << left << q->date << setw(40) << left << q->lists << endl;
		}
		else {
			cout << setw(4) << left << n << setw(30) << left << q->author << setw(50) << left << q->name << setw(30) << left << q->date << setw(40) << left << q->lists << endl;
		}
		q = q->next;
		n++;
	}
}

void DeleteList(PNode& Head) {
	PNode q = Head;
	PNode nextNode;

	while (q) {
		nextNode = q->next;
		delete q;
		q = nextNode;
	}
	Head = NULL;
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

int Search_element(int swi, int pos_curs, PNode& Head) {
	PNode q = Head;
	int k = 1;
	string line;
	switch (swi) {
	case 1: {
		cout << "Введите автора: ";
		getline(cin, line);
		ClearLine(pos_curs);
		while (q) {
			if (q->author == line) {
				return k;
			}
			q = q->next;
			k++;
		}
		break;
	}
	case 2: {
		cout << "Введите название: ";
		getline(cin, line);
		ClearLine(pos_curs);
		while (q) {
			if (q->name == line) {
				return k;
			}
			q = q->next;
			k++;
		}
		break;
	}
	case 3: {
		cout << "Введите год издания: ";
		getline(cin, line);
		ClearLine(pos_curs);
		if (!Testi(line)) return k;
		while (q) {
			if (q->date == stoi(line)) {
				return k;
			}
			q = q->next;
			k++;
		}
		break;
	}
	default:
		break;
	}
	return 1;
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

void Interface(PNode& Head) {
	gotoxy(0, 1);
	cout << setw(40) << left << "[A] - Для добавления в список" << setw(40) << left << "[D] - Для удаления произведения" << setw(70) << left << "[R] - Для изменения количества прочитанных страниц произведения" << setw(40) << left << "[Q] - Для сохранения электронной библиотеки";
	gotoxy(0, 3);
	cout << setw(40) << left << "[S] - Для поиска" << setw(40) << left << "[P] - Для удаления всего списка" << setw(70) << left << "[Y] - Для открытия сохранённой библиотеки" << setw(40) << left << "[E] - Для завершения программы";
	gotoxy(0, 4);
	for (int i = 0; i < Console_wide(); i++) cout << "_";
	gotoxy(0, 6);
	cout << setw(4) << left << "№" << setw(30) << left << "Автор" << setw(50) << left << "Название" << setw(30) << left << "Год издания" << setw(40) << left << "Статус чтения";
	gotoxy(0, 7);
	for (int i = 0; i < Console_wide(); i++) cout << "_";
	gotoxy(0, 8);
	showList(0, Head);
}

void Programm(PNode& Head) {
	char ch = '\0';
	int position_curs = 8;
	int choose_the_book = 1;
	Interface(Head);
	do {
		ch = _getch();
		if (ch == 'a' || ch == 'A' || ch == 'ф' || ch == 'Ф') {
			string aut, nam, datstr, lists;
			int dat;
			cout << "Введите автора: ";
			getline(cin, aut);
			ClearLine(position_curs);
			cout << "Введите название : ";
			getline(cin, nam);
			ClearLine(position_curs);
			cout << "Введите год издания : ";
			getline(cin, datstr);
			ClearLine(position_curs);
			if (!Testi(datstr)) continue;
			dat = stoi(datstr);
			cout << "Введите количество прочитанных страниц, если книга прочитана, введите -1 : ";
			getline(cin, lists);
			ClearLine(position_curs);
			if (lists == "-1") lists = "Прочитана";
			AddLast(CreateNode(aut, nam, dat, lists), Head);
			position_curs++;
		}
		else if ((ch == 'd' || ch == 'D' || ch == 'в' || ch == 'В') && Size_of_List(Head) > 0) {
			DeleteNode(choose_the_book, Head);
			choose_the_book = 1;
			position_curs--;
			ClearLine(position_curs);

		}
		else if (int(ch) == -32) {
			switch (_getch())
			{
			case 72: {
				choose_the_book--;
				if (choose_the_book < 1) choose_the_book = 1;
				break;
			}
			case 80: {
				choose_the_book++;
				if (choose_the_book > Size_of_List(Head)) choose_the_book = Size_of_List(Head);
				break;
			}
			default:
				break;
			}
		}
		else if ((ch == 's' || ch == 'S' || ch == 'ы' || ch == 'Ы') && Size_of_List(Head) > 0) {
			string line;
			int swi;
			cout << "Нажмите [1] - для поиска по автору, [2] - по названию, [3] - по году издания";
			swi = _getch() - '0';
			ClearLine(position_curs);
			choose_the_book = Search_element(swi, position_curs, Head);
		}
		else if ((ch == 'p' || ch == 'P' || ch == 'з' || ch == 'З') && Size_of_List(Head) > 0) {
			DeleteList(Head);
			for (int i = 8; i < position_curs; i++) {
				ClearLine(i);
			}
			choose_the_book = 1;
			position_curs = 8;
		}
		else if ((ch == 'r' || ch == 'R' || ch == 'к' || ch == 'К') && Size_of_List(Head) > 0) {
			string new_lists;
			cout << "Введите количество прочитанных страниц, если книга прочитана, введите -1 : ";
			getline(cin, new_lists);
			ClearLine(position_curs);
			if (new_lists == "-1") new_lists = "Прочитана";
			PNode q = Head;
			int i = 1;
			while (i != choose_the_book) {
				i++;
				q = q->next;
			}
			q->lists = new_lists;
		}
		else if (ch == 'q' || ch == 'Q' || ch == 'й' || ch == 'Й') {
			ofstream File("My_Library.txt");
			File << "Моя библиотека!" << endl;
			PNode q = Head;
			while (q) {
				File << q->author << " " << q->name << " " << q->date << " " << q->lists << endl;
				q = q->next;
			}
			File.close();
		}
		else if (ch == 'y' || ch == 'Y' || ch == 'н' || ch == 'Н') {
			ifstream File("My_Library.txt");
			string line_in_file;
			getline(File, line_in_file);
			while (getline(File, line_in_file)) {
				istringstream iss(line_in_file);
				string aut, nam, lists;
				int dat;
				iss >> aut >> nam >> dat >> lists;
				AddLast(CreateNode(aut, nam, dat, lists), Head);
				position_curs++;
			}
			File.close();
		}
		gotoxy(0, 8);
		showList(choose_the_book, Head);
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
