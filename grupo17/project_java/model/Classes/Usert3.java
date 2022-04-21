import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Usert3 implements Serializable {

    private String userId;
    private int nrReviews;
    private int nrNegocios;
    private Double notaMedia;
    private List<String> negocios;
    private List<Double> notas;

    public Usert3(){
        this.userId = "";
        this.nrReviews = 0;
        this.nrNegocios = 0;
        this.notaMedia = 0.0;
        this.negocios = new ArrayList<>();
        this.notas = new ArrayList<>();
    }


    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public int getNrReviews() {
        return nrReviews;
    }

    public void setNrReviews(int nrReviews) {
        this.nrReviews = nrReviews;
    }

    public int getNrNegocios() {
        return nrNegocios;
    }

    public void setNrNegocios(int nrNegocios) {
        this.nrNegocios = nrNegocios;
    }

    public Double getNotaMedia() {
        return notaMedia;
    }

    public void setNotaMedia(Double notaMedia) {
        this.notaMedia = notaMedia;
    }

    public List<String> getNegocios() {
        return negocios;
    }

    public void setNegocios(List<String> negocios) {
        this.negocios = negocios;
    }

    public List<Double> getNotas() {
        return notas;
    }

    public void setNotas(List<Double> notas) {
        this.notas = notas;
    }

    public void addNota(Double nota){
        this.notas.add(nota);
        this.notaMedia = notas.stream().mapToDouble(t -> t).average().getAsDouble();
    }

    public void addNegocio(String id){

        if( !this.negocios.contains(id) ){
            this.negocios.add(id);
            this.nrNegocios++;
        }

    }



}
