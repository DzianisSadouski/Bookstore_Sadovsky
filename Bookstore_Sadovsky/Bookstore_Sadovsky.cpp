#include "Header.h"

int number_of_acc = 0;
int current_acc = -1;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    Account arr_of_acc[MAX_NUMBER_OF_ARR];

    Publisher publishers[MAX_PUBLISHERS];
    int publisherCount = 0;

    Book books[MAX_BOOKS];
    int bookCount = 0;

    int ch = 0;
    int choice = 0;

    readFileAcc(arr_of_acc, number_of_acc);
    while (ch == 0) {
        if (number_of_acc == 0) {
            registerAcc(arr_of_acc, number_of_acc);
        }
        cout << "\nАвторизоваться(1)\nЗарегистрироватьcя(2)\n";
        if (scanf_s("%d", &choice) == 1 && choice < 3 && choice > 0) {
            switch (choice) {
            case 1:
                current_acc = logIn(arr_of_acc, number_of_acc);
                if (current_acc > -1) {
                    ch = 1;
                }
                break;
            case 2:
                registerAcc(arr_of_acc, number_of_acc);
                break;
            }
        }
        else {
            scanf_s("%*[^\n]");
            printf("    Ошибка.\n");
        }
    }

    system("cls");

    string filename = "data.txt";
    loadFromFile(publishers, publisherCount, books, bookCount, filename);

    choice = 0;
    do {
        printPublishersTable(publishers, publisherCount, books, bookCount);

        cout << "\nМеню:\n"
            << "1. Добавить издательство\n"
            << "2. Редактировать издательство\n"
            << "3. Сортировать по названию\n"
            << "4. Сортировать по году основания\n"
            << "5. Сортировать по количеству книг\n"
            << "6. Сортировать по рейтингу\n"
            << "7. Сохранить данные в файл\n"
            << "8. Выйти\n"
            << "9. Управление аккаунтами - только для администратора\n"
            << "Введите ваш выбор: ";
        while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 9) {
            cout << "Ошибка! Введите число от 1 до 8: ";
            scanf_s("%*[^\n]");
        }

        switch (choice) {
        case 1:
            addPublisher(publishers, publisherCount);
            break;
        case 2: 
            int index;
            cout << "Введите номер издательства для редактирования: ";
            while (scanf_s("%d", &index) != 1 || index < 1 || index > publisherCount) {
                cout << "Ошибка! Введите корректный номер: ";
                scanf_s("%*[^\n]");
            }
            system("cls");
            editPublisher(publishers, publisherCount, books, bookCount, index - 1);
            break;
        case 3:
            sortPublishersByName(publishers, publisherCount);
            system("cls");
            cout << "Издатели отсортированы по названию!" << endl;
            break;
        case 4:
            sortPublishersByYear(publishers, publisherCount);
            system("cls");
            cout << "Издатели отсортированы по году основания!" << endl;
            break;
        case 5:
            sortPublishersByBookCount(publishers, publisherCount, books, bookCount);
            system("cls");
            cout << "Издатели отсортированы по количеству книг!" << endl;
            break;
        case 6:
            sortPublishersByRating(publishers, publisherCount);
            system("cls");
            cout << "Издатели отсортированы по рейтингу!" << endl;
            break;
        case 7:
            system("cls");
            saveToFile(publishers, publisherCount, books, bookCount, filename);
            break;
        case 8:
            cout << "Выход из программы." << endl;
            break;
        case 9:
            system("cls");
            if (arr_of_acc[current_acc].type == 1) {
                showStartAccArr(arr_of_acc, number_of_acc);
            }
            else {
                cout << "\nДанный вариант доступен только администратору.\n";
            }
            break;
        }
    } while (choice != 8);
}