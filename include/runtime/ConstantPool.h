#include <stdio.h>
#include "../types/General.h"
#include "ClassBase.h"
#include <string.h>
#include <ctype.h>

/*
 * Please move from the exit rows if you are unwilling and unable to perform the necessary actions without injury

class ConstantPoolUnit {
    UInt cpool_count;
public:
    ConstantPoolUnit() {
        
    }

    void BuildFromClassBasic(class_attribute* clattr) {
        this->cpool_count = clattr->get_constant_pool_count();
        cpool* ctr = clattr->cpool();
    }
};

*/

class ConstantPool;

class ConstantPoolMetaType {
protected:
    int instance_type;
public:
    int GetInstanceType() {return instance_type;}
    virtual void* GetValue() {return NULL;}
    virtual NAT GetNameAndType() {return "";}
    virtual ~ConstantPoolMetaType() {}
    virtual int resolved(ConstantPool*) {};
};

class ConstantPoolRefType: public ConstantPoolMetaType {
    NAT nat;
    UShort class_index, entry_index;
public:
    ConstantPoolRefType(UShort _class_index, UShort _entry_index, int _instance_type) {
        instance_type = _instance_type; 
        class_index = _class_index;
        entry_index = _entry_index;
        nat = "";
    }

    int resolved(ConstantPool*);
    
    NAT GetNameAndType() {
        if (nat == "") {
            return ""; 
        } 
        return nat;
    }
};

class ConstantPoolValueType: public ConstantPoolMetaType {
    void* value;
public:
    ConstantPoolValueType(void* _value, int _instant_type) {
        instance_type = _instant_type;
        if (instance_type == CONS_FLOAT) 
            value = new float(*(float*)_value);
        else if (instance_type == CONS_DOUBLE) 
            value = new double(*(double*)_value);
        else if (instance_type == CONS_LONG)    
            value = new long(*(long*)_value);
        else if (instance_type == CONS_INTEGER) 
            value = new int(*(int*)_value);
        else if (instance_type == CONS_STRING)
            value = new std::string((char*)_value);
        else if (instance_type == CONS_UTF8)
            value = new NAT(*(NAT*)_value);
        else if (instance_type == CONS_CLASS)
            value = new UShort(*(UShort*)_value);
    }

    ~ConstantPoolValueType() {
        delete value;
    }
    void* GetValue() { return value; }
};

class ConstantPoolNAT: public ConstantPoolMetaType {
    UInt name_index, descriptor_index;
    string nat;
public:
    ConstantPoolNAT(UInt _name_index, UInt _descriptor_index) {
        name_index = _name_index;
        descriptor_index = _descriptor_index;
        nat = "";
    }

    int resolved(ConstantPool* pcp);
    NAT GetNameAndType() {
        return nat;
    }
};

class ConstantPool {
    ConstantPoolMetaType** cpm;
    UShort constant_pool_count;
public:
    ConstantPool(CONSTANT_METATYPE** pcm, UShort ConstantPoolCount) {
        constant_pool_count = ConstantPoolCount;
        cpm = new ConstantPoolMetaType*[constant_pool_count];
        for (int i = 0; i < ConstantPoolCount; i++) {
            auto instype = pcm[i]->get_instance_type();
            if (instype == CONS_METATYPE) throw "ConstantPool can't have any CONS_METATYPE entry!";
            if (instype == CONS_UTF8) {
                cpm[i] = new ConstantPoolValueType(pcm[i]->get_value(), instype); 
            } else if (instype == CONS_INTEGER || instype == CONS_FLOAT || instype == CONS_LONG || instype == CONS_DOUBLE || instype == CONS_STRING) {
                cpm[i] = new ConstantPoolValueType(pcm[i]->get_value(), instype);
            } else if (instype == CONS_CLASS) { // 类的描述符
                cpm[i] = new ConstantPoolValueType(pcm[i]->get_value(), instype);
            } else if (instype == CONS_FIELD || instype == CONS_METHOD || instype == CONS_INTERFACE) {
                std::pair<UShort, UShort>* pus2 = (std::pair<UShort, UShort>*)pcm[i]->get_binary_info();
                cpm[i] = new ConstantPoolRefType(pus2->first, pus2->second, instype);
            } else if (instype == CONS_NAME_TYPE) {
                cpm[i] = new ConstantPoolNAT();
            } else if (instype == CONS_METHOD_HANDLE) {
                // Unimplemented
            } else if (instype == CONS_INVOKE_DYNAMIC) {
                // Unimplemented
            }
        }
    }

    ~ConstantPool() {
        if (cpm != NULL) {
            for (int i=1; i<constant_pool_count; i++) 
                if (cpm[i] != NULL) delete cpm[i];
            delete[] cpm;
        }
    }

    ConstantPoolMetaType* GetConstantPoolItem(int index) {
        assert(index >= 1 && index < constant_pool_count);
        return cpm[index];
    }
};

int ConstantPoolRefType::resolved(ConstantPool* pcp) { // resolve the index form into string form 
    auto* pci = pcp->GetConstantPoolItem(class_index);
    auto* pei = pcp->GetConstantPoolItem(entry_index);
    if (pci == NULL || pei == NULL)
        return 0;
    if (pci->GetValue() == NULL || pei->GetValue() == NULL) // 无法获得字符串
        return 0;
    UInt utf8_index = *(UInt*)pci->GetValue();
    auto* pui = pcp->GetConstantPoolItem(utf8_index);
    if (pui == NULL || pui->GetValue() == NULL) return 0;
    this->nat = *(NAT*)pui->GetValue() + "." + pei->GetNameAndType();
    return 1;
}

int ConstantPoolNAT::resolved(ConstantPool* pcp) {
    auto* pci = pcp->GetConstantPoolItem(name_index);
    auto* pei = pcp->GetConstantPoolItem(descriptor_index);

    if (pci == NULL || pei == NULL)
        return 0;
    if (pci->GetValue() == NULL || pei->GetValue() == NULL) // 无法获得字符串
        return 0;

    this->nat = *(NAT*)pci->GetValue() + ":" + *(NAT*)pei->GetValue();
    return 1;
}
