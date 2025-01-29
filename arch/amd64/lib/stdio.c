#include <stdio.h>


static uint16_t skip_atoi(const char **str) {
	uint16_t num = 0;
	while (isdigit(**str))
		num = num * 10 + *((*str)++) - '0';
	return num;
}
static char *number(char *str, int64_t x, int base, int flag, int flied_width, int precision, char space) {
	char buffer[40], *digit = "0123456789abcdefghijklmnopqrstuvwxyz";
	int len;
	if (flag & __STDIO_UPPER__)
		digit = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (!x) 
		buffer[0] = '0', len = 1;
	else {
		len = 0;
		if (x < 0) { if (flag & __STDIO_SIGNAL__)
			*str++ = '-', x = -x, --flied_width;
		} else if (flag & __STDIO_SIGNED__)
			*str++ = '+', --flied_width;
		for (; x; x /= base)
			buffer[len++] = digit[x % base];
	}
	if (flag & __STDIO_LEFT__) {
		flied_width -= len;
		while (flied_width-- > 0) *str++ = space;
		while (len--) *str++ = buffer[len];
	} else {
		while (len--) *str++ = buffer[len];
		flied_width -= len;
		while (flied_width-- > 0) *str++ = space;
	}
	return str;
}
int vsprintf(char *buf, const char *fmt, va_list args) {
	char *str, *temp;
	char qualifier, space;
	int flag, len;
	int field_width, precision;
    uint64_t num;
	for (str = buf; *fmt; fmt++) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
		flag = 0;
		precision = field_width = -1;
		qualifier = 0;
		space = ' ';
	loop:
		switch (*++fmt) {
			case '-': flag |= __STDIO_LEFT__; goto loop;
			case '+': flag |= __STDIO_SIGNED__; goto loop;
			case '0': space = '0'; goto loop;
			case '#': flag |= __STDIO_EXT__; goto loop;
			case ' ': space = ' '; goto loop;
		}
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			field_width = va_arg(args, int);
			if (field_width < 0)
				field_width = -field_width, flag |= __STDIO_LEFT__;
		}
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				precision = va_arg(args, int);
				if (precision < 0)
					precision = -precision, flag |= __STDIO_LEFT__;
			}
			if (precision < 0) precision = 0;
		}
		if (*fmt == 'l')
			if (*++fmt == 'l') qualifier = 'L', ++fmt;
			else qualifier = 'l';
		else if (*fmt == 'h')
			if (*++fmt == 'h') qualifier = 'H', ++fmt;
			else qualifier = 'h';
		else if (*fmt == 'q' || *fmt == 'Q') qualifier = 'z', ++fmt;
		else if (*fmt == 'z' || *fmt == 'Z') qualifier = 'z', ++fmt;
		else if (*fmt == 't' || *fmt == 'T') qualifier = 'z', ++fmt;
		else if (*fmt == 'H') qualifier = 'H', ++fmt;
		else if (*fmt == 'L') qualifier = 'L', ++fmt;
        
        if (isupper(*fmt)) flag |= __STDIO_UPPER__;
		switch (tolower(*fmt)) {
			case 'c':
				if (!(flag & __STDIO_LEFT__))
					while (--field_width > 0)
						*str++ = space;
				*str++ = (unsigned char) va_arg(args, size_t);
				break;
			case 's':
				temp = va_arg(args, char *);
				len = strlen(temp);
				if (flag & __STDIO_LEFT__)
					while (*temp)
						*str++ = *temp++;
				if (field_width > len) {
					field_width -= len;
					while (field_width--)
						*str++ = space;
				}
				if (!(flag & __STDIO_LEFT__))
					while (*temp)
						*str++ = *temp++;
				break;
			case 'd':
			case 'i': len = 10, flag |= __STDIO_SIGNAL__ | __STDIO_NUMBER__; break;
			case 'u': len = 10, flag |= __STDIO_NUMBER__; break;
			case 'o': len = 8, flag |= __STDIO_NUMBER__; break;
			case 'x': len = 16, flag |= __STDIO_NUMBER__; break;
			case 'b': len = 2, flag |= __STDIO_NUMBER__; break;
			default: *str++ = *fmt; break;
		}
        if(flag & __STDIO_NUMBER__){
			switch (qualifier) {
				case 'H': num = va_arg(args, char); break;
				case 'h': num = va_arg(args, short); break;
				case 'l': num = va_arg(args, long); break;
				case 'L': num = va_arg(args, long long); break;
				default: num = va_arg(args, int);
			}
            str = number(str, num, len, flag, field_width, precision, space);
        }
	}
	*str = 0;
	return str - buf;
}

int sprintf(char *buf, const char *fmt, ...) {
	va_list args;
	int i;
	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);
	return i;
}
