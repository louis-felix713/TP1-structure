/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Étudiant(e)
 * \version 0.1
 * \date Automne 2023
 *
 */

#include "Porte.h"

namespace TP1
{
    //Complétez ou modifiez l'implémentation des méthodes demandées.

    Porte::Porte(){
      Porte::color = Aucun;
      Porte::destination = nullptr;
    }

    Porte::Porte(Couleur c, Piece* d){
      Porte::color = c;
      Porte::destination = d;
    }

    Porte::Porte(const Porte& source){
      this->color = source.color;
      this->destination = source.destination;
    }

    Porte::~Porte() {
      
    }

    const Porte& Porte::operator =(const Porte& source) {
        return *this;
    }

    bool Porte::operator ==(const Porte& source) const {
        return true;
    }

}
