## 基本概念

合格的函数

- input->output
- 不引用外部可变数据（stream-final)



函数的本质是规则，函数对象固化规则，使之可传递



1. 行为参数化

```java
public class FunctionalPro {

    @AllArgsConstructor
    @ToString
    static class Student {
        private String name;
        private Integer age;
        private String sex;
    }

    public static void main(String[] args) {
        List<Student> list = Arrays.asList(
                new Student("张无忌",18,"男"),
                new Student("杨不悔",16,"女"),
                new Student("周芷若",19,"女"),
                new Student("宋青书",20,"男")
        );

        //lambda本质是接口的匿名实例化
        System.out.println(filter(list, student -> student.name.equals("张无忌")));

        System.out.println(filter(list, student -> student.age < 19));

        System.out.println(filter(list, student -> student.sex.equals("女")));
    }

    @FunctionalInterface //确保只有一个抽象方法
    interface Lambda {
        boolean predicate(Student student);
    }

    static private List<Student> filter(List<Student> list, Lambda pred) {
        List<Student> res = new ArrayList<>();
        for(Student student : list) {
            if(pred.predicate(student)) {
                res.add(student);
            }
        }
        return res;
    }
}
```

2. 延迟执行

*行为参数化后带来的结果就是可以自行选择执行时机，外部if->内部if，提高了整体性*

```java
public class FunctionalPro {

    public static void main(String[] args) {

        int logLevel = 1;

        if(logLevel == 1) {
            excute();
        }

        showLog(logLevel, () -> excute()); //等价showLog(logLevel, FunctionalPro::excute);
    }

    static void showLog(int level, Supplier<String> supplier) {
        if(level == 1) {
            System.out.println(supplier.get());
        }
    }

    static String excute() {
        System.out.println("执行耗时操作");
        return "需要的结果";
    }

}

```



## 函数对象类型

什么是函数接口（Functional Interface)：a Single Abstract Method(SAM) interface

```java
@FunctionalInterface //确保只有一个抽象方法
interface Lambda {
    boolean predicate(Student student);
}
```



什么是函数对象(Functional Object)：函数接口（Functional Interface）的实现类

类型：

1. lambda表达式 `Lmbda lambda = student -> student.age <= 18`
2. 方法引用（现有方法转为含数据对象）

| 方法引用            | 对应的Lambda表达式                       | 类型             |
| ------------------- | ---------------------------------------- | ---------------- |
| Math::max           | (int a, int b) -> Math.max(a,b);         | 类的静态方法     |
| Student::getName    | (Student stu) -> stu.getName();          | 类的非静态方法   |
| System.out::println | (Object obj) -> System.out.println(obj); | 对象的非静态方法 |
| Student::new        | () -> new Student();                     | 对象的new方法    |

*本质：静态方法直接调用，非静态方法需要对象调用*



Jdk中已定义的函数接口：

| 类型              | 函数接口形式               | 对应的lambda   |
| ----------------- | -------------------------- | -------------- |
| Runnable          | void run();                | () -> void     |
| Callable<V>       | V call();                  | () -> V        |
| Supplier<T>       | T get(); [Lazy Evaluation] | () -> T        |
| Consumer<T>       | void accept(T t);          | (T) -> void    |
| Function<T,R>     | R apply(T t);              | (T) -> R       |
| Predicate<T>      | boolean test(T t);         | (T) -> boolean |
| BiFunction<T,U,R> | R apply(T t, U u);         | (T, U) -> R    |



## 闭包和柯里化

**闭包**：

捕获外部变量，变量需要时`final`或者`effective final`

```java
public class FunctionalPro {
    public static void main(String[] args) {
        List<Runnable> list = new ArrayList<>();
        for(int i = 0; i < 10; i++) {
            int k = i + 1;
            Runnable task = () -> System.out.println(Thread.currentThread()+"：执行任务"+k);
            list.add(task);
        }

        ExecutorService executorService = Executors.newCachedThreadPool();
        for(Runnable task : list) {
            executorService.submit(task);
        }
    }
}
```

**柯里化**：

让接收多个参数的函数转换成一系列接收一个参数的函数（闭包传递前端参数），让函数分步执行

> 代码见：currying.java



## 高阶函数

含义：是其它函数对象的使用者。

作用：

- 将通用、复杂的逻辑隐含在**高阶函数**
- 内将易变、未定的逻辑放在外部的**函数对象**中

实现简单流：

> 代码见：SimpleStream.java 



## Stream API

流的特性：一次使用，两类操作（中间操作 lazy，终结操作 eager）



构建与生成：

```java
//构建流
List.stream();
Arrays.Stream();
Stream.of(1,2,3);
//生成流
IntStream.range(1,10).forEach(System.out::println);

IntStream.iterate(1, x->x+1).limit(10).forEach(System.out::println);
IntStream.iterate(1, x->x<=9, x->x+1).forEach(System.out::println);

IntStream.generate(()->ThreadLocalRandom.current().nextInt(100)).limite(10).forEach(System.out::println);
ThreadLocalRandom.current().ints(5, 0, 100).forEach(System.out::println);
    
```

流操作：

| 操作         | 写法                                                         |
| ------------ | ------------------------------------------------------------ |
| 合并         | Stream.of(s1, s2);                                           |
| 截取（分页） | skip(n);                                                     |
|              | limit(n);                                                    |
| 查找         | filter(Predicate p).findAny();                               |
|              | filter(Predicate p).findFirst();                             |
| 判断         | anyMatch(Predicate p);                                       |
|              | allMatch(Predicate p);                                       |
|              | noneMatch(Predicate p);                                      |
| 去重         | distinct()                                                   |
| 排序         | sorted(Comparator c);                                        |
| 化简         | reduce(p,x) -> r); <br />reduce(init, (p, x) -> r); <br />reduce(init, (p, x) -> r, (r1, r2) -> r) |
| 收集         | collect(Supplier<R> supplier,BiConsumer<R, ? super T> accumulator,BiConsumer<R, R> combiner);<br />collect(Collector<? super T, A, R> collector); |

> 代码见： StreamAPI.java



下游收集器：

| 作用       | 下游收集器                   |
| ---------- | ---------------------------- |
| 映射后收集 | mapping(x -> y, dc);         |
| 计数       | counting();                  |
| 计算       | summingInt(x -> int);        |
|            | averageDouble(x -> double);  |
| 化简       | reducing(init, (p, x) -> r); |

> 代码见： DCollector.java



基本类型流：

- IntStream
- LongStream
- DoubleStream

基本流方法：

| 方法                          | 作用                          |
| ----------------------------- | ----------------------------- |
| intstream.mapToobj(int ->obj) | 转换为obj流                   |
| stream.mapToInt(x -> int)     | obj流转换为基本流             |
| intstream.boxed()             | 转换为Integer流               |
| intstream.sum()               | 求和                          |
| intstream.min()               | 求最小值，返回Optional        |
| intstream.max()               | 求最大值，返回optional        |
| intstream.average()           | 求平均值，返回Optional        |
| intstream.summarystatistics() | 综合count sum min max average |

> Stream API汇总见： Stream.html

## 并行流

方法： `.parallel()`

并发收集器组成部分：

![image-20240706111945124](https://raw.githubusercontent.com/timothy020/pic/main/img/image-20240706111945124.png)

| 枚举                                      | 特性             |
| ----------------------------------------- | ---------------- |
| Collector.Characteristics.IDENTITY_FINISH | 不需要收尾       |
| Collector.Characteristics.UNORDERED       | 不需要保证顺序   |
| Collector.Characteristics.CONCURRENT      | 容器需要支持并发 |



一般用法：

1. CONCURRENT+UNORDERED+线程安全容器
2. 默认 + 线程不安全容器



效率：

- 数据量少时： 单线程收集
- 数据量多时： 多线程Concurent收集 > 多线程非Concurrent收集
- 处理基本类型时： 基本流 $\approx$ 普通循环 >> 普通Stream流



> 代码见： ParallelStream



## 具体应用

1. 统计分析

> 代码见： AnalysisTest.java

2. 异步处理

> 代码见： 

3. 框架设计

> 代码见： 

4. 并行计算

> 代码见： 

5. UI设计

> 代码见： 