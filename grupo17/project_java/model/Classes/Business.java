import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Business implements Serializable {

    private String id;
    private String name;
    private String city;
    private String state;
    private List<String> categories;

    //----------------------------------------------------Construtores--------------------------------------------------------------
    public Business() {
        this.id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<>();
    }

    public Business(String id, String name, String city, String state, List<String> categories) {
        this.id = id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories;
    }

    //----------------------------------------------------Metodos--------------------------------------------------------------

    /**
     *  Realiza o parse de um negocio
     *
     * @param  s String completa com a informação do negocio agregada
     * @return Intancia de Business com as informacoes providenciadas pela String
     */

    public static Business readB(String s){
        String[] campos = s.split(";");
        List<String> categorias;

        if (campos.length == 5) categorias = Arrays.asList(campos[4].split(","));
        else categorias = new ArrayList<>();

        if( campos.length > 3 && campos[0]!=null && campos[1]!=null && campos[2]!=null && campos[3]!=null)
            return new Business(campos[0],campos[1],campos[2],campos[3],categorias);

        else return null;
    }



    //---------------------------------------------------Sets e Gets---------------------------------------------------------------
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public List<String> getCategories() {
        return new ArrayList<>(categories);
    }

    public void setCategories(List<String> categories) {
        this.categories = categories;
    }

    //------------------------------------------------Metodos Base------------------------------------------------------------------
    public String toString() {
        return "Business[" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", city='" + city + '\'' +
                ", state='" + state + '\'' +
                ", categories=" + categories +
                ']';
    }

    public Business clone(){
        return new Business(this.id,this.name,this.city,this.state,this.categories);
    }
}
