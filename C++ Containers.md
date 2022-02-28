- [**array**](http://www.cplusplus.com/reference/array/array/)

  Array class (class template )

- [**deque**](http://www.cplusplus.com/reference/deque/deque/)

  Double ended queue (class template )

- [**forward_list**](http://www.cplusplus.com/reference/forward_list/forward_list/)

  Forward list (class template )

- [**list**](http://www.cplusplus.com/reference/list/list/)

  List (class template )

- [**map**](http://www.cplusplus.com/reference/map/map/)

  Map (class template )

- [**multimap**](http://www.cplusplus.com/reference/map/multimap/)

  Multiple-key map (class template )

- [**queue**](http://www.cplusplus.com/reference/queue/queue/)

  FIFO queue (class template )

- [**priority_queue**](http://www.cplusplus.com/reference/queue/priority_queue/)

  Priority queue (class template )

- [**set**](http://www.cplusplus.com/reference/set/set/)

  Set (class template )

- [**multiset**](http://www.cplusplus.com/reference/set/multiset/)

  Multiple-key set (class template )

- [**stack**](http://www.cplusplus.com/reference/stack/stack/)

  LIFO stack (class template )

- [**unordered_map**](http://www.cplusplus.com/reference/unordered_map/unordered_map/)

  Unordered Map (class template )

- [**unordered_multimap**](http://www.cplusplus.com/reference/unordered_map/unordered_multimap/)

  Unordered Multimap (class template )

- [**unordered_set**](http://www.cplusplus.com/reference/unordered_set/unordered_set/)

  Unordered Set (class template )

- [**unordered_multiset**](http://www.cplusplus.com/reference/unordered_set/unordered_multiset/)

  Unordered Multiset (class template )

- [**vector**](http://www.cplusplus.com/reference/vector/vector/)

  Vector (class template )

- [**vector<bool>**](http://www.cplusplus.com/reference/vector/vector-bool/)

  Vector of bool (class template specialization )



https://www.cnblogs.com/fusiwei/p/11823234.html



定义一个函数为虚函数，不代表函数为不被实现的函数。定义他为虚函数是为了允许用基类的指针来调用子类的这个函数。定义一个函数为纯虚函数，才代表函数没有被实现。定义纯虚函数是为了实现一个接口，起到一个规范的作用，规范继承这个类的程序员必须实现这个函数。



纯虚函数最显著的特征是：它们必须在继承类中重新声明函数（不要后面的＝0，否则该派生类也不能实例化），而且它们在抽象类中往往没有定义。

定义纯虚函数的目的在于，使派生类仅仅只是继承函数的接口。

纯虚函数的意义，让所有的类对象（主要是派生类对象）都可以执行纯虚函数的动作，但类无法为纯虚函数提供一个合理的缺省实现。所以类纯虚函数的声明就是在告诉子类的设计者，“你必须提供一个纯虚函数的实现，但我不知道你会怎样实现它”。

抽象类的定义：  称带有纯虚函数的类为抽象类。（2）抽象类的作用：抽象类的主要作用是将有关的操作作为结果接口组织在一个继承层次结构中，由它来为派生类提供一个公共的根，[派生类](https://www.zhihu.com/search?q=派生类&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A69592611})将具体实现在其基类中作为接口的操作。所以派生类实际上刻画了一组子类的操作接口的通用语义，这些语义也传给子类，子类可以具体实现这些语义，也可以再将这些语义传给自己的子类。



总结：

1、纯虚函数声明如下： virtual void funtion1()=0; 纯虚函数一定没有定义，纯虚函数用来规范派生类的行为，即接口。包含纯虚函数的类是抽象类，抽象类不能定义实例，但可以声明指向实现该抽象类的具体类的指针或引用。

2、虚函数声明如下：virtual ReturnType FunctionName(Parameter)；虚函数必须实现，如果不实现，编译器将报错，错误提示为：

error LNK****: unresolved external symbol "public: virtual void __thiscall ClassName::virtualFunctionName(void)"

3、对于虚函数来说，父类和子类都有各自的版本。由多态方式调用的时候动态绑定。

4、实现了纯虚函数的子类，该纯虚函数在子类中就编程了虚函数，子类的子类即孙子类可以覆盖该虚函数，由多态方式调用的时候动态绑定。

5、虚函数是C++中用于实现多态(polymorphism)的机制。核心理念就是通过基类访问派生类定义的函数。





多态的好处：违反了设计模式开闭原则：对扩展开放，对修改关闭



总结:虚函数目的是在用基类指针指向派生类的时候还能正确调用派生的实现。

虚函数是为了将方法和对象绑定在一起，而不是直接将方法和类型绑定在一起，从而可以实现运行时的多态



父类指针指向子类对象时,父类和子类有相同方法无虚函数: 指针只能调用父类的方法有虚函数: 指针只能调用子类的方法



### **重载和重写的区别**

- “重载”（overloading）通常是指在同一个类中有多个具有相同名称和返回类型但参数不同的方法
- “重写”（overriding）非常不同，后者两个函数具有完全相同的**function signature**，同时是在派生类中的。

从编程写法上来说：

- `virtual void Function() = 0;` 是纯虚函数

- `virtual void Function()`是虚函数   

  

  

虚函数突破了“基类指针无法调用派生类中成员函数”的限制。

静态派发就是指在编译期[[1\]](https://zhuanlan.zhihu.com/p/259875110#ref_1)就能知道要调用的函数具体是哪一个。

动态派发就是编译期**”不知道“**要调用的是哪个函数，只有等到程序运行，跑到这一行代码才知道要调用的是哪个函数。



1. 编译器知道变量`Base* d`是一个指针，它指向Heap的一块内存区域（绿色开头的，也就是C++的对象）（几乎都在Heap，你要硬搞不在heap， C++也可以做到）。 
2. 首先沿着d指针找到这块内存区域。
3. 接着读取这块内存区域的头部内容（绿色部分, 也就是虚指针vptr）。
4. 接着沿着这个虚指针到达另外一块内存区域（蓝色区域，也就是虚函数表vtble，简称虚表）。
5. 然后根据偏移量（这个偏移量是编译期由我们调用的函数确定），移动到虚表的某个位置，这个位置存储的内容就是我们要调用的函数的地址 f_addr。
6. 最后根据这个地址调用函数，也就是运行指令 call f_addr。

![preview](https://pic2.zhimg.com/v2-63a6ace576636f48c13d321b76dcda81_r.jpg)



总结前面的内容
（1） 基类方法中声明了方法为虚后，该方法在基类派生类中是虚的。
（2） 若使用指向对象的引用或指针调用虚方法，程序将根据对象类型来调用方法，而不是指针的类型。
（3）如果定义的类被用作基类，则应将那些要在派生类中重新定义的类方法声明为虚。
构造函数不能为虚函数。
基类的析构函数应该为虚函数。
友元函数不能为虚，因为友元函数不是类成员，只有类成员才能是虚函数。
如果派生类没有重定义函数，则会使用基类版本。
重新定义继承的方法若和基类的方法不同（协变除外），会将基类方法隐藏；如果基类声明方法被重载，则派生类也需要对重载的方法重新定义，否则调用的还是基类的方法。
