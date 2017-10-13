import java.util.*;

public class Array
{
  public static void main (String [] args)
  {
    double array[] = new double[12];
    userFill(array);
    System.out.println("Il y a "+countNegValue(array)+" valeur(s) strictement inférieure(s) à zéro.");
    double value = 0;
    System.out.println("Il y a "+countValue(array, value)+" fois la valeur "+value+".");
  }

  public static void userFill(double array[])
  {
    System.out.println("Entrés des nombres réels :");
    Scanner keyboard = new Scanner(System.in);
    for (int i = 0; i < array.length; ++i) {
      System.out.print("["+i+"] :");
      array[i] = keyboard.nextDouble();
    }
  }

  public static int countNegValue(double array[])
  {
    int count = 0;
    for (double value : array)
      if (value < 0)
        ++count;

    return count;
  }

  public static int countValue(double array[], double value)
  {
    int count = 0;
    for (double v : array)
      if (v == value)
        ++count;

    return count;
  }
}
