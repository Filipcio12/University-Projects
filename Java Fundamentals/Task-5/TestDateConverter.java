import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

class TestDateConverter {
    public static void main(String[] args) {
        String[] data = null;

        try {
            data = IO.readFile("InputData.txt");
        }
        catch (FileNotFoundException ex) {
            System.out.println("File not found.");
            return;
        }

        List<Date> dates = new ArrayList<Date>();

        for (String d : data) {
            Date date = DateConverter.convertDate(d);
            if (!date.equals(new Date())) {
                dates.add(date);
            }
        }

        Collections.sort(dates);

        List<Date> newDates = new ArrayList<Date>();
        newDates.add(dates.get(0));

        int numOfRewrites = 0;
        for (int i = 1; i < dates.size(); ++i) {
            if (!dates.get(i).equals(dates.get(i - 1))) {
                newDates.add(dates.get(i));
            }
            else {
                numOfRewrites++;
            }
        }

        dates = newDates;

        System.out.println(numOfRewrites);

        try {
            IO.writeFile("OutputData.txt", dates);
        }
        catch (IOException ex) {
            System.out.println("Error writing into the file.");
        }
        
    }
}