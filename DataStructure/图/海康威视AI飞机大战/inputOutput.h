#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>

using namespace std;

struct Point2D
{
	int x;
	int y;
	Point2D() { }
	Point2D(int x, int y) :x(x), y(y) { }
};

struct Point3D
{
	int x;
	int y;
	int z;
	Point3D() { }
	Point3D(int x, int y, int z)
		:x(x), y(y), z(z) { }
};

struct BuildingArea
{
	Point2D startPos;

	int len;
	int width;
	int height;
	BuildingArea() {}
	BuildingArea(Point2D startPos,
		int len, int width, int height)
		:startPos(startPos), len(len), width(width), height(height){ }
};

struct FogArea
{
	Point2D startPos;

	int len;
	int width;
	int bHeight;
	int tHeight;
	FogArea() {}
	FogArea(Point2D startPos,
		int len, int width, int bHeight, int tHeight)
		:startPos(startPos),
		len(len), width(width), bHeight(bHeight), tHeight(tHeight){ }
};

struct GoodsInfo
{
	int no;
	Point2D startPos;
	Point2D endPos;
	int weight;
	int value;
	int startTime;
	int remainTime;
    int leftTime;
    int state;
    int toBeCarryUAVNo;
	GoodsInfo() { }
	GoodsInfo(int no, Point2D startPos, Point2D endPos,
        int weight, int value,
        int startTime, int remainTime, int leftTime, int state)
		:no(no), startPos(startPos), endPos(endPos),
		weight(weight), value(value),
        startTime(startTime), remainTime(remainTime),
        leftTime(leftTime), state(state)
    {
        toBeCarryUAVNo = -1;
    }
};

struct initUAV
{
	int no;
	Point3D startPos;
	int loadWeight;
	string type;
    int status;
	int goodsNo;
	initUAV() { }
	initUAV(int no, Point3D startPos, int loadWeight,
        string type, int status, int goodsNo)
		:no(no), startPos(startPos), loadWeight(loadWeight),
		type(type), status(status), goodsNo(goodsNo){ }
};

struct UAVCurInfo
{
	int no;
	Point3D curPos;
	int goodsNo;
	bool isArriveStart;
	bool isArriveEnd;
    int toCarrayGoodsNo;
    int loadWeight;
    string type;
    int status;
	UAVCurInfo() { }
	UAVCurInfo(int no, Point3D pos, int goodsNo, 
        int loadWeight, string type, int status)
        :no(no), curPos(pos), goodsNo(goodsNo),
          loadWeight(loadWeight), type(type), status(status)
    {
        isArriveStart = false;
        isArriveEnd = false;
        toCarrayGoodsNo = -1;
    }
};

struct UAVPrice
{
	string type;
	int loadWeight;
	int value;
	UAVPrice(){}
	UAVPrice(string type, int loadWeight, int value)
		:type(type), loadWeight(loadWeight), value(value) { }
};



struct UAVStatus
{
	int no;
	string type;
	Point3D curPos;
	int goodsNo;
    int status;
	UAVStatus() { }
	UAVStatus(int no, string type, Point3D pos,
        int goodsNo, int status)
		:no(no), type(type), curPos(pos),
		goodsNo(goodsNo), status(status) { }
};


struct MapInfo
{
	int xWidth;
	int yLength;
	int zHeight;

	Point2D parkingPos;

	int hLow;
	int hHigh;

	vector<BuildingArea> buildings;
	vector<FogArea> fogs;
	vector<initUAV> initUAVs;
	vector<UAVPrice> UAVprices;

	MapInfo(){ }
	MapInfo(int xWidth, int yLength, int zHeight,
		Point2D parkingPos, int hLow, int hHigh)
		:xWidth(xWidth), yLength(yLength), zHeight(zHeight),
		parkingPos(parkingPos), hLow(hLow), hHigh(hHigh){ }
};

ofstream outf("demo.json");

class InputOutput
{
public:
	void socketInit(const char *IP, const char *port)
	{
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock == -1)
			error_handling("socket() error");

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(IP);
		serv_addr.sin_port = htons(atoi(port));
		if (connect(sock, (struct sockaddr*)& serv_addr,
			sizeof(serv_addr)) == -1)
			error_handling("connect() error");
	}

#if 0
    Json::Value readSocket()
    {
        const int maxMessageLen = 1024 * 1024 * 4;
        char *message = (char*)malloc(maxMessageLen*sizeof(char));// new char[maxMessageLen];
        memset(message, 0, maxMessageLen*sizeof(char));
        int str_len = read(sock, message, maxMessageLen * sizeof(char));
        if (str_len == -1)
            error_handling("read() error");
        //printf("Message from server : %s \n", message);
        message += 8;
        Json::Reader reader;
        Json::Value input;
        reader.parse(message, input);
        message -= 8;
        //delete[] message;message = nullptr;
        if(message) {
            free(message);message = nullptr;
        }

        Json::FastWriter fwrite;
        Json::StyledWriter sw;
        //string ss = sw.write(input);
        outf << sw.write(input) << endl;
        cout << input;
        return input;
    }
#endif

    int OSRecv(int hSocket, char *pBuf, int nLen)
    {
        int nRet = 0;
        int nCount = 2;        /// 接受2次

        while (1)
        {
            struct timeval timeout = { 6, 0 };           ///< 接受数据超时设置为3秒

            // 减少应用计数
            nCount--;

            nRet = setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
            if (nRet != 0)
            {
                // 失败直接报错
                printf("setsockopt error no %d, strerror %s\n", errno, strerror(errno));
                return nRet;
            }

            nRet = recv(hSocket, pBuf, nLen, 0);
            if (nRet <= 0)
            {
                // 失败了，重新接收
                printf("recv error no %d, strerror %s\n", errno, strerror(errno));
                continue;
            }
            else
            {
                break;
            }
        }
        return nRet;
    }

    Json::Value readSocket()
    {
        const int MAX_SOCKET_BUFFER = 1024 * 1024 * 4;
        const int SOCKET_HEAD_LEN = 8;

        char *pRecvBuffer = (char*)malloc(MAX_SOCKET_BUFFER*sizeof(char));// new char[maxMessageLen];
        memset(pRecvBuffer, 0, MAX_SOCKET_BUFFER*sizeof(char));

        int         nRecvLen = 0;
        int         nLen = 0;

        while (1)
        {
            // 接受头部长度
            nLen = OSRecv(sock, pRecvBuffer + nRecvLen, MAX_SOCKET_BUFFER);
            if (nLen <= 0)
            {
                printf("recv error\n");
                return nLen;
            }

            nRecvLen += nLen;

            if (nRecvLen >= SOCKET_HEAD_LEN)
            {
                break;
            }
        }

        int         nJsonLen = 0;
        char        szLen[10] = { 0 };

        memcpy(szLen, pRecvBuffer, SOCKET_HEAD_LEN);

        nJsonLen = atoi(szLen);

        while (nRecvLen < (SOCKET_HEAD_LEN + nJsonLen))
        {
            // 说明数据还没接受完
            nLen = OSRecv(sock, pRecvBuffer + nRecvLen, MAX_SOCKET_BUFFER);
            if (nLen <= 0)
            {
                printf("recv error\n");
                return nLen;
            }

            nRecvLen += nLen;
        }

        Json::Reader reader;
        Json::Value input;
        pRecvBuffer += 8;
        reader.parse(pRecvBuffer, input);
        pRecvBuffer -= 8;
        if(pRecvBuffer) {
            free(pRecvBuffer);pRecvBuffer = nullptr;
        }

        Json::FastWriter fwrite;
        Json::StyledWriter sw;
        //string ss = sw.write(input);
        outf << sw.write(input) << endl;
        cout << input;
        return input;
    }

	int writeSocket(Json::Value wr)
	{
		Json::FastWriter fast;
        string sendStr = fast.write(wr);
        sendStr.pop_back();
        string sendStrLen = to_string(sendStr.size());
		int makeNZeroes = 8 - sendStrLen.size();
		string headStr(makeNZeroes, '0');
		string realSendStr = headStr + sendStrLen + sendStr;
        cout << "sendStr:" << realSendStr << endl;
        outf << realSendStr << endl;
        int str_len = write(sock, realSendStr.c_str(), realSendStr.size());
		return str_len;
	}

	void error_handling(char *message)
	{
		fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
	}

	void socketClose() { close(sock); }

private:
	int sock;
	struct sockaddr_in serv_addr;
};

#endif // INPUTOUTPUT_H
