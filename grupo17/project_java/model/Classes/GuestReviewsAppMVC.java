import java.util.ArrayList;
import java.util.List;

public class GuestReviewsAppMVC {

    public static void main (String[] args){

        IGestReview gestReview = new GestReview();
        IView view = new View();
        Controller controller = new Controller(gestReview,view);

        controller.run();

    }

}

