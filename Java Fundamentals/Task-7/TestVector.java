import java.io.IOException;
import java.util.List;

public class TestVector {
    public static String ordinal(int i) {
        int mod100 = i % 100;
        int mod10 = i % 10;
        if(mod10 == 1 && mod100 != 11) {
            return i + "st";
        } else if(mod10 == 2 && mod100 != 12) {
            return i + "nd";
        } else if(mod10 == 3 && mod100 != 13) {
            return i + "rd";
        } else {
            return i + "th";
        }
    }
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Args is the number of input vectors!");
            return;
        }

        int num = 0;
        try {
            num = Integer.parseInt(args[0]);   
        } catch (NumberFormatException ex) {
            System.out.println("Failure parsing int.");
        }
        if (num < 2) {
            System.out.println("You must input at least 2 vectors.");
            return;
        }

        UserInput userInput = new UserInput();
        Vector sum;
        while (true) {
            try {
                sum = Vector.sumVectors(userInput.inputVectors(num));
                break;
            } catch (DifferentVectorLengthsException ex) {
                String msg = ex.getMessage();
                List<Integer> lengthList = ex.getLengthList();
                for (int i = 0; i < lengthList.size(); ++i) {
                    msg += ordinal(i + 1) + " vector length is " + lengthList.get(i) + ".\n";
                }
                for (int i = 0; i < lengthList.size(); ++i) {
                    if (i > 0 && lengthList.get(i) > lengthList.get(i - 1)) {
                        msg += ordinal(i + 1) + " vector length is bigger than " + ordinal(i) + ".\n"; 
                    }
                    if (i > 0 && lengthList.get(i) < lengthList.get(i - 1)) {
                        msg += ordinal(i + 1) + " vector length is lower than " + ordinal(i) + ".\n"; 
                    }
                }
                System.out.println(msg);
            }
        }
        userInput.close();
        System.out.println(sum);

        try {
            IO.writeFile("result.txt", sum);
        } catch (IOException ex) {
            System.out.println("\nError opening the file.");
        } 
    }
}