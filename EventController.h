// EventController.h
#pragma once

#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>

#include "Model.h"

using namespace osg;
using namespace osgGA;

// Classe qui va servir � d�finir un "event callback" li� aux actions de l'utilisateur
namespace Controller{
	class EventController :
		public NodeCallback
	{
	public:
		EventController();
		// C'est l'op�rateur ci-dessous, h�rit� de NodeCallback, qui doit �tre red�fini
		// afin de g�rer des �v�nements li�s � un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
		//~EventController();
	private:
        bool sourisSurvolPlateau(Node* node, float mouseX, float mouseY, Vec3 &positionSourisSurPlateau = Vec3(0,0,0));
		virtual void zoomCamera(float x, float y, float z);
	};
}