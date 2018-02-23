import java.util.*;
import java.util.Map.Entry;

public class Vectorr
{
  public static void main (String [] args)
  {
    Vector<String> inputs = new Vector<String>();
    sortedFill(inputs);
    System.out.println("Ce que vous avez entré :");
    disp(inputs);
    System.out.println("Lise des doublons :");
    showDuplication(inputs);
  }

  public static void disp(Vector<String> array)
  {
    for (String str : array) {
      System.out.println(str);
    }
  }

  public static void fill(Vector<String> array)
  {
    Scanner k = new Scanner(System.in);
    String input;
    boolean isZero;
    do {
      System.out.print("Entrez une chaine de caractères (\\0 pour terminer) : ");
      input = k.next();
      isZero = input.equals("\\0");
      if (!isZero)
        array.add(input);
    } while (!isZero);
    k.close();
  }

  public static void sortedFill(Vector<String> array)
  {
    fill(array);
    Collections.sort(array);
  }

  public static Map<String, Integer> getDuplication(Vector<String> array)
  {
   Map<String, Integer> duplication = new HashMap<>();
   Integer occ;
   for (String str : array) {
     occ = duplication.get(str);
     if (occ == null)
       duplication.put(str, 1);
     else
       duplication.put(str, occ+1);
   }

   Set<Entry<String, Integer>> dupSet = duplication.entrySet();
   Iterator<Entry<String, Integer>> it = dupSet.iterator();
   while(it.hasNext()){
      Entry<String, Integer> e = it.next();
      if (e.getValue() <= 1)
       duplication.remove(e.getKey());
   }

   return duplication;
  }

  public static void showDuplication(Vector<String> array)
  {
    getDuplication(array).forEach((k, v) -> System.out.println(k + " : " + v));
  }
}
