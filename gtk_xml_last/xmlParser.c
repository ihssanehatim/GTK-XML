#include <stdio.h>
#include <gtk/gtk.h>
#include<gdk/gdk.h>
#include "boutton.h"
#include "label.h"
#include "entry.h"
#include "scale.h"
#include "combobox.h"
#include "zone_text.h"
#include "barre_outil.h"
#include "menu.h"
#include "image.h"
#include "notebook.h"
#include "frame.h"
#include "dialog.h"
#include "message.h"



cel *add_to_list(GtkWidget *wi, GtkWidget *bt, cel *list)
{
    cel *nv;
    if(!list)
    {
        list = (cel*)malloc(sizeof(cel));
        if(!list) EXIT_FAILURE;
        list->w = wi;
        list->b = bt;
        list->suivant = NULL;
        return list;
    }
    else
    {
        nv = (cel*)malloc(sizeof(cel));
        if(!nv) EXIT_FAILURE;
        nv->w = wi;
        nv->b = bt;
        nv->suivant = list;
        return nv;
    }
}

void display_signal(GtkWidget *bt, cel *list)
{
    cel *tmp;
    tmp = list;
    int fin = 0;
    while(tmp && !fin)
    {
        if(tmp->b == bt)
        {
            fin = 1;
        }
        else
            tmp = tmp->suivant;
    }
    if(!tmp)
        printf("Introuvable !");
    gtk_widget_show_all(tmp->w);
    //gtk_dialog_run(tmp->w);
    g_signal_connect(tmp->w, "delete-event", G_CALLBACK(gtk_widget_hide), NULL);
    gtk_main();
}

void extractWidgetProperty(xmlNode *root, GtkWidget *table, cel *list)
{

    xmlChar *propertyContent;
    char *text;
    int nbr,nbr2,nbr3,nbr4;
    GList *pGroup=NULL;
    GtkWidget *barmenu = gtk_menu_bar_new();
    int i=0;

/*********************parser le fichier **********************/

    xmlNode *widgetNode = root->children;
	for( ; widgetNode; widgetNode = widgetNode->next)
	{

        /************Boutton******************/
		if((!xmlStrcmp(widgetNode->name,"boutton")))
		{

		    Bouton *boutton;
		    boutton=initBouton(widgetNode);
		    creerButton(boutton);
		    if(boutton->sigal == 1)
            {
                window *win;
                win = NULL;
                win = initialiser_window(widgetNode->children->next);
                create_window(win);
                extractWidgetProperty(widgetNode->children->next,win->table, list);
                list = add_to_list(win->objet, boutton->btn, list);
                g_signal_connect(G_OBJECT(boutton->btn), "clicked", G_CALLBACK(display_signal), list);
            }
            else if(boutton->sigal == 2)
            {
                if((!xmlStrcmp(widgetNode->children->next->name,"boite_dialogue")))
                {
                    boite *b;
                    b = init_boite_dialog(widgetNode->children->next);
                    create_boite_dialog(b, widgetNode->children->next, list);
                    list = add_to_list(b->bd, boutton->btn, list);
                    g_signal_connect(G_OBJECT(boutton->btn), "clicked", G_CALLBACK(display_signal), list);
                }
            }
            else if(boutton->sigal == 3)
            {
                if((!xmlStrcmp(widgetNode->children->next->name,"boite_message")))
                {
                    msg *m;
                    m = init_msg(widgetNode->children->next);
                    create_msg(m);
                    list = add_to_list(m->mg, boutton->btn, list);
                    g_signal_connect(G_OBJECT(boutton->btn), "clicked", G_CALLBACK(display_signal), list);
                }
            }
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),boutton->btn,boutton->cMin,boutton->cMax,
                                      boutton->lMin,boutton->lMax);
		}
		/************chekBoutton******************/
		if((!xmlStrcmp(widgetNode->name,"chekboutton")))
		{

		    CheckBouton *chekbtn;
		    chekbtn=initCheckBouton(widgetNode);
		    creerCheckBouton(chekbtn);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),chekbtn->btn,chekbtn->cMin,chekbtn->cMax,
                                      chekbtn->lMin,chekbtn->lMax);
		}
		/************RadioBoutton******************/
		if((!xmlStrcmp(widgetNode->name,"radioboutton")))
		{
		    Radiobtn *bRadio;
		    bRadio=initRadioBouton(widgetNode);

            propertyContent = xmlGetProp(widgetNode,"new");
            nbr=(int)atoi((char*)propertyContent);
            ///si nbr==1 donc nv groupe sinon un membre du groupe
            if(nbr)
            {
                pGroup=creerRadioBouton(pGroup,bRadio);
            }
            else
            {
                pGroup=creerRadioBoutonGr(pGroup,bRadio);
            }
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),bRadio->btn,bRadio->cMin,bRadio->cMax,
                                      bRadio->lMin,bRadio->lMax);
		}

        if((!xmlStrcmp(widgetNode->name,"entry")))
		{
		    entry *input;
		    input=initEntree(widgetNode);
            creerEntree(input);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),input->input,input->cMin,input->cMax,
                                      input->lMin,input->lMax);
		}

        if((!xmlStrcmp(widgetNode->name,"scale")))
		{
		    scale *sc;
		    sc=initScale(widgetNode);
            creerScale(sc);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),sc->objet,sc->cMin,sc->cMax,
                                      sc->lMin,sc->lMax);
		}

		if((!xmlStrcmp(widgetNode->name,"combobox")))
		{
		    combobox *cb;
		    cb=initCbox(widgetNode);
            creerCBox(cb);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),cb->objet,cb->cMin,cb->cMax,
                                      cb->lMin,cb->lMax);
		}
		if((!xmlStrcmp(widgetNode->name,"zone")))
        {
            zone *mazone=initialiser_zoneText(widgetNode);
            gtk_table_attach_defaults(GTK_TABLE(table),mazone->scrool,mazone->cMin,mazone->cMax,
                                      mazone->lMin,mazone->lMax);

        }
        if((!xmlStrcmp(widgetNode->name,"barreoutil")))
        {
            barre *mabarre=initialiser_BO(widgetNode);
            creer_BO(mabarre);
            /****ajouter dans la fenetre*****/
            gtk_table_attach_defaults(GTK_TABLE(table),mabarre->BO,mabarre->cMin,mabarre->cMax
                                      ,mabarre->lMin,mabarre->lMax);

        }

            if((!xmlStrcmp(widgetNode->name,"menu")))
        {
            if(!i)
            {

                int cmax,lmax;
                gtk_table_get_size(table,&lmax,&cmax);
                gtk_table_attach_defaults(GTK_TABLE(table),barmenu,0,cmax,0,1);
                i=1;
            }
            Menu *menu=lecture(widgetNode);

            barmenu=creation(menu,barmenu);

        }
            /****ajouter dans la fenetre*****/

        if((!xmlStrcmp(widgetNode->name,"label")))
        {
            Mylabel *label;
            label=initialiser_label(label,widgetNode);
            create_label(label,table);
        }
        if((!xmlStrcmp(widgetNode->name,"image")))
        {
            Myimage *image;
            image=(Myimage*)malloc(sizeof(Myimage));
            initialiser_image(image,widgetNode);
            create_image(*image,table);
        }
        if((!xmlStrcmp(widgetNode->name,"note")))
        {
            notebook *note;
            note=init_notebook(widgetNode);
            creer_note(note);
            xmlNode *widgetNodepage = widgetNode->children;

                for( ; widgetNodepage; widgetNodepage = widgetNodepage->next)
                {
                    if((!xmlStrcmp(widgetNodepage->name,"page")))
                    {
                            char *titre;
                            GtkWidget *pTabLabel;
                            propertyContent = xmlGetProp(widgetNodepage,"designation");
                            titre=propertyContent;
                            pTabLabel = gtk_label_new(titre);
                            free(titre);

                            GtkWidget *tab;
                            tab=gtk_table_new((note->lMax-note->lMin),(note->cMax-note->cMin),note->homo);
                            extractWidgetProperty(widgetNodepage,tab, list);
                            gtk_notebook_append_page(GTK_NOTEBOOK(note->objet),tab,pTabLabel);
                    }
                }
            gtk_table_attach_defaults(GTK_TABLE(table),note->objet,note->cMin,note->cMax,note->lMin,note->lMax);

        }
        if((!xmlStrcmp(widgetNode->name,"frame")))
        {
            frame *f;
            f = init_frame(widgetNode);
            create_frame(f);
            extractWidgetProperty(widgetNode, f->table, list);
            gtk_table_attach_defaults(GTK_TABLE(table), f->object, f->cmin, f->cmax, f->lmin, f->lmax);
        }
    }
}






