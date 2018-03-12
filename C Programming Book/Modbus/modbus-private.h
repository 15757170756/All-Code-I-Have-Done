#ifndef _MODBUS_PRIVATE_H_
#define _MODBUS_PRIVATE_H_

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


# include "stdint.h"
# include <time.h>
typedef int ssize_t;

#include "modbus.h"

MODBUS_BEGIN_DECLS

/* It's not really the minimal length (the real one is report slave ID
 * in RTU (4 bytes)) but it's a convenient size to use in RTU or TCP
 * communications to read many values or write a single one.
 * Maximum between :
 * - HEADER_LENGTH_TCP (7) + function (1) + address (2) + number (2)
 * - HEADER_LENGTH_RTU (1) + function (1) + address (2) + number (2) + CRC (2)
 */
#define _MIN_REQ_LENGTH 12

#define _REPORT_SLAVE_ID 180

#define _MODBUS_EXCEPTION_RSP_LENGTH 5

/* Timeouts in microsecond (0.5 s) */
#define _RESPONSE_TIMEOUT    500000
#define _BYTE_TIMEOUT        500000

/* Function codes */
/*功能码	名称          	   作用
01	Read Coil Status 读取线圈状态	取得一组逻辑线圈的当前状态(ON / OFF)
02  Read Input Status 读取输入状态	取得一组开关输入的当前状态(ON / OFF)
03	Read Holding Registers 读取保持寄存器	在一个或多个保持寄存器中取得当前的二进制值
04	Read Input Registers 读取输入寄存器	在一个或多个输入寄存器中取得当前的二进制值
05	Force Single Coil 强置单线圈		强置一个逻辑线圈的通断状态
06	Preset Single Register 预置单寄存器	把具体二进值装入一个保持寄存器
07	Read Exception Status 读取异常状态	取得 8 个内部线圈的通断状态，这 8 个线圈的地址由控制器决定，用户逻辑可以将这些线圈定义，以说明
						从机状态，短报文适宜于迅速读取状态
08	Diagnostics 回送诊断校验	把诊断校验报文送从机，以对通信处理进行评鉴
09	Program 484	编程(只用于 484)	使主机模拟编程器作用，修改 PC 从机逻辑
10	Poll 484 控询(只用于 484)	可使主机与一台正在执行长程序任务从机通信，探询该从机是否已完成其操作任务，仅在含有功能码 9
							的报文发送后，本功能码才发送
11	Fetch Comm. Event Ctr 读取事件计数	可使主机发出单询问，并随即判定操作是否成功，尤其是该命令或其它应答产生通信错误时
12	Fetch Comm. Event Log 读取通信事件记录	可使主机检索每台从机的 ModBus 事务处理通信事件记录。如果某项事务处理完成，记录会给出有关错误
13	Program Controller 编程(184 / 384 484 584)	可使主机模拟编程器功能修改 PC 从机逻辑
14	Poll Controller 探询(184 / 384 484 584)	可使主机与正在执行任务的从机通信，定期控询该从机是否已完成其程序操作，仅在含有功能 13 的报文
								发送后，本功能码才得发送
15	Force Multiple Coils 强置多线圈	强置一串连续逻辑线圈的通断
16	Preset Multiple Registers 预置多寄存器	把具体的二进制值装入一串连续的保持寄存器
17	Report Slave ID	报告从机标识	可使主机判断编址从机的类型及该从机运行指示灯的状态
18	Program 884/M84 884 和 MICRO 84	可使主机模拟编程功能，修改 PC 状态逻辑
19	Reset Comm. Link 重置通信链路	发生非可修改错误后，是从机复位于已知状态，可重置顺序字节
20	Read General Reference 读取通用参数(584L)	显示扩展存储器文件中的数据信息
21		写入通用参数(584L)	把通用参数写入扩展存储文件，或修改
22~64	保留作扩展功能备用
65~72	保留以备用户功能所用	留作用户功能的扩展编码
73~119	非法功能
120~127	保留	留作内部作用
128~255	保留	用于异常应答

22 Mask Write 4X Register 
23 Read/Write 4X Registers 
24 Read FIFO Queue*/
#define _FC_READ_COILS                0x01
#define _FC_READ_DISCRETE_INPUTS      0x02
#define _FC_READ_HOLDING_REGISTERS    0x03
#define _FC_READ_INPUT_REGISTERS      0x04
#define _FC_WRITE_SINGLE_COIL         0x05
#define _FC_WRITE_SINGLE_REGISTER     0x06
#define _FC_READ_EXCEPTION_STATUS     0x07
#define _FC_WRITE_MULTIPLE_COILS      0x0F
#define _FC_WRITE_MULTIPLE_REGISTERS  0x10
#define _FC_REPORT_SLAVE_ID           0x11
#define _FC_WRITE_AND_READ_REGISTERS  0x17

typedef enum {
    _MODBUS_BACKEND_TYPE_RTU=0,
    _MODBUS_BACKEND_TYPE_TCP
} modbus_bakend_type_t;

/* This structure reduces the number of params in functions and so
 * optimizes the speed of execution (~ 37%). */
typedef struct _sft {
    int slave;
    int function;
    int t_id;
} sft_t;



//const modbus_backend_t _modbus_rtu_backend = {
//	_MODBUS_BACKEND_TYPE_RTU,
//	_MODBUS_RTU_HEADER_LENGTH,
//	_MODBUS_RTU_CHECKSUM_LENGTH,
//	MODBUS_RTU_MAX_ADU_LENGTH,
//	_modbus_set_slave,
//	_modbus_rtu_build_request_basis,
//	_modbus_rtu_build_response_basis,
//	_modbus_rtu_prepare_response_tid,
//	_modbus_rtu_send_msg_pre,
//	_modbus_rtu_send,
//	_modbus_rtu_recv,
//	_modbus_rtu_check_integrity,
//	NULL,
//	_modbus_rtu_connect,
//	_modbus_rtu_close,
//	_modbus_rtu_flush,
//	_modbus_rtu_select,
//	_modbus_rtu_filter_request
//};
typedef struct _modbus_backend {
    unsigned int backend_type;                                             //_MODBUS_BACKEND_TYPE_RTU
    unsigned int header_length;
    unsigned int checksum_length;
    unsigned int max_adu_length;
	//函数指针
    int (*set_slave) (modbus_t *ctx, int slave); 
    int (*build_request_basis) (modbus_t *ctx, int function, int addr,
                                int nb, uint8_t *req);                     //_modbus_rtu_build_request_basis
    int (*build_response_basis) (sft_t *sft, uint8_t *rsp);
    int (*prepare_response_tid) (const uint8_t *req, int *req_length);
    int (*send_msg_pre) (uint8_t *req, int req_length);
    ssize_t (*send) (modbus_t *ctx, const uint8_t *req, int req_length);
    ssize_t (*recv) (modbus_t *ctx, uint8_t *rsp, int rsp_length);
    int (*check_integrity) (modbus_t *ctx, uint8_t *msg,
                            const int msg_length);
    int (*pre_check_confirmation) (modbus_t *ctx, const uint8_t *req,
                                   const uint8_t *rsp, int rsp_length);
    int (*connect) (modbus_t *ctx);
    void (*close) (modbus_t *ctx);
    int (*flush) (modbus_t *ctx);
    int (*select) (modbus_t *ctx, fd_set *rfds, struct timeval *tv, int msg_length);
    int (*filter_request) (modbus_t *ctx, int slave);
} modbus_backend_t;

struct _modbus {
    /* Slave address */
    int slave;
    /* Socket or file descriptor */
    int s;
    int debug;
    int error_recovery;
    struct timeval response_timeout;
    struct timeval byte_timeout;
    const modbus_backend_t *backend;
    void *backend_data;
};

void _modbus_init_common(modbus_t *ctx);
void _error_print(modbus_t *ctx, const char *context);

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#endif

MODBUS_END_DECLS

#endif  /* _MODBUS_PRIVATE_H_ */
