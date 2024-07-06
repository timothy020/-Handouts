import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import static java.util.stream.Collectors.*; //静态导入，少写类名

public class DCollectors {

    public static void main(String[] args) {
        Stream<Hero> stream = Stream.of(
                new Hero("令狐冲", 90),
                new Hero("风清扬", 98),
                new Hero("孤独求败", 100),
                new Hero("冲虚", 98),
                new Hero("方证", 92),
                new Hero("问向天", 88)
        );

        // mapping(x -> y, dc)
//        Map<Integer, List<Integer>> result1 = stream.collect(groupingBy(x -> x.getName().length(),
//                mapping(Hero::getStrength, toList())));
//        result1.entrySet().forEach(System.out::println);

        // counting()
//        Map<Integer, Long> result2 = stream.collect(groupingBy(x -> x.getName().length(),
//                counting()));
//        System.out.println(result2);

        // minBy((a,b) -> int)
//        Map<Integer, Optional<Hero>> result3 = stream.collect(groupingBy(x -> x.getName().length(),
//                minBy(Comparator.comparingInt(Hero::getStrength))));
//        result3.entrySet().forEach(System.out::println);

        // summingInt(x -> int) averageDouble(x -> double)
//        Map<Integer, Integer> result4 = stream.collect(groupingBy(x -> x.getName().length(), summingInt(Hero::getStrength)));
//        result4.entrySet().forEach(System.out::println);

//        Map<Integer, Double> result5 = stream.collect(groupingBy(x -> x.getName().length(), averagingDouble(Hero::getStrength)));
//        result5.entrySet().forEach(System.out::println);

//        Map<Integer, Integer> result6 = stream.collect(groupingBy(x -> x.getName().length(),
//                mapping(Hero::getStrength, reducing(0, Integer::sum))));
//        result6.entrySet().forEach(System.out::println);

    }

    @Data
    @AllArgsConstructor
    public static class Hero {
        private String name;
        private int strength;
    }
}
