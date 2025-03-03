#include "Header.h"

void readFileAcc(Account* arr_of_acc, int& number_of_acc)
{
    ifstream fin(FILE_OF_ACC, ios::in);
    if (!fin.is_open()) {
        cout << "Файл с пользовательскими данными не найден!\n Регистрация нового пользователя.\n\n";
    }
    else {
        int i = 0;
        while (!fin.eof())
        {
            if (i < MAX_NUMBER_OF_ARR) {

                getline(fin, arr_of_acc[i].username);
                fin >> arr_of_acc[i].password >> arr_of_acc[i].type >> arr_of_acc[i].access;
                fin.get();
                i++;
            }
            else {
                cout << "Недостаточно памяти для чтения всех данных!" << endl;
                break;
            }
        }
        number_of_acc = i;
    }
    fin.close();
}

void registerAcc(Account* arr_of_acc, int& number_of_acc) {
    if (number_of_acc + 1 <= MAX_NUMBER_OF_ARR) {
        number_of_acc++;

        int check = 1;
        while (check == 1) {
            check = 0;
            cout << "Введите имя пользователя: ";            
            getline(cin, arr_of_acc[number_of_acc - 1].username);
            int i = 0;
            while ((i < number_of_acc - 1) && check == 0) {
                if (arr_of_acc[number_of_acc - 1].username == arr_of_acc[i].username) {
                    cout << "Имя пользователя занято.\n";
                    check = 1;
                }
                i++;
            }
        }


        cout << "Введите пароль: ";
        cin >> arr_of_acc[number_of_acc - 1].password;

        if (number_of_acc == 1) {
            arr_of_acc[number_of_acc - 1].type = 1;
        }
        else {
            arr_of_acc[number_of_acc - 1].type = 2;
        }

        arr_of_acc[number_of_acc - 1].access = 1;

        writeFileAcc(arr_of_acc, number_of_acc);
    }
    else {
        cout << "Недостаточно памяти для добавления нового аккаунта!" << endl;
    }
}

int logIn(Account* arr_of_acc, int& number_of_acc) {
    string username;
    string password;
    cout << "Введите имя пользователя: ";
    cin >> username;
    int i = 0;
    int check = 0;
    while (i < number_of_acc && check == 0) {
        if (arr_of_acc[i].username == username) {
            check = 1;
            i--;
        }
        i++;
    }
    if (check == 1) {
        if (arr_of_acc[i].access == 1) {
            cout << "Введите пароль: ";
            cin >> password;
            if (arr_of_acc[i].password == password) {
                return i;
            }
            else {
                cout << "Пароль неверный.";
                return -1;
            }

        }
        else {
            cout << "Пользователь заблокирован.";
            return -1;
        }
    }
    else {
        cout << "Пользователь не найден.";
        return -1;
    }
}

void writeFileAcc(Account* arr_of_acc, int number_of_acc)
{
    ofstream fout(FILE_OF_ACC, ios::out);
    for (int i = 0; i < number_of_acc; i++) {
        fout << arr_of_acc[i].username << "\n" << arr_of_acc[i].password << " " << arr_of_acc[i].type << " " << arr_of_acc[i].access;
        if (i < number_of_acc - 1)
        {
            fout << endl;
        }
        cout << "sdfhdfshsdf   " << arr_of_acc[i].username;
    }
    fout.close();
}

void delAcc(Account* arr_of_acc, int& number_of_acc)
{
    int number_of_deleted_item;
    if (number_of_acc > 1) {

        cout << "Введите номер удаляемого аккаунта: ";

        if (scanf_s("%d", &number_of_deleted_item) == 1 && number_of_deleted_item - 1 >= 0 && number_of_deleted_item - 1 < number_of_acc) {
            number_of_deleted_item = number_of_deleted_item - 1;

            for (int i = number_of_deleted_item; i < number_of_acc - 1; i++) {
                arr_of_acc[i] = arr_of_acc[i + 1];
            }


            number_of_acc--;
            writeFileAcc(arr_of_acc, number_of_acc);

            int checkadmin = 0;
            int i = 0;
            while (i < number_of_acc && checkadmin == 0) {
                if (arr_of_acc[i].type == 1) {
                    checkadmin = 1;
                }
                i++;
            }
            if (checkadmin == 0) {
                arr_of_acc[0].type = 1;
            }
            system("cls");

        }
        else {
            scanf_s("%*[^\n]");
            system("cls");
            cout << "Введен некорректный номер удалемого аккаунта!" << endl;
        }
    }
    else {
        system("cls");
        cout << "Нельзя удалить единственный аккаунт.";
    }
}

void blockAcc(Account* arr_of_acc, int& number_of_acc)
{
    int number_of_block_Acc;

    if (number_of_acc > 1) {

        cout << "Введите номер блокируемого аккаунта: ";
        if (scanf_s("%d", &number_of_block_Acc) == 1 && number_of_block_Acc - 1 >= 0 && number_of_block_Acc - 1 < number_of_acc) {
            number_of_block_Acc--;
            if (arr_of_acc[number_of_block_Acc].type == 1) {
                int checkadmin = 0;
                int i = 0;
                while (i < number_of_acc) {
                    if (arr_of_acc[i].type == 1 && arr_of_acc[i].access == 1) {
                        checkadmin++;
                    }
                    i++;
                }

                if (checkadmin > 1) {
                    arr_of_acc[number_of_block_Acc].access = 2;
                    system("cls");
                    cout << "Аккаунт " << arr_of_acc[number_of_block_Acc].username << " заблокирован." << endl;
                }
                else {
                    system("cls");
                    cout << "Нельзя заблокировать единственный доступный аккаунт администратора." << endl;
                }
            }
            else {
                arr_of_acc[number_of_block_Acc].access = 2;
                system("cls");
                cout << "Аккаунт " << arr_of_acc[number_of_block_Acc].username << " заблокирован." << endl;
            }
        }
        else {
            scanf_s("%*[^\n]");
            system("cls");
            cout << "Введен некорректный номер блокируемого аккаунта!" << endl;
        }

    }
    else {
        system("cls");
        cout << "Нельзя заблокировать единственный аккаунт.";
    }
    writeFileAcc(arr_of_acc, number_of_acc);
}

void unblockAcc(Account* arr_of_acc, int& number_of_acc)
{
    int number_of_unblock_Acc;
    cout << "Введите номер разблокируемого аккаунта: ";
    if (scanf_s("%d", &number_of_unblock_Acc) == 1 && number_of_unblock_Acc - 1 >= 0 && number_of_unblock_Acc - 1 < number_of_acc) {
        number_of_unblock_Acc--;
        if (arr_of_acc[number_of_unblock_Acc].access == 2) {
            arr_of_acc[number_of_unblock_Acc].access = 1;
            system("cls");
        }
        else {
            system("cls");
            cout << "Данный аккаунт не заблокирован.";
        }
    }
    else {
        scanf_s("%*[^\n]");
        system("cls");
        cout << "Введен некорректный номер аккаунта!" << endl;
    }
    writeFileAcc(arr_of_acc, number_of_acc);
}

void changeAccType(Account* arr_of_acc, int& number_of_acc)
{
    int number_of_change_Acc;
    cout << "Введите номер меняемого типа аккаунта: ";
    if (scanf_s("%d", &number_of_change_Acc) == 1 && number_of_change_Acc - 1 >= 0 && number_of_change_Acc - 1 < number_of_acc) {
        number_of_change_Acc--;
        if (arr_of_acc[number_of_change_Acc].type == 1) {
            int checkadmin = 0;
            int i = 0;
            while (i < number_of_acc) {
                if (arr_of_acc[i].type == 1 && arr_of_acc[i].access == 1) {
                    checkadmin++;
                }
                i++;
            }
            if (checkadmin > 1) {
                arr_of_acc[number_of_change_Acc].type = 2;
                system("cls");
                cout << "Теперь " << arr_of_acc[number_of_change_Acc].username << " пользователь." << endl;
            }
            else {
                system("cls");
                cout << "Нельзя сделать пользователем единственного доступного администратора." << endl;
            }
        }
        else {
            arr_of_acc[number_of_change_Acc].type = 1;
            system("cls");
            cout << "Теперь " << arr_of_acc[number_of_change_Acc].username << " администратор." << endl;
        }
    }
    else {
        system("cls");
        scanf_s("%*[^\n]");
        cout << "Введен некорректный номер аккаунта!" << endl;
    }
    writeFileAcc(arr_of_acc, number_of_acc);
}

void showStartAccArr(Account* arr_of_acc, int number_of_acc) {
    int ch = 0;
    int choice = 0;

    while (ch == 0) {
        showAccArr(arr_of_acc, number_of_acc);
        cout << "\nИзменить статус аккаунта(пользователь-администратор)(1)\nЗаблокировать аккаунт(2)\nРазблокировать аккаунт(3)\nУдалить аккаунт(4)\nНазад(5)\n";
        if (scanf_s("%d", &choice) == 1 && choice < 6 && choice > 0) {
            switch (choice) {
            case 1:
                changeAccType(arr_of_acc, number_of_acc);
                break;
            case 2:
                blockAcc(arr_of_acc, number_of_acc);
                break;
            case 3:
                unblockAcc(arr_of_acc, number_of_acc);
                break;
            case 4:
                delAcc(arr_of_acc, number_of_acc);
                break;
            case 5:
                system("cls");
                ch = 1;
                break;
            }
        }
        else {
            system("cls");
            scanf_s("%*[^\n]");
            printf("    Ошибка.\n");
        }
    }
}

void showAccArr(Account* arr_of_acc, int number_of_acc) {

    for (int i = 0; i < number_of_acc; i++) {
        cout << "\n" << i + 1 << ") " << arr_of_acc[i].username << " - ";
        if (arr_of_acc[i].type == 1) {
            cout << "администратор";
        }
        else {
            cout << "пользователь";
        }

        if (arr_of_acc[i].access != 1) {
            cout << " - заблокирован\n";
        }
        else {
            cout << "\n";
        }
    }
}



void addPublisher(Publisher publishers[], int& publisherCount) {
    if (publisherCount >= MAX_PUBLISHERS) {
        cout << "Достигнуто максимальное количество издательств!" << endl;
    }
    else {
        Publisher newPublisher;
        bool isUnique;
        do {
            cout << "Введите название издательства: ";
            cin.ignore();
            getline(cin, newPublisher.name);

            // Проверка на уникальность имени издательства
            isUnique = true;
            for (int i = 0; i < publisherCount; i++) {
                if (publishers[i].name == newPublisher.name) {
                    cout << "Ошибка! Издательсво с таким названием уже существует.\n";
                    isUnique = false;
                }
            }
        } while (!isUnique);



        cout << "Введите год основания: ";
        while (scanf_s("%d", &newPublisher.yearFounded) != 1 || newPublisher.yearFounded < 0) {
            cout << "Ошибка! Введите корректный год: ";
            scanf_s("%*[^\n]");
        }

        newPublisher.booksPublished = 0;

        cout << "Введите рейтинг: ";
        while (scanf_s("%f", &newPublisher.rating) != 1 || newPublisher.rating < 0 || newPublisher.rating > 10) {
            cout << "Ошибка! Введите рейтинг от 0 до 10: ";
            scanf_s("%*[^\n]");
        }

        publishers[publisherCount] = newPublisher;
        publisherCount++;
        system("cls");
        cout << "Издательство добавлено!" << endl;
    }
}

void addBook(Book books[], int& bookCount, Publisher publishers[], int publisherCount, const string& publisherName) {
    if (bookCount >= MAX_BOOKS) {
        cout << "Достигнуто максимальное количество книг!" << endl;
    }
    else {
        Book newBook;
        cout << "Введите название книги: ";
        cin.ignore();
        getline(cin, newBook.title);

        cout << "Введите автора книги: ";
        //cin.ignore();
        getline(cin, newBook.author);

        cout << "Введите год публикации: ";
        while (scanf_s("%d", &newBook.yearPublished) != 1 || newBook.yearPublished < 0) {
            cout << "Ошибка! Введите корректный год: ";
            scanf_s("%*[^\n]");
        }

        newBook.publisherName = publisherName;

        // Поиск издательства и обновление количества книг
        for (int i = 0; i < publisherCount; i++) {
            if (publishers[i].name == publisherName) {
                publishers[i].booksPublished++;
            }
        }
        books[bookCount] = newBook;
        bookCount++;
        system("cls");
        cout << "Книга добавлена!" << endl;
    }
}

string formatBookList(const Book books[], int bookCount, const string& publisherName) {
    string bookList;
    int currentLength = 0;
    bool lastBook = false;
    string prevName;

    for (int i = 0; i < bookCount; i++) {
        if (books[i].publisherName == publisherName && currentLength <= MAX_BOOK_LIST_LENGTH - 5) {
            if (currentLength + books[i].title.length() + 2 < MAX_BOOK_LIST_LENGTH - 5) {
                if (bookList.empty()) {
                    bookList += books[i].title;
                    currentLength += books[i].title.length();
                }
                else {
                    bookList += ", " + books[i].title;
                    currentLength += 2 + books[i].title.length();
                }
            }
            else {
                if (!bookList.empty()) {
                    bookList += ", ";
                    currentLength += 2;
                }
                
                bookList += books[i].title.substr(0, MAX_BOOK_LIST_LENGTH - 3 - currentLength);
                prevName = books[i].title.substr(0, MAX_BOOK_LIST_LENGTH - 3 - currentLength);
                currentLength += books[i].title.substr(0, MAX_BOOK_LIST_LENGTH - 3 - currentLength).length();
            }
        }

        if (books[i].publisherName == publisherName && currentLength == MAX_BOOK_LIST_LENGTH - 3 && books[i].title.length() > 1) {
            if (lastBook || books[i].title != prevName) {
                bookList += "...";
                currentLength += 3;
            }
            else {
                lastBook = true;
            } 
        }
    }

    if (bookList.empty()) {
        bookList = "Нет книг";
    }

    return bookList;
}

void printPublishersTable(const Publisher publishers[], int publisherCount, const Book books[], int bookCount) {
    cout << "+-----+---------------------+---------------+-------------+---------+-----------------------------+" << endl;
    cout << "|  №  | Название            | Год основания | Кол-во книг | Рейтинг | Книги                       |" << endl;
    cout << "+-----+---------------------+---------------+-------------+---------+-----------------------------+" << endl;

    for (int i = 0; i < publisherCount; i++) {
        string bookList = formatBookList(books, bookCount, publishers[i].name);

        cout << "| " << right << setw(3) << i + 1 << " | " << left << setw(19);

        if (publishers[i].name.length() > 16) {
            cout << publishers[i].name.substr(0, 16) + "...";
        }
        else {
            cout << publishers[i].name;
        }

        cout << " | " << right << setw(13) << publishers[i].yearFounded << " | "
            << right << setw(11) << publishers[i].booksPublished << " | "
            << right << setw(7) << fixed << setprecision(1) << publishers[i].rating << " | "
            << left << setw(27) << bookList << " |" << endl;
    }

    cout << "+-----+---------------------+---------------+-------------+---------+-----------------------------+" << endl;
}

void printBooksTable(const Book books[], int bookCount, const string& publisherName) {
    cout << "+-----+----------------------------------------------+---------------------+----------------+" << endl;
    cout << "|  №  | Название книги                               | Автор               | Год публикации |" << endl;
    cout << "+-----+----------------------------------------------+---------------------+----------------+" << endl;

    int bookIndex = 1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].publisherName == publisherName) {
            cout << "| " << right << setw(3) << bookIndex++ << " | " << left << setw(44);

            if (books[i].title.length() > 41) {
                cout << books[i].title.substr(0, 41) + "...";
            }
            else {
                cout << books[i].title;
            }

            cout << " | " << left << setw(19);


            if (books[i].author.length() > 16) {
                cout << books[i].author.substr(0, 16) + "...";
            }
            else {
                cout << books[i].author;
            }

            cout << " | " << right << setw(14) << books[i].yearPublished << " | " << endl;
        }
    }

    cout << "+-----+----------------------------------------------+---------------------+----------------+" << endl;
}

void loadFromFile(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        publisherCount = 0;
        bookCount = 0;
        string line;
        bool readingPublishers = false;
        bool readingBooks = false;

        while (getline(inFile, line)) {
            if (line == "Publishers:") {
                readingPublishers = true;
                readingBooks = false;
                continue;
            }
            else if (line == "Books:") {
                readingPublishers = false;
                readingBooks = true;
                continue;
            }

            if (readingPublishers && publisherCount < MAX_PUBLISHERS) {
                Publisher newPublisher;
                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);

                newPublisher.name = line.substr(0, pos1);             
                newPublisher.yearFounded = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                newPublisher.booksPublished = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                newPublisher.rating = stod(line.substr(pos3 + 1));

                publishers[publisherCount] = newPublisher;
                publisherCount++;
            }
            else if (readingBooks && bookCount < MAX_BOOKS) {
                Book newBook;
                size_t pos1 = line.find('|');
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);

                newBook.title = line.substr(0, pos1);
                
                newBook.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                newBook.yearPublished = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                newBook.publisherName = line.substr(pos3 + 1);
                
                books[bookCount] = newBook;
                bookCount++;
            }
        }

        inFile.close();
        cout << "Данные загружены из файла." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для чтения!" << endl;
    }
}

void saveToFile(const Publisher publishers[], int publisherCount, const Book books[], int bookCount, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Publishers:" << endl;
        for (int i = 0; i < publisherCount; i++) {
            outFile << publishers[i].name << "|"
                << publishers[i].yearFounded << "|"
                << publishers[i].booksPublished << "|"
                << publishers[i].rating << endl;
        }

        outFile << "Books:" << endl;
        for (int i = 0; i < bookCount; i++) {
            outFile << books[i].title << "|"
                << books[i].author << "|"
                << books[i].yearPublished << "|"
                << books[i].publisherName << endl;
        }

        outFile.close();
        cout << "Данные сохранены в файл." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи!" << endl;
    }
}


void deleteBook(Book books[], int& bookCount, Publisher publishers[], int publisherCount, int bookOnePublisherIndex, string publisherName) {
    int bookIndex = -1;
    int OnePublisherIndex = 0;

    do {
        bookIndex++;

        if (books[bookIndex].publisherName == publisherName) {
            OnePublisherIndex++;
        }
    } while (OnePublisherIndex != bookOnePublisherIndex);

    string oldTitle = books[bookIndex].title;

    // Уменьшаем количество книг у издательства
    for (int i = 0; i < publisherCount; i++) {
        if (publishers[i].name == publisherName) {
            publishers[i].booksPublished--;
        }
    }

    // Сдвигаем все книги после удаляемой на одну позицию влево
    for (int i = bookIndex; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }

    // Уменьшаем общее количество книг
    bookCount--;
    system("cls");
    cout << "Книга '" << oldTitle << "' успешно удалена!" << endl;
}

// Функция для удаления издательства и связанных книг
void deletePublisher(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, int index) {
    string publisherName = publishers[index].name;

    // Удаляем все книги, связанные с этим издательством
    int i = 0;
    while (i < bookCount) {
        if (books[i].publisherName == publisherName) {
            deleteBook(books, bookCount, publishers, publisherCount, 1, publisherName);
        }
        else {
            i++; // Переходим к следующей книге, если текущая не связана с удаляемым издательством
        }
    }

    // Удаляем издательство из массива
    for (int j = index; j < publisherCount - 1; j++) {
        publishers[j] = publishers[j + 1];
    }
    publisherCount--;

    system("cls");
    cout << "Издательство '" << publisherName << "' и все связанные книги успешно удалены!" << endl;
}

void sortBooksByTitleForPublisher(Book books[], int bookCount, const string& publisherName) {
    // Применяем сортировку методом пузырька только для книг одного издательства
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (books[j].publisherName == publisherName && books[j + 1].publisherName == publisherName) {
                if (books[j].title > books[j + 1].title) {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
}

void sortBooksByAuthorForPublisher(Book books[], int bookCount, const string& publisherName) {
    // Применяем сортировку методом пузырька только для книг одного издательства
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (books[j].publisherName == publisherName && books[j + 1].publisherName == publisherName) {
                if (books[j].author > books[j + 1].author) {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
}

void sortBooksByYearForPublisher(Book books[], int bookCount, const string& publisherName) {
    // Применяем сортировку методом пузырька только для книг одного издательства
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (books[j].publisherName == publisherName && books[j + 1].publisherName == publisherName) {
                if (books[j].yearPublished > books[j + 1].yearPublished) {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
}

void sortPublishersByName(Publisher publishers[], int publisherCount) {
    for (int i = 0; i < publisherCount - 1; i++) {
        for (int j = 0; j < publisherCount - 1 - i; j++) {
            if (publishers[j].name > publishers[j + 1].name) {
                Publisher temp = publishers[j];
                publishers[j] = publishers[j + 1];
                publishers[j + 1] = temp;
            }
        }
    }
}

void sortPublishersByYear(Publisher publishers[], int publisherCount) {
    for (int i = 0; i < publisherCount - 1; i++) {
        for (int j = 0; j < publisherCount - 1 - i; j++) {
            if (publishers[j].yearFounded > publishers[j + 1].yearFounded) {
                Publisher temp = publishers[j];
                publishers[j] = publishers[j + 1];
                publishers[j + 1] = temp;
            }
        }
    }
}

void sortPublishersByBookCount(Publisher publishers[], int publisherCount, Book books[], int bookCount) {
    for (int i = 0; i < publisherCount - 1; i++) {
        for (int j = 0; j < publisherCount - 1 - i; j++) {
            int bookCount1 = 0, bookCount2 = 0;
            for (int k = 0; k < bookCount; k++) {
                if (books[k].publisherName == publishers[j].name) {
                    bookCount1++;
                }
                if (books[k].publisherName == publishers[j + 1].name) {
                    bookCount2++;
                }
            }
            if (bookCount1 < bookCount2) {
                Publisher temp = publishers[j];
                publishers[j] = publishers[j + 1];
                publishers[j + 1] = temp;
            }
        }
    }
}

void sortPublishersByRating(Publisher publishers[], int publisherCount) {
    for (int i = 0; i < publisherCount - 1; i++) {
        for (int j = 0; j < publisherCount - 1 - i; j++) {
            if (publishers[j].rating < publishers[j + 1].rating) {
                Publisher temp = publishers[j];
                publishers[j] = publishers[j + 1];
                publishers[j + 1] = temp;
            }
        }
    }
}

void editPublisher(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, int index) {
    int choice;
    string oldName;
    int bookCountOnePublisher;
    do {
        cout << "Редактирование издательства: " << publishers[index].name << " | "
            << publishers[index].yearFounded << " | "
            << publishers[index].rating << endl;

        printBooksTable(books, bookCount, publishers[index].name);

        cout << "\nМеню редактирования:\n"
            << "1. Добавить книгу\n"
            << "2. Удалить книгу\n"
            << "3. Сортировать по названию книги\n"
            << "4. Сортировать по автору\n"
            << "5. Сортировать по году публикации\n"
            << "6. Изменить данные издательства\n"
            << "7. Удалить издательство\n"
            << "8. Вернуться в главное меню\n"
            << "Введите ваш выбор: ";
        while (scanf_s("%d", &choice) != 1 || choice < 1 || choice > 8) {
            cout << "Ошибка! Введите число от 1 до 8: ";
            scanf_s("%*[^\n]");
        }

        switch (choice) {
        case 1:
            addBook(books, bookCount, publishers, publisherCount, publishers[index].name);
            break;
        case 2:
            int bookOnePublisherIndex;
            bookCountOnePublisher = 0;

            for (int i = 0; i < bookCount; i++) {
                if (books[i].publisherName == publishers[index].name) {
                    bookCountOnePublisher++;
                }
            }

            cout << "Введите номер книги для удаления: ";
            if (scanf_s("%d", &bookOnePublisherIndex) != 1 || bookOnePublisherIndex < 1 || bookOnePublisherIndex > bookCountOnePublisher) {
                system("cls");
                cout << "Ошибка! Введён некорректный номер.\n";
                scanf_s("%*[^\n]");
            }
            else {
                deleteBook(books, bookCount, publishers, publisherCount, bookOnePublisherIndex, publishers[index].name);
            }
            break;
        case 3:
            sortBooksByTitleForPublisher(books, bookCount, publishers[index].name);
            system("cls");
            cout << "Книги издательства отсортированы по названию!" << endl;
            break;
        case 4:
            sortBooksByAuthorForPublisher(books, bookCount, publishers[index].name);
            system("cls");
            cout << "Книги издательства отсортированы по автору!" << endl;
            break;
        case 5:
            sortBooksByYearForPublisher(books, bookCount, publishers[index].name);
            system("cls");
            cout << "Книги издательства отсортированы по году публикации!" << endl;
            break;
        case 6:
            oldName = publishers[index].name;

            cout << "Введите новое название издательства: ";
            cin.ignore();
            getline(cin, publishers[index].name);

            // Обновляем имя издательства у связанных книг
            for (int i = 0; i < bookCount; i++) {
                if (books[i].publisherName == oldName) {
                    books[i].publisherName = publishers[index].name;
                }
            }

            cout << "Введите новый год основания: ";
            while (scanf_s("%d", &publishers[index].yearFounded) != 1 || publishers[index].yearFounded < 0) {
                cout << "Ошибка! Введите корректный год: ";
                scanf_s("%*[^\n]");
            }

            cout << "Введите новый рейтинг: ";
            while (scanf_s("%f", &publishers[index].rating) != 1 || publishers[index].rating < 0 || publishers[index].rating > 10) {
                cout << "Ошибка! Введите рейтинг от 0 до 10: ";
                scanf_s("%*[^\n]");
            }
            system("cls");
            break;
        case 7:
            char saveChoice;
            cout << "Вы уверены, что хотите удалить издательство и связанные с ним книги? (y/n): ";
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') {
                deletePublisher(publishers, publisherCount, books, bookCount, index);
            }
            else {
                choice = 0;
                system("cls");
            }
            break;
        case 8:
            system("cls");
            cout << "Возврат в главное меню." << endl;
            break;
        }
    } while (choice != 8 && choice != 7);
}
