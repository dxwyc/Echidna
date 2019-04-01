template <typename T>
class Dynamic_Array<T> {
    T* array;
    int len;

    Dynamic_Array<T>(){}
    Dynamic_Array<T>(int len){
        this->len = len;
    }
};

