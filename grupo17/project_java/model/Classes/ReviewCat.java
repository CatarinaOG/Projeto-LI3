import java.io.Serializable;
import java.util.ArrayList;
import java.time.Month;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ReviewCat implements IReviewCat, Serializable {

    private Map<String,Review> cat;
    private int nrReviewsErradas;

    //----------------------------------------Construtores------------------------------------------
    public ReviewCat(){
        this.cat = new HashMap<>();
        this.nrReviewsErradas = 0;
    }


    //------------------------------------------Metodos---------------------------------------------

    public void addReviewToCat (Review r){
        cat.put(r.getReview_id(),r);
    }

    public void print(){
        cat.values().forEach(this::printReviewId);
    }

    public void printReviewId(Review r){
        System.out.println((r.getReview_id()));
    }

    public void printSize(){
        System.out.println("Nr of Reviews: "+cat.size());
    }

    public int getNrReviewsErradas() {
        return nrReviewsErradas;
    }

    public void setNrReviewsErradas(int nrReviewsErradas) {
        this.nrReviewsErradas = nrReviewsErradas;
    }


    //------------------------------------------Metodos base---------------------------------------------

    public Map<String,Review> getCat(){
        return this.cat.values().stream().collect(Collectors.toMap( Review::getReview_id, Review::clone ));
    }

    public int catSize(){
        return this.cat.size();
    }

    public void addReviewErrada(){
        setNrReviewsErradas(getNrReviewsErradas()+1);
    }























}

