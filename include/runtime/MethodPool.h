#include <memory>
#include <vector>
#include <stack>
#include "../types/General.h"
#include "Attribute.h"

// [ClassName] PureCode
// 纯十六进制的方法区代码存储
class PureCode {
    HexCode* pData;
    UInt code_length;
    UShort current_pos;
    // CodeAttribute code_attribute; // 其他属性

    UShort max_stack;
    UShort max_locals;
    UInt code_length;
    UShort attributes_count;
public:
	PureCode():code_length(0), current_pos(0) {pData = NULL;}
    PureCode(CODE* pCode) {
        pData = new HexCode[_codeLength + 1];
        current_pos = 0;

        max_stack = pCode->max_stack;
        max_locals = pCode->max_locals;
        code_length = pCode->code_length;
        attributes_count = pCode->attributes_count;

        for (auto x = 0; x < code_length; x++)
            *(pData+x) = *(pCode->code+x);
    }

    UShort GetMaxStack() {return max_stack;}
    UShort GetMaxLocals() {return max_locals;}
    UInt GetCodeLength() {return code_length;}

    ~PureCode() {delete[] pData;}

    HexCode GetNextCode() {
        try {
            if (current_pos + 1 >= code_length)
                throw "Access denied! The hex code read exceeds the maximum length.";
            return *(pData+(current_pos++));
        } catch (char *error_info) {
#ifdef DEBUG_CLASS
            cout << error_info << endl;
#endif
        }
    }

    void SetCurrentPos(UShort index) {
        try {
            if (index >= code_length)
                throw "Access denied! The hex code read exceeds the maximum length.";
            else if (index < 0) 
                throw "Access denied! The index can't be negative!";
            current_pos = index;
        } catch (char *error_info) {
#ifdef DEBUG_CLASS
            cout << error_info << endl;
#endif
        }
    }

    HexCode GetCurrentPos() const {
        return current_pos;
    }
    
    HexCode GetIndexCode(UShort index) const{
        try {
            if (index >= code_length)
                throw "Access denied! The hex code read exceeds the maximum length.";
            else if (index < 0) 
                throw "Access denied! The index can't be negative!";
            return *(pData+index);
        } catch (char *error_info) {
#ifdef DEBUG_CLASS
            cout << error_info << endl;
#endif
        }
    }
};

// [ClassName] PureCodePool
// 管理PureCode用的索引结构
class PureCodePool {
public:
    using DataType = PureCode*;
    using PureContainer = std::vector<PureCode*>;
    using PureVacantIndexContainer = std::stack<UInt>;
    PureCodePool(UInt poolLength) {
        CodePool.resize(poolLength);
        PoolLength = poolLength;
        for (auto k = poolLength - 1; k >= 1; k--) {
            VacantIndexStack.push(k);
        }
    }

    UInt Reserve(CODE* pCode) { // UInt _codeLength, UBytePtr _codeString) {
        if (VacantIndexStack.empty()) // 分配PureCode失败
            return 0;
        UInt reserved_slot = VacantIndexStack.top();
        VacantIndexStack.pop();
        CodePool[reserved_slot] = new PureCode(pCode); //_codeLength, _codeString);
        return reserved_slot;
    }

    DataType Access(UInt access_slot) {
        try {
            if (access_slot >= PoolLength)
                throw "[PureCodePool] Invalid Access!";
            return CodePool[access_slot];
        } catch (char *error_info) {
#ifdef DEBUG_CLASS
            cout << error_info << endl;
#endif
            return NULL;
        }        
    }

    // [MethodName] PureCodePool::Release
    // 返回是否释放成功
    StatusCode Release(UInt released_slot) {
        if (CodePool[released_slot] == NULL)
            return 0;

        delete CodePool[released_slot];
        VacantIndexStack.push(released_slot);
        return 1;
    }

    ~PureCodePool() {
        for (auto k = 0; k < PoolLength; k++)
            Release(k);
    }
private:
    PureContainer CodePool;
    UInt PoolLength;
    PureVacantIndexContainer VacantIndexStack;
} GenCodePool(100);

class MethodEntry {
    bool ACC_PUBLIC;
    bool ACC_PRIVATE;
    bool ACC_PROTECTED;
    bool ACC_STATIC;
    bool ACC_FINAL;
    bool ACC_SYNCHRONIZED;
    bool ACC_BRIDGE;
    bool ACC_VARARGS;
    bool ACC_NATIVE;
    bool ACC_ABSTRACT;
    bool ACC_STRICTFP;
    bool ACC_SYNTHETIC;

    NAT name;
    NAT descriptor;
    NAT name_and_descriptor;

    UShort attribute_count;
    UInt   method_res_pos;
public:
    bool GetAccessFlags(string flag) {
        switch (flag) {
            case "ACC_STATIC":
                return ACC_STATIC;
            case "ACC_FINAL":
                return ACC_FINAL;
            case "ACC_PUBLIC":
                return ACC_PUBLIC;
            case "ACC_PRIVATE":
                return ACC_RPIVATE;
            case "ACC_ABSTRACT":
                return ACC_ABSTRACT;
            case "ACC_NATIVE":
                return ACC_NATIVE;
            default:
                return 0;
        }
    }

    MethodEntry() {}

    MethodEntry(METHODINFO* pmi, class_info* pkl) {
        ACC_PUBLIC = pmi->ACC_PUBLIC;
        ACC_PRIVATE = pmi->ACC_PRIVATE;
        ACC_PROTECTED = pmi->ACC_PROTECTED;
        ACC_STATIC = pmi->ACC_STATIC;
        ACC_FINAL = pmi->ACC_FINAL;
        ACC_SYNCHRONIZE = pmi->ACC_SYNCHRONIZE
        ACC_BRIDGE = pmi->ACC_BRIDGE;
        ACC_VARARGS = pmi->ACC_VARARGS;
        ACC_NATIVE = pmi->ACC_NATIVE;
        ACC_ABSTRACT = pmi->ACC_ABSTRACT;
        ACC_STRICTFP = pmi->ACC_STRICTFP;
        ACC_SYNTHETIC = pmi->ACC_SYNTHETIC; 

        auto info = pmi->get_info(pkl);

        name = info.first
        descriptor = info.second;

        name_and_descriptor = name + descriptor; 

        attribute_count = pmi->attribute_count;
        method_res_pos = GenCodePool.Reserve(pmi->attributes[pmi->get_code_index()]); //pmi->get_code_length(), pmi->get_code());
    }
    
    NAT GetName() {return name;}
    NAT GetDescriptor() {return descriptor;}
    NAT GetNameAndDescriptor() {return name_and_descriptor;}

    UInt GetMethodResPos() { return method_res_pos; }
};
