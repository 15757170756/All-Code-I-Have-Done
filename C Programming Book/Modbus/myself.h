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
* �������ܣ��򿪴��ڲ�����
\**********************************/
DLL_DECLARATION EQUIP_HANDLE OpenEquipment(char* portName);

/**********************************\
* �������ܣ����modbus����Ȩ
\**********************************/
DLL_DECLARATION int GetConModbus(EQUIP_HANDLE hdl);

/**********************************\
* �������ܣ��رմ��ں�modbus����
\**********************************/
DLL_DECLARATION void CloseEquipment(EQUIP_HANDLE hdl);


DLL_DECLARATION int HaltX(EQUIP_HANDLE hdl);
DLL_DECLARATION int HaltY(EQUIP_HANDLE hdl);

DLL_DECLARATION float GetX(EQUIP_HANDLE hdl);
DLL_DECLARATION float GetY(EQUIP_HANDLE hdl);

DLL_DECLARATION void Test_HaltX(float relativeDistance_X, float relativeVelocity_X, EQUIP_HANDLE hdl);

/**********************************\
* �������ܣ���λ���������мĴ�������
\**********************************/
DLL_DECLARATION int Reset(EQUIP_HANDLE hdl);
/**********************************\
* �������ܣ�X��Y��������
* ���ص�ԭ�㣬�ٶȲ������ã�Ĭ���ٶ�
\**********************************/
DLL_DECLARATION int MoveToOrigin(EQUIP_HANDLE hdl);


DLL_DECLARATION int MoveRel_X(EQUIP_HANDLE hdl, float dx, float vx);
DLL_DECLARATION int MoveRel_Y(EQUIP_HANDLE hdl, float dy, float vy);

DLL_DECLARATION int MoveAbs_X(EQUIP_HANDLE hdl, float px, float vx);
DLL_DECLARATION int MoveAbs_Y(EQUIP_HANDLE hdl, float py, float vy);


/**********************************\
* �������ܣ�X����Y�������˶�����
* ������ٶȶ��ǵ����ȸ���������λΪmm��mm/s
* ���������˶�����Ժ�ŷ���
\**********************************/
DLL_DECLARATION int MoveRel_XY(EQUIP_HANDLE hdl, float dx, float dy, float vx, float vy);

/**********************************\
* �������ܣ�X����Y��ľ����˶�����
* ������ٶȶ��ǵ����ȸ���������λΪmm��mm/s
* ���������˶�����Ժ�ŷ���
\**********************************/
DLL_DECLARATION int MoveAbs_XY(EQUIP_HANDLE hdl, float px, float py, float vx, float vy);


DLL_DECLARATION void MoveRel_Z(EQUIP_HANDLE hdl, float dx, float dy,
	float vx, float vy, float start_X, float end_X,
	float start_Y, float end_Y, unsigned int Sleeptime);

#endif



///**********************************\
//* �������ܣ���ʮ������ת��Ϊ����������32λ�����Ʊ�ʾ��
//* ԭ��C�����е����ȸ����� float������32λ�Ķ����Ʊ�ʾ��
//* ���磺ʮ����0.2 ת��Ϊ������Ϊ3E4CCCCD������ǰ4λΪ���ֽ�
//* ��4λΪ���ֽڡ�������floatΪ0.2��
//* �����buf[0] = CCCD, buf[1] = 3E4C
//\**********************************/
//DLL_DECLARATION void DEC2Float_C(float dec, uint16_t* buf);
//DLL_DECLARATION void DEC2Float_G(float dec, uint16_t* buf);
//
///**********************************\
//* �������ܣ���������ת��Ϊʮ����������32λ�����Ʊ�ʾ��
//\**********************************/
//DLL_DECLARATION float Float2DEC(uint16_t* buf);
//
//
///**********************************\
//* �������ܣ�����X������˶��ٶ�
//\**********************************/
//DLL_DECLARATION void setrelativeVelocity_X(float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����Y������˶��ٶ�
//\**********************************/
//DLL_DECLARATION void setrelativeVelocity_Y(float relativeVelocity_Y, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����X������˶��ٶ�
//\**********************************/
//DLL_DECLARATION void setabsoluteVelocity_X(float absoluteVelocity_X, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����Y������˶��ٶ�
//\**********************************/
//DLL_DECLARATION void setabsoluteVelocity_Y(float absoluteVelocity_Y, modbus_t* ctx);
//
//
///**********************************\
//* �������ܣ�����X������˶�����
//\**********************************/
//DLL_DECLARATION void setrelativeDistance_X(float relativeDistance_X, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����Y������˶�����
//\**********************************/
//DLL_DECLARATION void setrelativeDistance_Y(float relativeDistance_Y, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����X������˶�����
//\**********************************/
//DLL_DECLARATION void setabsolutePosition_X(float absoluteDistance_X, modbus_t* ctx);
//
///**********************************\
//* �������ܣ�����Y������˶�����
//\**********************************/
//DLL_DECLARATION void setabsolutePosition_Y(float absoluteDistance_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* �������ܣ�ʹ��X������˶�����
//\**********************************/
//DLL_DECLARATION void enablerelative_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�ʹ��Y������˶�����
//\**********************************/
//DLL_DECLARATION void enablerelative_Y(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�ʹ��X������˶�����
//\**********************************/
//DLL_DECLARATION void enableabsolute_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�ʹ��Y������˶�����
//\**********************************/
//DLL_DECLARATION void enableabsolute_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* �������ܣ��ж�X������˶����
//\**********************************/
//DLL_DECLARATION int isrelativeActionDone_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ��ж�Y������˶����
//\**********************************/
//DLL_DECLARATION int isrelativeActionDone_Y(modbus_t* ctx);
//
///**********************************\
//* �������ܣ��ж�X������˶����
//\**********************************/
//DLL_DECLARATION int isabsoluteActionDone_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ��ж�Y������˶����
//\**********************************/
//DLL_DECLARATION int isabsoluteActionDone_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* �������ܣ�X������˶����λ��0
//\**********************************/
//DLL_DECLARATION void setrelativeActionDone_XT0(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�Y������˶����λ��0
//\**********************************/
//DLL_DECLARATION void setrelativeActionDone_YT0(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�X������˶����λ��0
//\**********************************/
//DLL_DECLARATION void setabsoluteActionDone_XT0(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�Y������˶����λλ��0
//\**********************************/
//DLL_DECLARATION void setabsoluteActionDone_YT0(modbus_t* ctx);
//
//
//
///**********************************\
//* ��������: ���Ժ���������X������˶��ĸ���״̬
//\**********************************/
//DLL_DECLARATION void testrelative_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* ��������: ���Ժ���������Y������˶��ĸ���״̬
//\**********************************/
//DLL_DECLARATION void testrelative_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx);
//
///**********************************\
//* ��������: ���Ժ���������X������˶��ĸ���״̬
//\**********************************/
//DLL_DECLARATION void testabsolute_X(float absoluteDistance_X, float absoluteVelocity_X, modbus_t* ctx);
//
///**********************************\
//* ��������: ���Ժ���������Y������˶��ĸ���״̬
//\**********************************/
//DLL_DECLARATION void testabsolute_Y(float absoluteDistance_Y, float absoluteVelocity_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* ��������: ���Ժ���������sethalt_X��ͣ����
//\**********************************/
//DLL_DECLARATION void testsethalt_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx);
//
///**********************************\
//* ��������: ���Ժ���������sethalt_Y��ͣ����
//\**********************************/
//DLL_DECLARATION void testsethalt_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx);
//
//
//
///**********************************\
//* �������ܣ���ȡ��ǰX������
//\**********************************/
//DLL_DECLARATION float getLocation_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ���ȡ��ǰX������
//\**********************************/
//DLL_DECLARATION float getLocation_Y(modbus_t* ctx);
//
//
//
//
///**********************************\
//* �������ܣ�X������ֹͣ
//\**********************************/
//DLL_DECLARATION void sethalt_X(modbus_t* ctx);
//
///**********************************\
//* �������ܣ�Y������ֹͣ
//\**********************************/
//DLL_DECLARATION void sethalt_Y(modbus_t* ctx);
//
//
//
///**********************************\
//* �������ܣ�X��Y��������
//\**********************************/
//DLL_DECLARATION void XT0_YT0(modbus_t* ctx);
//
///**********************************\
//* �������ܣ���λ���������мĴ�������
//\**********************************/
//DLL_DECLARATION void reset(modbus_t* ctx);
//
//
///**********************************\
//* �������ܣ��򿪴��ڲ�����
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