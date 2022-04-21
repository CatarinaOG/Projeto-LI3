import java.util.Map;

public interface IReviewCat {
    public void addReviewToCat (Review r);
    public void printSize();
    public void print();
    public int getNrReviewsErradas();
    public Map<String,Review> getCat();
    public int catSize();
    public void addReviewErrada();

}

