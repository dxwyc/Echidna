#include "Heap.h"
/*
 * [ClassName] HeapHandleUnit
 * 堆句柄类主要用于常量池中的直接引用与堆中实例数据堆连接过程 
 * 方便在之后进行垃圾回收的时候
 */
class HeapHandleUnit {
    HeapUnit* pInstance;
    pClass* pkl;
public:
    HeapHandle(){pInstance=pkl=NULL;}
    HeapHandle(HeapUnit* _obj, pClass* _pkl):pInstance(_obj), pkl(_pkl) {}
};

/*
 * [ClassName] HeapHandlePool
 * 管理所有HeapHandleUnit 
 */
class HeapHandlePool {
    HeapHandleUnit* hhu[MAX_HEAPHANDLE_POOL];
    const static int MAX_HEAPHANDLE_POOL = 100000;
public:
    HeapHandlePool() {}
    HeapHandlePool(int); 
    HeapHandleUnit* retriveOneHanle();
    HeapHandleUnit* retriveSeveralHandle();

};
