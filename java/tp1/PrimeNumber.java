import java.util.*;
import java.lang.*;

public class PrimeNumber
{
  public static void main(String[] args)
  {
    System.out.print("Le nombre à tester (>0) :");
    Scanner keyboard = new Scanner(System.in);
    int userNumber = keyboard.nextInt();

    if (userNumber <= 0) {
      System.out.println("Le nombre à tester doit être > 0 !!!!!!!!!!");
      return;
    }

    if (isPrimeNumber(userNumber))
      System.out.println(userNumber+" est un nombre premier.");
    else
      System.out.println(userNumber+" n'est pas un nombre premier.");

    for (int i = 1; i<=100; ++i) {
      if(isPrimeNumber(i))
        System.out.println(i+" ");
    }
  }

  public static boolean isPrimeNumber(int number) {
    if (number % 2 == 0)
      return false;

    for (int i = 3; i <= Math.ceil(Math.sqrt(number)); i += 2)
      if (number % i == 0)
        return false;

    return true;
  }
}
