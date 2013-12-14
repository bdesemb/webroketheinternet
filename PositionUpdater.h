#include "Pion.h"

using namespace osg;

// Classe qui va servir à définir un "update callback" pour la mise à jour de la position du parallélépipède

namespace Controller{
	class PositionUpdater :
		public NodeCallback
	{
	
	public:
		// C'est l'opérateur ci-dessous, hérité de NodeCallback, qui doit être redéfini
		// afin de gérer des mises à jour liées à un Node dans le cadre du parcours d'un NodeVisitor
		virtual void operator()(Node* node, NodeVisitor* nv);
	};
}
