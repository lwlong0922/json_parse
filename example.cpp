#include "json.h"
//[
//	{
//		"nId": 2001,
//		"strName" : "药水哥",
//		"nBirthRow" : 8,
//		"nBirthCol" : 8,
//		"nMapId" : 1001,
//		"strPic" : "药",
//		"nType" : 0
//	},
//	{
//		"nId": 2002,
//		"strName" : "武器大师",
//		"nBirthRow" : 8,
//		"nBirthCol" : 9,
//		"nMapId" : 1001,
//		"strPic" : "武",
//		"nType" : 0
//	}
//]
void loadFile(const string &strPath)
{   
    //传入路径，生成适配器
    auto jba = new JsonAdapter(strPath);
    //拿到json对象
    auto jb = jba->getJsonObject();

    //getArraySize(): 拿到json对象的array的大小
    //operator[] 拿到json对象中array的json对象
    //getObject(key_value); 拿到对象
    //getInteger(key_value)； 拿到整数
    //getBool(key_value)；拿到bool
    //getDouble(key_value): 拿到复数
    //getString(key_value)：拿到字符串

    //拿到对象例子
    // jb[0].getObject("friend");
    for (int i = 0; i < jb.getArraySize(); i++)
    {
        auto cDt = new CNpcDt();
        cDt->nId = jb[i].getInteger("nId");
        cDt->nBirthRow = jb[i].getInteger("nBirthRow");
        cDt->nBirthCol = jb[i].getInteger("nBirthCol");
        cDt->nMapId = jb[i].getInteger("nMapId");
        cDt->strName = jb[i].getString("strName");
        cDt->strPic = jb[i].getString("strPic");
        m_vecDatas.push_back(cDt);
    }
}






//[
//{
//	"nId": 1001,
//		"strName" : "新手村",
//		"nMaxRow" : 20,
//		"nMaxCol" : 15,
//		"nBirthRow" : 5,
//		"nBirthCol" : 5,
//		"transfer" : [
//	{
//		"nRow": 11,
//			"nCol" : 10,
//			"nextId" : 1002
//	}
//		]
//},
//{
//	"nId": 1002,
//	"strName" : "高手村",
//	"nMaxRow" : 20,
//	"nMaxCol" : 15,
//	"nBirthRow" : 1,
//	"nBirthCol" : 1,
//	"transfer" : [
//	{
//		"nRow": 11,
//			"nCol" : 10,
//			"nextId" : 1001
//	},
//	{
//		"nRow": 4,
//		"nCol" : 4,
//		"nextId" : 1003
//	}
//	]
//}
//]
void CMapDtMgr::loadFile(const string& strPath)
{
	auto aj = new JsonAdapter(strPath);
	auto ab = aj->getJsonObject();
	for(int i = 0; i < ab.getArraySize(); i++)
	{
		auto mapDt = new CMapDt();
		mapDt->nId = ab[i].getInteger("nId");
		mapDt->nMaxRow = ab[i].getInteger("nMaxRow");
		mapDt->nMaxCol = ab[i].getInteger("nMaxCol");
		mapDt->nBirthRow = ab[i].getInteger("nBirthRow");
		mapDt->nBirthCol = ab[i].getInteger("nBirthCol");
		mapDt->strName = ab[i].getString("strName");
		mapDt->pArrMap = new int *[mapDt->nMaxRow];
		for(int j = 0; j < mapDt->nMaxRow; j++)
		{
			mapDt->pArrMap[j] = new int[mapDt->nMaxCol];
		}
		for(int j = 0; j < mapDt->nMaxRow; j++)
		{
			for(int k = 0; k < mapDt->nMaxCol; k++)
			{
				if(j == 0 || k == 0 || j == mapDt->nMaxRow - 1 || k == mapDt->nMaxCol - 1)
					mapDt->pArrMap[j][k] = 1;
				else
					mapDt->pArrMap[j][k] = 0;
			}
		}
		auto nextObj = ab[i].getObject("transfer");
		for(int j = 0; j < nextObj.getArraySize(); j++)
		{
			int nRow = nextObj[j].getInteger("nRow");
			int nCol = nextObj[j].getInteger("nCol");
			int nextId = nextObj[j].getInteger("nextId");
			mapDt->pArrMap[nRow][nCol] = nextId;
		}

		m_vecDatas.push_back(mapDt);
	}
}

