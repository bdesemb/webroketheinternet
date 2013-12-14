#include "MyView.h"

using namespace osg;
using namespace View;

int main(void){
	MyView * vue = MyView::getInstance();
	ref_ptr<osgViewer::Viewer> osgViewer = vue->getMyView();
	// Lancement de la boucle de rendu associée au viewer défini 
	return 	osgViewer->run();
}