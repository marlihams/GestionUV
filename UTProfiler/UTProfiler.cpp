#include "UTProfiler.h"
#include "QMessageBox"


/*void Semestre::addInscription(const InscriptionUV &ins){
    inscriptions.push_back(ins);
}
void Semestre::deleteInscription(const InscriptionUV &ins){
    //  std::vector<Inscription>::iterator it = std::find(inscriptions.begin(), inscriptions.end(), ins);
    if(it!=inscriptions.end()){
        inscriptions.erase(it);
    }

}*/

void DossierEtudiant::addInscription(const InscriptionUV &ins){
    inscriptions.push_back(ins);
}
void DossierEtudiant::deleteInscription(const QString &str){
    //  std::vector<Inscription>::iterator it = std::find(inscriptions.begin(), inscriptions.end(), ins);
   /* if(it!=inscriptions.end()){
        inscriptions.erase(it);
    }*/

}
