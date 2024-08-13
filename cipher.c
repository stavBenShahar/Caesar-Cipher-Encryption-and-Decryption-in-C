#include "cipher.h"

#define ALPHABET_SIZE 26
#define UPPER_A 65
#define LOWER_A 97

void encode(char s[], int k) {
  if (k < 0) {
    k = ALPHABET_SIZE + (k % ALPHABET_SIZE);
  }

  for (int i = 0; s[i] != '\0'; i++) {
    if (isupper(s[i])) {
      s[i] = ((s[i] - UPPER_A + k) % ALPHABET_SIZE) + UPPER_A;
    } else if (islower(s[i])) {
      s[i] = ((s[i] - LOWER_A + k) % ALPHABET_SIZE) + LOWER_A;
    }
  }
}

void decode(char s[], int k) {
  encode(s, -k);
}
