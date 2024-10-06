package pl.dmcs.springbootjsp_iwa.model;

public class Fib {

    private String indexString;
    public String getIndexString() {
        return indexString;
    }
    public void setIndexString(String indexString) {
        this.indexString = indexString;
    }

    public static long calcFib(int n) {
        if (n <= 1) {
            return n;
        }
        long fib = 1;
        long prevFib = 1;

        for (int i = 2; i < n; i++) {
            long temp = fib;
            fib += prevFib;
            prevFib = temp;
        }
        return fib;
    }

}
