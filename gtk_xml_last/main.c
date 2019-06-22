#include <stdio.h>
#include <gtk/gtk.h>
#include "window.h"
#include "xmlParser.c"

int main(int argc,char **argv)
{
    //  Initialisation de GTK
    window *win;
    cel *list;
    list = NULL;
    gtk_init(&argc,&argv);

    //	Charge l'arborescence du fichier XML dans la memoire
	xmlDoc *doc = xmlReadFile("testgtk.xml",NULL,0);

	//	Verifier si le fichier a bien été chargé
	if(doc == NULL)
	{
		printf("Le fichier contenant les propriétés n'a pu être chargé");
		exit(1);
	}

	//	Retrouver le noeud pere
	xmlNode *root = xmlDocGetRootElement(doc);

	//verifier l'element root de xml
	if(xmlStrcmp(root->name,"fenetre"))
    {
        printf("\n erreur de syntaxe");
        exit(2);
    }

/*********************** initialiser fenetre*******************************/

    win=initialiser_window(root);
    create_window(win);
    extractWidgetProperty(root, win->table, list);
    gtk_widget_show_all(GTK_WINDOW(win->objet));
    gtk_main();
    return 0;
}
