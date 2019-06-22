#include"biblio.h"

enum {
        PPOS_LEFT,PPOS_RIGHT,PPOS_BOTTOM,PPOS_TOP
        };

typedef struct note
{
    GtkWidget *objet;
    int lMin,lMax,cMin,cMax,homo;
    int position;
    int scrol; ///0:false ; 1:true
}notebook;


notebook* init_notebook(xmlNode *root)
{
    notebook *note;
    note=(notebook*)malloc(sizeof(notebook));
    if(!root)
    {
        printf("\n erreur noteBook");
        EXIT_FAILURE;
    }
    xmlNode *widgetNode = root->children;
    xmlChar *propertyContent=NULL;

    ///position de menu
    propertyContent = xmlGetProp(root,"postion");
    note->position=(int)atoi((char*)propertyContent);
    propertyContent=NULL;
    printf("\n pos:%d",note->position);

    ///position de menu
    propertyContent = xmlGetProp(root,"scrol");
    note->scrol=(int)atoi((char*)propertyContent);
    propertyContent=NULL;

    /*****position dans la fenetre****/
      propertyContent = xmlGetProp(root,"nblignemin");
      note->lMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nblignemax");
      note->lMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nbcolonnemin");
      note->cMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nbcolonnemax");
      note->cMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"homo");
      note->homo=(int)atoi((char*)propertyContent);

    note->objet=NULL;
    return note;
}

void creer_note(notebook *note)
{

    if(!note)
    {
        printf("\n erreur creation notebook");
         exit(2);
    }
     /* Creation du GtkNotebook */
    note->objet = gtk_notebook_new();
    /* Position des onglets : en bas */
    switch(note->position)
        {
        case PPOS_BOTTOM:
            gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note->objet), GTK_POS_BOTTOM);
            break;
         case PPOS_LEFT:
            gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note->objet), GTK_POS_LEFT);
            break;
         case PPOS_RIGHT:
            gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note->objet), GTK_POS_RIGHT);
            break;
         case PPOS_TOP:
            gtk_notebook_set_tab_pos(GTK_NOTEBOOK(note->objet), GTK_POS_TOP);
            break;
        }
    /* Ajout des boutons de navigation */
    if(note->scrol)
        gtk_notebook_set_scrollable(GTK_NOTEBOOK(note->objet), TRUE);
    else
         gtk_notebook_set_scrollable(GTK_NOTEBOOK(note->objet), FALSE);

}
