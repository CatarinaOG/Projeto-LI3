import java.util.Map;

public interface IBusinessCat {

    public void addBusinessToCat (Business b);
    public Integer catSize();
    public Map<String,Business> getCat();

}
