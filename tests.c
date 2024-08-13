#include "tests.h"
#include <string.h>

#define TEST_SUCCESS 0
#define TEST_FAIL 1

#define K_THREE 3
#define K_TWO 2
#define K_MINUS_ONE -1
#define K_MINUS_THREE -3
#define K_29 29

int test_encode_non_cyclic_lower_case_positive_k() {
  char input[] = "abc";
  char expected[] = "def";
  encode(input, K_THREE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_encode_cyclic_lower_case_special_char_positive_k() {
  char input[] = "az,b";
  char expected[] = "cb,d";
  encode(input, K_TWO);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_encode_non_cyclic_lower_case_special_char_negative_k() {
  char input[] = "egg?";
  char expected[] = "dff?";
  encode(input, K_MINUS_ONE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_encode_cyclic_lower_case_negative_k() {
  char input[] = "bed";
  char expected[] = "yba";
  encode(input, K_MINUS_THREE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_encode_cyclic_upper_case_positive_k() {
  char input[] = "ABZ";
  char expected[] = "DEC";
  encode(input, K_29);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_decode_non_cyclic_lower_case_positive_k() {
  char input[] = "def";
  char expected[] = "abc";
  decode(input, K_THREE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_decode_cyclic_lower_case_special_char_positive_k() {
  char input[] = "cb,d";
  char expected[] = "az,b";
  decode(input, K_TWO);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_decode_non_cyclic_lower_case_special_char_negative_k() {
  char input[] = "dff?";
  char expected[] = "egg?";
  decode(input, K_MINUS_ONE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_decode_cyclic_lower_case_negative_k() {
  char input[] = "yba";
  char expected[] = "bed";
  decode(input, K_MINUS_THREE);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}

int test_decode_cyclic_upper_case_positive_k() {
  char input[] = "DEC";
  char expected[] = "ABZ";
  decode(input, K_29);
  return strcmp(input, expected) == 0 ? TEST_SUCCESS : TEST_FAIL;
}
