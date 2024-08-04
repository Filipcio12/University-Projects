public class Person extends TelephoneEntry {

    String name;
    String lastName;

    Person() {
        name = null;
        lastName = null;
        address = null;
        telephoneNumber = null;
    }

    Person(
        String name, String lastName, 
        Address address, TelephoneNumber telephoneNumber
    ) {
        this.name = name;
        this.lastName = lastName;
        this.address = address;
        this.telephoneNumber = telephoneNumber;
    }

    public String description() {
        return (
            "Person: " + name + ", " + lastName + ", " + 
            address + ", " + telephoneNumber
        );
    }
}
