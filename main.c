
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void do_dir (const char * file_name, const char * const *parms);
void do_file (const char * file_name, const char *const *parms, struct dirent *curstruct);

int main(int argc, const char * argv[]) {
    
    const char *parms [1] = {argv[1]};
    //    parms habe ich vorerst einen beliebigen Wert gegeben, da momentan noch uninteressant
    
    char path[strlen(argv[1])];
    strcpy(path, argv[1]);
//    char path[] wird definiert und danach wird argv[1] (übergebener Pfad) hineinkopiert
    
    do_dir(path, parms);
//    aufrufen der Funktion do_dir mit dem übergebenen Pfad und parms (derzeit unwichtig)
    
    return 0;
}

void do_dir (const char * file_name, const char * const *parms)
{
    DIR *curdir = opendir(file_name);
//    öffnet den Directory Stream für das aktuelle Verzeichnis
    
    struct dirent *curstruct;
//    erstellt ein struct dirent in dem die Rückgabe der Funktion readdir() gespeichert werden kann
    
    while ((curstruct = readdir(curdir)))
//        weist curstruct das aktuelle Ergebnis aus readdir() zu; solange readdir() keinen NULL-Pointer ausgibt wird der Anweisungsblock ausgeführt
        
    {
        if ((strcmp(curstruct->d_name, ".") == 0) || (strcmp(curstruct->d_name, "..") == 0))  continue;
//        übergeht alle Einträge die "." oder ".." heißen, da diese zu einem Fehler beim ausführen führen
        
        char newpath[(strlen(file_name))+(strlen(curstruct->d_name))+1];
//        char newpath[] wird erstellt; die Dimenson wird mit der Länge des bisherigen Pfades, der Länge des Namens des aktuellen Eintrags plus einem weiteren Feld angegeben
        
        strcpy(newpath, file_name);
        strcat(newpath, "/");
        strcat(newpath, curstruct->d_name);
//        Dieses Konstrukt fügt den aktuellen Pfad + "/" + den aktuell bearbeiteten Eintrag zusammen, sodass in newpath der neue, aktuellste Pfad gespeichert ist
        
        do_file(newpath, parms, curstruct);
//        do_file() wird mit dem aktuellsten Pfad (newpath) aufgerufen; dazu wird das aktuelle Ergebnis von readdir() übergeben, um in do_file() auf den Typen des Eintrages zugreifen zu können
    }
}



void do_file (const char * file_name, const char *const *parms, struct dirent *curstruct)
{
    printf("%s\n", file_name);
//    der volle, aktuellste Pfad wird ausgegeben
    
    if (curstruct->d_type == 4) do_dir(file_name, parms);
//    falls es sich bei dem aktuellen Eintrag um ein Directory handelt (d_type == 4) wird do_dir() mit dem aktuellsten Pfad aufgerufen
    
}

