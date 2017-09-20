import java.util.*;
import java.lang.*;

public class MysteryNumber
{
  public static void main(String[] args)
  {
    final int maxSecretNumber = 10;
    Random rand = new Random();
    int secretNumber = rand.nextInt(maxSecretNumber + 1);
    int userNumber = -1;
    int attempsLeft = 5;
    
    Scanner keyboard = new Scanner(System.in);
    while (userNumber != secretNumber) {
      if (attempsLeft > 0) {
        --attempsLeft;
      } else {
        System.out.println("Tu es nul !");
        break;
      }
      System.out.print("Choisi un nombre dans l'intervale [0; "+maxSecretNumber+"], essais restant = "+attempsLeft+": ");
      userNumber = keyboard.nextInt();

      if (userNumber > secretNumber)
        System.out.println("Plus petit !");
      else if (userNumber < secretNumber)
        System.out.println("Plus grand !");
      else
        System.out.println("T'es trop fort !");
    }
  }
}
