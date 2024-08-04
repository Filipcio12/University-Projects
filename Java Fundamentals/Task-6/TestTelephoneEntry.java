import java.util.TreeMap;
import java.util.Set;
import java.util.Iterator;

public class TestTelephoneEntry {
    public static void main(String[] args) {
        Person mateusz = new Person(
            "Mateusz", "Galinski", 
            new Address("Łódź", "Piotrkowska", 66), 
            new TelephoneNumber("48", "666666666")
        );
        Person kubus = new Person(
            "Kubus", "Dulas",
            new Address("Warszawa", "Krakowskie Przedmieście", 12),
            new TelephoneNumber("48", "123123123")
        );
        Person marcinek = new Person(
            "Marcinek", "Grawinski",
            new Address("Wrocław", "Inżynierska", 72),
            new TelephoneNumber("00", "999999999")
        );
    
        Company ericson = new Company(
            "Ericson",
            new Address("Sztokholm", "Drottninggatan", 7),
            new TelephoneNumber("72", "766734892")
        );
        Company google = new Company(
            "Google",
            new Address("NYC", "Manhattan", 14),
            new TelephoneNumber("54", "821394320")
        );
        Company intersoft = new Company(
            "INTERsoft",
            new Address("Łódź", "Sienkiewicza", 74),
            new TelephoneNumber("+48", "671230049")
        );
        
        TreeMap <TelephoneNumber, TelephoneEntry> directory = new TreeMap<TelephoneNumber, TelephoneEntry>();
        directory.put(mateusz.telephoneNumber, mateusz);
        directory.put(kubus.telephoneNumber, kubus);
        directory.put(marcinek.telephoneNumber, marcinek);
        directory.put(ericson.telephoneNumber, ericson);
        directory.put(google.telephoneNumber, google);
        directory.put(intersoft.telephoneNumber, intersoft);

        Set <TelephoneNumber> keyset = directory.keySet();
        Iterator <TelephoneNumber> it = keyset.iterator();

        while (it.hasNext()) {
            TelephoneNumber key = it.next();
            System.out.println(directory.get(key).description());
        }
    }
}