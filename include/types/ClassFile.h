#include "../runtime/VirtualTable.h"
#include "../runtime/ClassBase.h"
#include "../runtime/ConstantPool.h"
#include "ClassLoader.h"
#include <assert.h>

// [ClassName] pClass
// 解析后的类存放地址

class pClass {
    UBoolean is_loaded;
public:
    VirtualTable* vtp;
    StaticMethodTable* smtp; // 针对类中所有的静态函数的Table

    pClass* pFatherClass;
    MethodEntry** arrMethod; // 类中所有函数的对应MethodEntry*
    FieldEntry** arrField;
    ConstantPool* pcp;

    ConstantPoolMetaType* GetConstantPoolItem(int pl_index) {return pcp->GetConstantPoolItem(pl_index);}

    bool ACC_PUBLIC;
    bool ACC_FINAL;
    bool ACC_SUPER;
    bool ACC_INTERFACE;
    bool ACC_ABSTRACT;
    bool ACC_SYNTHETIC;
    bool ACC_ANNOTATION;
    bool ACC_ENUM;

    UInt magic;
    UShort minor_version;
    UShort major_version;
    UShort this_class;
    UShort constant_pool_count;

    UShort field_count;
    UShort method_count;

    pClass();
    pClass(class_file*);
    /*
    pClass(class_file* pcf):ACC_PUBLIC(pcf->ACC_PUBLIC), ACC_FINAL(pcf->ACC_FINAL), ACC_SUPER(pcf->ACC_SUPER), ACC_INTERFACE(pcf->ACC_INTERFACE), 
        ACC_ABSTRACT(pcf->ACC_ABSTRACT), ACC_SYNTHETIC(pcf->ACC_SYNTHETIC), ACC_ANNOTATION(pcf->ACC_ANNOTATION), ACC_ENUM(pcf->ACC_ENUM) {
            magic = pcf->magic;
            minor_version = pcf->minor_version;
            major_version = pcf->major_version;
            this_class = pcf->this_class;
            constant_pool_count = pcf->constant_pool_count;

            field_count = pcf->field_count;
            method_count = pcf->method_count;

            arrMethod = new MethodEntry*[method_count];

            for (auto k = method_count - 1; k >= 0; k--) {
                METHODINFO *pmi = pcf->method_info[k];
                arrMethod[k] = new MethodEntry(pmi, pcf);
            }

            for (auto k = field_count - 1; k >= 0; k--) {
                FIELDINFO *pfi = pcf->field_info[k];
                arrField[k] = new FieldEntry(pfi, pcf);
            }

            pFatherClass = ClassLoader::findLoadedClass(pcf->get_class_name(pcf->parent_index)); // 尝试获取父类 
            assert(pFatherClass != NULL); // 父类必须存在

            if (!pFatherClass->is_loaded()) {
                if (!ClassLoader::LoadClass(pFatherClass))
                    throw "Can't load father class into runtime environment.";
                // Load Father Class
            }

            // Load This Class.
            if (!ClassLoader::LoadClass(this)) {
                throw "Can't load this class into runtime environment.";
            }
    }*/

    int MakeVirtualTable() ;/*{
        vtp = new VirtualTable(this);
        return vtp == NULL;
    }
*/
    int MakeStaticMethodTable();/* {
        smtp = new StaticMethodTable(this);
        return smtp == NULL;
    }
*/
    ~pClass(); /* {
        if (vtp != NULL) delete vtp;
        if (smtp != NULL) delete smtp;
        if (arrMethod != NULL) { 
            for (auto k = method_count - 1; k >= 0; k--) 
                if (arrMethod[k] != NULL) delete arrMethod[k];
            delete[] arrMethod;
        } 
        if (arrField != NULL) {
            for (auto k = field_count - 1; k >= 0; k--)
                if (arrField[k] != NULL) delete arrField[k];
            delete[] arrField;
        }
    }*/

    UBoolean is_loaded();
};
