import static java.lang.System.nanoTime;

public class Crono {

    // Variaveis de instância
    private static long inicio = 0L;
    private static long fim = 0L;

    /**
     * Metodo que permite iniciar a contagem do tempo
     */
    public static void start() {
        fim = 0L; inicio = nanoTime();
    }

    /**
     * Metodo que retorna tempo passado
     */
    public static double stop() {
        fim = nanoTime();
        long elapsedTime = fim - inicio;
        // segundos
        return elapsedTime / 1.0E09;
    }

    /**
     * Metodo que retorna tempo passado
     */
    public static double getTime() {
        return stop();
    }

    /**
     * Metodo que retorna tempo passado no formato de string
     */
    public static String getTimeString() {
        return "Elapsed Time: " + getTime() + "s\n";
    }
}
