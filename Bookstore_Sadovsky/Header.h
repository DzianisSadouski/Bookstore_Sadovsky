#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <windows.h> // Для очистки экрана system("cls");

#define _CRT_SECURE_NO_WARNINGS //Для scanf_s("%*[^\n]");

using namespace std;

const int MAX_NUMBER_OF_ARR = 1000;
const string FILE_OF_ACC = "ArrOfAccount.txt";
const int MAX_PUBLISHERS = 100;
const int MAX_BOOKS = 1000;
const int MAX_BOOK_LIST_LENGTH = 27;

struct Account {
    string username;
    string password;
    int type;// 1 - admin, 2 - user
    int access;// 1 - active, 2 - blocked
};

struct Publisher {
    string name;
    int yearFounded;
    int booksPublished;
    float rating;
};

struct Book {
    string title;
    string author;
    int yearPublished;
    string publisherName;
};

void readFileAcc(Account* arr_of_acc, int& number_of_acc);
void registerAcc(Account* arr_of_acc, int& number_of_acc);
int logIn(Account* arr_of_acc, int& number_of_acc);
void writeFileAcc(Account* arr_of_acc, int number_of_acc);
void delAcc(Account* arr_of_acc, int& number_of_acc);
void blockAcc(Account* arr_of_acc, int& number_of_acc);
void unblockAcc(Account* arr_of_acc, int& number_of_acc);
void changeAccType(Account* arr_of_acc, int& number_of_acc);
void showStartAccArr(Account* arr_of_acc, int number_of_acc);
void showAccArr(Account* arr_of_acc, int number_of_acc);

void addPublisher(Publisher publishers[], int& publisherCount);
void addBook(Book books[], int& bookCount, Publisher publishers[], int publisherCount, const string& publisherName);
string formatBookList(const Book books[], int bookCount, const string& publisherName);
void printPublishersTable(const Publisher publishers[], int publisherCount, const Book books[], int bookCount);
void printBooksTable(const Book books[], int bookCount, const string& publisherName);
void loadFromFile(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, const string& filename);
void saveToFile(const Publisher publishers[], int publisherCount, const Book books[], int bookCount, const string& filename);
void deleteBook(Book books[], int& bookCount, Publisher publishers[], int publisherCount, int bookOnePublisherIndex, string publisherName);
void deletePublisher(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, int index);
void sortBooksByTitleForPublisher(Book books[], int bookCount, const string& publisherName);
void sortBooksByAuthorForPublisher(Book books[], int bookCount, const string& publisherName);
void sortBooksByYearForPublisher(Book books[], int bookCount, const string& publisherName);
void sortPublishersByName(Publisher publishers[], int publisherCount);
void sortPublishersByYear(Publisher publishers[], int publisherCount);
void sortPublishersByBookCount(Publisher publishers[], int publisherCount, Book books[], int bookCount);
void sortPublishersByRating(Publisher publishers[], int publisherCount);
void editPublisher(Publisher publishers[], int& publisherCount, Book books[], int& bookCount, int index);
