#include "MyView.h"
#include "Model.h"
#include "EventController.h"
#include "PositionUpdater.h"
#include "ButtonController.h"
#include "ButtonOverController.h"

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osgText/Text>
#include <osg/Switch>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

using namespace osg;
using namespace Controller;
using namespace model;

namespace View{
	MyView *MyView::instance = 0;

	//Model* model = Model::getInstance(); // Récupère le modèle

	MyView::MyView(){

		this->myView = new osgViewer::Viewer;
		//On définit sa position et sa taille
		this->myView->setUpViewInWindow(32, 32, WINDOW_WIDTH, WINDOW_HEIGHT);
		//On défini sa position et sa taille
		this->myView->getCamera()->setAllowEventFocus(false);
		//On définit un nom à la fenêtre
		osgViewer::Viewer::Windows windows;
		this->myView->getWindows(windows);
		windows[0]->setWindowName("Quoridor");

		Model* model = Model::getInstance();
		taillePlateau = model->getTaillePlateau();
		largeurPlateau = model->getLargeurPlateau();
		longueurPlateau = model->getLongueurPlateau();

		//Assignation couleur
		couleur_camera_boutons = Vec4(0.141,0.266,0.360,1);
		couleur_camera_messages = Vec4(0.141,0.266,0.360,1);
		couleur_camera_plateau = Vec4(0.501,0.427,0.352,1);
		couleur_sol = Vec4(0.807,0.807,0.807,1);
		couleur_slot = Vec4(0.352,0.368,0.419,1);
		couleur_mur = Vec4(0.533,0.258,0.113,1);
		couleur_pion1 = Vec4(1,1,1,1);
		couleur_pion2  = Vec4(0,0,0,1);

		ref_ptr<Camera> cameraBoutons = creerCameraBoutons();
		ref_ptr<Camera> cameraMessages = creerCameraMessages();

		//On crée un groupe root pour accueillir les cameras
		ref_ptr<Group> groupCamera = new Group;
		//On ajout les cameras au groupe
		groupCamera->addChild(cameraBoutons.get());
		cameraPlateau = creerPlateauDeJeu();
		groupCamera->addChild(cameraPlateau.get());
		groupCamera->addChild(cameraMessages.get());

		myView->setSceneData(groupCamera); 

	}

	//Deconstructeur
	MyView::~MyView(){

	}

	MyView *MyView::getInstance(){
		if (instance == 0)
			instance = new MyView();

		return instance;
	}

	osgViewer::Viewer* MyView::getMyView(){
		return this->myView.get();
	}

	void MyView::setStatut(std::string message, Vec4 couleur){
		this->statutTexte->setTexte(message, couleur);
	}

	void MyView::setJoueurTexte(std::string message, Vec4 couleur){
		this->joueurTexte->setTexte(message, couleur);
	}

	osg::Camera* MyView::creerCameraBoutons(){
		ref_ptr<Camera> camera = new Camera;
		Vec3 eye = Vec3(0,0,1);
		Vec3 center = Vec3(0,0,0);
		Vec3 up = Vec3(0,1,0);
		camera->setViewMatrixAsLookAt(eye,center,up);
		camera->setProjectionMatrixAsOrtho(-7.5f,7.5f,-4,4,0.5,5);
		camera->setViewport(new Viewport(WINDOW_WIDTH/2,WINDOW_HEIGHT/4*3,WINDOW_WIDTH/2,WINDOW_HEIGHT/4)); 
		camera->setReferenceFrame(Camera::ABSOLUTE_RF);
		camera->setClearColor(couleur_camera_boutons);

		camera->addChild(creerLesBoutons());

		camera->addEventCallback(new ButtonController);
		camera->addEventCallback(new ButtonOverController);

		return camera.release();
	}

	osg::Camera* MyView::creerCameraPlateau(){
		// Définition de la caméra plateau de jeu et de ses caractéristiques
		ref_ptr<Camera> camera = new Camera;
		cameraPlateauEye = Vec3((taillePlateau+4.25)/2,4,10);
		cameraPlateauCenter = Vec3((taillePlateau+4.25)/2,(taillePlateau+4)/2,0);
		cameraPlateauUp = Vec3(0,1,0);
		
		camera->setViewMatrixAsLookAt(cameraPlateauEye,cameraPlateauCenter,cameraPlateauUp);
		camera->setProjectionMatrixAsFrustum(-(taillePlateau+4)/2,(taillePlateau+4)/2,-(taillePlateau+4)/2,(taillePlateau+4)/2,9,10);
		camera->setViewport(new Viewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT/4*3));
		camera->setReferenceFrame(Camera::ABSOLUTE_RF);

		camera->setClearColor(couleur_camera_plateau);

		return camera.release();
	}

	osg::Camera* MyView::creerPlateauDeJeu(){

		StateSet* stateset;
		ref_ptr<Camera> camera = creerCameraPlateau();

		//création du sol
		ref_ptr<ShapeDrawable> solDrawable = new ShapeDrawable;
		solDrawable->setShape(new Box(Vec3(0,0,-0.1),11,13,0.1));
		solDrawable->setColor(couleur_sol);
		ref_ptr<Geode> solGeode = new Geode;
		stateset = solGeode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		solGeode->addDrawable(solDrawable.get());
		ref_ptr<MatrixTransform> solTrans = new MatrixTransform;
		solTrans->setMatrix(Matrix::translate(6.5f,6.5f,0));
		solTrans->addChild(solGeode.get());
		//Création geode case
		ref_ptr<Geode> slotGeode = new Geode;
		ref_ptr<ShapeDrawable> slot = new ShapeDrawable;
		slot->setShape(new Box(Vec3(0,0,0),0.7,0.7,0.1));
		slot->setColor(couleur_slot);
		stateset = slotGeode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		slotGeode->addDrawable(slot.get());
		//Création geode mur
		ref_ptr<Geode> murGeode = new Geode;
		ref_ptr<ShapeDrawable> mur = new ShapeDrawable;
		mur->setShape(new Box(Vec3(0,0,0),0.2,2,0.4));
		mur->setColor(couleur_mur);
		stateset = murGeode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		murGeode->addDrawable(mur.get());
		//Création geode pion1
		ref_ptr<Geode> pion1Geode = new Geode;
		ref_ptr<ShapeDrawable> pion1 = new ShapeDrawable;
		pion1->setShape(new Cylinder(Vec3(0,0,0),0.3,0.2));
		pion1->setColor(Vec4(1,1,1,1));
		stateset = pion1Geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		pion1Geode->addDrawable(pion1.get());
		//Création geode pion2
		ref_ptr<Geode> pion2Geode = new Geode;
		ref_ptr<ShapeDrawable> pion2 = new ShapeDrawable;
		pion2->setShape(new Cylinder(Vec3(0,0,0),0.3,0.2));
		pion2->setColor(Vec4(0,0,0,1));
		stateset = pion2Geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING,StateAttribute::OFF);
		pion2Geode->addDrawable(pion2.get());

		ref_ptr<MatrixTransform> newTransfo;
		ref_ptr<MatrixTransform> translation = new MatrixTransform;
		ref_ptr<Group> groupElement = new Group;
		//translation->setMatrix(Matrix::identity());
		
		//Dessin du plateau de jeu
		float posX = 2.5;
		float posY = 2.5;
		float i = posX;
		float j = posY;
		for(i; i<posX + taillePlateau; i++){
			j = posY;
			for(j; j<posY +taillePlateau; j++){
				newTransfo = new MatrixTransform;
				newTransfo->addChild(slotGeode.get());
				newTransfo->setMatrix(Matrix::translate(i,j,0));
				groupElement->addChild(newTransfo.get());
			}
		}
		//Dessin des murs du joueur1
		posX = 2;
		for(i = posX; i<posX + 10; i++){
			newTransfo = new MatrixTransform;
			newTransfo->addChild(murGeode.get());
			char nom[20] ="";
			int pos = i-posX;
			sprintf(nom,"murJoueur1%d",pos);
			newTransfo->setName(nom);
			newTransfo->setUpdateCallback(new PositionUpdater());
			groupElement->addChild(newTransfo.get());
		}
		//Dessin des murs du joueur2
		posX = 2;
		for(i = posX; i<posX + 10; i++){
			newTransfo = new MatrixTransform;
			newTransfo->addChild(murGeode.get());
			char nom[20] ="";
			int pos = i-posX;
			sprintf(nom,"murJoueur2%d",pos);
			newTransfo->setName(nom);
			newTransfo->setUpdateCallback(new PositionUpdater());
			groupElement->addChild(newTransfo.get());
		}
		//Dessin du pion1
		newTransfo = new MatrixTransform;
		newTransfo->addChild(pion1Geode.get());
		groupElement->addChild(newTransfo.get());
		newTransfo->setName("pion1");
		newTransfo->setUpdateCallback(new PositionUpdater());
		//Dessin du pion2
		newTransfo = new MatrixTransform;
		newTransfo->addChild(pion2Geode.get());
		groupElement->addChild(newTransfo.get());
		newTransfo->setName("pion2");
		newTransfo->setUpdateCallback(new PositionUpdater());
		//Dessin du sol
		groupElement->addChild(solTrans.get());
		//Ajout des events
		camera->setEventCallback(new EventController);
		//Ajout du tout dans caméra1
		camera->addChild(groupElement.get());

		// Définit deux lumières et associe chacune d'elle à une source d'éclairage
		ref_ptr<Light> light0 = new Light;
		light0->setLightNum(0);
		light0->setPosition(Vec4(10,10,1,1)); // Source positionelle
		light0->setAmbient(Vec4(1,0,0,1));

		ref_ptr<LightSource> source1 = new LightSource;
		source1->setLight(light0);
		source1->setReferenceFrame(LightSource::ABSOLUTE_RF); // la position ne light0 ne subit pas les transformations géométriques de noeuds parents

		ref_ptr<Light> light1 = new Light;
		light1->setLightNum(1);
		light1->setPosition(Vec4(5,5,1,0)); // Source Directionnelle
		light1->setAmbient(Vec4(0,1,0,1));
		light1->setDirection(Vec3(1,1,0));

		ref_ptr<LightSource> source2 = new LightSource;//
		source2->setLight(light1);
		source2->setReferenceFrame(LightSource::ABSOLUTE_RF); // la position ne light0 ne subit pas les transformations géométriques de noeuds parents

	
		camera->addChild(source1);
		camera->addChild(source2);

		camera->getOrCreateStateSet()->setMode(GL_LIGHT0,StateAttribute::ON); // Active la lumière light0
		camera->getOrCreateStateSet()->setMode(GL_LIGHT1,StateAttribute::ON); // Active la lumière light1

		return camera.release();
	}

	osg::Camera* MyView::creerCameraMessages(){
		ref_ptr<Camera> camera = new Camera;
		Vec3 eye = Vec3(0,0,1);
		Vec3 center = Vec3(0,0,0);
		Vec3 up = Vec3(0,1,0);
		camera->setViewMatrixAsLookAt(eye,center,up);
		camera->setProjectionMatrixAsOrtho(-3,3,-1,1,0.5f,5);
		camera->setViewport(new Viewport(0,WINDOW_HEIGHT/4*3,WINDOW_WIDTH/2,WINDOW_HEIGHT/4)); 
		camera->setReferenceFrame(Camera::ABSOLUTE_RF);
		camera->setClearColor(couleur_camera_messages);

		//On crée un translation et on place le texte "Controles" dedans
		ref_ptr<MatrixTransform> titreTextTranslate = new MatrixTransform;
		titreTextTranslate->setMatrix(Matrix::translate(-1,0.625f,0));
		titreTextTranslate->addChild(new TexteNode("Messages"));
		ref_ptr<MatrixTransform> titreTextScale = new MatrixTransform;
		titreTextScale->setMatrix(Matrix::scale(1.5f,1,1));
		titreTextScale->addChild(titreTextTranslate.get());

		//Gestion message "tour de"
		ref_ptr<MatrixTransform> tourTextTranslate = new MatrixTransform;
		tourTextTranslate->setMatrix(Matrix::translate(-2.75f,0,0));
		tourTextTranslate->addChild(new TexteNode("Au tour de : "));
		ref_ptr<MatrixTransform> tourTextScale = new MatrixTransform;
		tourTextScale->setMatrix(Matrix::scale(1,0.75f,1));
		tourTextScale->addChild(tourTextTranslate.get());

		//Gestion de l'emplacement qui accueillera le joueur a qui c'est le tour
		ref_ptr<MatrixTransform> tourJoueur = new MatrixTransform;
		tourJoueur->setMatrix(Matrix::translate(-0.5f,0,0));
		this->joueurTexte = new TexteNode("");
		tourJoueur->setName("tour");
		tourJoueur->addChild(joueurTexte.get());

		//Gestion message "Message courant"
		ref_ptr<MatrixTransform> messageTextTranslate = new MatrixTransform;
		messageTextTranslate->setMatrix(Matrix::translate(-2.75f,-0.5f,0));
		messageTextTranslate->addChild(new TexteNode("Message : "));
		ref_ptr<MatrixTransform> messageTextScale = new MatrixTransform;
		messageTextScale->setMatrix(Matrix::scale(1,0.75f,1));
		messageTextScale->addChild(messageTextTranslate.get());

		//Gestion message courant
		ref_ptr<MatrixTransform> messageCourant = new MatrixTransform;
		messageCourant->setMatrix(Matrix::translate(-2.50f,-0.75,0));
		this->statutTexte = new TexteNode("");
		messageCourant->addChild(statutTexte.get());

		camera->addChild(titreTextScale.get());
		camera->addChild(tourTextScale.get());
		camera->addChild(tourJoueur.get());
		camera->addChild(messageTextScale.get());
		camera->addChild(messageCourant.get());

		return camera.release();
	}

	osg::Node* MyView::creerLesBoutons(){

		//Translation qui accueillera tous les elements de cette partie
		ref_ptr<MatrixTransform> boutons = new MatrixTransform;

		//Creation de l'echelle des boutons
		ref_ptr<MatrixTransform> boutonScale = new MatrixTransform;
		boutonScale->setMatrix(Matrix::scale(1,1,1));
		boutons->addChild(boutonScale.get());

		ref_ptr<Bouton> boutonUP = new Bouton("BOUTON_UP", Vec3(0,1.1f,0));
		ref_ptr<Bouton> boutonDOWN = new Bouton("BOUTON_DOWN", Vec3(0,0,0));
		ref_ptr<Bouton> boutonLEFT = new Bouton("BOUTON_LEFT", Vec3(-1.1f,0,0));
		ref_ptr<Bouton> boutonRIGHT = new Bouton("BOUTON_RIGHT", Vec3(1.1f,0,0));
		ref_ptr<Bouton> boutonRotation = new Bouton("BOUTON_ROTATION", Vec3(-5.2f,0,0));
		ref_ptr<Bouton> boutonMur = new Bouton("BOUTON_CHOIX_MUR", Vec3(-4.1f,0,0));
		ref_ptr<Bouton> boutonValidation = new Bouton("BOUTON_VALIDATION", Vec3(-3,0,0));
		ref_ptr<Bouton> boutonNew = new Bouton("BOUTON_NEW", Vec3(-7.55f,1.1,0));
		ref_ptr<Bouton> boutonLoad = new Bouton("BOUTON_LOAD", Vec3(-8.1f,0,0));
		ref_ptr<Bouton> boutonSave = new Bouton("BOUTON_SAVE", Vec3(-7,0,0));

		listeBoutons.push_back(boutonUP);
		listeBoutons.push_back(boutonDOWN);
		listeBoutons.push_back(boutonLEFT);
		listeBoutons.push_back(boutonRIGHT);
		listeBoutons.push_back(boutonRotation);
		listeBoutons.push_back(boutonMur);
		listeBoutons.push_back(boutonValidation);
		listeBoutons.push_back(boutonNew);
		listeBoutons.push_back(boutonLoad);
		listeBoutons.push_back(boutonSave);

		//On crée un translation et on place le texte "Controles" dedans
		ref_ptr<MatrixTransform> textScale = new MatrixTransform;
		textScale->setMatrix(Matrix::scale(4,4,1));
		textScale->addChild(new TexteNode("Contrôles"));

		ref_ptr<MatrixTransform> textTranslate = new MatrixTransform;
		textTranslate->setMatrix(Matrix::translate(-8.5,4.5,0));
		textTranslate->addChild(textScale);
	
		boutons->addChild(textTranslate.get());

		boutonScale->setMatrix(Matrix::scale(1.4,1,1));

		boutonScale->addChild(boutonUP.get());
		boutonScale->addChild(boutonDOWN.get());
		boutonScale->addChild(boutonLEFT.get());
		boutonScale->addChild(boutonRIGHT.get());
		boutonScale->addChild(boutonRotation.get());
		boutonScale->addChild(boutonMur.get());
		boutonScale->addChild(boutonValidation.get());
		boutonScale->addChild(boutonNew.get());
		boutonScale->addChild(boutonLoad.get());
		boutonScale->addChild(boutonSave.get());

		boutons->setMatrix(Matrix::translate(5,-2,0));

		return boutons.release();
	}

	void MyView::setSurvolBouton(Bouton *bouton){
		int size = listeBoutons.size();
		for(int i = 0; i < size; i++){
			if(listeBoutons[i] != bouton)
				listeBoutons[i]->setSurvol(false);
		}
		if(bouton)
			bouton->setSurvol(true);
	}
}