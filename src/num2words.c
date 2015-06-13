#include "num2words.h"
#include "string.h"

static const char* const STUNDEN[] = {
  "zwölf",
  "eins",
  "zwei",
  "drei",
  "vier",
  "fünf",
  "sechs",
  "sieben",
  "acht",
  "neun",
  "zehn",
  "elf"
};

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

void fuzzy_time_to_words(int hours, int minutes, char* words, size_t length) {

  size_t remaining = length;
  memset(words, 0, length);

  if (minutes == 0) {
    if (hours == 0) {
      remaining -= append_string(words, remaining, "mitter- nacht");
    } else {
      if (hours % 12 == 1) {
        remaining -= append_string(words, remaining, "ein");
      } else {
        remaining -= append_string(words, remaining, STUNDEN[hours % 12]);
      }
      remaining -= append_string(words, remaining, "   uhr");
      if (hours  < 5 || hours > 21) {
        remaining -= append_string(words, remaining, " nachts");
      } else if ( hours < 12) {
        remaining -= append_string(words, remaining, " morgens");
      } else if ( hours < 13) {
        remaining -= append_string(words, remaining, " mittags");
      } else if ( hours < 18) {
        remaining -= append_string(words, remaining, " nach- mittags");
      } else {
        remaining -= append_string(words, remaining, " abends");
      }
    }
    return;
  };

  if (minutes <= 3) {
    remaining -= append_string(words, remaining, "kurz nach");
  } else if (minutes <= 8) {
    remaining -= append_string(words, remaining, "fünf nach");
  } else if (minutes <= 12) {
    remaining -= append_string(words, remaining, "zehn nach");
  } else if (minutes <= 17) {
    remaining -= append_string(words, remaining, "viertel nach");
  } else if (minutes <= 22) {
    remaining -= append_string(words, remaining, "zwanzig nach");
  } else if (minutes <= 28) {
    remaining -= append_string(words, remaining, "fünf vor halb");
  } else if (minutes <= 29) {
    remaining -= append_string(words, remaining, "kurz vor halb");
  } else if (minutes <= 30) {
    remaining -= append_string(words, remaining, "halb");
  } else if (minutes <= 32) {
    remaining -= append_string(words, remaining, "kurz nach halb");
  } else if (minutes <= 37) {
    remaining -= append_string(words, remaining, "fünf nach halb");
  } else if (minutes <= 43) {
    remaining -= append_string(words, remaining, "zwanzig vor");
  } else if (minutes <= 48) {
    remaining -= append_string(words, remaining, "viertel vor");
  } else if (minutes <= 53) {
    remaining -= append_string(words, remaining, "zehn vor");
  } else if (minutes <= 57) {
    remaining -= append_string(words, remaining, "fünf vor");
  } else if (minutes <= 59) {
    remaining -= append_string(words, remaining, "kurz vor");
}

  remaining -= append_string(words, remaining, " ");
  if (minutes < 23) {
    remaining -= append_string(words, remaining, STUNDEN[hours % 12]);
  } else {
    remaining -= append_string(words, remaining, STUNDEN[(hours+1) % 12]);
  }
}
