import java.time.Month;
import java.time.format.TextStyle;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class View implements IView{

    private Scanner scan;

    // Construtor
    public View(){
        this.scan = new Scanner(System.in);
    }

    /**
     * Apresentação do menu especificado
     * @param menus lista de strings que representa o menu
     */
    public void printMenu(String[] menus){

        StringBuffer sb = new StringBuffer();

        sb.append("----------------------Menu------------------------\n");

        for(int i=0 ; i<menus.length ; i++ ){
            sb.append(i+": "+menus[i]+"\n");
        }

        sb.append("--------------------------------------------------\n");

        System.out.print(sb.toString());
    }

    /**
     * Apresenta o formato que o utilizador tem que se seguir e faz a leitura do input do user retornando esse input
     * @param inputs aquilo que o utilziador deve introduzir
     * @return String
     */
    public String[] getInput(String[] inputs){

        StringBuffer sb = new StringBuffer();
        sb.append("Escreva da seguinte forma: ");

        for( int i=0 ; i<inputs.length ; i++){
            sb.append("<").append(inputs[i]).append(">").append(";");
        }

        System.out.println(sb.toString());
        return scan.nextLine().split(";");
    }

    /**
     * iImprimir a string especificada
     * @param s string especificada
     */
    public void printString(String s){
        System.out.println(s);
    }

    /**
     * Imprime a stats
     * @param time tempo
     * @param fBuz ficheiro de negócios
     * @param fUsers ficheiro de users
     * @param fReviews ficheiro de reviews
     * @param revErradas número de reviews erradas
     * @param busz número de negócios
     * @param buszAvaliados número de negócios diferentes avaliados
     * @param busNaoAvaliados número de negócios diferentes não avaliados
     * @param nrUsers número de users
     * @param usersComReviews número de users que fizeram reviews
     * @param usersSemReviews número de users que não fizeram reviews
     * @param nrReviews número de reviews
     * @param reviewsSemImpacto número de reviews sem impacto
     */
    public void printDadosIniciais(Double time,
                                   String fBuz,
                                   String fUsers,
                                   String fReviews,
                                   Integer revErradas,
                                   Integer busz,
                                   long buszAvaliados,
                                   long busNaoAvaliados,
                                   Integer nrUsers,
                                   long usersComReviews,
                                   long usersSemReviews,
                                   int nrReviews,
                                   int reviewsSemImpacto){

        String sb = "Leitura dos ficheiros em " + time + " segundos\n" +
                "Ficheiros lidos: " + fBuz + "," + fReviews + "," + fUsers + "\n" +
                "Nr de Negocios: " + busz + "\n" +
                "Nr de negocios diferentes avaliados: " + buszAvaliados + "\n" +
                "Nr de negocios diferentes nao avaliados: " + busNaoAvaliados + "\n" +
                "Nr de users: " + nrUsers + "\n" +
                "Nr de Users que fizeram reviews: " + usersComReviews + "\n" +
                "Nr de Users que nao fizeram reviews: " + usersSemReviews + "\n" +
                "Nr de Reviews: " + nrReviews + "\n" +
                "Nr de reviews sem impacto: " + reviewsSemImpacto + "\n";
        System.out.println(sb);
    }

    /**
     * Apresenta a informação stats relacionadas com os meses do ano
     * @param reviewsPorMes número de reviews por mês
     * @param mediaClassMes média de classificações por mês
     * @param difUsersPorMes número de distintos users que avaliaram em cada mês
     */
    public void printTabelaMeses(List<Integer> reviewsPorMes, List<Double> mediaClassMes, List<Integer> difUsersPorMes, double mediaGlobal){

        System.out.println("    Mes    |   Nr Reviews   |    Media    |  Nr Users   |");

        for( int i=0 ; i <12 ; i++){
            System.out.printf("%-10s",Month.of(i+1).getDisplayName(TextStyle.FULL , Locale.ENGLISH ));
            System.out.print(" | ");
            System.out.printf("%-14s",reviewsPorMes.get(i));
            System.out.print(" | ");
            System.out.printf("%-11s",String.format("%.2f",mediaClassMes.get(i)));
            System.out.print(" | ");
            System.out.printf("%-11s",difUsersPorMes.get(i));
            System.out.print(" | \n");

        }

        System.out.println("Media global: "+mediaGlobal);
    }

    /**
     * Imprime a tabela
     * @param table tabela
     */
    public void printTable(Table table) {
        if(table!=null)
            Show.showController(table.getTable());
    }

    /**
     * Apresenta mensagem de erro
     */
    public void printMissingStructure(){
        System.out.println("Têm de inicializar o programa com o carregar de ficheiros");
    }

    /**
     * Imprime o tempo
     * @param d tempo
     */
    public void printTime(double d){
        System.out.println("Elapsed time: "+d);
    }


}

