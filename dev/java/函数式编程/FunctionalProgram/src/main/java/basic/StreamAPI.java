package basic;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class StreamAPI {
    public static void main(String[] args) {
        // 1.合并
        Stream<Integer> s1 = Stream.of(1, 2, 3);
        Stream<Integer> s2 = Stream.of(4, 5, 6);

        Stream<Integer> concat = Stream.concat(s1, s2);

        // 2.截取：skip, limit
        concat.skip(2).limit(2).forEach(System.out::println);

        // 3.查找： findFirst, findAny
        IntStream stream1 = IntStream.of(1, 2, 3, 5);

//        System.out.println(stream1.filter(x -> (x & 1) == 0).findFirst().orElse(-1));
//        stream1.filter(x -> (x & 1) == 0).findFirst().ifPresent(System.out::println);

        stream1.filter(x -> (x & 1) == 0).findAny().ifPresent(System.out::println);

        // 4.判断： anyMatch, allMatch, noneMatch
        IntStream stream2 = IntStream.of(1, 2, 3, 5);

        System.out.println(stream2.anyMatch(x -> (x & 1) == 0));
//        System.out.println(stream2.allMatch(x -> (x & 1) == 0));
//        System.out.println(stream2.noneMatch(x -> (x & 1) == 0));

        // 5.去重： distinct
        IntStream.of(1,2,3,1,2,3,4,5)
                .distinct()
                .forEach(System.out::println);

        // 6.排序： sorted
        Stream.of(
                new Hero("令狐冲", 90),
                new Hero("风清扬", 98),
                new Hero("孤独求败", 100),
                new Hero("冲虚", 98)
        ).sorted(Comparator.comparingInt(Hero::getStrength).reversed().thenComparingInt(h->h.getName().length())) //武力降序，武力值相等按名字长度升序
                .forEach(System.out::println);

        //7.化简： reduce
        /*
            最大值，最小值，求和，求个数
            .reduce((p,x) -> r)
            .reduce(init, (p, x) -> r)
            .reduce(init, (p, x) -> r, (r1, r2) -> r)
         */
        Stream<Hero> stream = Stream.of(
                new Hero("令狐冲", 90),
                new Hero("风清扬", 98),
                new Hero("孤独求败", 100),
                new Hero("冲虚", 98)
        );

        // ①武力值最高的Hero
//        Optional<Hero> result1 = stream.reduce((h1, h2) -> h1.getStrength() > h2.getStrength() ? h1 : h2);
//        System.out.println(result1);

//        Hero result2 = stream.reduce(new Hero("-", -1), (h1, h2) -> h1.getStrength() > h2.getStrength() ? h1 : h2);
//        System.out.println(result2);

        // ②高手总数
//        Integer result3 = stream.map(h -> 1).reduce(0, Integer::sum);
//        System.out.println(result3);

        // ③语法糖
//        System.out.println(stream.max(Comparator.comparingInt(Hero::getStrength)));;
//        System.out.println(stream.count());
//        System.out.println(stream.mapToInt(Hero::getStrength).sum());
        System.out.println(stream.mapToInt(Hero::getStrength).average());

        // 8.收集
        /*
            .collect(() -> c, (c, x) -> void, ?)

            () -> c         创建容器
            (c, x) -> void  将元素x添加到容器
         */

        Stream<String> strStream = Stream.of("令狐冲", "风清扬", "孤独求败", "冲虚");

//        List<String> result4 = strStream.collect(ArrayList::new, ArrayList::add, (a, b) -> {});
//        System.out.println(result4);

//        StringBuilder result5 = strStream.collect(StringBuilder::new, StringBuilder::append, (a, b) -> {});
//        System.out.println(result5);

//        String result6 = strStream.collect(Collectors.joining("-"));
//        System.out.println(result6);

        Map<Integer, List<String>> result7 = strStream.collect(Collectors.groupingBy(String::length, Collectors.toList()));
        for(Map.Entry<Integer, List<String>> entry :result7.entrySet()) {
            System.out.println(entry);
        }

    }


    @Data
    @AllArgsConstructor
    public static class Hero{
        private String name;
        private int strength;
    }
}
