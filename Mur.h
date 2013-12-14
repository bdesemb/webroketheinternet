#pragma once

using namespace osg;

namespace model{
	class Mur: public Referenced{
	private:
		float grapheX, grapheY; //Position sur le graphe
		int tableX, tableY;		//Position dans la table
		bool placer;			//Si mur placer sur le plateau
		bool horizontal;		//Si mur à l'horizontal
	public:
			Mur(float nGrapheX,float nGrapheY, int nTableX, int nTableY){
				this->grapheX=nGrapheX;
				this->grapheY=nGrapheY;
				this->tableX=nTableX;
				this->tableY=nTableY;
				this->placer = false;
				this->horizontal = false;
			}
			Mur(float nGrapheX,float nGrapheY, int nTableX, int nTableY, bool placee, bool horizontal){
				this->grapheX=nGrapheX;
				this->grapheY=nGrapheY;
				this->tableX=nTableX;
				this->tableY=nTableY;
				this->placer = placee;
				this->horizontal = horizontal;
			}
			bool getPlacer(){	//Renvoie true si le mur est placé sur le plateau
				return placer;
			}
			bool getHorizontal(){	//Renvoie true si le mur est à l'horizontal
				return horizontal;
			}
			float getGrapheX(){		//Renvoie la position x sur le graphe
				return grapheX;
			}
			float getGrapheY(){		//Renvoie la position y sur le graphe
				return grapheY;
			}
			int getTableX(){		//Renvoie la position x dans la table
				return tableX;
			}
			int getTableY(){		//Renvoie la position y dans la table
				return tableY;
			}
			void setHorizontal(bool boolean){
				this->horizontal = boolean;
			}
			void setGrapheX(float nGrapheX){	//Change la position x sur le graphe
				this->grapheX = nGrapheX;
			}
			void setGrapheY(float nGrapheY){	//Change la position y sur le graphe
				this->grapheY = nGrapheY;
			}
			void setTableX(int nTableX){		//Change la position x dans la table
				this->tableX = nTableX;
			}
			void setTableY(int nTableY){		//Change la position y dans la table
				this->tableY = nTableY;
			}
			void setTableXY(int nTableX, int nTableY){
                this->grapheX = (nTableX/2) + 3;
                this->grapheY = (nTableY/2) + 3;
                this->tableX = nTableX;
                this->tableY = nTableY;
            }
			void deplacer(float nX,float nY){	//Déplacer le mur, paramètre: x à changer, y à changer
				this->grapheX=(grapheX+nX);
				this->grapheY =(grapheY+nY);
				this->tableX = (tableX+nX*2);
				this->tableY = (tableY+nY*2);
			}
			void placerMur(){					//Indiquer le mur comme placé sur le plateau
				this->placer = true;
			}
			void rotation(){			//effectuer une rotation du mur
				if(horizontal)
					this->horizontal = false;
				else
					this->horizontal = true;
			}
	};
}