import java.util.*;
import java.lang.*;

public class Fibonacci
{
  public static void main(String[] args)
  {
    // if (args.length != 1) {
    //   System.out.print("Il faut donner un nombre en argument >= 2 !");
    //   return;
    // }
    //
    // double user_number = Integer.parseInt(args[0]);
    //
    // if (user_number < 2) {
    //   System.out.print("Le nombre en argument doit être >= 2 !");
    //   return;
    // }

    Scanner keyboard = new Scanner(System.in);
    int userNumber;

    do {
      System.out.print("Nombre i (>=2) :");
      userNumber = keyboard.nextInt();
    } while (userNumber < 2);

    int first = 1, second = 1, third = 0;
    //System.out.print("t0 = "+first+"\n");
    //System.out.print("t1 = "+second+"\n");
    for (int i = 2; i <= userNumber; i = i + 1) {
      third = first + second;
      first = second;
      second = third;

      //System.out.print("t"+i+" = "+third+"\n");
    }
    System.out.print("t"+userNumber+" = "+third+"\n");
  }
}
