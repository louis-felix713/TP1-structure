/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Étudiant(e)
 * \version 0.1
 * \date Automne 2023
 *
 */

#include "Piece.h"

namespace TP1
{
    //Complétez ou modifiez l'implémentation des méthodes demandées.

    Piece::Piece(){
      this->nom = "";
      this->distanceDuDebut = 0;
      this->parcourue = false;
      this->portes = std::list<Porte>();
      
    }

    Piece::Piece(const std::string & s){
      this->nom = s;
      this->distanceDuDebut = 0;
      this->parcourue = false;
      this->portes = std::list<Porte>();
    }

    Piece::Piece(const Piece& source){
      this->nom = source.nom;
      this->distanceDuDebut = source.distanceDuDebut;
      this->parcourue = source.parcourue;
      this->portes = source.portes;
    }

    Piece::~Piece(){
      portes.clear ();
    }

    const Piece& Piece::operator =(const Piece& source){
      if (this != &source) {
          this->portes = source.portes;
          this->nom = source.nom;
          this->parcourue = source.parcourue;
          this->distanceDuDebut = source.distanceDuDebut;
      }
        return *this;
    }

    void Piece::setParcourue(bool p){
      this->parcourue = p;
    }

    void Piece::setDistanceDuDebut(int d){
      this->distanceDuDebut = d;
    }

    void Piece::ajoutePorte(const Porte& p){
      this->portes.push_back (p);
    }

}
