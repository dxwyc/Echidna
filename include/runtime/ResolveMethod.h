#include "../types/ClassFile.h"

// 无法解析静态函数
MethodEntry* FindStaticMethod(pClass* pkl, string nat) {
    MethodEntry* pret=NULL;
    while (pkl != NULL) {
        pret = pkl->smtp->GetStaticMethodEntry(nat);
        if (pret != NULL)
            return pret;
        pkl = pkl->pFatherClass;
    } 
    return NULL;
}

MethodEntry* FindVirtualMethod(pClass* pkl, string nat) {
    MethodEntry* pret = NULL;

    if (pkl == NULL) throw "Current Class Can't Be NULL!";
    if (pkl->vtp == NULL) throw "Loaded Class Can't Have No Virtual Table!";

    pret = pkl->vtp->GetVirtualEntry(nat);
    if (pret != NULL) return pret;
    
    throw "Fail to get the corresponding form of the specified virtual function.";
    return NULL;
}
