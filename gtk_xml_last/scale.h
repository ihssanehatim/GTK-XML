#include "biblio.h"
enum {
    POS_LEFT ,POS_RIGHT,POS_TOP,POS_BOTTOM
     };

enum {
    vscale,hscale
     };

typedef struct sc
{
    GtkWidget *objet;
    gdouble min;
    gdouble max;
    gdouble step;
    gint type;// vscale,hscale
    gboolean label;
    gint poslabel;
    int lMin,lMax,cMin,cMax;
}scale;

scale* initScale(xmlNode *widgetNode)
{
    xmlChar *propertyContent=NULL;
    scale *sc=(scale*)malloc(sizeof(scale));
    if(!sc)
    {
        printf("\n erreur dans l'alocation de scale");
        EXIT_FAILURE;
    }
    ///la valeur minimal
     propertyContent = xmlGetProp(widgetNode,"min");
     sc->min=(int)atoi((char*)propertyContent);
     propertyContent=NULL;

    ///la valeur maximal
     propertyContent = xmlGetProp(widgetNode,"max");
     sc->max=(int)atoi((char*)propertyContent);
     propertyContent=NULL;

     ///step
     propertyContent = xmlGetProp(widgetNode,"step");
     sc->step=(int)atoi((char*)propertyContent);
     propertyContent=NULL;


    ///type horizontal|vertical
     propertyContent = xmlGetProp(widgetNode,"type");
     sc->type=(int)atoi((char*)propertyContent);
     propertyContent=NULL;

     ///label
     propertyContent = xmlGetProp(widgetNode,"label");
     sc->label=(int)atoi((char*)propertyContent);
     propertyContent=NULL;

      ///position de label
     propertyContent = xmlGetProp(widgetNode,"pos_label");
     sc->poslabel=(int)atoi((char*)propertyContent);
     propertyContent=NULL;

      /*****position dans la fenetre****/
      propertyContent = xmlGetProp(widgetNode,"nblignemin");
      sc->lMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nblignemax");
      sc->lMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemin");
      sc->cMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemax");
      sc->cMax=(int)atoi((char*)propertyContent);

      sc->objet=NULL;

      return sc;

}


void creerScale(scale *sc)
{
    if(!sc)
    {
        printf("\n erreur dans creer scale");
        EXIT_FAILURE;
    }

    if(sc->max && sc->step)
    {
        switch(sc->type)
        {
            case vscale :
                sc->objet=gtk_vscale_new_with_range(sc->min, sc->max, sc->step);
                break;
            case hscale :
                sc->objet=gtk_hscale_new_with_range(sc->min, sc->max, sc->step);
                break;
            default :
                sc->objet=gtk_hscale_new_with_range(sc->min, sc->max, sc->step);
                break;
        }
    }
    else
    {
        sc->objet=gtk_hscale_new_with_range(0, 0, 0);
    }
    if(!sc->label)
        gtk_scale_set_draw_value(GTK_SCALE(sc->objet), FALSE);
    if(sc->poslabel != -1)
    {
        switch(sc->poslabel)
        {
            case POS_LEFT :
                gtk_scale_set_value_pos(GTK_SCALE(sc->objet), GTK_POS_LEFT);
                break;
            case POS_RIGHT :
                gtk_scale_set_value_pos(GTK_SCALE(sc->objet), GTK_POS_RIGHT);
                break;
            case POS_TOP :
                gtk_scale_set_value_pos(GTK_SCALE(sc->objet), GTK_POS_TOP);
                break;
            case POS_BOTTOM :
                gtk_scale_set_value_pos(GTK_SCALE(sc->objet), GTK_POS_BOTTOM);
                break;
        }
    }


}
