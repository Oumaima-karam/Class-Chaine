#include<iostream>
#include<cstring>
#include"chaine.hpp"

using namespace std;

//class Chaine-------------------------------------------
unsigned int Chaine::getTaille(){
    return _taille;
};
void Chaine::settaille(size_t i){
    Chaine s;
    s._taille=i;
};
Chaine::Chaine():_taille(0),_donnees(nullptr){
    _donnees = new char[1];
    _donnees[0] = '\0';
};
Chaine::Chaine(const char* s):_taille(strlen(s)),_donnees(nullptr){
    _donnees = new char[_taille + 1];
    strcpy(_donnees, s);
};
Chaine::Chaine(const Chaine& c):_taille(c._taille),_donnees(c._donnees){
    _donnees = new char[strlen(c._donnees)+1];
    strcpy(_donnees,c._donnees);
};
Chaine::~Chaine(){
    delete[] _donnees;
};
Chaine Chaine::operator=(const Chaine& c){
     if (this != &c) {
        delete[] _donnees;
        _taille = c._taille;
        _donnees = new char[_taille + 1];
        strcpy(_donnees, c._donnees);
    }
    return *this;
};
char Chaine::operator[](int i){
     if (i >= 0 && i < _taille)
        return _donnees[i];
    else
        throw out_of_range("Erreur");
};

Chaine Chaine::operator+(const Chaine& c) const {
    Chaine result;
    result._taille = _taille + c._taille;
    result._donnees = new char[result._taille + 1];
    strcpy(result._donnees,_donnees);
    strcat(result._donnees, c._donnees);
    
    return result;
};

ostream& operator<<(ostream& os, const Chaine& c) {
    os << c._donnees;
    return os;
};

//class Curseura-------------------------------------------
Chaine* Chaine::Curseura::getChai(){
    return chai;
};
int Chaine::Curseura::get_position(){
    return _position;
};
void Chaine::Curseura::set_position(int position){
    _position=position;
};
Chaine::Curseura::Curseura():chai(),_position(0){};
Chaine::Curseura::Curseura(Chaine* c,int pos):chai(c),_position(pos){};
char Chaine::Curseura::operator*(){
    return chai->_donnees[_position];
};

//class CurseuClassique------------------------------
Chaine::CurseurClassique::CurseurClassique(Chaine* chainee, int pos):Curseura(const_cast<Chaine*>(chainee),pos){};
Chaine::CurseurClassique& Chaine::CurseurClassique::operator++() {
    ++_position;
    return *this;
};
Chaine::CurseurClassique& Chaine::CurseurClassique::operator--() {
    --_position;
    return *this;
};
Chaine::CurseurClassique& Chaine::CurseurClassique::fini() {
    if(chai->_taille == _position+1){
        cout<<"Vrai";
    }else{
        cout<<"Faux";
    }
};
Chaine::CurseurClassique& Chaine::CurseurClassique::debut() {
    _position = 0;
    return *this;
};
void Chaine::CurseurClassique::fin(){
    Chaine::Curseura::set_position(chai->getTaille()-1);
};
void afficheCurseur(Chaine::CurseurClassique& curseur) {
    cout<<"Affiche : ";
    cout << *curseur.getChai() << endl;
}

//class CurseuPas-----------------------------------
int Chaine::CurseurPas::getpos_fin(){
    return pos_fin;
};
int Chaine::CurseurPas::getPas(){
    return pas;
};
Chaine::CurseurPas::CurseurPas(Chaine* chain , int debut , int fin , int pass , int pos):Curseura(chain,pos), pos_debut(debut) , pos_fin(fin) ,pas(pass) {};
Chaine::CurseurPas& Chaine::CurseurPas::operator++() {
    _position += pas;
    return *this;
};
Chaine::CurseurPas& Chaine::CurseurPas::operator--() {
    _position -= pas;
    return *this;
};
Chaine::CurseurPas& Chaine::CurseurPas::fini() {
    if(chai->getTaille() == get_position()+1){
        cout<<"Vrai";
    }else{
        cout<<"Faux";
    }
};
Chaine::CurseurPas& Chaine::CurseurPas::debut() {
    set_position(pos_debut);
    return *this;
};
void Chaine::CurseurPas::fin(){
    set_position(chai->getTaille()-1);
};
void Chaine::CurseurPas::afficheCurseur(Chaine::CurseurPas& curseur) {
    if(curseur.pos_fin==0){
        cout<<"Affiche : ";
        cout << "[" << *curseur.debut();
        while (get_position() < chai->getTaille()-1) {
            int newpos = Curseura::get_position();
            newpos += curseur.getPas();
            Curseura::set_position(newpos);
            cout << *curseur;
        }
        cout << "]" << endl;
    }else{
        cout<<"Affiche : ";
        cout <<"["<< *curseur.debut();
        int fin = getpos_fin() -1 ;
        while (get_position() < chai->getTaille()+fin) {
            int newpos = Curseura::get_position();
            newpos += curseur.getPas();
            Curseura::set_position(newpos);
            cout << *curseur;
        }
        cout << "]" << endl;
    }   
}

//Main----------------------------------------------
int main() {
    Chaine chaine1("Un texte");
    cout << "Chaine 1: " << chaine1<< endl;
    cout<<"Taille : "<<chaine1.getTaille()<<endl;

    Chaine chaine2(" long");
    cout << "Chaine 2: " << chaine2 << endl;
    cout<<"Taille : "<<chaine2.getTaille()<<endl;

   
    Chaine chaine3 = chaine1 + chaine2;
    cout << "Resultat de la concatenation : " << chaine3<< endl;

    cout<<"************************************"<<endl;
    cout << "Curseur Classique: "<<endl;

    Chaine::CurseurClassique C1(&chaine3,1);
    cout<<"Le pointeur : "<<*C1 <<endl;
    C1.fini();
    cout <<endl;
    C1.debut();
    cout<<"Retour au debut : "<<*C1<<endl;
    C1.fin();
    cout<<"Aller a la fin du parcours : "<<*C1<<endl;
    afficheCurseur(C1);

    cout<<"************************************"<<endl;
    cout << "Curseur Pas: "<<endl;

    Chaine::CurseurPas P1(&chaine3, 0,-3 ,9 , 12);
    cout<<"Le pointeur : "<<*P1 <<endl;
    P1.fini();
    cout <<endl;
    P1.debut();
    cout<<"Retour au debut : "<<*P1<<endl;
    P1.fin();
    cout<<"Aller a la fin du parcours : "<<*P1<<endl;
    P1.afficheCurseur(P1);
    Chaine::CurseurPas P2(&chaine3, 0, 0 ,3 ,1);
    P2.afficheCurseur(P2);

    return 0;
}
