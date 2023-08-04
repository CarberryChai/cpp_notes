## 内置原始类型（primitive built-in types）
  **Types determine the meaning of the data and operations in our programs.**
  | Type | Meaning | Minimum Size |
  | ----- | ----- | ------ |
  | bool | boolean | NA |
  | char | character | 8 bits |
  | wchar_t | wide character | 16 bits |
  | char16_t | Unicode character | 16 bits |
  | char32_t | Unicode character | 32 bits |
  | short | short integer | 16 bits |
  | int | integer | 16 bits |
  | long | long integer | 32 bits |
  | long long | long integer | 64 bits |
  | float | single-precision floating-point | 6 significant digits |
  | double | double-precision floating-point | 10 significant digits |
  | long double | extended-precision floating-point | 10 significant digits |

## 变量
  A **variable** provides us with named storage that our programs can manipulate.
  在C++中，每一个变量都有一个类型。**The type determines the size and layout of the variable's memory, the range of values that can be stored within that memory, and the set of operations that can be applied to the variable.**
  * 变量定义
    A simple variable definition consists of a **type specifier**, followed by a list of one or more variable names separated by commas, and ends with a semicolon.
    ```cpp
      int sum = 0, value, units_sold = 0; // sum, value, and units_sold have type int; sum and units_sold have initial value 0
      Sales_item item;
      std::string book("0-201-78345-X"); // string is a library type, representing a variable-length sequence of characters, book initialized from string literal
    ```
  * 初始化
    An object that is **initialized** gets the specified value at the moment it is created.
    **Initialization is not assignment. Initialization happens when a variable is given a value when it is created. Assignment obliterates(清除) an object's current value and replaces that value with a new one.**
  * Variable Declarations and Definitions
   ** A declaration makes a name known to the program. A file that wants to use a name defined elsewhere includes a declaration for that name. A definition creates the associated entity.**
  变量的声明规定了变量的类型和名字。一个变量的定义也是声明。除了规定变量的名字和类型，定义还分配存储空间，可能提供变量一个初始值。
  Variables must be defined exactly once but can be declared many times.

## Compound types
  C++ has several compound types, two of which -- references and pointers.
  Simple declarations consist of a type followed by a list of variable names. More generally, a declaration is a **base type** followed by a list of **declarators**. Each declarator names a variable and gives the variable a type that is related to the base type.
  * References
    A reference defines an alternative name for an object. A reference type "refers to" another type. We define a reference type by writing a declarator of the form `&d`, where `d` is the name being declared:
    ```cpp
      int ival = 1024;
      int &refval = ival; // refval refers to (is another name for) ival
      int &refval2; // error: a reference must be initialized
    ```
    `int &refval = ivla` 声明了一个reference，其中`&`是声明的一部分，不要和后面的取址运算符搞混了。
    **A reference is not an object. Instead, a reference is just another name for an already existing object.**

  * Pointers
    A **pointer** is a compound type that "points to" another type. Pointers can be assigned and copied; a single pointer can point to several different objects over its lifetime.
    We define a pointer type by writing a declarator of the form `*d`, where `d` is the name being defined. The `*` must be repeated for each pointer variable:
    ```cpp
      int *ip1, *ip2; // both ip1 and ip2 are pointers to int
      double dp, *dp2; // dp2 is a pointer to double; dp is a double
    ```
    `int *ip1` 声明了一个指针，和声明reference一样，其中`*`是声明的一部分，不要和后面的取值运算符搞混了。
  * Understanding Compound Type Declarations
    ```cpp
    // i is an int; p is a pointer to int; r is a reference to int 在这里需特别注意 & 即是声明的一部分又是运算符，同一个符号在不同的context下不同的意义。
    int i = 1024, *p = &i, &r = i;
    ```
  * References to Pointers
    ```cpp
      int i = 42;
      int *p; // p is a pointer to int
      int *&r = p; // r is a reference to the pointer p
      r = &i; // r refers to a pointer; assigning &i to r makes p point to i
      *r = 0; // dereferencing r yields i, the object to which p points; changes i to 0
    ```












