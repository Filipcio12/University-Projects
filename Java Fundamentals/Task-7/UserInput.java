import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class UserInput {
    private Scanner scanner;

    public UserInput() {
        scanner = new Scanner(System.in);
    }

    public List<Vector> inputVectors(int num) {
        List<Vector> vectors = new ArrayList<Vector>();
        for (int i = 0; i < num; ++i) {
            String input = scanner.nextLine();
            Vector v = new Vector(input);
            vectors.add(v);
        }
        return vectors;
    }

    public void close() {
        scanner.close();
    }
}
