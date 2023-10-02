/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author IFT-2008, Louis-Felix Veillette (537 183 048)
 * \version 0.1
 * \date Automne 2023
 *
 */

#include "Piece.h"

namespace TP1
{
    
    /**
     * \brief Constructeur d'une piece
     * \post la piece sera initialise
     */
    Piece::Piece(){
      this->nom = "";
      this->distanceDuDebut = 0;
      this->parcourue = false;
      this->portes = std::list<Porte>();
      
    }
    /**
     * \brief Constructeur surcharge initialise un nom de piece
     * \param[in] s, Le nom de la piece
     * \post la piece sera initialise avec un nom
     */
    Piece::Piece(const std::string & s){
      this->nom = s;
      this->distanceDuDebut = 0;
      this->parcourue = false;
      this->portes = std::list<Porte>();
    }
    /**
     * \brief Constructeur de copie d'une piece
     * \param[in] source, la piece a copie
     */
    Piece::Piece(const Piece& source){
      this->nom = source.nom;
      this->distanceDuDebut = source.distanceDuDebut;
      this->parcourue = source.parcourue;
      this->portes = source.portes;
    }
    /**
     * Destructeur d'une piece
     */
    Piece::~Piece(){
      portes.clear ();
    }
    /**
     * \brief Code de l'operateur =
     * \param[in] source, La piece egale
     * \return la piece
     */
    const Piece& Piece::operator =(const Piece& source){
      if (this != &source) {
          this->portes = source.portes;
          this->nom = source.nom;
          this->parcourue = source.parcourue;
          this->distanceDuDebut = source.distanceDuDebut;
      }
        return *this;
    }
    /**
     * \brief Modifie si la piece est parcouru ou non
     * \param[in] p, la reponse a la question
     */
    void Piece::setParcourue(bool p){
      this->parcourue = p;
    }
    /**
     * \brief Change la distance parcourue
     * \param[in] d, la nouvelle distance
     */
    void Piece::setDistanceDuDebut(int d){
      this->distanceDuDebut = d;
    }
    /**
     * \brief Ajoute une porte a la piece
     * \param[in] d, la nouvelle porte
     */
    void Piece::ajoutePorte(const Porte& p){
      this->portes.push_back (p);
    }

}
