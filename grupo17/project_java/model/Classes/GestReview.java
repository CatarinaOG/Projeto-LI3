import java.io.*;
import java.lang.reflect.Array;
import java.time.Month;
import java.time.format.TextStyle;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.util.stream.Collectors.toMap;

public class GestReview implements IGestReview , Serializable{

    private IBusinessCat bCat;
    private IReviewCat rCat;
    private IUserCat uCat;
    private IStats stats;

    private double time;

    public GestReview(){
        this.bCat = new BusinessCat();
        this.rCat = new ReviewCat();
        this.uCat = new UserCat();
    }

    /**
     *  Faz a leitura dos 3 ficheiros fornecidos, e ainda cria a instancia de stats caracteristica destes
     *
     * @param business path para o ficheiro de businesses
     * @param users path para o ficheiro de users
     * @param reviews path para o ficheiro de reviews
     */
    public void readFicheiros(String business , String users , String reviews){
        Crono.start();

        readBCat(business);
        readUCat(users);
        readRCat(reviews);
        stats = new Stats(bCat,rCat,uCat);

        time = Crono.getTime();
    }

    /**
     *  Faz a leitura do ficheiro de businesses especificamente
     *
     * @param file path para o ficheiro de businesses
     */
    public void readBCat(String file){
        this.bCat = new BusinessCat();

        try{
            InputStream inputStream = new FileInputStream(file);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            Stream<String> linesStream = bufferedReader.lines();
            linesStream.forEach(this::readB);
        }
        catch( IOException e ){ System.out.println("erro a ler ficheiro business");}
    }
    /**
     *  Faz a leitura do ficheiro de users especificamente
     *
     * @param file path para o ficheiro de users
     */
    public void readUCat(String file){
        this.uCat = new UserCat();

        try{
            InputStream inputStream = new FileInputStream(file);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            Stream<String> linesStream = bufferedReader.lines();
            linesStream.forEach(this::readU);
        }
        catch(IOException e){ System.out.println("erro a ler ficheiro users");}
    }
    /**
     *  Faz a leitura do ficheiro de reviews especificamente
     *
     * @param file path para o ficheiro de reviews
     */
    public void readRCat(String file){
        this.rCat = new ReviewCat();
        Set<String> key = this.bCat.getCat().keySet();
        Set<String> keyu = this.uCat.getCat().keySet();
        try{
            InputStream inputStream = new FileInputStream(file);
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            Stream<String> linesStream = bufferedReader.lines();
            linesStream.forEach(this::readR);
            for(Map.Entry f :rCat.getCat().entrySet()){
                Review r = (Review) f.getValue();
                String s = (String) f.getKey();
                if(!key.contains(r.getBusiness_id())||!keyu.contains(r.getUser_id())) rCat.getCat().remove(s);
            }
        }
        catch( IOException e ){ System.out.println("erro a ler ficheiro reviews");}
    }

    /**
     *  Cria a instancia Business de acordo com a informacao de uma String e adiciona-a ao catalogo de businesses
     *
     * @param s String recolhida do ficheiro de businesses
     */
    public void readB( String s ){
        Business biz = Business.readB(s);
        if(biz!=null) bCat.addBusinessToCat(biz);
    }
    /**
     *  Cria a instancia User de acordo com a informacao de uma String e adiciona-a ao catalogo de users
     *
     * @param s String recolhida do ficheiro de users
     */
    public void readU(String s){
        User user = User.readU(s);
        if(user != null) uCat.addUserToCat(user);
    }
    /**
     *  Cria a instancia Review de acordo com a informacao de uma String e adiciona-a ao catalogo de reviews
     *
     * @param s String recolhida do ficheiro de reviews
     */
    public void readR( String s ){
        Review rev = Review.readR(s);
        if(rev!=null) rCat.addReviewToCat(rev);
    }

    //--------------------------------InfoInicial--------------------------------------

    /**
     *  Chama o metodo getNrReviewsErradas do stats
     *
     * @return número de reviews Erradas
     */
    public Integer reviewsErradas(){
        return rCat.getNrReviewsErradas();
    }
    /**
     *  Descobre o numero de negocios corretos existentes
     *
     * @return numero de negocios lidos corretamente
     */
    public Integer nrDeNegocios(){return bCat.catSize();}
    /**
     *  Chama o metodo nrNegociosAvaliados do stats
     *
     * @return numero de negocios avaliados
     */
    public long nrDeNegociosAvaliados(){
        return stats.nrNegociosAvaliados();
    }
    /**
     *  Chama o metodo nrNaoNegociosAvaliados do stats
     *
     * @return numero de negocios nao avaliados
     */
    public long nrDeNegociosNaoAvaliados(){return stats.nrDeNegociosNaoAvaliados(); }
    /**
     *  Descobre o numero de users corretos existentes
     *
     * @return numero de users lidos corretamente
     */
    public Integer nrDeUsers(){return uCat.catSize();}
    /**
     *  Chama o metodo nrUsersComReviews do stats
     *
     * @return numero de users que realizaram reviews
     */
    public long nrUsersComReviews(){return stats.nrUsersComReviews(); }
    /**
     *  Chama o metodo nrUsersSemReviews do stats
     *
     * @return numero de users que nao realizaram reviews
     */
    public long nrUsersSemReviews(){return stats.nrUsersSemReviews(); }
    /**
     *  Descobre o numero de reviews corretas existentes
     *
     * @return numero de reviews lidos corretamente
     */
    public int nrDeReviews(){return rCat.catSize();}
    /**
     *  Chama o metodo nrDeReviewsSemImpacto do stats
     *
     * @return numero de reviews sem impacto
     */
    public int nrDeReviewsSemImpacto(){return stats.nrDeReviewsSemImpacto();}

    //--------------------------------Tabela dos meses--------------------------------------

    /**
     *  Chama o metodo reviewsPorMes do stats
     *
     * @return uma lista ordenada pelos meses do ano com o numero de reviews por mes
     */
    public List<Integer> reviewsPorMes(){return stats.reviewsPorMes();}
    /**
     *  Chama o metodo mediaClassMes do stats
     *
     * @return uma lista ordenada pelos meses do ano com a média de estrelas por mes
     */
    public List<Double> mediaClassMes(){return stats.mediaClassMes();}
    /**
     *  Chama o metodo diferentesUsersPorMes do stats
     *
     * @return uma lista ordenada pelos meses do ano com o numero de diferentes users que avaliaram
     */
    public List<Integer> diferentesUsersPorMes(){return stats.diferentesUsersPorMes();}
    /**
     *  Calcula a media global das classificacoes atribuidas aos negocios
     *
     * @return um double com a media global
     */
    public double mediaGlobal(){
        return rCat.getCat().values().stream().mapToDouble(Review-> Review.getStars()).sum()/(rCat.getCat().size());
    }

    //-------------------------------------Queries--------------------------------------

    /**
     *  Chama o metodo query1 do stats
     *
     * @return uma Table ordenada alfabeticamente com os identificadores dos negócios nunca
     * avaliados;
     */
    public Table query1(){ return stats.query1();}
    /**
     *  Chama o metodo query2 do stats
     *
     * @param month mes escolhido
     * @param year ano escolhido
     * @throws DataErradaException caso a data inserida nao seja valida
     *
     */
    public void query2(int month, int year) throws DataErradaException { stats.query2(month,year); }
    /**
     *  Chama o metodo query3 do stats
     *
     * @param user_id user de que queremos saber a informacao
     * @return uma Table em que para cada mês, descreve quantas reviews fez, quantos negócios distintos avaliou e que nota média atribuiu;
     */
    public Table query3(String user_id){return stats.query3(user_id);}
    /**
     * Chama o metodo query4 do stats
     *
     * @param bus business de qual queremos a informacao
     * @return uma Table em que para cada mês informa quantas vezes o negocios foi avaliado, por quantos users diferentes e a média de classificação
     */
    public Table query4(String bus){return stats.query4(bus);}
    /**
     * A estratégia adotada foi a de criar um ArrayList com todos os negócios que o utilizador passado como parâmetro
     * da função avaliou. De seguida, é feita a construção de um HashMap com id de cada negócio e a frequência de vezes
     * que este aparece na lista do utilizador e por fim, é feita a conceção do HashMap com o nome do respetivo negócio
     * e a frequência de vezes que este foi avaliado, visto ser o pedido no enunciado. Faltando ainda a ordenação por
     * ordem decrescente de quantidade e, para quantidades iguais, por ordem alfabética dos negócios, sendo isso feito
     * à custa do ComparatorQuery9 já mencionado à priori.
     *
     * @param id identificador do user
     * @return uma Table com todos os negocios que avaliou ordenadamente
     */
    public Table query5(String id){

        Crono.start();
        ComparatorQuery9 comp = new ComparatorQuery9();

        ArrayList<String> bus_user = rCat.getCat().values().stream().filter(x -> x.getUser_id().equals(id)).map(Review::getBusiness_id).collect(Collectors.toCollection(ArrayList::new)); // negócios do user dado

        HashMap<String, Integer> freq = new HashMap<>(); // id_negocio, frequencia
        for (String b : bus_user){
            if(freq.containsKey(b)){
                freq.put(b,freq.get(b)+1);
            }
            else{
                freq.put(b,1);
            }
        }

        HashMap<String, Integer> info_bus = new HashMap<>(); // Id_negocio, Nome_Negocio
        for (String ids : freq.keySet()) {
            String nomes = bCat.getCat().get(ids).getName();
            info_bus.put(nomes, freq.get(ids));
        }

        List<Map.Entry<String,Integer>> list = new ArrayList<>(info_bus.entrySet());
        list.sort(comp);

        ArrayList<List<String>> table = new ArrayList<>();

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Negocios");
        titulos.add("Nr de Reviews");

        table.add(titulos);

        for( Map.Entry<String,Integer> m : list){
            ArrayList<String> linha = new ArrayList<>();
            linha.add(m.getKey());
            linha.add(String.valueOf(m.getValue()));

            table.add(linha);
        }

        time = Crono.getTime();
        return new Table(table);
    }
    /**
     * Chama o metodo query6 do stats
     * @param x top
     * @return uma Table com os negocios mais avaliados e o respetivo total de users que os avaliaram
     */
    public Table query6(int x){
        return stats.query6(x);
    }
    /**
     * Chama o metodo query7 do stats
     * @return uma Table com cada cidade em conjunto com os top 3 negocios mais avalaidos nela
     */
    public Table query7(){return stats.query7();}
    /**
     * Chama a query8 do stats
     *
     * @param x número de utilizadores desejado
     * @return uma Table com o conjunto dos top x utilizadores que mais avaliaram negocios
     */
    public Table query8(int x){ return stats.query8(x);}
    /**
     * Utilizados dois HashMaps, no Map freq foi colocado como key o id de user e como value o número de
     * vezes que este user avaliou um negocio, no Map stat foi colocado o id de user como key e valor o
     * número de estrelas total que este deu a um negócio. O Map stat é de seguida atualizado com a média
     * das avaliações feitas por cada user. O Map freq é depois colocado numa List para posteriormente ser
     * ordenada com o comparador ComparatorQuery9 que ordena de acordo com o critério da query 5. Finalmente
     * são colocados numa LinkedHashMap os X users e as suas médias de avaliações.
     *
     * @param business_id identificador do negocio
     * @param x top
     * @return uma Table com o top x users que avaliaram o negocio fornecido e a respetiva media de classificacao
     */
    public Table query9(String business_id, int x){
        Crono.start();

        ArrayList<List<String>> f = new ArrayList<>();
        ComparatorQuery9 com = new ComparatorQuery9();
        HashMap<String,Integer> freq = new HashMap<>();
        HashMap <String,Double> stat = new HashMap<>();
        LinkedHashMap<String,Double> ordf = new LinkedHashMap<>();
        int n = 0;
        ArrayList <Review> revs = rCat.getCat().values().stream().filter(Rev->Rev.getBusiness_id().equals(business_id)).collect(Collectors.toCollection(ArrayList::new));
        ArrayList<String> bus = rCat.getCat().values().stream().filter(Rev->Rev.getBusiness_id().equals(business_id)).map(Review::getUser_id).collect(Collectors.toCollection(ArrayList::new));

        for (String b:bus){
            if(freq.containsKey(b)) freq.put(b,freq.get(b)+1);
            else freq.put(b,1);
        }
        for(Review r:revs){
            if(stat.containsKey(r.getUser_id())) stat.put(r.getUser_id(),(stat.get(r.getUser_id())+r.getStars()));
            else stat.put(r.getUser_id(),r.getStars());
        }

        for (Map.Entry m :  stat.entrySet()){
            Double k = (Double) m.getValue();
            String id = (String) m.getKey();
            int s = freq.get(id);
            stat.put(id,k/s);
        }

        List<Map.Entry<String,Integer>> list = new ArrayList<>(freq.entrySet());
        list.sort(com);
        for (Map.Entry m: list){
            String id = (String) m.getKey();
            Double k = stat.get(id);
            ordf.put(id,k);
            n++;
            if(n==x) break;
        }

        ArrayList<List<String>> table = new ArrayList<>();

        List<String> titulos = new ArrayList<>();
        titulos.add("User id");
        titulos.add("Média");

        table.add(titulos);

        for(Map.Entry<String,Double> m : ordf.entrySet() ){
            List<String> linha = new ArrayList<>();
            linha.add(m.getKey());
            linha.add(String.format("%.2f",m.getValue()));

            table.add(linha);
        }

        time = Crono.getTime();
        return new Table(table);
    }
    /**
     * Chama a query10 do stats
     * @return uma Table com o conjunto de todos os estados, todas as cidades associadas a ele, e para estas, todos os negocios associados em conjunto com a sua media de classificacao
     */
    public Table query10(){return stats.query10();}

    //-------------------------------------GetQueries------------------------------------

    public String getQuery1(){return stats.getQuery1();}
    public String getQuery2(){return stats.getQuery2();}
    public String getQuery4(){return stats.getQuery4();}

    //-------------------------------------OutrosMetodos------------------------------------

    public void save (String objectPath) throws IOException{
        FileOutputStream fos = new FileOutputStream(objectPath);
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    public double getTime(){
        return this.time;
    }

    public double getStatsTime(){
        return stats.getTime();
    }






















}
