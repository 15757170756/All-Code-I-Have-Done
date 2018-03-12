#include <stdio.h>
//#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "myself.h"
 #include "modbus.h"
 #include "modbus-rtu.h"
 #include "modbus-private.h"


//int main(int argc, char *argv[])
//{
//	modbus_t* ctx = NULL;
//	char* portName = "COM2";
//
//	ctx = open_serial_port(portName, ctx);
//
//	setabsolutePosition_X(1000, ctx);
//	setabsoluteVelocity_X(20, ctx);
//
//	enablerelative_X(ctx);
//	uint16_t data[2] = { 0xc456, 0x0000 };
//	int rc = modbus_write_registers(ctx, 29, 2, data);
//	getLocation_X(ctx);
//	getLocation_Y(ctx);
//
//	modbus_close(ctx);
//	modbus_free(ctx);
//
//	return 0;
//}


/**********************************\
* 函数功能：将十进制数转化为浮点数（用32位二进制表示）
* 原理：C语言中单精度浮点数 float就是用32位的二进制表示的
* 例如：十进制0.2 转化为浮点数为3E4CCCCD，其中前4位为高字节
* 后4位为低字节。如输入float为0.2，
* 则输出buf[0] = CCCD, buf[1] = 3E4C
\**********************************/
void DEC2Float_C(float dec, uint16_t* buf) {
	uint16_t* p = NULL;
	p = (uint16_t*)(&dec);
	buf[1] = *p++;
	buf[0] = *p;
}


/**********************************\
* 函数功能：将十进制数转化为浮点数（用32位二进制表示）
* 原理：根据转换的一般原理，IEEE规定的(未完成)
\**********************************/
void DEC2Float_G(float dec, uint16_t* buf) {
	int s;
	if (dec < 0)
		s = 1;
	else
		s = 0;
	int integer = (int)dec;
	float decimal = dec - integer;
	int m = 0;
	while ((integer >> 1) > 0) {
		integer = integer >> 1;
		m++;
	}
	printf("%d\n", m);
}


float Float2DEC(uint16_t* buf) {
	float* a = NULL;
	uint32_t data;
	data = ((uint32_t)buf[0] << 16) + buf[1];
	a = (float*)(&data);
	return (*a);
}


/**********************************\
* 函数功能：设置X轴相对运动速度
\**********************************/
void setrelativeVelocity_X(float relativeVelocity_X, modbus_t* ctx) {
	int rc;
	uint16_t dara_relativeVelocity_X[2] = { 0 };

	DEC2Float_C(relativeVelocity_X, dara_relativeVelocity_X);

	rc = modbus_write_registers(ctx, 4, 2, dara_relativeVelocity_X);
	if (2 == rc) {
		//printf("成功写入X轴相对运动速度寄存器，速度为%.1fmm/s\n", relativeVelocity_X);
	}
	else {}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置Y轴相对运动速度
\**********************************/
void setrelativeVelocity_Y(float relativeVelocity_Y, modbus_t* ctx) {
	int rc;
	uint16_t data_relativeVelocity_Y[2] = { 0 };

	DEC2Float_C(relativeVelocity_Y, data_relativeVelocity_Y);

	rc = modbus_write_registers(ctx, 10, 2, data_relativeVelocity_Y);
	if (2 == rc) {
		//printf("成功写入Y轴相对运动速度寄存器，速度为%.1fmm/s\n", relativeVelocity_Y);
	}
	else {}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置X轴绝对运动速度
\**********************************/
void setabsoluteVelocity_X(float absoluteVelocity_X, modbus_t* ctx) {
	int rc;
	uint16_t data_absoluteVelocity_X[2] = { 0 };

	DEC2Float_C(absoluteVelocity_X, data_absoluteVelocity_X);

	rc = modbus_write_registers(ctx, 12, 2, data_absoluteVelocity_X);
	if (2 == rc) {
		//printf("成功写入X轴绝对运动速度寄存器，速度为%.1fmm/s\n", absoluteVelocity_X);
	}
	else { }
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置Y轴绝对运动速度
\**********************************/
void setabsoluteVelocity_Y(float absoluteVelocity_Y, modbus_t* ctx) {
	int rc;
	uint16_t data_absoluteVelocity_Y[2] = { 0 };

	DEC2Float_C(absoluteVelocity_Y, data_absoluteVelocity_Y);

	rc = modbus_write_registers(ctx, 16, 2, data_absoluteVelocity_Y);
	if (2 == rc) {
		//printf("成功写入Y轴绝对运动速度寄存器，速度为%.1fmm/s\n", absoluteVelocity_Y);
	}
	else {}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置X轴相对运动距离
\**********************************/
void setrelativeDistance_X(float relativeDistance_X, modbus_t* ctx) {
	int rc;
	uint16_t data_relativeDistance_X[2] = { 0 };

	DEC2Float_C(-1.0 * relativeDistance_X, data_relativeDistance_X);

	rc = modbus_write_registers(ctx, 2, 2, data_relativeDistance_X);
	if (2 == rc) {
		//printf("成功写入X轴相对运动距离寄存器，移动距离为%.1fmm\n", relativeDistance_X);
	}
	else{}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置Y轴相对运动距离
\**********************************/
void setrelativeDistance_Y(float relativeDistance_Y, modbus_t* ctx) {
	int rc;
	uint16_t data_relativeDistance_Y[2] = { 0 };

	DEC2Float_C(relativeDistance_Y, data_relativeDistance_Y);

	rc = modbus_write_registers(ctx, 8, 2, data_relativeDistance_Y);
	if (2 == rc) {
		//printf("成功写入Y轴相对运动距离寄存器，移动距离为%.1fmm\n", relativeDistance_Y);
	}
	else{}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置X轴绝对运动坐标
\**********************************/
void setabsolutePosition_X(float absoluteDistance_X, modbus_t* ctx) {
	int rc;
	uint16_t data_absoluteDistance_X[2] = { 0 };

	DEC2Float_C(-1.0 * absoluteDistance_X, data_absoluteDistance_X);

	rc = modbus_write_registers(ctx, 31, 2, data_absoluteDistance_X);
	if (2 == rc) {
		//printf("成功写入X轴绝对运动距离寄存器，移动距离为%.1fmm\n", absoluteDistance_X);
	}
	else{}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：设置Y轴绝对运动坐标
\**********************************/
void setabsolutePosition_Y(float absoluteDistance_Y, modbus_t* ctx) {
	int rc;
	uint16_t data_absoluteDistance_Y[2] = { 0 };

	DEC2Float_C(absoluteDistance_Y, data_absoluteDistance_Y);

	rc = modbus_write_registers(ctx, 14, 2, data_absoluteDistance_Y);
	if (2 == rc) {
		//printf("成功写入Y轴绝对运动距离寄存器，移动距离为%.1fmm\n", absoluteDistance_Y);
	}
	else{}
		//printf("未写入\n");
}


/**********************************\
* 函数功能：使能X轴相对运动控制
\**********************************/
void enablerelative_X(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 1, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 1, data0[0] | 0x0001);
		if (1 == rc) {
			//printf("使能X轴相对运动\n");
		}
	}
}


/**********************************\
* 函数功能：使能Y轴相对运动控制
\**********************************/
void enablerelative_Y(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 1, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 1, data0[0] | 0x4000);
		if (1 == rc) {
			//printf("使能Y轴相对运动\n");
		}
	}
}


/**********************************\
* 函数功能：使能X轴绝对运动控制
\**********************************/
void enableabsolute_X(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 19, data0[0] | 0x0004);
		if (1 == rc) {
			//printf("使能X轴绝对运动\n");
		}
	}
}





/**********************************\
* 函数功能：使能Y轴绝对运动控制
\**********************************/
void enableabsolute_Y(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 1, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 1, data0[0] | 0x0004);
		if (1 == rc) {
			//printf("使能Y轴绝对运动\n");
		}
	}
}


/**********************************\
* 函数功能：判断X轴相对运动完成
\**********************************/
int isrelativeActionDone_X(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if ((1 == rc) && (0x0001 == (data0[0] & 0x0001))) {
		//printf("X轴相对运动完成\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能：判断Y轴相对运动完成
\**********************************/
int isrelativeActionDone_Y(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 1, 1, data0);
	if ((1 == rc) && (0x0010 == (data0[0] & 0x0010))) {
		//printf("Y轴相对运动完成\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能：判断X轴绝对运动完成
\**********************************/
int isabsoluteActionDone_X(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if ((1 == rc) && (0x0008 == (data0[0] & 0x0008))) {
		//printf("X轴绝对运动完成\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能：判断Y轴绝对运动完成
\**********************************/
int isabsoluteActionDone_Y(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if ((1 == rc) && (0x0010 == (data0[0] & 0x0010))) {
		//printf("Y轴绝对运动完成\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能：X轴相对运动完成位置0
\**********************************/
void setrelativeActionDone_XT0(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 19, data0[0] & 0xfffe);
		//printf("X轴相对运动完成位置0\n");
	}
}


/**********************************\
* 函数功能：Y轴相对运动完成位置0
\**********************************/
void setrelativeActionDone_YT0(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 1, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 1, data0[0] & 0xffef);
		//printf("Y轴相对运动完成置位0\n");
	}
}


/**********************************\
* 函数功能：X轴绝对运动完成位置0
\**********************************/
void setabsoluteActionDone_XT0(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 19, data0[0] & 0xfff7);
		//printf("X轴绝对运动完成位位置0\n");
	}
}


/**********************************\
* 函数功能：Y轴绝对运动完成位位置0
\**********************************/
void setabsoluteActionDone_YT0(modbus_t* ctx) {
	int rc;
	uint16_t data0[1] = { 0 };
	rc = modbus_read_registers(ctx, 19, 1, data0);
	if (1 == rc) {
		rc = modbus_write_register(ctx, 19, data0[0] & 0xffef);
		//printf("Y轴绝对运动完成位置0\n");
	}
}


int MoveRel_X(EQUIP_HANDLE hdl, float dx, float vx) {
	modbus_t* ctx = (modbus_t*)hdl;

	setrelativeDistance_X(dx, ctx);
	setrelativeVelocity_X(vx, ctx);
	enablerelative_X(ctx);
	setrelativeActionDone_XT0(ctx);

	while (1) {
		if (1 == isrelativeActionDone_X(ctx)) {
			return 1;
		}
	}
	return 0;
}


int MoveRel_Y(EQUIP_HANDLE hdl, float dy, float vy) {
	modbus_t* ctx = (modbus_t*)hdl;

	setrelativeDistance_Y(dy, ctx);
	setrelativeVelocity_Y(vy, ctx);
	enablerelative_Y(ctx);
	setrelativeActionDone_YT0(ctx);

	while (1) {
		if (1 == isrelativeActionDone_Y(ctx)) {
			return 1;
		}
	}
	return 0;
}


int MoveRel_XY(EQUIP_HANDLE hdl, float dx, float dy, float vx, float vy) {
	modbus_t* ctx = (modbus_t*)hdl;

	setrelativeDistance_X(dx, ctx);
	setrelativeDistance_Y(dy, ctx);

	setrelativeVelocity_X(vx, ctx);
	setrelativeVelocity_Y(vy, ctx);

	enablerelative_X(ctx);
	enablerelative_Y(ctx);

	setrelativeActionDone_XT0(ctx);
	setrelativeActionDone_YT0(ctx);

	while (1) {
		if ((1 == isrelativeActionDone_X(ctx)) &&
			(1 == isrelativeActionDone_Y(ctx))) {

			/*setrelativeActionDone_XT0(ctx);
			setrelativeActionDone_YT0(ctx);*/

			return 1;
		}
	}

	return 0;
}



int MoveAbs_X(EQUIP_HANDLE hdl, float px, float vx) {
	modbus_t* ctx = (modbus_t*)hdl;

	setabsolutePosition_X(px, ctx);
	setabsoluteVelocity_X(vx, ctx);
	enableabsolute_X(ctx);
	setabsoluteActionDone_XT0(ctx);

	while (1) {
		if (1 == isabsoluteActionDone_X(ctx)) {
			return 1;
		}
	}
	return 0;
}


int MoveAbs_Y(EQUIP_HANDLE hdl, float py, float vy) {
	modbus_t* ctx = (modbus_t*)hdl;

	setabsolutePosition_Y(py, ctx);
	setabsoluteVelocity_Y(vy, ctx);
	enableabsolute_Y(ctx);
	setabsoluteActionDone_YT0(ctx);

	while (1) {
		if (1 == isabsoluteActionDone_Y(ctx)) {
			return 1;
		}
	}
	return 0;
}


/**********************************\
* 函数功能：绝对运动设置
* 注：X轴的运动极限为2100mm
*     X轴的运动极限为3300mm
\**********************************/
int MoveAbs_XY(EQUIP_HANDLE hdl, float px, float py, float vx, float vy) {
	modbus_t* ctx = (modbus_t*)hdl;

	setabsolutePosition_X(px, ctx);
	setabsolutePosition_Y(py, ctx);

	setabsoluteVelocity_X(vx, ctx);
	setabsoluteVelocity_Y(vy, ctx);

	enableabsolute_X(ctx);
	enableabsolute_Y(ctx);

	setabsoluteActionDone_XT0(ctx);
	setabsoluteActionDone_YT0(ctx);

	while (1) {
		if ((1 == isabsoluteActionDone_X(ctx)) &&
			(1 == isabsoluteActionDone_Y(ctx))) {

			/*setabsoluteActionDone_XT0(ctx);
			setabsoluteActionDone_YT0(ctx);*/

			return 1;
		}
	}

	return 0;
}


void MoveRel_Z(EQUIP_HANDLE hdl, float dx, float dy,
	float vx, float vy, float start_X, float end_X,
	float start_Y, float end_Y, unsigned int Sleeptime) {
	while (1) {
		while (1) {
			MoveRel_X(hdl, dx, vx);
			Sleep(Sleeptime);
			//take photo
			Sleep(Sleeptime);
			float currPosi_X = GetX(hdl);
			if ((currPosi_X <= start_X) || (currPosi_X >= end_X)) {
				dx = -dx;
				break;
			}
		}
		MoveRel_Y(hdl, dy, vy);
		Sleep(2 * Sleeptime);
		float currPosi_Y = GetY(hdl);
		if ((currPosi_Y <= start_Y) || (currPosi_Y >= end_Y)) {
			break;
		}
	}
}


/**********************************\
* 函数功能: 测试函数：测试X轴相对运动的各个状态
\**********************************/
void testrelative_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx) {
	setrelativeDistance_X(relativeDistance_X, ctx);
	setrelativeVelocity_X(relativeVelocity_X, ctx);
	for (int i = 0; i < 3; ++i) {
		enablerelative_X(ctx);
		setrelativeActionDone_XT0(ctx);
		while (1) {
			if (1 == isrelativeActionDone_X(ctx)) {
				break;
			}
		}
		Sleep(3000);
	}
}


/**********************************\
* 函数功能: 测试函数：测试Y轴相对运动的各个状态
\**********************************/
void testrelative_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx) {
	setrelativeDistance_Y(relativeDistance_Y, ctx);
	setrelativeVelocity_Y(relativeVelocity_Y, ctx);
	for (int i = 0; i < 3; ++i) {
		enablerelative_Y(ctx);
		setrelativeActionDone_YT0(ctx);
		while (1) {
			if (1 == isrelativeActionDone_Y(ctx)) {
				break;
			}
		}
		Sleep(3000);
	}
}


/**********************************\
* 函数功能: 测试函数：测试X轴绝对运动的各个状态
\**********************************/
void testabsolute_X(float absoluteDistance_X, float absoluteVelocity_X, modbus_t* ctx) {
	setabsoluteVelocity_X(absoluteVelocity_X, ctx);
	for (int i = 0; i < 3; ++i) {
		setabsolutePosition_X(absoluteDistance_X, ctx);
		enableabsolute_X(ctx);
		while (1) {
			if (1 == isabsoluteActionDone_X(ctx)) {
				setabsoluteActionDone_XT0(ctx);
				break;
			}
		}
		Sleep(3000);
		absoluteDistance_X -= 100;
	}
}


/**********************************\
* 函数功能: 测试函数：测试Y轴绝对运动的各个状态
\**********************************/
void testabsolute_Y(float absoluteDistance_Y, float absoluteVelocity_Y, modbus_t* ctx) {
	setabsoluteVelocity_Y(absoluteVelocity_Y, ctx);
	for (int i = 0; i < 3; ++i) {
		setabsolutePosition_Y(absoluteDistance_Y, ctx);
		enableabsolute_Y(ctx);
		while (1) {
			if (1 == isabsoluteActionDone_Y(ctx)) {
				setabsoluteActionDone_YT0(ctx);
				break;
			}
		}
		Sleep(3000);
		absoluteDistance_Y += 100;
	}
}


/**********************************\
* 函数功能: 测试函数：测试sethalt_X暂停函数
\**********************************/
void testsethalt_X(float relativeDistance_X, float relativeVelocity_X, modbus_t* ctx) {
	setrelativeDistance_X(relativeDistance_X, ctx);
	setrelativeVelocity_X(relativeVelocity_X, ctx);
	enablerelative_X(ctx);

	Sleep(3000);
	HaltX(ctx);
	Sleep(3000);
	enablerelative_X(ctx);
}



/**********************************\
* 函数功能: 测试函数：测试sethalt_Y暂停函数
\**********************************/
void testsethalt_Y(float relativeDistance_Y, float relativeVelocity_Y, modbus_t* ctx) {
	setrelativeDistance_Y(relativeDistance_Y, ctx);
	setrelativeVelocity_Y(relativeVelocity_Y, ctx);
	enablerelative_Y(ctx);

	Sleep(3000);
	HaltY(ctx);
	Sleep(3000);
	enablerelative_Y(ctx);
}


///**********************************\
//* 函数功能：X轴立马停止
//\**********************************/
//void sethalt_X(modbus_t* ctx) {
//	int rc;
//	uint16_t data0[1] = { 0 };
//	rc = modbus_read_registers(ctx, 19, 1, data0);
//	if (1 == rc) {
//		rc = modbus_write_register(ctx, 19, data0[0] | 0x8000);
//		if (1 == rc) {
//			printf("X轴停止\n");
//		}
//	}
//}


/**********************************\
* 函数功能：X轴立马停止
\**********************************/
int HaltX(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	int rc, rb;
	uint16_t data0[1] = { 0 };
	rb = modbus_read_registers(ctx, 19, 1, data0);
	rc = modbus_write_register(ctx, 19, data0[0] | 0x8000);
	if ((1 == rb) && (1 == rc)) {
		//printf("X轴停止\n");
		return 1;
	}
	else
		return 0;
}


///**********************************\
//* 函数功能：Y轴立马停止
//\**********************************/
//void sethalt_Y(modbus_t* ctx) {
//	int rc;
//	uint16_t data0[1] = { 0 };
//	rc = modbus_read_registers(ctx, 1, 1, data0);
//	if (1 == rc) {
//		rc = modbus_write_register(ctx, 1, data0[0] | 0x2000);
//		if (1 == rc) {
//			printf("Y轴停止\n");
//		}
//	}
//}


/**********************************\
* 函数功能：Y轴立马停止
\**********************************/
int HaltY(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	int rc, rb;
	uint16_t data0[1] = { 0 };
	rb = modbus_read_registers(ctx, 1, 1, data0);
	rc = modbus_write_register(ctx, 1, data0[0] | 0x2000);
	if ((1 == rb) && (1 == rc)) {
		//printf("Y轴停止\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能: 测试函数：测试HaltX暂停函数
\**********************************/
void Test_HaltX(float relativeDistance_X, float relativeVelocity_X, EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	setrelativeDistance_X(relativeDistance_X, ctx);
	setrelativeVelocity_X(relativeVelocity_X, ctx);
	enablerelative_X(ctx);

	Sleep(3000);
	HaltX(ctx);
	Sleep(3000);
	enablerelative_X(ctx);
}



///**********************************\
//* 函数功能：获取当前X轴坐标
//\**********************************/
//float getLocation_X(modbus_t* ctx)
//{
//	int rc;
//	float Location_X = 0.0f;
//	uint16_t data[2] = { 0, 0 };
//	rc = modbus_read_registers(ctx, 29, 2, data);
//	//printf("%x\n%x\n", data[0], data[1]);
//	Location_X = modbus_get_float(data);
//	printf("当前X的坐标为%.1fmm\n", Location_X);
//	return Location_X;
//
//}


/**********************************\
* 函数功能：获取当前X轴坐标
\**********************************/
float GetX(EQUIP_HANDLE hdl) {	
	modbus_t* ctx = (modbus_t*)hdl;
	int rc;
	float Location_X = 0.0f;
	uint16_t data[2] = { 0, 0 };

	rc = modbus_read_registers(ctx, 29, 2, data);
	//printf("%x\n%x\n", data[0], data[1]);
	Location_X = modbus_get_float(data);
	if (Location_X == 0) {
		//printf("当前X的坐标为%.1fmm\n", Location_X);
		return Location_X;
	}
	else {
		//printf("当前X的坐标为%.1fmm\n", -1.0 * Location_X);
		return (-1.0 * Location_X);
	}
	
}


///**********************************\
//* 函数功能：获取当前Y轴坐标
//\**********************************/
//float getLocation_Y(modbus_t* ctx)
//{
//	int rc;
//	float Location_Y = 0.0f;
//	uint16_t data[2] = { 0, 0 };
//	rc = modbus_read_registers(ctx, 27, 2, data);
//	//printf("%x\n%x\n", data[0], data[1]);
//	Location_Y = modbus_get_float(data);
//	printf("当前Y的坐标为%.1fmm\n", Location_Y);
//	return Location_Y;
//
//}


/**********************************\
* 函数功能：获取当前Y轴坐标
\**********************************/
float GetY(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	int rc;
	float Location_Y = 0.0f;
	uint16_t data[2] = { 0, 0 };
	rc = modbus_read_registers(ctx, 27, 2, data);
	//printf("%x\n%x\n", data[0], data[1]);
	Location_Y = modbus_get_float(data);
	//printf("当前Y的坐标为%.1fmm\n", Location_Y);
	return Location_Y;
}


///**********************************\
//* 函数功能：打开串口并连接
//\**********************************/
//modbus_t* open_serial_port(char* portName, modbus_t* ctx) {
//	ctx = modbus_new_rtu(portName, 9600, 'N', 8, 1);
//	modbus_set_slave(ctx, 2);
//	int a = modbus_connect(ctx);
//	//printf("%x\n", ctx);
//	if (0 == a) {
//		printf("成功打开%s串口，并且连接到modbus从机\n", portName);
//	}
//	else
//		printf("未打开串口\n");
//
//	return ctx;
//}


/**********************************\
* 函数功能：打开串口并连接
\**********************************/
EQUIP_HANDLE OpenEquipment(char* portName)
{
	modbus_t* ctx;
	ctx = modbus_new_rtu(portName, 9600, 'N', 8, 1);
	modbus_set_slave(ctx, 2);
	int a = modbus_connect(ctx);
	//printf("%x\n", ctx);
	if (0 == a) {
		//printf("Open %s series port, and connect the modbus slaver\n", portName);
	}
	else{}
		//printf("can't open series port\n");

	return (void*)ctx;
}


/**********************************\
* 函数功能：获得modbus控制权
\**********************************/
int GetConModbus(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)(hdl);
	int rb, rc;
	uint16_t data0[1] = { 0 };
	rb = modbus_read_registers(ctx, 19, 1, data0);
	rc = modbus_write_register(ctx, 19, data0[0] & 0xfffd);
	if ((1 == rb) && (1 == rc)) {
		//printf("软件获得modbus控制权\n");
		return 1;
	}
	else
		return 0;
}


/**********************************\
* 函数功能：关闭串口和modbus连接
\**********************************/
void CloseEquipment(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	modbus_close(ctx);
	modbus_free(ctx);
	//printf("关闭串口和modbus连接\n");
}


///**********************************\
//* 函数功能：连续拍照
//\**********************************/
//void TakePhoto(int distance_per_X, int distance_total_X, modbus_t* ctx) {
//	for (int i = 0; i < distance_total_X / distance_per_X; ++i) {
//		int enableRelative_registers = 1;
//		uint16_t data0[1] = { 0 };
//		int rc = modbus_read_registers(ctx, 0x0001, enableRelative_registers, data0);
//		if (enableRelative_registers == rc) {
//			rc = modbus_write_register(ctx, 0x0001, data0[0] | 0x4000);
//			rc = modbus_write_register(ctx, 0x0001, data0[0] & 0xffef);
//			if (1 == rc) {
//				printf("成功将地址为0x0001的寄存器第2位(2.6)置1,使能运动\n");
//			}
//		}
//
//		while (1) {
//			uint16_t data1[1] = { 0 };
//			rc = modbus_read_registers(ctx, 0x0001, 1, data1);
//			if (0x0010 == (data1[0] & 0x0010))
//				Sleep(1000);  //暂停时间视情况而定，因为机械装置停了以后还不稳定
//							  //拍照
//			break;
//		}
//
//	}
//
//	while (1) {
//
//	}
//}


///**********************************\
//* 函数功能：X与Y轴回零操作
//\**********************************/
//void XT0_YT0(modbus_t* ctx) {
//	int rc;
//	uint16_t data[1] = { 0 };
//	rc = modbus_read_registers(ctx, 1, 1, data);
//	rc = modbus_write_register(ctx, 1, data[0] | 0x1000);
//	rc = modbus_write_register(ctx, 1, data[0] & 0xefff);
//
//	rc = modbus_read_registers(ctx, 19, 1, data);
//	rc = modbus_write_register(ctx, 19, data[0] | 0x0020);
//	rc = modbus_write_register(ctx, 19, data[0] & 0xffdf);
//
//	printf("立马回原点\n");
//}


/**********************************\
* 函数功能：X与Y轴回零操作
\**********************************/
int MoveToOrigin(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	int rx, ry;
	uint16_t data[1] = { 0 };
	rx = modbus_read_registers(ctx, 1, 1, data);
	rx = modbus_write_register(ctx, 1, data[0] | 0x1000);
	rx = modbus_write_register(ctx, 1, data[0] & 0xefff);

	ry = modbus_read_registers(ctx, 19, 1, data);
	ry = modbus_write_register(ctx, 19, data[0] | 0x0020);
	ry = modbus_write_register(ctx, 19, data[0] & 0xffdf);

	//printf("立马回原点\n");
	if ((1 == rx) && (1 == ry))
		return 1;
	else
		return 0;
}


///**********************************\
//* 函数功能：复位操作，所有寄存器清零
//\**********************************/
//void reset(modbus_t* ctx) {
//	int rc;
//	uint16_t data[100];
//	memset(data, 0, 100 * sizeof(uint16_t));
//	rc = modbus_write_registers(ctx, 0, 100, data);
//	if (100 == rc) {
//		printf("将所有寄存器归零\n");
//	}
//}


/**********************************\
* 函数功能：复位操作，所有寄存器清零
\**********************************/
int Reset(EQUIP_HANDLE hdl) {
	modbus_t* ctx = (modbus_t*)hdl;
	int rc;
	uint16_t data[100];
	memset(data, 0, 100 * sizeof(uint16_t));
	rc = modbus_write_registers(ctx, 0, 100, data);
	if (100 == rc) {
		//printf("将所有寄存器归零\n");
		return 1;
	}
	else
		return 0;
}
