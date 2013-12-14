// ButtonController.h
#pragma once

#include <osgUtil/LineSegmentIntersector>
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>

#include <iostream>
#include "Model.h"
#include "ParcourirFichier.h"

using namespace osg;
using namespace osgGA;
using namespace osgUtil;	

//Type Intersection
typedef osgUtil::LineSegmentIntersector::Intersection Intersection;

namespace Controller{
	// Classe qui va servir à définir un "event callback" lié aux actions de l'utilisateur
	class ButtonController :
		public NodeCallback
	{
	public:
		ButtonController();
		//Manipule les resultat de l'intersection pour voir quel boutton a été cliqué
		virtual void handleResult(Intersection result);
		// C'est l'opérateur ci-dessous, hérité de NodeCallback, qui doit être redéfini
		// afin de gérer des évènements liés à un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
		//~EventController();
	};
}