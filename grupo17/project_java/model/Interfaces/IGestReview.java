import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public interface IGestReview {

    public void readFicheiros(String business,String reviews,String users);

    public void readBCat(String file);
    public void readRCat(String file);
    public void readUCat(String file);

    //----------------------------Info Inicial-----------------------------
    public Integer reviewsErradas();
    public Integer nrDeNegocios();
    public long nrDeNegociosAvaliados();
    public long nrDeNegociosNaoAvaliados();
    public Integer nrDeUsers();
    public long nrUsersComReviews();
    public long nrUsersSemReviews();
    public int nrDeReviews();
    public int nrDeReviewsSemImpacto();

    //-------------------------------Tabela Inicial-------------------------
    public List<Integer> reviewsPorMes();
    public List<Double> mediaClassMes();
    public List<Integer> diferentesUsersPorMes();
    public double mediaGlobal();

    //-------------------------------Queries---------------------------------
    public Table query1();
    public void query2(int month, int year) throws DataErradaException;
    public Table query3(String user_id);
    public Table query4(String bus);
    public Table query5(String id);
    public Table query6(int x);
    public Table query7();
    public Table query8(int x);
    public Table query9(String business_id, int x);
    public Table query10();


    //----------------------------GetQueries-----------------------------
    public String getQuery1();
    public String getQuery2();
    public String getQuery4();

    //----------------------------OutrosMetodos-----------------------------
    public void save (String path) throws IOException;
    public double getTime();
    public double getStatsTime();
}
