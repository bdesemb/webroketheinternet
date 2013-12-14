#pragma once
//Classe permettant de creer une geode pour afficher du texte
#include <osg/Geode>
#include <osgText/Text>

namespace View{
	class TexteNode : public osg::Geode{
		private:
			//La node de texte utile si on désire changer le texte
			osg::ref_ptr<osgText::Text> texte;

		protected:
			//Destructeur
			virtual ~TexteNode();

		public: 
			//Constructeur qui prend en parametre le texte de depard de la node
			TexteNode(std::string);
			//Permet de changer le texte affiché et la couleur du texte
			virtual void setTexte(std::string, osg::Vec4);

	};
}