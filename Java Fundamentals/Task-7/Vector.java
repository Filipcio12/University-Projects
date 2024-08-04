import java.util.ArrayList;
import java.util.List;

public class Vector {
    private List<Integer> components;

    Vector() {
        components = new ArrayList<>();
    }

    Vector(String input) {
        components = new ArrayList<>();

        String[] nums = input.split(",");
        for (String num : nums) {
            try {
                int component = Integer.parseInt(num);
                components.add(component);
            }
            catch(NumberFormatException ex) {}
        }

        if (components.isEmpty()) {
            components.add(0);
        }
    }

    public Vector clone() {
        Vector vector = new Vector();
        for (int comp : components) {
            vector.components.add(comp);
        }
        return vector;
    }
    
    public String toString() {
        String vectorString = "[";
        
        for (Integer component : components) {
            vectorString += component + ", ";
        }

        vectorString = vectorString.substring(0, vectorString.length() - 2);
        vectorString += "]";

        return vectorString;
    }

    public int length() {
        return components.size();
    }

    public void add(Vector oVector) throws DifferentVectorLengthsException {
        int length = length();
        if (length != oVector.length()) {
           throw new DifferentVectorLengthsException();
        }

        for (int i = 0; i < length; ++i) {
            components.set(i, 
            components.get(i) + oVector.components.get(i));
        }
    }

    public static Vector sumVectors(List<Vector> vectors) throws DifferentVectorLengthsException {
        List<Integer> lengthList = new ArrayList<Integer>();
        for (Vector v : vectors) {
            lengthList.add(v.length());
        }

        Vector sum = vectors.get(0).clone();
        for (int i = 1; i < vectors.size(); ++i) {
            try {
                sum.add(vectors.get(i));
            } catch (DifferentVectorLengthsException ex) {
                throw new DifferentVectorLengthsException("Vectors have different lengths.\n", lengthList);
            }
        }
        return sum;
    }
}
