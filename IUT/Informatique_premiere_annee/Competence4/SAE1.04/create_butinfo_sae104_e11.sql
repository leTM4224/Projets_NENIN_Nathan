drop schema if exists programme_but cascade;
create schema programme_but;
set schema 'programme_but';

CREATE TABLE _competences (
	lib_competence VARCHAR(255) PRIMARY KEY
);

CREATE TABLE _activites (
	lib_activite VARCHAR(255) PRIMARY KEY,
	lib_competence VARCHAR(255) NOT NULL,
	CONSTRAINT _activites_fk FOREIGN KEY (lib_competence) REFERENCES _competences(lib_competence)
);

CREATE TABLE _niveau (numero_n INT PRIMARY KEY);

CREATE TABLE _semestre (
	numero_sem VARCHAR(255) PRIMARY KEY,
	numero_n INT NOT NULL,
	CONSTRAINT _semestre_fk FOREIGN KEY (numero_n) REFERENCES _niveau(numero_n)
);

CREATE TABLE _ue (
	code_ue VARCHAR(255) PRIMARY KEY,
	lib_activite VARCHAR(255) NOT NULL,
	numero_sem VARCHAR(255) NOT NULL,
	CONSTRAINT _ue_fk1 FOREIGN KEY (lib_activite) REFERENCES _activites(lib_activite),
	CONSTRAINT _ue_fk2 FOREIGN KEY (numero_sem) REFERENCES _semestre(numero_sem)
);

CREATE TABLE _parcours (
	code_p VARCHAR(255) PRIMARY KEY,
	libelle_parcours VARCHAR(255) NOT NULL,
	nbre_gpe_td_p INT NOT NULL,
	nbre_gpe_tp_p INT NOT NULL
);

CREATE TABLE _ressources (
	code_r VARCHAR(255) PRIMARY KEY,
	lib_r VARCHAR(255) NOT NULL,
	nb_h_cm_pn INT NOT NULL,
	nb_h_td_pn INT NOT NULL,
	nb_h_tp_pn INT NOT NULL,
	numero_sem VARCHAR(255) NOT NULL,
	code_p VARCHAR(255) NOT NULL,
	CONSTRAINT _ressources_fk1 FOREIGN KEY (numero_sem) REFERENCES _semestre(numero_sem)
);

CREATE TABLE _est_enseignee (
	code_p VARCHAR(255),
	code_r VARCHAR(255),
	CONSTRAINT _est_enseignee_pk PRIMARY KEY(code_p, code_r),
	CONSTRAINT _est_enseignee_fk1 FOREIGN KEY (code_p) REFERENCES _parcours(code_p),
	CONSTRAINT _est_enseignee_fk2 FOREIGN KEY (code_r) REFERENCES _ressources(code_r)
);

CREATE TABLE _sae (
	code_sae VARCHAR(255) PRIMARY KEY,
	lib_SAE VARCHAR(255) NOT NULL,
	nb_h_td_enc INT NOT NULL,
	nb_h_td_projet_autonomie INT NOT NULL
);

CREATE TABLE _comprend_r (
	code_sae VARCHAR(255),
	code_r VARCHAR(255),
	nb_h_td_c INT NOT NULL,
	nb_h_tp_c INT NOT NULL,
	CONSTRAINT _comprend_r_pk PRIMARY KEY(code_sae, code_r),
	CONSTRAINT _comprend_r_fk1 FOREIGN KEY (code_sae) REFERENCES _sae(code_sae),
	CONSTRAINT _comprend_r_fk2 FOREIGN KEY (code_r) REFERENCES _ressources(code_r)
);

CREATE TABLE _correspond (
	lib_activite VARCHAR(255),
	numero_n INT,
	code_p VARCHAR(255),
	CONSTRAINT _correspond_pk PRIMARY KEY(lib_activite, numero_n, code_p),
	CONSTRAINT _correspond_fk1 FOREIGN KEY (lib_activite) REFERENCES _activites(lib_activite),
	CONSTRAINT _correspond_fk2 FOREIGN KEY (numero_n) REFERENCES _niveau(numero_n),
	CONSTRAINT _correspond_fk3 FOREIGN KEY (code_p) REFERENCES _parcours(code_p)
);
