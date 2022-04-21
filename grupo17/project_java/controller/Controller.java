import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Scanner;

public class Controller implements IController {

    // Variaveis e construtor
    private IGestReview gestReview;
    private IView view;

    public Controller( IGestReview m , IView v ){
        this.gestReview = m;
        this.view = v;
    }

    /**
     *  Método de execução do programa
     */
    public void run(){

        int vazio = 0;
        int opcao;
        Scanner scan = new Scanner(System.in);
        String[] campos;
        String[] porOmissao =  {"business_full.csv","users_full.csv","reviews_1M.csv"};
        long time;
        Table t = null;

        String[] MENU = {"Carregar Ficheiros","Query1","Query2","Query3","Query4","Query5","Query6","Query7","Query8","Query9","Query10","Guardar GestReview","Ler GestReview","Sair"};
        view.printMenu(MENU);

        while( (opcao = scan.nextInt()) != 13 ){

            switch(opcao){
                case 0:
                    campos = view.getInput(new String[] {"Path para os business","Path para os users","Path para as reviews"});

                    if(campos.length < 2) campos = porOmissao;

                    gestReview.readFicheiros("business_full.csv","users_full.csv","reviews_1M.csv");
                    view.printDadosIniciais(gestReview.getTime(),
                                            campos[0],
                                            campos[1],
                                            campos[2],
                                            gestReview.reviewsErradas(),
                                            gestReview.nrDeNegocios(),
                                            gestReview.nrDeNegociosAvaliados(),
                                            gestReview.nrDeNegociosNaoAvaliados(),
                                            gestReview.nrDeUsers(),
                                            gestReview.nrUsersComReviews(),
                                            gestReview.nrUsersSemReviews(),
                                            gestReview.nrDeReviews(),
                                            gestReview.nrDeReviewsSemImpacto());
                    view.printTabelaMeses(gestReview.reviewsPorMes(),gestReview.mediaClassMes(),gestReview.diferentesUsersPorMes(), gestReview.mediaGlobal());
                    vazio = 1;
                    break;

                case 1:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    t = gestReview.query1();
                    view.printTime(gestReview.getStatsTime());
                    view.printString(gestReview.getQuery1());
                    view.printTable(t);

                    break;

                case 2:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"Month","Year"});

                    try {
                        gestReview.query2(Integer.parseInt(campos[0]),Integer.parseInt(campos[1]));
                    }catch (DataErradaException e){
                        view.printString(e.toString());
                    }

                    view.printTime(gestReview.getStatsTime());
                    view.printString(gestReview.getQuery2());
                    break;

                case 3:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"User id"});

                    t = gestReview.query3(campos[0]);
                    view.printTime(gestReview.getStatsTime());
                    view.printTable(t);
                    break;

                case 4:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"Business id"});

                    t = gestReview.query4(campos[0]);
                    view.printTime(gestReview.getStatsTime());
                    view.printString("Média classificação: "+gestReview.mediaGlobal());
                    view.printTable(t);
                    break;

                case 5:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"User id"});

                    t = gestReview.query5(campos[0]);
                    view.printTime(gestReview.getTime());
                    view.printTable(t);
                    break;

                case 6:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"Top x"});

                    t = gestReview.query6(Integer.parseInt(campos[0]));
                    view.printTime(gestReview.getStatsTime());
                    view.printTable(t);
                    break;

                case 7:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    t = gestReview.query7();
                    view.printTime(gestReview.getStatsTime());
                    view.printTable(t);

                    break;

                case 8:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"top x users"});

                    t = gestReview.query8(Integer.parseInt(campos[0]));
                    view.printTime(gestReview.getStatsTime());
                    view.printTable(t);

                    break;

                case 9:

                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"Business id","Top x"});

                    t = gestReview.query9(campos[0],Integer.parseInt(campos[1]));
                    view.printTime(gestReview.getTime());
                    view.printTable(t);
                    break;

                case 10:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    t = gestReview.query10();
                    view.printTime(gestReview.getStatsTime());
                    view.printTable(t);
                    break;

                case 11:
                    if(vazio == 0) {view.printMissingStructure(); break; }

                    campos = view.getInput(new String[] {"Path"});

                    if(campos.length == 0) campos[0] = "gestReviews.dat";

                    Crono.start();
                    try {
                        gestReview.save(campos[0]);
                    } catch (Exception e){
                        view.printString(e.toString());
                    }
                    view.printTime(Crono.getTime());
                    view.printString("All done");
                    break;

                case 12:
                    campos = view.getInput(new String[] {"Path"});
                    if(campos.length == 0) campos[0] = "gestReviews.dat";

                    Crono.start();
                    try {
                        this.read(campos[0]);
                    } catch (Exception e){
                        view.printString(e.toString());
                    }

                    vazio = 1;
                    view.printTime(Crono.getTime());
                    view.printString("All done");
                    break;
            }
            view.printMenu(MENU);
        }
    }

    /**
     * Método de leitura
     */
    public void read(String objectPath) throws IOException,ClassNotFoundException{
        FileInputStream fileIn = new FileInputStream(objectPath);
        ObjectInputStream in = new ObjectInputStream(fileIn);

        this.gestReview = (GestReview) in.readObject();
    }


}
