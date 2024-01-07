以升序进行排列，或是指定谓词实现其他排序需求。这个排序函数无法对``list``使用，相对的，有``list::sort``函数。
lambda函数可以救一狗命，很多时候需要闭包，而闭包的传统实现是借用``functional``库的``bind``函数，略显麻烦。
functional-bind函数的使用：[https://blog.csdn.net/qq_38410730/article/details/103637778](https://blog.csdn.net/qq_38410730/article/details/103637778)




<br>

***

# sort

MSDN：[点击跳转](https://learn.microsoft.com/zh-cn/cpp/standard-library/algorithm-functions?view=msvc-170#sort)


```cpp
template<class RandomAccessIterator>
void sort(
    RandomAccessIterator first,
    RandomAccessIterator last);

template<class RandomAccessIterator, class Compare>
void sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    Compare pred);

template<class ExecutionPolicy, class RandomAccessIterator>
void sort(
    ExecutionPolicy&& exec,
    RandomAccessIterator first,
    RandomAccessIterator last);

template<class ExecutionPolicy, class RandomAccessIterator, class Compare>
void sort(
    ExecutionPolicy&& exec,
    RandomAccessIterator first,
    RandomAccessIterator last,
    Compare pred);
```

#### 参数

*exec*
要使用的执行策略。

*first*
指定范围-前

*last*
指定范围-后

*pred*
用户定义的谓词函数对象，定义排序中连续元素要满足的比较条件。 该二元谓词采用两个参数，并且，如果两个参数按顺序排序，将返回 true，否则将返回 false。 该比较器函数必须对序列中的元素对进行严格弱排序。 有关详细信息，请参阅算法。

#### 注解
引用的范围必须有效；所有指针都必须可以引用，并且在序列中，可通过递增从第一个位置到达最后一个位置。

元素是等效的，但是如果两者都不小于对方，则不一定要相等。 sort 算法不稳定，因此不保证保留等效元素的相对顺序。 算法 stable_sort 会保留此原始顺序。

排序复杂性的平均值为 O( N log N )，其中 N = last - first。

# 参考：
- 使用sort对常见容器排序：[https://zhuanlan.zhihu.com/p/623209227](https://zhuanlan.zhihu.com/p/623209227)
- STL自定义排序：[https://zhuanlan.zhihu.com/p/600531550](https://zhuanlan.zhihu.com/p/600531550)

