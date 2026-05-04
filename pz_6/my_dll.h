#ifndef MY_DLL_H   
#define MY_DLL_H    

#include <cstdint>        

#ifdef __cplusplus       
extern "C" {              
#endif                   

typedef struct {    //створюємо структуру
    int64_t result;     //результат арифметичної операції
    bool overflow;   //ознака переповнення
} ArithmeticResult;     //ім'я типу структури

ArithmeticResult add64(int64_t a, int64_t b);   //додавання
ArithmeticResult sub64(int64_t a, int64_t b);   //віднімання
ArithmeticResult mul64(int64_t a, int64_t b);   //множення
ArithmeticResult div64(int64_t a, int64_t b, bool *div_by_zero); //ділення з перевіркою ділення на нуль

#ifdef __cplusplus        
}                         
#endif              

#endif  