/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-27
 */
#ifndef _SYM_KERNEL_PRINT_H_
#define _SYM_KERNEL_PRINT_H_

#include <lib/loader/main.h>
#include <lib/loader/text_screen.h>
#include <lib/loader/instrument.h>
#include <ia32/stddef.h>

struct Instrument *StdCon;
struct Instrument *ErrCon;
static char NumTable[] = "0123456789ABCDEF";
static char bufer[128] = "";

#pragma pack(4)

struct ConsoleOpt {
	void (*clear)(void *);
	void (*scroll)(void *, u16);
	void (*puts)(void *, const char *);
	void (*putc)(void *, char);
};

static struct Instrument Console;
static struct ConsoleOpt tso;
static struct TextScreen ts;

void printsi(const char *, struct Instrument *);
void printsl(const char *);
void printel(const char *, u16);

void initPrint(void) {
	static int i;

	ts.h = 25, ts.w = 80;
	ts.cx = ts.cy = 0;
	ts.vm = (void *)0xb8000;

	tso.clear = (void (*)(void *))clearTextScreen;
	tso.scroll = (void (*)(void *, u16))scrollTextScreen;
	tso.puts = (void (*)(void *, const char *))TSputs;
	tso.putc = (void (*)(void *, char))TSputc;

	Console.it = CONSOLE;
	Console.it2 = 1;
	Console.object = &ts;
	Console.operation = &tso;

	StdCon = &Console;
	ErrCon = StdCon;
	printsl("\e0");
	return ;
}

void printsi(const char *s, struct Instrument *ins) {
	((struct ConsoleOpt *)(ins->operation))->puts(ins->object, s);
}

void printsl(const char *s) {
	printsi(s, StdCon);
}

void printsni(const char *s, u64 n, struct Instrument *ins) {
	static u64 i;
	for (i = 0; i < n; ++i) {
		((struct ConsoleOpt *)(ins->operation))->putc(ins->object, s[i]);
	}
}

void printsnl(const char *s, u64 n) {
	printsni(s, n, StdCon);
}

void printel(const char *description, u16 code) {
	static u16 i;
	for (i = 0; i < 4; ++i, code <<= 4)
		bufer[i + 1] = NumTable[(code & 0xf000) >> 12];
	bufer[0] = '#', bufer[5] = 0;
	printsi("[Loader32] ", ErrCon);
	printsi("\es\x07[\es\x0d", ErrCon);
	printsi(bufer, ErrCon);
	printsi("\es\x07]\es\x0c", ErrCon);
	printsi(description, ErrCon);
	printsi("\e0", ErrCon);
}

void printdi (u64 num, struct Instrument *ins) {
	static u16 i;
	for (i = 0; i < 8; ++i, num <<= 4)
		bufer[i + 2] = NumTable[(num & 0xf000000000000000) >> 60];
	for (i = 0; i < 8; ++i, num <<= 4)
		bufer[i + 11] = NumTable[(num & 0xf000000000000000) >> 60];
	bufer[0] = '0', bufer[1] = 'x', bufer[10] = '_', bufer[19] = 0;
	printsi(bufer, ins);
}

void printdl (u64 num) {
	printdi(num, StdCon);
}

#endif //_SYM_KERNEL_PRINT_H_
