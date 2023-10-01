/**
 * \file Labyrinthe.cpp
 * \brief Le code des méthodes membres et privés de la classe Labyrinthe.
 * \author IFT-2008, Étudiant(e)
 * \version 0.1
 * \date Automne 2023
 * 
 */

//Fichiers à compléter par les autres méthodes de la classe Labyrinthes demandées

#include "Labyrinthe.h"

namespace TP1
{
 using namespace std;

// --------------------------
//	Méthodes à implémenter
// --------------------------

    Labyrinthe::Labyrinthe(){
      this->depart = nullptr;
      this->arrivee = nullptr;
      this->dernier = nullptr;
    }

    Labyrinthe::Labyrinthe(const Labyrinthe& source){
      this->dernier = new NoeudListePieces();
      this->dernier->suivant = dernier;
      NoeudListePieces* sentinelleThis = this->dernier;
      NoeudListePieces* sentinelleSource = source.dernier;
      
      do {
          sentinelleThis->piece = Piece (sentinelleSource->piece);
          sentinelleThis->suivant = new NoeudListePieces();
          if (sentinelleSource->suivant == source.dernier) {
              sentinelleThis->suivant = this->dernier;
          }
          sentinelleThis = sentinelleThis->suivant;
          sentinelleSource = sentinelleSource->suivant;
          
        }while(source.dernier != sentinelleSource);
    }

    Labyrinthe::~Labyrinthe() {
      if (dernier != nullptr) {
          NoeudListePieces* sentinelle = dernier->suivant;
          NoeudListePieces* toDelete = sentinelle;
          while(sentinelle != dernier) {
              sentinelle = sentinelle->suivant;
              toDelete->suivant = nullptr;
              delete toDelete;
              toDelete = sentinelle;
          }
          dernier->suivant = nullptr;
          delete dernier;
      }
      dernier = nullptr;
    }

    const Labyrinthe& Labyrinthe::operator =(const Labyrinthe& source) {
      if (this != &source) {
        this->depart = source.depart;
        this->arrivee = source.arrivee;
        this->dernier = source.dernier;
      }

        return *this;
    }

// -------------------------
//	Méthodes fournies
// -------------------------

/**
 * \fn	void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream &entree)
 * \param[in]	couleur, la couleur du jouer auquel le labyrinthe chargé s'applique
 * \param[in]	entree, fichier contenant la définition du labyrinthe
 */
void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream &entree)
 {
	int nbCols, nbRangs;

    if (!entree.is_open())
        throw logic_error("Labyrinthe::chargeLabyrinthe: Le fichier n'est pas ouvert !");

	entree >> nbCols >> nbRangs;
	entree.ignore(); //pour consommer le \n (le caractère fin de ligne)

	const int MAX_LIGNE = 1000;
	char ligne[MAX_LIGNE];

	entree.getline(ligne, MAX_LIGNE);
	entree.getline(ligne, MAX_LIGNE);

	std::ostringstream s; //Une chaîne pour écrire dedans, cette chaîne servira pour nommer les pièces du labyrinthe

	for (int i = 0; i < nbCols; i++)
	{
		for (int j = 0; j < nbRangs; j++)
		{
			s << i << "," << j;
			Piece p(s.str());
			s.str("");
			ajoutePieceLabyrinthe(p);
		}
	}

	for (int i = 0; i < nbCols; i++)
	{
		if (ligne[i * 4 + 1] == 'D' || ligne[i * 4 + 1] == 'd')
		{
			std::string nom;
			s << i << ",0";
			nom = s.str();
			s.str("");
			placeDepart(nom);
		}
		if (ligne[i * 4 + 1] == 'F' || ligne[i * 4 + 1] == 'f' || ligne[i * 4
				+ 1] == 'A' || ligne[i * 4 + 1] == 'a')
		{
			std::string nom;
			s << i << ",0";
			nom = s.str();
			s.str("");
			placeArrivee(nom);
		}
	}

	for (int j = 0; j < nbRangs; j++)
	{
		entree.getline(ligne, MAX_LIGNE);

		for (int i = (j == nbRangs - 1 && (j & 1)) ? 1 : 0; i < nbCols; i++)
		{
			if (j & 1)
			{
				if (j < nbRangs - 2 && ligne[i * 4 + 3] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 2);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 1);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
				{
					ajoutePassage(couleur, i - 1, j, i, j + 1);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'D' || ligne[i * 4
						+ 1] == 'd'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeDepart(nom);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'F' || ligne[i * 4
						+ 1] == 'f' || ligne[i * 4 + 1] == 'A' || ligne[i * 4
						+ 1] == 'a'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeArrivee(nom);
				}
			}
			else
			{
				if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
				{
					ajoutePassage(couleur, i - 1, j + 1, i, j);
				}
				if (j < nbRangs - 2 && ligne[i * 4 + 1] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 2);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 1);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'D' || ligne[i * 4
						+ 3] == 'd'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeDepart(nom);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'F' || ligne[i * 4
						+ 3] == 'f' || ligne[i * 4 + 3] == 'A' || ligne[i * 4
						+ 3] == 'a'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeArrivee(nom);
				}
			}
		}
	}
 }

/**
 * \fn	Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
 * \param[in]	Couleur couleur Couleur de la porte à ajouter
 * \param[in]	int i1
 * \param[in]	int j1
 * \param[in]	int i2
 * \param[in]	int j2
 */
 void Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
 {

	NoeudListePieces *piece1, *piece2;
	string nomPiece1, nomPiece2;
	ostringstream s;

	s << i1 << "," << j1;
	nomPiece1 = s.str();

	s.str("");

	s << i2 << "," << j2;
	nomPiece2 = s.str();

	s.str("");

	piece1 = trouvePiece(nomPiece1);
	piece2 = trouvePiece(nomPiece2);

	Porte nouvellePorte(couleur, &(piece2->piece));

	piece1->piece.ajoutePorte(nouvellePorte);
 }


/**
 * \fn	Labyrinthe::ajoutePieceLabyrinthe(Piece& p)
 * \brief ajoute une pièce au labyrinthe (si elle ne s'y trouve pas déjà)
 * \param[in]	p La pièce à ajouter
 * \post	la pièce appartient au labyrinthe;
 */

 void Labyrinthe::ajoutePieceLabyrinthe(const Piece& p) {

    if (appartient(p)) return;
    else {	
        Labyrinthe::NoeudListePieces* noeud = new Labyrinthe::NoeudListePieces;
        noeud->piece = p;

        if (dernier == 0){
            noeud->suivant = noeud;
            dernier = noeud;
        }
        else{	
            noeud->suivant = dernier->suivant;
            dernier->suivant = noeud;
        }	
    }
 }

// -------------------------------
//	Autres méthodes à implémenter
// -------------------------------

    int Labyrinthe::solutionner(Couleur joueur) {
      std::queue<Piece*> queue = std::queue<Piece*>();
      Labyrinthe::NoeudListePieces* sentinelle = dernier;
      depart->setDistanceDuDebut (0);
      arrivee->setDistanceDuDebut (-1);
      queue.push(depart);
      
      do {
          sentinelle->piece.setParcourue (false);
          sentinelle = sentinelle->suivant;
        } while(sentinelle != dernier);
            

      while(queue.size () && arrivee != queue.front()) {
          Piece* chemin = queue.front();
          chemin->setParcourue (true);
          queue.pop ();
          for (Porte porte : chemin->getPortes()) {
              if(porte.getCouleur () == joueur) {
                  porte.getDestination ()->setParcourue (false);
                  porte.getDestination ()->setDistanceDuDebut (chemin->getDistanceDuDebut () + 1);
                  queue.push (porte.getDestination ());
              }
          }

          sentinelle = dernier;
          do {
              if (sentinelle->piece.getNom () != chemin->getNom () && !sentinelle->piece.getParcourue ()) {
                  for (Porte porte : sentinelle->piece.getPortes ()) {
                      if(porte.getCouleur () == joueur && porte.getDestination () == chemin) {
                          sentinelle->piece.setDistanceDuDebut (chemin->getDistanceDuDebut () + 1);
                          sentinelle->piece.setParcourue(false);
                          queue.push (&sentinelle->piece);
                      }
                  }
                }
            sentinelle = sentinelle->suivant;
            } while(sentinelle != dernier);

        }
      return arrivee->getDistanceDuDebut();

    }

    Couleur Labyrinthe::trouveGagnant() {
      Couleur gagnant = Aucun;
      int plusPetit = 0;
      int solutions[4];

      solutions[0] = solutionner(Rouge);
      solutions[1] = solutionner(Vert);
      solutions[2] = solutionner(Bleu);
      solutions[3] = solutionner(Jaune);

      if (solutions[0] == solutions[1] && solutions[1] == solutions[2] && solutions[2] == solutions[3]) { 
          return Aucun;
      }
      for(int i = 0; i <= 3; i++) {
          if (solutions[plusPetit] > solutions[i] && solutions[i] != -1) {
              plusPetit = i;
          }
      }

      switch (plusPetit) {
        case 0:
          return Rouge;
        case 1:
          return Vert;
        case 2:
          return Bleu;
        case 3:
          return Jaune;
        default:
          return Aucun;
      }

    }

    bool Labyrinthe::appartient(const Piece& p) const {
      try {
          this->trouvePiece (p.getNom ());
          return true;
      } catch(exception& e) {
          return false;
      } 
    }

    void Labyrinthe::placeDepart(const std::string& nom) {
      try {
          this->depart = &trouvePiece(nom)->piece;
      } catch(exception& e) {
          std::cout << "Erreur";
      }
    }

    void Labyrinthe::placeArrivee(const std::string& nom) {
      try {
          this->arrivee = &trouvePiece(nom)->piece;
      } catch(exception& e) {
          std::cout << "Erreur";
      }
    }

    Labyrinthe::NoeudListePieces* Labyrinthe::trouvePiece(const std::string& nom) const {
        if (nom == "") throw (std::invalid_argument("Le nom est invalide"));
        if (dernier != nullptr) {
            Labyrinthe::NoeudListePieces* sentinelle = dernier;
            do {
                if (sentinelle->suivant->piece.getNom () == nom) {
                    return sentinelle->suivant;
                }
                sentinelle = sentinelle->suivant;
              } while (sentinelle != nullptr && sentinelle->suivant != dernier) ;
                
            if (dernier->piece.getNom() == nom) {
                return dernier;  
            }
        }

        throw (logic_error("La piece est introuvable"));
    }


 }//fin du namespace
