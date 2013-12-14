#include "TexteNode.h"
#include "Bouton.h"

#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>

using namespace osg;
	namespace View {
	class MyView {
		private:
			static const int VIEWPORT_HEIGHT = 100;
			static const int WINDOW_HEIGHT = 800;
			static const int WINDOW_WIDTH = 600;
			static MyView *instance;	// Instance de la View pour le pattern singleton
			//Geode du texte de statut
			osg::ref_ptr<TexteNode> statutTexte;
			osg::ref_ptr<TexteNode> joueurTexte;
			osg::ref_ptr<osgViewer::Viewer> myView;
			osg::ref_ptr<Camera> cameraPlateau;
			osg::Vec3 cameraPlateauEye;
			osg::Vec3 cameraPlateauCenter;
			osg::Vec3 cameraPlateauUp;

			osg::Vec4 couleur_camera_boutons;
			osg::Vec4 couleur_camera_messages;
			osg::Vec4 couleur_camera_plateau;
			osg::Vec4 couleur_sol;
			osg::Vec4 couleur_slot;
			osg::Vec4 couleur_mur;
			osg::Vec4 couleur_pion1;
			osg::Vec4 couleur_pion2;

			int taillePlateau;
			int largeurPlateau;
			int longueurPlateau;
			virtual osg::Camera* MyView::creerCameraBoutons();
			virtual osg::Camera* MyView::creerCameraPlateau();
			virtual osg::Camera* MyView::creerCameraMessages();
			virtual osg::Node* MyView::creerLesBoutons();
			virtual osg::Camera* MyView::creerPlateauDeJeu();
			std::vector<osg::ref_ptr<Bouton>> listeBoutons;
			MyView();
		protected:
			virtual ~MyView();

		public:

			//Obtenir l'instance de la vue
			static MyView* getInstance();
			//Obtenir l'objet osg viewer
			osgViewer::Viewer* getMyView();
			//Obtenir l'oeil de la camera de niveau
			osg::Vec3 getCameraPlateauEye() {
				return cameraPlateauEye;
			}
			//Va servir pour le zoom, que le eye qui doit être modifié
			void setCameraPlateauEye(osg::Vec3 eye) {
				this->cameraPlateauEye = eye;
			}
			//Obtenir le centre de la camera de niveau
			osg::Vec3 getCameraPlateauCenter() {
				return cameraPlateauCenter;
			}
			//Obtenir le sens de la camera de niveau
			osg::Vec3 getCameraPlateauUp() {
				return cameraPlateauUp;
			}
			//Obtenir la camera de niveau
			osg::Camera* getCameraPlateau() {
				return cameraPlateau;
			}
			//modifier le message de statut avec un nouveau texte et une nouvelle couleur
			virtual void setStatut(std::string, osg::Vec4);
			//modifie le statut du jeu pour signaler qui doit jouer
			virtual void setJoueurTexte(std::string, osg::Vec4);
			//Passe le bouton en mode survol si il ne l'est pas, et vice versa
			virtual void setSurvolBouton(Bouton*);
	};
}