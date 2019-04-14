# Javap Doc
## class `class_file`:
Attributes:
```
    uint magic; //魔数
    ushort minor_version;
    ushort major_version; //主次版本号
    ushort constant_pool_count; //常量池大小
    ushort access_flags;  //访问的flag
    CONSTANT_METATYPE **constant_pool; //常量池入口指针
    ushort parent_index;  //父类对应的符号饮用在常量池的位置
    ushort class_index; //该类自己的符号引用在常量池的位置
    ushort interface_length;  //接口长度，还没做
    ushort field_count; //字段数
    ushort method_count;  //方法数
    FIELDINFO **field_info; //字段入口指针，每一项代表一个字段
    METHODINFO **method_info; //方法入口指针
    bool ACC_PUBLIC;
    bool ACC_FINAL;
    bool ACC_SUPER;
    bool ACC_INTERFACE;
    bool ACC_ABSTRACT;
    bool ACC_SYNTHETIC;
    bool ACC_ANNOTATION;
    bool ACC_ENUM;
```
Methods:
```
string get_class_name(int index);   //直接返回常量池第i号元素的类名，i必须是类
```

## class `CONSTANT_METATYPE`
这个是所有常量池类型的元类，实现了虚函数用来取类型、值等操作
Methods:
```
    virtual void* get_value(){return NULL; }  //得到该对象的值，固定返回void*，需要你自己转类型
    virtual types get_instance_type(){  //得到该对象的类型
        return CONS_METATYPE;
    }
```

## class `METHODINFO`
方法类，一个对象就代表一个方法

Attributes:
```
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
    ushort name_index;  //方法名在常量池的位置
    ushort descriptor_index;  //方法描述符的位置（参数，返回值等）
    ushort attributes_count;  //方法所携带的附加信息数
    ATTRIBUTEINFO **attributes; //方法携带的附加信息入口指针，内有Code等等
```
Methods:
```
    types get_permission(){  //获取方法的访问权限
        if (ACC_PUBLIC) return PUBLIC;
        else if (ACC_PRIVATE) return PRIVATE;
        else return PROTECTED;
    }
    uchar* get_code(); //获取该方法的字节码
    ushort get_code_length(); //获取字节码长度
    pair<string,string> get_info(); //返回pair,第一个分量是方法名，第二个分量是描述符（参数类型+返回类型）
```

## class `FIELDINFO`
字段类，一个对象代表一个字段。方法和属性与METHODINFO几乎一样

Attributes:
```
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
```
Methods:
```
    types get_permission(){
        if (ACC_PUBLIC) return PUBLIC;
        else if (ACC_PRIVATE) return PRIVATE;
        else return PROTECTED;
    }
```

## class `ATTRIBUTEINFO`
属性类元类，一个对象代表一个属性。这个类的子类可能有很大，比如Code和LineNumberTable。目前只实现了这两个

```
    ushort attribute_name_index;  //属性名在常量池位置
    uint attribute_length;  //属性所占bytes，只包含它之下的部分
```

### class `CODE`
代码类，属性类子类

Attributes:
```
    ushort max_stack; //最大栈深度
    ushort max_locals;  //最大本地变量空间大小
    uint code_length; //代码长度
    uchar *code;  //存代码的数组
    ushort exception_table_length;  //一个叫exception_table的长度，还未实现
    ushort attributes_count;  //代码里头也有可能包含属性。这个是它的个数
    ATTRIBUTEINFO **attributes;
    EXCEPTIONINFO **exception_table;
```

### class `LINENUMBERTABLE`
行号表类，属性类子类

Attributes:
```
    ushort line_number_table_length;
    LINENUMBERINFO** line_number_table; //指向length个行号信息
```

### class `LINENUMBERINFO`
行号信息

Attributes:
```
    ushort start_pc;  //字节码行号
    ushort line_number; //Java源码行号
```
