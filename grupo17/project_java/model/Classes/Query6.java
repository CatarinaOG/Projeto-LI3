import java.util.HashSet;
import java.util.Set;

public class Query6 {

    private String id_negocio;
    private int nr_reviews;
    private Set<String> users;

    public Query6(String id_negocio) {
        this.id_negocio = id_negocio;
        this.nr_reviews = 0;
        this.users = new HashSet<>();
    }

    public String getId_negocio() {
        return id_negocio;
    }

    public void setId_negocio(String id_negocio) {
        this.id_negocio = id_negocio;
    }

    public int getNr_reviews() {
        return nr_reviews;
    }

    public void setNr_reviews(int nr_reviews) {
        this.nr_reviews = nr_reviews;
    }

    public Set<String> getUsers() {
        return users;
    }

    public void setUsers(Set<String> users) {
        this.users = users;
    }

    public int getUsersSize() {
        return this.users.size();
    }

    public String toString() {
        return "Query6{" +
                "id_negocio='" + id_negocio + '\'' +
                ", nr_reviews=" + nr_reviews +
                ", users=" + users.size() +
                '}';
    }
}
