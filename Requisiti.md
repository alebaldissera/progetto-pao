# PROGETTO DI PROGRAMMAZIONE AD OGGETTTI

Occupa circa 50 ore per studente.
Bisogna iscriversi ad una lista per dire se si partecipa in coppia o da soli.

## VICOLI OBBLIGATORI:
1. Definire una gerarchia di tipi che soddisfi
    a. almeno 3 diversi tipi istanziabili
    b. alemeno una classe astratta
    c. altezza della gerarchia >= 2
2. Defire e utilizzare un opportuno template di classe che soddisfi:
    a. avere iteratori
    b. non deve usare contenitori di altre librerie
    c. implementare il contenitore opportunamente alle funzionalità che offre il progetto
3. Definire un template di classe DeepPtr<T> di puntatori polimorfi smart che soddisfi:
    a. gestione automatica della memoria in modalità profonda
    b. T deve supportare clonazione e distruzione polimorfa (guardare la documentazione degli std::unique_ptr<T>)
4. L'utilizzo del contenitore (punto 2) per memorizzare puntatori polimorfi smart ai tipi della gerarchia (punto1)
5. il front-end deve essere una GUI sviluppata con Qt
6. Per i progette di coppia:
    a. Definire I/O da file per gestire i dati dell'applicazione. Non è richiesto l'utilizzo della libreria standard (si possono usare le parti di I/O fornite da Qt). Il formato da usare è libero (XML, JSON, YAML, AXON, ...)
7. Separazione logica tra modello logico e GUI
8. Usare esplicitamente codice polimorfo che sfrutti in modo corretto, ragionevole ed estensibile l'organizzazione gerachicha di tipi (punto 1)

## PER LA GUI:
1. Si può fare il design che si vuole (sia desktop che sistemi mobile)
2. Aderire al design patten Model-View-Controller o Model-View per la progettazione architetturale
3. Si possono aderire a dei design-patter usati comunemente in C++:
    a. Visitor
    b. Proxy
    c. Bridge
    d. Decorator

## CRITERI DI VALUTAZIONE:
1. Deve soddisfare tutti i vincoli 
2. Deve compilare ed eseguire correttamente nella macchiana virtuale ssh.studenti.math.unipd.it
    Si tratta di una condizione necessaria per la valutazione.
    La compilazione dovrà essere possibile invocando òa sequenza di comandi "qmake -project && qmake && make"
    da shell dovrà essere prodotto l'eseguibile sulla macchiana
    Alcuni widget di Qt hanno bisogno del file progetto.pro che nel caso dovrà essere consegnato e dovrà essere esplicitamente documentato nella relazione di proggeto
3. Il progetto deve usare obbligatoriamente chiamate polimorfe:
    a. Incapsulamento
    b. Modularità
    c. Estensibililtà e evolvibilità (in particolare mediante il polimorfismo)
    d. Efficienza e robustezza
4. Funzionalità: quante e quali funzionalità il progetto rende disponibili, e la loro qualità
5. GUI: utilizzo e corretto della libreria Qt; qualità, usabilità e robustezza della GUI

## RELAZIONE:
1. è obbligatoria e verrà valutata
2. Descrizione di tutte le gerarchie di tipi usate
3. Descrizione di tutte le chiamate polimorfe
4. Descrizione di tutti i formati dei file usati per I/O
5. Se necessario, il manuale utente della GUI
6. Se necessario, indicare eventuali istruzioni per la compilazione
7. Indicare le ore effettivamente richieste dalle diverse fasi del progetto (analisi preliminare, proggettazione del modello e gui, apprendimento Qt, codifica modello e gui, debugging, testing) Se si esce dalle 50 ore bisogna giustificare il motivo
8. Per progetto di coppia dovranno essere prodotte due relazioni individuali. Ogni studente dovrà contenere una esplicita sezione "suddivisione del lavoro progettuale" che descriva le diverse responsabilità progettuali della coppia di studenti.
9. Se il progetto viene riconsegnato nella relazione bisogna obbligatoriamente descrivere in modo dettagliato le modifiche apportate al codice rispetto alla precedente versione consegnata. in particolare elencando in modo puntale le modifiche al codice che risolvono i punti deboli riscontrati nella precedente versione


## CONSIGLI:
1. Usare il versioning (git o svn) per fare modifiche parallele

## ESAME ORALE E REGISTRAZIONE VOTO:
1. Si partecipa all'esame orale con:
    a. esame scritto passato con almeno 18/30
    b. Avere consegnato il progetto entro la scadenza stabilita, che verrà sempre comunicata in Moodle
    c. Per le coppie ogniuno consegna distintamente il progetto
    d. Essere iscritti alla lista Uniweb dell'esame orale
2. Durante l'esame verrà comunicato il voto e un feedback. Ci sono 3 esiti possibili:
    a. Valutazione positiva del progetto con registrazione del voto complessivo con esenzione dell'esame orale. Se il voto non è soddisfacente per lo studente si può rifiutare o richiedere l'orale, che potrà portare a variazioni in + o - del voto.
    b. Valutazione del progetto da completarsi con l'esame orale obbligatorio. Al termine verrà proposto un voto complessivo sufficiente oppiure si dovrà riconsegnare il progetto per un successivo esame orale
    c. Progetto rigettato e richiesta di una riconsegna del progetto per un successivo esame orale. In questo caso il voto dello scritto rimane valido
Quando si vuole migliorare il voto il voto precedente viene perso alla sola presenza all'esame.

## SCADENZA DI CONSEGNA:
Il progetto dovrà essere consegnato rispettando tassativamente le scadenze ufficiali previste rese note in Moodle.
La scadenza sarà circa 10-14 giorni prima dell'esame.
Prima sessione di esami orali:
- Primo orale: 10/02/2021 scadenza il 31/01/2021 alle 23.59
- Secondo orale: 26/02/2021 scadenza il 14/01/2021 alle 23.59
