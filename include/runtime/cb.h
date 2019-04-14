#include <cstdio>
#include <string.h>
#include <stdlib.h>

#define DEBUG

using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;

class CONSTANT_POOL;
class class_attribute;
class EXCEPTIONINFO;
class ATTRIBUTEINFO;
class FIELDINFO;
class METHODINFO;

int process_constant_pool(char *buffer, int count, int *point, CONSTANT_POOL *cpool);
void process_access_flags(class_attribute *p, ushort flag);
void process_field_info(char *buffer, int count, int *point, class_attribute *cl);
void process_method_info(char *buffer, int count, int *point, class_attribute *cl);
void process_attribute_info(char *buffer, int count, int *point, ATTRIBUTEINFO **attr, class_attribute *cl);
uint read_u(char *buffer, int count, int *point);
double read_f(char *buffer, int count, int *point);

enum types {CONS_UTF8, CONS_INTEGER, CONS_FLOAT, CONS_LONG, CONS_DOUBLE, CONS_STRING, CONS_CLASS,
    CONS_FIELD, CONS_METHOD, CONS_INTERFACE, CONS_NAME_TYPE, CONS_METHOD_HANDLE, CONS_METHOD_TYPE,
    CONSTANT_INVOKE_DYNAMIC, CONS_METATYPE, PUBLIC, PRIVATE, PROTECTED
} type;
