//============================================================================
// Name        : main.cpp
// Author      : MarcF
// Version     : 0.9.2 eleve
// Date        : 11/01/2018 pour CCF2
// Copyright   : Your copyright notice
// Description : E5 CCF2 01/2018 : extraction tags flac
//				 + insertion fichier (pas de Bdd)
// REM         : 
//============================================================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
	using namespace std;

#include "tags_std.hpp"

void insert_file();
void ecrit_fichier_log(string);

int main()
{
	//DECLARATIONS :
    ifstream myfile;
    string taglines;
    string caract;
    string caract2;
    const char *caract3=(char *)malloc(1);
    size_t trouve;
    size_t posegal;
    short numero;
    short boucle;
    bool ouverture_fichier;

	//OUVERTURE FICHIER MUSIQUE .flac :
	myfile.open("01-10-Allemande_24bits_96kHz-SMR.flac", ios_base::binary);
	
	//TEST SI OUVERTURE OK :
    ouverture_fichier = myfile.is_open();

    if(ouverture_fichier == true)
    {
        /* write log file */
        ecrit_fichier_log("OK : FICHIER AUDIO OUVERT");
        ecrit_fichier_log("SUITE APPLICATION........");
        //cout << "OK : FICHIER AUDIO OUVERT" << endl ;
		
		//EXTRACTION DES PREMIERES LIGNES DU FICHIER :
        for(short l=0; l<4096; l++)
        {
            caract=myfile.get();
            taglines+=caract;
        }

		//RECHERCHE DES TAGS STANDARDS :
        for ( numero = 0; numero < NB_MAX_TAGS; numero++ )
        {
            trouve=taglines.find(tags_std[numero]);
            if(trouve!=string::npos)
            {
                cout << tags_std[numero] << " : OK ! " ;
                posegal=trouve+tags_std[numero].length();
                boucle=0;
                do
                {
                    caract2=taglines.substr(posegal+1+boucle++,1);
                    caract3=caract2.c_str();
                    tags_contents[numero]+=caract3;
                }
                while(*caract3!=0x00);
                tags_contents[numero].resize(tags_contents[numero].length()-1);
                cout<<"*"<<tags_contents[numero]<<"*"<<endl;
            }
        }

        myfile.close();
        ecrit_fichier_log("OK : FICHIER AUDIO FERME");

        insert_file();
    }
    else
    {
        /* open log file */
        ecrit_fichier_log("ERR : FICHIER AUDIO NON OUVERT");
        ecrit_fichier_log("APPLICATION INTERROMPUE.......");
        cout << "ERR : FICHIER AUDIO NON OUVERT" << endl ;
        cout << "APPLICATION INTERROMPUE......." << endl ;
    }
//deuxieme son

	
    myfile.open ("01-08-III_Menuetto_Allegro_24bits_88kHz-SMR.flac", ios_base::binary);
	ouverture_fichier = myfile.is_open();
	
	if(ouverture_fichier == true)
    {
        /* write log file */
        ecrit_fichier_log("OK : FICHIER AUDIO OUVERT");
        ecrit_fichier_log("SUITE APPLICATION........");
        //cout << "OK : FICHIER AUDIO OUVERT" << endl ;
		
		//EXTRACTION DES PREMIERES LIGNES DU FICHIER :
        for(short l=0; l<4096; l++)
        {
            caract=myfile.get();
            taglines+=caract;
        }

		//RECHERCHE DES TAGS STANDARDS :
        for ( numero = 6; numero < NB_MAX_TAGS; numero = numero + 2 )
        {
            trouve=taglines.find(tags_std[numero]);
            if(trouve!=string::npos)
            {
                cout << tags_std[numero] << " : OK ! " ;
                posegal=trouve+tags_std[numero].length();
                boucle=0;
                do
                {
                    caract2=taglines.substr(posegal+1+boucle++,1);
                    caract3=caract2.c_str();
                    tags_contents[numero]+=caract3;
                }
                while(*caract3!=0x00);
                tags_contents[numero].resize(tags_contents[numero].length()-1);
                cout<<"*"<<tags_contents[numero]<<"*"<<endl;
            }
        }

        myfile.close();
        ecrit_fichier_log("OK : FICHIER AUDIO FERME");

        insert_file();
    }
    else
    {
        /* open log file */
        ecrit_fichier_log("ERR : FICHIER AUDIO NON OUVERT");
        ecrit_fichier_log("APPLICATION INTERROMPUE.......");
        cout << "ERR : FICHIER AUDIO NON OUVERT" << endl ;
        cout << "APPLICATION INTERROMPUE......." << endl ;
    }

    return 0;
}

void insert_file()
{
    /* open tags file */
    FILE * fichier_tags ;
    fichier_tags = fopen("fichier_tags.txt","wt");

    if( fichier_tags == NULL )
    {
        /* open .txt tags file */
        ecrit_fichier_log("ERR : fichier_tags.txt NON OUVERT");
        fprintf(stderr, "Can't open file: %s\n", "fichier_tags.txt");
        exit(0);
    }
    else
    {
        /* write .txt tags file */
        ecrit_fichier_log("OK : fichier_tags.txt OUVERT");
        fprintf(stdout, "Opened file successfully\n");

        for(short indice = 0; indice <=14 ; indice++)
        {
            fputs(tags_std[indice].c_str(),fichier_tags);
            fputs("\t\t\t",fichier_tags);
            fputs(tags_contents[indice].c_str(),fichier_tags);
            fputs("\n",fichier_tags);
        }

        fclose(fichier_tags);
        ecrit_fichier_log("OK : fichier_tags.txt FERME");
        ecrit_fichier_log("OK : FIN DU PROGRAMME");

    }
    return ;
}

void ecrit_fichier_log(string a_ecrire)
{
    FILE * log_file = fopen("fichier_tags.log","at");
    fputs(a_ecrire.c_str(),log_file);
    fputs("\n",log_file);
    fclose(log_file);
}
