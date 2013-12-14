#pragma once
//Classe utilisant l4API windows pour permettre � l'utilisatuer de choisir un fichier � sauver ou � charger
//Source : http://msdn.microsoft.com/en-us/library/windows/desktop/ff485843%28v=vs.85%29.aspx

#include <windows.h>
#include <shobjidl.h> 

#include <iostream>
#include <string>

namespace View {
	class ParcourirFichier{
	public:
		//Ouvre la fenetre de selection de fichier � ouvrir et renvoie le chemin du fichier selection� 
		static std::string ouvrir();
		//Ouvre la fenetre de selection de l'emplacement et du nom du fichier � sauver et renvoie le chemin du fichier choisi
		static std::string sauver();
	};
}