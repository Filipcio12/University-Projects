import java.util.Scanner;

public class Fib {

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

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = 1;

        System.out.println("Input a positive integer and the program will return the corresponding Fibonacci number:");

        while (true) {
            try {
                String inputString = scanner.nextLine();
                n = Integer.parseInt(inputString);
                if (n < 1) {
                    System.out.println("Incorrect input");
                    continue;
                }
                break;
            } catch (Exception ex) {
                System.out.println("Incorrect input");
            }
        }

        long result = calcFib(n);
        
        if (result < 0) {
            System.out.println("Overflow");
        } else {
            System.out.println(result);
        }

        scanner.close();
    }
}