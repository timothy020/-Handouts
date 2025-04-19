package apply;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.YearMonth;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Stream;

import static java.util.stream.Collectors.*;

public class AnalysisTest {
    /*
        数据格式
        0       1       2       3       4       5       6     7      8        9     10    11
        序号    下单时间  订单编号  商品编号 类别编号  类别码   品牌   价格   用户编号   年龄   性别   地区
     */
    static final int INDEX = 0;
    static final int TIME = 1;
    static final int ORDER_ID = 2;
    static final int PRODUCT_ID = 3;
    static final int CATEGORY_ID = 4;
    static final int CATEGORY_CODE = 5;
    static final int BRAND = 6;
    static final int PRICE = 7;
    static final int USER_ID = 8;
    static final int USER_AGE = 9;
    static final int USER_SEX = 10;
    static final int USER_REGION = 11;
    static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss z");

    public static void main(String[] args) {
        // 1) 统计每月的销售量
//        case1();
        // 2) 统计销售量最高的月份
//        case2();
        // 3) 统计销售量最高的商品
//        case3();
        // 4)下单最多的前十名用户
//        case42();
//        case41();
        // 5)每个地区下单前三的用户
//        case5();
        // 6) 按照一级类别统计销量
//        case6();
        // 7) 按照价格区间统计销量
//        case7();
        // 8) 不同年龄段的女性所下不同类型的订单数
        case8();
    }

    static String ageRange(String[] array) {
        int age = Double.valueOf(array[USER_AGE]).intValue();
        if(age < 18) {
            return "[0, 18)";
        } else if(age <30) {
            return "[18,30)";
        } else if(age<50) {
            return "[30,50)";
        } else {
            return "[50,∞)";
        }
    }

    // 8) 不同年龄段的女性所下不同类型的订单数
    public static void case8() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            Map<String, TreeMap<String, Long>> map = lines.skip(1)
                    .map(line -> line.split(","))
                    .filter(array -> array[USER_SEX].equals("女"))
                    .filter(array -> !array[CATEGORY_CODE].isEmpty())
                    .collect(groupingBy(AnalysisTest::ageRange,
                            groupingBy(AnalysisTest::firstCategory, TreeMap::new, counting())));

            for (Map.Entry<String, TreeMap<String, Long>> e1 : map.entrySet()) {
                for (Map.Entry<String, Long> e2 : e1.getValue().entrySet()) {
                    System.out.printf("%-12s%-15s%s%n", e1.getKey(), e2.getKey(), e2.getValue());
                }
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static String priceRange(Double price) {
        if(price <100) {
            return "[0,100)";
        } else if (price >=100 &&price<500) {
            return"[100,500)";
        } else if (price >=500 &&price<1000) {
            return "[500,1000)";
        } else {
            return "[1000,∞)";
        }
    }

    // 7) 按照价格区间统计销量
    public static void case7() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            lines.skip(1)
                    .map(line -> line.split(","))
                    .map(array -> Double.valueOf(array[PRICE]))
                    .collect(groupingBy(AnalysisTest::priceRange, counting()))
                    .entrySet().forEach(System.out::println);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static String firstCategory(String[] array) {
        String s = array[CATEGORY_CODE];
        int idx = s.indexOf(".");
        return s.substring(0, idx);
    }

    // 6) 按照一级类别统计销量
    public static void case6() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            lines.skip(1)
                    .map(line -> line.split(","))
                    .filter(array -> !array[CATEGORY_CODE].isEmpty())
                    .collect(groupingBy(AnalysisTest::firstCategory, TreeMap::new, counting()))
                    .entrySet().forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 5)每个地区下单前三的用户
    public static void case5() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            Map<String, Map<String, Long>> collect = lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> array[USER_REGION],
                            groupingBy(array -> array[USER_ID], counting())));

            collect.entrySet().stream().map(e -> new AbstractMap.SimpleEntry<>(
                    e.getKey(),
                    e.getValue().entrySet().stream()
//                            .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
//                            .limit(3)
//                            .collect(toList()))
                            .collect(
                                    () -> new MyQueue<Map.Entry<String, Long>>(Map.Entry.comparingByValue(), 3),
                                    MyQueue::add,
                                    MyQueue::addAll
                            )
            )).forEach(System.out::println);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    static class MyQueue<E> extends PriorityQueue<E> {
        private int max;

        public MyQueue(Comparator<E> comparator, int max) {
            super(comparator);
            this.max = max;
        }

        @Override
        public boolean offer(E e) {
            boolean r = super.offer(e);
            if(this.size() > max) {
                super.poll();
            }
            return r;
        }
    }

    // 4)下单最多的前十名用户（小顶堆）
    public static void case41() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            Set<Map.Entry<String, Long>> collect = lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> array[USER_ID], counting()))
                    .entrySet();

            // 小顶堆
            MyQueue<Map.Entry<String, Long>> queue = collect.stream().collect(
                    () -> new MyQueue<Map.Entry<String, Long>>(Map.Entry.comparingByValue(), 10),
                    MyQueue::add,
                    MyQueue::addAll
            );

            while (!queue.isEmpty()) {
                System.out.println(queue.poll());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 4)下单最多的前十名用户
    public static void case42() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> array[USER_ID], counting()))
                    .entrySet().stream()
                    .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                    .limit(10)
                    .forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 3) 统计销售量最高的商品
    public static void case3() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> array[PRODUCT_ID], counting()))
                    .entrySet().stream().max(Map.Entry.comparingByValue())
                    .ifPresent(System.out::println);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 2) 统计销售量最高的月份
    public static void case2() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> YearMonth.from(formatter.parse(array[TIME])), counting()))

                    .entrySet().stream().max(Map.Entry.comparingByValue())
                    .ifPresent(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 1) 统计每月的销售量
    public static void case1() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            Map<YearMonth, Long> collect = lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> YearMonth.from(formatter.parse(array[TIME])), TreeMap::new, counting()));
            System.out.println(collect);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}
