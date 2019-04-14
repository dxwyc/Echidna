#include "../include/types/ClassLoader.h"

// ClassLoader::Loader 流程
// 1)  将类信息文件的常量池信息载入常量池
// 2)  将方法载入方法区,并处理出非虚函数表和虚函数表
// 3)  将字段表信息载入方法区
// 4)  创建该类对应的pClass对象，设置堆中句柄对象和实例对象的映射关系

namespace ClassLoader {
    int LoadClass(class_attribute* pkla) {
        int res_pos = -1;
        pClass *pkl = NULL;
        for (int i = 0; i < ClassLoader::MAX_CONSTANTPOOL_COUNT; i++)
            if (ClassLoader::arrLoadedClass[i] == NULL) { res_pos = i;
                break;
            }

        if (res_pos < 0) {
            throw "ClassLoader can't load any more class right now!";
            return 0;
        }

        pkl = pClass(pkla);

        ClassLoader::arrLoadedClass[res_pos] = pkl;
        ClassLoader::nameMap[pkla->get_class_name(pkl->this_class)] = res_pos;
        pkl->is_loaded = true;

        return 1;
    }
    
    pClass* findLoadedClass(string class_name) {
        if (ClassLoader::nameMap.count(class_name)) 
            return ClassLoader::arrLoadedClass[ClassLoader::nameMap[class_name]];
        return NULL;
    }
}
