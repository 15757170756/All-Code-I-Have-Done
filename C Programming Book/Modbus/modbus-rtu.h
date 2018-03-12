#ifndef _MODBUS_RTU_H_
#define _MODBUS_RTU_H_

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//	// In DLL project, Visual Studio will define macro ${PROJECT_NAME}_EXPORTS
//	// we can use this marco to EXPORT variables/functions in DLL project,
//	// and to IMPORT variables/functions in other projects which using this dll.
//#ifdef SAMPLEDLL_EXPORTS
//#define DLL_DECLARATION __declspec(dllexport) 
//#else
//#define DLL_DECLARATION __declspec(dllimport)
//#endif


#include "modbus.h"

MODBUS_BEGIN_DECLS

/* Modbus_Application_Protocol_V1_1b.pdf Chapter 4 Section 1 Page 5
 * RS232 / RS485 ADU = 253 bytes + slave (1 byte) + CRC (2 bytes) = 256 bytes
 */
#define MODBUS_RTU_MAX_ADU_LENGTH  256

modbus_t* modbus_new_rtu(const char *device, int baud, char parity,
                         int data_bit, int stop_bit);

#define MODBUS_RTU_RS232 0
#define MODBUS_RTU_RS485 1

int modbus_rtu_set_serial_mode(modbus_t *ctx, int mode);
int modbus_rtu_get_serial_mode(modbus_t *ctx);

MODBUS_END_DECLS

#endif /* _MODBUS_RTU_H_ */
