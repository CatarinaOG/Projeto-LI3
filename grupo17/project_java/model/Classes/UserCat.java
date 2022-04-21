import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class UserCat implements IUserCat , Serializable {

    private Map<String, User> cat_user;

    //------------------------------------------------ Construtores ------------------------------------------------
    public UserCat(){
        this.cat_user = new HashMap<>();
    }

    //------------------------------------------------ Metodos ------------------------------------------------
    // Adiciona utilizador ao catalogo de user
    public void addUserToCat (User u){
        cat_user.put(u.getUser_id(),u);
    }

    public void print(){
        cat_user.values().forEach(this::printUserId);
    }

    public void printUserId(User u){
        System.out.println((u.getUser_id()));
    }

    //------------------------------------------------ Metodos Base ----------------------------------------------
    public Map<String,User> getCat(){
        return this.cat_user.values().stream().collect(Collectors.toMap(User :: getUser_id, User :: clone));
    }

    public Integer catSize(){
        return cat_user.size();
    }

}