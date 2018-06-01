#ifndef BATTLEAI_H
#define BATTLEAI_H

#include "inputOutput.h"
#include "InputHandler.h"
#include "Node.h"
#include "SquareGraph.h"

struct Route
{
    Point2D UAVstartPos;
    Point2D goodsStartPos;
    Point2D goodsEndPos;
    vector<Node> UAVToGoods;
    vector<Node> goodsStartToEnd;
    int UAVNo;
    int goodNo;
    Route() { }
    Route(Point2D UAVstartPos, Point2D goodsStartPos, Point2D goodsEndPos,
          vector<Node> UAVToGoods, vector<Node> goodsStartToEnd,
          int UAVNo,int goodNo)
        :UAVstartPos(UAVstartPos), goodsStartPos(goodsStartPos), goodsEndPos(goodsEndPos),
          UAVToGoods(UAVToGoods), goodsStartToEnd(goodsStartToEnd),
          UAVNo(UAVNo), goodNo(goodNo) { }
};

class BattleAI
{
public:
    BattleAI() { }
    ~BattleAI()
    {
        for (int i = 0; i < UAVCurInfos.size(); ++i) {
            if (UAVCurInfos[i]) {
                delete UAVCurInfos[i];
                UAVCurInfos[i] = nullptr;
            }
        }
        UAVCurInfos.clear();

        for (int i = 0; i < goodsInfos.size(); ++i) {
            if (goodsInfos[i]) {
                delete goodsInfos[i];
                goodsInfos[i] = nullptr;
            }
        }
        goodsInfos.clear();

        for (int i = 0; i < UAVStatusWe.size(); ++i) {
            if (UAVStatusWe[i]) {
                delete UAVStatusWe[i];
                UAVStatusWe[i] = nullptr;
            }
        }
        UAVStatusWe.clear();

        for (int i = 0; i < UAVStatusEnemy.size(); ++i) {
            if (UAVStatusEnemy[i]) {
                delete UAVStatusEnemy[i];
                UAVStatusEnemy[i] = nullptr;
            }
        }
        UAVStatusEnemy.clear();

    }

	//连接服务器
	void linkToTheServer(const char *IP, const char *port, const char *token)
	{
		io.socketInit(IP, port);
		this->token = string(token);
	}

	//服务器第一次返回
	Json::Value firstLinkToTheServer()
	{
		Json::Value root = io.readSocket();
		//token = root["token"].asString();
		return root;
	}

	//向服务器确认身份
	int identifyToTheServer()
	{
		Json::Value root;
		root["token"] = Json::Value(token);
		root["action"] = Json::Value("sendtoken");
		return io.writeSocket(root);
	}

    //向服务器确认准备好
    int identifyToTheServerReady()
    {
        Json::Value root;
        root["token"] = Json::Value(token);
        root["action"] = Json::Value("ready");
        return io.writeSocket(root);
    }

    Json::Value identifyServerToClient()
	{
		return io.readSocket();
	}

	void startBattleServerToClient()
	{
		Json::Value root = io.readSocket();

		time = root["time"].asInt();
        mapIn.xWidth = root["map"]["map"]["x"].asInt();
        mapIn.yLength = root["map"]["map"]["y"].asInt();
        mapIn.zHeight = root["map"]["map"]["z"].asInt();
		mapIn.parkingPos = Point2D(root["parking"]["x"].asInt(), root["parking"]["y"].asInt());
        mapIn.hLow = root["map"]["h_low"].asInt();
        mapIn.hHigh = root["map"]["h_high"].asInt();

        int buildingsSize = root["map"]["building"].size();
		for (int i = 0; i < buildingsSize; ++i) {
            Json::Value tempValue = root["map"]["building"][i];
			Point2D tempPoint = Point2D(tempValue["x"].asInt(), tempValue["y"].asInt());
			int templ = tempValue["l"].asInt();
			int tempw = tempValue["w"].asInt();
			int temph = tempValue["h"].asInt();
			mapIn.buildings.emplace_back(tempPoint, templ, tempw, temph);
		}

        int fogsSize = root["map"]["fog"].size();
		for (int i = 0; i < fogsSize; ++i) {
            Json::Value tempValue = root["map"]["fog"][i];
			Point2D tempPoint = Point2D(tempValue["x"].asInt(), tempValue["y"].asInt());
			int templ = tempValue["l"].asInt();
			int tempw = tempValue["w"].asInt();
			int tempb = tempValue["b"].asInt();
			int tempt = tempValue["t"].asInt();
			mapIn.fogs.emplace_back(tempPoint, templ, tempw, tempb, tempt);
		}

        int initUAVsSize = root["map"]["init_UAV"].size();
		for (int i = 0; i < initUAVsSize; ++i) {
            Json::Value tempValue = root["map"]["init_UAV"][i];
			int tempNo = tempValue["no"].asInt();
			Point3D tempPoint = Point3D(tempValue["x"].asInt(),
				tempValue["y"].asInt(), tempValue["z"].asInt());
			int tempLoad = tempValue["load_weight"].asInt();
			string tempType = tempValue["type"].asString();
            int tempStatus = tempValue["status"].asInt();
			int tempGoodsNo = tempValue["goods_no"].asInt();
			mapIn.initUAVs.emplace_back(tempNo, tempPoint, tempLoad,
				tempType, tempStatus, tempGoodsNo);

            //UAVCurInfo *newUAVCurInfo = new UAVCurInfo(tempNo, tempPoint, tempGoodsNo);
            //UAVCurInfos.emplace_back(newUAVCurInfo);
            int cnt = 0;
            for (int i = 0; i < UAVCurInfos.size(); ++i) {
                if (tempNo == UAVCurInfos[i]->no)
                    ++cnt;
            }
            if (cnt == 0) {
                UAVCurInfo *newUAVCurInfo = new UAVCurInfo(tempNo, tempPoint, tempGoodsNo,
                                                           tempLoad, tempType, tempStatus);
                UAVCurInfos.emplace_back(newUAVCurInfo);
                sort(UAVCurInfos.begin(), UAVCurInfos.end(),
                     [](UAVCurInfo *a, UAVCurInfo *b) {return a->loadWeight > b->loadWeight; });
            }
		}

        int UAVpricesSize = root["map"]["UAV_price"].size();
		for (int i = 0; i < UAVpricesSize; ++i) {
            Json::Value tempValue = root["map"]["init_UAV"][i];
			string tempType = tempValue["type"].asString();
			int tempLoad = tempValue["load_weight"].asInt();
			int tempValues = tempValue["value"].asInt();
			mapIn.UAVprices.emplace_back(tempType, tempLoad, tempValues);
		}

		sort(mapIn.UAVprices.begin(), mapIn.UAVprices.end(),
			[](UAVPrice a, UAVPrice b){return a.value > b.value; });
	}

	int sentPosToServer(bool isNeedPurchaseUAV = false)
	{
		Json::Value root;
		root["token"] = Json::Value(token);
		root["action"] = Json::Value("flyPlane");
		for (int i = 0; i < UAVCurInfos.size(); ++i) {
			int no = UAVCurInfos[i]->no;
			int x = UAVCurInfos[i]->curPos.x;
			int y = UAVCurInfos[i]->curPos.y;
			int z = UAVCurInfos[i]->curPos.z;
			int goodsNo = UAVCurInfos[i]->goodsNo;
			Json::Value tempV;
			tempV["no"] = Json::Value(no);
			tempV["x"] = Json::Value(x);
			tempV["y"] = Json::Value(y);
			tempV["z"] = Json::Value(z);
			tempV["goods_no"] = Json::Value(goodsNo);
			root["UAV_info"][i] = tempV;
		}
		if (isNeedPurchaseUAV) {
			int idx = -1;
			for (int i = 0; i < mapIn.UAVprices.size(); ++i) {
				if (mapIn.UAVprices[i].value < acquireValue) {
					idx = i;
				}
			}
			if (idx != -1) {
				Json::Value tempBuy;
				tempBuy["purchase"] = Json::Value(mapIn.UAVprices[idx].type);
				root["purchase_UAV"][0] = tempBuy;
			}
		}
		int str_len = io.writeSocket(root);
		return str_len;
	}

	void getWeEnemyInfo(int &matchStatus)
	{
		Json::Value root = io.readSocket();
		matchStatus = root["match_status"].asInt();
        if (matchStatus == 1)
			return;
		time = root["time"].asInt();

//		for (int i = 0; i < UAVCurInfos.size(); ++i) {
//			if (UAVCurInfos[i]) {
//				delete UAVCurInfos[i];
//				UAVCurInfos[i] = nullptr;
//			}
//		}
//		UAVCurInfos.clear();

		for (int i = 0; i < UAVStatusWe.size(); ++i) {
			if (UAVStatusWe[i]) {
				delete UAVStatusWe[i];
				UAVStatusWe[i] = nullptr;
			}
		}

		UAVStatusWe.clear();
		int UAVWeSize = root["UAV_we"].size();
		for (int i = 0; i < UAVWeSize; ++i) {
			Json::Value tempValue = root["UAV_we"][i];
			int tempNo = tempValue["no"].asInt();
			string tempType = tempValue["type"].asString();
			Point3D tempPoint = Point3D(tempValue["x"].asInt(),
				tempValue["y"].asInt(), tempValue["z"].asInt());
			int tempGoodsNo = tempValue["goods_no"].asInt();
            int tempStatus = tempValue["status"].asInt();

			UAVStatus *newUAVStatus = new UAVStatus(tempNo, tempType, tempPoint,
				tempGoodsNo, tempStatus);
			UAVStatusWe.emplace_back(newUAVStatus);

            //UAVCurInfo *newUAVCurInfo = new UAVCurInfo(tempNo, tempPoint, tempGoodsNo);
//			UAVCurInfos.emplace_back(newUAVCurInfo);

            int cnt = 0;
            for (int i = 0; i < UAVCurInfos.size(); ++i) {
                if (tempNo == UAVCurInfos[i]->no)
                    ++cnt;
            }
            if (cnt == 0) {
                int tempLoad;
                for (int i = 0; i < mapIn.UAVprices.size(); ++i)
                    if (tempType == mapIn.UAVprices[i].type) {
                        tempLoad = mapIn.UAVprices[i].loadWeight;
                        break;
                    }
                UAVCurInfo *newUAVCurInfo = new UAVCurInfo(tempNo, tempPoint, tempGoodsNo,
                                                           tempLoad, tempType, tempStatus);
                UAVCurInfos.emplace_back(newUAVCurInfo);
                sort(UAVCurInfos.begin(), UAVCurInfos.end(),
                     [](UAVCurInfo *a, UAVCurInfo *b) {return a->loadWeight > b->loadWeight; });
            }
		}
		totalValue = root["we_value"].asInt();

		for (int i = 0; i < UAVStatusEnemy.size(); ++i) {
			if (UAVStatusEnemy[i]) {
				delete UAVStatusEnemy[i];
				UAVStatusEnemy[i] = nullptr;
			}
		}
		UAVStatusEnemy.clear();
		int UAVEnemySize = root["UAV_enemy"].size();
		for (int i = 0; i < UAVEnemySize; ++i) {
			Json::Value tempValue = root["UAV_enemy"][i];
			int tempNo = tempValue["no"].asInt();
			string tempType = tempValue["type"].asString();
			Point3D tempPoint = Point3D(tempValue["x"].asInt(),
				tempValue["y"].asInt(), tempValue["z"].asInt());
			int tempGoodsNo = tempValue["goods_no"].asInt();
            int tempStatus = tempValue["status"].asInt();

			UAVStatus *newUAVStatus = new UAVStatus(tempNo, tempType, tempPoint,
				tempGoodsNo, tempStatus);
			UAVStatusEnemy.emplace_back(newUAVStatus);
		}

//		for (int i = 0; i < goodsInfos.size(); ++i) {
//			if (goodsInfos[i]) {
//				delete goodsInfos[i];
//				goodsInfos[i] = nullptr;
//			}
//		}
//		goodsInfos.clear();

		int goodsInfosSize = root["goods"].size();
		for (int i = 0; i < goodsInfosSize; ++i) {
			Json::Value tempValue = root["goods"][i];
			int tempNo = tempValue["no"].asInt();
			Point2D tempStartPos = Point2D(tempValue["start_x"].asInt(), 
				tempValue["start_y"].asInt());
			Point2D tempEndPos = Point2D(tempValue["end_x"].asInt(),
				tempValue["end_y"].asInt());
			int tempWeight = tempValue["Weight"].asInt();
			int tempValues = tempValue["value"].asInt();
			int tempStartTime = tempValue["start_time"].asInt();
			int tempRemainTime = tempValue["remain_time"].asInt();
            int tempLeftTime = tempValue["left_time"].asInt();
            //int tempLeftTime = 0;
            int tempStatus = tempValue["status"].asInt();

//			GoodsInfo *newGoodsInfo = new GoodsInfo(tempNo, tempStartPos, tempEndPos,
//                tempWeight, tempValues,tempStartTime, tempRemainTime, tempLeftTime, tempStatus);
//			goodsInfos.emplace_back(newGoodsInfo);
            int cnt = 0;
            for (int i = 0; i < goodsInfos.size(); ++i) {
                if (tempNo == goodsInfos[i]->no)
                    ++cnt;
            }
            if (cnt == 0) {
                GoodsInfo *newGoodsInfo = new GoodsInfo(tempNo, tempStartPos, tempEndPos,
                                                        tempWeight, tempValues,tempStartTime,
                                                        tempRemainTime, tempLeftTime, tempStatus);
                goodsInfos.emplace_back(newGoodsInfo);
                sort(goodsInfos.begin(), goodsInfos.end(),
                     [](GoodsInfo *a, GoodsInfo *b) {return a->value > b->value;});
            }
		}
	}

    void initMap()
    {
        matrixMap.assign(mapIn.xWidth, vector<char>(mapIn.yLength, ' '));
        for (int j = 0; j < mapIn.buildings.size(); ++j) {
            for (int x = mapIn.buildings[j].startPos.x, xn1 = 0;
                 xn1 < mapIn.buildings[j].len;++x, ++xn1) {
                for (int y = mapIn.buildings[j].startPos.y, yn1 = 0;
                     yn1 < mapIn.buildings[j].width;++y, ++yn1)
                    matrixMap[x][y] = 'X';
            }
        }
    }

    Route* calRoutes(UAVCurInfo *curUAV, GoodsInfo *curGoods)
    {
		Route *route = new Route();
        matrixMap[curUAV->curPos.x][curUAV->curPos.y] = 'T';
        matrixMap[curGoods->startPos.x][curGoods->startPos.y] = 'G';
        InputHandler handler;
        SquareGraph graph = handler.readMap(matrixMap);
        vector<Node> path = graph.executeAStar();
        //graph.printPath(path);
       // paths.emplace_back(path);
        //getchar();
        if (path.size() + 2*mapIn.hLow + time 
					 > curGoods->startTime + curGoods->remainTime) 
            return nullptr;
      
        route->UAVToGoods = path;

        matrixMap[curUAV->curPos.x][curUAV->curPos.y] = ' ';
        matrixMap[curGoods->startPos.x][curGoods->startPos.y] = 'T';
        matrixMap[curGoods->endPos.x][curGoods->endPos.y] = 'G';
        graph = handler.readMap(matrixMap);
        path = graph.executeAStar();
        graph.printPath(path);
        matrixMap[curGoods->startPos.x][curGoods->startPos.y] = ' ';
        matrixMap[curGoods->endPos.x][curGoods->endPos.y] = ' ';
        //pathsStartToEnd.emplace_back(path);
        route->goodsStartToEnd = path;
        route->goodNo = curGoods->no;
		route->UAVstartPos = Point2D(curUAV->curPos.x, curUAV->curPos.y);
        route->goodsStartPos = curGoods->startPos;
        route->goodsEndPos = curGoods->endPos;
        route->UAVNo = curUAV->no;
        return route;
    }

	void initUAVStatus()
	{
		sentPosToServer();
		int match_status;
		getWeEnemyInfo(match_status);
		if (match_status == 1) {
			//break;
			return;
		}
	}

	void startBattle()
	{
        initMap();
		for (;;) {
            sentPosToServer();
            int match_status;
            getWeEnemyInfo(match_status);
            if (match_status == 1) {
                //break;
                return;
            }

            //calculate the route
			for (int i = 0; i < UAVCurInfos.size(); ++i) {
				if (UAVCurInfos[i]->toCarrayGoodsNo != -1)
					continue;
				for (int j = 0; j < goodsInfos.size(); ++j) {
					if (goodsInfos[j]->toBeCarryUAVNo != -1)
						continue;
					if (UAVCurInfos[i]->loadWeight < goodsInfos[j]->weight
						|| goodsInfos[j]->state != 0)
						continue;
					Route *route = calRoutes(UAVCurInfos[i], goodsInfos[j]);
					if (route == nullptr)
						continue;
					else {
						UAVCurInfos[i]->toCarrayGoodsNo = goodsInfos[j]->no;
						goodsInfos[j]->toBeCarryUAVNo = UAVCurInfos[i]->no;
						routes.emplace_back(route);
                        break;
					}
				}
			}

            //every route march
			for (int i = 0; i < routes.size(); ++i) {
				Route *route = routes[i];
				int idxUAV, idxGoods;
				for (int j = 0; j < UAVCurInfos.size(); ++j) {
					if (route->UAVNo == UAVCurInfos[j]->no) {
						idxUAV = j;
						break;
					}
				}
				for (int j = 0; j < goodsInfos.size(); ++j) {
					if (route->goodNo == goodsInfos[j]->no) {
						idxGoods = j;
						break;
					}
				}
                //up
				while (UAVCurInfos[idxUAV]->curPos.z < mapIn.hLow) {
                    ++UAVCurInfos[idxUAV]->curPos.z;
					sentPosToServer();
					int match_status;
					getWeEnemyInfo(match_status);
					if (match_status == 1) {
						//break;
						return;
					}

				}

                //to goods startPos
				for (int j = 1; j < route->UAVToGoods.size(); ++j) {
                    UAVCurInfos[idxUAV]->curPos.x = route->UAVToGoods[j].x;
                    UAVCurInfos[idxUAV]->curPos.y = route->UAVToGoods[j].y;

					sentPosToServer();
					int match_status;
					getWeEnemyInfo(match_status);
					if (match_status == 1) {
						//break;
						return;
					}					
				}

                //down
				while (UAVCurInfos[idxUAV]->curPos.z >= 0) {
                    --UAVCurInfos[idxUAV]->curPos.z;
                    if (UAVCurInfos[idxUAV]->curPos.z == 0)
                        UAVCurInfos[idxUAV]->goodsNo = route->goodNo;

					sentPosToServer();
					int match_status;
					getWeEnemyInfo(match_status);
					if (match_status == 1) {
						//break;
						return;
                    }

                    if (UAVCurInfos[idxUAV]->curPos.z == 0)
                        break;

				}

                //up
				while (UAVCurInfos[idxUAV]->curPos.z < mapIn.hLow) {                   
                    ++UAVCurInfos[idxUAV]->curPos.z;

					sentPosToServer();
					int match_status;
					getWeEnemyInfo(match_status);
					if (match_status == 1) {
						//break;
						return;
					}	
				}

                //move
				for (int j = 1; j < route->goodsStartToEnd.size(); ++j) {
                    UAVCurInfos[idxUAV]->curPos.x = route->goodsStartToEnd[j].x;
                    UAVCurInfos[idxUAV]->curPos.y = route->goodsStartToEnd[j].y;

					sentPosToServer();
					int match_status;
					getWeEnemyInfo(match_status);
					if (match_status == 1) {
						//break;
						return;
					}					
				}

                //down
                while (UAVCurInfos[idxUAV]->curPos.z >= 0) {
                    --UAVCurInfos[idxUAV]->curPos.z;

                    sentPosToServer();
                    int match_status;
                    getWeEnemyInfo(match_status);
                    if (match_status == 1) {
                        //break;
                        return;
                    }

                    if (UAVCurInfos[idxUAV]->curPos.z == 0) {
                        UAVCurInfos[idxUAV]->toCarrayGoodsNo = -1;
                        break;
                    }
                }

                for (auto iter = goodsInfos.begin();
                     iter != goodsInfos.end(); ++iter) {
					if ((*iter)->no == route->goodNo) {
						goodsInfos.erase(iter);
						break;
					}
				}
			}

			for (int i = 0; i < routes.size(); ++i) {
				if (routes[i]) {
					delete routes[i];
					routes[i] = nullptr;
				}
			}
			routes.clear();
		}
#if 0
        bool flag = false;
        vector<vector<Node>> paths;
        vector<vector<Node>> pathsStartToEnd;
        vector<int> steps(100, 0);
		for (;;) {


            sentPosToServer();
            int match_status;
            getWeEnemyInfo(match_status);
            if (match_status == 1) {
                //break;
                return;
            }

//            if (UAVCurInfos[0]->curPos.z < mapIn.hLow
//                    && (!UAVCurInfos[0]->isArriveStart
//                        && !UAVCurInfos[0]->isArriveStart))
//                ++(UAVCurInfos[0]->curPos.z);

            if (UAVCurInfos[0]->isArriveStart) {
                if (UAVCurInfos[0]->curPos.z > 0)
                    --(UAVCurInfos[0]->curPos.z);
                else if (UAVCurInfos[0]->curPos.x != paths[0][paths[0].size() - 1].x
                         || UAVCurInfos[0]->curPos.y != paths[0][paths[0].size() - 1].y) {
                    UAVCurInfos[0]->isArriveStart = false;
                }
                if (UAVCurInfos[0]->curPos.z == 0) {
                    UAVCurInfos[0]->goodsNo = goodsInfos[0]->no;
                    UAVCurInfos[0]->isArriveStart = false;
                }
            }
            else if (UAVCurInfos[0]->isArriveEnd) {
                if (UAVCurInfos[0]->curPos.z > 0)
                    --(UAVCurInfos[0]->curPos.z);
                else if (UAVCurInfos[0]->curPos.z == 0) {
                    UAVCurInfos[0]->isArriveEnd= false;
                }
            }
            else if (UAVCurInfos[0]->curPos.z < mapIn.hLow)
                ++(UAVCurInfos[0]->curPos.z);

            else if (UAVCurInfos[0]->curPos.z >=  mapIn.hLow
                    && !UAVCurInfos[0]->isArriveStart && !UAVCurInfos[0]->isArriveEnd
                    && paths.size() > 1) {
                if(steps[0] < paths[0].size() - 1) {
                    UAVCurInfos[0]->curPos.x = paths[0][steps[0] + 1].x;
                    UAVCurInfos[0]->curPos.y = paths[0][steps[0] + 1].y;
                    ++steps[0];
                }

                else if (UAVCurInfos[0]->curPos.x == paths[0][paths[0].size() - 1].x
                 && UAVCurInfos[0]->curPos.y == paths[0][paths[0].size() - 1].y) {
                     UAVCurInfos[0]->isArriveStart = true;
                     paths.erase(paths.begin());
                }
            }

            else if (UAVCurInfos[0]->curPos.z >=  mapIn.hLow
                     && !UAVCurInfos[0]->isArriveEnd) {
                if(pathsStartToEnd.size() > 0) {
                     if(steps[1] < pathsStartToEnd[0].size() - 1) {
                        UAVCurInfos[0]->curPos.x = pathsStartToEnd[0][steps[1] + 1].x;
                        UAVCurInfos[0]->curPos.y = pathsStartToEnd[0][steps[1] + 1].y;
                     }
                     ++steps[1];
                     if (UAVCurInfos[0]->curPos.x == pathsStartToEnd[0][pathsStartToEnd[0].size() - 1].x
                         && UAVCurInfos[0]->curPos.y == pathsStartToEnd[0][pathsStartToEnd[0].size() - 1].y)
                         UAVCurInfos[0]->isArriveEnd = true;
                }
            }
            else {

            }

            for (int i = 1; i < UAVCurInfos.size(); ++i) {
				if (UAVCurInfos[i]->isArriveStart) {
					if (UAVCurInfos[i]->curPos.z > 0)
						--(UAVCurInfos[i]->curPos.z);
                    else if (UAVCurInfos[i]->curPos.z == 0) {
                        UAVCurInfos[i]->isArriveStart = false;
                    }
				}
				else if (UAVCurInfos[i]->isArriveEnd) {
					if (UAVCurInfos[i]->curPos.z > 0)
						--(UAVCurInfos[i]->curPos.z);
                    else if (UAVCurInfos[i]->curPos.z == 0) {
                        UAVCurInfos[i]->isArriveEnd= false;
                    }
				}
                else if (UAVCurInfos[i]->curPos.z < mapIn.hLow
                         && UAVCurInfos[i-1]->curPos.z - UAVCurInfos[i]->curPos.z > 1)
					++(UAVCurInfos[i]->curPos.z);
				else {

				}
			}

            if(flag == false) {
                flag = true;
                for (int i = 0; i < 2; ++i) {
                    matrixMap.clear();
                    matrixMap.assign(mapIn.xWidth, vector<char>(mapIn.yLength, ' '));
                    matrixMap[mapIn.initUAVs[i].startPos.x][mapIn.initUAVs[i].startPos.y] = 'T';
                    matrixMap[goodsInfos[i]->startPos.x][goodsInfos[i]->startPos.y] = 'G';
                    for (int j = 0; j < mapIn.buildings.size(); ++j) {
                        for (int x = mapIn.buildings[j].startPos.x, xn1 = 0;
                             xn1 < mapIn.buildings[j].len;++x, ++xn1) {
                            for (int y = mapIn.buildings[j].startPos.y, yn1 = 0;
                                 yn1 < mapIn.buildings[j].width;++y, ++yn1)
                                matrixMap[x][y] = 'X';
                        }
                    }
                    InputHandler handler;
                    SquareGraph graph = handler.readMap(matrixMap);
                    vector<Node> path = graph.executeAStar();
                    //graph.printPath(path);
                    paths.emplace_back(path);
                    //getchar();


                    matrixMap[mapIn.initUAVs[i].startPos.x][mapIn.initUAVs[i].startPos.y] = ' ';
                    matrixMap[goodsInfos[i]->startPos.x][goodsInfos[i]->startPos.y] = 'T';
                    matrixMap[goodsInfos[i]->endPos.x][goodsInfos[i]->endPos.y] = 'G';
                    graph = handler.readMap(matrixMap);
                    path = graph.executeAStar();
                    graph.printPath(path);
                    pathsStartToEnd.emplace_back(path);
                    //getchar();
                }
            }
		}
#endif

	}

private:
	MapInfo mapIn;
	InputOutput io;
	int time;
	string token;
    vector<UAVCurInfo*> UAVCurInfos;
    //unordered_map<int, UAVCurInfo*> UAVCurInfos;

	vector<UAVStatus*> UAVStatusWe;
	vector<UAVStatus*> UAVStatusEnemy;

    vector<GoodsInfo*> goodsInfos;
    //unordered_map<int, GoodsInfo*> goodsInfos;

    vector<Route*> routes;

	vector<vector<char>> matrixMap;
	int totalValue;
	int acquireValue;
	
};

#endif // BATTLEAI_H
