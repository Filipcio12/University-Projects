import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class IO {
    public static void writeFile(String filePath, Vector v) throws IOException {
        File file = new File(filePath);
        file.createNewFile();
        FileWriter writer = new FileWriter(filePath);
        writer.write(v.toString());
        writer.close();
    }
}
