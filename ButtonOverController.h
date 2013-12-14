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
		// C'est l'opérateur ci-dessous, hérité de NodeCallback, qui doit être redéfini
		// afin de gérer des évènements liés à un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
	protected:
		//Destructeur
		virtual ~ButtonOverController();
	}; 
}