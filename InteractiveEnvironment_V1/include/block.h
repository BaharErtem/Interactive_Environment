#ifndef BLOCK_H
#define BLOCK_H


class block
{
    public:
        block();
        virtual ~block();
         /** Jeder Block hat eine eindeutige ID **/
        string id;
    protected:
    private:
         /** die Postion eines Blocks innerhalb des Patches **/
        int position;
        int anzahlEingaenge;
        int anzahlAusgaenge;

        /** Platzhalter f�r die Funktion, die die Daten in einem Block verarbeitet
        @param es werden die zu verarbeitenden Daten als Parameter �bergeben
        @return gibt die verabeiteten Daten zur�ck **/
        void verarbeiteDaten();
};

#endif // BLOCK_H
