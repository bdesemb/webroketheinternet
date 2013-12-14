// EventController.h
#pragma once

#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>

#include "Model.h"

using namespace osg;
using namespace osgGA;

// Classe qui va servir à définir un "event callback" lié aux actions de l'utilisateur
namespace Controller{
	class EventController :
		public NodeCallback
	{
	public:
		EventController();
		// C'est l'opérateur ci-dessous, hérité de NodeCallback, qui doit être redéfini
		// afin de gérer des évènements liés à un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
		//~EventController();
	private:
        bool sourisSurvolPlateau(Node* node, float mouseX, float mouseY, Vec3 &positionSourisSurPlateau = Vec3(0,0,0));
		virtual void zoomCamera(float x, float y, float z);
	};
}