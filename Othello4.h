
#include <iostream>

using namespace std;

class bordvakje {
	public:
		char kleur;
		bordvakje* buren [8];
};// bordvakje


class othellobord {
	private:
		bordvakje* ingang; //Ingang van pointerlijst
		int lengte; //Geeft grote aan van de pointerlisjt
		int mogelijkeZet [100][2];
   		int beurtNummer; //max = hoogte * breedte - 4
		int aantalGeldigeZetten; //Houd per beurt bij hoeveel geldige zetten er mogelijk zijn
		bool beurt; //Geeft aan wie aan de beurt is
		bool speler1; //Speler 1 Computer of speler
		bool speler2; //Speler 2 Computer of speler

	public:
		othellobord(); //(constructor) 8 bij 8? 0 bij 0?
		~othellobord (); //destructor
		void stand (); //Huidige stand en beurt aantal
		void ritsen (bordvakje* boven, bordvakje* onder); //Aan elkaar verbinden van rijen en vakjes naast elkaar
		//Rijen boven en onder
		void print (); //print het bord
		void beginpositie (); //Bepaalt startpostie wit zwart /n zwart wit
		void verwijder (); //(verwijdert bord na het programma)
		void gegevens (); //vraagt gegevens aan gebruiker
		void maakbord (); //Maakt boord aan
		void ritsen (); //(bordvakje* boven, bordvakje* onder
		void doeZet (int i, int j); //Voert zet uit
		bool isZetGeldig (); //Controleer of zet geldig is voor klaar
		bool compofmens (); //Kijkt of de huidige speler mens is of computer
		void randomZet(); //zet door computer
		int klaar (); //int omdat je het verschil wilt returnen tussen het aantal witte en zwarte vakjes
		void mensZet (); //vraagt zet aan gebruiker net zo lang tot geldig
		bordvakje* gaNaar (int m, int n); //Gaat naar bepaald vakje
		int leesGetal (int minGetal, int maxGetal); //Leest een getal in
		char maakKeuze (); //hoofdmenu keuze
		void statistieken ();  // statistiek bijhouden hoeveel stenen iemand heeft bij winst
}; //Othellobord

