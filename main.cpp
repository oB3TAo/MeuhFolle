#include <iostream> // Pour les entrées/sorties standard
#include <fstream> // Pour la lecture de fichiers
#include <sstream> // Pour les flux de chaînes de caractères
#include <vector> // Pour utiliser des vecteurs
#include <string> // Pour utiliser des chaînes de caractères

using namespace std; // Pour éviter d'écrire "std::" devant les éléments standard

// Cette classe représente un créneau avec ses caractéristiques.
class Creneau {
public:
    // Constructeur de la classe Creneau
    Creneau(const string& label, const string& plage_horaire, const string& type_mission, int coefficient)
            : label(label), plage_horaire(plage_horaire), type_mission(type_mission), coefficient(coefficient) {}

    string label; // Label du créneau
    string plage_horaire; // Plage horaire du créneau
    string type_mission; // Type de mission du créneau
    int coefficient; // Coefficient du créneau
};

// Cette classe représente un bénévole avec ses choix de coéquipiers et missions.
class Benevole {
public:
    // Constructeur de la classe Benevole
    Benevole(const string& nom, const vector<string>& choix_coquipiers, const vector<string>& choix_missions)
            : nom(nom), choix_coquipiers(choix_coquipiers), choix_missions(choix_missions) {}

    string nom; // Nom du bénévole
    vector<string> choix_coquipiers; // Choix de coéquipiers du bénévole
    vector<string> choix_missions; // Choix de missions du bénévole
};

// Cette fonction lit le contenu d'un fichier CSV et crée les objets Creneau et Benevole correspondants.
pair<vector<Creneau>, vector<Benevole>> lire_fichier(const string& fichier) {
    vector<Creneau> creneaux; // Vecteur de créneaux
    vector<Benevole> benevoles; // Vecteur de bénévoles

    ifstream file(fichier); // Ouverture du fichier en lecture
    if (!file.is_open()) { // Vérification de l'ouverture du fichier
        cerr << "Impossible d'ouvrir le fichier " << fichier << endl; // Affichage d'un message d'erreur
        return make_pair(creneaux, benevoles); // Retourne des vecteurs vides
    }

    string line; // Variable pour stocker chaque ligne lue du fichier
    // Lire les informations sur les créneaux
    while (getline(file, line)) { // Tant qu'il y a des lignes à lire dans le fichier
        stringstream ss(line); // Création d'un flux à partir de la ligne lue
        string label, plage_horaire, type_mission; // Variables pour stocker les informations du créneau
        int coefficient; // Variable pour stocker le coefficient du créneau
        getline(ss, label, ';'); // Lecture du label du créneau
        getline(ss, plage_horaire, ';'); // Lecture de la plage horaire du créneau
        getline(ss, type_mission, ';'); // Lecture du type de mission du créneau
        ss >> coefficient; // Lecture du coefficient du créneau
        // Si le label commence par "ben_", on considère que c'est le séparateur
        if (label.substr(0, 4) == "ben_") { // Vérification du label
            break; // Sortie de la boucle
        }
        // Création et ajout d'un nouvel objet Creneau au vecteur creneaux
        creneaux.emplace_back(label, plage_horaire, type_mission, coefficient);
    }

    // Lire les informations sur les bénévoles
    do {
        stringstream ss(line); // Création d'un flux à partir de la ligne lue
        string nom, choix_coquipiers_str, choix_missions_str; // Variables pour stocker les informations du bénévole
        getline(ss, nom, ';'); // Lecture du nom du bénévole
        vector<string> coquipiers; // Vecteur pour stocker les choix de coéquipiers du bénévole
        getline(ss, choix_coquipiers_str, ';'); // Lecture des choix de coéquipiers du bénévole
        stringstream coq_ss(choix_coquipiers_str); // Création d'un flux à partir de la chaîne de choix de coéquipiers
        string coquipier; // Variable pour stocker chaque choix de coéquipier
        // Parcours des choix de coéquipiers et ajout dans le vecteur coquipiers
        while (getline(coq_ss, coquipier, ',')) { // Tant qu'il y a des choix de coéquipiers à lire
            coquipiers.push_back(coquipier); // Ajout du choix de coéquipier dans le vecteur coquipiers
        }

        vector<string> missions; // Vecteur pour stocker les choix de missions du bénévole
        getline(ss, choix_missions_str, ';'); // Lecture des choix de missions du bénévole
        stringstream mission_ss(choix_missions_str); // Création d'un flux à partir de la chaîne de choix de missions
        string mission; // Variable pour stocker chaque choix de mission
        // Parcours des choix de missions et ajout dans le vecteur missions
        while (getline(mission_ss, mission, ',')) { // Tant qu'il y a des choix de missions à lire
            missions.push_back(mission); // Ajout du choix de mission dans le vecteur missions
        }
        // Création et ajout d'un nouvel objet Benevole au vecteur benevoles
        benevoles.emplace_back(nom, coquipiers, missions);
    } while (getline(file, line)); // Tant qu'il y a des lignes à lire dans le fichier

    file.close(); // Fermeture du fichier
    return make_pair(creneaux, benevoles); // Retourne les vecteurs creneaux et benevoles
}

// Exemple d'utilisation
int main() {
    string chemin_fichier = "Pb0.csv"; // Chemin vers le fichier CSV
    auto [creneaux, benevoles] = lire_fichier(chemin_fichier); // Appel de la fonction lire_fichier

    cout << "Creneaux:" << endl;
    // Parcours et affichage des créneaux
    for (const auto& creneau : creneaux) {
        cout << "Label: " << creneau.label << ", Plage horaire: " << creneau.plage_horaire
             << ", Type de mission: " << creneau.type_mission << ", Coefficient: " << creneau.coefficient << endl;
    }

    cout << "\nBenevoles:" << endl;
    // Parcours et affichage des bénévoles
    for (const auto& benevole : benevoles) {
        cout << "Nom: " << benevole.nom << ", Choix coequipiers: ";
        for (const auto& coequipier : benevole.choix_coquipiers) { // Parcours et affichage des choix de coéquipiers
            cout << coequipier << " ";
        }
        cout << ", Choix missions: ";
        for (const auto& mission : benevole.choix_missions) { // Parcours et affichage des choix de missions
            cout << mission << " ";
        }
        cout << endl;
    }

    return 0; // Fin du programme
}
