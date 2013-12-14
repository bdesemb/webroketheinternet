// Model.cpp
#include "Model.h"
#include "MyView.h"

#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace View;
using namespace model;

namespace model {

	// Les membres static non constants doivent êtres initialisés dans le .cpp
	Model *Model::instance = 0;

	//Constructeur du model
	Model::Model(){
		taillePlateau = 9;
		pion1 = new Pion(6.5, 2.5, 8, 0);
		pion2 = new Pion(6.5, 10.5, 8, 16);
		tour = true;
		murMvt = false;
		gameOver = false;
		int i, j;
		for (i = 0; i < 17; i++){		//Indications de cases vide pour toutes les casses du plateau
			for (j = 0; j < 17; j++){
				tablePosition[i][j] = 0;
			}
		}
		tablePosition[8][0] = 1;		//Position du pion1 dans le tableau
		tablePosition[8][16] = 1;		//Position du pion2 dans le tableau
		for (i = 0; i < 10; i++){	//Placement des murs du joueur1
			murJoueur1[i] = new Mur(i + 2, 1, i, 0);
		}
		for (i = 0; i < 10; i++){	//Placement des murs du joueur2
			murJoueur2[i] = new Mur(i + 2, 12, i, 16);
		}
	}

	// Implémentation classique du pattern singleton
	Model *Model::getInstance(){
		if (instance == 0)
			instance = new Model();
		return instance;
	}

	// Fonctions déplacement des pions //

	//Déplace le centre du pion d'une unité vers les x positifs
	//Return: true si pion a bougé, false sinon
	bool Model::incPion_x(){
		ref_ptr<Pion> pionActuel = pionAModifier();	//On récupère le pion dont c'est le tour
		if (pionActuel->getTableX() != 16 && this->tablePosition[pionActuel->getTableX() + 1][pionActuel->getTableY()] == 0){	//Déplacement du pion de 1 case accepté
			if (this->tablePosition[pionActuel->getTableX() + 2][pionActuel->getTableY()] == 1){	//Si nécéssaire déplacement de 2 cases
				if (pionActuel->getTableX() != 14 && this->tablePosition[pionActuel->getTableX() + 3][pionActuel->getTableY()] == 0){	//Déplacement du pion de 2 case accepté
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
					pionActuel->deplacer(2, 0);		//On déplace le pion de 2 cases
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
					MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
					return true;
				}
				MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
				return false;
			}
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
			pionActuel->deplacer(1, 0);	//On déplace le pion de 1 case
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
			return true;
		}
		MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
		return false;
	}
	//Déplace le centre du pion d'une unité vers les x negatifs
	//Return: true si pion a bougé, false sinon
	bool Model::decPion_x(){
		ref_ptr<Pion> pionActuel = pionAModifier();	//On récupère le pion dont c'est le tour
		if (pionActuel->getTableX() != 0 && this->tablePosition[pionActuel->getTableX() - 1][pionActuel->getTableY()] == 0){	//Déplacement du pion de 1 case accepté
			if (this->tablePosition[pionActuel->getTableX() - 2][pionActuel->getTableY()] == 1){	//Si nécéssaire déplacement de 2 cases
				if (pionActuel->getTableX() != 2 && this->tablePosition[pionActuel->getTableX() - 3][pionActuel->getTableY()] == 0){	//Déplacement du pion de 2 case accepté
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
					pionActuel->deplacer(-2, 0);		//On déplace le pion de 2 cases
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
					MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
					return true;
				}
				MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
				return false;
			}
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
			pionActuel->deplacer(-1, 0);	//On déplace le pion de 1 case
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
			return true;
		}
		MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
		return false;
	}
	//Déplace le centre du pion d'une unité vers les y positifs
	//Return: true si pion a bougé, false sinon
	bool Model::incPion_y(){
		ref_ptr<Pion> pionActuel = pionAModifier();
		if (pionActuel->getTableY() != 16 && this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() + 1] == 0){	//Déplacement du pion de 1 case accepté
			if (this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() + 2] == 1){	//Si nécéssaire déplacement de 2 cases
				if (pionActuel->getTableY() != 14 && this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() + 3] == 0){	//Déplacement du pion de 2 case accepté
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
					pionActuel->deplacer(0, 2);		//On déplace le pion de 2 cases
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
					MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
					if (this->pion1->getTableY() == 16){		//On vérifie qu'après déplacement il n'y a pas de gagnant
						MyView::getInstance()->setStatut("Victoire Blanc!", Vec4(1, 1, 1, 1));
						this->gameOver = true;		//On indique la partie comme terminée
					}
					return true;
				}
				MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
				return false;
			}
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
			pionActuel->deplacer(0, 1);	//On déplace le pion de 1 case
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
			if (this->pion1->getTableY() == 16){		//On vérifie qu'après déplacement il n'y a pas de gagnant
				MyView::getInstance()->setStatut("Victoire Blanc!", Vec4(1, 1, 1, 1));
				this->gameOver = true;		//On indique la partie comme terminée
			}
			return true;
		}
		MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
		return false;
	}
	//Déplace le centre du pion d'une unité vers les y negatifs
	//Return: true si pion a bougé, false sinon
	bool Model::decPion_y(){
		ref_ptr<Pion> pionActuel = pionAModifier();
		if (pionActuel->getTableY() != 0 && this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() - 1] == 0){	//Déplacement du pion de 1 case accepté
			if (this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() - 2] == 1){	//Si nécéssaire déplacement de 2 cases
				if (pionActuel->getTableY() != 2 && this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY() - 3] == 0){	//Déplacement du pion de 2 case accepté
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
					pionActuel->deplacer(0, -2);		//On déplace le pion de 2 cases
					this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
					MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
					if (this->pion1->getTableY() == 16){		//On vérifie qu'après déplacement il n'y a pas de gagnant
						MyView::getInstance()->setStatut("Victoire Blanc!", Vec4(1, 1, 1, 1));
						this->gameOver = true;		//On indique la partie comme terminée
					}
					return true;
				}
				MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
				return false;
			}
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 0;	//On marque la case comme vide dans le tableau
			pionActuel->deplacer(0, -1);	//On déplace le pion de 1 case
			this->tablePosition[pionActuel->getTableX()][pionActuel->getTableY()] = 1;	//On marque la présence du pion sur la case
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
			if (this->pion2->getTableY() == 0){		//On vérifie qu'après déplacement il n'y a pas de gagnant
				MyView::getInstance()->setStatut("Victoire Noir!", Vec4(0, 0, 0, 1));
				this->gameOver = true;		//On indique la partie comme terminée
			}
			return true;
		}
		MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
		return false;
	}

	// Fonction déplacement des murs //

	//Déplace le centre du mur d'une unité vers les x positifs
	void Model::incMur_x(){
		ref_ptr<Mur> murActuel = murAModifier();	//On récupère le mur à placer du joueur
		if (murActuel->getTableX() != 15){		//Le déplacement du mur est accepté
			murActuel->deplacer(1, 0);		//On déplace le mur
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
		}
		else
			MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
	}
	//Déplace le centre du mur d'une unité vers les x negatifs
	void Model::decMur_x(){
		ref_ptr<Mur> murActuel = murAModifier();	//On récupère le mur à placer du joueur
		if (murActuel->getTableX() != 1){		//Le déplacement du mur est accepté
			murActuel->deplacer(-1, 0);		//On déplace le mur
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
		}
		else
			MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
	}
	//Déplace le centre du mur d'une unité vers les y positifs
	void Model::incMur_y(){
		ref_ptr<Mur> murActuel = murAModifier();	//On récupère le mur à placer du joueur
		if (murActuel->getTableY() != 15){		//Le déplacement du mur est accepté
			murActuel->deplacer(0, 1);		//On déplace le mur
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
		}
		else
			MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
	}
	//Déplace le centre du mur d'une unité vers les y negatifs
	void Model::decMur_y(){
		ref_ptr<Mur> murActuel = murAModifier();	//On récupère le mur à placer du joueur
		if (murActuel->getTableY() != 1){		//Le déplacement du mur est accepté
			murActuel->deplacer(0, -1);		//On déplace le mur
			MyView::getInstance()->setStatut("Mouvement accepté", Vec4(0, 1, 0, 1));
		}
		else
			MyView::getInstance()->setStatut("Mouvement invalide", Vec4(1, 0, 0, 1));
	}


	//Entrer en mode modification des murs
	void Model::enterMurMvt(){
		ref_ptr<Mur> murActuel;
		if (tour){	//On récupère le mur à placer du joueur dont c'est le tour
			for (int i = 0; i < 10; i++){
				if (!murJoueur1[i]->getPlacer()){
					murActuel = murJoueur1[i];
					break;
				}
			}
		}
		else{
			for (int i = 0; i < 10; i++){
				if (!murJoueur2[i]->getPlacer()){
					murActuel = murJoueur2[i];
					break;
				}
			}
		}
		if (murActuel != NULL){		//Si on a trouvé un mur à placer
			this->murMvt = true;	//Mode déplacement des murs à true
			murActuel->setGrapheX(3);	//On change les coordonées du murs dans la caméra
			murActuel->setGrapheY(3);
			murActuel->setTableX(1);	//et dans la table
			murActuel->setTableY(1);
		}
		else						//Si plus de murs à placer
			MyView::getInstance()->setStatut("Plus de mur disponible", Vec4(1, 0, 0, 1));
	}
	//Sortie du mode modification des murs
	void Model::outMurMvt(){
		this->murMvt = false;	//Mode déplacement des murs à false
		if (tour){		//Récupération du mur et on le repositionne à sa place hors du plateau
			for (int i = 0; i < 10; i++){
				if (!murJoueur1[i]->getPlacer()){
					if (murJoueur1[i]->getHorizontal())	//Si le mur est a l'horiontal on effectue une rotation
						murJoueur1[i]->rotation();
					murJoueur1[i]->setGrapheX(i + 2);
					murJoueur1[i]->setGrapheY(1);
					murJoueur1[i]->setTableX(i);
					murJoueur1[i]->setTableY(0);
				}
			}
		}
		else{
			for (int i = 0; i < 10; i++){
				if (!murJoueur2[i]->getPlacer()){
					if (murJoueur2[i]->getHorizontal())	//Si le mur est a l'horiontal on effectue une rotation
						murJoueur2[i]->rotation();
					murJoueur2[i]->setGrapheX(i + 2);
					murJoueur2[i]->setGrapheY(12);
					murJoueur2[i]->setTableX(i);
					murJoueur2[i]->setTableY(16);
				}
			}
		}
	}
	//Passe au tour de jeu suivant
	void Model::tourSuivant(){
		if (this->getTour()){	//Tour de jeu de joueur1
			this->tour = false;
			MyView::getInstance()->setJoueurTexte("Noir", Vec4(0, 0, 0, 1));
		}
		else{					//Tour de jeu de joueur2
			this->tour = true;
			MyView::getInstance()->setJoueurTexte("Blanc", Vec4(1, 1, 1, 1));
		}
		if (this->murMvt)	//Sortie automatique du mode de modification des murs
			this->murMvt = false;
	}
	//Ajouter un mur sur le plateau
	bool Model::ajouterMur(){
		ref_ptr<Mur> murActuel = murAModifier();		//On recupère le mur à ajouter
		if (this->tablePosition[murActuel->getTableX()][murActuel->getTableY()] == 3){	//On vérifie que le mur puisse être ajouté
			MyView::getInstance()->setStatut("Placement du mur impossible", Vec4(1, 0, 0, 1));
			return false;
		}
		if (murActuel->getHorizontal()){		//Si il est horizontal on vérifie les extrémitées gauches et droites
			if (this->tablePosition[murActuel->getTableX() - 1][murActuel->getTableY()] == 3 || this->tablePosition[murActuel->getTableX() + 1][murActuel->getTableY()] == 3){
				MyView::getInstance()->setStatut("Placement du mur impossible", Vec4(1, 0, 0, 1));
				return false;
			}
		}
		else{		//sinon haut et bas
			if (this->tablePosition[murActuel->getTableX()][murActuel->getTableY() - 1] == 3 || this->tablePosition[murActuel->getTableX()][murActuel->getTableY() + 1] == 3){
				MyView::getInstance()->setStatut("Placement du mur impossible", Vec4(1, 0, 0, 1));
				return false;
			}
		}
		if (!peutPlacerMur(pionAModifier()->getTableX(), pionAModifier()->getTableY(),
			murActuel->getTableX(), murActuel->getTableY(), this->getTour())) {
			MyView::getInstance()->setStatut("IA : Nope", Vec4(1, 0, 0, 1));
			return false;
		}
		murActuel->placerMur();		//On indique le mur comme placé
		if (murActuel->getHorizontal()){		//On ajoute les position du mur dans le tableau
			this->tablePosition[murActuel->getTableX()][murActuel->getTableY()] = 3;
			this->tablePosition[murActuel->getTableX() - 1][murActuel->getTableY()] = 3;
			this->tablePosition[murActuel->getTableX() + 1][murActuel->getTableY()] = 3;
		}
		else{
			this->tablePosition[murActuel->getTableX()][murActuel->getTableY()] = 3;
			this->tablePosition[murActuel->getTableX()][murActuel->getTableY() - 1] = 3;
			this->tablePosition[murActuel->getTableX()][murActuel->getTableY() + 1] = 3;
		}
		this->murMvt = false;		//On sort du mode modifactaion mur
		MyView::getInstance()->setStatut("Mur placé", Vec4(0, 1, 0, 1));
		return true;
	}

	//Retourne le mur à placer sur le plateau de jeu
	ref_ptr<Mur> Model::murAModifier(){
		if (tour){		//Si tour du joueur1
			for (int i = 0; i < 10; i++){
				if (!murJoueur1[i]->getPlacer())		//pour chaque mur du joueur on vérifie s'il est placé
					return murJoueur1[i];			//On retourne le premier mur non-placé trouvé
			}
			return NULL;
		}
		else{
			for (int i = 0; i < 10; i++){
				if (!murJoueur2[i]->getPlacer())		//pour chaque mur du joueur on vérifie s'il est placé
					return murJoueur2[i];			//On retourne le premier mur non-placé trouvé
			}
			return NULL;
		}
	}
	//Retourne le pion à modifier en fonction du tour de jeu
	ref_ptr<Pion> Model::pionAModifier(){
		if (this->getTour())	//Tour de jeu de joueur1
			return this->pion1;
		return this->pion2;
	}
	//Effectuer une rottation sur le mur
	void Model::rotation(){
		ref_ptr<Mur> murActuel = murAModifier();
		murActuel->rotation();
	}
	//Recommencer la partie
	void Model::redemarrer(){
		this->instance = new Model();
		MyView::getInstance()->setStatut("La partie recommence", Vec4(1, 1, 1, 1));
	}

	void Model::deplacerMur(float x, float y){ //Deplace le mur à la position la plus proche

		//std::list<Vec3> possiblePositions;
		ref_ptr<Mur> murActuel = murAModifier();


		Vec3 mousePosition = Vec3(((x - 3) * 2) + 1, ((y - 3) * 2) + 1, 0);

		Vec3 closestPoint = Vec3(1, 1, 0);
		Vec3 vecDistance = mousePosition - closestPoint;
		float closestDistance = vecDistance.length();


		for (int i = 1; i <= 15; i = i + 2) {
			for (int j = 1; j <= 15; j = j + 2) {
				Vec3 currentPoint = Vec3(i, j, 0);
				Vec3 vecNewDistance = mousePosition - currentPoint;
				float newDistance = vecNewDistance.length();
				if (newDistance < closestDistance) {
					closestDistance = newDistance;
					closestPoint = currentPoint;
				}
			}
		}
		murActuel->setTableXY(closestPoint.x(), closestPoint.y());
	}

	bool Model::sauvegarderPlateauJeu(string fileName){
		filebuf fb;
		fb.open(fileName, ios::out);
		ostream os(&fb);
		if (!os)return false;
		os << *this;
		fb.close();
		return true;
	}

	bool Model::chargerPlateauJeu(string fileName){
		filebuf fb;
		fb.open(fileName, ios::in);
		istream is(&fb);
		if (!is) return false;
		is >> *this;
		fb.close();
		return true;
	}

	ostream & operator << (ostream& fichierOut, const Model& model){
		int tour = model.getTour() ? 1 : 0;
		//0 pour le pion1(blanc), 1 pour le pion2 (noir)
		fichierOut << tour << endl;
		//ecriture coord du pion 1
		fichierOut << model.getPion1()->getGrapheX() << endl;
		fichierOut << model.getPion1()->getGrapheY() << endl;
		//ecriture de la position tableau du pion 2
		fichierOut << model.getPion1()->getTableX() << endl;
		fichierOut << model.getPion1()->getTableY() << endl;
		//ecriture coord du pion 2
		fichierOut << model.getPion2()->getGrapheX() << endl;
		fichierOut << model.getPion2()->getGrapheY() << endl;
		//ecriture de la position tableau du pion 2
		fichierOut << model.getPion2()->getTableX() << endl;
		fichierOut << model.getPion2()->getTableY() << endl;
		for (int i = 0; i < 10; i++) {
			//ecriture coord d'un mur du pion 2
			fichierOut << model.getMurJoueur1(i)->getGrapheX() << endl;
			fichierOut << model.getMurJoueur1(i)->getGrapheY() << endl;
			//ecriture de la position tableau d'un mur du pion 1
			fichierOut << model.getMurJoueur1(i)->getTableX() << endl;
			fichierOut << model.getMurJoueur1(i)->getTableY() << endl;
			//sauvegarde de si le mur est placé ou pas
			fichierOut << model.getMurJoueur1(i)->getPlacer() << endl;
			//sauvegarde de l'orientation du mur
			fichierOut << model.getMurJoueur1(i)->getHorizontal() << endl;
		}
		for (int i = 0; i < 10; i++) {
			//ecriture coord d'un mur du pion 2
			fichierOut << model.getMurJoueur2(i)->getGrapheX() << endl;
			fichierOut << model.getMurJoueur2(i)->getGrapheY() << endl;
			//ecriture de la position tableau d'un mur du pion 2
			fichierOut << model.getMurJoueur2(i)->getTableX() << endl;
			fichierOut << model.getMurJoueur2(i)->getTableY() << endl;
			//sauvegarde de si le mur est placé ou pas
			fichierOut << model.getMurJoueur2(i)->getPlacer() << endl;
			//sauvegarde de l'orientation du mur
			fichierOut << model.getMurJoueur2(i)->getHorizontal() << endl;
		}
		return fichierOut;
	}
	istream & operator >> (istream& fichierIn, const Model& model){
		int tour;
		//coord pion1
		float pion1GrapheX;
		float pion1GrapheY;
		float pion1TableauX;
		float pion1TableauY;
		//coord pion2
		float pion2GrapheX;
		float pion2GrapheY;
		float pion2TableauX;
		float pion2TableauY;
		//coord mur
		float murGrapheX;
		float murGrapheY;
		float murTableauX;
		float murTableauY;

		bool placee;
		bool horizontal;

		fichierIn >> tour >> pion1GrapheX >> pion1GrapheY >> pion1TableauX >> pion1TableauY >> pion2GrapheX >> pion2GrapheY >> pion2TableauX >> pion2TableauY;

		ref_ptr<Pion> pion1 = new Pion(pion1GrapheX, pion1GrapheY, pion1TableauX, pion1TableauY);
		ref_ptr<Pion> pion2 = new Pion(pion2GrapheX, pion2GrapheY, pion2TableauX, pion2TableauY);

		ref_ptr<Mur> tableauMurJoueur1[10];
		for (int i = 0; i < 10; i++){
			fichierIn >> murGrapheX >> murGrapheY >> murTableauX >> murTableauY >> placee >> horizontal;
			ref_ptr<Mur> murJoueur1 = new Mur(murGrapheX, murGrapheY, murTableauX, murTableauY, placee, horizontal);
			tableauMurJoueur1[i] = murJoueur1;
		}

		ref_ptr<Mur> tableauMurJoueur2[10];
		for (int i = 0; i < 10; i++){
			fichierIn >> murGrapheX >> murGrapheY >> murTableauX >> murTableauY >> placee >> horizontal;
			ref_ptr<Mur> murJoueur2 = new Mur(murGrapheX, murGrapheY, murTableauX, murTableauY, placee, horizontal);
			tableauMurJoueur2[i] = murJoueur2;
		}

		Model::getInstance()->setPlateau(tour, pion1, pion2, tableauMurJoueur1, tableauMurJoueur2);
		return fichierIn;
	}

	void Model::setPlateau(int tour, ref_ptr<Pion> p1, ref_ptr<Pion> p2, ref_ptr<Mur> murJoueur1[], ref_ptr<Mur> murJoueur2[]) {
		this->instance = new Model();
		tour == 0 ? this->instance->setTour(false) : this->instance->setTour(true);
		this->instance->setPion1(p1);
		this->instance->setPion2(p2);
		for (int i = 0; i < 10; i++){
			this->instance->setMurJoueur1(i, murJoueur1[i]);
			this->instance->setMurJoueur2(i, murJoueur2[i]);
		}
	}

	/*
	Simule le plateau avec le nouveau mur placé pour vérifier s'il peut être placé.
	Si origin, chemin possible vers x[0] sinon chemin possible vers
	x[taille-1] */
	bool Model::peutPlacerMur(int pionX, int pionY, int murX, int murY, bool origin) {
		if (taillePlateau % 2 != 1) {
			throw new invalid_argument("La taille doit être impaire");
		}
		array<int, 2> coord = { pionX, pionY };
		stack<array<int, 2>> pile;
		pile.push(coord);
		while (!pile.empty()) {
			coord = pile.top();
			pile.pop();
			if (origin) {
				if (coord.at(0) == 0)
					return true;
			}
			else {
				if (coord.at(0) == taillePlateau - 1)
					return true;
			}
			vector<array<int, 2>> succs = getSuccessors(coord, murX, murY);
			for (int i = 0; i < succs.size(); i++) {
				pile.push(succs.at(i));
			}
		}
		return false;
	}

	vector<array<int, 2>> Model::getSuccessors(const array<int, 2> coord, int murX, int murY) {
		vector<array<int, 2>> ret;
		//s'il y a encore de la place à gauche et pas de mur (x min)
		if (coord.at(0) > 1 && tablePosition[coord.at(0) - 1][coord.at(1)] != MUR) {
			array<int, 2> push = { coord.at(0) - 2, coord.at(1) };
			ret.push_back(push);
		}
		//s'il y a encore de la place à droite et pas de mur (x max)
		if (coord.at(0) < taillePlateau - 2 && tablePosition[coord.at(0) + 1][coord.at(1)] != MUR) {
			array<int, 2> push = { coord.at(0) + 2, coord.at(1) + 1 };
			ret.push_back(push);
		}
		//s'il y a encore de la place en haut et pas de mur (y min)
		if (coord.at(1) > 1 && tablePosition[coord.at(0)][coord.at(1) - 1] != MUR) {
			array<int, 2> push = { coord.at(0), coord.at(1) - 2 };
			ret.push_back(push);
		}
		//s'il y a encore de la place en bas et pas de mur (y max)
		if (coord.at(0) < taillePlateau - 2 && tablePosition[coord.at(0)][coord.at(1) + 1] != MUR) {
			array<int, 2> push = { coord.at(0), coord.at(1) + 2 };
			ret.push_back(push);
		}
		return ret;
	}

}
