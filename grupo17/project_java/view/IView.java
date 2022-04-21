import java.util.ArrayList;
import java.util.List;

public interface IView {

    public void printMenu(String[] menus);
    public String[] getInput(String[] inputs);
    public void printString(String s);
    public void printDadosIniciais(Double time,
                                   String fBuz,
                                   String fUsers,
                                   String fReviews,
                                   Integer revErradas,
                                   Integer busz,
                                   long buszAvaliados,
                                   long busNaoAvaliados,
                                   Integer users,
                                   long usersComReviews,
                                   long usersSemReviews,
                                   int nrReviews,
                                   int reviewsSemImpacto);

    public void printTabelaMeses(List<Integer> reviewsPorMes, List<Double> mediaClassMes, List<Integer> difUsersPorMes, double mediaGlobal);

    public void printTable(Table table);

    public void printMissingStructure();

    public void printTime(double d);
}

