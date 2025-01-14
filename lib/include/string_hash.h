#include <string.h>

struct string_hash {
    unsigned long long hash1;
    unsigned long long hash2;
};

const int string_hash_mod = 1e9 + 7;
const int hash_base1 = 114;
const int hash_base2 = 514;

inline string_hash get_string_hash(const char *str) {
    int len = strlen(str);
    string_hash reu = {0, 0};
    for (int i = 0; i < len; i++) {
        reu.hash1 = reu.hash1 * hash_base1 + str[i];
        reu.hash2 = (reu.hash2 * hash_base2 + str[i]) % string_hash_mod;
    }
    return reu;
}

inline string_hash get_string_hash(const char *str, const int &len) {
    string_hash reu = {0, 0};
    for (int i = 0; i < len; i++) {
        reu.hash1 = reu.hash1 * hash_base1 + str[i];
        reu.hash2 = (reu.hash2 * hash_base2 + str[i]) % string_hash_mod;
    }
    return reu;
}
