// Завдання 1 (C).
// 1. Використовуючи введення-виведення в стилі С створити файл та записати в нього структуровані дані.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DVD {
    char name[50];
    char director[50];
    int duration;
    float price;
};

struct DVD inputDVD() {     //введення даних структури
    struct DVD dvd;
    printf("Назва фільму: ");
    scanf(" %[^\n]", dvd.name);
    printf("Режисер: ");
    scanf(" %[^\n]", dvd.director);
    printf("Тривалість (хв): ");
    scanf("%d", &dvd.duration);
    printf("Ціна: ");
    scanf("%f", &dvd.price);
    return dvd;
}


void printDVD(struct DVD dvd) {             //вивід одного двд
    printf("%-30s | %-25s | %5d хв | %8.2f грн\n",
           dvd.name, dvd.director, dvd.duration, dvd.price);
}


void createFile(const char* filename) {     //створення файлу та запису даних
    FILE* f = fopen(filename, "w");     //відкрити файл у текстовому режимі для запису
    if (f == NULL) {
        perror("Помилка");
        return;
    }
    
    int n;          // кількість двд
    printf("Введіть кількість DVD-дисків: ");
    scanf("%d", &n);
    
    struct DVD dvd;     //тимчасова структура для зберігання одного двд
    for (int i = 0; i < n; i++) {       // цикл для введення та запису всіх дисків
        printf("\nDVD №%d\n", i + 1);
        dvd = inputDVD();
        fprintf(f, "%s\n%s\n%d\n%.2f\n", dvd.name, dvd.director, dvd.duration, dvd.price);
    }
    
    fclose(f);
    printf("\nФайл створено\n");
}

void printFile(const char* filename) {  //вивід файлу на екран
    FILE* f = fopen(filename, "r");    //відкриваємо для читання
    if (f == NULL) {
        perror("Помилка");
        return;
    }
    
    struct DVD dvd;
    int count = 0;      //лічильник прочитанних двд
    
    printf("\n");
    while (fscanf(f, " %[^\n]", dvd.name) == 1) {       //читаємо назву
        fscanf(f, " %[^\n]", dvd.director);         //режисера...
        fscanf(f, "%d", &dvd.duration);
        fscanf(f, "%f", &dvd.price);
        
        count++;        //збільшуємо лічильник 
        printf("DVD №%d\n", count);     //вивід номера двд...
        printf("Назва фільму: %s\n", dvd.name);
        printf("Режисер: %s\n", dvd.director);
        printf("Тривалість: %d хв\n", dvd.duration);
        printf("Ціна: %.2f грн\n", dvd.price);
        printf("\n");
    }
    
    if (count == 0) {
        printf("Файл порожній\n");
    } else {
        printf("Всього записів у файлі: %d\n", count);
    }
    
    fclose(f);
}

void deleteByPrice(const char* filename, float maxPrice) {      //видалення елементів з ціною вище за задану
    FILE* f = fopen(filename, "r");            // відкриваємо вихідний файл
    FILE* temp = fopen("temp.txt", "w");           //відкриваємо тимчасовий 
    
    if (f == NULL || temp == NULL) {    
        perror("Помилка");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }
    
    struct DVD dvd;
    int deletedCount = 0;       //лічильник видалених двд
    int keptCount = 0;      //лічильник двд, що залишилися 
    
    printf("\nВидалення дисків з ціною вище %.2f грн\n", maxPrice);
    printf("Видаляються:\n");
    
    while (fscanf(f, " %[^\n]", dvd.name) == 1) {   //читаємо назву...
        fscanf(f, " %[^\n]", dvd.director);
        fscanf(f, "%d", &dvd.duration);
        fscanf(f, "%f", &dvd.price);
        
        if (dvd.price > maxPrice) {     //якщо ціна вища ща задану - вивід назву, ціну, збільшуємо лічильник видалених
            printf("  - %s (%.2f грн)\n", dvd.name, dvd.price);
            deletedCount++;
        } else {                //інакше - записуємо двд у тимчасовий файл та збільшуємо лічильник залишенних двд
            fprintf(temp, "%s\n%s\n%d\n%.2f\n", dvd.name, dvd.director, dvd.duration, dvd.price);
            keptCount++;
        }
    }
    
    fclose(f);
    fclose(temp);
    
    if (deletedCount == 0) {
        printf("Немає дисків з ціною вище %.2f грн\n", maxPrice);
        remove("temp.txt");
    } else {
        remove(filename);
        rename("temp.txt", filename);
        printf("\nВидалено записів: %d\nЗалишилось записів: %d\n", deletedCount, keptCount);
    }
}

void insertAtIndex(const char* filename, int k) {       //додавання елемента з номером К
    if (k < 1) {
        printf("Номер K повинен бути >= 1\n");
        return;
    }
    
    FILE* f = fopen(filename, "r");         //відкр. вихідний файл
    FILE* temp = fopen("temp.txt", "w");        //відкр. тимчасовий файл 
    
    if (f == NULL || temp == NULL) {
        perror("Помилка");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }
    
    struct DVD dvd;
    int currentIndex = 1;       //лічильник поточної позиції 
    

    while (currentIndex < k && fscanf(f, " %[^\n]", dvd.name) == 1) {   //поки не дійшли до K і вдалося прочитати назву
        fscanf(f, " %[^\n]", dvd.director);     //читаємо рядок з режисером...
        fscanf(f, "%d", &dvd.duration);
        fscanf(f, "%f", &dvd.price);
        
        fprintf(temp, "%s\n%s\n%d\n%.2f\n", dvd.name, dvd.director, dvd.duration, dvd.price);   //записуємо у тимчас. файл
        currentIndex++;
    }
    
    printf("\nВведіть новий DVD-диск для вставки на позицію %d\n", k);
    struct DVD newDVD = inputDVD();         // функцію для введення нового диска
    fprintf(temp, "%s\n%s\n%d\n%.2f\n", newDVD.name, newDVD.director, newDVD.duration, newDVD.price); //записуємо новий диск у тимч. файл
    
    while (fscanf(f, " %[^\n]", dvd.name) == 1) {       //читаємо решту записів
        fscanf(f, " %[^\n]", dvd.director);
        fscanf(f, "%d", &dvd.duration);
        fscanf(f, "%f", &dvd.price);
        
        fprintf(temp, "%s\n%s\n%d\n%.2f\n", dvd.name, dvd.director, dvd.duration, dvd.price);       //записуємо у тимчас. файл
    }
    
    fclose(f);
    fclose(temp);
    
    remove(filename);
    rename("temp.txt", filename);
    
    printf("\nЗапис вставлено на позицію %d\n", k);
}

void searchByName(const char* filename) {     // пошук фільму за назвою
    FILE* f = fopen(filename, "r");     //відкриваємо файл для читання
    if (f == NULL) {
        perror("Помилка");
        return;
    }
    
    char searchName[50];
    printf("Введіть назву фільму для пошуку: ");
    getchar();  // очищаємо буфер після попереднього введення
    fgets(searchName, 50, stdin);   //зчитуємо рядок 
    searchName[strcspn(searchName, "\n")] = 0;  // видаляємо символ нового рядка
    
    struct DVD dvd;
    int foundCount = 0;
    
    printf("\nРезультати пошуку\n");
    printf("Шукаємо фільм: \"%s\"\n\n", searchName);
    
    while (fscanf(f, " %[^\n]", dvd.name) == 1) {   // цикл читання записів з файлу поки є що читати
        fscanf(f, " %[^\n]", dvd.director);
        fscanf(f, "%d", &dvd.duration);
        fscanf(f, "%f", &dvd.price);
        
        if (strstr(dvd.name, searchName) != NULL) {     // пошук підрядка в назві
            foundCount++;
            printf("Знайдено DVD №%d:\n", foundCount);
            printf("  Назва: %s\n", dvd.name);
            printf("  Режисер: %s\n", dvd.director);
            printf("  Тривалість: %d хв\n", dvd.duration);
            printf("  Ціна: %.2f грн\n\n", dvd.price);
        }
    }
    
    fclose(f);
    
    printf("Результат запиту\n");
    if (foundCount == 0) {
        printf("Фільм \"%s\" не знайдено.\n", searchName);
    } else {
        printf("Всього знайдено фільмів: %d\n", foundCount);
    }
}

int main() {
    const char* filename = "dvdc.txt";
    int choice;
    float maxPrice;
    int k;
    
    printf("   Робота з файлом DVD-дисків\n");
    
    do {
        printf("\nМеню\n");
        printf("1. Створити файл та записати дані\n");
        printf("2. Вивести вміст файлу на екран\n");
        printf("3. Видалити всі диски з ціною вище заданої\n");
        printf("4. Додати елемент з номером K\n");
        printf("5. Пошук фільму за назвою\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                printf("\nВміст файлу\n");
                printFile(filename);
                break;
            case 3:
                printf("Введіть ціну: ");
                scanf("%f", &maxPrice);
                deleteByPrice(filename, maxPrice);
                break;
            case 4:
                printf("Введіть номер K: ");
                scanf("%d", &k);
                insertAtIndex(filename, k);
                break;
            case 5:
                searchByName(filename);
                break;
            case 0:
                break;
            default:
                printf("Некоректний вибір\n");
        }
    } while (choice != 0);
    
    return 0;
}