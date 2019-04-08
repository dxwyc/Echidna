#include <memory>
#include <vector>
#include <stack>
#include "../types/General.h"

// [ClassName] CodeAttribute
// 存储代码信息的
class CodeAttribute {
    UShort max_stack;
    UShort max_local;
    UInt code_length;
    UShort attributes_count;
public:
    CodeAttribute() {
    }
};

// [ClassName] PureCode
// 纯十六进制的方法区代码存储
class PureCode {
    HexCode* pData;
    UInt code_length;
    UShort current_pos;
    CodeAttribute code_attribute; // 其他属性
public:
	PureCode():code_length(0), current_pos(0) {pData = NULL;}
    PureCode(UInt _codeLength, UBytePtr _codeString):code_length(_codeLength) {
        pData = new HexCode[_codeLength + 1];
        current_pos = 0;
        for (auto x = 0; x < code_length; x++)
            *(pData+x) = *_codeString++;
    }

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
        PoolLength = PoolLength;
        for (auto k = poolLength - 1; k >= 1; k--) {
            VacantIndexStack.push(k);
        }
    }

    UInt Reserve(UInt _codeLength, UBytePtr _codeString) {
        if (VacantIndexStack.empty()) // 分配PureCode失败
            return 0;
        UInt reserved_slot = VacantIndexStack.top();
        VacantIndexStack.pop();
        CodePool[reserved_slot] = new PureCode(_codeLength, _codeString);
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

