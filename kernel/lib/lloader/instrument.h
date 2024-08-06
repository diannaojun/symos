/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-05
 */
#ifndef _SYM_KERNEL_INSTRUMENT_H_
#define _SYM_KERNEL_INSTRUMENT_H_

#include <IA64/stddef.h>

#pragma pack(8)
struct Instrument{
	void* ins_data;
	void* ins_operation;
	u16 ins_type,ins_class;
	u32 ins_uuid;
};

#endif //_SYM_KERNEL_INSTRUMENT_H_
