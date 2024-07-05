import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Currying {

    @FunctionalInterface
    interface F3 {
        List<Integer> op(List<Integer> a, List<Integer> b, List<Integer> c);
    }

    @FunctionalInterface
    interface Fa {
        Fb op(List<Integer> a);
    }

    @FunctionalInterface
    interface Fb {
        Fc op(List<Integer> b);
    }

    @FunctionalInterface
    interface Fc {
        List<Integer> op(List<Integer> c);
    }


    public static void main(String[] args) {
        List<Integer> listA = Arrays.asList(1,2,3);
        List<Integer> listB = Arrays.asList(4,5,6);
        List<Integer> listC = Arrays.asList(7,8,9);

        // normal
        F3 f3 = (a,b,c) -> {
            List<Integer> res = new ArrayList<>();
            res.addAll(a);
            res.addAll(b);
            res.addAll(c);
            return res;
        };

        System.out.println(f3.op(listA, listB, listC));

        // currying
        System.out.println(step3(step2(step1())));
    }

    private static Fb step1() {
        List<Integer> listA = Arrays.asList(1,2,3);
        Fa fa = a -> b -> c -> {
            List<Integer> res = new ArrayList<>();
            res.addAll(a);
            res.addAll(b);
            res.addAll(c);
            return res;
        };
        return fa.op(listA);
    }

    private static Fc step2(Fb fb) {
        List<Integer> listB = Arrays.asList(4,5,6);
        return fb.op(listB);
    }

    private static List<Integer> step3(Fc fc) {
        List<Integer> listC = Arrays.asList(7,8,9);
        return fc.op(listC);
    }

}