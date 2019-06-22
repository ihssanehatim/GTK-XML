#include "biblio.h"
enum {espace, quitter, enregistrer, nouveau, ouvrir};

typedef struct barre
{
    GtkWidget *BO;
    int type,pos,lMin,lMax,cMin,cMax,expand;

}barre;

barre *initialiser_BO(xmlNode *widgetNode)
{
    xmlChar *propertyContent;
    barre *mabarre=(barre*)malloc(sizeof(barre));
    if(!mabarre)
        exit(0);
        propertyContent=xmlGetProp(widgetNode,"type");
            mabarre->type=(int)atoi((char*)propertyContent);
            propertyContent=xmlGetProp(widgetNode,"position");
            mabarre->pos=(int)atoi((char*)propertyContent);
            /*****position dans la fenetre****/
            propertyContent = xmlGetProp(widgetNode,"nblignemin");
            mabarre->lMin=(int)atoi((char*)propertyContent);
            propertyContent = xmlGetProp(widgetNode,"nblignemax");
            mabarre->lMax=(int)atoi((char*)propertyContent);
            propertyContent = xmlGetProp(widgetNode,"nbcolonnemin");
            mabarre->cMin=(int)atoi((char*)propertyContent);
            propertyContent = xmlGetProp(widgetNode,"nbcolonnemax");
            mabarre->cMax=(int)atoi((char*)propertyContent);
    mabarre->BO=gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(mabarre->BO),GTK_TOOLBAR_ICONS);
    return mabarre;
}

void creer_BO(barre *mabarre)
{
    GtkToolItem *bouton;
    switch(mabarre->type)
    {
    case espace :
        bouton=gtk_separator_tool_item_new();
        gtk_toolbar_insert(GTK_TOOLBAR(mabarre->BO),bouton,mabarre->pos);
        break;

    case quitter :
        bouton=gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
        gtk_toolbar_insert(GTK_TOOLBAR(mabarre->BO),bouton,mabarre->pos);
       g_signal_connect(G_OBJECT(bouton), "clicked", G_CALLBACK(gtk_main_quit),NULL);
        break;

    case enregistrer :
        bouton=gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
        gtk_toolbar_insert(GTK_TOOLBAR(mabarre->BO),bouton,mabarre->pos);
        break;

    case nouveau :
        bouton=gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
        gtk_toolbar_insert(GTK_TOOLBAR(mabarre->BO),bouton,mabarre->pos);
        break;

    case ouvrir :
        bouton=gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
        gtk_toolbar_insert(GTK_TOOLBAR(mabarre->BO),bouton,mabarre->pos);
        break;
    }
}
