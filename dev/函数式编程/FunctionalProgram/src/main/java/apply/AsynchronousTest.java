package apply;

import lombok.extern.slf4j.Slf4j;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.YearMonth;
import java.time.format.DateTimeFormatter;
import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.util.stream.Collectors.counting;
import static java.util.stream.Collectors.groupingBy;

@Slf4j
public class AsynchronousTest {
    static final int TIME = 1;
    static final DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss z");

    public static void main(String[] args) throws IOException {
        // 异步：线程池
        log.info("开始统计");
        ExecutorService service = Executors.newFixedThreadPool(3);
        service.submit(() -> {
            Map<YearMonth, Long> map = monthlySalesReport();
            for (Map.Entry<YearMonth, Long> e : map.entrySet()) {
                log.info(e.toString());
            }
        });
        log.info("执行其它操作");

        // 异步： CompletableFuture
        // 1) 异步执行任务
        /*
            CompletableFuture.runAsync()    在任务不需要返回结果时
            CompletableFuture.supplyAsync() 在任务需要处理结果时
                thenApply(Function)             转换结果
                thenApplyAsync                  异步转换结果
                thenAccept(Consumer)            消费结果
                thenAcceptAsync(Consumer)       异步消费结果
                thenCombine(y, BiFunction)      合并结果
                thenCombineAsync(y, BiFunction) 异步合并结果
         */

        CompletableFuture.runAsync(() -> log.info("异步操作开始"));
        CompletableFuture<Map<YearMonth, Long>> completableFuture = CompletableFuture.supplyAsync(AsynchronousTest::monthlySalesReport);

        completableFuture.thenAccept(map -> {
            String string = map.entrySet().stream().map(Object::toString).collect(Collectors.joining("\n"));
            try {
                Files.write(Paths.get("./result.txt"), string.getBytes());
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        log.info("异步操作结束");

        System.in.read(); // 不让主线程立刻结束
    }

    private static Map<YearMonth, Long> monthlySalesReport() {
        try (Stream<String> lines = Files.lines(Paths.get("./data.txt"))) {
            Map<YearMonth, Long> collect = lines.skip(1)
                    .map(line -> line.split(","))
                    .collect(groupingBy(array -> YearMonth.from(formatter.parse(array[TIME])), TreeMap::new, counting()));
            return collect;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
