#include "General.h"
// 设计思路是，每个Object存着所有该类的字段信息，具体解析流程通过句柄对应的类型数据解析
// 比如 通过某句柄对象解析出 pClass -> getFieldInformation(name_and_type) => 对应在Object里的编号 pObjIndex
// Object pObj->getIndex2Field(int index) => void*
//
// [ClassName] Object
// This class is mainly used for Heap Object Arrangement

using PObj = void *;

class Object {
    PObj* fields;
    UInt fieldCount;
public:
    Object():fields(NULL);
    Object(UInt field_count) {
        fieldCount = field_count;
        fields = new PObj[fieldCount];
    }

    ~Object() {
        if (fields != NULL)
            for (auto i = 0; i < fieldCount; i++)
                delete[] (char*)fields[i];
            delete[] fields;
    }

    void createAs(pClass* pkl) {
        for (auto i = 0; i < pkl->field_count; i++) {
            fields[i] = new char[pkl->arrField[i]->GetByte()];
        }
    }

    PObj getIndex2Field(int index) {
        try {
            if (index < 0 || index >= fieldCount)
                throw "[Object] Exceeded index!";
            return fields[index];
        } catch {
            return NULL;
        }
    }

    void fillFields(int index, void* content) {
        fields[index] = content;
    }
};


