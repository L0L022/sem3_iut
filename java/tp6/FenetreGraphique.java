import javax.swing.*;

public class FenetreGraphique extends JFrame
{
  ZoneDessin zoneDessin;

  FenetreGraphique()
  {
    super();
    setSize(300, 300);
    setLocationRelativeTo(null);
    setResizable(false);
    setDefaultCloseOperation(FenetreGraphique.EXIT_ON_CLOSE);
    setAlwaysOnTop(true);
    setTitle("Ma fenetre");

    zoneDessin = new ZoneDessin();
    setContentPane(zoneDessin);
    pack();
    
    setVisible(true);
  }
}
