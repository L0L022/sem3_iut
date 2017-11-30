import javax.swing.*;

public class FenetreGraphique extends JFrame
{
  ZoneDessin zoneDessin;

  FenetreGraphique()
  {
    super();
    zoneDessin = new ZoneDessin();
    setContentPane(zoneDessin);
    pack();
  }
}
