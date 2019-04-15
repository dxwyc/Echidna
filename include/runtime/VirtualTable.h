#include "MethodPool.h"
#include <map>
#include <string>
using std::string;
using std::map;

// [ClassName] VirtualTable
// 存放类的虚函数表，以供invokevirtual指令运行
// nameMap: 每一个全限定名对应着一个项
// 
class VirtualTable {
    using MapContainerType = map<string, int>;
    using ContainerType = std::vector<MethodEntry*>;

    MapContainerType nameMap;
    ContainerType entryList;
public:
    VirtualTable(pClass* pkl);
   /* 
        if (pkl==NULL) throw "Cannot create virtual tables for NULL!";

        VirtualTable* vtpFatherClass = NULL;

        if (pkl->pFatherClass != NULL) {
            vtpFatherClass = pkl->pFatherClass->vtp;
            // 对父类虚函数表的深度拷贝
            for (auto it : vtpFatherClass->entryList) 
                entryList.append(it)
            for (auto it : vtpFatherClass->nameMap)
                nameMap[it.first] = it.second
        }

        // 处理类中重写的虚函数
        for (int i = 0; i < pkl->method_count; i++) {
            
            auto* it = pkl->arrMethod[i];
            if (it->GetAccessFlags("ACC_STATIC")) // 静态方法不能添加进虚函数表
                continue;
            if (it->GetAccessFlags("ACC_PRIVATE")) // 针对private修饰的函数不支持多态，不能将其放入函数表中
                continue;

            // 重写父类虚函数或者是子类新增虚函数
            // string nat = pkl->GetConstantPoolItem((*it)->GetNameIndex())+pkl->GetConstantPoolItem((*it)->GetTypeIndex());
            auto nat = it->GetNameAndType();

            if (nameMap.count(nat)) {
                entryList[nameMap[nat]] = it; // 子类对象的重写
            } else {
                entryList.append(it);
                nameMap[nat] = entryList.length() - 1; // 新增虚函数的增加
            }
        }
    }
    */
    MethodEntry* GetVirtualEntry(string nat) { // nat for NameAndType
        if (!nameMap.count(nat)) return NULL;
        return entryList[nameMap[nat]];
    }
};
