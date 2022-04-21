import java.io.Serializable;
import java.lang.reflect.Array;
import java.time.Month;
import java.time.format.TextStyle;
import java.util.*;
import java.util.stream.Collectors;

public class Stats implements IStats , Serializable {

    private IBusinessCat bCat;
    private IReviewCat rCat;
    private IUserCat uCat;
    private Map<String,BizInfo> bizsInfo;
    private Map<String,Map<Integer,Usert3>> usersInfoPorMes;

    private long nrNegociosAvaliados;
    private long nrNegociosNaoAvaliados;
    private long nrUsersComReviews;
    private long nrUsersSemReviews;
    private int nrReviesSemImpacto;

    private String query1;
    private String query2;
    private String query4;

    private double time;


    public Stats(IBusinessCat bCat, IReviewCat rCat, IUserCat uCat){
        this.bCat = bCat;
        this.rCat = rCat;
        this.uCat = uCat;
        this.bizsInfo = getBizsInfo();
        this.usersInfoPorMes = getUsersInfoPorMes();
        this.nrNegociosAvaliados = 0;
        this.nrNegociosNaoAvaliados = 0;
        this.nrUsersComReviews = 0;
        this.nrUsersSemReviews = 0;
        this.nrReviesSemImpacto = 0;
    }

    //---------------------------------Info---------------------------------------

    /**
     *  Percorremos todas as reviews, e criar um Map cuja key são business id’s e cujo value são instâncias da
     *  classe BizInfo que contêm a informação pertinente de cada negócio (id, nome, estado, cidade, número de reviews,
     *  número médio de estrelas recebidas e uma lista das suas estrelas).
     *
     * @return um Map cuja key sao os ids dos negocios, e values instancias de BizInfo
     */
     public Map<String,BizInfo> getBizsInfo(){

        Map<String,BizInfo> bizs = new HashMap<>();
        Map<String,Business> bizcat = bCat.getCat();

        for( Review r : rCat.getCat().values() ) {

            Business b = bizcat.get(r.getBusiness_id());

            if(b!=null) { // retirar quando tiver as condicoes
                String bizId = b.getId();
                if (bizs.containsKey(bizId)) bizs.get(bizId).addReview(r);
                else {
                    BizInfo bInfo = new BizInfo(b);
                    bInfo.addReview(r);
                    bizs.put(bizId, bInfo);
                }
            }
        }

        return bizs;
    }

    /**
     *  Percorremos todas as reviews, vai colocar no Map como key cada um dos utilizadores, e ao mesmo tempo colocar no seu value, um outro Map
     *  cujas keys são os meses, e os values Usert3. Este último vai conter todas as informações necessárias em relação a cada mês
     *  (número de reviews, número de negócios avaliados, e o número médio de estrelas atribuído)
     *
     * @return um Map cuja key sao os ids dos users, e values um outro Map cuja key sao os meses, e os values instancias de Usert3
     **/
     public Map<String,Map<Integer,Usert3>> getUsersInfoPorMes(){

        Map<String, Map<Integer,Usert3>> users = new HashMap<>();
        Usert3 user;

        for( Review r : rCat.getCat().values()){

            String user_id = r.getUser_id();
            Integer mes = r.getDate().getMonthValue();

            if( users.containsKey( user_id ) ){
                if( users.get( user_id ).containsKey( mes ) ){

                    user = users.get( user_id ).get( mes );

                    user.setNrReviews( user.getNrReviews()+1 );
                    user.addNota( r.getStars() );
                    user.addNegocio( r.getBusiness_id() );
                }
                else {

                    user = new Usert3();

                    user.setNrReviews( user.getNrReviews()+1 );
                    user.addNota( r.getStars() );
                    user.addNegocio( r.getBusiness_id() );

                    users.get(user_id).put( r.getDate().getMonthValue() , user );
                }
            }
            else{

                Map<Integer,Usert3> userInfo = new HashMap<>();
                user = new Usert3();

                user.setUserId( r.getUser_id() );
                user.setNrReviews( user.getNrReviews()+1 );
                user.addNota( r.getStars() );
                user.addNegocio( r.getBusiness_id() );

                userInfo.put( r.getDate().getMonthValue() , user );
                users.put( r.getUser_id() , userInfo );
            }
        }


        return users;
    }


    //---------------------------------InfoInicial---------------------------------------

    /**
     * @return numero de negocios avaliados
     **/
    public long nrNegociosAvaliados(){
        String x = null;
        List<String> n = rCat.getCat().values().stream().map(Review::getBusiness_id).distinct().collect(Collectors.toList());
        this.nrNegociosAvaliados = n.size();
        return this.nrNegociosAvaliados;
    }
    /**
     * @return numero de negocios nao avaliados
     **/
    public long nrDeNegociosNaoAvaliados(){
        this.nrNegociosNaoAvaliados = bCat.catSize()-nrNegociosAvaliados;
        return nrNegociosNaoAvaliados;
    }
    /**
     * @return numero de users que realizaram reviews
     **/
    public long nrUsersComReviews(){
        this.nrUsersComReviews =  rCat.getCat().values().stream().map(Review::getUser_id).distinct().count();
        return nrUsersComReviews;
    }
    /**
     * @return numero de users que nao realizaram reviews
     **/
    public long nrUsersSemReviews(){
        this.nrUsersSemReviews = uCat.catSize()-nrUsersComReviews;
        return nrUsersSemReviews; }
    /**
     * @return numero de reviews sem impacto
     **/
    public int nrDeReviewsSemImpacto(){
        List<String> rev = new ArrayList<>();

        for (Review r : rCat.getCat().values()) {
            if (r.getCool() == 0 && r.getFunny() == 0 && r.getUseful() == 0) {
                rev.add(r.getReview_id());
            }
        }

        this.nrReviesSemImpacto = rev.size();
        return nrReviesSemImpacto;
    }


    //---------------------------------Tabela Inicial---------------------------------------

    /**
     * @return uma lista ordenada pelos meses do ano com o numero de reviews por mes
     */
    public List<Integer> reviewsPorMes(){

        List<Integer> revsPorMes = new ArrayList<>();

        for(int i=0 ; i<12 ; i++)
            revsPorMes.add(i,0);

        for( Review r : rCat.getCat().values()){
            int mes = r.getDate().getMonthValue();
            revsPorMes.set(mes-1, revsPorMes.get(mes-1)+1);
        }

        return revsPorMes;
    }
    /**
     * @return uma lista ordenada pelos meses do ano com a média de estrelas por mes
     */
    public List<Double> mediaClassMes(){
        List<Double> media = new ArrayList<>();
        double jan, fev, mar,abr, mai,jun, jul, ago, set, out, nov, dez;
        double jstar = 0.0,fstar = 0.0,mstar=0.0,astar=0.0,maystar=0.0,junstar=0.0,julstar=0.0,agstar=0.0,setstar=0.0,octstar=0.0,novstar=0.0,decstar=0.0;
        int ja = 0,fe = 0,ma = 0,ab=0,maio=0,ju=0,julh=0,ag=0,se=0,ou=0,no=0,de=0;
        ArrayList <Review> reviews = new ArrayList<>(this.rCat.getCat().values());
        for(Review r : reviews){
            if(r.getDate().getMonthValue()==1) {ja++; jstar += r.getStars();}
            if(r.getDate().getMonthValue()==2) {fe++; fstar +=r.getStars();}
            if(r.getDate().getMonthValue()==3) {ma++; mstar += r.getStars();}
            if(r.getDate().getMonthValue()==4) {ab++; astar +=r.getStars();}
            if(r.getDate().getMonthValue()==5) {maio++; maystar+=r.getStars();}
            if(r.getDate().getMonthValue()==6) {ju++; junstar+=r.getStars();}
            if(r.getDate().getMonthValue()==7) {julh++; julstar+=r.getStars();}
            if(r.getDate().getMonthValue()==8) {ag++; agstar+=r.getStars();}
            if(r.getDate().getMonthValue()==9) {se++; setstar+=r.getStars();}
            if(r.getDate().getMonthValue()==10) {ou++; octstar+=r.getStars();}
            if(r.getDate().getMonthValue()==11) {no++; novstar+=r.getStars();}
            if(r.getDate().getMonthValue()==12) {de++; decstar+=r.getStars();}
        }
        jan = jstar/ja;
        media.add(jan);
        fev = fstar/fe;
        media.add(fev);
        mar = mstar/ma;
        media.add(mar);
        abr = astar/ab;
        media.add(abr);
        mai = maystar/maio;
        media.add(mai);
        jun = junstar/ju;
        media.add(jun);
        jul = julstar/julh;
        media.add(jul);
        ago = agstar/ag;
        media.add(ago);
        set = setstar/se;
        media.add(set);
        out = octstar/ou;
        media.add(out);
        nov = novstar/no;
        media.add(nov);
        dez = decstar/de;
        media.add(dez);
        double med = (jan+fev+mar+abr+mai+jun+jul+ago+set+out+nov+dez)/12;
        media.add(med);
        return media;
    }
    /**
     * @return uma lista ordenada pelos meses do ano com o numero de diferentes users que avaliaram
     */
    public List<Integer> diferentesUsersPorMes(){
        HashMap[] users = new HashMap[12];

        // Inicializar HashMaps
        for(int i = 0; i < 12; i++){
            users[i] = new HashMap<String, Boolean>();
        }
        for(Review r : rCat.getCat().values()){
            if (!users[r.getDate().getMonthValue()-1].containsKey(r.getUser_id())){
                users[r.getDate().getMonthValue()-1].put(r.getUser_id(), true);
            }
        }

        List<Integer> result = new ArrayList<>();
        for(int i = 0; i < 12; i++){
            result.add(users[i].size());
        }
        return result;
    }

    //--------------------------------------queries--------------------------------------------

    /**
     *  É percorrido o KeySet da HashMap dos negócios para verificar se estes negócios foram avaliados e aparecem na HashMap das Reviews.
     *  Depois de juntar todos os ids dos negócios nunca avaliados numa List é usado o comparador BusinessIdComparator para ordená-los
     *  alfabeticamente
     *
     * @return uma table ordenada alfabeticamente com os identificadores dos negócios nunca
     * avaliados;
     */
    public Table query1(){
    Crono.start();

    HashSet<String> revh = rCat.getCat().values().stream().map(Review::getBusiness_id).collect(Collectors.toCollection(HashSet::new));
    HashSet <String> bus = new HashSet<>(bCat.getCat().keySet());

    List <String> revno = bus.stream().filter(x->!revh.contains(x)).collect(Collectors.toList());
    BusinessIdComparator comp = new BusinessIdComparator();
        revno.sort(comp);

    ArrayList<List <String>>  f = new ArrayList<>();

    ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Negocios");

        f.add(titulos);

        for( String s : revno){
        ArrayList<String>  linha = new ArrayList<>();
        linha.add(s);
        f.add(linha);
    }

        query1 = "Numero de negócios não avaliados: "+revno.size();
        time = Crono.getTime();
        return new Table(f);
    }
    /**
     * Usando iteradores internos foram filtradas as Reviews realizadas no ano e mês fornecidos, sendo estas colocadas numa List.
     * Usando novamente iteradores internos, foram colocados numa List os users distintos da lista de reviews mencionada anteriormente.
     * No final atualiza-se a variável de instância do stats para o fornecer à View
     *
     * @param month mes escolhido
     * @param year ano escolhido
     *
     */
    public void query2(int month, int year) throws DataErradaException {
        Crono.start();
        ArrayList<List <String>>  f = new ArrayList<>();
        if(month <1 || month>12 || year>2021) throw new DataErradaException("Data inserida inexistente");
        List<Review> rev= rCat.getCat().values().stream().filter(x->x.getDate().getMonthValue()==month && (x.getDate().getYear())==year).collect(Collectors.toList());
        if(rev.size()!=0) {
            List<String> user = rev.stream().map(Review::getUser_id).distinct().collect(Collectors.toList());
            this.query2 = "Número de reviews realizadas em " + month + "-" + year + ": " + rev.size()/12 + " reviews.\n" + "Número de users distintos que as realizaram: " + user.size() + "\n";
        }
        time = Crono.getTime();
    }
    /**
     *  Para concretizar o objetivo desta query optou-se por criar primeiro a coleção UserInfoPorMes. Apôs a criação desta coleção,
     *  fazemos um simples get do user desejado.
     *
     * @param user_id_fornecido user de que queremos saber a informacao
     * @return uma Table em que para cada mês, descreve quantas reviews fez, quantos negócios distintos avaliou e que nota média atribuiu;
     */
    public Table query3(String user_id_fornecido){
        Crono.start();

        Map<Integer,Usert3> map = usersInfoPorMes.get(user_id_fornecido);

        ArrayList<List<String>> table = new ArrayList<>();
        ArrayList<String> titulo = new ArrayList<>();
        titulo.add("Mês");
        titulo.add("Nr de Reviews");
        titulo.add("Nr de Negocios");
        titulo.add("Media");

        table.add(titulo);

        for( Map.Entry<Integer,Usert3> m : map.entrySet() ) {

            ArrayList<String> linha = new ArrayList<>();
            Usert3 u = m.getValue();

            linha.add(Month.of(m.getKey()).name());
            linha.add(String.valueOf(u.getNrNegocios()));
            linha.add(String.valueOf(u.getNrReviews()));
            linha.add(String.format("%.2f",u.getNotaMedia()));

            table.add(linha);
        }

        Table t = new Table(table);

        time = Crono.getTime();
        return t;

    }
    /**
     * Foram colocadas em 12 listas as reviews realizadas em cada mês que posteriormente foram adicionadas a uma lista de listas.
     * De seguida, esta lista e percorrida num loop for sendo feito o calculo do número de users diferentes, a media do mes e a media.
     * Estas informações foram depois adicionadas a uma lista que seria posteriormente adicionada à tabela.
     *
     * @param bus business de qual queremos a informacao
     * @return uma Table em que para cada mês informa quantas vezes o negocios foi avaliado, por quantos users diferentes e a média de classificação
     */
    public Table query4(String bus){
        Crono.start();

        ArrayList<List <String>> tabela = new ArrayList<>();
        List<Review> rev= rCat.getCat().values().stream().filter(x-> x.getBusiness_id().equals(bus)).collect(Collectors.toList());

        int nrReviews;
        int nrUsers;
        double mediaMes;
        double mediaGlobal = 0;
        int i=1;

        if(rev.size()==0) return null;

        List <Review> j = rev.stream().filter(x->x.getDate().getMonthValue()==1).collect(Collectors.toList());
        List <Review> feb = rev.stream().filter(x->x.getDate().getMonthValue()==2).collect(Collectors.toList());
        List <Review> marc = rev.stream().filter(x->x.getDate().getMonthValue()==3).collect(Collectors.toList());
        List <Review> april = rev.stream().filter(x->x.getDate().getMonthValue()==4).collect(Collectors.toList());
        List <Review> may = rev.stream().filter(x->x.getDate().getMonthValue()==5).collect(Collectors.toList());
        List <Review> june = rev.stream().filter(x->x.getDate().getMonthValue()==6).collect(Collectors.toList());
        List <Review> july = rev.stream().filter(x->x.getDate().getMonthValue()==7).collect(Collectors.toList());
        List <Review> aug = rev.stream().filter(x->x.getDate().getMonthValue()==8).collect(Collectors.toList());
        List <Review> sep = rev.stream().filter(x->x.getDate().getMonthValue()==9).collect(Collectors.toList());
        List <Review> oct = rev.stream().filter(x->x.getDate().getMonthValue()==10).collect(Collectors.toList());
        List <Review> novem = rev.stream().filter(x->x.getDate().getMonthValue()==11).collect(Collectors.toList());
        List <Review> dec = rev.stream().filter(x->x.getDate().getMonthValue()==12).collect(Collectors.toList());


        List<List<Review>> meses = new ArrayList<>();
        meses.add(j);
        meses.add(feb);
        meses.add(marc);
        meses.add(april);
        meses.add(may);
        meses.add(june);
        meses.add(july);
        meses.add(aug);
        meses.add(sep);
        meses.add(oct);
        meses.add(novem);
        meses.add(dec);

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Mês");
        titulos.add("Nr de Reviews");
        titulos.add("Nr de Users");
        titulos.add("Media");

        tabela.add(titulos);

        for( List<Review> l : meses){
            nrReviews = l.size();
            nrUsers = (int) l.stream().map(Review::getUser_id).distinct().count();
            mediaMes = (l.stream().mapToDouble(Review::getStars).sum())/l.size();
            mediaGlobal = mediaGlobal + mediaMes;

            ArrayList<String> linha = new ArrayList<>();
            linha.add(Month.of(i).getDisplayName(TextStyle.FULL , Locale.ENGLISH ));
            linha.add(String.valueOf(nrReviews));
            linha.add(String.valueOf(nrUsers));
            linha.add(String.format("%.2f",mediaMes));

            tabela.add(linha);
            i++;
        }

        this.query4 = "Média Global: "+ String.format("%.2f",mediaGlobal/12);
        Table t = new Table(tabela);

        time = Crono.getTime();
        return t;
    }
    /**
     * Utilizamos um HashMap que possui o ano, com outro HashMap com o id de negócio e a Query6, tendo esta a informação do id de negócio, o número de reviews do negócio e um conjunto de utilizadores
     * que lhe fizeram a respetiva review. Depois de termos esta informação ordena-se pelos negócios mais avaliados, à custa do ComparatorQuery6 e apresenta-se apenas o conjunto com o X dado pelo utilizador.
     *
     * @param x top
     * @return uma Table com os negocios mais avaliados e o respetivo total de users que os avaliaram
     */
    public Table query6(int x){

        Crono.start();

        HashMap<Integer, HashMap<String,Query6>> ano_negocio= new HashMap<>();

        // meter a info na hash
        for(Review r : rCat.getCat().values()){
            int ano = r.getDate().getYear();
            if(!ano_negocio.containsKey(ano)){
                ano_negocio.put(ano,new HashMap<>());
            }
            String id_negocio = r.getBusiness_id();
            if(!ano_negocio.get(ano).containsKey(id_negocio)){
                ano_negocio.get(ano).put(id_negocio, new Query6(id_negocio));
            }
            String id_user = r.getUser_id();
            ano_negocio.get(ano).get(id_negocio).getUsers().add(id_user);
            int nrRewiews = ano_negocio.get(ano).get(id_negocio).getNr_reviews();
            nrRewiews++;
            ano_negocio.get(ano).get(id_negocio).setNr_reviews(nrRewiews);
        }

        // set ordenado pelos negocios mais avaliados
        HashMap<Integer,TreeSet<Query6>> ord = new HashMap<>();
        for (int ano : ano_negocio.keySet()){
            if (!ord.containsKey(ano)){
                ord.put(ano, new TreeSet<>(new ComparatorQuery6()));
            }
            HashMap<String, Query6> negocios = ano_negocio.get(ano);
            for (Query6 q : negocios.values()){
                ord.get(ano).add(q);
            }
        }

        // truncar a construir o resultado
        HashMap<Integer, List<Query6>> result = new HashMap<>();
        for (int ano : ord.keySet()){
            result.put(ano, new ArrayList<>());
            int contador = 0;
            for (Query6 q : ord.get(ano)){
                if (contador > x || contador > ord.get(ano).size()) {
                    break;
                }
                result.get(ano).add(q);
                contador++;
            }
        }

        ArrayList<List<String>> table = new ArrayList<>();

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Ano");
        titulos.add("Nr reviews");
        titulos.add("Nr de users");

        table.add(titulos);

        for( Map.Entry<Integer,List<Query6>> map : result.entrySet() ){
            for( Query6 q : map.getValue() ){

                ArrayList<String> linha = new ArrayList<>();
                linha.add(String.valueOf(map.getKey()));
                linha.add(String.valueOf(q.getNr_reviews()));
                linha.add(String.valueOf(q.getUsersSize()));

                table.add(linha);
            }
        }

        time = Crono.getTime();
        return new Table(table);
    }
    /**
     * Percorremos em primeiro lugar todas as reviews, de modo a criar um HashMap, cuja key é o nome da cada cidade, e cujo value é um outro Map.
     * Este último é constituído pelo par key/value: nome do negócio e o seu respetivo número de reviews.
     * Seguidamente, percorre-se este Map constituído por todas as cidades e converte-se este mesmo num Map com as mesmas keys, mas cujos values são simplesmente listas com os top três negócios.
     *
     * @return uma Table com cada cidade em conjunto com os top 3 negocios mais avalaidos nela
     */
    public Table query7(){
        Crono.start();

        Map<String, Map<String,Integer>> cidades = new HashMap<>();   // Cidade , Negocio , nr de reviews
        Map<String,Business> bizs = bCat.getCat();

        for( Review r : rCat.getCat().values() ){
            //retirar dpois das condicoes estarem escritas
            if( bizs.get(r.getBusiness_id()) != null) {
                String city = bizs.get(r.getBusiness_id()).getCity();
                String business = bizs.get(r.getBusiness_id()).getName();

                if (cidades.containsKey(city)) {

                    Map<String, Integer> infoCidade = cidades.get(city);

                    if (infoCidade.containsKey(business)) infoCidade.replace(business, infoCidade.get(business) + 1);
                    else infoCidade.put(business, 1);
                } else {
                    Map<String, Integer> infoCidade = new HashMap<>();
                    infoCidade.put(business, 1);

                    cidades.put(city, infoCidade);
                }
            }
        }

        Map<String,List<String>> cidadesComTopN = new HashMap<>();

        for( Map.Entry<String,Map<String,Integer>> m : cidades.entrySet() )
            cidadesComTopN.put( m.getKey() , m.getValue().entrySet().stream().sorted(Comparator.comparingInt(Map.Entry::getValue)).limit(3).map(Map.Entry::getKey).collect(Collectors.toList()) ) ;

        ArrayList<List<String>> table = new ArrayList<>();

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Cidade");
        titulos.add("Negocios Top3");

        table.add(titulos);

        for( Map.Entry<String,List<String>> cidade : cidadesComTopN.entrySet() ){
            for(  String negocio : cidade.getValue() ) {
                ArrayList<String> linha = new ArrayList<>();
                linha.add(cidade.getKey());
                linha.add(negocio);
                table.add(linha);
            }
        }

        Table t = new Table(table);
        time = Crono.getTime();

        return t;
    }
    /**
     * Foi criado um HashMap com o id do utilizador e um conjunto com os respetivos id´s de negócio.
     * De seguida é feita a ordenação pelo maior de negócios diferentes a que um user fez review, com o auxílio do ComparatorQuery8.
     *
     * @param x número de utilizadores desejado
     * @return uma Table com o conjunto dos top x utilizadores que mais avaliaram negocios
     */
    public Table query8(int x){
        Crono.start();

        HashMap<String, HashSet<String>> usersBusiness = new HashMap<>();

        for (Review r : rCat.getCat().values()){
            if (!usersBusiness.containsKey(r.getUser_id()))   usersBusiness.put(r.getUser_id(), new HashSet<>());
            if (!usersBusiness.get(r.getUser_id()).contains(r.getBusiness_id()))   usersBusiness.get(r.getUser_id()).add(r.getBusiness_id());
        }

        TreeSet<Query8> aux = new TreeSet<>(new ComparatorQuery8());
        for (String u : usersBusiness.keySet()){
            Query8 a = new Query8(u, usersBusiness.get(u).size());
            aux.add(a);
        }

        int control = aux.size();

        ArrayList<List<String>> table = new ArrayList<>();

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("User id");
        titulos.add("Nr de negocios");

        table.add(titulos);

        for (int i = 0 ; i < control && i < x; i++){

            ArrayList<String> linha = new ArrayList<>();
            Query8 user = aux.pollLast();
            linha.add(user.getIdUser());
            linha.add(String.valueOf(user.getNrBusiness()));

            table.add(linha);
        }

        time = Crono.getTime();
        return new Table(table);
    }
    /**
     * Agrupamos a bizsInfo pelo nome da cidade, criando assim um Map cuja key continua o nome da cidade e key como uma lista de instâncias de BizInfo.
     * Finalmente, cria-se um novo Map cujas keys são os estados, e cujos values são um outro Map, este por sua com com as keys, as cidades e os values as listas de instâncias de BizInfo.
     *
     * @return uma Table com o conjunto de todos os estados, todas as cidades associadas a ele, e para estas, todos os negocios associados em conjunto com a sua media de classificacao
     */
    public Table query10(){
        Crono.start();

        Map<String,List<BizInfo>> map1 = bizsInfo.values().stream().collect(Collectors.groupingBy(BizInfo::getCidade));
        Map<String,Map<String,List<BizInfo>>> map2 = new HashMap<>();

        for( Map.Entry<String,List<BizInfo>> m : map1.entrySet() ){

            String estado = m.getValue().get(0).getEstado();

            if( map2.containsKey( estado )) map2.get(estado).put( m.getKey() , map1.get(m.getKey()));

            else {
                Map<String,List<BizInfo>> newMap = new HashMap<>();
                newMap.put( m.getKey() , map1.get ( m.getKey() ) );

                map2.put( estado , newMap );
            }
        }


        ArrayList<List<String>> table = new ArrayList<>();

        ArrayList<String> titulos = new ArrayList<>();
        titulos.add("Estado");
        titulos.add("Cidade");
        titulos.add("Negocio");
        titulos.add("Media");

        table.add(titulos);

        for( Map.Entry<String,Map<String,List<BizInfo>>> m : map2.entrySet() ){
            for( Map.Entry<String,List<BizInfo>> m1 : m.getValue().entrySet() ) {
                for( BizInfo biz : m1.getValue() ) {
                    ArrayList<String> linha = new ArrayList<>();
                    linha.add(m.getKey());
                    linha.add(m1.getKey());
                    linha.add(biz.getNome());
                    linha.add(String.format("%.2f",biz.getNotaMedia()));

                    table.add(linha);
                }
            }
        }

        Table t = new Table(table);
        time = Crono.getTime();

        return t;
    }

    //----------------------------------------getsQueries-------------------------------------

    public String getQuery1(){return this.query1;}
    public String getQuery2(){
        return this.query2;
    }
    public String getQuery4(){
        return this.query4;
    }
    public double getTime(){
        return this.time;
    }



}
