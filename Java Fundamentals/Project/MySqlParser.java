import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MySqlParser {

    public static List<String> parseCreateTable(String createTableStatement) {
        List<String> columnNames = new ArrayList<>();

        Pattern pattern = Pattern.compile("\\bCREATE\\s+TABLE\\s+\\w+\\s*\\(([^)]+)\\)", Pattern.CASE_INSENSITIVE);

        Matcher matcher = pattern.matcher(createTableStatement);
        if (matcher.find()) {
            String columnsString = matcher.group(1);

            String[] columnsArray = columnsString.split("\\s*,\\s*");

            for (String column : columnsArray) {
                columnNames.add(column.trim());
            }
        }

        return columnNames;
    }

    public static String extractTableName(String sqlStatement) {
        Pattern pattern = Pattern.compile("\\b(?:FROM|INTO|CREATE\\s+TABLE)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\b", Pattern.CASE_INSENSITIVE);
    
        Matcher matcher = pattern.matcher(sqlStatement);
        if (matcher.find()) {
            return matcher.group(1);
        }
    
        return null;
    }

    public static Map<String, String> parseInsertStatement(String sqlInsert) {
        Map<String, String> row = new HashMap<>();

        String regex = "INSERT\\s+INTO\\s+([a-zA-Z_]+)\\s*\\(([^)]+)\\)\\s*VALUES\\s*\\(([^)]+)\\)";
        Pattern pattern = Pattern.compile(regex, Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(sqlInsert);

        if (matcher.matches()) {
            String[] columnNames = matcher.group(2).split("\\s*,\\s*");
            String[] values = matcher.group(3).split("\\s*,\\s*");

            for (int i = 0; i < columnNames.length; i++) {
                row.put(columnNames[i], values[i]);
            }
            
        } else {
            System.out.println("Invalid INSERT statement");
        }

        return row;
    }

    public static List<String> parseSelectStatement(String selectStatement) {
        List<String> selectedColumns = new ArrayList<>();

        String regex = "SELECT\\s+(.+?)\\s+FROM\\s+([a-zA-Z_]+|\\*)\\s*.*";
        Pattern pattern = Pattern.compile(regex, Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(selectStatement);

        if (matcher.matches()) {
            String selectedColumnsStr = matcher.group(1);

            if ("*".equals(selectedColumnsStr.trim())) {
                selectedColumns.add("*");
            } else {
                for (String column : selectedColumnsStr.split("\\s*,\\s*")) {
                    selectedColumns.add(column.trim());
                }
            }
        } else {
            System.out.println("Invalid SELECT statement");
        }

        return selectedColumns;
    }

    public static Map<String, String> parseUpdateStatement(String updateStatement) {
        Map<String, String> columnValueMap = new HashMap<>();
    
        if (!updateStatement.toLowerCase().startsWith("update ")) {
            System.out.println("Invalid UPDATE statement");
            return columnValueMap;
        }
    
        String[] whereSplit = updateStatement.split("(?i) where ", 2);
        if (whereSplit.length > 1) {
            updateStatement = whereSplit[0];
        }
    
        String[] parts = updateStatement.split("(?i) set ", 2);
        if (parts.length != 2) {
            System.out.println("Invalid UPDATE statement");
            return columnValueMap;
        }
    
        String[] assignments = parts[1].split(", ");
        for (String assignment : assignments) {
            String[] keyValue = assignment.split("=", 2);
            if (keyValue.length == 2) {
                String column = keyValue[0].trim();
                String value = keyValue[1].trim();
                columnValueMap.put(column, value);
            } else {
                System.out.println("Invalid UPDATE statement");
                columnValueMap.clear();
                return columnValueMap;
            }
        }
    
        return columnValueMap;
    }    

    public static String parseDeleteStatement(String sql) {
        String pattern = "DELETE\\s+FROM\\s+(\\w+)";
        Pattern regex = Pattern.compile(pattern, Pattern.CASE_INSENSITIVE);

        Matcher matcher = regex.matcher(sql);

        if (matcher.find()) {
            return matcher.group(1);
        } else {
            return null;
        }
    }

    public static String detectSqlStatementType(String sql) {
        String lowercaseSql = sql.toLowerCase();
    
        String selectPattern = "\\bselect\\b";
        String insertPattern = "\\binsert\\b";
        String updatePattern = "\\bupdate\\b";
        String deletePattern = "\\bdelete\\b";
        String createPattern = "\\bcreate\\s+table\\b";
    
        if (matchesPattern(lowercaseSql, selectPattern)) {
            return "SELECT";
        } else if (matchesPattern(lowercaseSql, insertPattern)) {
            return "INSERT";
        } else if (matchesPattern(lowercaseSql, updatePattern)) {
            return "UPDATE";
        } else if (matchesPattern(lowercaseSql, deletePattern)) {
            return "DELETE";
        } else if (matchesPattern(lowercaseSql, createPattern)) {
            return "CREATE";
        } else {
            return "UNKNOWN";
        }
    }

    private static boolean matchesPattern(String input, String pattern) {
        Pattern regex = Pattern.compile(pattern, Pattern.CASE_INSENSITIVE);
        Matcher matcher = regex.matcher(input);
        return matcher.find();
    }

}
