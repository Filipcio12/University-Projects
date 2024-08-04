public class TelephoneNumber implements Comparable<TelephoneNumber> {

    String countryCode;
    String localNumber;

    TelephoneNumber() {
        countryCode = "";
        localNumber = "";
    }

    TelephoneNumber(String countryCode, String localNumber) {
        this.countryCode = new String(countryCode);
        this.localNumber = new String(localNumber);
    }

    public int compareTo(TelephoneNumber oTelephoneNumber) {
        int diff = countryCode.compareTo(oTelephoneNumber.countryCode);
        if (diff != 0) {
            return diff;
        }
        else {
            return localNumber.compareTo(oTelephoneNumber.localNumber);
        }
    }

    public String toString() {
        return ("+" + countryCode + "-" + localNumber);
    }
}
