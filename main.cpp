#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

struct Event
{
    string name;
    string date;
    string place;
};

vector<Event> events;
const string FILE_NAME = "events.txt";

void saveToFile()
{
    ofstream file(FILE_NAME);

    for (const auto& e : events)
    {
        file << e.name << "|"
             << e.date << "|"
             << e.place << endl;
    }

    file.close();
}

void loadFromFile()
{
    ifstream file(FILE_NAME);

    if (!file)
        return;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        Event e;

        getline(ss, e.name, '|');
        getline(ss, e.date, '|');
        getline(ss, e.place, '|');

        events.push_back(e);
    }

    file.close();
}

bool isFutureDate(const string& date)
{
    time_t now = time(0);
    tm* current = localtime(&now);

    int currentYear = current->tm_year + 1900;
    int currentMonth = current->tm_mon + 1;
    int currentDay = current->tm_mday;

    int year, month, day;

    if (sscanf(date.c_str(), "%d-%d-%d",
               &year, &month, &day) != 3)
    {
        return false;
    }

    if (year > currentYear)
        return true;

    if (year == currentYear && month > currentMonth)
        return true;

    if (year == currentYear &&
        month == currentMonth &&
        day >= currentDay)
        return true;

    return false;
}

void addEvent()
{
    Event e;

    cin.ignore();

    cout << "\nНазва події: ";
    getline(cin, e.name);

    cout << "Дата (YYYY-MM-DD): ";
    getline(cin, e.date);

    cout << "Місце проведення: ";
    getline(cin, e.place);

    events.push_back(e);

    saveToFile();

    cout << "\nПодію успішно додано!\n";
}

void showFutureEvents()
{
    cout << "\n===== Майбутні події =====\n";

    bool found = false;

    for (const auto& e : events)
    {
        if (isFutureDate(e.date))
        {
            cout << "\nНазва: " << e.name
                 << "\nДата: " << e.date
                 << "\nМісце: " << e.place
                 << "\n-------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "Майбутніх подій немає.\n";
    }
}

void showPastEvents()
{
    cout << "\n===== Минулі події =====\n";

    bool found = false;

    for (const auto& e : events)
    {
        if (!isFutureDate(e.date))
        {
            cout << "\nНазва: " << e.name
                 << "\nДата: " << e.date
                 << "\nМісце: " << e.place
                 << "\n-------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "Минулих подій немає.\n";
    }
}

void searchEvent()
{
    cin.ignore();

    string keyword;

    cout << "\nВведіть назву події: ";
    getline(cin, keyword);

    bool found = false;

    for (const auto& e : events)
    {
        if (e.name.find(keyword) != string::npos)
        {
            cout << "\nНазва: " << e.name
                 << "\nДата: " << e.date
                 << "\nМісце: " << e.place
                 << "\n-------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nПодію не знайдено.\n";
    }
}

void menu()
{
    cout << "\n=================================";
    cout << "\n       МЕНЕДЖЕР ПОДІЙ";
    cout << "\n=================================";
    cout << "\n1. Додати подію";
    cout << "\n2. Переглянути майбутні події";
    cout << "\n3. Переглянути минулі події";
    cout << "\n4. Пошук події";
    cout << "\n5. Вихід";
    cout << "\n=================================";
    cout << "\nВаш вибір: ";
}

int main()
{
    loadFromFile();

    int choice;

    do
    {
        menu();

        while (!(cin >> choice))
        {
            cout << "\nПомилка! Введіть число: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice)
        {
            case 1:
                addEvent();
                break;

            case 2:
                showFutureEvents();
                break;

            case 3:
                showPastEvents();
                break;

            case 4:
                searchEvent();
                break;

            case 5:
                cout << "\nРоботу завершено.\n";
                break;

            default:
                cout << "\nНевірний пункт меню!\n";
        }

    } while (choice != 5);

    return 0;
}