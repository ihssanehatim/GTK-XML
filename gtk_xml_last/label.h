#include"biblio.h"

typedef struct Mylabel
{
    GtkWidget *objet; /// label (widget)
    int nblignemin,nblignemax,nbcolonnemin,nbcolonnemax;
    gchar *text; /// le champs a afficher ;
    int alignement; /// justify ::
    /**
       case 0 : GTK_JUSTIFY_LEFT
       case 1 : GTK_JUSTIFY_RIGHT
       case 2 : GTK_JUSTIFY_CENTER
       case 3 : GTK_JUSTIFY_FILL
       default :GTK_JUSTIFY_LEFT
    **/
    gchar *style;/// style="gras"
    /**
        gras;
        souligne;
        big;
        barre;
        italique;
    **/
    gchar *color;
    /**
        la meme chose que html : color="black" ; color="white";
    **/
    gchar *background; /// comme color ;
    int expand; /// pour indiquer la position dans le tab
    /**
    0: centré au milieu
    xoptions = GTK_EXPAND
    yoptions = GTK_EXPAND

    1:occupe toute la zone ms hi f ttol
    xoptions = GTK_EXPAND | GTK_FILL
    yoptions = GTK_EXPAND

    2:occupe toute la zone ms f l hauteur
    xoptions = GTK_EXPAND
    yoptions = GTK_EXPAND | GTK_FILL

    3:occupe toute la zone
    xoptions = GTK_EXPAND | GTK_FILL
    yoptions = GTK_EXPAND | GTK_FILL
    */
}Mylabel;


void fixeObjetDansTable(GtkWidget *table,GtkWidget *objet,int left,int right,int top,int bottom,int expand)
{
    switch(expand)
    {
        case 0: gtk_table_attach(table,objet,left,right,top,bottom,GTK_EXPAND,GTK_EXPAND,0,0);
                break;
        case 1: gtk_table_attach(table,objet,left,right,top,bottom,GTK_EXPAND|GTK_FILL,GTK_EXPAND,0,0);
                break;
        case 2: gtk_table_attach(table,objet,left,right,top,bottom,GTK_EXPAND,GTK_EXPAND | GTK_FILL,0,0);
                break;
        case 3: gtk_table_attach(table,objet,left,right,top,bottom, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
                break;
        default :
                gtk_table_attach(table,objet,left,right,top,bottom,GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
                break;
    }
}


//////////////////////////////////////////////////////////////////////
/** remplir la structure depuis le fichier XML :: **/
/** put the root child and the variable to be set */
Mylabel* initialiser_label(Mylabel *label,xmlNode *label_xml)
{
    int nb=0;
    xmlChar *prop;
    label=(Mylabel*)malloc(sizeof(Mylabel));
     if(!label)
    {
        printf("\n erreur");
        exit(1);
    }

    ////////////////////////////////////////
    prop=xmlGetProp(label_xml,"text");
    if(prop)
    {
        label->text=(char *)malloc(strlen((char *)prop)*sizeof(char));
         strcpy(label->text,(char *)prop);
        prop=NULL;
    }

    ////////////////////////////////////////
    prop=xmlGetProp(label_xml,"alignement");
    if(prop)
        {
            int justify=(int)atoi((char*)prop);
            label->alignement=justify;
            prop=NULL;
        }
    else
        label->alignement=0;
    //////////////////////////////////////////
    prop=xmlGetProp(label_xml,"color");
    if(prop)
    {
        label->color=(char *)malloc(sizeof(char));
        strcpy(label->color,(char *)prop);
        prop=NULL;
    }
    else
    {
       label->color=NULL;
    }


    //////////////////////////////////////////
    prop=xmlGetProp(label_xml,"background");
    if(prop)
    {
        label->background=(char*)malloc(sizeof(char));
        strcpy(label->background,(char *)prop);
        prop=NULL;
    }
    else
        label->background=NULL;
    /////////////////////////////////////////
    prop=xmlGetProp(label_xml,"style");
     if(prop)
     {
         label->style=(char*)malloc(sizeof(char));
         strcpy(label->style,(char *)prop);
         prop=NULL;
     }
    else
        label->style=NULL;
    /////////////////////////////////////////
    prop=xmlGetProp(label_xml,"nblignemax");
    nb=(int)atoi((char*)prop);
    label->nblignemax=nb;
    /////////////////////////////////////////
    prop=xmlGetProp(label_xml,"nblignemin");
     nb=(int)atoi((char*)prop);
    label->nblignemin=nb;
    /////////////////////////////////////////
    prop=xmlGetProp(label_xml,"nbcolonnemax");
     nb=(int)atoi((char*)prop);
    label->nbcolonnemax=nb;
    //////////////////////////////////////////
    prop=xmlGetProp(label_xml,"nbcolonnemin");
     nb=(int)atoi((char*)prop);
    label->nbcolonnemin=nb;
    ///////////////////////////////////////////
    prop=xmlGetProp(label_xml,"expand");
    if(prop)
     {
        nb=(int)atoi((char*)prop);
        label->expand=nb;
     }
     else
         label->expand=3;/// par defaut occupe toute la zone
         label->objet=NULL;

         return label;

}
/////////////////////////////////////////////////////////////////////////////////////
/** cette fonction pour ajouter du style (rendre le texte en gras ou italique ..)**/
/////////////////////////////////////////////////////////////////////////////////////
void add_start_end(gchar *str,gchar *toadd,gchar *newstr)
{
    gchar *tab=(gchar *)malloc(sizeof(gchar));

    if(!strcmp(toadd,"gras"))
    {
        strcpy(tab,"<b>");  /// <b>
        strcat(tab,str);    /// <b> str
        strcat(tab,"</b>"); /// <b> str </b>
        strcpy(newstr,tab); /// <b> str </b>
    }
    if(!strcmp(toadd,"souligne"))
    {
        strcpy(tab,"<u>");  /// <u>
        strcat(tab,str);    /// <u> str
        strcat(tab,"</u>"); /// <u> str </u>
        strcpy(newstr,tab); /// <u> str </u>
    }
    if(!strcmp(toadd,"big"))
    {
        strcpy(tab,"<big>");
        strcat(tab,str);
        strcat(tab,"</big>");
        strcpy(newstr,tab);
    }
    if(!strcmp(toadd,"barre"))
    {
        strcpy(tab,"<s>");
        strcat(tab,str);
        strcat(tab,"</s>");
        strcpy(newstr,tab);
    }
    if(!strcmp(toadd,"italique"))
    {
        strcpy(tab,"<i>");
        strcat(tab,str);
        strcat(tab,"</i>");
        strcpy(newstr,tab);
    }
}
////////////////////////////////////////////////////////
/** passer la couleur et le texte et recuperer la nouvelle balise*/
void add_bgcolor_label(gchar *str,gchar *bgcolor,gchar *newstr)
{
    strcpy(newstr,"<span background=\"");
    strcat(newstr,bgcolor);
    strcat(newstr,"\" >");
    strcat(newstr,str);
    strcat(newstr,"</span>"); /// fermer la balise
}
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/** passer la couleur et le texte et recuperer la nouvelle balise*/
void add_color_label(gchar *str,gchar *color,gchar *newstr)
{
    strcpy(newstr,"<span foreground=\"");
    strcat(newstr,color);
    strcat(newstr,"\" >");
    strcat(newstr,str);
    strcat(newstr,"</span>"); /// fermer la balise
}
/////////////////////////////////////////////////////////
/**create the label (without puting it into the window)
the label shall be created in the table (his parent)
**/
void create_label(Mylabel *label,GtkWidget *table)
{
    /// initialiser label with the text ::
    label->objet=gtk_label_new(label->text);

    /// justify text ::
            switch(label->alignement)
                {
                    case 0 : gtk_label_set_justify(GTK_LABEL(label->objet), GTK_JUSTIFY_LEFT);
                            break;
                    case 1 : gtk_label_set_justify(GTK_LABEL(label->objet), GTK_JUSTIFY_RIGHT);
                            break;
                    case 2 : gtk_label_set_justify(GTK_LABEL(label->objet), GTK_JUSTIFY_CENTER);
                            break;
                    case 3 : gtk_label_set_justify(GTK_LABEL(label->objet), GTK_JUSTIFY_FILL);
                            break;
                    default : gtk_label_set_justify(GTK_LABEL(label->objet), GTK_JUSTIFY_LEFT);
                              break;
                }
    /// style ::  gras ;souligne; big; barre; italique;
    if(label->style)
    {
        add_start_end(label->text,label->style,label->text); /// le texte contient le nouveau style
        gtk_label_set_markup(label->objet,label->text);
    }
    /// color :ex: color="black"
    if(label->color)
    {
        add_color_label(label->text,label->color,label->text);
        gtk_label_set_markup(label->objet,label->text);
    }
    fixeObjetDansTable(table,label->objet,label->nbcolonnemin,label->nbcolonnemax,
    label->nblignemin,label->nblignemax,label->expand);
}

