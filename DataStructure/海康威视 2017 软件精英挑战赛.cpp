#include<vector>
#include<iostream>
#include<map>
#include<fstream>
#include<queue>
#include<algorithm>
#include<functional>
#include<unordered_map>

using namespace std;
int nextStep[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

struct parkingCarMess
{
	int carID;
	int entrantRobotID;
	int entrantTime;
	vector<pair<int, int>> entrantPath;

	int exitRobotID;
	int exitTime;
	vector<pair<int, int>> exitPath;

	parkingCarMess(int carID, int entrantRobotID) :carID(carID), entrantRobotID(entrantRobotID)
	{

	}


};

struct parkLocation
{
	pair<int, int>index;
	int sumLength;
	int length2Entrance;//距离入口距离
	int canServiceTime;
	bool isParking;//表示正在停车中
	parkLocation(int x, int y) :index(x, y), canServiceTime(0), sumLength(10000)
	{
		isParking = false;
	}
};
class CCar
{
public:
	CCar(){
	};
	~CCar(){};

public:
	int m_nIndex;
	int m_nApplyInTime;
	int m_nApplyOutTime;
	int m_nMaxWaitTIme;
	int m_nWeight;

	parkLocation*m_nParkLocation;// 该辆车的停车位
};
struct Robot
{
	int id;
	pair<int, int>curLocate;
	int curTime;
	CCar* serviceCar;

	Robot(int a, int b, int x, int y) :id(a), curTime(b), serviceCar(NULL), curLocate(x, y)
	{
	}

};
class CGrargeMap
{
public:
	CGrargeMap(){};
	~CGrargeMap();

	bool isValidMap();
	bool BFS(int x, int y);  //广度优先搜索，返回是否满足要求
	bool isValidParkLocation(int x, int y); //判断一个车位是不是有且仅有一个出口

	void BFS_Common(int x, int y);  //对某个通道点进行广度优先搜索
	void CreateParkLocation();  //根据判断图是否合法的两次广搜，创建停车位
	void CalcLength_BetweenParkLocation();//根据停车位路径计算停车位之间的最短路径
	vector<pair<int, int>> CalcParklocation(int x, int y);//计算一个通道点周围的停车位
	pair<int, int> getXIndex(int x, int y);//对于一个停车位，寻找它相邻的一个通道节点

	void Initialize();
public:

	int m_nRow;
	int m_nColumn;
	int m_parkLocationNum;
	int m_nExist2EntranceLength;  //保存出口到入口的距离
	int m_EntranceX, m_EntranceY, m_ExistX, m_ExistY; //出入口坐标

	int maxLenth2Entrance = 0;  //停车位距离入口的最大距离
	int minSumLength = 100000;   //停车位到出入口距离的最小和
	int minLength2Exit = 0;  //停车位距离出口的最小距离

	//vector<parkLocation*>m_srcParkLocationList;//原始停车位信息
	vector<parkLocation*>m_SortBySumLengthParkList;//根据到出入口距离和进行排序

	char m_cGarageMap[100][100];

	//priority_queue<parkLocation, vector<parkLocation>, greater<parkLocation>>m_nParkLocatinList;

	map<pair<int, int>, vector<pair<int, int>>> m_Entrance2ParkLocationPath;
	map<pair<int, int>, vector<pair<int, int>>> m_Exit2ParkLocationPath;

	map<pair<pair<int, int>, pair<int, int>>, int> pathTable;//存储两个停车位之间的最短路径长度
};

class parkLocationDistruteTool
{
public:
	vector<parkLocation*> curParkLocationList;  //按照到出入距离大小排序
public:
	parkLocationDistruteTool(){};
	~parkLocationDistruteTool(){};
	void Add(parkLocation*aParkLocaiton);
	void Delete(parkLocation*aParkLocaiton);
private:

};

void parkLocationDistruteTool::Add(parkLocation*aParkLocaiton)
{
	int curSumLength = aParkLocaiton->sumLength;
	parkLocation*tmp = aParkLocaiton;
	curParkLocationList.push_back(tmp);
	if (curParkLocationList.size() == 1)
		return;
	int p = curParkLocationList.size() - 2;
	while (p >= 0 && curParkLocationList[p]->sumLength>curSumLength)
	{
		curParkLocationList[p + 1] = curParkLocationList[p];
		p--;
	}
	p++;
	curParkLocationList[p] = aParkLocaiton;
}
void parkLocationDistruteTool::Delete(parkLocation *aParkLocaiton)
{
	if (curParkLocationList.size() == 1)
	{
		curParkLocationList.pop_back();
		return;
	}

	int p = 0;
	while (curParkLocationList[p] != aParkLocaiton)
	{
		p++;
	}

	p++;
	while (p<curParkLocationList.size())
	{
		curParkLocationList[p - 1] = curParkLocationList[p];
		p++;
	}

	curParkLocationList.pop_back();


}


CGrargeMap::~CGrargeMap()
{
	for (int i = 0; i < m_SortBySumLengthParkList.size(); i++)
	{
		delete m_SortBySumLengthParkList[i];
		m_SortBySumLengthParkList[i] = NULL;
	}
	m_SortBySumLengthParkList.clear();
	m_Entrance2ParkLocationPath.clear();
	m_Exit2ParkLocationPath.clear();
	pathTable.clear();
}

void CGrargeMap::Initialize()
{
	for (int i = 0; i < m_SortBySumLengthParkList.size(); i++)
	{
		m_SortBySumLengthParkList[i]->canServiceTime = 0;
		m_SortBySumLengthParkList[i]->isParking = false;
	}
}

bool CGrargeMap::isValidMap()
{
	//判断是否有出入口
	if (m_EntranceX < 0 || m_ExistX<0)
		return false;
	//判断出入口是否重合
	if (m_EntranceX == m_ExistX&&m_EntranceY == m_ExistY)
		return false;
	//判断出入口是否在边缘
	if (m_EntranceX != 0 && m_EntranceX != m_nRow - 1 && m_EntranceY != 0 && m_EntranceY != m_nColumn - 1)
		return false;
	if (m_ExistX != 0 && m_ExistX != m_nRow - 1 && m_ExistY != 0 && m_ExistY != m_nColumn - 1)
		return false;

	return BFS(m_EntranceX, m_EntranceY) && BFS(m_ExistX, m_ExistY);  //广度优先搜索，判断从出入口是否能到达所有停车位


}
bool CGrargeMap::BFS(int x, int y)
{
	bool **check = new bool *[m_nRow];
	for (int i = 0; i < m_nRow; i++)
	{
		check[i] = new bool[m_nColumn];
		for (int j = 0; j < m_nColumn; j++)
			check[i][j] = false;
	}
	int curParkLocationNum = 0;

	queue<pair<pair<int, int>, vector<pair<int, int>>>> que;


	//先把出入口设置为过道标志，便于广度遍历
	m_cGarageMap[m_EntranceX][m_EntranceY] = 'X';
	m_cGarageMap[m_ExistX][m_ExistY] = 'X';


	pair<int, int> srcIndex(x, y);
	vector<pair<int, int>> path;
	path.push_back(srcIndex);
	pair<pair<int, int>, vector<pair<int, int>>> root(srcIndex, path);
	que.push(root);
	check[x][y] = true;

	while (!que.empty())
	{
		pair<pair<int, int>, vector<pair<int, int>>> curCoord = que.front();
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int xx = curCoord.first.first + nextStep[i][0];
			int yy = curCoord.first.second + nextStep[i][1];
			pair<int, int>nextIndex(xx, yy);
			vector<pair<int, int>>tmpPath = curCoord.second;

			if (xx >= 0 && xx < m_nRow&&yy >= 0 && yy < m_nColumn&&m_cGarageMap[xx][yy] != 'B'&&!check[xx][yy])
			{
				check[xx][yy] = true;
				if (m_cGarageMap[xx][yy] == 'X')  //如果是过道
				{
					tmpPath.push_back(nextIndex);
					pair<pair<int, int>, vector<pair<int, int>>> nextCoord(nextIndex, tmpPath);
					que.push(nextCoord);

					//判断是不是出口或入口，保存路径长度
					if (xx == m_EntranceX&&yy == m_EntranceY)
					{
						m_nExist2EntranceLength = tmpPath.size();
					}
					else if (xx == m_ExistX&&yy == m_ExistY)
					{
						m_nExist2EntranceLength = tmpPath.size();
					}

				}
				else if (m_cGarageMap[xx][yy] == 'P')   //如果是停车位
				{
					curParkLocationNum++;
					if (!isValidParkLocation(xx, yy))  //判断这个车位是不是只有一个出口
					{
						//该车位不只有一个出口，返回false
						for (int j = 0; j < m_nRow; j++)
						{
							delete[]check[j];
							check[j] = NULL;
						}
						delete[]check;
						check = NULL;

						return false;
					}
					if (x == m_EntranceX&&y == m_EntranceY)
					{
						//保存入口到该车位的全路径
						tmpPath.push_back(nextIndex);
						m_Entrance2ParkLocationPath[nextIndex] = tmpPath;
					}

					if (x == m_ExistX &&y == m_ExistY)
					{
						//保存出口到该车位的全路径
						tmpPath.push_back(nextIndex);
						m_Exit2ParkLocationPath[nextIndex] = tmpPath;
					}
				}
			}
		}
	}
	//还原出入口标志
	m_cGarageMap[m_EntranceX][m_EntranceY] = 'I';
	m_cGarageMap[m_ExistX][m_ExistY] = 'E';

	for (int j = 0; j < m_nRow; j++)
	{
		delete[] check[j];
		check[j] = NULL;
	}
	delete[] check;
	check = NULL;

	return curParkLocationNum == m_parkLocationNum; //如果能到达的停车位数量等于停车位总数，那么是符合要求的
}

pair<int, int> CGrargeMap::getXIndex(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int xx = x + nextStep[i][0];
		int yy = y + nextStep[i][1];
		if (xx >= 0 && xx < m_nRow&&yy >= 0 && yy < m_nColumn)
		{
			if (m_cGarageMap[xx][yy] == 'X' || m_cGarageMap[xx][yy] == 'I' || m_cGarageMap[xx][yy] == 'E')
			{
				pair<int, int> result(xx, yy);
				return result;
			}
		}
	}
}
void CGrargeMap::BFS_Common(int x, int y)
{
	bool **check = new bool *[m_nRow];
	for (int i = 0; i < m_nRow; i++)
	{
		check[i] = new bool[m_nColumn];
		for (int j = 0; j < m_nColumn; j++)
			check[i][j] = false;
	}

	vector<pair<int, int>> realSrc = CalcParklocation(x, y);

	pair<int, int> srcLocation(x, y);

	queue<pair<pair<int, int>, int>> que;
	pair<pair<int, int>, int> root(srcLocation, 2);
	que.push(root);

	check[srcLocation.first][srcLocation.second] = true;
	check[x][y] = true;

	for (int j = 0; j < realSrc.size(); j++)
	{
		check[realSrc[j].first][realSrc[j].second] = true;
	}
	while (!que.empty())
	{
		pair<pair<int, int>, int> cur = que.front();
		pair<int, int> curIndex = cur.first;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int xx = curIndex.first + nextStep[i][0];
			int yy = curIndex.second + nextStep[i][1];

			pair<int, int> nextIndex(xx, yy);

			if (xx >= 0 && xx < m_nRow&&yy >= 0 && yy < m_nColumn&&m_cGarageMap[xx][yy] != 'B'&&!check[xx][yy])
			{
				check[xx][yy] = true;
				if (m_cGarageMap[xx][yy] == 'P')
				{
					for (int j = 0; j < realSrc.size(); j++)
					{
						pathTable[pair<pair<int, int>, pair<int, int>>(realSrc[j], nextIndex)] = cur.second + 1;
						pathTable[pair<pair<int, int>, pair<int, int>>(nextIndex, realSrc[j])] = cur.second + 1;

					}
				}
				else
				{
					pair<pair<int, int>, int> nextOne(nextIndex, cur.second + 1);
					que.push(nextOne);
				}

			}
		}

	}
	for (int j = 0; j < m_nRow; j++)
	{
		delete[] check[j];
		check[j] = NULL;
	}
	delete[] check;
	check = NULL;
}

bool CGrargeMap::isValidParkLocation(int x, int y)
{
	int num = 0;
	for (int i = 0; i < 4; i++)
	{
		int xx = x + nextStep[i][0];
		int yy = y + nextStep[i][1];
		if (xx >= 0 && xx < m_nRow&&yy >= 0 && yy < m_nColumn &&
			(m_cGarageMap[xx][yy] == 'I' || m_cGarageMap[xx][yy] == 'E' || m_cGarageMap[xx][yy] == 'X'))
		{
			num++;
		}
	}
	return num == 1;
}
bool CompareByInLength(parkLocation*a, parkLocation*b)
{
	if (a->length2Entrance == b->length2Entrance)
		return a->index < b->index;
	return a->length2Entrance < b->length2Entrance;
}
bool CompareBySumLength(parkLocation*a, parkLocation*b)
{
	if (a->sumLength == b->sumLength)
		return a->index < b->index;
	return a->sumLength < b->sumLength;
}
void CGrargeMap::CreateParkLocation()
{
	map<pair<int, int>, vector<pair<int, int>>>::iterator it = m_Entrance2ParkLocationPath.begin();
	while (it != m_Entrance2ParkLocationPath.end())
	{
		parkLocation*cur = new parkLocation(it->first.first, it->first.second);
		cur->length2Entrance = it->second.size();
		cur->sumLength = m_Exit2ParkLocationPath[cur->index].size() + m_Entrance2ParkLocationPath[cur->index].size();

		maxLenth2Entrance = max(maxLenth2Entrance, cur->length2Entrance);
		minSumLength = min(minSumLength, cur->sumLength);
		minLength2Exit = min(minLength2Exit, (int)m_Exit2ParkLocationPath[cur->index].size());
		it++;

		m_SortBySumLengthParkList.push_back(cur);
	}
	//sort(m_srcParkLocationList.begin(), m_srcParkLocationList.end(), CompareByInLength);
	sort(m_SortBySumLengthParkList.begin(), m_SortBySumLengthParkList.end(), CompareBySumLength);
}

//从一个通道坐标计算它相邻的停车位坐标
vector<pair<int, int>> CGrargeMap::CalcParklocation(int x, int y)
{
	vector<pair<int, int>> result;
	for (int i = 0; i < 4; i++)
	{
		int xx = x + nextStep[i][0];
		int yy = y + nextStep[i][1];

		if (xx >= 0 && xx < m_nRow&&yy >= 0 && yy < m_nColumn&&m_cGarageMap[xx][yy] == 'P')
		{
			pair<int, int>temp(xx, yy);
			result.push_back(temp);
		}
	}

	return result;

}

void CGrargeMap::CalcLength_BetweenParkLocation()
{
	map<pair<int, int>, vector<pair<int, int>>>::iterator it = m_Entrance2ParkLocationPath.begin();

	for (; it != m_Entrance2ParkLocationPath.end(); it++)
	{
		vector<pair<int, int>> tmpPath = it->second;   //一条从入口到一个停车位的最短路径

		for (int i = 0; i < tmpPath.size() - 1; i++)
		{
			int curx = tmpPath[i].first;
			int cury = tmpPath[i].second;
			vector<pair<int, int>> parkLocations = CalcParklocation(curx, cury);
			if (parkLocations.empty())continue;

			for (int j = 0; j < parkLocations.size(); j++)
			{
				pair<int, int>aParkLocation = parkLocations[j];
				if (aParkLocation == it->first)continue;
				pathTable[pair<pair<int, int>, pair<int, int>>(it->first, aParkLocation)] = tmpPath.size() - i + 1;
				pathTable[pair<pair<int, int>, pair<int, int>>(aParkLocation, it->first)] = tmpPath.size() - i + 1;
			}
		}
	}

	it = m_Exit2ParkLocationPath.begin();
	for (; it != m_Exit2ParkLocationPath.end(); it++)
	{
		vector<pair<int, int>> tmpPath = it->second;   //一条从入口到一个停车位的最短路径

		for (int i = 0; i < tmpPath.size() - 2; i++)
		{
			int curx = tmpPath[i].first;
			int cury = tmpPath[i].second;
			vector<pair<int, int>> parkLocations = CalcParklocation(curx, cury);
			if (parkLocations.empty())continue;

			for (int j = 0; j < parkLocations.size(); j++)
			{
				pair<int, int> aParkLocation = parkLocations[j];
				if (aParkLocation == it->first)continue;
				pathTable[pair<pair<int, int>, pair<int, int>>(it->first, aParkLocation)] = tmpPath.size() - i + 1;
				pathTable[pair<pair<int, int>, pair<int, int>>(aParkLocation, it->first)] = tmpPath.size() - i + 1;
			}
		}
	}



}

struct Cmp
{
	bool operator()(CCar* const a, CCar* const b)
	{
		if (a->m_nApplyOutTime == b->m_nApplyOutTime)
			return a->m_nIndex < b->m_nIndex;
		return a->m_nApplyOutTime > b->m_nApplyOutTime;
	}
};

int m_nK, m_nP, m_nA, m_nB, Z;
CGrargeMap m_cGarageMap;
int curParkingCarNum = 0;
int minZ = 0;
int m_AbandanByNoArr = 0;//因为机器人不能等待时间接待二放弃的车辆数
int m_AbandanByFull = 0; //因为车库已满放弃的车辆
int m_nT1 = 0, m_nW = 0, m_nQ = 0, m_nRobotNum = 30;
int m_nCarNum = 0;
int index2Distribute = 0;
int m_EntranceWaitTime = 0;
vector<CCar*> m_nCars;
map<int, parkingCarMess*> m_nParkingResult;

parkLocationDistruteTool parkLocationTool;   //停车位分配工具

vector<CCar*> newCarList;

//对车辆根据质量递减排序
bool SortCarByWeight(CCar*a, CCar*b)
{
	if (a->m_nWeight == b->m_nWeight)
		return a->m_nIndex < b->m_nIndex;
	return a->m_nWeight>b->m_nWeight;
}
void WriteLeaveHis(CCar*curCar, int RobotID, int waitTime)
{
	m_nParkingResult[curCar->m_nIndex]->exitPath = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkLocation->index];
	m_nParkingResult[curCar->m_nIndex]->exitRobotID = RobotID;
	m_nParkingResult[curCar->m_nIndex]->exitTime = curCar->m_nApplyOutTime + waitTime;
}
void WriteEntrantHis(CCar*curCar, int RobotID, int waitTime)
{
	parkingCarMess *newHis = new parkingCarMess(curCar->m_nIndex, RobotID);
	newHis->entrantPath = m_cGarageMap.m_Entrance2ParkLocationPath[curCar->m_nParkLocation->index];
	newHis->entrantTime = waitTime + curCar->m_nApplyInTime;
	m_nParkingResult[curCar->m_nIndex] = newHis;
}
//选择要把车运进车库的机器人,返回的是被选中的机器人到入口接车时，车辆的等待时间，小于0的话，表示车还未到，机器人已经在入口等待时间
int ChooseEntrantRobot(CCar*curCar, vector<Robot*>&RobotList, int&chooseIndex)
{
	//Robot* chooseRobot = NULL;
	int minV = 100000000;

	pair<int, int> entrancePoint(m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
	pair<int, int> exitPoint(m_cGarageMap.m_ExistX, m_cGarageMap.m_ExistY);

	for (int i = 0; i < RobotList.size(); i++)
	{
		int tmpTime = 0;
		if (RobotList[i]->curLocate == entrancePoint)
		{
			//如果该机器人在入口，直接作为返回结果
			chooseIndex = i;
			return  0;
		}
		else if (RobotList[i]->curLocate == exitPoint)
		{
			//如果该机器人在出口
			int withoutTime = curCar->m_nApplyInTime - RobotList[i]->curTime; //表示该机器人在汽车还未到来前的时间
			tmpTime = m_cGarageMap.m_nExist2EntranceLength - 1 - withoutTime;  //表示该机器人去接该车辆的话，比车辆到达出口的时间晚多少
			//该值有可能是负值，负值表示机器人提前车辆多长时间到达

			if (tmpTime <= 0 && (tmpTime>minV || minV>0))
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
			else if (tmpTime > 0 && tmpTime < minV)
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
		}
		else
		{
			//机器人在某个车位上
			int withoutTime = curCar->m_nApplyInTime - RobotList[i]->curTime;
			//计算该机器人从它所在的车位出发到入口去接车辆需要花费的时间比该车辆到达出口要晚多少
			tmpTime = m_cGarageMap.m_Entrance2ParkLocationPath[RobotList[i]->curLocate].size() - 1 - withoutTime;

			if (tmpTime <= 0 && (tmpTime>minV || minV>0))
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
			else if (tmpTime > 0 && tmpTime < minV)
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
		}
	}
	if (minV>curCar->m_nMaxWaitTIme)
	{
		chooseIndex = -1;
	}
	if (minV < 0)minV = 0;
	return minV;
}

//选择要把车运出车库的机器人,返回的是被选中的机器人到停车位接车时，车辆的等待时间，小于0的话，表示车还未到，机器人已经在入口等待时间
int ChooseLeaveRobot(CCar *curCar, vector<Robot*> &RobotList, int &chooseIndex)
{
	//Robot* chooseRobot = NULL;
	int minV = 100000000;
	//用于存储该汽车申请出库后需要等待的时间，有可能为负值，负值表示汽车还未申请出库，机器人已在该停车位等候
	//int sendTime = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkingIndex].size()-1;
	pair<int, int> entrancePoint(m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
	pair<int, int> exitPoint(m_cGarageMap.m_ExistX, m_cGarageMap.m_ExistY);
	int withoutTime, tmpTime;
	for (int i = 0; i < RobotList.size(); i++)
	{
		if (RobotList[i]->curLocate == entrancePoint)
		{
			withoutTime = curCar->m_nApplyOutTime - RobotList[i]->curTime;
			tmpTime = m_cGarageMap.m_Entrance2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1 - withoutTime;

			if (tmpTime <= 0 && (tmpTime>minV || minV > 0))
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
			else if (tmpTime > 0 && tmpTime < minV)
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}

		}
		else if (RobotList[i]->curLocate == exitPoint)
		{
			withoutTime = curCar->m_nApplyOutTime - RobotList[i]->curTime;
			tmpTime = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1 - withoutTime;

			if (tmpTime <= 0 && (tmpTime>minV || minV > 0))
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
			else if (tmpTime > 0 && tmpTime < minV)
			{
				minV = tmpTime;
				chooseIndex = i;
				//chooseRobot = RobotList[i];
			}
		}
		else  //两个位置是两个停车位
		{
			pair<int, int> robotIndex = RobotList[i]->curLocate;
			pair<pair<int, int>, pair<int, int>> tmpLine(robotIndex, curCar->m_nParkLocation->index);
			if (m_cGarageMap.pathTable.count(tmpLine) == 0)  //如果找不到两个停车位之间的最短距离，那么先对汽车所在停车位进行广度优先搜索
			{
				pair<int, int>temp = m_cGarageMap.getXIndex(curCar->m_nParkLocation->index.first, curCar->m_nParkLocation->index.second);
				m_cGarageMap.BFS_Common(temp.first, temp.second);
			}
			withoutTime = curCar->m_nApplyOutTime - RobotList[i]->curTime;
			tmpTime = m_cGarageMap.pathTable[tmpLine] - 1 - withoutTime;

			if (tmpTime <= 0 && (minV > 0 || tmpTime > minV))
			{
				minV = tmpTime;
				chooseIndex = i;
			}
			else if (tmpTime > 0 && tmpTime < minV)
			{
				minV = tmpTime;
				chooseIndex = i;
			}

		}
	}
	if (minV < 0)minV = 0;
	return minV;

}


//选择到出入口距离最小的停车位
parkLocation* ChooseMinSumLengthParkLocation(CCar *curCar, Robot *curRobot, int waitTime)
{
	for (int i = 0; i < m_cGarageMap.m_SortBySumLengthParkList.size(); i++)
	{
		if (m_cGarageMap.m_SortBySumLengthParkList[i]->isParking)
			continue;
		parkLocation*curParkLocation = m_cGarageMap.m_SortBySumLengthParkList[i];
		int arriveTime = curCar->m_nApplyInTime + waitTime + m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
		if (arriveTime >= curParkLocation->canServiceTime)
			return curParkLocation;
	}
	return NULL;
}
void HandleIn(CCar *curCar, vector<Robot*> &m_nRobots, priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{
	//处理入库
	int chooseIndex;
	int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
	if (chooseIndex < 0)  //因为机器人不可达放弃停车
	{
		m_AbandanByNoArr++;
		m_nQ++;
		return;
	}



	parkLocation*chooseParkLocation = ChooseMinSumLengthParkLocation(curCar, m_nRobots[chooseIndex], waitTime);


	if (chooseParkLocation == NULL)  //因为停车位不够导致不可达
	{
		m_AbandanByFull++;
		m_nQ++;
		return;
	}
	else
	{
		int inLength = m_cGarageMap.m_Entrance2ParkLocationPath[chooseParkLocation->index].size() - 1;
		int outLength = m_cGarageMap.m_Exit2ParkLocationPath[chooseParkLocation->index].size() - 1;

		int totalWaste = 0;
		totalWaste += (waitTime + outLength)*m_nB;   //加入等待时间
		totalWaste += (inLength + outLength)*m_nK*curCar->m_nWeight;  //加入能耗
		if (totalWaste >= m_nP)
		{
			m_AbandanByFull++;
			m_nQ++;
			return;
		}

		newCarList.push_back(curCar);


		m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

		m_nRobots[chooseIndex]->curLocate = chooseParkLocation->index;

		chooseParkLocation->isParking = true;
		curCar->m_nParkLocation = chooseParkLocation;


		m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + inLength;
		WriteEntrantHis(curCar, chooseIndex, waitTime);
		m_nWaitLeaveCar.push(curCar);

		curParkingCarNum++;
		m_nT1 += waitTime;
		m_nW += m_nK*curCar->m_nWeight*inLength;
	}
}

void HandleOut(CCar *curCar, vector<Robot*> &m_nRobots, priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{
	//处理出库
	//旧方法
	int chooseIndex;
	m_nWaitLeaveCar.pop();
	int waitTime = ChooseLeaveRobot(curCar, m_nRobots, chooseIndex);
	int outLength = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1;

	m_nRobots[chooseIndex]->curLocate = pair<int, int>(m_cGarageMap.m_ExistX, m_cGarageMap.m_ExistY);
	m_nRobots[chooseIndex]->curTime = curCar->m_nApplyOutTime + waitTime + outLength;
	WriteLeaveHis(curCar, chooseIndex, waitTime);
	curCar->m_nParkLocation->canServiceTime = curCar->m_nApplyOutTime + waitTime + 1;
	curCar->m_nParkLocation->isParking = false;

	m_nT1 += waitTime + outLength;
	m_nW += m_nK*curCar->m_nWeight*outLength;


	/*
	int chooseIndex;
	m_nWaitLeaveCar.pop();
	int waitTime = ChooseLeaveRobot(curCar, m_nRobots, chooseIndex);
	int outLength = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1;

	m_nRobots[chooseIndex]->curLocate = pair<int, int>(m_cGarageMap.m_ExistX, m_cGarageMap.m_ExistY);
	m_nRobots[chooseIndex]->curTime = curCar->m_nApplyOutTime + waitTime + outLength;
	WriteLeaveHis(curCar, chooseIndex, waitTime);
	curCar->m_nParkLocation->canServiceTime = curCar->m_nApplyOutTime + waitTime + 1;
	curCar->m_nParkLocation->isParking = false;

	m_DistributeTool.AddParkLocation(curCar->m_nParkLocation);
	if (index2Distribute < m_nCarNum)
	{
	m_DistributeTool.AddCar(m_nCars[index2Distribute++]);
	}

	m_nT1 += waitTime + outLength;
	m_nW += m_nK*curCar->m_nWeight*outLength;
	*/



}

void HandleOutTest(CCar *curCar, vector<Robot*> &m_nRobots, 
	priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{
	//处理出库
	//旧方法
	int chooseIndex;
	m_nWaitLeaveCar.pop();
	int waitTime = ChooseLeaveRobot(curCar, m_nRobots, chooseIndex);
	int outLength = m_cGarageMap.m_Exit2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1;

	m_nRobots[chooseIndex]->curLocate = pair<int, int>(m_cGarageMap.m_ExistX, m_cGarageMap.m_ExistY);
	m_nRobots[chooseIndex]->curTime = curCar->m_nApplyOutTime + waitTime + outLength;
	WriteLeaveHis(curCar, chooseIndex, waitTime);
	curCar->m_nParkLocation->canServiceTime = curCar->m_nApplyOutTime + waitTime + 1;
	curCar->m_nParkLocation->isParking = false;

	parkLocationTool.Add(curCar->m_nParkLocation);
	curParkingCarNum--;
	m_nT1 += waitTime + outLength;
	m_nW += m_nK*curCar->m_nWeight*outLength;
}

void Show()
{
	cout << "YES" << "\n";
	cout << m_nRobotNum << " " << m_nT1*m_nB + m_nP*m_nQ << " " << m_nW << "\n";
	for (int i = 1; i <= m_nCarNum; i++)
	{
		if (m_nParkingResult.count(i) == 0)
		{
			cout << i << " yes" << "\n";
			continue;
		}
		parkingCarMess*cur = m_nParkingResult[i];
		cout << i << " no " << cur->entrantRobotID << " " << cur->entrantTime;
		for (int j = 0; j < cur->entrantPath.size(); j++)
		{
			cout << " (" << cur->entrantPath[j].first << "," << cur->entrantPath[j].second << ")";
		}
		cout << " " << cur->exitRobotID << " " << cur->exitTime;
		for (int j = cur->exitPath.size() - 1; j >= 0; j--)
		{
			cout << " (" << cur->exitPath[j].first << "," << cur->exitPath[j].second << ")";
		}
		cout << "\n";
	}
}
bool compareCarsByInTime(CCar *a, CCar *b)
{
	if (a->m_nApplyInTime == b->m_nApplyInTime)
		return a->m_nIndex < b->m_nIndex;
	return a->m_nApplyInTime < b->m_nApplyInTime;
}
int ReadCaseInfo(char *szPath)
{
	if (szPath == NULL)
	{
		return 0;
	}
	FILE    *pFile = fopen(szPath, "r");

	if (pFile == NULL)
	{
		return 0;
	}

	fscanf(pFile, "%d %d %d %d",
		&m_nK,
		&m_nP,
		&m_nA,
		&m_nB);
	fscanf(pFile, "%d %d", &m_cGarageMap.m_nRow, &m_cGarageMap.m_nColumn);

	for (int i = 0; i < m_cGarageMap.m_nRow; i++)
	{
		for (int j = 0; j < m_cGarageMap.m_nColumn; j++)
		{
			char szTmp[2] = { 0 };
			fscanf(pFile, "%s", szTmp);
			m_cGarageMap.m_cGarageMap[i][j] = szTmp[0];

			if (szTmp[0] == 'I')
			{
				m_cGarageMap.m_EntranceX = i;
				m_cGarageMap.m_EntranceY = j;
			}
			if (szTmp[0] == 'E')
			{
				m_cGarageMap.m_ExistX = i;
				m_cGarageMap.m_ExistY = j;
			}
			if (szTmp[0] == 'P')
			{
				m_cGarageMap.m_parkLocationNum++;
				//保存该停车位
				//parkLocation*tmp = new parkLocation(i,j);
				//m_cGarageMap.m_nParkLocatinList.push(tmp);
			}

		}
	}

	// 读取车辆信息
	fscanf(pFile, "%d", &m_nCarNum);

	for (int i = 0; i < m_nCarNum; i++)
	{
		CCar* cCar = new CCar();
		fscanf(pFile, "%d %d %d %d %d",
			&cCar->m_nIndex,
			&cCar->m_nApplyInTime,
			&cCar->m_nApplyOutTime,
			&cCar->m_nMaxWaitTIme,
			&cCar->m_nWeight);
		m_nCars.push_back(cCar);
	}

	sort(m_nCars.begin(), m_nCars.end(), compareCarsByInTime);
	return 1;
}

//选择最合适的停车位
parkLocation* ChooseBestParkLocation(CCar*curCar, int waitTime, int range)
{
	/*
	for (int i = range; i < parkLocationTool.curParkLocationList.size(); i++)
	{
	parkLocation*curParkLocation = parkLocationTool.curParkLocationList[i];
	int arriveTime = curCar->m_nApplyInTime + waitTime + m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
	if (arriveTime >= curParkLocation->canServiceTime)
	{
	parkLocationTool.Delete(curParkLocation);
	return curParkLocation;
	}
	}

	for (int i = range-1; i>=0; i--)
	{
	parkLocation*curParkLocation = parkLocationTool.curParkLocationList[i];
	int arriveTime = curCar->m_nApplyInTime + waitTime + m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
	if (arriveTime >= curParkLocation->canServiceTime)
	{
	parkLocationTool.Delete(curParkLocation);
	return curParkLocation;
	}
	}
	*/
	parkLocation* curParkLocation = parkLocationTool.curParkLocationList[range];
	int arriveTime = curCar->m_nApplyInTime + waitTime + m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
	if (arriveTime >= curParkLocation->canServiceTime)
	{
		parkLocationTool.Delete(curParkLocation);
		return curParkLocation;
	}

	for (int i = 0; i < parkLocationTool.curParkLocationList.size(); i++)
	{
		if (i == range)
			continue;

		parkLocation *aParkLocation = parkLocationTool.curParkLocationList[i];
		int time = curCar->m_nApplyInTime + waitTime + m_cGarageMap.m_Entrance2ParkLocationPath[aParkLocation->index].size() - 1;
		if (time >= aParkLocation->canServiceTime)
		{
			parkLocationTool.Delete(aParkLocation);
			return aParkLocation;
		}
	}


	return NULL;



}

void HandleInTest(CCar *curCar, vector<Robot*> &m_nRobots, 
	priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar, int range)
{
	int chooseIndex;
	int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
	if (chooseIndex < 0)  //因为机器人不可达放弃停车
	{
		m_AbandanByNoArr++;
		m_nQ++;
		return;
	}
	parkLocation *chooseParkLocation = ChooseBestParkLocation(curCar, waitTime, range);


	if (chooseParkLocation == NULL)  //因为停车位不够导致不可达
	{
		m_AbandanByFull++;
		m_nQ++;
		return;
	}
	else
	{

		m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

		m_nRobots[chooseIndex]->curLocate = chooseParkLocation->index;

		chooseParkLocation->isParking = true;
		curCar->m_nParkLocation = chooseParkLocation;
		int inLength = m_cGarageMap.m_Entrance2ParkLocationPath[chooseParkLocation->index].size() - 1;

		m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + inLength;
		WriteEntrantHis(curCar, chooseIndex, waitTime);
		m_nWaitLeaveCar.push(curCar);

		curParkingCarNum++;
		m_nT1 += waitTime;
		m_nW += m_nK*curCar->m_nWeight*inLength;
	}
}

//批量处理入库的车辆
void HandleInGroup(vector<CCar*> curCarList, vector<Robot*> &m_nRobots, 
	priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{
	vector<CCar*> tempCarList = curCarList;
	sort(tempCarList.begin(), tempCarList.end(), SortCarByWeight); //对车辆根据质量降序排列

	vector<int> rangeList(curCarList.size(), 0);

	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];
		for (int j = 0; j < tempCarList.size(); j++)
		{
			if (tempCarList[j] == curCar)
			{
				rangeList[i] = j;
				break;
			}
		}
	}


	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];

		int num = 0, j = 0;

		for (; j < parkLocationTool.curParkLocationList.size(); j++)
		{
			if (num == rangeList[i])
				break;

			parkLocation *curParkLocation = parkLocationTool.curParkLocationList[j];
			int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
			if (InTime + curCar->m_nApplyInTime >= curParkLocation->canServiceTime)
				num++;
		}

		bool isHandle = false;
		int chooseIndex;
		int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
		if (chooseIndex < 0)  //因为机器人不可达放弃停车
		{
			m_AbandanByNoArr++;
			m_nQ++;
			continue;
		}

		for (int k = j; k < parkLocationTool.curParkLocationList.size(); k++)
		{
			if (isHandle)
				break;
			parkLocation *curParkLocation = parkLocationTool.curParkLocationList[k];
			int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
			if (InTime + curCar->m_nApplyInTime + waitTime < curParkLocation->canServiceTime)
				continue;

			isHandle = true;

			m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

			m_nRobots[chooseIndex]->curLocate = curParkLocation->index;

			curParkLocation->isParking = true;
			curCar->m_nParkLocation = curParkLocation;

			m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + InTime;
			WriteEntrantHis(curCar, chooseIndex, waitTime);
			m_nWaitLeaveCar.push(curCar);

			parkLocationTool.Delete(curParkLocation);

			curParkingCarNum++;
			m_nT1 += waitTime;
			m_nW += m_nK*curCar->m_nWeight*InTime;
		}
		if (!isHandle)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (isHandle)
					break;
				parkLocation *curParkLocation = parkLocationTool.curParkLocationList[k];
				int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
				if (InTime + curCar->m_nApplyInTime + waitTime < curParkLocation->canServiceTime)
					continue;

				isHandle = true;

				m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

				m_nRobots[chooseIndex]->curLocate = curParkLocation->index;

				curParkLocation->isParking = true;
				curCar->m_nParkLocation = curParkLocation;

				m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + InTime;
				WriteEntrantHis(curCar, chooseIndex, waitTime);
				m_nWaitLeaveCar.push(curCar);

				parkLocationTool.Delete(curParkLocation);

				curParkingCarNum++;
				m_nT1 += waitTime;
				m_nW += m_nK*curCar->m_nWeight*InTime;
			}
		}
		if (!isHandle)
		{
			m_AbandanByFull++;
			m_nQ++;
		}
	}

}

void MergeHandleIn(vector<CCar*> curCarList, vector<Robot*> &m_nRobots, 
	priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{

	vector<CCar*> tempCarList = curCarList;
	sort(tempCarList.begin(), tempCarList.end(), SortCarByWeight); //对车辆根据质量降序排列



	vector<int> rangeList(curCarList.size(), 0);

	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];
		for (int j = 0; j < tempCarList.size(); j++)
		{
			if (tempCarList[j] == curCar)
			{
				rangeList[i] = j;
				break;
			}
		}
	}


	map<CCar*, bool> distribution;

	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];

		int chooseIndex;
		int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
		if (chooseIndex < 0)  //因为机器人不可达放弃停车
		{
			continue;
		}







	}


	/*for (int i = 0; i < tempCarList.size(); i++)
	{
	CCar*curCar = tempCarList[i];
	curCar->m_nParkLocation = NULL;

	for (int j = 0; j < parkLocationTool.curParkLocationList.size(); j++)
	{
	parkLocation*curParkLocation = parkLocationTool.curParkLocationList[j];

	int inTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
	int outTime = m_cGarageMap.m_Exit2ParkLocationPath[curParkLocation->index].size() - 1;
	int waste = (inTime + outTime)*curCar->m_nWeight*m_nK + outTime*m_nB;
	if (waste>=m_nP)
	{
	break;
	}
	if (waste < m_nP&&(inTime+curCar->m_nApplyInTime)>=curParkLocation->canServiceTime)
	{
	curCar->m_nParkLocation = curParkLocation;
	parkLocationTool.Delete(curParkLocation);
	break;
	}
	}
	}

	for (int i = 0; i < curCarList.size(); i++)
	{
	CCar*curCar = curCarList[i];
	if (curCar->m_nParkLocation == NULL)
	{
	m_AbandanByFull++;
	m_nQ++;
	continue;
	}

	int chooseIndex;
	int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
	if (chooseIndex < 0)  //因为机器人不可达放弃停车
	{
	parkLocationTool.Add(curCar->m_nParkLocation);
	m_AbandanByNoArr++;
	m_nQ++;
	continue;
	}

	int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curCar->m_nParkLocation->index].size() - 1;
	if (InTime + curCar->m_nApplyInTime + waitTime >= curCar->m_nParkLocation->canServiceTime)
	{
	m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

	m_nRobots[chooseIndex]->curLocate = curCar->m_nParkLocation->index;

	curCar->m_nParkLocation->isParking = true;

	m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + InTime;
	WriteEntrantHis(curCar, chooseIndex, waitTime);
	m_nWaitLeaveCar.push(curCar);


	curParkingCarNum++;
	m_nT1 += waitTime;
	m_nW += m_nK*curCar->m_nWeight*InTime;
	}
	else
	{
	parkLocationTool.Add(curCar->m_nParkLocation);
	m_AbandanByNoArr++;
	m_nQ++;
	continue;
	}
	}
	*/









}


//带拒载的处理方法
void Calculation()
{
	priority_queue<CCar*, vector<CCar*>, Cmp> m_nWaitLeaveCar;//等待出库的车辆，根据出库时间排序
	vector<Robot*> m_nRobots;



	int curCarIndex = 0;
	curParkingCarNum = 0;

	for (int i = 0; i <m_nRobotNum; i++)  //创建机器人
	{
		Robot *aRobot = new Robot(i, 0, m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
		m_nRobots.push_back(aRobot);
	}

	//还有车没申请进库或者还有车没出库
	while (curCarIndex<m_nCars.size() || !m_nWaitLeaveCar.empty())
	{
		CCar *curEnterCar = NULL;
		CCar *curExitCar = NULL;
		if (curCarIndex < m_nCars.size())
		{
			curEnterCar = m_nCars[curCarIndex];
		}
		if (!m_nWaitLeaveCar.empty())
		{
			curExitCar = m_nWaitLeaveCar.top();
		}

		if (curEnterCar != NULL&&curExitCar != NULL)
		{


			//如果申请出库的时间早于申请入库时间，或者库已满，处理出库
			if (curExitCar->m_nApplyOutTime <curEnterCar->m_nApplyInTime || curParkingCarNum == m_cGarageMap.m_parkLocationNum)
			{
				HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
			}
			else
			{
				//处理入库
				curCarIndex++;
				HandleIn(curEnterCar, m_nRobots, m_nWaitLeaveCar);


			}
		}
		else if (curEnterCar != NULL)
		{
			//处理入库
			curCarIndex++;
			HandleIn(curEnterCar, m_nRobots, m_nWaitLeaveCar);
		}
		else
		{
			//处理出库
			HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
		}
	}
	for (int i = 0; i <m_nRobotNum; i++)  //创建机器人
	{
		delete m_nRobots[i];
		m_nRobots[i] = NULL;
	}
	m_nRobots.clear();
}

//计算从carIndex开始的同一批进库的汽车
vector<CCar*> getCarGroup(vector<CCar*> carList, int &carIndex, int minLeaveTime)
{
	vector<CCar*> result;
	if (carIndex == carList.size())
		return result;


	if (minLeaveTime < 0)//表示当前还没有任何车在库中
	{
		int minOutTime = pow(2, 30) - 1 + pow(2, 30);
		while (carIndex<carList.size() && carList[carIndex]->m_nApplyInTime<minOutTime
			&&result.size()<parkLocationTool.curParkLocationList.size())
		{
			minOutTime = min(minOutTime, carList[carIndex]->m_nApplyOutTime);
			result.push_back(carList[carIndex]);
			carIndex++;
		}
	}
	else
	{
		int minOutTime = pow(2, 30) - 1 + pow(2, 30);
		while (carIndex<carList.size() && carList[carIndex]->m_nApplyInTime<minLeaveTime&&carList[carIndex]->m_nApplyInTime<minOutTime
			&&carList[carIndex]->m_nApplyOutTime>minLeaveTime&&result.size()<parkLocationTool.curParkLocationList.size())
		{
			minOutTime = min(minOutTime, carList[carIndex]->m_nApplyOutTime);
			result.push_back(carList[carIndex]);
			carIndex++;
		}
	}

	if (result.empty())
	{
		result.push_back(carList[carIndex++]);
	}
	return result;
}



void CalculationTest()
{
	priority_queue<CCar*, vector<CCar*>, Cmp> m_nWaitLeaveCar;//等待出库的车辆，根据出库时间排序
	vector<Robot*> m_nRobots;

	parkLocationTool.curParkLocationList.clear(); //清空分配工具
	for (int i = 0; i < m_cGarageMap.m_SortBySumLengthParkList.size(); i++)
	{
		parkLocationTool.Add(m_cGarageMap.m_SortBySumLengthParkList[i]);   //将所有的停车位都加入到分配工具中
	}



	int curCarIndex = 0;
	curParkingCarNum = 0;

	for (int i = 0; i <m_nRobotNum; i++)  //创建机器人
	{
		Robot*aRobot = new Robot(i, 0, m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
		m_nRobots.push_back(aRobot);
	}

	//还有车没申请进库或者还有车没出库
	while (curCarIndex<m_nCars.size() || !m_nWaitLeaveCar.empty())
	{
		CCar*curEnterCar = NULL;
		CCar*curExitCar = NULL;
		if (curCarIndex < m_nCars.size())
		{
			curEnterCar = m_nCars[curCarIndex];
		}
		if (!m_nWaitLeaveCar.empty())
		{
			curExitCar = m_nWaitLeaveCar.top();
		}

		if (curEnterCar != NULL&&curExitCar != NULL)
		{
			//如果申请出库的时间早于申请入库时间，或者库已满，处理出库
			if (curExitCar->m_nApplyOutTime <curEnterCar->m_nApplyInTime || curParkingCarNum == m_cGarageMap.m_parkLocationNum)
			{
				//处理出库
				//HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
				HandleOutTest(curExitCar, m_nRobots, m_nWaitLeaveCar);
			}
			else
			{
				//处理入库
				int minLeaveTime = -1;
				if (curExitCar != NULL)
					minLeaveTime = curExitCar->m_nApplyOutTime;
				vector<CCar*>tmpCarList = getCarGroup(m_nCars, curCarIndex, minLeaveTime);
				HandleInGroup(tmpCarList, m_nRobots, m_nWaitLeaveCar);
				//MergeHandleIn(tmpCarList, m_nRobots, m_nWaitLeaveCar);
				int tt = 0;
			}
		}
		else if (curEnterCar != NULL)
		{
			//处理入库
			int minLeaveTime = -1;
			if (curExitCar != NULL)
				minLeaveTime = curExitCar->m_nApplyOutTime;
			vector<CCar*>tmpCarList = getCarGroup(m_nCars, curCarIndex, minLeaveTime);
			HandleInGroup(tmpCarList, m_nRobots, m_nWaitLeaveCar);
			//MergeHandleIn(tmpCarList, m_nRobots, m_nWaitLeaveCar);
			//curCarIndex++;
			//HandleIn(curEnterCar, m_nRobots, m_nWaitLeaveCar);


		}
		else
		{
			//处理出库
			HandleOutTest(curExitCar, m_nRobots, m_nWaitLeaveCar);
			//HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
		}
	}


	for (int i = 0; i <m_nRobotNum; i++)
	{
		delete m_nRobots[i];
		m_nRobots[i] = NULL;
	}
	m_nRobots.clear();
}

void InputData()
{
	cin >> m_nK >> m_nP >> m_nA >> m_nB;
	cin >> m_cGarageMap.m_nRow >> m_cGarageMap.m_nColumn;
	char szTmp;
	for (int i = 0; i < m_cGarageMap.m_nRow; i++)
	{
		for (int j = 0; j < m_cGarageMap.m_nColumn; j++)
		{

			cin >> szTmp;
			m_cGarageMap.m_cGarageMap[i][j] = szTmp;

			if (szTmp == 'I')
			{
				m_cGarageMap.m_EntranceX = i;
				m_cGarageMap.m_EntranceY = j;
			}
			if (szTmp == 'E')
			{
				m_cGarageMap.m_ExistX = i;
				m_cGarageMap.m_ExistY = j;
			}
			if (szTmp == 'P')
			{
				m_cGarageMap.m_parkLocationNum++;
				//保存该停车位
				//parkLocation*tmp = new parkLocation(i,j);
				//m_cGarageMap.m_nParkLocatinList.push(tmp);
			}

		}
	}

	// 读取车辆信息
	cin >> m_nCarNum;

	for (int i = 0; i < m_nCarNum; i++)
	{
		CCar* cCar = new CCar();
		cin >> cCar->m_nIndex >> cCar->m_nApplyInTime >> cCar->m_nApplyOutTime >> cCar->m_nMaxWaitTIme >> cCar->m_nWeight;
		m_nCars.push_back(cCar);
	}
	//sort(m_nCars.begin(), m_nCars.end(), compareCarsByInTime);
}
void Initialize()
{
	curParkingCarNum = 0;
	m_nT1 = 0;
	m_nW = 0;
	m_nQ = 0;
	m_AbandanByNoArr = 0;//因为机器人不能等待时间接待二放弃的车辆数
	m_AbandanByFull = 0; //因为车库已满放弃的车辆
	index2Distribute = 0;
	m_EntranceWaitTime = 0;
	Z = 0;

	newCarList.clear();

	map<int, parkingCarMess*>::iterator it = m_nParkingResult.begin();
	while (it != m_nParkingResult.end())
	{
		delete it->second;
		it->second = NULL;
		it++;
	}

	for (int i = 0; i < m_nCars.size(); i++)
	{
		m_nCars[i]->m_nParkLocation = NULL;
	}
	m_nParkingResult.clear();
	m_cGarageMap.Initialize();
}
void SaveResult(string fileName)
{
	ofstream out;
	out.open(fileName);

	out << "YES" << "\n";
	out << m_nRobotNum << " " << m_nT1*m_nB + m_nP*m_nQ << " " << m_nW << "\n";
	for (int i = 1; i <= m_nCarNum; i++)
	{
		if (m_nParkingResult.count(i) == 0)
		{
			out << i << " yes" << "\n";
			continue;
		}
		parkingCarMess*cur = m_nParkingResult[i];
		out << i << " no " << cur->entrantRobotID << " " << cur->entrantTime;
		for (int j = 0; j < cur->entrantPath.size(); j++)
		{
			out << " (" << cur->entrantPath[j].first << "," << cur->entrantPath[j].second << ")";
		}
		out << " " << cur->exitRobotID << " " << cur->exitTime;
		for (int j = cur->exitPath.size() - 1; j >= 0; j--)
		{
			out << " (" << cur->exitPath[j].first << "," << cur->exitPath[j].second << ")";
		}
		out << "\n";
	}

	out.close();
}

void Test()
{
	for (int i = 5; i < 30; i++)
	{
		Initialize();
		m_nRobotNum = i;
		//Calculation();
		CalculationTest();
		cout << "机器人数量：" << m_nRobotNum << endl;
		cout << "不可达放弃停车数：" << m_AbandanByNoArr << endl;
		cout << "车库满放弃停车数：" << m_AbandanByFull << endl;
		cout << "放弃停车数：" << m_nQ << endl;
		cout << "入库等待时间：" << m_EntranceWaitTime*m_nB << endl;
		cout << "罚时：" << m_nP*m_nQ << endl;
		cout << "等待时间：" << m_nB*m_nT1 << endl;
		cout << "能耗：" << m_nW << endl;
		cout << "Z值：" << m_nRobotNum*m_nA + m_nB*m_nT1 + m_nP*m_nQ + m_nW << endl;

		cout << endl;
	}
}

void HandleInWithNewCars(vector<CCar*> curCarList, vector<Robot*> &m_nRobots, 
	priority_queue<CCar*, vector<CCar*>, Cmp> &m_nWaitLeaveCar)
{
	vector<CCar*> tempCarList = curCarList;
	sort(tempCarList.begin(), tempCarList.end(), SortCarByWeight); //对车辆根据质量降序排列

	vector<int> rangeList(curCarList.size(), 0);

	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];
		for (int j = 0; j < tempCarList.size(); j++)
		{
			if (tempCarList[j] == curCar)
			{
				rangeList[i] = j;
				break;
			}
		}
	}

	for (int i = 0; i < curCarList.size(); i++)
	{
		CCar *curCar = curCarList[i];

		int num = 0, j = 0;

		for (; j < parkLocationTool.curParkLocationList.size(); j++)
		{
			if (num == rangeList[i])
				break;

			parkLocation*curParkLocation = parkLocationTool.curParkLocationList[j];
			int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
			if (InTime + curCar->m_nApplyInTime >= curParkLocation->canServiceTime)
				num++;
		}

		bool isHandle = false;
		int chooseIndex;
		int waitTime = ChooseEntrantRobot(curCar, m_nRobots, chooseIndex);
		if (chooseIndex < 0)  //因为机器人不可达放弃停车
		{
			m_AbandanByNoArr++;
			m_nQ++;
			continue;
		}

		for (int k = j; k < parkLocationTool.curParkLocationList.size(); k++)
		{
			if (isHandle)
				break;
			parkLocation *curParkLocation = parkLocationTool.curParkLocationList[k];
			int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
			if (InTime + curCar->m_nApplyInTime + waitTime < curParkLocation->canServiceTime)
				continue;


			int outTime = m_cGarageMap.m_Exit2ParkLocationPath[curParkLocation->index].size() - 1;

			if (m_nK*(InTime + outTime)*curCar->m_nWeight + (waitTime + outTime)*m_nB>m_nP)
			{
				break;
			}


			int curRange = rangeList[i];
			for (int t = 0; t < rangeList.size(); t++)
			{
				if (rangeList[t]>curRange)
				{
					rangeList[t]--;
				}
			}


			isHandle = true;

			m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

			m_nRobots[chooseIndex]->curLocate = curParkLocation->index;

			curParkLocation->isParking = true;
			curCar->m_nParkLocation = curParkLocation;

			m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + InTime;
			WriteEntrantHis(curCar, chooseIndex, waitTime);
			m_nWaitLeaveCar.push(curCar);

			parkLocationTool.Delete(curParkLocation);

			curParkingCarNum++;
			m_nT1 += waitTime;
			m_nW += m_nK*curCar->m_nWeight*InTime;
		}
		if (!isHandle)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (isHandle)
					break;
				parkLocation*curParkLocation = parkLocationTool.curParkLocationList[k];
				int InTime = m_cGarageMap.m_Entrance2ParkLocationPath[curParkLocation->index].size() - 1;
				if (InTime + curCar->m_nApplyInTime + waitTime < curParkLocation->canServiceTime)
					continue;



				int outTime = m_cGarageMap.m_Exit2ParkLocationPath[curParkLocation->index].size() - 1;
				if (m_nK*(InTime + outTime)*curCar->m_nWeight + (waitTime + outTime)*m_nB>m_nP)
				{
					continue;
				}

				isHandle = true;


				int curRange = rangeList[i];
				for (int t = 0; t < rangeList.size(); t++)
				{
					if (rangeList[t]>curRange)
					{
						rangeList[t]--;
					}
				}

				m_EntranceWaitTime += waitTime;  //记录车辆进库的等待时间

				m_nRobots[chooseIndex]->curLocate = curParkLocation->index;

				curParkLocation->isParking = true;
				curCar->m_nParkLocation = curParkLocation;

				m_nRobots[chooseIndex]->curTime = curCar->m_nApplyInTime + waitTime + InTime;
				WriteEntrantHis(curCar, chooseIndex, waitTime);
				m_nWaitLeaveCar.push(curCar);

				parkLocationTool.Delete(curParkLocation);

				curParkingCarNum++;
				m_nT1 += waitTime;
				m_nW += m_nK*curCar->m_nWeight*InTime;
			}
		}
		if (!isHandle)
		{
			m_AbandanByFull++;
			m_nQ++;
			int curRange = rangeList[i];
			for (int t = 0; t < rangeList.size(); t++)
			{
				if (rangeList[t]>curRange)
				{
					rangeList[t]--;
				}
			}
		}
	}
}


void CalculationWithNewCars()
{
	priority_queue<CCar*, vector<CCar*>, Cmp> m_nWaitLeaveCar;//等待出库的车辆，根据出库时间排序
	vector<Robot*> m_nRobots;

	parkLocationTool.curParkLocationList.clear(); //清空分配工具
	for (int i = 0; i < m_cGarageMap.m_SortBySumLengthParkList.size(); i++)
	{
		parkLocationTool.Add(m_cGarageMap.m_SortBySumLengthParkList[i]);   //将所有的停车位都加入到分配工具中
	}



	int curCarIndex = 0;
	curParkingCarNum = 0;

	for (int i = 0; i <m_nRobotNum; i++)  //创建机器人
	{
		Robot*aRobot = new Robot(i, 0, m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
		m_nRobots.push_back(aRobot);
	}

	//还有车没申请进库或者还有车没出库
	while (curCarIndex<newCarList.size() || !m_nWaitLeaveCar.empty())
	{
		CCar*curEnterCar = NULL;
		CCar*curExitCar = NULL;
		if (curCarIndex < newCarList.size())
		{
			curEnterCar = newCarList[curCarIndex];
		}
		if (!m_nWaitLeaveCar.empty())
		{
			curExitCar = m_nWaitLeaveCar.top();
		}

		if (curEnterCar != NULL&&curExitCar != NULL)
		{
			//如果申请出库的时间早于申请入库时间，或者库已满，处理出库
			if (curExitCar->m_nApplyOutTime <curEnterCar->m_nApplyInTime || curParkingCarNum == m_cGarageMap.m_parkLocationNum)
			{
				//处理出库
				//HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
				HandleOutTest(curExitCar, m_nRobots, m_nWaitLeaveCar);
			}
			else
			{
				//处理入库
				int minLeaveTime = -1;
				if (curExitCar != NULL)
					minLeaveTime = curExitCar->m_nApplyOutTime;
				vector<CCar*>tmpCarList = getCarGroup(newCarList, curCarIndex, minLeaveTime);
				//HandleInGroup(tmpCarList,m_nRobots,m_nWaitLeaveCar);
				HandleInWithNewCars(tmpCarList, m_nRobots, m_nWaitLeaveCar);
				int tt = 0;
			}
		}
		else if (curEnterCar != NULL)
		{
			//处理入库
			int minLeaveTime = -1;
			if (curExitCar != NULL)
				minLeaveTime = curExitCar->m_nApplyOutTime;
			vector<CCar*>tmpCarList = getCarGroup(newCarList, curCarIndex, minLeaveTime);
			//HandleInGroup(tmpCarList, m_nRobots, m_nWaitLeaveCar);
			HandleInWithNewCars(tmpCarList, m_nRobots, m_nWaitLeaveCar);


		}
		else
		{
			//处理出库
			HandleOutTest(curExitCar, m_nRobots, m_nWaitLeaveCar);
			//HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
		}
	}


	for (int i = 0; i <m_nRobotNum; i++)
	{
		delete m_nRobots[i];
		m_nRobots[i] = NULL;
	}
	m_nRobots.clear();
}

int calcBestRobotNum(void (*fun)(), int &minZ)
{
	minZ = m_nCarNum*m_nP;
	int bestNum = 0;

	m_AbandanByNoArr = m_nCarNum;
	m_EntranceWaitTime = 0;


	int pre = 0, cur = 0;

	while (m_AbandanByNoArr*m_nP + m_EntranceWaitTime*m_nB>m_nA)   //表示当前机器人数量还有优化空间
	{
		pre = cur;
		cur += 10;
		Initialize();
		m_nRobotNum = cur;
		fun();
		int curZ = m_nRobotNum*m_nA + m_nW + m_nP*m_nQ + m_nB*m_nT1;

		if (curZ < minZ)
		{
			minZ = curZ;
			bestNum = cur;
		}
	}
	for (int i = pre + 1; i < cur; i++)
	{
		Initialize();
		m_nRobotNum = i;

		fun();
		int curZ = m_nRobotNum*m_nA + m_nW + m_nP*m_nQ + m_nB*m_nT1;
		if (curZ < minZ)
		{
			minZ = curZ;
			bestNum = i;
		}
	}

	return bestNum;
}

int CalcNewCarsBestNum(vector<CCar*> carList,int curRotbotNum,int curAbandonNum,int &minZ)
{
	Initialize();
	m_nQ = curAbandonNum;
	newCarList = carList;

	m_nRobotNum = curRotbotNum;
	CalculationWithNewCars();
	minZ = m_nRobotNum*m_nA + m_nB*m_nT1 + m_nP*m_nQ + m_nW;

	curRotbotNum--;
	while (curRotbotNum>=0)
	{
		Initialize();
		m_nQ = curAbandonNum;
		newCarList = carList;

		m_nRobotNum = curRotbotNum;
		CalculationWithNewCars();

		int curZ = m_nRobotNum*m_nA + m_nB*m_nT1 + m_nP*m_nQ + m_nW;
		if (curZ >= minZ)
			break;
		else
		{
			minZ = curZ;
			curRotbotNum--;
		}
	}
	return curRotbotNum + 1;



}

void showMessage()
{
	cout << "机器人数量：" << m_nRobotNum << endl;
	cout << "不可达放弃停车数：" << m_AbandanByNoArr << endl;
	cout << "车库满放弃停车数：" << m_AbandanByFull << endl;
	cout << "放弃停车数：" << m_nQ << endl;
	cout << "入库等待时间：" << m_EntranceWaitTime*m_nB << endl;
	cout << "罚时：" << m_nP*m_nQ << endl;
	cout << "等待时间：" << m_nB*m_nT1 << endl;
	cout << "能耗：" << m_nW << endl;
	cout << "Z值：" << m_nRobotNum*m_nA + m_nB*m_nT1 + m_nP*m_nQ + m_nW << endl;
	SaveResult("1result.txt");
	system("demo.bat");
	cout << endl;
}

void ReleseMemory()
{
	for (int i = 0; i < m_nCars.size(); i++)
	{
		delete m_nCars[i];
		m_nCars[i] = NULL;
	}
	m_nCars.clear();
	map<int, parkingCarMess*>::iterator it = m_nParkingResult.begin();
	while (it != m_nParkingResult.end())
	{
		delete it->second;
		it->second = NULL;
		it++;
	}
	m_nParkingResult.clear();

	for (int i = 0; i < m_nCars.size(); i++)
	{
		delete m_nCars[i];
		m_nCars[i] = NULL;
	}
	m_nCars.clear();
}

unordered_map<CCar*, bool> GetInCars(int abandNum)  //获取所有进库的车辆
{
	unordered_map<CCar*, bool> result;

	vector<CCar*> tempCarList = m_nCars;
	sort(tempCarList.begin(), tempCarList.end(), SortCarByWeight); //对车辆根据质量降序排列

	int inCarNum = m_nCarNum - abandNum;

	for (int i = tempCarList.size() - 1; i >= 0; i--)
	{
		if (result.size() == inCarNum)
			break;
		result[tempCarList[i]] = true;
	}

	return result;



}


void CalculationFinal(unordered_map<CCar*, bool> inputCars)
{
	priority_queue<CCar*, vector<CCar*>, Cmp> m_nWaitLeaveCar;//等待出库的车辆，根据出库时间排序
	vector<Robot*> m_nRobots;

	int curCarIndex = 0;
	curParkingCarNum = 0;

	for (int i = 0; i <m_nRobotNum; i++)  //创建机器人
	{
		Robot *aRobot = new Robot(i, 0, m_cGarageMap.m_EntranceX, m_cGarageMap.m_EntranceY);
		m_nRobots.push_back(aRobot);
	}

	//还有车没申请进库或者还有车没出库
	while (curCarIndex<m_nCars.size() || !m_nWaitLeaveCar.empty())
	{
		CCar *curEnterCar = NULL;
		CCar *curExitCar = NULL;
		/*if (curCarIndex < m_nCars.size())
		{
		curEnterCar = m_nCars[curCarIndex];
		}*/
		while (curCarIndex < m_nCars.size())
		{
			if (inputCars.find(m_nCars[curCarIndex]) == inputCars.end())
			{
				curCarIndex++;
			}
			else
			{
				curEnterCar = m_nCars[curCarIndex];
				break;
			}
		}



		if (!m_nWaitLeaveCar.empty())
		{
			curExitCar = m_nWaitLeaveCar.top();
		}

		if (curEnterCar != NULL&&curExitCar != NULL)
		{


			//如果申请出库的时间早于申请入库时间，或者库已满，处理出库
			if (curExitCar->m_nApplyOutTime <curEnterCar->m_nApplyInTime || curParkingCarNum == m_cGarageMap.m_parkLocationNum)
			{
				HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
			}
			else
			{
				//处理入库
				curCarIndex++;
				HandleIn(curEnterCar, m_nRobots, m_nWaitLeaveCar);


			}
		}
		else if (curEnterCar != NULL)
		{
			//处理入库
			curCarIndex++;
			HandleIn(curEnterCar, m_nRobots, m_nWaitLeaveCar);
		}
		else
		{
			//处理出库
			HandleOut(curExitCar, m_nRobots, m_nWaitLeaveCar);
		}
	}
	for (int i = 0; i <m_nRobotNum; i++)  //销毁机器人
	{
		delete m_nRobots[i];
		m_nRobots[i] = NULL;
	}
	m_nRobots.clear();
}




int main()
{

	//char *szPath = "1.txt";
	//ReadCaseInfo(szPath);
	InputData();


	if (!m_cGarageMap.isValidMap())  //先判断地图正确与否
	{
		cout << "NO" << "\n";
		return 0;
	}

	m_cGarageMap.CreateParkLocation();//生成所有的停车位,同时进行排序
	m_cGarageMap.CalcLength_BetweenParkLocation();//计算所有目前已知的停车位到停车位的最短路径

	//Test();
	//return 0;



	int minZ0, minZ1, minZ2;
	int bestRobotNum0 = calcBestRobotNum(CalculationTest, minZ0);
	int bestRobotNum1 = calcBestRobotNum(Calculation, minZ1);



	Initialize();
	m_nRobotNum = bestRobotNum1;
	Calculation();

	/*int curAbandant = m_nQ;
	vector<CCar*>tmp = newCarList;
	Initialize();
	m_nQ = curAbandant;
	newCarList = tmp;
	m_nRobotNum = bestRobotNum1-4;
	CalculationWithNewCars();
	minZ2 = m_nRobotNum*m_nA + m_nB*m_nT1 + m_nP*m_nQ + m_nW;*/

	int curAbandant = m_nQ;
	vector<CCar*> tmp = newCarList;
	Initialize(); 

	int bestRobotNum2 = CalcNewCarsBestNum(tmp, bestRobotNum1, curAbandant, minZ2);

	


	if (minZ0 < minZ1&&minZ0 < minZ2)
	{
		Initialize();
		m_nRobotNum = bestRobotNum0;
		CalculationTest();
	}
	else if (minZ1 < minZ0&&minZ1 < minZ2)
	{
		Initialize();
		m_nRobotNum = bestRobotNum1;
		Calculation();
	}
	else
	{
		Initialize();
		m_nQ = curAbandant;
		newCarList = tmp;
		m_nRobotNum = bestRobotNum2;
		CalculationWithNewCars();
	}
	Show();
	//showMessage();

	

	ReleseMemory();
	return 0;
}