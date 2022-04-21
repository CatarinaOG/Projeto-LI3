import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class BizInfo implements Serializable {

    private String id;
    private String nome;
    private String estado;
    private String cidade;
    private int nrReviews;
    private double notaMedia;
    private List<Double> notas;

    public BizInfo(Business b){
        this.id = b.getId();
        this.nome = b.getName();
        this.estado = b.getState();
        this.cidade = b.getCity();
        this.nrReviews = 0;
        this.notaMedia = 0;
        notas = new ArrayList<>();
    }

    public String getId() {
        return id;
    }
    public void setId(String id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEstado() {
        return estado;
    }
    public void setEstado(String estado) {
        this.estado = estado;
    }

    public String getCidade() {
        return cidade;
    }
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public int getNrReviews() {
        return nrReviews;
    }
    public void setNrReviews(int nrReviews) {
        this.nrReviews = nrReviews;
    }

    public double getNotaMedia() {
        return notaMedia;
    }
    public void setNotaMedia(double notaMedia) {
        this.notaMedia = notaMedia;
    }


    /**
     *  Adiciona a informacao de um negocio as caracteristicas da review providenciada.
     *
     * @param  r Review que queremos adicionar a informacao do negocio
     */
    public void addReview(Review r){
        nrReviews += 1;
        notas.add( r.getStars() );
        notaMedia = notas.stream().mapToDouble(t->t).average().getAsDouble();
    }



}
