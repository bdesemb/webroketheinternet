#include "Bouton.h"

using namespace osg;

namespace View{

	Bouton::Bouton(std::string nom, Vec3 translate):MatrixTransform(){

		switchNode = new Switch;
		switchNode->setName("switch_" + nom);

		ref_ptr<ShapeDrawable> buttonShape = new ShapeDrawable;
		buttonShape->setShape(new Box(translate,1,1,0.3));

		ref_ptr<Geode> geode = new Geode;
		geode->addDrawable(buttonShape.get());
		geode->setName(nom);
		appliquerTexture(geode.get());

		ref_ptr<Geode> geodeSurvol = new Geode;
		geodeSurvol->addDrawable(buttonShape.get());
		geodeSurvol->setName(nom+"_SURVOL");
		appliquerTexture(geodeSurvol.get());

		switchNode->addChild(geode, true);
		switchNode->addChild(geodeSurvol, false);

		this->addChild(switchNode.get());
	}

	Bouton::~Bouton(){

	}

	void Bouton::appliquerTexture(Geode* g){
		ref_ptr<Geode> geode = g;
		//On charge le fichier image de la texture
		ref_ptr<Image> image = osgDB::readImageFile("ressources/" + geode->getName() + ".png");
		if (!image) {
			std::cout << "Couldn't load image." << std::endl;
			return;
		}

		//On cree la texture
		ref_ptr<Texture2D> texture = new Texture2D;
		texture->setImage(image);

		ref_ptr<StateSet> stateset;
		stateset = geode->getOrCreateStateSet();
		stateset->setTextureAttributeAndModes(0, texture.get());
		stateset->setMode(GL_LIGHTING,StateAttribute::ON);
	}

	void Bouton::setSurvol(bool survol){
		switchNode->setValue(0, !survol);
		switchNode->setValue(1, survol);
	}

}