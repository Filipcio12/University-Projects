import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DateConverter {
    public static Date convertDate(String dateString) {
        String[] dateFormats = {
            "^\\d{2}/\\d{1,2}/\\d{4} [A-Za-z]+$",   // dd/mm/yyyy weekday
            "^[A-Za-z]+ \\d{2}/\\d{1,2}/\\d{4}$",   // weekday dd/mm/yyyy
            "^\\d{4}-\\d{2}-\\d{2} [A-Za-z]+$",     // yyyy-mm-dd weekday
            "^[A-Za-z]+ \\d{2}\\.\\d{2}\\.\\d{4}$", // weekday dd.mm.yyyy
        };

        int formatIndex = -1;
        for (int i = 0; i < dateFormats.length; ++i) {
            Pattern pattern = Pattern.compile(dateFormats[i], Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(dateString);

            if (matcher.find()) {
                formatIndex = i;
                break;
            }
        }

        return parseDate(formatIndex, dateString);
    }

    private static Date parseDate(int formatIndex, String dateString) {
        Date date = new Date();
        if (formatIndex == 0) {
            String[] dandy = dateString.split(" ");
            String[] dateArr = dandy[0].split("/");
            date.day = Integer.parseInt(dateArr[0]);
            date.month = Integer.parseInt(dateArr[1]);
            date.year = Integer.parseInt(dateArr[2]);
            date.weekDay = dandy[1];
        }
        else if (formatIndex == 1) {
            String[] dandy = dateString.split(" ");
            String[] dateArr = dandy[1].split("/");
            date.day = Integer.parseInt(dateArr[0]);
            date.month = Integer.parseInt(dateArr[1]);
            date.year = Integer.parseInt(dateArr[2]);
            date.weekDay = dandy[0];
        }
        else if (formatIndex == 2) {
            String[] dandy = dateString.split(" ");
            String[] dateArr = dandy[0].split("-");
            date.year = Integer.parseInt(dateArr[0]);
            date.month = Integer.parseInt(dateArr[1]);
            date.day = Integer.parseInt(dateArr[2]);
            date.weekDay = dandy[1];
        }
        else if (formatIndex == 3) {
            String[] dandy = dateString.split(" ");
            String[] dateArr = dandy[1].split(".");
            date.day = Integer.parseInt(dateArr[0]);
            date.month = Integer.parseInt(dateArr[1]);
            date.year = Integer.parseInt(dateArr[2]);
            date.weekDay = dandy[0];
        }

        return date;
    }
}
