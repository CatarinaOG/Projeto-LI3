import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * Script que testa execução do programa
 */

public class ScriptPerformance {

    public static void main(String[] args) {

        GestReview gr = new GestReview();

        PrintWriter writer = null;
        try {
            writer = new PrintWriter(new File("TestesPerfomance.csv"));
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        writer.write("Funcionalidade, 1ª Medição (s), 2ª Medição (s), 3ª Medição (s), 4ª Medição (s), 5ª Medição (s), Média (s)\n");

        ArrayList<Double[]> times = new ArrayList<>();

        for (int i = 0; i < 5; i++){
            times.add(new Double[11]);
        }

        for (int i = 0; i < 5; i++) {
            // Carregamento de ficheiros
            try {
                Crono.start();
                gr.readFicheiros("/Users/inesmarinho/Desktop/li3Java/business_full.csv",
                        "/Users/inesmarinho/Desktop/li3Java/users_full.csv",
                        "/Users/inesmarinho/Desktop/li3Java/reviews_1M.csv");
                double time = Crono.stop();
                times.get(i)[0] = time;
                System.out.println("Tempo de carregamento de ficheiros = " + time + "s");

                // Queries interativas
                System.out.println("Queries interativas:");
                // Query 1
                Crono.start();
                gr.query1();
                time = Crono.stop();
                times.get(i)[1] = time;
                System.out.println("Tempo da query 1 = " + time + "s");

                // Query 2
                Crono.start();
                gr.query2(4, 2004);
                time = Crono.stop();
                times.get(i)[2] = time;
                System.out.println("Tempo da query 2 = " + time + "s");

                // Query 3
                Crono.start();
                gr.query3("q_QQ5kBBwlCcbL1s4NVK3g");
                time = Crono.stop();
                times.get(i)[3] = time;
                System.out.println("Tempo da query 3 = " + time + "s");

                // Query 4
                Crono.start();
                gr.query4("IWrImh0qK2qFZ4oFI8oMTg");
                time = Crono.stop();
                times.get(i)[4] = time;
                System.out.println("Tempo da query 4 = " + time + "s");

                // Query 5
                Crono.start();
                gr.query5("RtGqdDBvvBCjcu5dUqwfzA");
                time = Crono.stop();
                times.get(i)[5] = time;
                System.out.println("Tempo da query 5 = " + time + "s");

                // Query 6
                Crono.start();
                gr.query6(5);
                time = Crono.stop();
                times.get(i)[6] = time;
                System.out.println("Tempo da query 6 = " + time + "s");


                // Query 7
                Crono.start();
                gr.query7();
                time = Crono.stop();
                times.get(i)[7] = time;
                System.out.println("Tempo da query 7 = " + time + "s");

                // Query 8
                Crono.start();
                gr.query8(4);
                time = Crono.stop();
                times.get(i)[8] = time;
                System.out.println("Tempo da query 8 = " + time + "s");

                // Query 9
                Crono.start();
                gr.query9("RA4V8pr014UyUbDvI-LW2A", 10);
                time = Crono.stop();
                times.get(i)[9] = time;
                System.out.println("Tempo da query 9 = " + time + "s");

                // Query 10
                Crono.start();
                gr.query10();
                time = Crono.stop();
                times.get(i)[10] = time;
                System.out.println("Tempo da query 10 = " + time + "s");

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        // Escrever para ficheiro
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 11; i++) {
            if (i == 0) {
                sb.append("Tempo de carregamento dos ficheiros");
                sb.append(",");
                for (int j = 0; j <= 5; j++) {
                    if (j != 5) {
                        sb.append(times.get(j)[i].toString());
                        sb.append(",");
                    }
                    else {
                        Double media = new Double(0);
                        for (int k = 0; k < 5; k++){
                            media += times.get(k)[i];
                        }
                        media = media/5;
                        sb.append(media.toString());
                    }
                }
            }
            else {
                sb.append("Query " + i);
                sb.append(",");
                for (int j = 0; j <= 5; j++) {
                    if (j != 5) {
                        sb.append(times.get(j)[i].toString());
                        sb.append(",");
                    }
                    else {
                        Double media = new Double(0);
                        for (int k = 0; k < 5; k++){
                            media += times.get(k)[i];
                        }
                        media = media/5;
                        sb.append(media.toString());
                    }
                }
            }
            sb.append("\n");
        }
        writer.write(sb.toString());
        writer.flush();
        writer.close();
    }
}
