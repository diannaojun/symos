#include <string.h>

ulint_t hash1(const char *str) {
	const static ulint_t factor[4] = {31, 131, 1313, 13131};
	ulint_t ret = 0, len = 0;
	while (*str)
		ret = ret * factor[(++len) & 3] + *(++str);
	return ret * factor[len & 3] + len;
}

ulint_t hash2(const char *str) {
	ulint_t ret = 0, len = 0;
	while (*str)
		ret = (ret * 331 + *(++str)) % 1000000000000002493ull;
	return ret;
}
