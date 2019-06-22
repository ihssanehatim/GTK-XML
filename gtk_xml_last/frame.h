#include "biblio.h"

typedef struct frame
{
    GtkWidget *object;
    GtkWidget *table;
    gchar *title;
    int style;
    int lmin, lmax, cmin, cmax;
    int nbrl, nbrc;
}frame;

frame *init_frame(xmlNode *root)
{
    frame *f;
    f = (frame*)malloc(sizeof(frame));
    if(!f) EXIT_FAILURE;
    xmlChar *propertyContent;
    propertyContent = xmlGetProp(root,"titre");
    if(propertyContent)
    {
        f->title = (gchar*)malloc(strlen(propertyContent)*sizeof(gchar));
        strcpy(f->title,propertyContent);
    }
    else
        f->title = NULL;
    propertyContent = xmlGetProp(root,"style");
    if(propertyContent)
        f->style = atoi(propertyContent);
    else
        f->style = 0;
    propertyContent = xmlGetProp(root,"nblignemin");
    if(propertyContent)
        f->lmin = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nblignemax");
    if(propertyContent)
        f->lmax = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbcolonnemin");
    if(propertyContent)
        f->cmin = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbcolonnemax");
    if(propertyContent)
        f->cmax = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbligne");
    f->nbrl = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbcolonne");
    f->nbrc = atoi(propertyContent);
    return f;
}

void create_frame(frame *f)
{
    f->object = gtk_frame_new(f->title);
    switch(f->style)
    {
        case 1: gtk_frame_set_shadow_type(f->object, GTK_SHADOW_NONE); break;
        case 2: gtk_frame_set_shadow_type(f->object, GTK_SHADOW_IN); break;
        case 3: gtk_frame_set_shadow_type(f->object, GTK_SHADOW_OUT); break;
        case 4: gtk_frame_set_shadow_type(f->object, GTK_SHADOW_ETCHED_OUT); break;
        default: gtk_frame_set_shadow_type(f->object, GTK_SHADOW_ETCHED_IN); break;
    }
    f->table = gtk_table_new(f->nbrl, f->nbrc, 1);
    gtk_container_add(f->object, f->table);
}











