#include"biblio.h"

typedef struct window
{
    GtkWidget *objet;
    int type;
    /**
    par defaut : 0
    top_level : 0
    pop_up    : 1
    */
    gchar *title;
    gchar *path_icon; /// par defaut pas d icon, si il existe icon=""
                        /// alors il doit etre le chemin vers l icon
    int position;
    /**
        0 :     GTK_WIN_POS_NONE : la fenêtre aura une position aléatoire lors de son affichage ;
        1 :     GTK_WIN_POS_CENTER : la fenêtre sera centrée à l'écran ;
        2 :     GTK_WIN_POS_MOUSE : le coin supérieur droit de la fenêtre correspondra à la position de la
                            souris au moment de l'affichage ;
        3 :     GTK_WIN_POS_CENTER_ALWAYS
    */
    gboolean resizable;
    /** par defaut : 1 : oui resizable */

    int background ;
    /**
        0 :black
        1 :white
        2 :red
        3 :green
        4 :blue
        5 :yellow
    */
    int height,width;

    GtkWidget *table; /// le tableau qui est dans la fenetre;

    int nbligne,nbcolonne,homo; /// les lignes et colonnes de tableau;
    int scroll; //ScrolBar
     GtkWidget *scr;
}window;
/// la valeur de "type" :

enum{WINDOW_TOPLEVEL,WINDOW_POPUP};

/// la valeur de "position" :

enum{WIN_POS_NONE,WIN_POS_CENTER,WIN_POS_MOUSE,WIN_POS_CENTER_ALWAYS};

/// les couleurs ::

enum {black ,white ,red ,green ,blue ,yellow} ;
//////////////////////////////////////////////////////////////////////////////////////////
/**remplir la structure ::
*/
/// on doit passer le nom du fichier qui contient le root pour construire la fenetre ::
window* initialiser_window(xmlNode *root)
{
    /// declaration of the window ::
    window *win;

    win = (window*)malloc(sizeof(window));
    win->scr=NULL;
    if(!win)
    {
        EXIT_FAILURE;
    }
    /////////////////////
    xmlChar *prop=xmlGetProp(root,"resizable");
    if(prop)
        win->resizable = (int) atoi((char *)prop);
    else
        win->resizable=1;
    ////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"title");
    if(prop)
    {
        win->title =(gchar *)malloc(sizeof(prop));

        strcpy(win->title,(char *) prop);
    }
    else
    {
        win->title =(gchar *)malloc(sizeof(prop));
        strcpy(win->title,"window GTK");
    }
    ///////////////////////
     prop=NULL;
     prop=xmlGetProp(root,"icon");
     if(prop)
     {
        win->path_icon=(gchar *)malloc(sizeof(prop));
        strcpy(win->path_icon,prop);
     }
     else
            win->path_icon=NULL;
     ///////////////////////
      prop=NULL;
     prop=xmlGetProp(root,"type");

     if(prop)
        win->type=(int )atoi((char *)prop);
    else
        win->type=0; /// par defaut toplevel
    ///////////////////////

      prop=NULL;
     prop=xmlGetProp(root,"position");
     if(prop)
        win->position=(int )atoi((char *)prop);
    else
        win->position=1; /// par defaut centrée
    ///////////////////////
        prop=NULL;
        prop=xmlGetProp(root,"width");
        if(prop)
        {
            win->width=(int)atoi((char *)prop);
        }
        else
            win->width=300;
    ///////////////////////
        prop=NULL;
        prop=xmlGetProp(root,"height");
        if(prop)
        {
            win->height=(int)atoi((char *)prop);
        }
        else
            win->height=500;
    /////////// le tableau ::

 /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"nbligne");
    win->nbligne=(int)atoi((char*)prop);
    /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"nbcolonne");
     win->nbcolonne=(int)atoi((char*)prop);

     /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"homo");
    win->homo=(int)atoi((char*)prop);

    ///////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"background");
    if(prop)
        win->background=(int)atoi((char*)prop);
    else
        win->background=1;
    ///////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(root,"scroll");
    if(prop)
        win->scroll=(int)atoi((char*)prop);
    else
        win->scroll=0;

 return win;
}
/***************creation de la fenetre *************************/////////////

void create_window(window *win)
{

    GdkColor c;
    c.pixel=1;
    switch(win->type)
        {
         case WINDOW_POPUP    : win->objet = gtk_window_new(GTK_WINDOW_POPUP);break;
         case WINDOW_TOPLEVEL : win->objet = gtk_window_new(GTK_WINDOW_TOPLEVEL);break;
         default:
             win->objet = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        }
    if(win->title)
        gtk_window_set_title(win->objet,win->title);
    else
        gtk_window_set_title(win->objet,"my window");

    if(win->path_icon)
        gtk_window_set_icon_from_file(GTK_WINDOW(win->objet),win->path_icon,NULL);
    if(!win->resizable) /// par defaut : resizable = 1
        gtk_window_set_resizable(win->objet,0);
        ////////////////////////////
    switch(win->position)
    {
        case WIN_POS_CENTER : gtk_window_set_position(win->objet,GTK_WIN_POS_CENTER);
                    break;
        case WIN_POS_CENTER_ALWAYS : gtk_window_set_position(win->objet,GTK_WIN_POS_CENTER_ALWAYS);
                    break;
        case WIN_POS_NONE : gtk_window_set_position(win->objet,GTK_WIN_POS_NONE);
                    break;
        case WIN_POS_MOUSE : gtk_window_set_position(win->objet,GTK_WIN_POS_MOUSE);
                    break;
        default : gtk_window_set_position(win->objet,GTK_WIN_POS_CENTER);
    }
    //////////////////////////////////SIZE ::
    gtk_window_set_default_size(win->objet,win->width,win->height);
    ///////////////////////////////
    switch(win->background)
    {
        case green : /// green
                    c.blue=c.red=0;
                    c.green=40000;
                    break;
        case blue : /// blue
                    c.blue=40000;
                    c.green=c.red=0;
                    break;
        case red : /// red
                    c.red=40000;
                    c.green=c.blue=0;
                    break;
        case black : /// black
                    c.blue=c.green=c.red=0;
                    break;
        default : /// white
                    c.blue=c.green=c.red=65025;
    }



        win->table=gtk_table_new(win->nbligne,win->nbcolonne,win->homo);
    if(win->scroll)
    {
        gtk_widget_modify_bg(win->objet,GTK_STATE_NORMAL,&c);
        win->scr=gtk_scrolled_window_new(NULL,NULL);
        gtk_container_add(win->objet,win->scr);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(win->scr),win->table);
    }
    else
    {
        gtk_container_add(win->objet,win->table);
         gtk_widget_modify_bg(win->objet,GTK_STATE_NORMAL,&c);
    }

        g_signal_connect(G_OBJECT(win->objet), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}
