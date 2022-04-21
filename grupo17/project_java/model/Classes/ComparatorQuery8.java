import java.util.Comparator;


public class ComparatorQuery8  implements Comparator <Query8> {

    /**
     *  Compara o numero de negocios que 2 user avaliaram (instancias de Query8)
     *
     * @param o1 1º instancia de Query8
     * @param o2 2º instancia de Query8
     * @return 1 se a primeira instancia de Query8 tiver maior numero de negocios avaliados
     */

    public int compare(Query8 o1, Query8 o2) {
        if (o1.getNrBusiness() > o2.getNrBusiness()) return 1;
        return -1;
    }
}
