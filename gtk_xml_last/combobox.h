#include "biblio.h"
#define MaxElem 10

typedef struct cb
{
    GtkWidget *objet;
    char *list[MaxElem];
    int der;
    int lMin,lMax,cMin,cMax;
}combobox;

combobox* initCbox(xmlNode *root)
{
    combobox *cb=(combobox*)malloc(sizeof(combobox));
    xmlNode *widgetNode = root->children;
    xmlChar *propertyContent=NULL;
    cb->der=0;
    for( ; widgetNode; widgetNode = widgetNode->next)
	{
        propertyContent = xmlGetProp(widgetNode,"designation");
        if(propertyContent)
        {
            cb->list[cb->der]=propertyContent;
            cb->der++;
        }
        propertyContent=NULL;
	}

     /*****position dans la fenetre****/
      propertyContent = xmlGetProp(root,"nblignemin");
      cb->lMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nblignemax");
      cb->lMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nbcolonnemin");
      cb->cMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(root,"nbcolonnemax");
      cb->cMax=(int)atoi((char*)propertyContent);

      cb->objet=NULL;
}

void creerCBox(combobox *cb)
{
    if(!cb)
    {
        printf("\n erreur dans creerCBox");
        EXIT_FAILURE;
    }
    cb->objet=gtk_combo_box_text_new ();
    int i;
    int maxE = cb->der;
  /* G_N_ELEMENTS is a macro which determines the number of elements in an array.*/
    for (i = 0; i < maxE; i++)
        {
         gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (cb->objet), cb->list[i]);
        }

      /* Choose to set the first row as the active one by default, from the beginning */
        gtk_combo_box_set_active (GTK_COMBO_BOX (cb->objet), 0);

}
