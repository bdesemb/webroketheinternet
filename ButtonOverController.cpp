#include "ButtonOverController.h"
#include "MyView.h"

using namespace View;

namespace Controller{

	ButtonOverController::ButtonOverController(){

	}

	ButtonOverController::~ButtonOverController(){

	}
	
	void ButtonOverController::operator()(Node* node, NodeVisitor* nv){
		//La classe osgGA::GUIEventAdapter gère tous les types d'évènemens qui peuvent survenir
		std::list<ref_ptr<GUIEventAdapter>> events; // Structure de type liste (librairie standard)
		ref_ptr<EventVisitor> ev = dynamic_cast<EventVisitor*>(nv); // Particularise le "visiteur" de noeuds
		if(ev) events = ev->getEvents(); // Récupère les "évènements" dans la liste
		ref_ptr<GUIEventAdapter> ea = events.back(); // Récupère le dernier élément de la liste
		events.pop_back(); // Supprime l'élément récupéré de la liste
		switch(ea->getEventType()){
		case GUIEventAdapter::MOVE : 
			// Intersecteur à partir du point de l'écran (en pixels) de la position de la souris
			ref_ptr<LineSegmentIntersector> intersector = new LineSegmentIntersector(Intersector::WINDOW,ea->getX(),ea->getY());
			// Visite des noeuds spécifiés pour déterminer si des Drawables entrent en intersection
			// avec la "ligne de mire" du click de la souris
			IntersectionVisitor iv(intersector.get());
			// chaque noeud visité sera traité pour la sélection via un click de la souris
			node->accept(iv);
			// si au moins un Drawable est sélectionné
			bool bouton_trouve = false; //defini si on a trouve un bouton en dessous de la souris ou non (intersection dans la boucle for)
			if(intersector->containsIntersections()){
				// on récupère le plus proche (?) et ses coordonnées dans l'univers de dessin
				LineSegmentIntersector::Intersection result = intersector->getFirstIntersection();
				osg::NodePath &nodes = result.nodePath; //On recupert l'ensemble des nodes de l'intersection
				//On itere sur les nodes de l'intersection, chaque node importante à un nom pour les différenciées
			   for (int i = nodes.size() - 1; i >= 0; i--){
				   ref_ptr<Bouton> boutonNode = dynamic_cast<Bouton*>(nodes[i]);
				   if(boutonNode){ //Si c'est pas null, alors on a trouvé une node de type bouton
						bouton_trouve = true; //on a trouve un bouton
						MyView::getInstance()->setSurvolBouton(boutonNode); //on met ce bouton en mode survol
				   }
			   }
			}
			if(!bouton_trouve){ //on a pas trouve de bouton en intersection, on s'assure de mettre tous les boutons en position non-survolé
			   MyView::getInstance()->setSurvolBouton(NULL); //on met aucun bouton en mode survol
			}
			break;
		}
	}
}