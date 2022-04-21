import java.util.Map;

public interface IUserCat {

    public void addUserToCat (User u);
    public void print();
    public Map<String,User> getCat();
    public Integer catSize();

}

