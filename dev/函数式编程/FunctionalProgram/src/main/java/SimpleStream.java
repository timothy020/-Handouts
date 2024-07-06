import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class SimpleStream<T> {
    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1,2,3,4,5,1,2,3);

        // output: 1 9 25
        SimpleStream.of(list)
                .filter(x -> ( x & 1 ) == 1)
                .map(x -> x*x)
                .forEach(System.out::println);

        // output: 21  1  5
        System.out.println(SimpleStream.of(list).reduce(0, Integer::sum));
        System.out.println(SimpleStream.of(list).reduce(Integer.MAX_VALUE, Integer::min));
        System.out.println(SimpleStream.of(list).reduce(Integer.MIN_VALUE, Integer::max));

        // output: [1, 2, 3, 4, 5]  12345123  1-2-3-4-5-1-2-3
        HashSet<Integer> collect1 = SimpleStream.of(list).collect(HashSet::new, HashSet::add);
        System.out.println(collect1);

        StringBuilder collect2 = SimpleStream.of(list).collect(StringBuilder::new, StringBuilder::append);
        System.out.println(collect2.toString());

        StringJoiner collect3 = SimpleStream.of(list)
                .map(String::valueOf)
                .collect(() -> new StringJoiner("-"), StringJoiner::add);
        System.out.println(collect3.toString());

        // output: {1=2, 2=2, 3=2, 4=1, 5=1}
        HashMap<Integer, Integer> collect4 = SimpleStream.of(list).collect(HashMap::new, (map, t) -> {
            if(!map.containsKey(t)) {
                map.put(t, 1);
            } else {
                Integer v = map.get(t);
                map.put(t, v+1);
            }
        });
        System.out.println(collect4);

        HashMap<Integer, Integer> collect5 = SimpleStream.of(list).collect(HashMap::new,
                (map, t) -> {
                    Integer i = map.computeIfAbsent(t, k -> 0);
                    map.put(t, i+1);
                });
        System.out.println(collect5);

        HashMap<Integer, AtomicInteger> collect6 = SimpleStream.of(list).collect(HashMap::new,
                (map, t) -> map.computeIfAbsent(t, k -> new AtomicInteger()).getAndIncrement());
        System.out.println(collect6);


    }
    // 收集
    public <C> C collect(Supplier<C> supplier, BiConsumer<C, T> biConsumer) {
        C c = supplier.get(); //创建容器
        for (T t : collection) {
            biConsumer.accept(c, t);
        }
        return c;
    }

    // 化简
    public T reduce(T o, BinaryOperator<T> binaryOperator) {
        T res = o;
        for(T t : collection) {
            res = binaryOperator.apply(res, t);
        }
        return res;
    }

    // 基本操作
    public SimpleStream<T> filter(Predicate<T> predicate) {
        List<T> res = new ArrayList<>();
        for(T t : collection) {
            if(predicate.test(t)) {
                res.add(t);
            }
        }
        return new SimpleStream<>(res);
    }

    public <U> SimpleStream<U> map(Function<T, U> function) {
        List<U> res = new ArrayList<>();
        for(T t : collection) {
            U u = function.apply(t);
            res.add(u);
        }
        return new SimpleStream<>(res);
    }

    public void forEach(Consumer<T> consumer) {
        for(T t : collection) {
            consumer.accept(t);
        }
    }

    // 构造函数与工厂方法
    private final Collection<T> collection;
    private SimpleStream(Collection<T> collection) {
        this.collection = collection;
    }
    public static <T> SimpleStream<T> of(Collection<T> collection) {
        return new SimpleStream<>(collection);
    }

}
