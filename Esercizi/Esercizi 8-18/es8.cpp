/*
NOTA MIA: usare .h e .o per fare makefile figo
Creare una classe Casa e la classica gerarchie di classi Persona, Studente, Docente.
-- Casa deve avere i campi numDiStanze, distanzaDalCentro.
-- Persona deve avere i campi char inizialeNome, inizialeCognome, e un puntatore di tipo
Casa.
- Il costruttore deve inizializzare le iniziali e settare nullptr il puntatore.
- Deve avere un metodo saluta() che stampa a schermo "Le mie iniziali sono" seguito dalle
due iniziali. Se il puntatore alla Casa non è nullo dovrà anche stampare " e abito in una casa
di " + numDiStanze + " a " + distanzaDalCentro + " metri dalla centro." . Questo metodo
dovrà supportare il binding dinamico in caso di override.
- Deve avere un metodo trasloca() che prende in input l'indirizzo di una Casa e lo assegna al
proprio puntatore.
- Implementare un distruttore. (cosa fare col puntatore Casa?)
-- Studente deve avere i campi matricola e un puntatore ad un array di interi.
- Il costruttore dovrà richiamare il costruttore della classe madre, inizializzare la matricola e
l'array con un array di 20 elementi con valori randomici tra 18 e 30.
- Deve avere un metodo calcolaMedia() che restituisce un intero rappresentante la sua media
- Deve effettuare l'override del metodo saluta() aggiungendo alla fine del risultato del metodo
della classe madre: " Sono uno studente con matricola " + matricola + " e i miei voti sono "
seguito da tutti i voti " con la media del " seguito dal risultato di calcolaMedia()
- Implementare un distruttore. (cosa fare con l'array?)
-- Docente deve avere i campi numInsegnamenti, numStudenti.
- Il costruttore dovrà richiamare il cosruttore della classe madre e inizializzare
numInsegnamenti e numStudenti.
- Deve fare l'override del metodo saluta() aggiugendo alla fine del risultato del metodo della
classe madre: "Sono un insegnante con " + numInsegnamenti+ " per un totale di " +
numStudenti + " studenti"
- Implementare un distruttore.
Nel main creare 4 Case e 7 Persone (tutti puntatori, no array).
Assegnare a ciascuna persona una Casa (quindi sì, più persone possono abitare nella stessa
casa, la casa non appartiene unicamente ad una persona) col metodo trasloca().
Le persone dovranno essere un po' studenti, un po' docenti e un po' persone generiche.
Scegliete voi se richiedere gli input da terminale.
Dopo averle create tutte, fate presentare tutte le persone.
Successivamente liberate la memoria prima di terminare il programma. */