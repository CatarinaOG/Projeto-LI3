import java.util.Comparator;

public class ComparatorQuery6 implements Comparator<Query6> {

    /**
     *  Compara o número de reviews entre 2 instancia de Query6
     *
     * @param o1 1º instancia de Query6
     * @param o2 2º instancia de Query6
     * @return 1 se a primeira instancia de Query6 tiver maior numero de Reviews realizadas
     */
    public int compare(Query6 o1, Query6 o2) {
        if (o1.getNr_reviews() > o2.getNr_reviews()) return -1;
        return 1;
    }
}
