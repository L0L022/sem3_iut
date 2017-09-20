import java.util.*;
import java.lang.*;

public class Pi
{
  public static void main(String[] args)
  {
    if (args.length != 1) {
      System.out.print("Il faut donner un nombre en argument > 0 !");
      return;
    }

    double userNumber = Integer.parseInt(args[0]);

    if (userNumber <= 0) {
      System.out.print("Le nombre en argument doit être > 0 !");
      return;
    }

    double tmp = 0;
    for (int i = 1; i <= userNumber; ++i) {
      tmp += 1 / Math.pow(i, 2);
    }

    double pi = Math.sqrt(6 * tmp);

    System.out.print("PI = "+pi);
  }
}
