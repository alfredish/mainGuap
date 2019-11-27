#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;

//MARK: ��������
struct ZNAK {
	string name;
	string soname;
	int date[3];
	string badassSign;
};

struct list {
	ZNAK value;
	list *next;
};


//MARK: ����� � ����������  int
int coutCinInt(string text) {
	int var;
	cout << text;
	cin >> var;
	return var;
}

//MARK: ����� � ���������� string
string coutCin(string text) {
	string var;
	cout << text;
	cin >> var;
	return var;
}

//MARK: �������� ������ � ������ ���������
list *createList(ZNAK timeStruct) {
	list *head = new list;
	head->next = NULL;
	head->value.name = timeStruct.name;
	head->value.soname = timeStruct.soname;
	head->value.badassSign = timeStruct.badassSign;
	head->value.date[0] = timeStruct.date[0];
	head->value.date[1] = timeStruct.date[1];
	head->value.date[2] = timeStruct.date[2];
	return head;
}

//MARK: ������� �������� � ������ ������
void prepend(list* &head, ZNAK timeStruct) {
	if (!head) {
		head = createList(timeStruct);
		return;
	}

	list *tmp = new list;
	tmp->value.name = timeStruct.name;
	tmp->value.badassSign = timeStruct.badassSign;
	tmp->value.soname = timeStruct.soname;
	tmp->value.date[0] = timeStruct.date[0];
	tmp->value.date[1] = timeStruct.date[1];
	tmp->value.date[2] = timeStruct.date[2];

	tmp->next = head;
	head = tmp;
}

//MARK: clear list
void clear(list* &listt) {
	while (listt) {
		list* temp = listt;
		listt = listt->next;
		delete temp;
	}
}

//MARK: ������ ������
int ListSize(list *list) {
	int count = 0;
	while (list) {
		list = list->next;
		count++;
	}
	return count;
}

//MARK: �������� ����� ������ �� ������������
bool uniqueData(list* &listt, ZNAK timeStruct) {
	list* temp = listt;
	while (listt) {
		if (listt->value.name == timeStruct.name && listt->value.soname == timeStruct.soname && listt->value.date[0] == timeStruct.date[0] && listt->value.date[1] == timeStruct.date[1] && listt->value.date[2] == timeStruct.date[2]) {
			listt = temp;
			return false;
		}
		listt = listt->next;
	}
	listt = temp;
	return true;
}


//MARK: ����� ����� ������
void printList(list *list) {
	if (ListSize(list)) {
		cout << "/---------------------------------------------------------\\" << endl;
		cout << "|                 ���������� � �����������                |" << endl;
		cout << "|---------------------------------------------------------|" << endl;
		cout << "|���        �������        ���� �������   ���� ��������   |" << endl;
		cout << "|---------------------------------------------------------|" << endl;

		while (list) {
			string date = to_string(list->value.date[0]) + "." + to_string(list->value.date[1]) + "." + to_string(list->value.date[2]);
			cout << "|" << setw(10) << left << list->value.name << " " << setw(14) << left << list->value.soname << " " << setw(15) << left << list->value.badassSign << setw(16) << left << date << "|" << endl;
			list = list->next;
		}
		cout << "|---------------------------------------------------------|" << endl;
	}
	else {
		cout << "������ ���� ��� ���� " << endl;
	}
}

//MARK: ����� ���������� �������� ������
list *getLast(list *list) {
	if (!list)
		return list;

	if (list->next)
		return getLast(list->next);
	return list;
}

//MARK: �������� ����
bool IsRange(int value, int min, int max) {
	if (value < min) return false;
	if (value > max) return false;
	return true;
}

bool checkDataFromFile(int day, int month, int year) {
	if (year < 1900 || year > 2019)
		return false;

	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return IsRange(day, 1, 31);
	case 2:
		if (year % 4 == 0 || (year % 100 == 0 && year % 400 == 0))
			return IsRange(day, 1, 29);
		else
			return IsRange(day, 1, 28);
	case 4:
	case 6:
	case 9:
	case 11:
		return IsRange(day, 1, 30);
	default:
		return false;
	}
}

//MARK: ����������� ����� �������
string badass(int day, int month) {
	if ((month == 3 && day > 20) || (month == 4 && day < 21)) {
		return "����";
	}
	else if ((month == 4 && day > 20) || (month == 5 && day < 21)) {
		return "�����";
	}
	else if ((month == 5 && day > 20) || (month == 6 && day < 22)) {
		return "��������";
	}
	else if ((month == 6 && day > 21) || (month == 7 && day < 23)) {
		return "���";
	}
	else if ((month == 7 && day > 22) || (month == 8 && day < 24)) {
		return "���";
	}
	else if ((month == 8 && day > 23) || (month == 9 && day < 24)) {
		return "����";
	}
	else if ((month == 9 && day > 23) || (month == 10 && day < 24)) {
		return "����";
	}
	else if ((month == 10 && day > 23) || (month == 11 && day < 23)) {
		return "��������";
	}
	else if ((month == 11 && day >22) || (month == 12 && day < 22)) {
		return "�������";
	}
	else if ((month == 12 && day > 21) || (month == 1 && day < 21)) {
		return "�������";
	}
	else if ((month == 1 && day > 20) || (month == 2 && day <21)) {
		return "�������";
	}
	else if ((month == 2 && day > 20) || (month == 3 && day < 21)) {
		return "����";
	}
	return "error";
}

//MARK: ���������� ����� ������
ZNAK readTimeStruct(bool &check) {
	ZNAK timeStruct;
	int day, month, year;

	string name, soname;
	cin.ignore();
	do {
		cout << "������� ��� ";
		getline(cin, name);
	} while (name.length()<1);
	do {
		cout << "������� ������� ";
		getline(cin, soname);
	} while (soname.length()<1);
	timeStruct.name = name;
	timeStruct.soname = soname;

	//timeStruct.name = coutCin("������� ���: ");
	//timeStruct.soname = coutCin("������� �������: ");
	do {
		if (!check) {
			cout << "�� ����� ����������� ���� ��������" << endl;
		}
		string days = coutCin("������� ���� �������� ");
		day = atoi(days.c_str());
		string months = coutCin("������� ����� �������� ");
		month = atoi(months.c_str());
		string years = coutCin("������� ��� �������� ");
		year = atoi(years.c_str());
		check = false;
	} while (!checkDataFromFile(day, month, year));
	check = true;
	timeStruct.date[0] = day;
	timeStruct.date[1] = month;
	timeStruct.date[2] = year;
	timeStruct.badassSign = badass(timeStruct.date[0], timeStruct.date[1]);

	return timeStruct;
}

//MARK: ���������� ������ �������� � ������ � �����
void append(list* &listt, ZNAK timeStruct,bool check) {

	if (uniqueData(listt, timeStruct)) {

		list *lastt = getLast(listt);
		if (!lastt) {
			prepend(listt, timeStruct);
			return;
		}

		list *tmp = new list;
		tmp->next = NULL;
		tmp->value.name = timeStruct.name;
		tmp->value.badassSign = timeStruct.badassSign;
		tmp->value.soname = timeStruct.soname;
		tmp->value.date[0] = timeStruct.date[0];
		tmp->value.date[1] = timeStruct.date[1];
		tmp->value.date[2] = timeStruct.date[2];
		lastt->next = tmp;
		if (check)
			cout << "������������ ������� ��������" << endl;
	}
	else {
		cout << "����� ������������ ��� ����" << endl;
	}
}


//MARK: ����
void menu() {
	cout << "/-----------------------------------------------\\" << endl;
	cout << "|            ���������� � �����������           |" << endl;
	cout << "|-----------------------------------------------|" << endl;
	cout << "| 1 - ���������� ������ ������������            |" << endl;
	cout << "| 2 - ����� �� �������                          |" << endl;
	cout << "| 3 - ��������� ������ ������������             |" << endl;
	cout << "| 4 - ���������� ������������� �� ����� ������� |" << endl;
	cout << "| 5 - ������� ������������                      |" << endl;
	cout << "| 6 - ���������� ������                         |" << endl;
	cout << "| 7 - ����� �� ����� ������ �������������       |" << endl;
	cout << "| 8 - ����� �� ���������                        |" << endl;
	cout << "\\-----------------------------------------------/" << endl << endl;
}


//MARK: ��������� ������
void workWithFileLine(list* &listt, string line) {

	ZNAK timeStruct;
	string timeString;
	int count = 0;
	for (size_t i = 0; i<line.length(); i++) {
		if (line[i] != '#') {
			timeString += line[i];
		}
		else {
			switch (count) {
			case 0:
				count++;
				timeStruct.name = timeString;
				timeString = "";
				break;
			case 1:
				count++;
				timeStruct.soname = timeString;
				timeString = "";
				break;
			case 2:
				count++;
				timeStruct.date[0] = atoi(timeString.c_str());;
				timeString = "";
				break;
			case 3:
				count++;
				timeStruct.date[1] = atoi(timeString.c_str());
				timeString = "";
				break;
			default:
				break;
			}
		}
	}
	if (count == 4) {
		timeStruct.date[2] = atoi(timeString.c_str());
		timeStruct.badassSign = badass(timeStruct.date[0], timeStruct.date[1]);
	}
	if (uniqueData(listt, timeStruct)) {
		if (timeStruct.badassSign != "error" && timeStruct.name != "" && timeStruct.name != " " && timeStruct.soname != "" && timeStruct.soname != " " && checkDataFromFile(timeStruct.date[0], timeStruct.date[1], timeStruct.date[2])) {
			append(listt, timeStruct,false);
		}
	}
}


//MARK: C��������� ������ �� �����
void readData(list* &listt, string path) {

	ifstream file(path);

	if (!file) {
		cout << "���� �� ������" << endl;
	}
	else {
		string line;
		while (getline(file, line)) {
			workWithFileLine(listt, line);
		}
		file.close();
	}
}

//MARK: ����� ����� �� ������ ��������
void findPeople(list* listt) {

	bool check = true;

	string monthRead = coutCin("������� �����, � ������� �������� ����: ");
	int month = atoi(monthRead.c_str());

	if (month<0 || month>12) {
		cout << "����������� ��������� �����" << endl;
	}
	else {
		while (listt) {
			if (listt->value.date[1] == month) {
				if (check == true) {
					cout << "/---------------------------------------------------------\\" << endl;
					cout << "|���        �������        ���� ��������   ���� �������   |" << endl;
					cout << "|---------------------------------------------------------|" << endl;
					check = false;
				}
				cout << "|" << setw(10) << left << listt->value.name << " " << setw(14) << left << listt->value.soname << " " << listt->value.date[0] << "." << listt->value.date[1] << "." << setw(10) << left << listt->value.date[2] << " " << setw(15) << left << listt->value.badassSign << "|" << endl;
			}
			listt = listt->next;
		}

		if (check == false) {
			cout << "|---------------------------------------------------------|" << endl;
		}
		else {
			cout << "� ������ ������ ����� �� �������" << endl;
		}
	}

}

//MARK: ��������� �����
void changeName(list* & listt, string name, string soname, list* & list2) {
	list* head = listt;
	ZNAK time;

	string newName;
	cin.ignore();
	cout << "������� ��� " << endl;
	getline(cin, newName);

	//string newName = coutCin("������� ����� ���: ");
	while (listt) {
		if (listt->value.name == list2->value.name && listt->value.soname == list2->value.soname && listt->value.date[0] == list2->value.date[0] && listt->value.date[1] == list2->value.date[1] && listt->value.date[2] == list2->value.date[2]) {
			time.name = listt->value.name;
			time.soname = newName;
			time.date[0] = listt->value.date[0];
			time.date[1] = listt->value.date[1];
			time.date[2] = listt->value.date[2];
			time.badassSign = badass(time.date[0], time.date[1]);
			if (uniqueData(head, time)) {
				listt->value.name = newName;
			}
			else {
				cout << "����� ������������ ��� ����" << endl;
			}
			break;
		}
		listt = listt->next;
	}
	listt = head;

}

//MARK: ��������� �������
void changeSoname(list* & listt, string name, string soname, list* &list2) {
	list* head = listt;
	ZNAK time;

	string newName;
	cin.ignore();
	cout << "name " << endl;
	getline(cin, newName);

	//string newName = coutCin("������� ����� �������: ");
	while (listt) {
		if (listt->value.name == list2->value.name && listt->value.soname == list2->value.soname && listt->value.date[0] == list2->value.date[0] && listt->value.date[1] == list2->value.date[1] && listt->value.date[2] == list2->value.date[2]) {
			time.name = newName;
			time.soname = listt->value.soname;
			time.date[0] = listt->value.date[0];
			time.date[1] = listt->value.date[1];
			time.date[2] = listt->value.date[2];
			time.badassSign = badass(time.date[0], time.date[1]);
			if (uniqueData(head, time)) {
				listt->value.name = newName;
			}
			else {
				cout << "����� ������������ ��� ����" << endl;
			}
			break;
		}
		listt = listt->next;
	}
	listt = head;
}

//MARK: ��������� ���� ��������� � ��������� �������������
void changeDate(list* &listt, string name, string soname, list* &list2) {
	list* head = listt;
	string days = coutCin("������� ���� �������� ");
	int day = atoi(days.c_str());
	string months = coutCin("������� ����� �������� ");
	int month = atoi(months.c_str());
	string years = coutCin("������� ��� �������� ");
	int year = atoi(years.c_str());
	ZNAK time;
	if (!checkDataFromFile(day, month, year)) {
		cout << "�� ����� ����������� ���� ��������" << endl;
	}
	else {
		while (listt) {
			if (listt->value.name == list2->value.name && listt->value.soname == list2->value.soname && listt->value.date[0] == list2->value.date[0] && listt->value.date[1] == list2->value.date[1] && listt->value.date[2] == list2->value.date[2]) {
				time.name = listt->value.name;
				time.soname = listt->value.soname;
				time.date[0] = day;
				time.date[1] = month;
				time.date[2] = year;
				time.badassSign = badass(time.date[0], time.date[1]);
				if (uniqueData(head, time)) {
					listt->value.date[0] = time.date[0];
					listt->value.date[1] = time.date[1];
					listt->value.date[2] = time.date[2];
					listt->value.badassSign = badass(time.date[0], time.date[1]);
				}
				else {
					cout << "����� ������������ ��� ����" << endl;
				}
				break;
			}
			listt = listt->next;
		}
	}
	listt = head;
}

//MARK: ����� ���������
void chose(list* &listt, list* &list2, string soname) {
	cout << "��� �� ������ �������� ?" << endl;
	cout << "1 - ���" << endl;
	cout << "2 - �������" << endl;
	cout << "3 - ���� ��������" << endl;

	string digites = coutCin("");
	int digite = atoi(digites.c_str());

	switch (digite) {
	case 1:
		changeName(listt, list2->value.name, soname, list2);
		break;
	case 2:
		changeSoname(listt, list2->value.name, soname, list2);
		break;
	case 3:
		changeDate(listt, list2->value.name, soname, list2);
		break;
	default:
		cout << "����� ������� �� ������� " << endl;
		break;
	}
}

//MARK: ��������� ������
void dataChange(list* &listt) {

	string soname = coutCin("������� ������� ������������: ");

	list* head = listt;
	int count = 0;
	list* list2 = NULL;
	while (listt) {
		if (listt->value.soname == soname) {
			ZNAK add = listt->value;
			append(list2, add,false);
			count++;
		}
		listt = listt->next;
	}
	listt = head;

	if (count == 0) {
		cout << "������ ������������ ����" << endl;
	}
	else if (count == 1) {
		chose(listt, list2, soname);
	}
	else {
		count = 1;
		list* temp2 = list2;
		while (list2) {
			cout << count << " " << list2->value.soname << " " << list2->value.name << " " << list2->value.date[0] << "." << list2->value.date[1] << "." << list2->value.date[2] << endl;
			count++;
			list2 = list2->next;
		}
		list2 = temp2;
		int personIndex = coutCinInt("�������� ������� ������������: ");
		if (personIndex > 0 && personIndex < count) {
			while (personIndex - 1) {
				list2 = list2->next;
				personIndex--;
			}
			chose(listt, list2, soname);
			list2 = temp2;
		}else {
			cout << "������ ������������ ����" << endl;
		}
		listt = head;
		clear(list2);
	}

}

//MARK: ���������� ������
void saveData(list* &listt, string path) {
	ofstream file(path);

	if (file.is_open()) {
		list* head = listt;
		while (listt) {
			file << listt->value.name << "#" << listt->value.soname << "#" << listt->value.date[0] << "#" << listt->value.date[1] << "#" << listt->value.date[2] << endl;
			listt = listt->next;
		}
		listt = head;
		cout << "������ ������� ��������� " << endl;
	}
	else {
		cout << "���� �� ������" << endl;
	}
}

//MARK: ���������� ����� �� �����
void sortPeople(list* &listt, string path) {
	list* ptr = listt, *tmp = NULL, *prev = NULL;
	bool flag = false;
	if (listt) {
		do {
			flag = false;
			ptr = listt;
			while (ptr->next) {
				if (ptr->value.badassSign > ptr->next->value.badassSign) {
					if (ptr == listt) {
						tmp = ptr;
						ptr = tmp->next;
						tmp->next = ptr->next;
						ptr->next = tmp;
						listt = ptr;
						flag = true;
					}
					else {
						tmp = ptr;
						ptr = tmp->next;
						tmp->next = ptr->next;
						ptr->next = tmp;
						prev->next = ptr;
						flag = true;
					}
				}
				prev = ptr;
				ptr = ptr->next;
			}
		} while (flag);
		cout << "������ ������������." << endl << endl;

		cout << "1 - ��������� ��������������� ������ " << endl;
		cout << "2 - ������� ��������������� ������ " << endl;
		cout << "����� ������ ������ ��� ����������� ������" << endl;
		string aa;
		cin >> aa;
		int a = atoi(aa.c_str());
		switch (a) {
		case 1:
			saveData(listt, path);
			break;
		case 2:
			printList(listt);
		default:
			break;
		}
	}
	else {
		cout << "������ ����" << endl;
	}
	cout << endl;
}

//MARK:�������� ��������
void removeElement(list* &listt, list* &list2, int count) {
	//�������� ������� �������
	if (listt->value.soname == list2->value.soname) {
		list* tmp = listt;
		listt = listt->next;
		delete tmp;
		cout << "������������ ������" << endl;
	}
	else {
		list* temp2 = list2;
		list* temp = listt;
		list *prev = nullptr;

		while (temp2) {
			while (listt->value.soname != list2->value.soname && count != 1) {
				prev = listt;
				listt = listt->next;
				count--;
			}
			temp2 = temp2->next;
		}
		prev->next = listt->next;
		delete listt;
		cout << "������������ ������" << endl;

		listt = temp;
		list2 = temp2;

	}
}

//MARK:����� �������� ��� ��������
void deleteEl(list* &listt) {
	string soname = coutCin("������� ������� ����������� ");
	list* head = listt;
	int count = 0, pos = 0;
	list* list2 = NULL;
	while (listt) {
		if (soname == listt->value.soname) {
			ZNAK add = listt->value;
			append(list2, add,false);
			count++;
		}
		pos++;
		listt = listt->next;
	}
	listt = head;

	if (count == 0) {
		cout << "������������ � ����� �������� ���� " << endl;
	}
	else if (count == 1) {
		removeElement(listt, list2, pos);
	}
	else {
		count = 1;
		list* temp2 = list2;
		while (list2) {
			cout << count << " " << list2->value.soname << " " << list2->value.name << " " << list2->value.date[0] << "." << list2->value.date[1] << "." << list2->value.date[2] << endl;
			count++;
			list2 = list2->next;
		}
		list2 = temp2;
		string nums = coutCin("������� ����� ��������, ������� ������ ������� ");
		int num = atoi(nums.c_str());
		if (num>0 && num < count)
			removeElement(listt, list2, count);
		else
			cout << "������ ������������ ����" << endl;
		clear(list2);
	}
}


//MARK: main function
int main() {

	list *listt = NULL;

	const string path = "file.txt";

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	readData(listt, path);

	bool check = true;
	while (check) {
		menu();

		string digites = coutCin("�������� ����� ����: ");
		int digite = atoi(digites.c_str());
		switch (digite) {
		case 1: {
			bool check = true;
			ZNAK timeStruct = readTimeStruct(check);
			if (check) {
				append(listt, timeStruct,true);
			}
			break;
		}
		case 2:
			findPeople(listt);
			break;
		case 3:
			dataChange(listt);
			break;
		case 4:
			sortPeople(listt, path);
			break;
		case 5:
			deleteEl(listt);
			break;
		case 6:
			saveData(listt, path);
			break;
		case 7:
			printList(listt);
			break;
		case 8: {
			bool saveOrNotSave = true;
			do {
				string saves = coutCin("��������� ������ ? 1-�� 2-��� ");
				int save = atoi(saves.c_str());
				if (save == 1) {
					saveData(listt, path);
					saveOrNotSave = false;
				}
				else if (save == 2) {
					saveOrNotSave = false;
				}
			} while (saveOrNotSave);
			clear(listt);
			check = false;
			break;
		}
		default:
			cout << "����� ������� ����" << endl;
			break;
		}
	}
}
