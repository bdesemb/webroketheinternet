#pragma once

#include "Bouton.h"

#include <osgUtil/LineSegmentIntersector>
#include <osgGA/GUIEventAdapter>
#include <osgGA/EventVisitor>

using namespace osg;
using namespace osgGA;
using namespace osgUtil;

//Permet d'utiliser le type Intersection plus facilement
typedef osgUtil::LineSegmentIntersector::Intersection Intersection;

namespace Controller{
	class ButtonOverController : public NodeCallback{

	public:
		//Constructeur
		ButtonOverController();
		// C'est l'op�rateur ci-dessous, h�rit� de NodeCallback, qui doit �tre red�fini
		// afin de g�rer des �v�nements li�s � un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
	protected:
		//Destructeur
		virtual ~ButtonOverController();
	}; 
}