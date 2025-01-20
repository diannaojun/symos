#include <string.h>

uint64_t hash1(const char *str) {
	const static uint64_t factor[4] = {31, 131, 1313, 13131};
	uint64_t ret = 0, len = 0;
	while (*str)
		ret = ret * factor[(++len) & 3] + *(++str);
	return ret * factor[len & 3] + len;
}

uint64_t hash2(const char *str) {
	uint64_t ret = 0;
	while (*str)
		ret = (ret * 331 + *(++str)) % 1000000000000002493ull;
	return ret;
}
