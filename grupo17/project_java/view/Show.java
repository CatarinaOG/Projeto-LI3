import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Show {

    /**
     * Cálculo do número de páginas
     * @param l tabela
     * @return int
     */
    public static int getPaginas(ArrayList<List<String>> l) {
        double lin = l.size();
        int z = 0;;
        double x = (lin / 13);
        if (lin % 13 == 0) {
            return (int) lin / 13;
        } else z = (int) Math.round(x);
        return z;
    }

    /**
     * Divide a tabela incial em páginas
     * @param l tabela
     * @param nr número da página
     * @return pagina especificada
     */
    public static ArrayList<List<String>> getShowN(ArrayList<List<String>> l, int nr) {
        int i;
        nr--;

        if (l.size() < 13) {
            return l;
        }

        ArrayList<List<String>> part = new ArrayList<>();
        int tam = nr * 13;
        if(tam + 13 > l.size()) {
            for (i = tam ; i < l.size(); i++)
                part.add(l.get(i));
        }
        else
            for( i = tam ; i < tam+13 ; i++)
                part.add(l.get(i));

        return part;
    }

    /**
     * Apresentação da página especifica
     * @param l tabela
     * @param k identificada se é ou não a primeira página
     */
    public static  void show(ArrayList<List<String>> l, int k){
        int nrColunas = l.get(0).size();

        for( int i=0 ; i< l.size() ; i++){
            for( int j = 0 ; j< l.get(i).size() ; j++ ){

                if(k==0 && i==1 && j==0){
                    for(int p=0 ; p<nrColunas ; p++)
                        System.out.print("---------------------------------------------|");
                    System.out.print("\n");
                }
                System.out.printf("%-45s",l.get(i).get(j));
                System.out.print("|");
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }

    /**
     *  Limpa a consola
     */
    public static void clear() {
        for (int i = 0; i < 2; i++){
            System.out.println();
        }
    }

    /**
     * Mini interpretador que mostra a tabela paginada
     * @param l tabela
     * @return int
     */
    public static int showController(ArrayList<List<String>> l){
        int exit = 0;
        int i = 1;
        ArrayList<List<String>> temp = new ArrayList<>();
        System.out.println("Imprimindo primeira página da tabela: ");
        temp = getShowN(l,1);
        show(temp,0);
        System.out.println("Insira \"quit\" se quiser parar de ver a página e voltar ao interpretador.");
        System.out.println("Insira \"next\" se quiser ver a página seguinte.");
        System.out.println("Insira \"back\" se quiser ver a página anterior.");
        System.out.println("Insira um número se quiser ir para uma página específica.");
        System.out.println("Insira \"fim\" se quiser ir até ao fim da tabela.");
        System.out.println("Insira \"inicio\" se quiser ir até ao início da tabela.");
        System.out.println("Insira \"num\" se quiser saber o número de páginas.");
        System.out.println("Insira \"ajuda\" se quiser ver os comandos possíveis");
        int paginas = getPaginas(l);
        System.out.printf("Número de páginas total: %d.\n",paginas);
        Scanner scan = new Scanner(System.in);
        while(scan.hasNext() && exit ==0){
            String op = scan.nextLine();
            switch(op){
                case "quit":
                    clear();
                    System.out.println("Saíndo do programa\n");
                    exit =1;
                    break;
                case "next":
                    clear();
                    if(i!=paginas) i++;
                    temp = getShowN(l,i);
                    show(temp,1);
                    System.out.printf("Página %d\n",(i));
                    break;
                case "back":
                    clear();
                    if(i!=1) i--;
                    temp = getShowN(l,i);
                    show(temp,1);
                    System.out.printf("Página %d\n",(i));
                    break;
                case "fim":
                    clear();
                    i=paginas;
                    temp = getShowN(l,i);
                    show(temp,1);
                    System.out.printf("Página %d\n",(i));
                    break;
                case "inicio":
                    clear();
                    i=0;
                    temp = getShowN(l,i);
                    show(temp,0);
                    System.out.printf("Página %d\n",(i));
                    break;
                case"num":
                    clear();
                    System.out.printf("Número de páginas total: %d.\n",paginas);
                    break;
                case "ajuda":
                    clear();
                    System.out.println("Insira \"quit\" se quiser parar de ver a página e voltar ao interpretador.");
                    System.out.println("Insira \"next\" se quiser ver a página seguinte.");
                    System.out.println("Insira \"back\" se quiser ver a página anterior.");
                    System.out.println("Insira um número se quiser ir para uma página específica.");
                    System.out.println("Insira \"fim\" se quiser ir até ao fim da tabela.");
                    System.out.println("Insira \"inicio\" se quiser ir até ao início da tabela.");
                    System.out.println("Insira \"num\" se quiser saber o número de páginas.");
                    System.out.println("Insira \"ajuda\" se quiser ver os comandos possíveis");
                    break;
                default:
                    clear();
                    i = Integer.parseInt(op)-1;
                    temp = getShowN(l,i);
                    show(temp,1);
                    System.out.printf("Página %d\n",(i));
                    break;
            }
        }
        return 0;
    }
}