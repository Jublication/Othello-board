#include "oth.h"
#include <fstream> 
using namespace std;

void infoblokje () {  // infoblokje
    cout << "Infoblokje:"<< endl;
	cout << "Dit programma is gemaakt door: " << endl;
	cout << "- Jordy van Brakel" << endl;
	cout << "- Thorsten Hopman" << endl;
	cout << "In dit programma kunt u het spel Othello spelen " << endl;
	cout << "Dit kan tegen iemand anders of tegen een computer " << endl;
	cout << "Ook kunt u het bord aanpassen" << endl << endl; 
}

othellobord::othellobord () { //Constructor
	lengte = 0; //Mag persoon gedeeltelijk zelf invullen
	beurt = true;
	beurtNummer = 0;
    aantalGeldigeZetten = 0;
	speler1 = false;
	speler2 = false;
};

othellobord::~othellobord () { //destructor
	delete ingang;
}

char leesOptie () { //Leest het antwoord van gebruiker bij (sub)menu
	char karKeuze; //Leest karakter van persoon in
	char karEerste; //Pakte eerste karakter van ingevoerde groep karakters
	cin.get (karKeuze);	
	while (karKeuze == '\n') { //Voorkomt nutteloze enters door gebruiker
		cout << "Voer opnieuw in" << endl;
		cin.get (karKeuze);
	}
	karEerste = karKeuze; //Alleen eerste karakter pakken dat wordt ingevoerd
	while (karKeuze != '\n') {
		cin.get (karKeuze);
	}
	return karEerste;
}

int othellobord::leesGetal (int minGetal, int maxGetal) { //leest getal in voor andere functies
	char kar; //Getal dat wordt ingelezen
	int getalsom = 0; //Getal dat uiteindelijk wordt teruggegeven
  	cin.get (kar);
  	while (kar == '\n') { //Voorkomt nutteloze enters door gebruiker
  	   cin.get (kar);
  	}
  	while ( kar != '\n') { //Zet kar om in int
  	   if (kar >= '0' && kar <= '9' && getalsom * 10 + (kar - '0') <= maxGetal) {
  	      getalsom = getalsom * 10 + (kar - '0');
  	   }
  	   cin.get (kar);
  	}
  	if (getalsom < minGetal) {
  		getalsom = minGetal;
  	}
  	return getalsom;
}

void othellobord::gegevens() { //Gegevens invullen door gebruiker
    char optie; //Voor j of n bij speler
	cout << "Vul de gegevens in van het spel" << endl;
	cout << "Vul de grote van het bord in. " << endl;
	cout << "Het bord moet breder zijn dan 5 en niet breder dan 9, " << endl;
	cout << "en de breedte moet een even getal zijn" << endl;
	lengte = leesGetal (6, 9);
    if (lengte %2) { //Voor even aantal
        lengte = lengte + 1;
    }
    cout << "Is de eerste speler (zwart) een computer j/n?" << endl;
    optie = leesOptie ();
    while (optie != 'j' and optie != 'n') { //Niet geldige antwoorden
        cout << "Voer een correct antwoord in" << endl;
        optie = leesOptie ();
    }
    if (optie == 'j') {
        speler1 = false; //Computer
    }
    else {
        speler1 = true; //Mens
    }
    cout << "Is de tweede speler (wit) een computer j/n?" << endl;
    optie = leesOptie ();
    while (optie != 'j' and optie != 'n') { //Niet geldige antwoorden
        cout << "Voer een correct antwoord in" << endl;
        optie = leesOptie ();
    }
    if (optie == 'j') {
        speler2 = false; //Computer
    }
    else {
        speler2 = true; //Mens
    }
	cout << endl;
}

void othellobord::print () { //Print het het huidige othellobord
	int j; // Teller bij for loop boven en cijfers boven en linkerkant bord
	bordvakje* hulp; //Wijst pointers aan die geprint worden
	bordvakje* hulpVerticaal; //Onthoudt eerste pointer van regel
	cout << "   "; 
	for (j = 1; j <= lengte; j++) { //Bovenste regel vullen met cijfers
		cout << " " << j << " ";
	}
	cout << endl;
	j = 1;
	hulp = ingang; //Voor horizontaal couten
	hulpVerticaal = ingang; //Houdt eerste bordvakje van rij vast om volgende regel kunnen aanteroepen
	while (hulpVerticaal != 0) {	//Volgende rij
		cout << " " << j << " "; //Maakt cijfers aan linker kan van bord
		j++;
		while (hulp != 0) { //Horizontaal couten
			cout << " " << hulp->kleur << " ";
			hulp = hulp->buren[6];
		}
		cout << endl;
		hulpVerticaal = hulpVerticaal->buren[4]; //Volgende rij
		hulp = hulpVerticaal;
	}
	cout << endl;
}

void othellobord::ritsen (bordvakje* rij1, bordvakje* rij2) {
	//Verbindt buren van twee rijen met elkaar
	while (rij1 != NULL) { //Loop die verbindt
		if (rij1->buren[2] == NULL) { //Als pointers eerste in is rij geen linksboven of linksonderbuur
			rij1->buren [4] = rij2;
			rij2->buren[0] = rij1;
		}
		else { //Niet eerste pointer in rij
			rij1->buren [3] = rij2->buren[2];
			rij1->buren [4] = rij2;
			rij2->buren[1] = rij1->buren[2];
			rij2->buren[0] = rij1;
		}
		if (rij1->buren[6] != NULL) { //Laatste in rij
			rij1->buren[5] = rij2->buren[6];
			rij2->buren[7] = rij1->buren[6];
		}
		rij1 = rij1->buren[6];
		rij2 = rij2->buren[6];
		//Volgende pointer pakken
	}
}

void othellobord::maakbord () {
	//Maakt rij van bord aan
	//Nummer 2 en 6 in array zijn respectievelijk links en rechter pointer gezien van uit huidige pointer
	bordvakje* pb; //Maakt pointers in regel aan
	bordvakje* ph;//Geeft eerste pointer huidige regel
	bordvakje* pvorige; //Onthoud eerste pointer vorige regel
	bordvakje* hulp = NULL; //Onthoudt vorige pointer
	int i,j; //teller bij for loop
	ingang = new bordvakje; //Beginnen met aanleggen
	pb = ingang;
	for (j = 1; j<= lengte;j++) { //Maakt eerste rij aan
		pb->buren[2] = hulp; 
		pb->kleur = '.'; 
		if (j == lengte) { //Einde rij
			pb->buren[6] = NULL; 
		}
		else {
			pb->buren[6] = new bordvakje; //Nieuw vakje rechts
			hulp = pb; 
			pb = pb-> buren [6]; //pb wordt volgende vakje
		}
	}
	pvorige = ingang; //Vorige regel onthouden
	ph = new bordvakje; //Nieuwe regel
	pb = ph; //Eerste van huidige regel onthouden
	hulp = NULL; //Start als NULL want buren [2] is leeg
	for (i = 1; i <= lengte-1; i++) { //Dubelle loop voor volgende regels
		for (j = 1; j<= lengte; j++) {
			pb->buren[2] = hulp; 
			pb->kleur = '.';
			if (j == lengte) { //Zelfde als eerste regel
				pb->buren [6] = NULL;
			}
			else {
				pb->buren[6] = new bordvakje;
				hulp = pb;
				pb = pb->buren [6];
			}
		}
		ritsen (pvorige, ph); //Verbindt regels
		pvorige = ph;
		ph = new bordvakje;
		pb = ph;
		hulp = NULL;
	}
}
void othellobord::beginpositie () { //Legt begin vierkantje neer
	int k = lengte/2; //Makkelijker invoeren
	bordvakje* hulp = gaNaar (k, k); //Kleuren geven aan beginhokjes
	hulp->kleur = 'z';
	hulp = gaNaar (k, k + 1);
	hulp->kleur = 'w';
	hulp = gaNaar (k + 1, k);
	hulp->kleur = 'w';
	hulp = gaNaar (k + 1, k + 1);
	hulp->kleur = 'z';
}

bordvakje* othellobord::gaNaar (int m, int n) {
	//Geeft pointer terug voor verticale en horizontale waarde
	int i, j; //Variabelen voor locatie vakje
	bordvakje* hulp = ingang; //hulp pointer om door lijst te gaan
	for (i = 1; i < m; i++) { //Loop door lijst heen
		hulp = hulp->buren[4];
	} 
	for (j = 1; j < n; j++) {
		hulp = hulp->buren[6];
	}
	return hulp;
}

bool othellobord::isZetGeldig () {
    bordvakje* hulp; //Vakje dat moet gecontroleerd worden
	int i, j, k; //tellers
    if (beurt) { //controleren voor beurt
        for (i = 1; i <= lengte; i++) { //telller
            for (j = 1; j <= lengte; j++) { //teller
                hulp = gaNaar (i, j);
                if (hulp->kleur == '.' ) { //Alleen lege vakjes
                	for (k = 0; k < 8; k++) {  //Controleren buren
                    	if (hulp->buren[k] == NULL) { //Nullen ontwijken
                        }
                        else if (hulp->buren[k]->kleur == 'w') {
                    	    hulp = hulp->buren[k];
                    	    while (hulp->kleur != 'z' and hulp != NULL and hulp->kleur != '.') {
                    			if (hulp-> buren[k] == NULL or hulp->kleur == '.') {
                	                break;
                                }
                                hulp = hulp->buren[k];
                            }
                            if (hulp->kleur == 'z') {
								//MogelijkeZetten in array stoppen
                            	mogelijkeZet [aantalGeldigeZetten][1] = i;
                            	mogelijkeZet [aantalGeldigeZetten][2] = j;
                            	aantalGeldigeZetten++;
                            }
						}
			 		}
        		}
        	}
        }
    	cout << endl;
    }
    else  { //controleren voor beurt
        for (i = 1; i <= lengte; i++) { //telller
            for (j = 1; j <= lengte; j++) { //teller
                hulp = gaNaar (i, j);
                if (hulp->kleur == '.' ) { //Alleen lege vakjes
                    for (k = 0; k < 8; k++) {  //Controleren buren
                        if (hulp->buren[k] == NULL) { //Nullen ontwijken
                        }
                        else if (hulp->buren[k]->kleur == 'z') {
                            hulp = hulp->buren[k];
                            while (hulp->kleur != 'w' and hulp != NULL and hulp->kleur != '.') {
                                if (hulp-> buren [k] == NULL or hulp->kleur == '.') {
                                    break;
                                }
                                hulp = hulp->buren[k];
                            }
                            if (hulp->kleur == 'w') {
								//Mogelijke zet in array stoppen
                                mogelijkeZet [aantalGeldigeZetten][1] = i;
                                mogelijkeZet [aantalGeldigeZetten][2] = j;
                                aantalGeldigeZetten++;
                            }
                        }
                    }
                }
            }
        }
        cout << endl;
    }
	if (mogelijkeZet [0][1] == 0) { //Als mogelijke zetten leeg is dan klaar
		return true;
	}
	beurtNummer++;
    return false; 
}
	
void othellobord::doeZet (int i, int j) {
	bordvakje* hulp = gaNaar (i, j); //Vakje waarop gezet moet worden
	bordvakje* hulpVerder; //Helpt bij 
	int k, l; //Door buren heen lopen
	int tel = 0;
	if (beurt) { //Zet voor zwart
		hulp->kleur = 'z'; //Controleren buren
		for (k = 0; k < 8; k++) {
            if (hulp->buren[k] == NULL) { //Voorkomen NULLS
            }  
			else if  (hulp->buren[k]->kleur == 'w') {
				//Controleren of er nog steen komt die zwart is
				//Dan alles tussen die stenen zwart maken
				hulpVerder = hulp->buren[k];
				while (hulpVerder->kleur != 'z' and hulpVerder != NULL and hulpVerder->kleur != '.') {
					tel++;
                    if (hulpVerder-> buren [k] == NULL) {
                        break;
                    }
                    hulpVerder = hulpVerder->buren[k];
				}
				if (hulpVerder->kleur == 'z') {
					hulpVerder = hulp;
					hulpVerder = hulpVerder->buren[k];
					for (l = 0; l < tel; l++) { 
						//Alle hokjes tussen plaats waar gezet is en volgende zwarte hokje zwart maken
						hulpVerder->kleur = 'z';
						hulpVerder = hulpVerder->buren[k];
					}		
				}
				tel = 0;
			}	
		}
		beurt = false; //Volgende beurt
	}
	else { //Zet voor wit
		hulp->kleur = 'w';
		for (k = 0; k < 8; k++) {
            if (hulp->buren[k] == NULL) { //Voorkomen NULLS
            }
			else if  (hulp->buren[k]->kleur == 'z') {
				//Controleren of er nog steen komt die zwart is
				//Dan alles tussen die stenen zwart maken
				hulpVerder = hulp->buren[k];
				while (hulpVerder->kleur != 'w' and hulpVerder != NULL and hulpVerder->kleur != '.') {
					tel++;
                    if (hulpVerder->buren[k] == NULL) {
                        break;
                    }
                    hulpVerder = hulpVerder->buren[k];
				}
				if (hulpVerder->kleur == 'w') {
					hulpVerder = hulp;
					hulpVerder = hulpVerder->buren[k];
					for (l = 0; l < tel; l++) {
						//Alle hokje tussen plaats waar gezet is en volgende witte hokje wit maken
						hulpVerder->kleur = 'w';
						hulpVerder = hulpVerder->buren[k];
					}		
				}
				tel = 0; //restetten tel
			}	
		}
		beurt = true; //Volgende beurt
	}
}

void othellobord::randomZet () { //Zet door computer
    int i, j, k; //tellers en getal voor random generator
    k = rand () % aantalGeldigeZetten; //Kiezen uit mogelijke zetten
    i = mogelijkeZet [k][1]; //Getal uit mogelijkezetten array hallen voor verticaal
    j = mogelijkeZet [k][2]; //Idem voor horizontaal
    doeZet (i, j);
    
    for (i = 0; i < aantalGeldigeZetten; i++) { //Leegmaken voor volgende ronde
        mogelijkeZet[i][1] = 0;
        mogelijkeZet[i][2] = 0;
        aantalGeldigeZetten = 0;
    }
} 


void othellobord::mensZet () { //Zet door een mens
//Vraagt zet aan speler en voert deze uit wanneer bool is zet geldig true is.
	int vert, hor, i;
	cout << "Geef de vertical waarde van het punt waar u wilt plaatsen : " << endl;
	vert = leesGetal (1, lengte + 1);
	cout << "Geeft de horizontale waarde van het punt waar u wilt plaatsen : " << endl;
	hor = leesGetal (1, lengte + 1);
    for (i = 0; i <= aantalGeldigeZetten; i++) {
        if (mogelijkeZet[i][1] == 0) {
            break;
        }
        else if (mogelijkeZet[i][1] == vert and mogelijkeZet[i][2] == hor) { //Deze moet getriggered worden
            doeZet (vert, hor);
        }
        else if (i == 100) {
            cout << "U heeft een ongeldige zet gedaan, voer opnieuw in" << endl;
            mensZet ();                
        }
    }
  
    vert = 0;
    hor = 0;
    for (i = 0; i < 100; i++) { //Leegmaken voor volgende ronden
        mogelijkeZet[i][1] = 0;
        mogelijkeZet[i][2] = 0;
        aantalGeldigeZetten = 0;
    }
}

int othellobord::klaar () { //Geeft aan wie wint en geeft verschil terug
    int telZwart = 0; //teller aantal zwarte vakjes
    int telWit = 0; //teller aantal witte vakjes
    int i,j; // Gebruikt bij for loop om pointerlijst uit te lezen
    bordvakje* hulp = ingang;
    bordvakje* hulpVerticaal = ingang;
    statistieken ();
    if (beurtNummer < ((lengte*lengte) - 4)) { //Als vroegtijdig over
        if (beurt) { //Zwart wint
            cout << "Wit wint doordat zwart geen stenen meer kan neerleggen" << endl;
        }
        else { //Wit wint
            cout << "Zwart wint doordat wit geen stenen meer kan neerleggen" << endl;
        }
    }
    else { //Bij vol bord
        for (i = 1; i <= lengte; i++) {
            for (j = 1; j <= lengte; j++) {
                if (hulp->kleur == 'z') {
                    telZwart++;
                }
                else if (hulp->kleur == 'w') {
                    telWit++;
                }
                hulp = hulp->buren[6];
            }
            hulpVerticaal = hulpVerticaal->buren[4];
            hulp = hulpVerticaal;
        }
        if (telZwart > telWit) {
            cout << "Zwart heeft gewonnen met een marge van " << telZwart - telWit << " stenen" << endl;
            return telZwart - telWit;
        }
        else if (telWit > telZwart) {
            cout << "Wit heeft gewonnen met een marge van " << telWit - telZwart << " stenen" << endl;
            return telWit - telZwart;
        }
        else {
            cout << "Het is een gelijkspel" << endl;
        }
    }
	return 0;
}


char othellobord::maakKeuze () { //Vertelt mogelijke keuzes en vraag keuze van persoon
	char menuKeuze; //Keuze van gebruiker
	int i; //Teller bij forloop voor prinen mogelijkeZetten
	cout << "Dit is het hoofdmenu u kunt:" << endl;
    cout << "g : De gegevens van het spel aanpassen. Dit reset het spel" << endl;
	cout << "s : Slaan" << endl;
	cout << "q : Het programma stoppen" << endl << endl;

	for (i = 0; i < aantalGeldigeZetten; i++) { //Print mogelijke zets
		cout << "#" << i + 1 << " " <<mogelijkeZet[i][1] << "," << mogelijkeZet[i][2] << " ";
	}
	cout << endl;
	menuKeuze = leesOptie ();
	return menuKeuze;
}

bool othellobord::compofmens () { //Controleer of huidige speler computer of mens is
	if ((speler1 and beurt) or (speler2 and !beurt)) {
		return true;
	}
	else {
		return false;
	}
}

void othellobord::stand() { //Geeft stand en huidige beurt
	bordvakje* hulp = ingang; //Begin voor forloop door pointerlijst
	bordvakje* hulpVerticaal = ingang; //Onthoudt eerste pointer in een rij
	int telWit = 0; //Telt aantal witte stenen
	int telZwart = 0; //Telt aantal zwarte stenen
	int i,j; //Teller voor for loop
	for (i = 1; i <= lengte; i++) { // loop door pointerlijst heen en tel
		for (j = 1; j <= lengte; j++) {
			if (hulp->kleur == 'z') {
				telZwart++;
			}
			else if (hulp->kleur == 'w') {
				telWit++;		
			}
			hulp = hulp->buren[6];
		}
		hulpVerticaal = hulpVerticaal->buren[4];
		hulp = hulpVerticaal;
	}
	if (beurt) {
	cout << "Zwart is aan de beurt" << endl;
	}
	else {
		cout << "Wit is aan de beurt" << endl;
	}
	cout << "Score zwart: " << telZwart << " " << "Score wit: " << telWit << endl;
	cout << "Beurt nummer: " << beurtNummer << endl;
}

void menu () { //Menu
    srand (time(NULL)); //Seed voor random generator
	int tel = 0; //teller voor whileloop menu
	char keuze; //keuze van gebruiker
	bool klaar; //controleert of er nog mogelijke zetten zijn
	bool speler; //Bepaalt of computer of mens
	othellobord othello; //constructor
	othello.gegevens (); //Gegevens vragen aan gebruiker
	othello.maakbord (); //Aanmaken bord
	othello.beginpositie (); //Start vierkantje maken
	cout << "Zwart begint" << endl;
	while (tel == 0 ) {
		othello.print ();
        klaar = othello.isZetGeldig ();
        if (klaar) { //Als geen zetten meer mogelijk einde spel
            othello.klaar ();
            exit (0);
        }
		othello.stand ();
		speler = othello.compofmens ();
		if (speler == true) { //Mens
            keuze = othello.maakKeuze (); //Keuze inlezen
            switch (keuze) { 
                case 'G':
                case 'g':
                    othello.gegevens (); //Gegens aanapssen
                    break;
                case 'S':
                case 's':
                    othello.mensZet (); //slaan
                    break;
                case 'Q': //Stoppen
                case 'q': 
                    tel++;
                default: 
                    cout << "Voer correct antwoord in" << endl;
            }
        }
        else  { //Computer
            othello.randomZet ();
        }
	}
	//~othellobord othello; 
}
void othellobord::statistieken () { //Stopt aantal beurten in apart txtbestand
	ofstream statistiekfile;
	statistiekfile.open ("beurtnummers.txt", ios::app);
	statistiekfile << endl <<  beurtNummer;
	statistiekfile.close ();
}
