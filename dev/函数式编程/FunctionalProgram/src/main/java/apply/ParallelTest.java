package apply;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

import static java.util.stream.Collectors.*;

public class ParallelTest {
    static Pattern reg = Pattern.compile("(\\S+) - \\[(.+)] (.+) (.+)");

    private static final int FILES = 100;

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        parallel();
    }

    private static Map<String, Long> one(int i) {
        try (Stream<String> lines = Files.lines(Paths.get(String.format("web_server_access_%d.log", i)))) {
            return lines
                    .map(reg::matcher) // reg::matcher
                    .filter(Matcher::find) // Matcher::find
                    .map(matcher -> new String[]{matcher.group(1), matcher.group(2), matcher.group(3), matcher.group(4)})
                    .collect(groupingBy(array -> array[2], counting()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void sequence() {
        long start = System.currentTimeMillis();
        Map<String, Long> m0 = new HashMap<>();
        for (int i = 0; i < FILES; i++) {
            Map<String, Long> mi = one(i);
            m0 = merge(m0, mi);
        }
        for (Map.Entry<String, Long> e : m0.entrySet()) {
            System.out.println(e);
        }
        System.out.println("cost: " + (System.currentTimeMillis() - start));
    }

    static Map<String, Long> merge(Map<String, Long> m1, Map<String, Long> m2) {
        return Stream.of(m1, m2)
                .flatMap(m -> m.entrySet().stream())
                .collect(toMap(Map.Entry::getKey, Map.Entry::getValue, Long::sum));
    }

    private static void parallel() throws InterruptedException, ExecutionException {
        long start = System.currentTimeMillis();
        List<CompletableFuture<Map<String, Long>>> futures = new ArrayList<>();
        for (int i = 0; i < FILES; i++) {
            int k = i;
            futures.add(CompletableFuture.supplyAsync(() -> one(k)));
        }

        CompletableFuture<Map<String, Long>> f0 = futures.get(0);
        for (int i = 1; i < futures.size(); i++) {
            CompletableFuture<Map<String, Long>> fi = futures.get(i);
            f0 = f0.thenCombine(fi, ParallelTest::merge);
        }

        Map<String, Long> map = f0.get();
        for (Map.Entry<String, Long> e : map.entrySet()) {
            System.out.println(e);
        }
        System.out.println("cost: " + (System.currentTimeMillis() - start));
    }
}
