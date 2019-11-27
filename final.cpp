#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;

//MARK: Струкура
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


//MARK: Вывод и считывание  int
int coutCinInt(string text) {
	int var;
	cout << text;
	cin >> var;
	return var;
}

//MARK: Вывод и считывания string
string coutCin(string text) {
	string var;
	cout << text;
	cin >> var;
	return var;
}

//MARK: Создание списка с первым значением
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

//MARK: Вставка элемента в начала списка
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

//MARK: РаЗМЕР списка
int ListSize(list *list) {
	int count = 0;
	while (list) {
		list = list->next;
		count++;
	}
	return count;
}

//MARK: Проверка новых данных на уникальность
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


//MARK: Вывод всего списка
void printList(list *list) {
	if (ListSize(list)) {
		cout << "/---------------------------------------------------------\\" << endl;
		cout << "|                 Информация о сотрудниках                |" << endl;
		cout << "|---------------------------------------------------------|" << endl;
		cout << "|Имя        Фамилия        Знак зодиака   Дата рождения   |" << endl;
		cout << "|---------------------------------------------------------|" << endl;

		while (list) {
			string date = to_string(list->value.date[0]) + "." + to_string(list->value.date[1]) + "." + to_string(list->value.date[2]);
			cout << "|" << setw(10) << left << list->value.name << " " << setw(14) << left << list->value.soname << " " << setw(15) << left << list->value.badassSign << setw(16) << left << date << "|" << endl;
			list = list->next;
		}
		cout << "|---------------------------------------------------------|" << endl;
	}
	else {
		cout << "Данных пока что нету " << endl;
	}
}

//MARK: Поиск последнего элемента списка
list *getLast(list *list) {
	if (!list)
		return list;

	if (list->next)
		return getLast(list->next);
	return list;
}

//MARK: проверка даты
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

//MARK: Определения знака зодиака
string badass(int day, int month) {
	if ((month == 3 && day > 20) || (month == 4 && day < 21)) {
		return "Овен";
	}
	else if ((month == 4 && day > 20) || (month == 5 && day < 21)) {
		return "Телец";
	}
	else if ((month == 5 && day > 20) || (month == 6 && day < 22)) {
		return "Близнецы";
	}
	else if ((month == 6 && day > 21) || (month == 7 && day < 23)) {
		return "Рак";
	}
	else if ((month == 7 && day > 22) || (month == 8 && day < 24)) {
		return "Лев";
	}
	else if ((month == 8 && day > 23) || (month == 9 && day < 24)) {
		return "Дева";
	}
	else if ((month == 9 && day > 23) || (month == 10 && day < 24)) {
		return "Весы";
	}
	else if ((month == 10 && day > 23) || (month == 11 && day < 23)) {
		return "Скорпион";
	}
	else if ((month == 11 && day >22) || (month == 12 && day < 22)) {
		return "Стрелец";
	}
	else if ((month == 12 && day > 21) || (month == 1 && day < 21)) {
		return "Козерог";
	}
	else if ((month == 1 && day > 20) || (month == 2 && day <21)) {
		return "Водолей";
	}
	else if ((month == 2 && day > 20) || (month == 3 && day < 21)) {
		return "Рыбы";
	}
	return "error";
}

//MARK: Считывание новых данных
ZNAK readTimeStruct(bool &check) {
	ZNAK timeStruct;
	int day, month, year;

	string name, soname;
	cin.ignore();
	do {
		cout << "Введите имя ";
		getline(cin, name);
	} while (name.length()<1);
	do {
		cout << "Введите фамилию ";
		getline(cin, soname);
	} while (soname.length()<1);
	timeStruct.name = name;
	timeStruct.soname = soname;

	//timeStruct.name = coutCin("Введите Имя: ");
	//timeStruct.soname = coutCin("Введите Фамилию: ");
	do {
		if (!check) {
			cout << "Вы ввели некоректную дату рождения" << endl;
		}
		string days = coutCin("Введите день рождения ");
		day = atoi(days.c_str());
		string months = coutCin("Введите месяц рождения ");
		month = atoi(months.c_str());
		string years = coutCin("Введите год рождения ");
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

//MARK: Добавление нового элемента в список в конец
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
			cout << "Пользователь успешно добавлен" << endl;
	}
	else {
		cout << "Такой пользователь уже есть" << endl;
	}
}


//MARK: Меню
void menu() {
	cout << "/-----------------------------------------------\\" << endl;
	cout << "|            Информация о сотрудниках           |" << endl;
	cout << "|-----------------------------------------------|" << endl;
	cout << "| 1 - добавление нового пользователя            |" << endl;
	cout << "| 2 - поиск по месяцам                          |" << endl;
	cout << "| 3 - изменение данных пользователя             |" << endl;
	cout << "| 4 - сортировка пользователей по знаку зодиака |" << endl;
	cout << "| 5 - удалить пользователя                      |" << endl;
	cout << "| 6 - сохранение данных                         |" << endl;
	cout << "| 7 - вывод на экран списка пользователей       |" << endl;
	cout << "| 8 - выход из программы                        |" << endl;
	cout << "\\-----------------------------------------------/" << endl << endl;
}


//MARK: Обработка строки
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


//MARK: Cчитывание данных из файла
void readData(list* &listt, string path) {

	ifstream file(path);

	if (!file) {
		cout << "файл не найден" << endl;
	}
	else {
		string line;
		while (getline(file, line)) {
			workWithFileLine(listt, line);
		}
		file.close();
	}
}

//MARK: Поиск людей по месяцу рождения
void findPeople(list* listt) {

	bool check = true;

	string monthRead = coutCin("Введите месяц, в котором родились люди: ");
	int month = atoi(monthRead.c_str());

	if (month<0 || month>12) {
		cout << "Некорректно введенный месяц" << endl;
	}
	else {
		while (listt) {
			if (listt->value.date[1] == month) {
				if (check == true) {
					cout << "/---------------------------------------------------------\\" << endl;
					cout << "|Имя        Фамилия        Дата рождения   Знак зодиака   |" << endl;
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
			cout << "В данном месяце никто не родился" << endl;
		}
	}

}

//MARK: Изменение имени
void changeName(list* & listt, string name, string soname, list* & list2) {
	list* head = listt;
	ZNAK time;

	string newName;
	cin.ignore();
	cout << "Введите имя " << endl;
	getline(cin, newName);

	//string newName = coutCin("Введите новое имя: ");
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
				cout << "Такой пользователь уже есть" << endl;
			}
			break;
		}
		listt = listt->next;
	}
	listt = head;

}

//MARK: Изменение фамилии
void changeSoname(list* & listt, string name, string soname, list* &list2) {
	list* head = listt;
	ZNAK time;

	string newName;
	cin.ignore();
	cout << "name " << endl;
	getline(cin, newName);

	//string newName = coutCin("Введите новую фамилию: ");
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
				cout << "Такой пользователь уже есть" << endl;
			}
			break;
		}
		listt = listt->next;
	}
	listt = head;
}

//MARK: Изменение даты рожедения и гороскопа автоматически
void changeDate(list* &listt, string name, string soname, list* &list2) {
	list* head = listt;
	string days = coutCin("Введите день рождения ");
	int day = atoi(days.c_str());
	string months = coutCin("Введите месяц рождения ");
	int month = atoi(months.c_str());
	string years = coutCin("Введите год рождения ");
	int year = atoi(years.c_str());
	ZNAK time;
	if (!checkDataFromFile(day, month, year)) {
		cout << "Вы ввели некоректную дату рождения" << endl;
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
					cout << "Такой пользователь уже есть" << endl;
				}
				break;
			}
			listt = listt->next;
		}
	}
	listt = head;
}

//MARK: Выбор изменения
void chose(list* &listt, list* &list2, string soname) {
	cout << "Что вы хотите изменить ?" << endl;
	cout << "1 - Имя" << endl;
	cout << "2 - Фамилия" << endl;
	cout << "3 - дата рождения" << endl;

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
		cout << "Такой команды не найдено " << endl;
		break;
	}
}

//MARK: Изменения данных
void dataChange(list* &listt) {

	string soname = coutCin("Введите фамилию пользователя: ");

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
		cout << "Такого пользователя нету" << endl;
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
		int personIndex = coutCinInt("Выберите нужного пользователя: ");
		if (personIndex > 0 && personIndex < count) {
			while (personIndex - 1) {
				list2 = list2->next;
				personIndex--;
			}
			chose(listt, list2, soname);
			list2 = temp2;
		}else {
			cout << "Такого пользователя нету" << endl;
		}
		listt = head;
		clear(list2);
	}

}

//MARK: Сохранение данных
void saveData(list* &listt, string path) {
	ofstream file(path);

	if (file.is_open()) {
		list* head = listt;
		while (listt) {
			file << listt->value.name << "#" << listt->value.soname << "#" << listt->value.date[0] << "#" << listt->value.date[1] << "#" << listt->value.date[2] << endl;
			listt = listt->next;
		}
		listt = head;
		cout << "Данные успешно сохранены " << endl;
	}
	else {
		cout << "Файл не создан" << endl;
	}
}

//MARK: Сортировка людей по знаку
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
		cout << "Список отсортирован." << endl << endl;

		cout << "1 - Сохранить отсортированный список " << endl;
		cout << "2 - Вывести отсортированный список " << endl;
		cout << "любой другой символ для продолжения работы" << endl;
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
		cout << "Список пуст" << endl;
	}
	cout << endl;
}

//MARK:Удаление элемента
void removeElement(list* &listt, list* &list2, int count) {
	//удаление первого элмента
	if (listt->value.soname == list2->value.soname) {
		list* tmp = listt;
		listt = listt->next;
		delete tmp;
		cout << "Пользователь удален" << endl;
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
		cout << "Пользователь удален" << endl;

		listt = temp;
		list2 = temp2;

	}
}

//MARK:Выбор элемента для удаления
void deleteEl(list* &listt) {
	string soname = coutCin("Введите фамилию пользвателя ");
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
		cout << "Пользователя с такой фамилией нету " << endl;
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
		string nums = coutCin("Введите номер элемента, который хотите удалить ");
		int num = atoi(nums.c_str());
		if (num>0 && num < count)
			removeElement(listt, list2, count);
		else
			cout << "Такого пользователя нету" << endl;
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

		string digites = coutCin("Выберите пункт меню: ");
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
				string saves = coutCin("Сохранить данные ? 1-да 2-нет ");
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
			cout << "Такой команды нету" << endl;
			break;
		}
	}
}
