#include "MethodPool.h"
#include <map>
#include <string>
using std::string;
using std::map;

// [ClassName] StaticMethodTable
// 处理所有静态函数和私有函数

class StaticMethodTable {
    using MapContainerType = map<string, int>;
    using ContainerType = vector<MethodEntry*>;

    MapContainerType nameMap;
    ContainerType entryList;
public:
    StaticMethodTable(pClass* pkl) {
        for (int i=0; i<pkl->method_count; i++) {
            auto *it = pkl->arrMethod[i];
            if (it->GetAccessFlags("ACC_STATIC") || it->GetAccessFlags("ACC_PRIVATE")) {
                entryList.append();
                nameMap[it->GetNameAndDescriptor()] = entryList.length() - 1;
            }
        }
    }

    MethodEntry* GetStaticMethodEntry(string nat) {
        if (nameMap.count(nat)) 
            return entryList[nameMap[nat]];
        return NULL; // 返回NULL，使得Resolve从父类继续解析
    }
};
