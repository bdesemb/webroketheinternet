// EventController.cpp
#include <osg/MatrixTransform>
#include "EventController.h"
#include "MyView.h"

#include <osgUtil/LineSegmentIntersector>

using namespace model;
using namespace View;

namespace Controller{

	//Constructeur vide
	EventController::EventController(){
	}

	void EventController::operator()(Node* node, NodeVisitor* nv)
	{
		Model* model = Model::getInstance(); //Récupère le modèle
		//La classe osgGA::GUIEventAdapter gère tous les types d'évènemens  qui peuvent survenir
		std::list<ref_ptr<GUIEventAdapter>> events; //Structure de type liste
		EventVisitor* ev = dynamic_cast<EventVisitor*>(nv); //Particularise le "visiteur" de noeuds
		if(ev) events = ev->getEvents(); //Récupère les "évènements" dans la liste
		ref_ptr<GUIEventAdapter> ea = events.back(); //Récupère le dernier élément de la liste
		events.pop_back(); //Supprime l'élément récupéré de la liste

		//Détermine le type d'évènement
		switch(ea->getEventType()){
			case GUIEventAdapter::MOVE:
                if(model->getMurMvt()){
                    Vec3 positionSourisSurPlateau;
                    if(sourisSurvolPlateau(node, ea->getX(), ea->getY(), positionSourisSurPlateau))
                        model->deplacerMur(positionSourisSurPlateau.x(), positionSourisSurPlateau.y());
                }
                //model->deplacerMur(intersector.);
                break;
            case GUIEventAdapter::DOUBLECLICK:
                if(sourisSurvolPlateau(node, ea->getX(), ea->getY()) && ea->getButton() == GUIEventAdapter::LEFT_MOUSE_BUTTON){
                    if(model->getMurMvt() && model->ajouterMur())
                        model->tourSuivant();
                }
                break;
            case GUIEventAdapter::RELEASE:
                if(sourisSurvolPlateau(node, ea->getX(), ea->getY()) && ea->getButton() == GUIEventAdapter::RIGHT_MOUSE_BUTTON){
                    if(model->getMurMvt())
                        model->rotation();
                }
                break;
			//Utilisation de la molette de la souris
			case GUIEventAdapter::SCROLL:
				switch (ea->getScrollingMotion()) {
					case GUIEventAdapter::SCROLL_DOWN: //Si c'est un scroll vers le bas, on va dézoomer
						zoomCamera(0,0,0.5);
						break;
					case GUIEventAdapter::SCROLL_UP: //Si c'est un scoll vers le haut, on va zoomer
						zoomCamera(0,0,-0.5);
						break;
				}
				break;
			//Enfoncement d'une touche
			case GUIEventAdapter::KEYDOWN:
				if(model->getGameOver() == false){	//S'assurer que la partie n'est pas terminée
					switch(ea->getKey()){
						//Flêche vers la droite
						case GUIEventAdapter::KEY_Right :
							if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
								model->incMur_x();
							else{					//Sinon on modifie le pion
								if(model->incPion_x())
									model->tourSuivant();
							}
							break;
							//Flêche vers la gauche
							case GUIEventAdapter::KEY_Left :
								if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
									model->decMur_x();
							else{						//Sinon on modifie le pion
								if(model->decPion_x())
									model->tourSuivant();
							}
							break;
							//Flêche vers le haut
							case GUIEventAdapter::KEY_Up :
								if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
									model->incMur_y();
								else{					//Sinon on modifie le pion
								if(model->incPion_y())
									model->tourSuivant();
							}
							break;
							//Flêche vers le bas
							case GUIEventAdapter::KEY_Down :
								if(model->getMurMvt())	//Si on se trouve dans le mode modifier mur
									model->decMur_y();
								else{					//Sinon on modifie le pio
									if(model->decPion_y())
										model->tourSuivant();
								}
								break;
							//Touche M
							case GUIEventAdapter::KEY_M :
								if(!model->getMurMvt()){	//Si on ne se trouve pas en mode mofication des murs
									model->enterMurMvt();	//On entre en mode modif murs
								}
								else						//Sinon on sort du mode modification des murs
									model->outMurMvt();
								break;
							//Touche Enter
							case GUIEventAdapter::KEY_Return :
								if(model->getMurMvt()){		//Si on se trouve dans le mode modifier mur
									if(model->ajouterMur())	//Alors on place le mur sur le plateau
										model->tourSuivant();
								}
								break;
							//Touche R
							case GUIEventAdapter::KEY_R :
								if(model->getMurMvt())		//Si on se trouve dans le mode modifier mur
									model->rotation();		//On effectue une rotation sur le mur à placer
								break;
							default:
								break;
						}
					}
				switch(ea->getKey()){	//A parcourir dans tous les cas, même si la partie est terminée
					//Touche P
					case GUIEventAdapter::KEY_P :
						model->redemarrer();	//On démarre une nouvelle partie
						break;
					default:
						break;
				}
				default:
					break;
			}
		}
	bool EventController::sourisSurvolPlateau(Node* node, float mouseX, float mouseY, Vec3 &positionSourisSurPlateau){
        ref_ptr<osgUtil::LineSegmentIntersector> intersector = 
            new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW,mouseX,mouseY);
        osgUtil::IntersectionVisitor iv(intersector.get());
        node->accept(iv);
		if(intersector->containsIntersections()){
			osgUtil::LineSegmentIntersector::Intersection result = intersector->getFirstIntersection();
			positionSourisSurPlateau =  result.getWorldIntersectPoint();
			return true;            
		}
        return false;
    }

	void EventController::zoomCamera(float x, float y, float z){
		Vec3 eye = MyView::getInstance()->getCameraPlateauEye();
		Vec3 center = MyView::getInstance()->getCameraPlateauCenter();
		Vec3 up = MyView::getInstance()->getCameraPlateauUp();
		if(z > 0 && eye.z() >= 25) {			//Test si la camera est pas deja à distance maximale
			MyView::getInstance()->setStatut("Impossible de dézoomer plus!", Vec4(1,0,0,1));
			return;
		} else if (z < 0  && eye.z() <= 10) {	//Test si la camera est pas deja à distance minimale
			MyView::getInstance()->setStatut("Impossible de zoomer plus!", Vec4(1,0,0,1));
			return;
		}
		//Il y a une action, on remet le statut de texte à vide
		MyView::getInstance()->setStatut("", Vec4(1,0.2,0.2,1));
		//On cree un nouveau vec qui est le deplacement de la camera
		Vec3 deplacement = Vec3(x,y,z);
		//On additionne l'ancien oeil au vecteur de deplacement
		eye += deplacement;
		//On met à jour la camera
		MyView::getInstance()->getCameraPlateau()->setViewMatrixAsLookAt(eye, center, up);
		//On met à jour la camera de la classe MyView
		MyView::getInstance()->setCameraPlateauEye(eye);
	}
}
