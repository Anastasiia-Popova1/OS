// Рядки тексту упорядкувати в порядку зростання, якщо відомо, 
// що символи цих рядків задані в ASCII або в Unicode

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

int CompareStrings(const void* a, const void* b) {    //регістрозалежне порівняння рядків
    const TCHAR** str1 = (const TCHAR**)a;      //перетворюємо void* на подвійний покажчик
    const TCHAR** str2 = (const TCHAR**)b;
    return _tcscmp(*str1, *str2);   //розіменовуємо покажчики та порівнюємо рядки з урахуванням регістру
}

int CompareStringsIgnoreCase(const void* a, const void* b) {     ////регістронезалежне порівняння рядків
    const TCHAR** str1 = (const TCHAR**)a;
    const TCHAR** str2 = (const TCHAR**)b;
    return _tcsicmp(*str1, *str2);             //розіменовуємо покажчики та порівнюємо рядки без урахування регістру
}

void PrintStrings(const TCHAR* title, const TCHAR** strings, int count) {   //вивід рядків
    _tprintf(_T("%s:\n"), title);
    for (int i = 0; i < count; i++) {       //цикл по всіх рядках масиву
        _tprintf(_T("\%s\n"), strings[i]);    //виводимо  рядок 
    }
    _tprintf(_T("\n"));
}

void SortStrings(TCHAR** strings, int count, bool ignoreCase = false) { //регістрозалежне сортування рядків 
    if (ignoreCase) {       ////якщо ignoreCase == true (потрібно ігнорувати регістр)
        qsort(strings, count, sizeof(TCHAR*), CompareStringsIgnoreCase);    //викликаємо qsort з функцією порівняння без урахування регістру
    } else {
        qsort(strings, count, sizeof(TCHAR*), CompareStrings); //викликаємо qsort з функцією порівняння з урахуванням регістру
    }
}

int _tmain(int argc, TCHAR* argv[])
{
    const TCHAR* strings1[] = {
        TEXT("bcsdf"),
        TEXT("Adfgkdf"),
        TEXT("gsdfpsdf"),
        TEXT("Cdfgkdfg"),
        TEXT("asddgk"),
        TEXT("Bddfgkdf")
    };
    int count1 = sizeof(strings1) / sizeof(strings1[0]);
    
    PrintStrings(_T("Початковий масив"), strings1, count1);
    
    TCHAR* copy1[20];       //копія для сортування
    for (int i = 0; i < count1; i++) {
        copy1[i] = (TCHAR*)strings1[i]; 
    }

    SortStrings(copy1, count1, false);
    PrintStrings(_T("Після сортування (регістрозалежне сортування)"), (const TCHAR**)copy1, count1);

    TCHAR* copy2[20];
    for (int i = 0; i < count1; i++) {
        copy2[i] = (TCHAR*)strings1[i];
    }
    
    SortStrings(copy2, count1, true);
    PrintStrings(_T("Після сортування (регістронезалежне сортування)"), (const TCHAR**)copy2, count1);
    
    return 0;
}