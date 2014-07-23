CREATE TABLE note (
	noteType varchar PRIMARY KEY
);

INSERT into note values ('A');
INSERT into note values ('B');
INSERT into note values ('C');
INSERT into note values ('D');
INSERT into note values ('E');
INSERT into note values ('F');
INSERT into note values ('Fx');
INSERT into note values ('RESERVE');
INSERT into note values ('ABS');
INSERT into note values ('EnCours');

CREATE TABLE saison (
	SaisonType varchar PRIMARY KEY
);
INSERT into saison values ('Automne');
INSERT into saison values ('Printemps');
INSERT into saison values ('Automne et printemps');

CREATE TABLE categorie (
	uvType varchar PRIMARY KEY
);

INSERT into categorie values ('CS');
INSERT into categorie values ('TM');
INSERT into categorie values ('TSH');
INSERT into categorie values ('SP');
INSERT into categorie values ('TX');

CREATE TABLE statut(
	etat varchar PRIMARY KEY
);

INSERT into statut values ('OUI');
INSERT into statut values ('NON');

CREATE TABLE TSH (
	typeTSH varchar PRIMARY KEY
);
INSERT into TSH values ('Concevoir-Démarches-Et-Pratiques');
INSERT into TSH values ('Communiquer-Démarches-Et-Pratiques');
INSERT into TSH values ('Organiser-Manager-Démarches-Et-Pratiques');
INSERT into TSH values ('Concevoir-Connaissances');
INSERT into TSH values ('Communiquer-Connaissances');
INSERT into TSH values ('Organiser-Manager-Connaissances');

CREATE TABLE nomGenie(
	genie VARCHAR PRIMARY KEY
);
INSERT INTO nomGenie values ('GI');
INSERT INTO nomGenie values ('GM');
INSERT INTO nomGenie values ('GSM');
INSERT INTO nomGenie values ('GSU');
INSERT INTO nomGenie values ('GB');

CREATE TABLE nomFiliere(
	filiere VARCHAR NOT NULL,
	genie varchar NOT NULL references nomGenie(genie),
	PRIMARY KEY (filiere,genie)
);
INSERT INTO nomFiliere values ('SRI','GI');
INSERT INTO nomFiliere values ('ICSI','GI');
INSERT INTO nomFiliere values ('STRIE','GI');
INSERT INTO nomFiliere values ('FDD','GI');
INSERT INTO nomFiliere values ('ADEL','GI');

INSERT INTO nomFiliere values ('AVI','GM');
INSERT INTO nomFiliere values ('FQI','GM');
INSERT INTO nomFiliere values ('MARS','GM');
INSERT INTO nomFiliere values ('IDI','GM');
INSERT INTO nomFiliere values ('MIT','GM');

INSERT INTO nomFiliere values ('CMI','GSM');
INSERT INTO nomFiliere values ('MOPS','GSM');
INSERT INTO nomFiliere values ('PIL','GSM');
INSERT INTO nomFiliere values ('MPI','GSM');

INSERT INTO nomFiliere values ('STI','GSU');
INSERT INTO nomFiliere values ('SR','GSU');
INSERT INTO nomFiliere values ('AIE','GSU');
INSERT INTO nomFiliere values ('MPI','GSU');

INSERT INTO nomFiliere values ('BM','GB');
INSERT INTO nomFiliere values ('BB','GB');
INSERT INTO nomFiliere values ('CIB','GB');
INSERT INTO nomFiliere values ('IAA','GB');


      
CREATE TABLE UV (
	code varchar PRIMARY KEY,
	titre varchar NOT NULL,
	uvCategorie varchar references categorie (uvType) NOT NULL,
	nbCredits integer NOT NULL,
	saison varchar references saison (SaisonType),
	final varchar NOT NULL,
	median varchar NOT NULL,
	projet varchar NOT NULL,
	td varchar NOT NULL,
	tp varchar NOT NULL,
	tauxDeReussiteRecent float NOT NULL,
	description varchar,
	typeTSH varchar references TSH(typeTSH),
	CHECK (tauxDeReussiteRecent>0 and tauxDeReussiteRecent<=1)
	);

CREATE TABLE Formation (
	nom varchar PRIMARY KEY,
	nbCreditsTotal integer NOT NULL,
	nbCS integer NOT NULL,
	nbTM integer NOT NULL,
	nbTSH integer NOT NULL,
	nbTotalCSTM,
	nbSP integer NOT NULL,
	nbCLibrePossibleMax integer NOT NULL,
	nbPSB integer,
	nbPSF integer,
	nbDifferColTSH smallint NOT NULL,
	nbDifferLigneTSH smallint NOT NULL,
	nbSemestreMaxPossible smallint NOT NULL
	);

Create TABLE UVFormation(
	codeUV varchar references UV(code),
	nomFormation varchar references Formation(nom),
	statutObligation varchar NOT NULL references statut(etat) ,
	statutPSF varchar NOT NULL,
	statutPCB varchar NOT NULL,
	minSemestreConseille smallint NOT NULL,
	genie VARCHAR references nomGenie(genie),
	filiere varchar references nomFiliere(filiere),

	PRIMARY KEY (codeUV,nomFormation)
);


CREATE TABLE EtudiantDossier(
	INE varchar NOT NULL,
	dossierIdentifiant PRIMARY KEY,
	nom varchar(20) NOT NULL,
	prenom varchar(20) NOT NULL,
	dateDeNaissance date,
	phone varchar,
	formation varchar references Formation(nom) NOT NULL 
);
CREATE TABLE Semestre(
	nomSemestre VARCHAR NOT NULL,
	dossierIdentifiant varchar references EtudiantDossier(dossierIdentifiant),
	PRIMARY KEY (nomSemestre,dossierIdentifiant)
);

CREATE TABLE Inscription (
	codeUV integer references UV(code) not null,
	inscriptionSsaison varchar references saison(SaisonType) not null,
	annee date NOT NULL,
	resultat varchar references note(noteType) not null,
	etudDossier varchar,
	nomSemestre varchar ,
	Primary KEY (codeUV,nomSemestre, etudDossier),
	FOREIGN KEY (nomSemestre, etudDossier) references Semestre(nomSemestre, etudDossier)
);

CREATE TABLE historique(

ideDossier varchar ,
codeH varchar references UV,
resultat varchar NOT NULL,
formation varchar NOT NULL,
PRIMARY KEY(ideDossier,code)
);