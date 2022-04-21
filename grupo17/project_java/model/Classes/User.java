import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class User implements Serializable {

    private String user_id;
    private String name;
    private List<String> friends; 

    //------------------------------------------------ Construtores ------------------------------------------------
    public User(){
        this.user_id = " ";
        this.name = " ";
        this.friends = new ArrayList<>();
    }

    public User(String user_id, String name, List<String> friends) {
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    //-------------------------------------------------- Metodos --------------------------------------------------
    public static User readU(String s){
        String[] campos = s.split(";");
        //List<String> amigos;

        //if (campos.length == 3) amigos = Arrays.asList(campos[2].split(","));
        //else amigos = new ArrayList<>();

        if(campos.length > 2 && campos[0] != null && campos[1] != null && campos[2] != null)
            return new User(campos[0],campos[1],null);

        else return null;
    }

    //------------------------------------------------ Gets e Sets ------------------------------------------------
    public String getUser_id() {
        return user_id;
    }

    public String getName() {
        return name;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public void setName(String name) {
        this.name = name;
    }

    // ------------------------------------------------ Metodos Base ----------------------------------------------
    public String toString() {
        return "User{" +
                "user_id='" + user_id + '\'' +
                ", name='" + name + '\'' +
                ", friends=" + friends +
                '}';
    }

    public User clone(){
        return new User(this.user_id,this.name,this.friends);
    }
}

