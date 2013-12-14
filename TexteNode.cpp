#include "TexteNode.h"

using namespace osg;

namespace View{
	TexteNode::TexteNode(std::string texte):Geode(){
		//Définition de la police d'écriture
		ref_ptr<osgText::Font> font = osgText::readFontFile("fonts/arial.ttf"); // True Type Font
		this->texte = new osgText::Text;
		//On applique la polie
		this->texte->setFont(font.get());
		//la taille de caractere
		this->texte->setCharacterSize(0.4);
		//la position du texte
		this->texte->setPosition(Vec3(0,0,0)); 
		//le texte à afficher
		this->texte->setText(texte);
		//Et la couleur
		this->texte->setColor(Vec4(1,1,1,1));
		//On le place dans une geode
		this->addDrawable(this->texte.get());
		ref_ptr<StateSet> stateset = this->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		this->texte->setDataVariance(DYNAMIC);
	}

	TexteNode::~TexteNode(){
		this->texte = NULL;
	}

	void TexteNode::setTexte(std::string texte, Vec4 couleur){
		//On change le texte de la node
		this->texte->setText(texte);
		//Et sa couleur
		this->texte->setColor(couleur);
	}
}
