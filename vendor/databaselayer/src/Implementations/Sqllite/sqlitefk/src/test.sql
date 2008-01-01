CREATE TABLE regressiontest (
	id INTEGER PRIMARY KEY
);

CREATE TABLE test (	
	id INTEGER PRIMARY KEY,
	id_reg INTEGER NOT NULL,
	CONSTRAINT cst_fk_reg FOREIGN KEY (id_reg) REFERENCES regressiontest (id)
);
