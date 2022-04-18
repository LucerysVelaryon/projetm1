#ifndef ANNEXES
#define ANNEXES

bool estVide(int) ;
bool estB(int) ;
bool estN(int i) ;
bool licite(int couleur, int i) ;
bool dedans(int x, int y) ;
int changeCouleur(int couleur) ;

#endif

/* --------------------------------------------------------------------------------------------------------------------------------- */

#ifndef GRILLE
#define GRILLE

class grille
{
  public:
    int g[8][8][3] ;      // dimension 2.1 = nombre de cases retournables blancs si joué ici ; dimension 2.2 = nombre de cases retournables noires si joué ici
    void init() ;
    void affichageJeu() const ;
    void affichageBrut() const ;
    void retournerPlacer(int, int, int) ;
    bool jeuFini() ;
    void gagnant(int*, int*, int*) ;
    int recupNbLicites(int) ;
    int recupNumeroTour() ;
    void incrementNumeroTour() ;
  private:
    int numero_tour ;
    int nb_licites_b ;    //nb coups jouables blanc
    int nb_licites_n ;    //nb coups jouables noir
    void rayonnement(int, int, int, int) ;
    void majNbCoupsLicite(int, int, int) ;
} ;

#endif

/* --------------------------------------------------------------------------------------------------------------------------------- */

#ifndef HUMAIN
#define HUMAIN

class humain
{
  public:
    void init(int) ;
    int recupCouleur() ;
    void choixCoups(grille, int*, int*) ;
  protected:
    int couleur ;
} ;

#endif

/* --------------------------------------------------------------------------------------------------------------------------------- */

#ifndef ORDI
#define ORDI

class ordiAleatoire : public humain         // hérite de humain, choisit un coup aléatoire parmis les coups possibles de sa couleur
{
  public:
    void init(int) ;
    void choixCoups(grille, int*, int*) ;
} ;

class ordiRetourneMax : public humain         // hérite de humain, choisit un coup qui retourne un max de pions adverses
{
  public:
    void choixCoups(grille, int*, int*) ;
  protected:
    int meilleurCoups(grille, int*, int*) ;
} ;

class ordiMinMax : public ordiRetourneMax
{
  public:
    void initProfondeur(int) ;
    void choixCoups(grille, int*, int*) ;
  private:
    int profondeur_max ;
    int fonctionMinMax(grille, int, int*, int*) ;
} ;

#endif