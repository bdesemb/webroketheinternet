// ButtonController.cpp
#include <osg/MatrixTransform>
#include "ButtonController.h"

using namespace model;
using namespace View;

namespace Controller{

	//Constructeur vide
	ButtonController::ButtonController(){

	}

	void ButtonController::operator()(Node* node, NodeVisitor* nv){
		Model* model = Model::getInstance(); //Récupère le modèle
		//La classe osgGA::GUIEventAdapter gère tous les types d'évènemens  qui peuvent survenir
		std::list<ref_ptr<GUIEventAdapter>> events; //Structure de type liste
		EventVisitor* ev = dynamic_cast<EventVisitor*>(nv); //Particularise le "visiteur" de noeuds
		if(ev) events = ev->getEvents(); //Récupère les "évènements" dans la liste
		ref_ptr<GUIEventAdapter> ea = events.back(); //Récupère le dernier élément de la liste
		events.pop_back(); //Supprime l'élément récupéré de la liste
		switch(ea->getEventType()){
			case GUIEventAdapter::PUSH:
				if(ea->getButton()==GUIEventAdapter::LEFT_MOUSE_BUTTON){
					// Intersecteur à partir du point de l'écran (en pixels) au moment du click
					ref_ptr<LineSegmentIntersector> intersector = 
						new LineSegmentIntersector(Intersector::WINDOW,ea->getX(),ea->getY());
					// Visite des noeuds spécifiés pour déterminer si des Drawables entrent en intersection
					// avec la "ligne de mire" du click de la souris
					IntersectionVisitor iv(intersector.get());
					// chaque noeud visité sera traité pour la sélection via un click de la souris
					node->accept(iv);
					// si au moins un Drawable est sélectionné
					if(intersector->containsIntersections()){
						// on récupère le plus proche (?) et ses coordonnées dans l'univers de dessin
						LineSegmentIntersector::Intersection result = intersector->getFirstIntersection();
				
						handleResult(result);
					}
				}

		}
		traverse(node,nv);
	}
	void ButtonController::handleResult(Intersection intersection){
		osg::NodePath &nodes = intersection.nodePath; //On recuperts l'ensemble des nodes de l'intersection
		Model* model = Model::getInstance();
		for (int i = nodes.size() - 1; i >= 0; i--) {
			if(model->getGameOver() == false){	//S'assurer que la partie n'est pas terminée
				if(nodes[i]->getName() == "BOUTON_UP_SURVOL"){
					if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
						model->incMur_y();
					else{					//Sinon on modifie le pion
						if(model->incPion_y())
							model->tourSuivant();
					}
					break;
				}else if(nodes[i]->getName() == "BOUTON_DOWN_SURVOL"){
					if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
						model->decMur_y();
					else{					//Sinon on modifie le pion
						if(model->decPion_y())
							model->tourSuivant();
					}
					break;
				}else if (nodes[i]->getName() == "BOUTON_LEFT_SURVOL"){
					if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
						model->decMur_x();
					else{					//Sinon on modifie le pio
						if(model->decPion_x())
							model->tourSuivant();
					}
					break;
				} else if(nodes[i]->getName() == "BOUTON_RIGHT_SURVOL"){
					if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
						model->incMur_x();
					else{					//Sinon on modifie le pio
						if(model->incPion_x())
							model->tourSuivant();
						}
					break;
				}else if(nodes[i]->getName() == "BOUTON_CHOIX_MUR_SURVOL"){
					if(!model->getMurMvt()){	//Si on ne se trouve pas en mode mofication des murs
						model->enterMurMvt();	//On entre en mode modif murs
					}
					else						//Sinon on sort du mode modification des murs
						model->outMurMvt();
					break;
				}else if(nodes[i]->getName() == "BOUTON_VALIDATION_SURVOL"){
					if(model->getMurMvt()){		//Si on se trouve dans le mode modifier mur
						if(model->ajouterMur())	//Alors on place le mur sur le plateau
							model->tourSuivant();
					}
					break;
				}else if(nodes[i]->getName() == "BOUTON_ROTATION_SURVOL"){
					if(model->getMurMvt())		//Si on se trouve dans le mode modifier mur
						model->rotation();		//On effectue une rotation sur le mur à placer
					break;
				}
			}
			if(nodes[i]->getName() == "BOUTON_NEW_SURVOL"){
				model->redemarrer();	//On démarre une nouvelle partie
				break;
			}else if(nodes[i]->getName() == "BOUTON_SAVE_SURVOL"){
				std::string path = ParcourirFichier::sauver();
				model->sauvegarderPlateauJeu(path);
			}else if(nodes[i]->getName() == "BOUTON_LOAD_SURVOL"){
				std::string path = ParcourirFichier::ouvrir();
				model->chargerPlateauJeu(path);
			}
		}
	}
}