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
	// “设备” 结构
	void* ins_data;			// 设备数据指针
	void* ins_operation;	// 设备操作指针
	u16 ins_type,ins_class;	// 设备类型、类
	u32 ins_uuid;			// 设备标志
};

#endif //_SYM_KERNEL_INSTRUMENT_H_
