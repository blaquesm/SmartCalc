#include "s21_smart_calc.h"
#include <stdio.h>

long double delet_num(result **struct_r) {
  result *del = NULL;
  long double res = 0;
  if (*struct_r != NULL) {
    del = *struct_r;
    res = del->num;
    *struct_r = (*struct_r)->next;
    free(del);
  }
  return res;
}

void push_num(result **struct_r, long double num) {
  result *temp = calloc(1, sizeof(result));
  if (temp != NULL) {
    temp->num = num;
    temp->next = *struct_r;
    *struct_r = temp;
  }
}
int is_digits(char s) { return (s >= '0' && s <= '9'); }

void push(stack **struct_c, int s, int p) {
  stack *temp = calloc(1, sizeof(stack));
  if (temp != NULL) {
    temp->symbol = s;
    temp->prior = p;
    temp->next = *struct_c;
    *struct_c = temp;
  }
}

int prior(char c) {
  int flag = -1;
  if (c == '(')
    flag = 0;
  else if (c == '-' || c == '+')
    flag = 1;
  else if (c == '*' || c == '/' || c == 'm')
    flag = 2;
  else if (c == '^')
    flag = 3;
  else
    flag = 4;
  return flag;
}

int is_oper(char c) {
  int flag = 0;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm')
    flag = c;
  return flag;
}

int is_unar(char *input, int *i) {
  int flag = 0;
  if ((*i == 0 && input[*i] == '-') ||
      (*i > 0 && input[*i - 1] != ')' && !is_digits(input[*i - 1]))) {
    if (input[*i] == '-')
      flag = '~';
    else if (input[*i] == '+')
      flag = '$';
  }
  if (flag != 0)
    *i += 1;
  return flag;
}

int is_funcion(char *input, int *i) {
  int flag = 0;
  if (input[*i] >= 'a' && input[*i] <= 'z') {
    if (strncmp("cos", input + *i, 3) == 0)
      flag = 'c';
    else if (strncmp("sin", input + *i, 3) == 0)
      flag = 's';
    else if (strncmp("tan", input + *i, 3) == 0)
      flag = 't';
    else if (strncmp("acos", input + *i, 4) == 0)
      flag = 'C';
    else if (strncmp("asin", input + *i, 4) == 0)
      flag = 'S';
    else if (strncmp("atan", input + *i, 4) == 0)
      flag = 'T';
    else if (strncmp("log", input + *i, 3) == 0)
      flag = 'l';
    else if (strncmp("ln", input + *i, 2) == 0)
      flag = 'L';
    else if (strncmp("sqrt", input + *i, 4) == 0)
      flag = 'Q';
  }
  if (flag == 'c' || flag == 's' || flag == 't' || flag == 'l')
    *i += 3;
  else if (flag == 'C' || flag == 'S' || flag == 'T' || flag == 'Q')
    *i += 4;
  else if (flag == 'L')
    *i += 2;
  return flag;
}
int check_fun(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void delet(stack **struct_c) {
  stack *del = NULL;
  if (*struct_c != NULL) {
    del = *struct_c;
    *struct_c = (*struct_c)->next;
    free(del);
  }
}

int count_brace(char *str, char s) {
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == s)
      count++;
  }
  return count;
}

void cut_digits(char *input, int *i, char *output) {
  while ((input[*i] != '\0' && is_digits(input[*i])) ||
         (input[*i] == '.' && is_digits(input[*i + 1]) &&
          is_digits(input[*i - 1]))) {
    output[strlen(output)] = input[*i];
    *i += 1;
  }
  if (input[*i] == 'E' || input[*i] == 'e') {
    output[strlen(output)] = input[*i];
    *i += 1;
    if (input[*i] == '+' || input[*i] == '-') {
      output[strlen(output)] = input[*i];
      *i += 1;
    }
  }
  while (input[*i] != '\0' && is_digits(input[*i])) {
    output[strlen(output)] = input[*i];
    *i += 1;
  }
  output[strlen(output)] = ' ';
}

int parser(char *input, char **output, double x) {
  int flag = 0;
  int i = 0;
  int check_func = 0;
  int check_unar = 0;
  int check_oper = 0;
  stack *box = NULL;
  while (input[i] != '\0' && flag == 0) {
    if (is_digits(input[i]))
      cut_digits(input, &i, *output + strlen(*output));
    else if (input[i] == 'x') {
      sprintf(*output + strlen(*output), "%g ", x);
      i++;
    } else if ((check_func = is_funcion(input, &i)) != 0)
      push(&box, check_func, prior(check_func));
    else if (input[i] == '(') {
      push(&box, '(', 0);
      i++;
    } else if ((check_unar = is_unar(input, &i)) != 0)
      push(&box, check_unar, prior(check_unar));
    else if ((check_oper = is_oper(input[i])) != 0) {
      while (box != NULL && box->prior >= prior(check_oper)) {
        sprintf(*output + strlen(*output), "%c ", box->symbol);
        delet(&box);
      }
      push(&box, check_oper, prior(check_oper));
      i++;
    } else if (input[i] == ')') {
      while (box != NULL && box->symbol != '(') {
        sprintf(*output + strlen(*output), "%c ", box->symbol);
        delet(&box);
      }
      if (box != NULL) {
        delet(&box);
        if (check_fun(box->symbol)) {
          sprintf(*output + strlen(*output), "%c ", box->symbol);
          delet(&box);
        }
      } else
        flag = -1;
      i++;
    } else
      i++;
  }
  if (box != NULL && (box->symbol == '(' || box->symbol == ')'))
    flag = -1;
  else {
    while (box != NULL) {
      sprintf(*output + strlen(*output), "%c ", box->symbol);
      delet(&box);
    }
  }
  return flag;
}

long double calc_function(long double number, char c) {
  long double result = 0;
  // printf("check = %Lf\n", number);
  switch (c) {
  case 'c':
    result = cosl(number);
    break;
  case 's':
    result = sinl(number);
    break;
  case 't':
    result = tanl(number);
    break;
  case 'C':
    result = acosl(number);
    break;
  case 'S':
    result = asinl(number);
    break;
  case 'T':
    result = atanl(number);
    break;
  case 'l':
    result = log10l(number);
    break;
  case 'L':
    result = logl(number);
    break;
  case 'Q':
    result = sqrtl(number);
    break;
  default:
    break;
  }
  return result;
}

long double calc_oper(long double right, long double left, char c) {
  long double result = 0;
  switch (c) {
  case '+':
    result = left + right;
    break;
  case '-':
    result = left - right;
    break;
  case '*':
    result = left * right;
    break;
  case '/':
    result = left / right;
    break;
  case 'm':
    result = fmodl(left, right);
    break;
  case '^':
    result = powl(left, right);
    break;
  default:
    break;
  }
  return result;
}

int calc(char *str, long double *res) {
  int flag = 0;
  result *number_res = NULL;
  long double left = 0;
  long double right = 0;
  char *temp = NULL;
  int i = 0;
  while (str[i] != '\0' && flag == 0) {
    if (isspace(str[i]))
      i++;
    if (is_digits(str[i])) {
      left = 0;
      temp = calloc(20, sizeof(char));
      cut_digits(str, &i, temp);
      sscanf(temp, "%Lg", &left);
      push_num(&number_res, left);
      free(temp);
    } else if (str[i] == '~') {
      number_res->num *= -1;
      i++;
    } else if (is_oper(str[i])) {
      if (number_res != NULL && number_res->next != NULL) {
        right = delet_num(&number_res);
        left = delet_num(&number_res);
        push_num(&number_res, calc_oper(right, left, str[i]));
      } else
        flag = -1;
      i++;
    } else if (check_fun(str[i])) {
      if (number_res == NULL)
        flag = -1;
      else {
        left = calc_function(number_res->num, str[i]);
        delet_num(&number_res);
        push_num(&number_res, left);
        left = 0;
      }
      // printf("check_1 = \t%Lf\n",number_res->num);
      i++;
    } else
      i++;
  }
  if (number_res != NULL && number_res->next == NULL)
    *res = delet_num(&number_res);
  else
    flag = -1;
  if (number_res != NULL) {
    flag = -1;
  }
  return flag;
}

int s21_calc(long double *result, const char *input, double x) {
  int flag = 0;
  char *output = calloc(250, sizeof(char));
  char *input_temp = calloc(255, sizeof(char));
  if (output && input_temp) {
    for (int i = 0; input[i] != '\0' && i < 255; i++) {
      input_temp[i] = input[i];
    }
    if (parser(input_temp, &output, x) == 0) {
      flag = calc(output, result);
    }
  }
  free(output);
  free(input_temp);
  return flag;
}
