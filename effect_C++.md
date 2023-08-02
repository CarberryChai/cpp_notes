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
  * A **default constructor** is one that can be called without any arguments. Such a constructor either has no parameters or has a default value for every parameter.
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