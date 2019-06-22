#include "biblio.h"


enum {
    ENT_TEXT,ENT_MDP,ENT_LECTURE,ENT_CHAR_INVISBLE
     };

typedef struct Ent
{
    GtkWidget *input;
    gint  max;
    gchar *placeholder;
    gchar vChar; // lettre à afichier
    gint type; // text ou password
    int lMin,lMax,cMin,cMax;
} entry;


entry* initEntree(xmlNode *widgetNode)
{
    xmlChar *propertyContent=NULL;
    entry *entree=(entry *)malloc(sizeof(entry));
    if(!entree)
        exit(2);

    ///place holder
    propertyContent = xmlGetProp(widgetNode,"placeholder");
    entree->placeholder=propertyContent;
    propertyContent=NULL;

    ///type
    propertyContent = xmlGetProp(widgetNode,"type");
    entree->type=(int)atoi((char*)propertyContent);
    propertyContent=NULL;

    ///maximum
    propertyContent = xmlGetProp(widgetNode,"max");
    entree->max=(int)atoi((char*)propertyContent);
    propertyContent=NULL;

    ///le caractère visible
    propertyContent = xmlGetProp(widgetNode,"visible");
    entree->vChar=propertyContent;
    propertyContent=NULL;

    /*****position dans la fenetre****/
      propertyContent = xmlGetProp(widgetNode,"nblignemin");
      entree->lMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nblignemax");
      entree->lMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemin");
      entree->cMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemax");
      entree->cMax=(int)atoi((char*)propertyContent);
    entree->input=NULL;

    return entree;
}

void creerEntree(entry *entree)
{
    if(entree)
    {

        entree->input = gtk_entry_new();
        if(entree->placeholder)
            gtk_entry_set_placeholder_text(GTK_ENTRY(entree->input),entree->placeholder);

        if(entree->max)
            gtk_entry_set_max_length(GTK_ENTRY(entree->input),entree->max);

        switch(entree->type)
        {
            case ENT_TEXT:
                break;
            case ENT_MDP:
                gtk_entry_set_visibility(GTK_ENTRY(entree->input),FALSE);
                break;
            case ENT_CHAR_INVISBLE:
                    if(entree->vChar)
                        gtk_entry_set_invisible_char(GTK_ENTRY(entree->input),entree->vChar);
                    else
                        gtk_entry_set_invisible_char(GTK_ENTRY(entree->input),'*');
                break;
            case ENT_LECTURE:
                gtk_editable_set_editable (GTK_EDITABLE (entree->input),FALSE);
                break;
        }
    }

    return entree;
}

