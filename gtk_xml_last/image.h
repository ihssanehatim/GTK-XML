#include"biblio.h"

typedef struct Myimage
{
    GtkWidget *objet ; /// l image (widget)
    int nblignemin,nblignemax,nbcolonnemin,nbcolonnemax;
    int expand;
    /// pour indiquer la position dans le tab
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
    gchar *path; /// le chemin vers l image
    gchar stock_id; /// stock_id="1"
    /**
    GTK_STOCK_QUIT   : 1
    GTK_STOCK_ADD    : 2
    GTK_STOCK_APPLY  : 3
    GTK_STOCK_ABOUT  : 4
    GTK_STOCK_CANCEL : 5
    GTK_STOCK_CLOSE  : 6
    GTK_STOCK_OK     : 7
    */
   // gchar size; /// size = "4" par defaut
    /**
    ce champs doit etre remplie ssi l image est from_stock ::
    GTK_ICON_SIZE_MENU          :1
    GTK_ICON_SIZE_SMALL_TOOLBAR :2
    GTK_ICON_SIZE_LARGE_TOOLBAR :3
    GTK_ICON_SIZE_BUTTON        :4
    GTK_ICON_SIZE_DND           :5
    GTK_ICON_SIZE_DIALOG        :6
    */
}Myimage;

//////////////////////////////////////////////////
/// image_xml est un node dans le fichier XML
/////////////////////////////////////////////////

void fixeObjetDansTable2(GtkWidget *table,GtkWidget *objet,int left,int right,int top,int bottom,int expand)
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

void initialiser_image(Myimage *image,xmlNode *image_xml)
{
    int nb=0;
    xmlChar *prop=(xmlChar*)malloc(sizeof(xmlChar));
    ////////////////////////////////////////////
    prop=xmlGetProp(image_xml,"path");
    if(prop)
    {
        image->path=(char *)malloc(sizeof(char));
        strcpy(image->path,prop);
    }

    ////////////////////////////////
    prop=NULL;
     prop=xmlGetProp(image_xml,"stock_id");
    if(prop)
        image->stock_id=prop; /// un seul caractere
     /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(image_xml,"nblignemax");
    nb=(int)atoi((char*)prop);
    image->nblignemax=nb;
    /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(image_xml,"nblignemin");
     nb=(int)atoi((char*)prop);
    image->nblignemin=nb;
    /////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(image_xml,"nbcolonnemax");
     nb=(int)atoi((char*)prop);
    image->nbcolonnemax=nb;
    //////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(image_xml,"nbcolonnemin");
     nb=(int)atoi((char*)prop);
    image->nbcolonnemin=nb;
    ///////////////////////////////////////////
    prop=NULL;
    prop=xmlGetProp(image_xml,"expand");
    if(prop)
     {
        image->expand=(int)atoi((char *)prop);
     }
     else
         image->expand=3;/// par defaut occupe toute la zone
}
/////////////////////////////////////////////////////////
/**create image (without puting it into the window)
the picture shall be created in the table (his parent)
**/
void create_image(Myimage image,GtkWidget *table)
{
    if(image.path)
        image.objet=gtk_image_new_from_file(image.path);
    else
        if(image.stock_id)

    /// je vais faire le size par defaut
            switch(image.stock_id)
            {
                case '1' :  gtk_image_new_from_stock(GTK_STOCK_QUIT,GTK_ICON_SIZE_BUTTON);
                            break;
                case '2' :  gtk_image_new_from_stock(GTK_STOCK_ADD,GTK_ICON_SIZE_BUTTON);
                            break;
                case '3' :  gtk_image_new_from_stock(GTK_STOCK_APPLY,GTK_ICON_SIZE_BUTTON);
                            break;
                case '4' :  gtk_image_new_from_stock(GTK_STOCK_ABOUT,GTK_ICON_SIZE_BUTTON);
                            break;
                case '5' :  gtk_image_new_from_stock(GTK_STOCK_CANCEL,GTK_ICON_SIZE_BUTTON);
                            break;
                case '6' :  gtk_image_new_from_stock(GTK_STOCK_CLOSE,GTK_ICON_SIZE_BUTTON);
                            break;
                case '7' :  gtk_image_new_from_stock(GTK_STOCK_OK,GTK_ICON_SIZE_BUTTON);
                            break;
            }
    fixeObjetDansTable2(table,image.objet,image.nbcolonnemin,image.nbcolonnemax,
    image.nblignemin,image.nblignemax,image.expand);
}

