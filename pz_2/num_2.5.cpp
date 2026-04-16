// Завдання 2.5
// 1. Ввести з клавіатури рядок символів і обробити її у відповідності зі своїм варіантом, використовуючи функції.
// 2. Створити програми обробки рядка
// Варіант 11
// Завдання 1 - Видалити кожне парне слово з рядка.
// Завдання 2 - Ввести символьну матрицю. Інвертувати її відносно середини рядку. Перетворити матрицю у стринг. Знайти довжину стринга.

#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

const int MAX_SIZE = 100;

void deleteEvenWords(char* str) {
    char result[MAX_SIZE * 10] = "";    
    char temp[MAX_SIZE] = "";          
    int wordIndex = 1;                  
    int i = 0, resIndex = 0;
    
    while (str[i] != '\0') {
        while (str[i] == ' ') {
            result[resIndex++] = str[i++];
        }
        if (str[i] == '\0') break;
        int tempIndex = 0;
        while (str[i] != ' ' && str[i] != '\0') {
            temp[tempIndex++] = str[i++];
        }
        temp[tempIndex] = '\0';
        if (wordIndex % 2 != 0) {
            for (int j = 0; temp[j] != '\0'; j++) {
                result[resIndex++] = temp[j];
            }
        }
        
        wordIndex++;
    }
    result[resIndex] = '\0';
    
    for (int j = 0; j <= resIndex; j++) {
        str[j] = result[j];
    }
}
void task1() {
    cin.ignore(); 
    char str[MAX_SIZE * 10];
    cout << "Введіть рядок символів: ";
    cin.getline(str, MAX_SIZE * 10);
    cout << "\nВихідний рядок: " << str << endl;
    deleteEvenWords(str);
    cout << "Рядок після видалення парних слів: " << str << endl;
}


void inputMatrix(char** matrix, int rows, int cols) {
    cin.ignore();
    cout << "Введіть символьну матрицю (" << rows << " x " << cols << "):" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "Рядок " << i + 1 << ": ";
        cin.getline(matrix[i], cols + 1); 
    }
}


void printMatrix(char** matrix, int rows, int cols) {
    cout << "\nСимвольна матриця:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

void invertString(char* str, int length) {      //інверт. рядка
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}
void invertMatrix(char** matrix, int rows, int cols) {  //інверт. всієї матриці
    for (int i = 0; i < rows; i++) {    
        int len = strlen(matrix[i]);
        invertString(matrix[i], len);
    }
}

string matrixToString(char** matrix, int rows, int cols) {      //матриця у стринг
    string result = "";
    
    for (int i = 0; i < rows; i++) {
        result += matrix[i];
    }
    
    return result;
}
void task2() {
    int rows, cols;
    
    cout << "\nВведіть кількість рядків симвільної матриці: ";
    cin >> rows;
    cout << "Введіть кількість стовпців симвільної матриці: ";
    cin >> cols;

    char** matrix = new char* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new char[cols + 1]; 
    }
    inputMatrix(matrix, rows, cols);

    printMatrix(matrix, rows, cols);

    invertMatrix(matrix, rows, cols);
    

    cout << "\nІнвертована матриця:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << matrix[i] << endl;
    }
    string resultString = matrixToString(matrix, rows, cols);
    
    cout << "\nОтриманий стринг: \"" << resultString << "\"" << endl;
    cout << "Довжина стринга: " << resultString.length() << " символів" << endl;
    
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


int main() {
    int choice;
    do {
        cout << "\n1. Завдання 1" << endl;
        cout << "2. Завдання 2" << endl;
        cout << "Вибір: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
        }
    } while (choice != 2);
    return 0;
}

// Перше завдання - робота з рядком символів. Потрібно було видалити всі слова, які стоять на парних позиціях. Для цього 
// в функції deleteEvenWords проходимо по вхідному рядку, розбиваємо його на слова за пробілами, нумеруємо слова, починаючи з 
// одиниці, і якщо номер слова непарний - копіюємо його в новий рядок result, а парні слова просто пропускаємо. Також зберігаємо 
// пробіли між словами, щоб не порушити форматування. Наприкінці отриманий рядок копіюється назад у вихідний масив str.

// Друге завдання - робота з символьним двовимірним масивом, тобто матрицею. Ми повинні ввести кількість рядків та стовпців, після 
// чого функція inputMatrix заповнює матрицю рядками символів за допомогою cin.getline. Потім функція printMatrix виводить її на екран. 
// Далі викликається invertMatrix, яка для кожного рядка матриці визначає його довжину за допомогою strlen і передає цей рядок у функцію 
// invertString. Остання інвертує рядок. Після інвертування всіх рядків матриця знову виводиться. Наступним кроком викликається функція 
// matrixToString, яка просто з'єднує всі рядки матриці в string. Потім цей рядок виводиться на екран. За допомогою методу 
// length() визначається його довжина.



// Результат:
// 1. Завдання 1
// 2. Завдання 2
// Вибір: 1
// Введіть рядок символів: aaa bbbbb cccc dddd eeeee

// Вихідний рядок: aaa bbbbb cccc dddd eeeee
// Рядок після видалення парних слів: aaa  cccc  eeeee

// 1. Завдання 1
// 2. Завдання 2
// Вибір: 2

// Введіть кількість рядків симвільної матриці: 3
// Введіть кількість стовпців симвільної матриці: 5
// Введіть символьну матрицю (3 x 5):
// Рядок 1: abcde
// Рядок 2: qwert 
// Рядок 3: 12345

// Символьна матриця:
// abcde
// qwert
// 12345

// Інвертована матриця:
// edcba
// trewq
// 54321

// Отриманий стринг: "edcbatrewq54321"
// Довжина стринга: 15 символів