#ifndef S21_SMART_CALC_
#define S21_SMART_CALC_
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct calc {
  int symbol;
  int prior;
  struct calc *next;
} stack;

typedef struct number {
  long double num;
  struct number *next;
} result;

int is_digits(char s);
int prior(char c);
int is_oper(char c);
int is_unar(char *input, int *i);
int is_funcion(char *input, int *i);
int check_fun(char c);
int count_brace(char *str, char s);
int calc(char *str, long double *res);
int parser(char *input, char **output, double x);
int s21_calc(long double *result, const char *input, double x);
void push_num(result **struct_r, long double num);
void push(stack **struct_c, int s, int p);
void delet(stack **struct_c);
void cut_digits(char *input, int *i, char *output);
long double delet_num(result **struct_r);
long double calc_function(long double number, char c);
long double calc_oper(long double right, long double left, char c);

#endif // S21_SMART_CALC_