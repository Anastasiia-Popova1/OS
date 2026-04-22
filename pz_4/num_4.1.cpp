// Завдання 1 (C++).
// 1. Використовуючи введення-виведення в стилі С + + створити файл та записати в нього структуровані дані.
// 2. Вивести створений файл на екран.
// 3. Видалити з файлу дані відповідно до варіанта.
// 4. Додати в файл дані відповідно до варіанта.
// 5. Вивести змінений файл на екран.

// № варианта - 11.
// Структура данных - 
// Структура "DVD-диск":
// -	название фильма;
// -	режиссер;
// -	продолжительность;
// -	цена.
// Удаление - Удалить все элементы с ценой выше заданной.
// Добавление - Добавить элемент с номером К.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

struct DVD {
    string name;
    string director;
    int duration;
    float price;
};

DVD inputDVD() {
    DVD dvd;
    cout << "Назва фільму: ";
    getline(cin, dvd.name);
    cout << "Режисер: ";
    getline(cin, dvd.director);
    cout << "Тривалість (хв): ";
    cin >> dvd.duration;
    cout << "Ціна: ";
    cin >> dvd.price;
    cin.ignore();
    return dvd;
}

void printDVD(const DVD& dvd) {
    cout << left << setw(30) << dvd.name << " | "
         << setw(25) << dvd.director << " | "
         << setw(5) << dvd.duration << " хв | "
         << fixed << setprecision(2) << dvd.price << " грн\n";
}

void createFile(const string& filename) {
    ofstream f(filename);
    if (!f) {
        cerr << "Помилка\n";
        return;
    }
    
    int n;
    cout << "Введіть кількість DVD-дисків: ";
    cin >> n;
    cin.ignore();
    
    DVD dvd;
    for (int i = 0; i < n; i++) {
        cout << "\nDVD №" << i + 1 << endl;
        dvd = inputDVD();
        f << dvd.name << "\n" << dvd.director << "\n" 
          << dvd.duration << "\n" << fixed << setprecision(2) << dvd.price << "\n";
    }
    
    f.close();
    cout << "\nФайл створено\n";
}

void printFile(const string& filename) {
    ifstream f(filename);
    if (!f) {
        cerr << "Помилка\n";
        return;
    }
    
    DVD dvd;
    int count = 0;
    
    cout << "\n";
    while (getline(f, dvd.name)) {
        getline(f, dvd.director);
        f >> dvd.duration;
        f >> dvd.price;
        f.ignore();
        
        count++;
        cout << "DVD №" << count << endl;
        cout << "Назва фільму: " << dvd.name << endl;
        cout << "Режисер: " << dvd.director << endl;
        cout << "Тривалість: " << dvd.duration << " хв\n";
        cout << "Ціна: " << fixed << setprecision(2) << dvd.price << " грн\n\n";
    }
    
    if (count == 0) {
        cout << "Файл порожній\n";
    } else {
        cout << "Всього записів у файлі: " << count << endl;
    }
    
    f.close();
}

void deleteByPrice(const string& filename, float maxPrice) {
    ifstream f(filename);
    ofstream temp("temp.txt");
    
    if (!f || !temp) {
        cerr << "Помилка\n";
        return;
    }
    
    DVD dvd;
    int deletedCount = 0;
    int keptCount = 0;
    
    cout << "\nВидалення дисків з ціною вище " << fixed << setprecision(2) 
         << maxPrice << " грн\n";
    cout << "Видаляються:\n";
    
    while (getline(f, dvd.name)) {
        getline(f, dvd.director);
        f >> dvd.duration;
        f >> dvd.price;
        f.ignore();
        
        if (dvd.price > maxPrice) {
            cout << "  - " << dvd.name << " (" << fixed << setprecision(2) 
                 << dvd.price << " грн)\n";
            deletedCount++;
        } else {
            temp << dvd.name << "\n" << dvd.director << "\n" 
                 << dvd.duration << "\n" << fixed << setprecision(2) 
                 << dvd.price << "\n";
            keptCount++;
        }
    }
    
    f.close();
    temp.close();
    
    if (deletedCount == 0) {
        cout << "Немає дисків з ціною вище " << fixed << setprecision(2) 
             << maxPrice << " грн\n";
        remove("temp.txt");
    } else {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "\nВидалено записів: " << deletedCount 
             << "\nЗалишилось записів: " << keptCount << endl;
    }
}

void insertAtIndex(const string& filename, int k) {
    if (k < 1) {
        cout << "Номер K повинен бути >= 1\n";
        return;
    }
    
    ifstream f(filename);
    ofstream temp("temp.txt");
    
    if (!f || !temp) {
        cerr << "Помилка\n";
        return;
    }
    
    DVD dvd;
    int currentIndex = 1;
    
    while (currentIndex < k && getline(f, dvd.name)) {
        getline(f, dvd.director);
        f >> dvd.duration;
        f >> dvd.price;
        f.ignore();
        
        temp << dvd.name << "\n" << dvd.director << "\n" 
             << dvd.duration << "\n" << fixed << setprecision(2) 
             << dvd.price << "\n";
        currentIndex++;
    }
    
    cout << "\nВведіть новий DVD-диск для вставки на позицію " << k << "\n";
    cin.ignore();
    DVD newDVD = inputDVD();
    temp << newDVD.name << "\n" << newDVD.director << "\n" 
         << newDVD.duration << "\n" << fixed << setprecision(2) 
         << newDVD.price << "\n";
    
    while (getline(f, dvd.name)) {
        getline(f, dvd.director);
        f >> dvd.duration;
        f >> dvd.price;
        f.ignore();
        
        temp << dvd.name << "\n" << dvd.director << "\n" 
             << dvd.duration << "\n" << fixed << setprecision(2) 
             << dvd.price << "\n";
    }
    
    f.close();
    temp.close();
    
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
    
    cout << "\nЗапис вставлено на позицію " << k << endl;
}

void searchByName(const string& filename) {      
    ifstream f(filename);
    if (!f) {
        cerr << "Помилка відкриття файлу\n";
        return;
    }
    
    string searchName;
    cout << "Введіть назву фільму для пошуку: ";
    cin.ignore();
    getline(cin, searchName);
    
    DVD dvd;
    int foundCount = 0;
    
    cout << "\nРезультати пошуку\n";
    cout << "Шукаємо фільм: \"" << searchName << "\"\n\n";
    
    while (getline(f, dvd.name)) {
        getline(f, dvd.director);
        f >> dvd.duration;
        f >> dvd.price;
        f.ignore();
        
        if (dvd.name.find(searchName) != string::npos) {
            foundCount++;
            cout << "Знайдено DVD №" << foundCount << ":\n";
            cout << "  Назва: " << dvd.name << "\n";
            cout << "  Режисер: " << dvd.director << "\n";
            cout << "  Тривалість: " << dvd.duration << " хв\n";
            cout << "  Ціна: " << fixed << setprecision(2) << dvd.price << " грн\n\n";
        }
    }
    
    f.close();
    
    cout << "Результат запиту\n";
    if (foundCount == 0) {
        cout << "Фільм \"" << searchName << "\" не знайдено.\n";
    } else {
        cout << "Всього знайдено фільмів: " << foundCount << endl;
    }
}

int main() {
    const string filename = "dvdcpp.txt";
    int choice;
    float maxPrice;
    int k;
    
    cout << "Робота з файлом DVD-дисків\n";
    
    do {
        cout << "\nМеню\n";
        cout << "1. Створити файл та записати дані\n";
        cout << "2. Вивести вміст файлу на екран\n";
        cout << "3. Видалити всі диски з ціною вище заданої\n";
        cout << "4. Додати елемент з номером K\n";
        cout << "5. Пошук фільму за назвою\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                cout << "\nВміст файлу\n";
                printFile(filename);
                break;
            case 3:
                cout << "Введіть ціну: ";
                cin >> maxPrice;
                deleteByPrice(filename, maxPrice);
                break;
            case 4:
                cout << "Введіть номер K: ";
                cin >> k;
                insertAtIndex(filename, k);
                break;
            case 5:
                searchByName(filename);
                break;
            case 0:
                break;
            default:
                cout << "Некоректний вибір\n";
        }
    } while (choice != 0);
    
    return 0;
}

// Структура кода вийшла така ж сама, як і на мові С. Є лише незначні зміни:
// Замість FILE*, fopen/fclose	- ifstream/ofstream
// printf/scanf - cout/cin
// char[] + strcpy	- string + присвоєння
// "%[^\n]" для рядків	- getline()
// Тому, щоб повторно коментарями не поясняти одні й ті ж самі функції, пропоную Вам спочатку ознайомитися з кодом на мові С. 
// Там є всі роз'яснення