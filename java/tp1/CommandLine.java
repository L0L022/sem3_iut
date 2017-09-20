import java.util.*;
import java.lang.*;

public class CommandLine
{
  public static void main(String[] args)
  {
    System.out.print("Il y a "+args.length+" arguments : ");
    for (int i = 0; i < args.length; ++i) {
      System.out.print(args[i]);
      if (i < args.length - 1)
        System.out.print(", ");
    }
    System.out.print("\n");
  }
}
