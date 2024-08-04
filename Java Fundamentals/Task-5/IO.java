import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.List;

public class IO {
    public static String[] readFile(String filePath) throws FileNotFoundException {
        String text = "";
        File file = new File(filePath);
        Scanner scanner = new Scanner(file);
        while (scanner.hasNextLine()) {
            text += scanner.nextLine() + "\n";
        }
        text = text.substring(0, text.length() - 1);
        scanner.close();
        String[] data = text.split("\n");
        return data;
    }

    public static void writeFile(String filePath, List<Date> dates) throws IOException {
        File file = new File(filePath);
        file.createNewFile();
        FileWriter writer = new FileWriter(filePath);
        for (Date date : dates) {
            writer.write(date + "\n");
        }
        writer.close();
    }
}
