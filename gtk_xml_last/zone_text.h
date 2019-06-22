#include "biblio.h"



typedef struct zone
{
  GtkWidget *zonetext;
  GtkWidget *scrool;
  GtkTextBuffer *buf;
  GtkTextIter debut;
  GtkTextIter fin;
  gchar *text;
  int lMin,lMax,cMin,cMax,expand;
}zone;

void saisie(GtkButton *btn,zone *mazone)
{
    mazone->buf=gtk_text_view_get_buffer(GTK_TEXT_VIEW(mazone->zonetext));
    gtk_text_buffer_get_start_iter(mazone->buf,&mazone->debut);
    gtk_text_buffer_get_end_iter(mazone->buf,&mazone->fin);
    mazone->text=gtk_text_buffer_get_text(mazone->buf,&mazone->debut,&mazone->fin,TRUE);
    printf("%s",mazone->text);
}

zone *initialiser_zoneText(xmlNode *widgetNode)
{

    zone *mazone=NULL;
    xmlChar *prop;
    mazone=(zone*)malloc(sizeof(zone));
    if(!mazone)
    {
        exit(0);
    }

      prop = xmlGetProp(widgetNode,"nblignemin");
      mazone->lMin = (int)atoi((char*)prop);
      prop = xmlGetProp(widgetNode,"nblignemax");
      mazone->lMax = (int)atoi((char*)prop);
      prop = xmlGetProp(widgetNode,"nbcolonnemin");
      mazone->cMin = (int)atoi((char*)prop);
      prop = xmlGetProp(widgetNode,"nbcolonnemax");
      mazone->cMax = (int)atoi((char*)prop);
      prop = xmlGetProp(widgetNode,"expand");
      mazone->expand = (int)atoi((char*)prop);
      mazone->zonetext=gtk_text_view_new();
      mazone->scrool=gtk_scrolled_window_new(NULL,NULL);
      gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mazone->scrool),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
      gtk_container_add(GTK_CONTAINER(mazone->scrool),mazone->zonetext);
    return mazone;
      //fixeObjetDansTable(table,zt->zonetext,zt->cMax,zt->cMin,zt->lMin,zt->lMax,zt->expand);
}


