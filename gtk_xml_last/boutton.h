#include "biblio.h"

/***********La structure d'un boutton************/
typedef struct Bout
{
    GtkWidget* btn;
    char * designation;
    int type; // label ou mnemonic
    int lMin,lMax,cMin,cMax;
    int sigal;
} Bouton;
///la valeur du type d'un boutton
enum {
    BTN_IMAGE,BTN_LABEL,BTN_MNEMONIC,BTN_ADD,BTN_DELETE,BTN_OPEN,
    BTN_CLOSE,BTN_ABOUT,BTN_FILECH, BTN_COLOR,BTN_FONTCH, BTN_APPLY
     };


/**********CheckBouton**********/
typedef Bouton CheckBouton;
///la valeur du type de chekboutton
enum {CHECK_BTN_NONE,CHECK_BTN_LABEL,CHECK_BTN_MNEMONIC};



/**********Radio Boutton********/

typedef Bouton Radiobtn;


///la valeur du type de RadioBoutton
enum {RADIO_BTN_NONE,RADIO_BTN_LABEL,RADIO_BTN_MNEMONIC};


/*******fichierExiste*********/
///Principe : pour verifier si une image existe
///ou non,
/// il reçoit le chemin de fichier comme parametre
///et qui retourner 1 si l'image existe 0 sinon
int fichierExiste(const char * filename)
{
    /* try to open file to read */
    FILE *file;
    if ((file = fopen(filename, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}


/*********initBouton**********/
///principe: lire les attribut d'une balise<boutton> d'un fichier xml
///et les stocker dans la structure de type bouton
///et qui reçoit comme paramètre une balise "xmlNode"
///retourner une structure de type boutton
Bouton *initBouton(xmlNode *widgetNode)
{
    Bouton *bouton=(Bouton *)malloc(sizeof(Bouton));
    xmlChar *propertyContent;
    if(!bouton)
    {
        exit(1);
    }
    /****** designation ******/
      propertyContent = xmlGetProp(widgetNode,"designation");
      bouton->designation=propertyContent;
    /****** type ******/
      propertyContent = xmlGetProp(widgetNode,"type");
      bouton->type=(int)atoi((char*)propertyContent);
    /*****position dans la fenetre****/
      propertyContent = xmlGetProp(widgetNode,"nblignemin");
      bouton->lMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nblignemax");
      bouton->lMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemin");
      bouton->cMin=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"nbcolonnemax");
      bouton->cMax=(int)atoi((char*)propertyContent);
      propertyContent = xmlGetProp(widgetNode,"signal");
      bouton->sigal=(int)atoi((char*)propertyContent);
      bouton->btn=NULL;

    return bouton;
}

/**********creerButton********/
///principe:creer boutone à partire d'une structure
void creerButton(Bouton *bouton)
{
    GtkWidget *img=NULL;

    if(bouton)
    {
        switch(bouton->type)
        {
        case BTN_LABEL:
            bouton->btn=gtk_button_new_with_label(bouton->designation);
            break;

        case BTN_MNEMONIC:
            bouton->btn=gtk_button_new_with_mnemonic(bouton->designation);
            break;

        case BTN_IMAGE:
            if (bouton->designation)
            {
                if(fichierExiste(bouton->designation))
                {
                    img=gtk_image_new_from_file(bouton->designation);
                    bouton->btn = gtk_button_new ();
                    gtk_button_set_image (GTK_BUTTON (bouton->btn), img);
                }
                else
                {
                    puts("Image n'existe pas");
                    bouton->btn=gtk_button_new_with_label("Img Btn er1");
                }
            }
            else
            {
                printf("Champ image non rempli");
                bouton->btn=gtk_button_new_with_label("Img Btn er2");
            }
            break;
        case BTN_ADD:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_ADD);
            break;
        //cas d'un bouton suppression
        case BTN_DELETE:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_DELETE);
            break;
        //cas d'un bouton ouverture
        case BTN_OPEN:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_OPEN);
            break;
        //cas d'un bouton fermeture
        case BTN_CLOSE:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
              g_signal_connect(G_OBJECT(bouton->btn), "clicked", G_CALLBACK(gtk_main_quit),NULL);
            break;
        //cas d'un bouton information
        case BTN_ABOUT:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
            break;
        case BTN_FILECH:
            bouton->btn = gtk_file_chooser_button_new("Parcourir ...",GTK_FILE_CHOOSER_ACTION_OPEN);
            break;
        case BTN_COLOR:
            bouton->btn = gtk_color_button_new();
            break;
        case BTN_FONTCH:
            bouton->btn = gtk_font_button_new();
            break;
        case BTN_APPLY:
            bouton->btn = gtk_button_new_from_stock(GTK_STOCK_APPLY);
            break;
        }
        if(!bouton->btn)
            exit(0);
    }
}


/*********Initialiser et cree chekboutton**********/
CheckBouton *initCheckBouton(xmlNode *widgetNode)
{
    return (CheckBouton *)initBouton(widgetNode);
}
void creerCheckBouton(CheckBouton *checkBouton)
{
    if(checkBouton)
    {
        switch(checkBouton->type)
        {
            case CHECK_BTN_NONE:
            checkBouton->btn = gtk_check_button_new();
                break;
            case CHECK_BTN_LABEL:
            checkBouton->btn = gtk_check_button_new_with_label(checkBouton->designation);
                break;
            case CHECK_BTN_MNEMONIC:
            checkBouton->btn = gtk_check_button_new_with_mnemonic(checkBouton->designation);
                break;
        }
    }
}

/*********Initialiser et cree bouttonRadio**********/


Radiobtn *initRadioBouton(xmlNode *widgetNode)
{
    return (Radiobtn *)initBouton(widgetNode);
}

/// cas du premier element d'un groupe

GList* creerRadioBouton(GList *list,Radiobtn *bRadio)
{
    if(bRadio)
    {
        switch(bRadio->type)
        {
            case RADIO_BTN_NONE:
            bRadio->btn=gtk_radio_button_new(NULL);
                break;
            case RADIO_BTN_LABEL:
            bRadio->btn=gtk_radio_button_new_with_label (NULL,bRadio->designation);
                break;
            case RADIO_BTN_MNEMONIC:
            bRadio->btn=gtk_radio_button_new_with_mnemonic_from_widget(NULL,bRadio->designation);
                break;
        }

    }

    list=NULL;
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(bRadio->btn));
    return list;
}


/// cas d'un membre d'un groupe

GList* creerRadioBoutonGr(GList *list,Radiobtn *bRadio)
{
    if(bRadio)
    {
        switch(bRadio->type)
        {
            case RADIO_BTN_NONE:
            bRadio->btn=gtk_radio_button_new(list);
                break;
            case RADIO_BTN_LABEL:
            bRadio->btn=gtk_radio_button_new_with_label (list,bRadio->designation);
                break;
            case RADIO_BTN_MNEMONIC:
            bRadio->btn=gtk_radio_button_new_with_mnemonic_from_widget(list,bRadio->designation);
                break;
        }

    }
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(bRadio->btn));
    return list;
}
