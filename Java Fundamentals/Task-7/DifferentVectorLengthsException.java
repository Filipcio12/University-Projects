import java.util.List;

public class DifferentVectorLengthsException extends Exception {
    private List<Integer> lengthList;

    public DifferentVectorLengthsException() {}

    public DifferentVectorLengthsException(String msg, List<Integer> lengthList) {
        super(msg);
        this.lengthList = lengthList;
    }

    public List<Integer> getLengthList() {
        return lengthList;
    }
}
