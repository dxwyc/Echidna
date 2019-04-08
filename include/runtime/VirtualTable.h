#include "MethodPool.h"
#include "../types/ClassFile.h"
#include <map>
#include <string>
using std::string;
using std::map;

// [ClassName] VirtualTable
// 存放类的虚函数表，以供invokevirtual指令运行
class VirtualTable {
    VirtualTable* vtpFatherClass;
    ContainerType nameMap;
public:
    using ContainerType = map<string, int>;
    VirtualTable(pClass* pkl) {
        if (pkl==NULL) throw "Cannot create virtual tables for NULL!";
        if (pkl->pFatherClass == NULL) vtpFatherClass = NULL;
        else vtpFatherClass = pkl->pFatherClass->vtp;

        for (auto it = pkl->arrMethodResPos.begin(); it != pkl->arrMethodResPos.end(); it++) {
            
        }
    }
};