#include "../types/General.h"
#include "ClassBase.h"

/*
struct AttributeInfo {
    UShort attribute_name_index;
    UInt attribute_length;
    AttributeInfo(ATTRIBUTEINFO *pattr) {
    }
};
*/

// [ClassName] CodeAttribute
// 存储代码信息的
class CodeAttribute {
public:
    UShort max_stack;
    UShort max_locals;
    UInt code_length;
    UShort attributes_count;

    CodeAttribute() {
    }

    CodeAttribute(CODE* pCode) {
        max_stack = pCode->max_stack;
        max_locals = pCode->max_locals;
        code_length = pCode->code_length;
        attributes_count = pCode->attributes_count;
    }
};
