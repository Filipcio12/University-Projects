import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Table {
    public String tableName;
    public List<Map<String, String>> rows;
    public List<String> columnNames;

    Table() {
        rows = new ArrayList<>();
        columnNames = new ArrayList<>();
    }
}
