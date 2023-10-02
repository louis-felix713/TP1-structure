/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author IFT-2008, Louis-Felix Veillette (537 183 048)
 * \version 0.1
 * \date Automne 2023
 *
 */

#include "Porte.h"

namespace TP1
{
    //Complétez ou modifiez l'implémentation des méthodes demandées.
  /**
   * \brief Constructeur par defaut d une porte
   */
    Porte::Porte(){
      Porte::color = Aucun;
      Porte::destination = nullptr;
    }
    /**
     * \brief constructeur qui initialize les vraies donnees de la porte
     * \param[in] c, la couleur de la porte
     * \param[in] d, la piece ou mene la porte
     */
    Porte::Porte(Couleur c, Piece* d){
      Porte::color = c;
      Porte::destination = d;
    }
    /**
     * Constructeur de copie d une porte
     * \param[in] source, la porte a copie
     */
    Porte::Porte(const Porte& source){
      this->color = source.color;
      this->destination = source.destination;
    }
    /**
     * \brief Destructeur
     */
    Porte::~Porte() {
      
    }
    /**
     * \brief Operateur egale
     * \param source, la porte qui sera indentique
     * \return notre porte
     */
    const Porte& Porte::operator =(const Porte& source) {
        return *this;
    }
    /**
     * \brief operateur egale de comparaison
     * \param source, la porte en comparaison
     * \return si la porte est identique
     */
    bool Porte::operator ==(const Porte& source) const {
        return *this == source;
    }

}
