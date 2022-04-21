import java.util.HashMap;
import java.util.Map;
import java.util.List;

public interface IStats {


    //--------------------------------InfoInicial-----------------------------------
    public long nrNegociosAvaliados();
    public long nrDeNegociosNaoAvaliados();
    public long nrUsersComReviews();
    public long nrUsersSemReviews();
    public int nrDeReviewsSemImpacto();

    //-------------------------------TabelaInicial----------------------------------
    public List<Integer> reviewsPorMes();
    public List<Double> mediaClassMes();
    public List<Integer> diferentesUsersPorMes();

    //---------------------------------Queries--------------------------------------
    public Table query1();
    public void query2(int month, int year) throws DataErradaException;
    public Table query3(String user_id_fornecido);
    public Table query4(String bus);
    public Table query6(int x);
    public Table query7();
    public Table query8(int x);
    public Table query10();

    //----------------------------------GetQueries--------------------------------
    public String getQuery1();
    public String getQuery2();
    public String getQuery4();
    public double getTime();


}
