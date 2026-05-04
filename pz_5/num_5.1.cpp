// Скласти функцію для порівняння двох каталогів, якщо відомо, що каталоги регістро 
// незалежні і можуть закінчуватися символом \. Цей символ можу бути відсутнім.

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

typedef enum {
    DIRS_EQUAL = 0,           //каталоги однакові
    DIRS_NOT_EQUAL = 1,       //каталоги різні
    DIRS_ERROR = -1           //помилка
} CompareResult;


CompareResult CompareDirectories(const TCHAR* tcDir1, const TCHAR* tcDir2)
{
    if (tcDir1 == NULL || tcDir2 == NULL) {     //перевірка на нуль
        return DIRS_ERROR;
    }
    
    size_t len1 = _tcslen(tcDir1);  //динамічно виділяємо пам'ять
    size_t len2 = _tcslen(tcDir2);

    TCHAR* tcNormalized1 = new TCHAR[len1 + 2]; //пам'ять під нормалізовані шляхи, +2 на можливий \ та '\0'
    TCHAR* tcNormalized2 = new TCHAR[len2 + 2];
    
    _tcscpy(tcNormalized1, tcDir1);     //копіюємо перший шлях
    if (tcNormalized1[_tcslen(tcNormalized1) - 1] != TEXT('\\')) {  //якщо шлях не закінчується на зворотній слеш
        _tcscat(tcNormalized1, TEXT("\\"));     //додаємо його 
    }
    
    _tcscpy(tcNormalized2, tcDir2);         //те ж саме з другим шляхом 
    if (tcNormalized2[_tcslen(tcNormalized2) - 1] != TEXT('\\')) {      
        _tcscat(tcNormalized2, TEXT("\\"));             
    }

    int compareResult = _tcsicmp(tcNormalized1, tcNormalized2); //порівнюємо без врахунку регістра
    
    delete[] tcNormalized1; //звільняємо пам'ять
    delete[] tcNormalized2;
    
    return (compareResult == 0) ? DIRS_EQUAL : DIRS_NOT_EQUAL;
}

int _tmain(int argc, TCHAR* argv[])
{           
    #define TEST(a,b) _tprintf(_T("\"%s\" vs \"%s\" -> %s\n"), \
        (a)?(a):_T("NULL"), (b)?(b):_T("NULL"), \
        (CompareDirectories(a,b)==DIRS_EQUAL)?_T("однакові"): \
        (CompareDirectories(a,b)==DIRS_NOT_EQUAL)?_T("різні"):_T("помилка"))
    
    TEST(TEXT("C:\\Windows"), TEXT("C:\\Windows\\"));
    TEST(TEXT("C:\\Program Files"), TEXT("C:\\PROGRAM FILES\\"));
    TEST(TEXT("D:\\Temp"), TEXT("D:\\TempOld"));
    TEST(NULL, TEXT("C:\\Windows"));
    
    return 0;
}

// Результати:

// "C:\Windows" vs "C:\Windows\" -> однакові
// "C:\Program Files" vs "C:\PROGRAM FILES\" -> однакові
// "D:\Temp" vs "D:\TempOld" -> різні
// "NULL" vs "C:\Windows" -> помилка