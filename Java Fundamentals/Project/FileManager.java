import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FileManager {

    public static void writeTableIntoFile(Table table) {
        String fileName = table.tableName + ".txt";
        List<Map<String, String>> rows = table.rows;
        List<String> columnNames = table.columnNames;

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, !isFileEmpty(fileName)))) {
            if (!isFileEmpty(fileName)) {
                clearFile(fileName);
            }

            writeColumns(writer, columnNames);

            for (Map<String, String> row : rows) {
                writeRow(writer, row, columnNames);
            }

            System.out.println("Table '" + table.tableName + "' has been written to the file: " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void createTableIntoNewFile(Table table) {
        String fileName = table.tableName + ".txt";
        List<Map<String, String>> rows = table.rows;
        List<String> columnNames = table.columnNames;

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writeColumns(writer, columnNames);

            for (Map<String, String> row : rows) {
                writeRow(writer, row, columnNames);
            }

            System.out.println("Table '" + table.tableName + "' has been written to the new file: " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void appendRowToFile(Table table, Map<String, String> newRow) {
        String fileName = table.tableName + ".txt";
        List<String> columnNames = table.columnNames;
    
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true))) {
            if (isFileEmpty(fileName)) {
                writeColumns(writer, columnNames);
            }
    
            writeRow(writer, newRow, columnNames);
    
            System.out.println("Row appended to the table '" + table.tableName + "'.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static boolean isFileEmpty(String fileName) throws IOException {
        Path path = Paths.get(fileName);
        return Files.notExists(path) || Files.size(path) == 0;
    }

    private static void clearFile(String fileName) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write("");
        }
    }

    private static void writeColumns(BufferedWriter writer, List<String> values) throws IOException {
        boolean firstColumn = true;
        for (String value : values) {
            if (!firstColumn) {
                writer.write(",");
            }
            writer.write(value);
            firstColumn = false;
        }
        writer.newLine();
    }

    private static void writeRow(BufferedWriter writer, Map<String, String> row, List<String> columnNames) throws IOException {
        boolean firstColumn = true;
        for (String columnName : columnNames) {
            if (!firstColumn) {
                writer.write(",");
            }
            String value = row.get(columnName);
            writer.write(value != null ? value.toString() : "null");
            firstColumn = false;
        }
        writer.newLine();
    }

    public static Table readTableFromFile(String tableName) {
        Table table = new Table();
        table.tableName = tableName;

        String fileName = tableName + ".txt";

        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String firstRow = br.readLine();
            if (firstRow != null) {
                String[] columnNamesArray = firstRow.split(",");
                table.columnNames = List.of(columnNamesArray);
            }

            table.rows = new ArrayList<>();
            String row;
            while ((row = br.readLine()) != null) {
                String[] valuesArray = row.split(",");
                Map<String, String> rowMap = new HashMap<>();

                for (int i = 0; i < table.columnNames.size(); i++) {
                    rowMap.put(table.columnNames.get(i), valuesArray[i]);
                }

                table.rows.add(rowMap);
            }
        } catch (IOException e) {
            System.out.println("Table not found");
            table = new Table();
        }

        return table;
    }
}
