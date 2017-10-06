import java.util.*;

public class Minimum
{
  public static void main (String [] args)
  {
    Scanner keyboard = new Scanner(System.in);
    double a, b, c;
    System.out.print("a :");
    a = keyboard.nextDouble();
    System.out.print("b :");
    b = keyboard.nextDouble();
    System.out.print("c :");
    c = keyboard.nextDouble();
    System.out.print("Minimum : "+minimum(a, b, c));
  }

  public static double minimum(double a, double b)
  {
    if (a < b)
      return a;
    else
      return b;
  }

  public static double minimum(double a, double b, double c)
  {
    return minimum(minimum(a, b), c);
  }
}
