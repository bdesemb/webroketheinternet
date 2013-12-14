// Model.h
#pragma once
#include <osg/Vec4>
#include <osgText/Text>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <array>

#include "Pion.h"
#include "Mur.h"

using namespace osg;
using namespace std;

namespace model{
	static const int MUR = 3;
	static const int PION = 1;
	class Model
	{
	private:
		static Model *instance;			// Instance du Model pour le pattern singleton
		int taillePlateau;
		int largeurPlateau;
		int longueurPlateau;
		ref_ptr<Pion> pion1;
		ref_ptr<Pion> pion2;
		ref_ptr<Mur> murJoueur1[10];	//Table des murs du joueur1
		ref_ptr<Mur> murJoueur2[10];	//Table des murs du joueur2
		bool tour;						// Indicateur de tour de jeu
		int tablePosition[17][17];		//Table contenant la position des murs et des pions sur le plateau
		bool murMvt;					//Mode modification des murs
		bool gameOver;					//Jeu terminé

		/* Methode utile à peutPlacerMur
		coord est de la forme [x,y]
		*/
		vector<array<int, 2>> Model::getSuccessors(const array<int, 2> coord);

	public:
		int getTaillePlateau()const{
			return taillePlateau;
		}
		int getLargeurPlateau()const{
			return largeurPlateau;
		}
		int getLongueurPlateau()const{
			return longueurPlateau;
		}
		bool getTour()const{
			return tour;
		}
		void setTour(bool boolean){
			tour = boolean;
		}
		bool getMurMvt(){
			return murMvt;
		}
		bool getGameOver(){
			return gameOver;
		}
		void enterPionMvt() {
			this->murMvt = false;
		}
		ref_ptr<Mur> getMurJoueur1(int numero)const{
			return murJoueur1[numero];
		}
		void setMurJoueur1(int numero, ref_ptr<Mur> m){
			murJoueur1[numero] = m;
		}
		ref_ptr<Mur> getMurJoueur2(int numero)const{
			return murJoueur2[numero];
		}
		void setMurJoueur2(int numero, ref_ptr<Mur> m){
			murJoueur2[numero] = m;
		}
		ref_ptr<Pion> getPion1()const{
			return pion1;
		}
		void setPion1(ref_ptr<Pion> p1){
			pion1 = p1;
		}
		ref_ptr<Pion> getPion2()const{
			return pion2;
		}
		void setPion2(ref_ptr<Pion> p2){
			pion2 = p2;
		}

		// Fonctions déplacement des pions //
		bool incPion_x();			//Déplacement du pion d'une unité vers les x positifs
		bool decPion_x();			//Déplacement du pion d'une unité vers les x negatifs
		bool incPion_y();			//Déplacement du pion d'une unité vers les y positifs
		bool decPion_y();			//Déplacement du pion d'une unité vers les y negatifs

		// Fonction déplacement des murs //
		void incMur_x();			//Déplacement du mur d'une unité vers les x positifs
		void decMur_x();			//Déplacement du mur d'une unité vers les x negatifs
		void incMur_y();			//Déplacement du mur d'une unité vers les y positifs
		void decMur_y();			//Déplacement du mur d'une unité vers les y negatifs

		void enterMurMvt();			//Entrer en mode modification des murs
		void outMurMvt();			//Sortie du mode modification des murs
		void tourSuivant();			//Passe au tour de jeu suivant
		bool ajouterMur();			//Ajouter un mur sur le plateau
		void rotation();			//Effectuer une rotation sur le mur
		void redemarrer();			//Recommencer la partie

		ref_ptr<Mur> murAModifier();	//Retourne le mur à placer sur le plateau de jeu
		ref_ptr<Pion> pionAModifier();	//Retourne le pion à modifier en fonction du tour de jeu

		// Pattern singleton
		Model();
		static Model *getInstance();
		void deplacerMur(float x, float y); //Deplace le mur à la position la plus proche

		bool sauvegarderPlateauJeu(string fileName);
		bool chargerPlateauJeu(string fileName);
		friend ostream & operator << (ostream& fichierOut, const Model& model);
		friend istream & operator >> (istream& fichierIn, const Model& model);
		void setPlateau(int tour, ref_ptr<Pion> pion1, ref_ptr<Pion> pion2, ref_ptr<Mur> tableauMurJoueur1[], ref_ptr<Mur> tableauMurJoueur2[]);
		/*
		Simule le plateau avec le nouveau mur placé pour vérifier s'il peut être placé.
		Si origin, chemin possible vers x[0] sinon chemin possible vers
		x[taille-1] */
		bool peutPlacerMur(int pionX, int pionY, int murX, int murY, bool origin);
	};
}
