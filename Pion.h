#pragma once
#include <osg/Referenced>

using namespace osg;

namespace model{
	class Pion: public Referenced{
	private:
		float grapheX, grapheY;		//Position sur le graphe
		int tableX, tableY;			//Position dans la table
	public:
		Pion(float nGrapheX, float nGrapheY, int nTableX, int nTableY);
		float getGrapheX();
		float getGrapheY();
		int getTableX();
		int getTableY();
		//déplacer le pion
		void deplacer(float nX, float nY);
	};
}
