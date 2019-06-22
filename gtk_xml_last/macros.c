#include <stdio.h>
#include <gtk/gtk.h>
#include <libxml/tree.h>
#include <libxml/parser.h>


/*******creer fenetre********/

GtkWidget* creerFenetre(xmlNode *node)
{
    GtkWidget *fenetre;
    xmlChar *propertyContent;
    char* text;
    int nbr;

    propertyContent = xmlGetProp(node,"titre");
    strcpy(text, propertyContent);
    propertyContent = xmlGetProp(node,"type");
    nbr=(int)atoi((char*)propertyContent);

    if(!nbr)
        fenetre=gtk_window_new(GTK_WINDOW_POPUP);
    else fenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    if(text)
        gtk_window_set_title(GTK_WINDOW(fenetre),text);
    else gtk_window_set_title(GTK_WINDOW(fenetre),"ma fenetre");
    return fenetre;
}
