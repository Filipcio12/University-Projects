import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class WhereParser {
    public static String extractWhereCondition(String sqlStatement) {
        Pattern wherePattern = Pattern.compile("\\bWHERE\\b\\s*(.+?)\\s*(?:$|GROUP BY|HAVING|ORDER BY|\\bLIMIT\\b)", Pattern.CASE_INSENSITIVE | Pattern.DOTALL);

        Matcher matcher = wherePattern.matcher(sqlStatement);

        if (matcher.find()) {
            String whereCondition = matcher.group(1).trim();
            return whereCondition;
        } else {
            return null;
        }
    }

    public static Map<String, String> extractConditionParts(String whereCondition) {
        Pattern conditionPattern = Pattern.compile("([\\w_]+)\\s*([=<>]+)\\s*('[^']*'|[\\d.]+)", Pattern.CASE_INSENSITIVE);

        Matcher matcher = conditionPattern.matcher(whereCondition);

        if (matcher.find()) {
            String columnName = matcher.group(1);
            String operator = matcher.group(2);
            String value = matcher.group(3);

            System.out.println("Column: " + columnName);
            System.out.println("Operator: " + operator);
            System.out.println("Value: " + value);

            Map<String, String> conditionParts = new HashMap<>();
            conditionParts.put("columnName", columnName);
            conditionParts.put("operator", operator);
            conditionParts.put("value", value);

            return conditionParts;
        } else {
            System.out.println("Invalid or unsupported WHERE condition.");
            return null;
        }
    }

    public static List<Map<String, String>> filterRows(String columnName, String condition, String value, List<Map<String, String>> rows) {
        List<Map<String, String>> matchingRows = new ArrayList<>();

        for (Map<String, String> row : rows) {
            if (row.containsKey(columnName)) {
                String columnValue = row.get(columnName);

                if (compareValues(columnValue, condition, value)) {
                    matchingRows.add(row);
                }
            }
        }

        return matchingRows;
    }

    private static boolean compareValues(String columnValue, String condition, String value) {
        if ("=".equals(condition) && columnValue.equals(value)) {
            return true;
        } else if (">".equals(condition) && ((Comparable<String>) columnValue).compareTo(value) > 0) {
            return true;
        } else if ("<".equals(condition) && ((Comparable<String>) columnValue).compareTo(value) < 0) {
            return true;
        } else {
            return false;
        }
    }

    public static List<Map<String, String>> parseWhere(String sqlStatement, List<Map<String, String>> rows) {
        String whereCondition = extractWhereCondition(sqlStatement);

        if (whereCondition != null) {
            Map<String, String> conditionParts = extractConditionParts(whereCondition);

            String columnName = conditionParts.get("columnName");
            String condition = conditionParts.get("operator");
            String value = conditionParts.get("value");

            return filterRows(columnName, condition, value, rows);
        } else {
            return rows;
        }
    }
}
