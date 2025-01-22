#include <ctype.h>

int isalnum(wchar_t ch) { return _isalnum(ch); }
int isalpha(wchar_t ch) { return _isalpha(ch); }
int isascii(wchar_t ch) { return _isascii(ch); }
int iscntrl(wchar_t ch) {
    if _isascii (ch)
        return (ch < ' ' || ch == 127);
    return 0;
}
int isdigit(wchar_t ch) {
    if _isascii (ch)
        return (ch >= '0' && ch <= '9');
    return 0;
}
int isgraph(wchar_t ch) {
    if _isascii (ch)
        return (ch >= '!' && ch <= '~');
    return 0;
}
int islower(wchar_t ch) {
    if _isascii (ch)
        return (ch >= 'a' && ch <= 'z');
    return 0;
}
int isprint(wchar_t ch) {
    if _isascii (ch)
        return (ch >= ' ' && ch <= '~');
    return 0;
}
int ispunct(wchar_t ch) {
    if _isascii (ch)
        return (ch >= '!' && ch <= '/') | (ch == ' ');
    return 0;
}
int isspace(wchar_t ch) {
    if _isascii (ch)
        return (ch >= '\t' && ch <= '\r') | (ch >= ':' && ch <= '@') | (ch >= '[' && ch <= '`') |
               (ch >= '{' && ch <= '~');
    return 0;
}
int isupper(wchar_t ch) {
    if _isascii (ch)
        return (ch >= 'A' && ch <= 'Z');
    return 0;
}
int isxdigit(wchar_t ch) { return (ch >= '0' && ch <= '9') | (ch >= 'A' && ch <= 'F') | (ch >= 'a' && ch <= 'f'); }
int toascii(wchar_t ch) {
    if _isascii (ch)
        return ch;
    return '?';
}
int tolower(wchar_t ch) {
    if (!isupper(ch))
        return ch;
    if _isascii (ch)
        return ch + 32;
    return '?';
}
int toupper(wchar_t ch) {
    if (!islower(ch))
        return ch;
    if _isascii (ch)
        return ch - 32;
    return '?';
}
