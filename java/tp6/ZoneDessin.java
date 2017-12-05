import java.awt.*;
import javax.swing.*;
import java.io.File;
import javax.imageio.ImageIO;
import java.io.IOException;
import java.lang.Math;
import java.awt.geom.Point2D;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class ZoneDessin extends JPanel
{
  Image img;

  ZoneDessin()
  {
    super();
    setPreferredSize(new Dimension(300, 300));
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
    g.fillOval(5, 5, 300-5, 300-5);
    g.setColor(Color.green);
    g.fillOval(10, 10, 300-15, 300-15);
    g.drawImage(img, 300/4, 300/4, this);
  }

  private void affiche_graduations(Graphics g)
  {
    g.setColor(Color.black);
    double center_x = 300/2, center_y = 300/2;
    double radius = 300/2 - 10;
    for (int i = 1; i < 13; ++i) {
      Point2D pt = hour_to_point(i, radius, center_x, center_y);
      g.drawString(String.valueOf(i), (int)(pt.getX()), (int)(pt.getY()));
    }
  }

  private void affiche_aiguilles(Graphics g)
  {
    Calendar calendar = new GregorianCalendar();
    int heures  = calendar.get(Calendar.HOUR_OF_DAY);
    int minutes = calendar.get(Calendar.MINUTE);
    int secondes = calendar.get(Calendar.SECOND);

    // Graphics2D g2 = (Graphics2D) g;
    // g2.setStroke(new BasicStroke(10));
    // g2.drawLine(20, 40, 200, 120);
    double center_x = 300/2, center_y = 300/2;
    double radius = 300/2 - 10;
    Point2D pt_heures = hour_to_point(heures, radius, center_x, center_y);
    g.drawLine((int)center_x, (int)center_y, (int)pt_heures.getX(), (int)pt_heures.getY());
  }

  private Point2D hour_to_point(double hour, double radius, double center_x, double center_y)
  {
    double nb = ((2 * Math.PI)/12)*((hour+9)%12);
    return new Point2D.Double(center_x + radius * Math.cos(nb), center_y + radius * Math.sin(nb));
  }
}
