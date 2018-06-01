#include "battleAI.h"
#include "inputOutput.h"

int main(int argc, char **argv)
{
//    Json::Value rot11, rot12, rot1;
//    rot11["x"] = Json::Value(3);
//    rot11["y"] = Json::Value(4);

//    rot12["x"] = Json::Value(8);
//    //rot12["y"] = Json::Value(9);
//    rot1["cordinate"][0] = rot11;
//    rot1["cordinate"][1] = rot12;
//    cout << rot1["cordinate"][1]["y"].asInt() << endl;


    BattleAI battle;
    battle.linkToTheServer(argv[1], argv[2], argv[3]);
    Json::Value root = battle.firstLinkToTheServer();
    Json::FastWriter fwrite;
    //cout << fwrite.write(root).size() << endl;
    battle.identifyToTheServer();
    root = battle.identifyServerToClient();
    battle.identifyToTheServerReady();
    //cout << root.toStyledString();
    battle.startBattleServerToClient();
    battle.startBattle();
}
