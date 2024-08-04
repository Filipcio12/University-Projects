import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class MyDatabase {
    public static final String tableFormat = new String("%-25s");

    Table table;

    public MyDatabase() {
        table = new Table();
    }

    public void createTable(List<String> columnNames, String tableName) {
        table = new Table();
        table.tableName = tableName;
        table.columnNames = columnNames;
        FileManager.createTableIntoNewFile(table);
    }

    public void insertRow(Map<String, String> row) {
        table.rows.add(row);
        FileManager.appendRowToFile(table, row);
    }

    public void select(List<String> selectedColumns, List<Map<String, String>> selectedRows) {
        if (selectedColumns.size() == 0) {
            return;
        }
        if (selectedColumns.get(0) == "*") {
            for (String columnName : table.columnNames) {
                System.out.printf(tableFormat, columnName);
            }
            System.out.println();

            for (Map<String, String> row : selectedRows) {
                for (String columnName : table.columnNames) {
                    String value = row.get(columnName);
                    System.out.printf(tableFormat, value != null ? value : "null");
                }
                System.out.println();
            }
            return;
        }
        for (String selectedColumn : selectedColumns) {
            System.out.printf(tableFormat, selectedColumn);
        }
        System.out.println();

        for (Map<String, String> row : selectedRows) {
            for (String selectedColumn : selectedColumns) {
                System.out.printf(tableFormat, row.get(selectedColumn));
            }
            System.out.println();
        }
    }

    public void update(Map<String, String> columnValueMap, List<Map<String, String>> selectedRows) {
        List<Map<String, String>> rows = table.rows;
    
        for (Map<String, String> row : selectedRows) {
            for (Map.Entry<String, String> entry : columnValueMap.entrySet()) {
                String columnName = entry.getKey();
                if (table.columnNames.contains(columnName)) {
                    row.put(columnName, entry.getValue());
                } else {
                    System.out.println("Invalid here");
                    System.out.println(columnName);
                    System.out.println("Invalid UPDATE statement");
                    return;
                }
            }
        }
    
        for (Map<String, String> row : rows) {
            if (selectedRows.contains(row)) {
                int index = rows.indexOf(row);
                rows.set(index, row);
            }
        }
    
        table.rows = rows;
        FileManager.writeTableIntoFile(table);
    }

    public void delete(List<Map<String, String>> selectedRows) {
        if (selectedRows != null && !selectedRows.isEmpty()) {
            table.rows.removeAll(selectedRows);
        }
        FileManager.writeTableIntoFile(table);
    }

    public void executeSqlStatement(String sql) {
        String statementType = MySqlParser.detectSqlStatementType(sql);

        String tableName = MySqlParser.extractTableName(sql);
        if (tableName != null && !tableName.equals(table.tableName) && !statementType.equals("CREATE")) {
            table = FileManager.readTableFromFile(tableName);
        }

        switch (statementType) {
            case "SELECT":
                select(MySqlParser.parseSelectStatement(sql), WhereParser.parseWhere(sql, table.rows));
                break;
            case "INSERT":
                insertRow(MySqlParser.parseInsertStatement(sql));
                break;
            case "UPDATE":
                update(MySqlParser.parseUpdateStatement(sql), WhereParser.parseWhere(sql, table.rows));
                break;
            case "DELETE":
                delete(WhereParser.parseWhere(sql, table.rows));
                break;
            case "CREATE":
                createTable(MySqlParser.parseCreateTable(sql), tableName);
                break;
            default:
                System.out.println("Unknown SQL statement type");
        }
    }

    public static void createSampleDB(MyDatabase db) {
        String createStatement = "CREATE TABLE employees (employee_id, first_name, last_name, job_title, department, hire_date, salary)";
        db.createTable(MySqlParser.parseCreateTable(createStatement), "employees");

        String insertStatement1 = "INSERT INTO employees (employee_id, first_name, last_name, job_title, department, hire_date, salary) " +
                                 "VALUES (1, 'John', 'Doe', 'Software Engineer', 'IT', '2022-01-01', 80000)";

        String insertStatement2 = "INSERT INTO employees (employee_id, first_name, last_name, job_title, department, hire_date, salary) " +
                                 "VALUES (2, 'Jane', 'Smith', 'Marketing Specialist', 'Marketing', '2022-02-15', 70000)";

        String insertStatement3 = "INSERT INTO employees (employee_id, first_name, last_name, job_title, department, hire_date, salary) " +
                                 "VALUES (3, 'Mike', 'Johnson', 'Financial Analyst', 'Finance', '2022-03-30', 75000)";
        
        db.insertRow(MySqlParser.parseInsertStatement(insertStatement1));
        db.insertRow(MySqlParser.parseInsertStatement(insertStatement2));
        db.insertRow(MySqlParser.parseInsertStatement(insertStatement3));

        FileManager.writeTableIntoFile(db.table);
    }

    public static void main(String[] args) {
        MyDatabase db = new MyDatabase();

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Enter SQL command (or 'EXIT' to quit): ");
            String command = scanner.nextLine().trim();

            if (command.equalsIgnoreCase("EXIT")) {
                System.out.println("Exiting...");
                break;
            }

            db.executeSqlStatement(command);
        }

        scanner.close();
    }
}