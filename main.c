#include "cipher.h"
#include "tests.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_LEN 1024

#define ENCODE "encode"
#define DECODE "decode"
#define TEST "test"

#define ARG_ERROR_MSG "The program receives 1 or 4 arguments only.\n"
#define TEST_ERROR_MSG "Usage: cipher test\n"
#define COMMAND_ERROR_MSG "The given command is invalid.\n"
#define SHIFT_ERROR_MSG "The given shift value is invalid.\n"
#define FILE_ERROR_MSG "The given file is invalid.\n"

enum { CMD = 1, KEY, IN_FILE, OUT_FILE };
enum { SUCCESS = 0, FAILURE = 1 };

int validate_args(int argc, char *argv[]);
int start_cipher_operation(char *argv[]);
int run_tests();

int main(int argc, char *argv[]) {
  if (validate_args(argc, argv) == FAILURE) {
    return EXIT_FAILURE;
  }
  if (start_cipher_operation(argv) == FAILURE) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int validate_args(int argc, char *argv[]) {
  if (argc != 2 && argc != 5) {
    fprintf(stderr, "%s", ARG_ERROR_MSG);
    return FAILURE;
  }

  if (argc == 2 && strcmp(argv[CMD], TEST) != 0) {
    fprintf(stderr, "%s", TEST_ERROR_MSG);
    return FAILURE;
  }

  if (argc == 5) {
    if (strcmp(argv[CMD], ENCODE) != 0 && strcmp(argv[CMD], DECODE) != 0) {
      fprintf(stderr, "%s", COMMAND_ERROR_MSG);
      return FAILURE;
    }

    char *end_ptr;
    strtol(argv[KEY], &end_ptr, 10);
    if (*end_ptr) {
      fprintf(stderr, "%s", SHIFT_ERROR_MSG);
      return FAILURE;
    }

    FILE *input_file = fopen(argv[IN_FILE], "r");
    if (!input_file) {
      fprintf(stderr, "%s", FILE_ERROR_MSG);
      return FAILURE;
    }
    fclose(input_file);

    FILE *output_file = fopen(argv[OUT_FILE], "w");
    if (!output_file) {
      fprintf(stderr, "%s", FILE_ERROR_MSG);
      return FAILURE;
    }
    fclose(output_file);
  }

  return SUCCESS;
}

int start_cipher_operation(char *argv[]) {
  if (strcmp(argv[CMD], TEST) == 0) {
    return run_tests();
  }

  FILE *input_file = fopen(argv[IN_FILE], "r");
  FILE *output_file = fopen(argv[OUT_FILE], "w");
  if (!input_file || !output_file) {
    return FAILURE;
  }

  char buffer[BUFFER_LEN];
  int shift_value = (int)strtol(argv[KEY], NULL, 10);

  while (fgets(buffer, BUFFER_LEN, input_file)) {
    if (strcmp(argv[CMD], ENCODE) == 0) {
      encode(buffer, shift_value);
    } else {
      decode(buffer, shift_value);
    }
    fprintf(output_file, "%s", buffer);
  }

  fclose(input_file);
  fclose(output_file);

  return SUCCESS;
}

int run_tests() {
  int test_results[] = {
      test_encode_non_cyclic_lower_case_positive_k(),
      test_encode_cyclic_lower_case_special_char_positive_k(),
      test_encode_non_cyclic_lower_case_special_char_negative_k(),
      test_encode_cyclic_lower_case_negative_k(),
      test_encode_cyclic_upper_case_positive_k(),
      test_decode_non_cyclic_lower_case_positive_k(),
      test_decode_cyclic_lower_case_special_char_positive_k(),
      test_decode_non_cyclic_lower_case_special_char_negative_k(),
      test_decode_cyclic_lower_case_negative_k(),
      test_decode_cyclic_upper_case_positive_k()
  };

  for (int i = 0; i < sizeof(test_results) / sizeof(test_results[0]); i++) {
    if (test_results[i] != 0) {
      return FAILURE;
    }
  }

  return SUCCESS;
}
