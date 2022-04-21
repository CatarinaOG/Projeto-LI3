public class Query8 {
    String idUser;
    int nrBusiness;

    public Query8(String idUser, int nrBusiness) {
        this.idUser = idUser;
        this.nrBusiness = nrBusiness;
    }

    public String getIdUser() {
        return idUser;
    }

    public void setIdUser(String idUser) {
        this.idUser = idUser;
    }

    public int getNrBusiness() {
        return nrBusiness;
    }

    public void setNrBusiness(int nrBusiness) {
        this.nrBusiness = nrBusiness;
    }

    public String toString() {
        return "Query8{" +
                "idUser='" + idUser + '\'' +
                ", nrBusiness=" + nrBusiness +
                '}';
    }
}

