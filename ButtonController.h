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
	// Classe qui va servir � d�finir un "event callback" li� aux actions de l'utilisateur
	class ButtonController :
		public NodeCallback
	{
	public:
		ButtonController();
		//Manipule les resultat de l'intersection pour voir quel boutton a �t� cliqu�
		virtual void handleResult(Intersection result);
		// C'est l'op�rateur ci-dessous, h�rit� de NodeCallback, qui doit �tre red�fini
		// afin de g�rer des �v�nements li�s � un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
		//~EventController();
	};
}