#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define DEBUG

using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;
using ulong = unsigned long;
enum types {CONS_UTF8, CONS_INTEGER, CONS_FLOAT, CONS_LONG, CONS_DOUBLE, CONS_STRING, CONS_CLASS,
    CONS_FIELD, CONS_METHOD, CONS_INTERFACE, CONS_NAME_TYPE, CONS_METHOD_HANDLE, CONS_METHOD_TYPE,
    CONSTANT_INVOKE_DYNAMIC, CONS_METATYPE, PUBLIC, PRIVATE, PROTECTED, ATTR_META, ATTR_CODE, ATTR_LINENUMBER, ATTR_SOURCEFILE
} type;

class CONSTANT_METATYPE;
class EXCEPTIONINFO;
class ATTRIBUTEINFO;
class FIELDINFO;
class METHODINFO;

class class_attribute{
public:
    uint magic;
    ushort minor_version;
    ushort major_version;
    ushort constant_pool_count;
    ushort access_flags;
    CONSTANT_METATYPE ** constant_pool;
    ushort parent_index;
    ushort class_index;
    ushort interface_length;
    ushort field_count;
    ushort method_count;
    ushort attributes_count;
    FIELDINFO **field_info;
    METHODINFO **method_info;
    ATTRIBUTEINFO **attributes;
    bool ACC_PUBLIC;
    bool ACC_FINAL;
    bool ACC_SUPER;
    bool ACC_INTERFACE;
    bool ACC_ABSTRACT;
    bool ACC_SYNTHETIC;
    bool ACC_ANNOTATION;
    bool ACC_ENUM;
    string get_class_name(int index);
    pair<string,string> get_info(int name, int descriptor);
    class_attribute(char* path);
};

class METHODINFO{
public:
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
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    types get_permission();
    pair<string,string> get_info(class_attribute* cl);
    uchar* get_code();
    ushort get_code_length();
    ushort get_code_index();
    METHODINFO(int access_flags, int name_index, int descriptor_index, int attributes_count);
};

class FIELDINFO{
public:
    bool ACC_PUBLIC;
    bool ACC_PRIVATE;
    bool ACC_PROTECTED;
    bool ACC_STATIC;
    bool ACC_FINAL;
    bool ACC_VOLATILE;
    bool ACC_TRANSIENT;
    bool ACC_SYNTHETIC;
    bool ACC_ENUM;
    ushort name_index;
    ushort descriptor_index;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    types get_permission();
    FIELDINFO(int access_flags, int name_index, int descriptor_index, int attributes_count);
};


class ATTRIBUTEINFO{
public:
    ushort attribute_name_index;
    uint attribute_length;
    ATTRIBUTEINFO(ushort index, ushort length);
    virtual void** get_attributes();
    virtual types get_instance_type();
    virtual uchar* get_code();
    virtual ushort get_length();
};

class CODE:public ATTRIBUTEINFO{
public:
    ushort max_stack;
    ushort max_locals;
    uint code_length;
    uchar *code;
    ushort exception_table_length;
    ushort attributes_count;
    ATTRIBUTEINFO **attributes;
    EXCEPTIONINFO **exception_table;
    void** get_attributes();
    types get_instance_type();
    uchar *get_code();
    ushort get_length();
    CODE(ushort ani, uint al, ushort ms, ushort ml, uint cl, uchar *cd, ushort etl, ushort ac);
};

int process_constant_pool(char *buffer, int count, int *point, CONSTANT_METATYPE **cpool);
void process_access_flags(class_attribute *p, ushort flag);
void process_field_info(char *buffer, int count, int *point, class_attribute *cl);
void process_method_info(char *buffer, int count, int *point, class_attribute *cl);
void process_attribute_info(char *buffer, int count, int *point, ATTRIBUTEINFO **attr, class_attribute *cl);
uint read_u(char *buffer, int count, int *point);
double read_f(char *buffer, int count, int *point);

