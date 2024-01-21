#ifndef CHAINE_HPP
#define CHAINE_HPP

#include<iostream>

using namespace std;

class Chaine{
    unsigned int _taille;
    char* _donnees;
    public:
    unsigned int getTaille();
    void settaille(size_t) ;
    Chaine();
    Chaine(const char*);
    Chaine(const Chaine&);
    ~Chaine();
    Chaine operator=(const Chaine&);
    char operator[](int);
    Chaine operator+(const Chaine&)const ;
    friend ostream& operator<<(ostream& os, const Chaine& c);
    class Curseura{
        protected:
        Chaine* chai;
        int _position;
        public:
        Chaine* getChai();
        int get_position();
        void set_position(int);
        Curseura();
        Curseura(Chaine* , int);
        char operator*();
        virtual Curseura& operator++()=0;
        virtual Curseura& operator--()=0;
        virtual Curseura& fini()=0;
        virtual Curseura& debut()=0;
        virtual void fin()=0;
    };
    class CurseurClassique:public Curseura{
        public:
        CurseurClassique(Chaine* , int);
        CurseurClassique& operator++() override;
        CurseurClassique& operator--() override;
        CurseurClassique& fini() override;
        CurseurClassique& debut() override;
        void fin() override;
        static void afficheCurseur(CurseurClassique&);
        
    };
    class CurseurPas : public Curseura {
        int pos_debut;
        int pos_fin;
        int pas;
        public:
        int getpos_fin();
        int getPas();
        CurseurPas(Chaine* , int , int , int , int);
        CurseurPas& operator++() override;
        CurseurPas& operator--() override;
        CurseurPas& fini() override;
        CurseurPas& debut() override;
        void fin() override;
        void afficheCurseur(CurseurPas&);
    };
};


#endif