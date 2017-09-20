import java.util.*;

public class Celsius
{
  public static void main(String[] args)
  {
    System.out.print("Celsius :");
    Scanner keyboard = new Scanner(System.in);
    double userCelsius = keyboard.nextDouble();
    double fahrenheit = userCelsius * 9 / 5 + 32;
    System.out.print("Fahrenheit : " + fahrenheit);
  }
}
