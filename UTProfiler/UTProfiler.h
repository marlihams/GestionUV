#ifndef UTPROFILER_H
#define UTPROFILER_H

#include <vector>
#include <QString>

class UTProfilerException{
public:
    UTProfilerException(const QString& message):info(message){}
    void shownfo();
private:
    QString info;
};

enum  Categorie {
    /* Connaissances Scientifiques */ CS,  /* Techniques et Méthodes */ TM,
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP,
    first=CS, last=SP
};
enum Note { A, B, C, D, E, F, FX, RESERVE, ABS,EnCours  };

class UV {
    QString code;
    QString titre;
    unsigned int nbCredits;
    QString categorie;
    float tauxReussite;
    bool finalExam;

public:

    UV(const UV& u){
        code=u.code;
        titre=u.titre;
        nbCredits=u.nbCredits;
        categorie=u.categorie;
    }
    UV(const QString& c, const QString& t, unsigned int nbc, QString cat,float p, bool final):
      code(c),titre(t),nbCredits(nbc),categorie(cat),tauxReussite(p),finalExam(final){}
    UV(const QString& c):code(c){

    }
    UV(){}
    float getTauxRReussite(){ return tauxReussite;}
    bool hasFinalExam(){return finalExam==true; }
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
    unsigned int getNbCredits() const { return nbCredits; }
    QString getCategorie() const { return categorie; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }

};

class InscriptionUV{

    UV uv;
    Note resultat;

public:

    InscriptionUV(const UV& uvI, Note note):uv(uvI),resultat(note){}
    const UV& getUV() const{
        return uv;
    }
    Note getResult(){
        return resultat;
    }

    void setUv( UV& uv){
        uv=uv;
    }

    void setResultat( Note not_e){
        resultat=not_e;
    }
    UV& getUV(){
        return uv;
    }
};

/*class Semestre {

    std::vector<InscriptionUV> inscriptions;
    int nbInsc;
    QString name;

    Semestre(QString nameS):nbInsc(0), name(nameS){}

    int getNbUvs(){
        return nbInsc;
    }
    QString getName(){
        return name;
    }
    std::vector<InscriptionUV>& getUVS(){
        return inscriptions;
    }

public:
    void addInscription (const InscriptionUV &ins);
    void deleteInscription(const InscriptionUV& ins);
};*/

class DossierEtudiant{

    QString identifiant;
    std::vector<InscriptionUV> inscriptions;
    int nbSemestre;
    QString formationName;
public:
    DossierEtudiant(QString& dossier, int nbSemestre,QString& formation):identifiant(dossier), nbSemestre(nbSemestre),formationName(formation){}

    const QString& getIdentifiant() const {
        return identifiant;
    }
    std::vector<InscriptionUV>& getInscriptions(){
        return inscriptions;
    }

    const int getNbsemstres() const {
        return nbSemestre;
    }
    const QString getFormationName() const {
        return formationName;
    }
public:
    void addInscription (const InscriptionUV& insc);
    void deleteInscription(const QString &str);

};

#endif // UTPROFILER_H
