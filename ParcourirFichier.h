#pragma once
//Classe utilisant l4API windows pour permettre à l'utilisatuer de choisir un fichier à sauver ou à charger
//Source : http://msdn.microsoft.com/en-us/library/windows/desktop/ff485843%28v=vs.85%29.aspx

#include <windows.h>
#include <shobjidl.h> 

#include <iostream>
#include <string>

namespace View {
	class ParcourirFichier{
	public:
		//Ouvre la fenetre de selection de fichier à ouvrir et renvoie le chemin du fichier selectioné 
		static std::string ouvrir();
		//Ouvre la fenetre de selection de l'emplacement et du nom du fichier à sauver et renvoie le chemin du fichier choisi
		static std::string sauver();
	};
}