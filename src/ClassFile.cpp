#include "../include/types/ClassFile.h"

pClass::pClass(class_file* pcf):ACC_PUBLIC(pcf->ACC_PUBLIC), ACC_FINAL(pcf->ACC_FINAL), ACC_SUPER(pcf->ACC_SUPER), ACC_INTERFACE(pcf->ACC_INTERFACE), 
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
    }

int pClass::MakeVirtualTable() {
    vtp = new VirtualTable(this);
    return vtp == NULL;
}

int pClass::MakeStaticMethodTable() {
    smtp = new StaticMethodTable(this);
    return smtp == NULL;
}

~pClass::pClass() {
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
}
pClass::pClass() {

}
UBoolean pClass::is_loaded() {
    return true;
}
