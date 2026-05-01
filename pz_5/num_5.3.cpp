// Рядки тексту упорядкувати в порядку зростання, якщо тип кодування невідомий. 

#include <tchar.h>
#include <stdio.h>
#include <windows.h>

int CompareWStrings(const void* a, const void* b)
{
    return wcscmp(*(const wchar_t**)a, *(const wchar_t**)b);        // розіменовуємо вказівники та порівнюємо рядки
}

const wchar_t* ToUnicode(const void* str, int size, wchar_t* output, int outputSize)
{
    int flag = -1;      //прапорець для визначення кодування
    if (IsTextUnicode(str, size, &flag)) {      //чи текст вже у юнікод
        wcscpy_s(output, outputSize, (const wchar_t*)str);  //копіюємо юнікод рядок у вихідний буфер
    } else {
        MultiByteToWideChar(CP_ACP, 0, (const char*)str, -1, output, outputSize);   //інакше - перетворюємо ANSI рядок у юнікод
    }
    return output;
}

int _tmain()
{
    const char* strs[] = { "osdfsf", "awer", "csdfe", "dwer", "fwerdf" }; //ANSI
    const wchar_t* wstrs[] = { L"bwerew", L"gfsdf", L"ewerey" };    //Unicode
    
    const void* allStrings[8];  //масив для зберігання вказівників на всі рядки
    int sizes[8];   // масив для зберігання розмірів кожного рядка в байтах
    wchar_t converted[8][100];  //буфер для перетворених ANSI рядків у Unicode
    const wchar_t* uniPtrs[8];  // масив вказівників на Unicode рядки 
    
    // ANSI рядки
    for (int i = 0; i < 5; i++) {
        allStrings[i] = strs[i];    // зберігаємо вказівник на ANSI рядок
        sizes[i] = (int)strlen(strs[i]) + 1;    //обчислюємо розмір ANSI рядка в байтах
    }
    
    // Unicode рядкт
    for (int i = 0; i < 3; i++) {
        allStrings[5 + i] = wstrs[i];
        sizes[5 + i] = (int)(wcslen(wstrs[i]) + 1) * sizeof(wchar_t);
    }
    
    _tprintf(_T("Оригінальні рядки:\n"));
    for (int i = 0; i < 8; i++) {
        uniPtrs[i] = ToUnicode(allStrings[i], sizes[i], converted[i], 100); //перетворюємо рядок у Unicode
        wprintf(L"%d: %s\n", i + 1, uniPtrs[i]);
    }
    
    qsort(uniPtrs, 8, sizeof(const wchar_t*), CompareWStrings);     //сортуємо масив вказівників на Unicode рядки
    
    _tprintf(_T("\nВідсортовані рядки:\n"));
    for (int i = 0; i < 8; i++) {
        wprintf(L"%d: %s\n", i + 1, uniPtrs[i]);
    }
    
    return 0;
}
