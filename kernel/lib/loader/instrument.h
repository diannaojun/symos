/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-27
 */
#ifndef _SYM_KERNEL_INSTRUMENT_H_
#define _SYM_KERNEL_INSTRUMENT_H_

#include <lib/loader/main.h>

enum insType{
	UK,CONSOLE,HD,FP
};
#pragma pack(4)
struct Instrument{
	enum insType it;
	u16 it2;
	void* object;
	void* operation;
};

#endif //_SYM_KERNEL_INSTRUMENT_H_