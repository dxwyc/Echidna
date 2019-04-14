#include "../include/runtime/ClassBase.h"

class CONSTANT_METATYPE{
public:
    virtual types get_instance_type(){
        return CONS_METATYPE;
    }
    virtual void* get_value(){return NULL; }
    virtual void* get_name_index(){return NULL;}
    virtual void* get_binary_info(){return NULL;}
};

class CONSTANT_utf8: public CONSTANT_METATYPE{
public:
    int length;
    string str;
    CONSTANT_utf8(int _length, string utf8):length(_length){
        str = utf8;
    }
    types get_instance_type() {
        return CONS_UTF8;
    }
    void* get_value(){
        return &str;
    }
};

class CONSTANT_integer: public CONSTANT_METATYPE{
public:
    int value;
    CONSTANT_integer(int _value):value(_value){}
    types get_instance_type() {
        return CONS_INTEGER;
    }
    void* get_value(){return &value;}
};

class CONSTANT_float: public CONSTANT_METATYPE{
public:
    float value;
    CONSTANT_float(float _value):value(_value){}
    types get_instance_type() {
        return CONS_FLOAT;
    }
    void* get_value(){return &value;}
};

class CONSTANT_long: public CONSTANT_METATYPE{
public:
    long value;
    CONSTANT_long(long _value):value(_value){}
    virtual types get_instance_type() {
        return CONS_LONG;
    }
    void* get_value(){return &value;}
};

class CONSTANT_double: public CONSTANT_METATYPE{
public:
    double value;
    CONSTANT_double(double _value):value(_value){}
    virtual types get_instance_type() {
        return CONS_DOUBLE;
    }
    void* get_value(){return &value;}
};

class CONSTANT_class: public CONSTANT_METATYPE{
public:
    int name_index;
    CONSTANT_class(int _value):name_index(_value){}
    types get_instance_type() {
        return CONS_CLASS;
    }
    void* get_value(){
        return &name_index;
    }
};

class CONSTANT_string: public CONSTANT_METATYPE{
public:
    int utf8_index;
    CONSTANT_string(int _value):utf8_index(_value){}
    virtual types get_instance_type() {
        return CONS_STRING;
    }
};

class CONSTANT_fieldref: public CONSTANT_METATYPE{
public:
    ushort class_index;
    ushort name_type_index;
    CONSTANT_fieldref(ushort _class, ushort _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_FIELD;
    }
    void* get_binary_info(){
        pair<ushort, ushort>* t = new pair<ushort, ushort>(class_index, name_type_index);
        return t;
    }
};

class CONSTANT_methodref: public CONSTANT_METATYPE{
public:
    ushort class_index;
    ushort name_type_index;
    CONSTANT_methodref(int _class, int _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_METHOD;
    }
    void* get_binary_info(){
        pair<ushort, ushort>* t = new pair<ushort, ushort>(class_index, name_type_index);
        return t;
    }
};

class CONSTANT_interface: public CONSTANT_METATYPE{
public:
    ushort class_index;
    ushort name_type_index;
    CONSTANT_interface(int _class, int _name_type):class_index(_class), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONS_INTERFACE;
    }
    void* get_binary_info(){
        pair<ushort, ushort>* t = new pair<ushort, ushort>(class_index, name_type_index);
        return t;
    }
};

class CONSTANT_name_type: public CONSTANT_METATYPE{
public:
    ushort name_index;
    ushort descriptor_index;
    CONSTANT_name_type(int _name, int _descriptor):name_index(_name), descriptor_index(_descriptor){}
    virtual types get_instance_type() {
        return CONS_NAME_TYPE;
    }
    void* get_binary_info(){
        pair<ushort, ushort>* t = new pair<ushort, ushort>(name_index, descriptor_index);
        return t;
    }
};

class CONSTANT_method_handle: public CONSTANT_METATYPE{
public:
    ushort reference_kind;
    ushort reference_index;
    CONSTANT_method_handle(int _kind, int _index):reference_kind(_kind), reference_index(_index){}
    virtual types get_instance_type() {
        return CONS_METHOD_HANDLE;
    }
    void* get_binary_info(){
        pair<ushort, ushort>* t = new pair<ushort, ushort>(reference_kind, reference_index);
        return t;
    }
};

class CONSTANT_method_type: public CONSTANT_METATYPE{
public:
    int descriptor_index;
    CONSTANT_method_type(int _descriptor):descriptor_index(_descriptor){}
    virtual types get_instance_type() {
        return CONS_METHOD_TYPE;
    }
};

class CONSTANT_invoke_dynamic: public CONSTANT_METATYPE{
public:
    int bootstrap_index;
    int name_type_index;
    CONSTANT_invoke_dynamic(int _boostrap, int _name_type):bootstrap_index(_boostrap), name_type_index(_name_type){}
    virtual types get_instance_type() {
        return CONSTANT_INVOKE_DYNAMIC;
    }
};

types FIELDINFO::get_permission(){
    if (ACC_PUBLIC) return PUBLIC;
    else if (ACC_PRIVATE) return PRIVATE;
    else return PROTECTED;
}

FIELDINFO::FIELDINFO(int access_flags, int name_index, int descriptor_index, int attributes_count){
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes_count = attributes_count;
    this->ACC_PUBLIC = access_flags & 1;
    this->ACC_PRIVATE = access_flags & 2;
    this->ACC_PROTECTED = access_flags & 4;
    this->ACC_STATIC = access_flags & 8;
    this->ACC_FINAL = access_flags & 0x10;
    this->ACC_VOLATILE = access_flags & 0x40;
    this->ACC_TRANSIENT = access_flags & 0x80;
    this->ACC_SYNTHETIC = access_flags & 0x1000;
    this->ACC_ENUM = access_flags & 0x4000;
#ifdef DEBUG
    if (ACC_PUBLIC)
        printf("PUBLIC\n");
    else if (ACC_PRIVATE)
        printf("PRIVATE\n");
    else if (ACC_PROTECTED)
        printf("PROTECTED\n");
#endif
}

void** ATTRIBUTEINFO::get_attributes(){return NULL;}
types ATTRIBUTEINFO::get_instance_type() { return ATTR_META; }
uchar* ATTRIBUTEINFO::get_code(){return NULL;}
ushort ATTRIBUTEINFO::get_length(){return 0;}
ATTRIBUTEINFO::ATTRIBUTEINFO(ushort index, ushort length):attribute_name_index(index), attribute_length(length){}

CODE::CODE(ushort ani, uint al, ushort ms, ushort ml, uint cl, uchar *cd, ushort etl, ushort ac):ATTRIBUTEINFO(ani, al), max_stack(ms), max_locals(cl), code_length(cl), exception_table_length(etl), attributes_count(ac){
    attributes = new ATTRIBUTEINFO* [ac];
    exception_table = new EXCEPTIONINFO* [etl];
    code = cd;
}
void** CODE::get_attributes(){return (void**)attributes;}
types CODE::get_instance_type(){ return ATTR_CODE; }
uchar* CODE::get_code(){return code;}
ushort CODE::get_length(){return code_length;}


class LINENUMBERINFO{
public:
    ushort start_pc;
    ushort line_number;
    LINENUMBERINFO(ushort s, ushort l):start_pc(s), line_number(l){}
};

class LINENUMBERTABLE: public ATTRIBUTEINFO{
public:
    ushort line_number_table_length;
    LINENUMBERINFO** line_number_table;
    void** get_attributes(){ return (void**)line_number_table; }
    types get_instance_type(){return ATTR_LINENUMBER;}
    ushort get_length(){return line_number_table_length;}
    LINENUMBERTABLE(ushort ani, uint al, ushort lntl):ATTRIBUTEINFO(ani, al), line_number_table_length(lntl){
        line_number_table = new LINENUMBERINFO* [lntl+1];
    }
};

class SOURCEFILE: public ATTRIBUTEINFO{
public:
    ushort source_file_index;
    types get_instance_type(){return ATTR_SOURCEFILE;}
    SOURCEFILE(ushort s, ushort l, ushort index):ATTRIBUTEINFO(s, l), source_file_index(index){}
};

METHODINFO::METHODINFO(int access_flags, int name_index, int descriptor_index, int attributes_count){
    this->name_index = name_index;
    this->descriptor_index = descriptor_index;
    this->attributes_count = attributes_count;
    this->ACC_PUBLIC = access_flags & 1;
    this->ACC_PRIVATE = access_flags & 2;
    this->ACC_PROTECTED = access_flags & 4;
    this->ACC_STATIC = access_flags & 8;
    this->ACC_FINAL = access_flags & 0x10;
    this->ACC_SYNCHRONIZED = access_flags & 0x20;
    this->ACC_BRIDGE = access_flags & 0x40;
    this->ACC_VARARGS = access_flags & 0x80;
    this->ACC_NATIVE = access_flags & 0x100;
    this->ACC_ABSTRACT = access_flags & 0x400;
    this->ACC_STRICTFP = access_flags & 0x800;
    this->ACC_SYNTHETIC = access_flags & 0x1000;
    this->attributes = new ATTRIBUTEINFO* [attributes_count+1];
#ifdef DEBUG
    if (ACC_PUBLIC)
        printf("PUBLIC\n");
    else if (ACC_PRIVATE)
        printf("PRIVATE\n");
    else if (ACC_PROTECTED)
        printf("PROTECTED\n");
#endif
}

types METHODINFO::get_permission(){
    if (ACC_PUBLIC) return PUBLIC;
    else if (ACC_PRIVATE) return PRIVATE;
    else return PROTECTED;
}

pair<string,string> METHODINFO::get_info(class_attribute* cl){
    pair<string,string> info = cl->get_info(name_index, descriptor_index);
    return info;
}

uchar* METHODINFO::get_code(){
    // Here we assert only one "CODE" attributes appear in a method.
    for (int i = 0; i < attributes_count; i ++){
        types T = attributes[i]->get_instance_type();
        if (T == ATTR_CODE){
            return attributes[i]->get_code();
        }
    }
    return NULL;
}

ushort METHODINFO::get_code_length(){
    for (int i = 0; i < attributes_count; i ++){
        types T = attributes[i]->get_instance_type();
        if (T == ATTR_CODE){
            return attributes[i]->get_length();
        }
    }
    return 0;
}

ushort METHODINFO::get_code_index(){
    for (int i = 0; i < attributes_count; i ++){
        types T = attributes[i]->get_instance_type();
        if (T == ATTR_CODE){
            return i;
        }
    }
    return 0;
}

pair<string, string> class_attribute::get_info(int name, int descriptor){
    string s1 = *(string*)this->constant_pool[name]->get_value();
    string s2 = *(string*)this->constant_pool[descriptor]->get_value();
    return pair<string,string>(s1, s2);
}

string class_attribute::get_class_name(int index){
    ushort name_index = *(ushort*)constant_pool[index]->get_value();
    string name = *(string*)constant_pool[name_index]->get_value();
    return name;
}

class_attribute::class_attribute(char* path){
    FILE *file;
    char *buffer = new char[10000];
    int point = 0;
    memset(buffer, 0, 10000);
    file = fopen(path, "r");
    fread(buffer, 10000, 1, file);
    // magic number
    this->magic = read_u(buffer, 4, &point);
    printf("magic: %x\n", this->magic);
    
    // minor/major version
    this->minor_version = read_u(buffer, 2, &point);
    printf("minor_version: %x\n", this->minor_version);
    this->major_version = read_u(buffer, 2, &point);
    printf("major_version: %x\n", this->major_version);
    
    // constant pool length
    this->constant_pool_count = read_u(buffer, 2, &point);
    printf("constant pool len: %x\n", this->constant_pool_count);
    
    // constant pool
    this->constant_pool = new CONSTANT_METATYPE* [constant_pool_count+1];
    process_constant_pool(buffer, this->constant_pool_count, &point, this->constant_pool);
#ifdef DEBUG
    printf("DEBUG: Printing all the class names.\n");
    for (int i = 1; i < constant_pool_count; i ++){
        if (constant_pool[i]->get_instance_type() == CONS_CLASS){
            string s = get_class_name(i);
            cout << s << endl;
        }
    }
#endif
    // access flags
    this->access_flags = read_u(buffer, 2, &point);
    process_access_flags(this, this->access_flags);
#ifdef DEBUG
    printf("NOW COUNT: %d\n", point);
#endif
    this->class_index = read_u(buffer, 2, &point);
    this->parent_index = read_u(buffer, 2, &point);
    this->interface_length = read_u(buffer, 2, &point);
#ifdef DEBUG
    printf("father index: %u\nclass index: %u\n", this->parent_index, this->class_index);
#endif
    // At this time we just ignore the interface index set.
    if (this->interface_length != 0){
        printf("Error: interface index length != 0!");
        exit(0);
    }
    
    // field table set
    this->field_count = read_u(buffer, 2, &point);
#ifdef DEBUG
    printf("field info count: %u\n", this->field_count);
#endif
    field_info = new FIELDINFO* [this->field_count];
    process_field_info(buffer, this->field_count, &point, this);
    
    // method table set
    this->method_count = read_u(buffer, 2, &point);
#ifdef DEBUG
    printf("method info count: %u\n", this->field_count);
#endif
    method_info = new METHODINFO* [this->method_count];
    process_method_info(buffer, this->method_count, &point, this);
    
#ifdef DEBUG
    for (int i = 0; i < method_count; i ++){
        uchar* tmp = method_info[i]->get_code();
        ushort len = method_info[i]->get_code_length();
        pair<string,string> info = method_info[i]->get_info(this);
        cout << info.first << "   " << info.second << endl;
        if(tmp == NULL)
            printf("Method %d, NULL.\n", i);
        else
            printf("Method %d, its code length: %u\n", i, len);
        for (int j = 0; j < len; j ++){
            printf("%x\n", tmp[j]);
        }
    }
#endif
    //attributes
    this->attributes_count = read_u(buffer, 2, &point);
    attributes = new ATTRIBUTEINFO* [attributes_count];
    process_attribute_info(buffer, attributes_count, &point, attributes, this);
    
    delete[] buffer;
}

uint read_u(char *buffer, int count, int *point){
    char tmp[8] = {};
    uint result = 0;
    uint store = 0;
    memcpy(tmp, buffer + *point, count);
    *point += count;
    for (int i = 0; i < count; i ++){
        store = ((store | tmp[count - i - 1]) & 0xff ) << (8 * i);
        result = result | store;
        store = 0;
    }
    return result;
}

double read_f(char *buffer, int count, int *point){
    double value;
    memcpy(&value, buffer + *point, count);
    *point += count;
    return value;
}

int process_constant_pool(char *buffer, int count, int *point, CONSTANT_METATYPE **cpool){
    int tag;
    int cnt = 1;
    //char *tmp;
    //tmp = (char*) malloc(sizeof(char) * count + 1);
    //memcpy(tmp, buffer + *point, count);
    while (cnt < count){
        //printf("position: %d limit: %d\n", cnt, count);
        tag = read_u(buffer, 1, point);
        //printf("The tag of this constant: %x\n", tag);
        switch(tag){
                // utf-8 info
            case(1):{
                int length = read_u(buffer, 2, point);
                char *utf8 = (char*) malloc(sizeof(char) * length + 1);
                memcpy(utf8, buffer + *point, length);
                *point += length;
                CONSTANT_utf8 *tmp = new CONSTANT_utf8(length, utf8);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The utf8 literal: %s\n", utf8);
#endif
                break;
            }
                // Integer info
            case(3):{
                int value = read_u(buffer, 4, point);
#ifdef DEBUG
                CONSTANT_integer *tmp = new CONSTANT_integer(value);
                cpool[cnt] = tmp;
                printf("Constant Pool %d -- ", cnt);
                printf("The integer value: %d\n", value);
#endif
                break;
            }
                // Float info
            case(4):{
                float value = read_f(buffer, 4, point);
                CONSTANT_float *tmp = new CONSTANT_float(value);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The float value: %f\n", value);
#endif
                break;
            }
                // Long info
            case(5):{
                long value = read_u(buffer, 8, point);
                CONSTANT_long *tmp = new CONSTANT_long(value);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("The long value: %ld\n", value);
#endif
                break;
            }
                // Double info
            case(6):{
                double value = read_f(buffer, 8, point);
                CONSTANT_double *tmp = new CONSTANT_double(value);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("double value: %lf\n", value);
#endif
                break;
            }
                // Class info
            case(7):{
                int index = read_u(buffer, 2, point);
                CONSTANT_class *tmp = new CONSTANT_class(index);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class info index: %d\n", index);
#endif
                break;
            }
                // String info
            case(8):{
                int index = read_u(buffer, 2, point);
                CONSTANT_string *tmp = new CONSTANT_string(index);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("string info index: %d\n", index);
#endif
                break;
            }
                // Fieldref info
            case(9):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_fieldref *tmp = new CONSTANT_fieldref(index_class, index_name_type);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name and type index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Methodref info
            case(10):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_methodref *tmp = new CONSTANT_methodref(index_class, index_name_type);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Interface_methodref
            case(11):{
                int index_class = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_interface *tmp = new CONSTANT_interface(index_class, index_name_type);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_class, index_name_type);
#endif
                break;
            }
                // Name_and_type info
            case(12):{
                int index_name = read_u(buffer, 2, point);
                int index_descriptor = read_u(buffer, 2, point);
                CONSTANT_name_type *tmp = new CONSTANT_name_type(index_name, index_descriptor);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("class index:%d, name index:%d\n", index_name, index_descriptor);
#endif
                break;
            }
                // Method_handle info
            case(15):{
                int reference_kind = read_u(buffer, 1, point);
                int index_reference = read_u(buffer, 2, point);
                CONSTANT_method_handle *tmp = new CONSTANT_method_handle(reference_kind, index_reference);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("reference kind:%d, reference index:%d\n", reference_kind, index_reference);
#endif
                break;
            }
                // Method_type info
            case(16):{
                int index_descriptor = read_u(buffer, 2, point);
                CONSTANT_method_type *tmp = new CONSTANT_method_type(index_descriptor);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("descriptor index:%d\n", index_descriptor);
#endif
                break;
            }
                // Invoke_dynamic info
            case(18):{
                int index_bootsrap = read_u(buffer, 2, point);
                int index_name_type = read_u(buffer, 2, point);
                CONSTANT_invoke_dynamic *tmp = new CONSTANT_invoke_dynamic(index_bootsrap, index_name_type);
                cpool[cnt] = tmp;
#ifdef DEBUG
                printf("Constant Pool %d -- ", cnt);
                printf("bootsrap index:%d, name_type index:%d\n", index_bootsrap, index_name_type);
#endif
                break;
            }
        }
        cnt += 1;

    }
    return 0;
}

void process_access_flags(class_attribute *p, ushort flag){
    p->ACC_PUBLIC = flag & 1;
    p->ACC_FINAL = flag & 0x10;
    p->ACC_SUPER = flag & 0x20;
    p->ACC_INTERFACE = flag & 0x200;
    p->ACC_ABSTRACT = flag & 0x400;
    p->ACC_SYNTHETIC = flag & 0x1000;
    p->ACC_ANNOTATION = flag & 0x2000;
    p->ACC_ENUM = flag & 0x4000;
}

void process_field_info(char *buffer, int count, int *point, class_attribute *cl){
    ushort access_flags, name_index, descriptor_index, attributes_count;
    for (int i = 0; i < count; i ++){
        access_flags = read_u(buffer, 2, point);
        name_index = read_u(buffer, 2, point);
        descriptor_index = read_u(buffer, 2, point);
        attributes_count = read_u(buffer, 2, point);
        cl->field_info[i] = new FIELDINFO(access_flags, name_index, descriptor_index, attributes_count);
#ifdef DEBUG
        printf("New field info, name_index:%u, descriptor_index:%u, attributes:%u\n", name_index, descriptor_index, attributes_count);
#endif
    }
}

void process_method_info(char *buffer, int count, int *point, class_attribute *cl){
    ushort access_flags, name_index, descriptor_index, attributes_count;
    for (int i = 0; i < count; i ++){
        access_flags = read_u(buffer, 2, point);
        name_index = read_u(buffer, 2, point);
        descriptor_index = read_u(buffer, 2, point);
        attributes_count = read_u(buffer, 2, point);
        cl->method_info[i] = new METHODINFO(access_flags, name_index, descriptor_index, attributes_count);
#ifdef DEBUG
        printf("New method info, name_index:%u, descriptor_index:%u, attributes:%u\n", name_index, descriptor_index, attributes_count);
#endif
        process_attribute_info(buffer, attributes_count, point, cl->method_info[i]->attributes, cl);
    }
}

void process_attribute_info(char *buffer, int count, int *point, ATTRIBUTEINFO **attr, class_attribute *cl){
    for (int i = 0; i < count; i ++){
        ushort index = read_u(buffer, 2, point);
        uint length = read_u(buffer, 4, point);
#ifdef DEBUG
        //printf("Pointer here: %d\n", *point);
        //printf("Length of this attribute: %d\n", length);
#endif
        if (cl->constant_pool[index]->get_instance_type() != CONS_UTF8)
            exit(0);
        string str = *(string*) (cl->constant_pool[index]->get_value());
#ifdef DEBUG
        printf("Attribute %d, index: %d, name: %s\n", i+1, index, str.c_str());
#endif
        if (str == "Code"){
            ushort max_stack = read_u(buffer, 2, point);
            ushort max_locals = read_u(buffer, 2, point);
            uint code_length = read_u(buffer, 4, point);
#ifdef DEBUG
            printf("In code: %d bytes\n", code_length);
#endif
            uchar *code = new uchar [code_length+1];
            memcpy(code, buffer+(*point), code_length);
            *point += code_length;
            ushort exception_table_length = read_u(buffer, 2, point);
            // Not handled yet
            *point += exception_table_length;
            ushort attributes_count = read_u(buffer, 2, point);
            attr[i] = new CODE(index, length, max_stack, max_locals, code_length, code, exception_table_length, attributes_count);
#ifdef DEBUG
            printf("In code: %d exceptions, %d attributes\n", exception_table_length, attributes_count);
#endif
            void **tmp = attr[i]->get_attributes();
            process_attribute_info(buffer, attributes_count, point, (ATTRIBUTEINFO**)tmp, cl);

        }
        else if (str == "LineNumberTable"){
            ushort line_number_table_length = read_u(buffer, 2, point);
            attr[i] = new LINENUMBERTABLE(index, length, line_number_table_length);
            LINENUMBERINFO **tmp = (LINENUMBERINFO**)attr[i]->get_attributes();
            for (int j = 0; j < line_number_table_length; j ++){
                ushort start_pc = read_u(buffer, 2, point);
                ushort line_number = read_u(buffer, 2, point);
                tmp[j] = new LINENUMBERINFO(start_pc, line_number);
            }
#ifdef DEBUG
            printf("In LineNumberTable: %d tables\n", line_number_table_length);
            //printf("Pointer here: %d\n", *point);
#endif
        }
        else if (str == "SourceFile"){
            ushort source = read_u(buffer, 2, point);
            attr[i] = new SOURCEFILE(index, length, source);
        }
        else
            *point += length;
        //printf("Quit Attribute, Pointer: %d\n", *point);
        //*point += length;
    }
}

int main(int argc, char **argv){
    class_attribute class_file(argv[1]);
    return 0;
}
