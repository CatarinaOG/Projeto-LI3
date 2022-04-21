import java.util.Comparator;

public class BusinessIdComparator implements Comparator<String> {
    /**
     *  Compara 2 Business identificadores
     *
     * @param s1 identificador
     * @param s2 identificador
     * @return 1 se o primeiro identificador for maior alfabeticamente que o segundo
     */
    public int compare(String s1, String s2) {
        return s1.compareToIgnoreCase(s2);
    }

}
