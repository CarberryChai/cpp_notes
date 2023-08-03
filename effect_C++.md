# Effect C++
## Terminology
  * A **declaration** tells compilers about the name and type of something, but it omits certain details.
  ```cpp
    extern int x; // object declaration
    std::size_t numDigits(int number); // function declaration
    class Widget; // class declaration
    template<typename T>
    class GraphNode; // template declaration
  ```
  * Each function's declaration reveals its **signature**, its parameter and return types. A function's signature is the same as its type.
  > in the case of `numDigits`, the **signature** is `std::size_t(int)`, "function taking an int and returning a `std::size_t`". The official C++ definition of "signature" excludes the function's return type, but in this book, it's more usefull to have the return type be considered part of the signature.
  * A **definition** provides compilers with the details a declaration omits.
  ```cpp
    int x; // object definition
    std::size_t numDigits(int number) { // function definition
      std::size_t digitsSoFar = 1;
      while((number / 10) != 0) ++digitsSoFar;
      return digitsSoFar;
    }
    class Widget {  // class definition
      public:
        Widget();
        ~Widget();
        // ...
    }
  ```
  * **Initialization** is the process of giving an object its first value. For objects generated from structs and classes, initialization is performed by constructors.
  * A **default constructor** is one that can be called w**ithout any arguments**. Such a constructor either has no parameters or has a default value for every parameter.
  ```cpp
    class A {
      public:
        A(); // default constructor
    };

    class B {
      public:
        explicit B(int x = 0, bool b = true); // default constructor
    };

    class C {
      public:
        explicit C(int x); // not a default constructor
    };
  ```
  The constructors for classes `B` and `C` are declared `explicit` here. That prevents them from being used to perform **implicit type conversions**. thought they may still be used for explicit type conversions.
  ```cpp
    void doSomething(B bobj); // a function taking an object of type B
    B bobj1; // an object of type B
    doSomething(bobj1); // fine, passes a B to doSomething
    B bobj2(28); // fine, creates a B from the int 28 (the boool defaults to true)
    doSomething(28); // error! doSomething takes a B, not an int, and there is no implicit conversion from int to B
    doSomething(B(28)); // fine, uses the B constructor to explicitly convert the int to a B for this call.
  ```
  **Constructors declared `explicit` are usually preferable to non-explicit ones**, because they prevent compilers from performing unexpected(often unintended) type conversions. Unless I have a good reason for allowing a constructor to be used for implicit type conversions, I declare it `explicit`
  * The **copy constructor** is used to initialize an object with a different object of the same type, and the **copy assignment operator** is used to copy the value from one object to another of the same type.
  ```cpp
    class Widget {
      public:
        Widget(); // default constructor
        Widget(const Widget& rhs); // copy constructor
        Widget& operator=(const Widget& rhs); // copy assignment operator
    };
    Widget w1; // invoke default constructor
    Widget w2(w1); // invoke copy constructor
    w1 = w2; // invoke copy assignment operator
  ```
  Read carefully when you see what appears to be an assignment, because the "=" syntax can also be used to call the copy constructor:
  ```cpp
    Widget w3 = w2; // invoke copy constructor
  ```
  Fortunately, copy construction is easy to distinguish from copy assignment. **If a new object is being defined**( such as the w3 in the statement above), **a constructor has to be called**; it can't be an assignment. **If no new object is being defined** ( such as in the "w1 = w2" statement above), no constructor can be invoked, so **it's an assignment**.
  The copy constructor is a particularly important function. because it defines how an object is passed by value. For example, consider this:
  ```cpp
    bool hasAcceptableQuality(Widget W);
    //...
    Widget aWidget;
    if(hasAcceptablequality(aWidget)) {}
  ```
  The parameter `w` is passed to `hasAcceptableQuality` by value, so in the call above, `aWidget` is copied into `w`. The copying is done by Widget's copy constructor. **Pass-by-value means "call the copy constructor."** (However, it's generally a bad idea to pass user-defined types by value. Pass-by-reference-to-const is typically a better choice.)

## Item 1: View C++ as a federation of languages.
  Today's C++ is a *multiparadigm programming language* , one supporting a combination of procedural（命令式）, object-oriented, functional, generic（范型）, and metaprogramming features.
  To make sense of C++, you have to recognize its primary sublanguages. Fortunately, there are only four:
  * **C.** C++ is still based on C. Blocks, statements, the preprocessor, built-in data types, arrays, points, etc., all come from C.
  * **Object-Oriented C++.** This part of C++ is what C with Classes was all about: classes (including constructors and destructors), encapsulation（封装）, inheritance（继承）, polymorphism（多态）, virtual functions (dynamic binding), etc.
  * **Template C++.** This is the generic programming part of C++.
  * **The STL.** The STL is a template library.
  
## Item 2: Prefer consts, enums, and inlines to #defines
  This Item might better be called "prefer the compiler to the preprocessor".
  * For simple constants, prefer `const` objects or enums to #defines.
  * For function-like macros, prefer inline functions to #defines.
## Item 3: Use `const` whenever possible.
  ```cpp
    char greeting[] = "hello";
    char *p = greeting; // non-const pointer, no-const data

    const char *p = greeting; // non-const pointer, const data

    char * const p = greeting; // const pointer, non-const data

    const char * const p = greeting; // const pointer, const data
  ```
  If the word `const` appears to the left of the asterisk(* 星号), what's pointed to is constant; if the word `const` appears to the right of the asterisk, the pointer itself is constant; if `const` appears on both sides, both are constant.

  STL iterators are modeled on pointers, so an iterator acts much like a `T*` pointer. Declaring a iteratror `const` is like declaring a pointer `const`(i.e., declaring a `T* const pointer`): the iterator isn't allowed to point to something different, but the thing it points to may be modified. If you want an iterator that points to something that can't be modified (i.e., the STL analogue of a `const T* pointer`), you want a const_iterator:
  ```cpp
    std::vector<int> vec;
    // ..
    const std::vector<int>::iterator iter = vec.begin(); // iter acts like a T* const
    *iter = 10; // ok, changes what iter points to
    ++iter; // error! iter is const

    std::vector<int>::const_iterator clter = vec.begin(); // clter acts like a const T*
    *clter = 10; // error! *clter is const
    ++clter; // fine, changes clter
  ```
  * `const` Member Functions
    The purpose of `const` on member functions is to identify which member functions may be invoked on `const` objects.
    - They make the interface of a class easier to understand. It's important to know which functions may modify an object an which may not.
    - They make it possible to work with `const` objects.
  ```cpp
    class TextBlock{
      public:
        //...
        const char& operator[](std::size_t position) const {
          return text[position];  // operator[] for const objects
        }
        char& operator[](std::size_t position) {
          return text[position]; // operator[] for non-const objects
        }
      private:
        std::string text;
    };

    TextBlock tb("hello");
    std::cout << tb[0]; // call non-const TextBlock::operator[]

    const TextBlock ctb("World");
    std::cout << ctb[0]; // calls const TextBlock::operator[]
  ```








