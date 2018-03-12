#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

	// In DLL project, Visual Studio will define macro ${PROJECT_NAME}_EXPORTS
	// we can use this marco to EXPORT variables/functions in DLL project,
	// and to IMPORT variables/functions in other projects which using this dll.
#ifdef SAMPLEDLL_EXPORTS
#define DLL_DECLARATION __declspec(dllexport) 
#else
#define DLL_DECLARATION __declspec(dllimport)
#endif

// sample SDK

typedef void* EQUIP_HANDLE;

/**********************************\
* 函数功能：打开串口并连接
\**********************************/
DLL_DECLARATION EQUIP_HANDLE OpenEquipment(char* portName);

/**********************************\
* 函数功能：获得modbus控制权
\**********************************/
DLL_DECLARATION int GetConModbus(EQUIP_HANDLE hdl);

/**********************************\
* 函数功能：关闭串口和modbus连接
\**********************************/
DLL_DECLARATION void CloseEquipment(EQUIP_HANDLE hdl);


DLL_DECLARATION int HaltX(EQUIP_HANDLE hdl);
DLL_DECLARATION int HaltY(EQUIP_HANDLE hdl);

DLL_DECLARATION float GetX(EQUIP_HANDLE hdl);
DLL_DECLARATION float GetY(EQUIP_HANDLE hdl);

DLL_DECLARATION void Test_HaltX(float relativeDistance_X, float relativeVelocity_X, EQUIP_HANDLE hdl);

/**********************************\
* 函数功能：复位操作，所有寄存器清零
\**********************************/
DLL_DECLARATION int Reset(EQUIP_HANDLE hdl);
/**********************************\
* 函数功能：X与Y轴回零操作
* 即回到原点，速度不用设置，默认速度
\**********************************/
DLL_DECLARATION int MoveToOrigin(EQUIP_HANDLE hdl);


DLL_DECLARATION int MoveRel_X(EQUIP_HANDLE hdl, float dx, float vx);
DLL_DECLARATION int MoveRel_Y(EQUIP_HANDLE hdl, float dy, float vy);

DLL_DECLARATION int MoveAbs_X(EQUIP_HANDLE hdl, float px, float vx);
DLL_DECLARATION int MoveAbs_Y(EQUIP_HANDLE hdl, float py, float vy);


/**********************************\
* 函数功能：X轴与Y轴的相对运动控制
* 距离和速度都是单精度浮点数，单位为mm和mm/s
* 两个方向都运动完成以后才返回
\**********************************/
DLL_DECLARATION int MoveRel_XY(EQUIP_HANDLE hdl, float dx, float dy, float vx, float vy);

/**********************************\
* 函数功能：X轴与Y轴的绝对运动控制
* 距离和速度都是单精度浮点数，单位为mm和mm/s
* 两个方向都运动完成以后才返回
\**********************************/
DLL_DECLARATION int MoveAbs_XY(EQUIP_HANDLE hdl, float px, float py, float vx, float vy);


DLL_DECLARATION void MoveRel_Z(EQUIP_HANDLE hdl, float dx, float dy,
	float vx, float vy, float start_X, float end_X,
	float start_Y, float end_Y, unsigned int Sleeptime);

#endif



///**********************************\
//* 函数功能：将十进制数转化为浮点数（用32位二进制表示）
//* 原理：C语言中单精度浮点数 float就是用32位的二进制表示的
//* 例如：十进制0.2 转化为浮点数为3E4CCCCD，其中前4位为高字节
//* 后4位为低字节。如输入float为0.2，
//* 则输出buf[0] = CCCD, buf[1] = 3E4C
//\**********************************/
//DLL_DECLARATION void DEC2Float_C(float dec, uint16_t* buf);
//DLL_DECLARATION void DEC2Float_G(float dec, uint16_t* buf);
//
///**********************************\
//* 函数功能：将浮点数转化为十进制数（用32位二进制表示）
//\**********************************/
//DLL_DECLARATION float Float2DEC(uint16_t* buf);
//
//
///**********************************\
//* 函数功能：设置X轴相对运动速度
//\**********************************/
//DLL_DECLARATION void setrelativeVelocity_X(float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置Y轴相对运动速度
//\**********************************/
//DLL_DECLARATION void setrelativeVelocity_Y(float relativeVelocity_Y, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置X轴绝对运动速度
//\**********************************/
//DLL_DECLARATION void setabsoluteVelocity_X(float absoluteVelocity_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置Y轴绝对运动速度
//\**********************************/
//DLL_DECLARATION void setabsoluteVelocity_Y(float absoluteVelocity_Y, modbus_t* ctx);
//
//
///**********************************\
//* 函数功能：设置X轴相对运动距离
//\**********************************/
//DLL_DECLARATION void setrelativeDistance_X(float relativeDistance_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置Y轴相对运动距离
//\**********************************/
//DLL_DECLARATION void setrelativeDistance_Y(float relativeDistance_Y, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置X轴绝对运动坐标
//\**********************************/
//DLL_DECLARATION void setabsolutePosition_X(float absoluteDistance_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能：设置Y轴绝对运动距离
//\**********************************/
//DLL_DECLARATION void setabsolutePosition_Y(float absoluteDistance_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能：使能X轴相对运动控制
//\**********************************/
//DLL_DECLARATION void enablerelative_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：使能Y轴相对运动控制
//\**********************************/
//DLL_DECLARATION void enablerelative_Y(modbus_t* ctx);
//
///**********************************\
//* 函数功能：使能X轴绝对运动控制
//\**********************************/
//DLL_DECLARATION void enableabsolute_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：使能Y轴绝对运动控制
//\**********************************/
//DLL_DECLARATION void enableabsolute_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能：判断X轴相对运动完成
//\**********************************/
//DLL_DECLARATION int isrelativeActionDone_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：判断Y轴相对运动完成
//\**********************************/
//DLL_DECLARATION int isrelativeActionDone_Y(modbus_t* ctx);
//
///**********************************\
//* 函数功能：判断X轴绝对运动完成
//\**********************************/
//DLL_DECLARATION int isabsoluteActionDone_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：判断Y轴绝对运动完成
//\**********************************/
//DLL_DECLARATION int isabsoluteActionDone_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能：X轴相对运动完成位置0
//\**********************************/
//DLL_DECLARATION void setrelativeActionDone_XT0(modbus_t* ctx);
//
///**********************************\
//* 函数功能：Y轴相对运动完成位置0
//\**********************************/
//DLL_DECLARATION void setrelativeActionDone_YT0(modbus_t* ctx);
//
///**********************************\
//* 函数功能：X轴绝对运动完成位置0
//\**********************************/
//DLL_DECLARATION void setabsoluteActionDone_XT0(modbus_t* ctx);
//
///**********************************\
//* 函数功能：Y轴绝对运动完成位位置0
//\**********************************/
//DLL_DECLARATION void setabsoluteActionDone_YT0(modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能: 测试函数：测试X轴相对运动的各个状态
//\**********************************/
//DLL_DECLARATION void testrelative_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能: 测试函数：测试Y轴相对运动的各个状态
//\**********************************/
//DLL_DECLARATION void testrelative_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx);
//
///**********************************\
//* 函数功能: 测试函数：测试X轴绝对运动的各个状态
//\**********************************/
//DLL_DECLARATION void testabsolute_X(float absoluteDistance_X, float absoluteVelocity_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能: 测试函数：测试Y轴绝对运动的各个状态
//\**********************************/
//DLL_DECLARATION void testabsolute_Y(float absoluteDistance_Y, float absoluteVelocity_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能: 测试函数：测试sethalt_X暂停函数
//\**********************************/
//DLL_DECLARATION void testsethalt_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* 函数功能: 测试函数：测试sethalt_Y暂停函数
//\**********************************/
//DLL_DECLARATION void testsethalt_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能：获取当前X轴坐标
//\**********************************/
//DLL_DECLARATION float getLocation_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：获取当前X轴坐标
//\**********************************/
//DLL_DECLARATION float getLocation_Y(modbus_t* ctx);
//
//
//
//
///**********************************\
//* 函数功能：X轴立马停止
//\**********************************/
//DLL_DECLARATION void sethalt_X(modbus_t* ctx);
//
///**********************************\
//* 函数功能：Y轴立马停止
//\**********************************/
//DLL_DECLARATION void sethalt_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* 函数功能：X与Y轴回零操作
//\**********************************/
//DLL_DECLARATION void XT0_YT0(modbus_t* ctx);
//
///**********************************\
//* 函数功能：复位操作，所有寄存器清零
//\**********************************/
//DLL_DECLARATION void reset(modbus_t* ctx);
//
//
///**********************************\
//* 函数功能：打开串口并连接
//\**********************************/
//DLL_DECLARATION modbus_t* open_serial_port(char* portName, modbus_t* ctx);

//// cpp
//#include "modbus.h"
//#include "modbus-rtu.h"
//#include "modbus-private.h"
//typedef void* EQUIP_HANDLE;
//EQUIP_HANDLE OpenEquipment(char* portName, EQUIP_HANDLE hdl)
//{
//	modbus_t* ctx = openSerial(portName);
//	return (void*)(ctx);
//}