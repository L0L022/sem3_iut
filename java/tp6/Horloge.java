public class Horloge
{
  public static void main (String [] args)
  {
    FenetreGraphique fenetre = new FenetreGraphique();
    fenetre.setDefaultCloseOperation(FenetreGraphique.EXIT_ON_CLOSE);
    fenetre.setTitle("Ma fenetre");
    fenetre.setSize(500, 400);
    fenetre.setVisible(true);
  }
}
