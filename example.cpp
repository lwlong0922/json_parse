#include "json.h"
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