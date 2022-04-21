
import java.io.Serializable;
import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.time.LocalDate;
import java.util.Map;


public class Review implements Serializable {

    private String review_id;
    private String user_id;
    private String business_id;
    private Double stars ;
    private int useful ;
    private int funny ;
    private int cool;
    private LocalDateTime date;
    private String text;

    public Review(){
        this.review_id = "";
        this.user_id = "";
        this.business_id = "";
        this.stars = 0.0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
        this.date = null;
        this.text = "";
    }



    public Review(  String review_id,String user_id,String business_id,Double stars,int useful,int funny,int cool,LocalDateTime date, String text){
        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }
//----------------------------------------------------Metodos--------------------------------------------------------------

    public static Review readR(String s){
        String[] campos = s.split(";");

        if (campos.length>8) {
            LocalDateTime e = convertDate(campos[7]);

            if (campos[0] != null && campos[1] != null && campos[2] != null && isNumeric(campos[3]) && campos[4] != null
                    && campos[5] != null && campos[6] != null && e != null && campos[8] != null)
                return new Review(campos[0], campos[1], campos[2], Double.parseDouble(campos[3]), Integer.parseInt(campos[4]), Integer.parseInt(campos[5]), Integer.parseInt(campos[6]), e, campos[8]);
            else return null;
        }
        else return null;
    }
    public static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch(NumberFormatException e){
            return false;
        }
    }
    public static LocalDateTime convertDate(String str){
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            return LocalDateTime.parse(str, formatter);
        } catch(DateTimeParseException e){
            return null;
        }

    }


    //---------------------------------------------------Sets e Gets---------------------------------------------------------------
    public String getReview_id() {
        return review_id;
    }

    public void setReview_id(String review_id) {
        this.review_id = review_id;
    }

    public String getUser_id() {
        return user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getBusiness_id() {
        return business_id;
    }

    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    public Double getStars() {
        return stars;
    }

    public void setStars(Double stars) {
        this.stars = stars;
    }

    public int getUseful() {
        return useful;
    }

    public void setUseful(int useful) {
        this.useful = useful;
    }

    public int getFunny() {
        return funny;
    }

    public void setFunny(int funny) {
        this.funny = funny;
    }

    public int getCool() {
        return cool;
    }

    public void setCool(int cool) {
        this.cool = cool;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    //------------------------------------------------Metodos Base------------------------------------------------------------------

    public String toStringReview() {
        return "Review[" +
                "review_id='" + review_id + '\'' +
                ", user_id='" + user_id + '\'' +
                ", business_id='" + business_id + '\'' +
                ", stars='" + stars + '\'' +
                ", useful=" + useful + '\'' +
                ", funny=" + funny + '\'' +
                ", cool=" + cool + '\'' +
                ", date=" +date + '\'' +
                ", text=" + text +
                ']';
    }

    public Review clone(){
        return new Review(this.review_id,this.user_id,this.business_id,this.stars,this.useful,this.funny,this.cool,this.date,this.text);
    }}