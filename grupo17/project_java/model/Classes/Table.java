import java.util.ArrayList;
import java.util.List;

public class Table {

    ArrayList<List<String>> table;

    public Table(){
        this.table = new ArrayList<>();
    }

    public Table(ArrayList<List<String>> table){
        this.table = table;
    }

    public ArrayList<List<String>> getTable() {
        return table;
    }
}
