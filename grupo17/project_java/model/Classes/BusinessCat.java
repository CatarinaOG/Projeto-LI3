import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class BusinessCat implements IBusinessCat, Serializable{

    private Map<String,Business> cat;

    //----------------------------------------Construtores------------------------------------------
    public BusinessCat(){
        this.cat = new HashMap<>();
    }

    //------------------------------------------Metodos---------------------------------------------
    public void addBusinessToCat (Business b){
        cat.put(b.getId(),b);
    }

    public Integer catSize(){return cat.size();}

    //------------------------------------------Metodos base---------------------------------------------

    /**
     *  Cria um novo catalogo, mas com as mesmas informacoes
     *
     * @return clone do catalogo original
     */

    public Map<String,Business> getCat(){
        return this.cat.values().stream().collect(Collectors.toMap( Business::getId, Business::clone ));
    }

}
