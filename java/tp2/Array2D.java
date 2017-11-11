import java.util.*;

public class Array2D
{
  public static void main (String [] args)
  {
    Scanner keyboard = new Scanner(System.in);

    System.out.print("Sur combien d'années travaillez vous ? : ");
    double data[][] = new double[keyboard.nextInt()][12];

    for (double array[] : data) {
      randFill(array);
      print(array);
      System.out.println();
    }
  }

  public static void randFill(double array[])
  {
    for (int i = 0; i < array.length; ++i)
      array[i] = Math.random() * 60.0 - 20.0;
  }

  public static void print(double array[])
  {
    for (int i = 0; i < array.length; ++i) {
      System.out.format("%.3f", array[i]);
      if (i < array.length - 1)
        System.out.print(", ");
    }
  }
}
