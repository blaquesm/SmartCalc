#include <check.h>

#include "./SmartCalc/s21_smart_calc.h"

START_TEST(test_1) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "10+10-10*10/+2", 0);
  ck_assert_ldouble_eq(num, -30);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_2) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sin(10)+cos(sqrt(45))/ln(41)", 0);
  ck_assert_ldouble_eq_tol(num, cos(sqrt(45)) / log(41) + sin(10), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_3) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "12345679*45", 0);
  ck_assert_ldouble_eq(num, 555555555);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_4) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "12345679*9", 0);
  ck_assert_ldouble_eq(num, 111111111);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_5) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sin(90)", 0);
  ck_assert_ldouble_eq_tol(num, 0.8939966636, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_6) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "asin(1)", 0);
  ck_assert_ldouble_eq_tol(num, asin(1), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_6_1) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "asin(0.1)/3.14+atan(0)", 0);
  ck_assert_ldouble_eq_tol(num, asin(0.1) / 3.14 + atan(0), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_7) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sqrt(16)", 0);
  ck_assert_ldouble_eq_tol(num, 4.0, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_8) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "log(100)", 0);
  ck_assert_ldouble_eq_tol(num, 2.0, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_9) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "ln(2.7)", 0);
  ck_assert_double_eq_tol(num, log(1), 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_10) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "17mod5", 0);
  ck_assert_ldouble_eq_tol(num, 2.0, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_11) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "30mod7", 0);
  ck_assert_ldouble_eq_tol(num, 2.0, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_12) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sqrt(144)+ln(1)+log(10)", 0);
  ck_assert_ldouble_eq_tol(num, 16.0, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_13) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sqrt(2)+sqrt(2)+sqrt(2)", 0);
  ck_assert_ldouble_eq_tol(num, 3.46410161514, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_14) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sqrt(3)+sqrt(3)", 0);
  ck_assert_ldouble_eq_tol(num, 3.46410161514, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_15) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sqrt(25)+sqrt(16)", 0);
  ck_assert_ldouble_eq(num, 9);
  ck_assert_int_eq(0, ret);
}
END_TEST

START_TEST(test_16) {
  long double num = 0;
  int ret = 0;
  ret = s21_calc(&num, "sin(45)+cos(45)", 0);
  ck_assert_ldouble_eq_tol(num, 1.41421356237, 7);
  ck_assert_int_eq(0, ret);
}
END_TEST

int main(void) {
  Suite *suite =
      suite_create("S21_TEST"); // создание наборов тестов и с именем S21_TEST
  SRunner *srunner = srunner_create(suite);

  TCase *create1 = tcase_create("test_1\t");
  suite_add_tcase(suite, create1);
  tcase_add_test(create1, test_1);

  TCase *create2 = tcase_create("test_2\t");
  suite_add_tcase(suite, create2);
  tcase_add_test(create2, test_2);

  TCase *create3 = tcase_create("test_3\t");
  suite_add_tcase(suite, create3);
  tcase_add_test(create3, test_3);

  TCase *create4 = tcase_create("test_4\t");
  suite_add_tcase(suite, create4);
  tcase_add_test(create4, test_4);

  TCase *create5 = tcase_create("test_5\t");
  suite_add_tcase(suite, create5);
  tcase_add_test(create5, test_5);

  TCase *create6 = tcase_create("test_6\t");
  suite_add_tcase(suite, create6);
  tcase_add_test(create6, test_6);

  TCase *create6_1 = tcase_create("test_6_1\t");
  suite_add_tcase(suite, create6_1);
  tcase_add_test(create6_1, test_6_1);

  TCase *create7 = tcase_create("test_7\t");
  suite_add_tcase(suite, create7);
  tcase_add_test(create7, test_7);

  TCase *create8 = tcase_create("test_8\t");
  suite_add_tcase(suite, create8);
  tcase_add_test(create8, test_8);

  TCase *create9 = tcase_create("test_9\t");
  suite_add_tcase(suite, create9);
  tcase_add_test(create9, test_9);

  TCase *create10 = tcase_create("test_10\t");
  suite_add_tcase(suite, create10);
  tcase_add_test(create10, test_10);

  TCase *create11 = tcase_create("test_11\t");
  suite_add_tcase(suite, create11);
  tcase_add_test(create11, test_11);

  TCase *create12 = tcase_create("test_12\t");
  suite_add_tcase(suite, create12);
  tcase_add_test(create12, test_12);

  TCase *create13 = tcase_create("test_13\t");
  suite_add_tcase(suite, create13);
  tcase_add_test(create13, test_13);

  TCase *create14 = tcase_create("test_14\t");
  suite_add_tcase(suite, create14);
  tcase_add_test(create14, test_14);

  TCase *create15 = tcase_create("test_15\t");
  suite_add_tcase(suite, create15);
  tcase_add_test(create15, test_15);

  TCase *create16 = tcase_create("test_16\t");
  suite_add_tcase(suite, create16);
  tcase_add_test(create16, test_16);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}