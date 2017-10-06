import java.util.*;
import static java.lang.Math.toIntExact;

public class NIR
{
  public static void main (String [] args)
  {
    Scanner keyboard = new Scanner(System.in);
    System.out.print("NIR  : ");
    String nir = keyboard.nextLine();
    System.out.print("code : ");
    int code = keyboard.nextInt();
    if (test(nir, code))
      info(nir);
    else
      System.out.println("Code invalide !");
  }

  public static int codeControle(String num)
  {
    if (num.length() != 13)
      throw new RuntimeException("NIR::codeControle: num.length() != 13");

    //un fonction c'est mieux
    long rm = 0;
    String validNum = num.replace('A', '0');
    validNum = validNum.replace('B', '0');

    if (num.indexOf('A') != -1)
      rm = 1000000;
    else if (num.indexOf('B') != -1)
      rm = 2000000;

    return 97 - (toIntExact((Long.parseLong(validNum) - rm) % 97L));
  }

  public static void info(String num)
  {
    String genre = new String();
    if (num.charAt(0) == '1') {
      genre = "Homme";
    } else if (num.charAt(0) == '2') {
      genre = "Femme";
    } else if (num.charAt(0) == '3') {
      genre = "Autre";
    }
    //ou tableau !
    System.out.println("Genre : "+genre);
    System.out.println("Année de naissance : "+num.substring(1, 3));
    System.out.println("Mois de naissance : "+num.substring(3, 5));
    System.out.println("Département de naissance : "+num.substring(5, 7));
    System.out.println("Commune de naissance : "+num.substring(7, 10));
    System.out.println("N° d’ordre : "+num.substring(10, 13));
  }

  public static boolean test(String nir, int code)
  {
    return codeControle(nir.substring(0, 13)) == code;
  }
}
