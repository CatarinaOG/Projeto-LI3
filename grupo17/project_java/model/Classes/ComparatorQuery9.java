import java.util.Comparator;
import java.util.Map;

public class ComparatorQuery9 implements Comparator<Map.Entry<String, Integer>>  {

    /**
     *  Compara dois pares, cada um com o seu id e o numero de reviews feitas )
     *
     * @param o1 1º par id/nr de reviews
     * @param o2 1º par id/nr de reviews
     * @return um numero negativo se o primeiro valor tiver maior numero de reviews feitas ou se iguais, tiver um id alfabeticamente menor
     */

    public int compare(Map.Entry<String,Integer> o1, Map.Entry<String,Integer> o2) {
        if (o1.getValue().equals(o2.getValue())) return o1.getKey().compareToIgnoreCase(o2.getKey());
        else if (o1.getValue() > o2.getValue()) return -1;
        return 1;
}}
