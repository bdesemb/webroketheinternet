// PositionUpdater.cpp
#include "Model.h"
#include "MyView.h"
#include "PositionUpdater.h"
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/ShapeDrawable>
//#include <iostream>

using namespace osg;
using namespace std;
using namespace model;
using namespace View;

namespace Controller{
	void PositionUpdater::operator()(Node* node, NodeVisitor* nv){
		Model* model = Model::getInstance(); // Récupère le modèle
		MatrixTransform* mt = static_cast<MatrixTransform*>(node); // Particularise le Node à traiter

		if(model->getTour()==true){
			MyView::getInstance()->setJoueurTexte("Blanc", Vec4(1,1,1,1));
		}else{
			MyView::getInstance()->setJoueurTexte("Noir", Vec4(0,0,0,1));
		}
		
		int i = 0;
		for(i; i<10; i++){	//Pour tous les murs du joueur1
			char nom[20] = "";
			sprintf(nom,"murJoueur1%d",i);
			if(node->getName() == nom){		//Si la node actuelle est un mur du joueur1
				mt->setMatrix(Matrix::identity()); // réinitialisation
				if(model->getMurJoueur1(i)->getHorizontal())	//Si le mur est a l'horizontal, effectuer la rotation
					mt->postMult(Matrix::rotate(1.57f,Z_AXIS));
				mt->postMult(Matrix::translate(model->getMurJoueur1(i)->getGrapheX(), model->getMurJoueur1(i)->getGrapheY(), 0)); //On effectue la translation
			}
		}
		for(i = 0; i<10; i++){	//Pour tous les murs du joueur2
			char nom[20] = "";
			sprintf(nom,"murJoueur2%d",i);
			if(node->getName() == nom){		//Si la node actuelle est un mur du joueur2
				mt->setMatrix(Matrix::identity()); // réinitialisation
				if(model->getMurJoueur2(i)->getHorizontal())	//Si le mur est a l'horizontal, effectuer la rotation
					mt->postMult(Matrix::rotate(1.57f,Z_AXIS));
				mt->postMult(Matrix::translate(model->getMurJoueur2(i)->getGrapheX(), model->getMurJoueur2(i)->getGrapheY(), 0)); //On effectue la translation
			}
		}
		if(node->getName() == "pion1"){ //Si la node est le pion1
			mt->setMatrix(Matrix::identity()); // réinitialisation
			mt->setMatrix(Matrix::translate(model->getPion1()->getGrapheX(), model->getPion1()->getGrapheY(), 0)); //On effectue la translation
		}

		if(node->getName() == "pion2"){
			mt->setMatrix(Matrix::identity()); // réinitialisation
			mt->setMatrix(Matrix::translate(model->getPion2()->getGrapheX(), model->getPion2()->getGrapheY(), 0)); //On effectue la translation
		}

		traverse(node,nv); //On passe à la node suivant
	}
}