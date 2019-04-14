// 这个文件主要实现将静态数据结构加载为虚拟机的运行时数据结构
// 并处理出每个类对应的字段表和虚函数表,以实现多态功能

#include "ClassFile.h"
#include <map>
#include <string>

namespace ClassLoader {

    map<string, int> nameMap;
    
    const int MAX_LOADED_CLASSNUM = 1000;
    pClass* arrLoadedClass[MAX_LOADED_CLASSNUM];  
    
    int LoadClass(class_attribute*); 
    pClass* findLoadedClass(string class_name);
}


