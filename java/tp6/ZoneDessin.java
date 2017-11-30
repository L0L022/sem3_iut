import java.awt.*;
import javax.swing.*;
import java.io.File;
import javax.imageio.ImageIO;
import java.io.IOException;

public class ZoneDessin extends JPanel
{
  Image img;

  ZoneDessin()
  {
    super();
    try {
      img = ImageIO.read(new File("tux.png"));
    } catch (IOException e) {
      e.printStackTrace();
    }
    setPreferredSize(new Dimension(300, 300));
  }

  public void paint(Graphics g)
  {
    affiche_fond(g);
    affiche_graduations(g);
    affiche_aiguilles(g);
  }

  private void affiche_fond(Graphics g)
  {
    g.setColor(Color.black);
    g.fillOval(0, 0, 10, 10);
    g.drawImage(img, 0, 0, this);
    g.drawString("LEO SUDREAU", 10, 10);
    for (int i = 1; i < 13; ++i) {
      int nb = i + 12/4;
      int nb = ((2pi)/12)*((i+9)%12);
      int x = cos(nb);
      int y = sin(nb);
    }
  }

  private void affiche_graduations(Graphics g)
  {

  }

  private void affiche_aiguilles(Graphics g)
  {

  }
}
