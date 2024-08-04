public class Company extends TelephoneEntry {

    String name;

    Company() {
        name = null;
        address = null;
        telephoneNumber = null;
    }

    Company(String name, Address address, TelephoneNumber telephoneNumber) {
        this.name = name;
        this.address = address;
        this.telephoneNumber = telephoneNumber;
    }

    public String description() {
        return (
            "Company: " + name + ", " + address + ", " + telephoneNumber
        );
    }
}
