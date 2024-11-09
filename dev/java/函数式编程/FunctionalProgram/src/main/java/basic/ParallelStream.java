package basic;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;
import java.util.function.Function;
import java.util.stream.Collector;
import java.util.stream.Stream;

public class ParallelStream {
    public static void main(String[] args) {
        List<Integer> res = Stream.of(1, 2, 3, 4)
                .parallel()
                .collect(Collector.of(
                        Vector::new,         // 1.如何创建容器
                        Vector::add,         // 2.如何向容器添加数据
                        (list1, list2) -> {
                            list1.addAll(list2);
                            return list1;
                        },                      // 3.如何合并两个容器的数据
                        Function.identity()     // 4.收尾
                        // 5.特性：并发，是否需要收尾，是否需要保证收集顺序
                        , Collector.Characteristics.IDENTITY_FINISH    // 不需要收尾
                        , Collector.Characteristics.UNORDERED          // 不需要保证顺序
                        , Collector.Characteristics.CONCURRENT         // 容器需要支持并发
                ));

        System.out.println(res);
    }
}
