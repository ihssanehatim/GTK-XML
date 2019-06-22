#include "biblio.h"

typedef struct cellule
{
    GtkWidget *w;
    GtkWidget *b;
    struct all *suivant;
}cel;

typedef struct boite
{
    GtkWidget *bd;
    GtkWidget *table;
    gchar *name;
    int type, nbrl, nbrc;
}boite;

boite *init_boite_dialog(xmlNode *root)
{
    boite *b;
    b = (boite*)malloc(sizeof(boite));
    if(!b) EXIT_FAILURE;
    xmlChar *propertyContent;
    propertyContent = xmlGetProp(root,"nom");
    if(propertyContent)
    {
        b->name = (gchar*)malloc(strlen(propertyContent)*sizeof(gchar));
        strcpy(b->name,propertyContent);
    }
    else
        b->name = NULL;
    propertyContent = xmlGetProp(root,"type");
    b->type = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbrc");
    b->nbrc = atoi(propertyContent);
    propertyContent = xmlGetProp(root,"nbrl");
    b->nbrl = atoi(propertyContent);
    return b;
}

void create_boite_dialog(boite *b, xmlNode *root, cel *liste)
{
    xmlChar *prop;
    GtkWidget *p;
    int i = 0;
    switch(b->type)
    {
        case 1: b->bd = gtk_dialog_new_with_buttons(b->name,NULL,GTK_DIALOG_DESTROY_WITH_PARENT,NULL);break;
        default: b->bd = gtk_dialog_new_with_buttons(b->name,NULL,GTK_DIALOG_MODAL,NULL);break;
    }
    b->table = gtk_table_new(b->nbrl,b->nbrc,1);
    p =  gtk_dialog_get_content_area (GTK_DIALOG (b->bd));
    gtk_container_add (GTK_CONTAINER (p), b->table);
    for(; root->children; root->children = root->children->next)
    {
        if((!xmlStrcmp(root->children->name,"boutton")))
        {
            prop = xmlGetProp(root->children,"name");
            i = xmlGetProp(root->children,"type");
            switch(i)
            {
                case 1: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_ACCEPT);break;
                case 2: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_APPLY);break;
                case 3: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_CANCEL);break;
                case 4: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_CLOSE);break;
                case 5: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_DELETE_EVENT);break;
                case 6: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_HELP);break;
                case 7: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_NO);break;
                case 8: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_OK);break;
                case 9: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_REJECT);break;
                case 10: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_YES);break;
                default: gtk_dialog_add_button(b->bd,prop,GTK_RESPONSE_NONE);break;
            }
        }
        else if((!xmlStrcmp(root->children->name,"chekboutton")))
        {
            CheckBouton *chekbtn;
		    chekbtn=initCheckBouton(root->children);
		    creerCheckBouton(chekbtn);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(b->table),chekbtn->btn,chekbtn->cMin,chekbtn->cMax,
                                      chekbtn->lMin,chekbtn->lMax);
        }
        else if((!xmlStrcmp(root->children->name,"image")))
        {
            Myimage *image;
            image=(Myimage*)malloc(sizeof(Myimage));
            initialiser_image(image,root->children);
            create_image(*image,b->table);
        }
        else if((!xmlStrcmp(root->children->name,"label")))
        {
            Mylabel *label;
            label=initialiser_label(label,root->children);
            create_label(label,b->table);
        }
        else if((!xmlStrcmp(root->children->name,"zone")))
        {
            zone *mazone=initialiser_zoneText(root->children);
            gtk_table_attach_defaults(GTK_TABLE(b->table),mazone->scrool,mazone->cMin,mazone->cMax,
                                      mazone->lMin,mazone->lMax);
        }
        else if((!xmlStrcmp(root->children->name,"combobox")))
		{
		    combobox *cb;
		    cb=initCbox(root->children);
            creerCBox(cb);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(b->table),cb->objet,cb->cMin,cb->cMax,
                                      cb->lMin,cb->lMax);
		}
		else if((!xmlStrcmp(root->children->name,"scale")))
		{
		    scale *sc;
		    sc=initScale(root->children);
            creerScale(sc);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(b->table),sc->objet,sc->cMin,sc->cMax,
                                      sc->lMin,sc->lMax);
		}
		else if((!xmlStrcmp(root->children->name,"entry")))
		{
		    entry *input;
		    input=initEntree(root->children);
            creerEntree(input);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(b->table),input->input,input->cMin,input->cMax,
                                      input->lMin,input->lMax);
		}
		else if(!(!xmlStrcmp(root->children->name,"text")))
            extractWidgetProperty(root->children,b->table,liste);
    }
}







