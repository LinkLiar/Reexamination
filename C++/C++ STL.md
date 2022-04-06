STL中六大组件：

1）容器（Container），是一种数据结构，如list，vector，和deques ，以模板类的方法提供。为了访问容器中的数据，可以使用由容器类输出的迭代器；

2）迭代器（Iterator），提供了访问容器中对象的方法。例如，可以使用一对迭代器指定list或vector中的一定范围的对象。迭代器就如同一个指针。事实上，C++的指针也是一种迭代器。但是，迭代器也可以是那些定义了operator*()以及其他类似于指针的操作符地方法的类对象。迭代器实际上也是一种将operator*、operator->、operator++、operator--等指针相关操作予以重载的class template

3）算法（Algorithm），是用来操作容器中的数据的模板函数。例如，STL用sort()来对一个vector中的数据进行排序，用find()来搜索一个list中的对象，函数本身与他们操作的数据的结构和类型无关，因此他们可以在从简单数组到高度复杂容器的任何数据结构上使用；

4）仿函数（Function object） ，行为类似函数，可作为算法的某种策略。从实现角度看，仿函数是一种重载了operator（）的class或class template。一般函数指针可视为狭义的仿函数。

5）迭代适配器（Adaptor），一种用来修饰容器、仿函数、迭代器接口的东西。STL提供的的queue和stack，虽然看似容器，其实只能算是一种容器配接器，因为他们的弟弟不完全借助deque，所有操作都由底层deque提供。

6）配置器（allocator），负责空间配置与管理。实现了动态空间配置，空间管理，空间释放的class template。

7）六大组件的交互关系：容器通过空间配置器取得数据存储空间，算法通过迭代器取得容器的内容，仿函数可以协助空间配置器完成不同的策略变化，适配器可以修饰或套接仿函数。

## 容器的底层实现
1.vector          底层数据结构为数组 ，支持快速随机访问。
2.list            底层数据结构为双向链表，支持快速增删。
3.deque           底层数据结构为一个中央控制器和多个缓冲区，支持首尾（中间不能）快速增删，也支持随机访问，看起来像是list和vector的结合品。
4.stack           底层一般用list或deque实现，封闭头部即可，不用vector的原因应该是容量大小有限制，扩容耗时。
5.queue           底层一般用list或deque实现，封闭头部即可，不用vector的原因应该是容量大小有限制，扩容耗时。
（stack和queue其实是适配器,而不叫容器，因为是对容器的再封装）
6.priority_queue  底层数据结构一般为vector为底层容器，堆heap为处理规则来管理底层容器实现。
7.set             底层数据结构为红黑树，有序，不重复
8.multiset        底层数据结构为红黑树，有序，可重复 
9.map             底层数据结构为红黑树，有序，不重复
10.multimap       底层数据结构为红黑树，有序，可重复
11.hash_set       底层数据结构为hash表，无序，不重复
12.hash_multiset  底层数据结构为hash表，无序，可重复
13.hash_map       底层数据结构为hash表，无序，不重复
14.hash_multimap  底层数据结构为hash表，无序，可重复 



































参考网址：https://blog.csdn.net/King_weng/article/details/88368534