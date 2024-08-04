public class Address {
    String city;
    String street;
    int residenceNumber;

    Address() {
        city = null;
        street = null;
        residenceNumber = 0;
    }

    Address(String city, String street, int residenceNumber) {
        this.city = city;
        this.street = street;
        this.residenceNumber = residenceNumber;
    }

    public String toString() {
        return(
            city + ", " + street + " " + residenceNumber
        );
    }
}
