#pragma once

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <osgDB/ReadFile>
#include <osg/Switch>
#include <osg/ShapeDrawable>

namespace View{
	class Bouton : public osg::MatrixTransform{
	private:
		osg::ref_ptr<osg::Switch> switchNode;
		virtual void appliquerTexture(osg::Geode*);
	protected:
		virtual ~Bouton();
	public:
		Bouton(std::string, osg::Vec3);
		virtual void setSurvol(bool);
	};
}