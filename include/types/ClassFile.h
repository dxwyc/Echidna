#include "../runtime/VirtualTable.h"

// [ClassName] pClass
// 解析后的类存放地址

class pClass {
    UInt cpool_res_pos;
    VirtualTable* vtp;
    pClass* pFatherClass;
    vector<UInt> arrMethodResPos;
public:
    pClass() {}
};