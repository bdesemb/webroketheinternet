#include "Pion.h"

using namespace osg;

// Classe qui va servir � d�finir un "update callback" pour la mise � jour de la position du parall�l�pip�de

namespace Controller{
	class PositionUpdater :
		public NodeCallback
	{
	
	public:
		// C'est l'op�rateur ci-dessous, h�rit� de NodeCallback, qui doit �tre red�fini
		// afin de g�rer des mises � jour li�es � un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
	};
}
