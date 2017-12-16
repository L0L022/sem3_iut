import javax.swing.*;

public class FenetreGraphique extends JFrame implements ActionListener
{
  FenetreGraphique()
  {
    super();
    setSize(600, 400);
    setDefaultCloseOperation(FenetreGraphique.EXIT_ON_CLOSE);
    setTitle("Ma fenetre");

    JMenuItem iCharger = new JMenuItem("Charger");
    iCharger.setActionCommand("menu charger");
    iCharger.addActionListener(this);

    JMenuItem iSauvegarder = new JMenuItem("Sauvegarder");
    iSauvegarder.setActionCommand("menu sauvegarder");
    iSauvegarder.addActionListener(this);

    JMenuItem iQuitter = new JMenuItem("Quitter");
    iQuitter.setActionCommand("menu quitter");
    iQuitter.addActionListener(this);

    JMenu mFichier = new JMenu("Fichier");
    mFichier.add(iCharger);
    mFichier.add(iSauvegarder);
    mCouleur.add(new JSeparator());
    mFichier.add(iQuitter);

    JMenuItem iNoir = new JMenuItem("Noir");
    iNoir.setActionCommand("menu noir");
    iNoir.addActionListener(this);

    JMenuItem iRouge = new JMenuItem("Rouge");
    iRouge.setActionCommand("menu rouge");
    iRouge.addActionListener(this);

    JMenuItem iBleu = new JMenuItem("Bleu");
    iBleu.setActionCommand("menu bleu");
    iBleu.addActionListener(this);

    JMenuItem iPersonnalisee = new JMenuItem("Personnalisée");
    iPersonnalisee.setActionCommand("menu personnalisee");
    iPersonnalisee.addActionListener(this);

    JMenu mCouleur = new JMenu("Couleur");
    mCouleur.add(iNoir);
    mCouleur.add(iRouge);
    mCouleur.add(iBleu);
    mCouleur.add(new JSeparator());
    mCouleur.add(iPersonnalisee);

    JMenuBar menuBar = new JMenuBar();
    menuBar.add(mFichier);
    menuBar.add(mCouleur);
    setJMenuBar(menuBar);

    setVisible(true);
  }

  public void actionPerformed(ActionEvent evenement)
  {
    switch (evenement.getActionCommand()) {
      case "menu quitter":
        System.exit();
        break;
    }
  }
}
