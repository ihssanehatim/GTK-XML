#include "biblio.h"


typedef struct lstitm
{
    int type;
    char *nm;//nom
    int gp;//nouveau groupe de boutons radio
    struct lstitm *suivant;
}lstitm;

typedef struct Menu
{
    char *name;
    lstitm *itm;//liste des items du menu
}Menu;


Menu *lecture(xmlNode *widgetNode)
{
        Menu *mn=NULL;
        xmlChar *propertyContent;
        propertyContent = xmlGetProp(widgetNode,"nom");
        mn = (Menu*)malloc(sizeof(Menu));
        if(!mn) EXIT_FAILURE;
        mn->itm == NULL;
        mn->name = (char*)malloc(strlen((const char *)propertyContent)*sizeof(char));
        strcpy(mn->name,((const char *)propertyContent));

        xmlNode *child = widgetNode->children;
        int i = 0;
        for(; child; child = child->next)
        {
            if((!xmlStrcmp(child->name,"item")))
            {
                if(i==0)
                {
                    i=1;
                    mn->itm = (lstitm*)malloc(sizeof(lstitm));
                    if(!mn->itm) EXIT_FAILURE;

                    mn->itm->nm = NULL;
                    int nbr;
                    propertyContent = xmlGetProp(child,"type");
                    nbr = atoi((char*)propertyContent);
                    mn->itm->type = nbr;
                    if(nbr != 4 && nbr != 5)
                    {
                        propertyContent = xmlGetProp(child,"nom");
                        mn->itm->nm = (char*)malloc(strlen((const char *)propertyContent)*sizeof(char));
                        strcpy(mn->itm->nm,((const char *)propertyContent));
                        if(nbr == 3)
                        {
                            propertyContent = xmlGetProp(child,"new");
                            nbr = atoi((char*)propertyContent);
                            mn->itm->gp = nbr;
                        }
                    }
                    mn->itm->suivant = NULL;
                }
                else
                {
                    lstitm *tmp;
                    tmp = (lstitm*)malloc(sizeof(lstitm));
                    if(!tmp) EXIT_FAILURE;
                    tmp->nm = NULL;
                    int nbr;
                    propertyContent = xmlGetProp(child,"type");
                    nbr = atoi((char*)propertyContent);
                    tmp->type = nbr;
                    if(nbr != 4 && nbr != 5)
                    {
                        propertyContent = xmlGetProp(child,"nom");
                        tmp->nm = (char*)malloc(strlen((const char *)propertyContent)*sizeof(char));
                        strcpy(tmp->nm,((const char *)propertyContent));
                        if(nbr == 3)
                        {
                            propertyContent = xmlGetProp(child,"new");
                            nbr = atoi((char*)propertyContent);
                            tmp->gp = nbr;
                        }
                    }
                    tmp->suivant = NULL;
                    lstitm *c;
                    c = mn->itm;
                    while(c->suivant)
                        c = c->suivant;
                    c->suivant = tmp;
                }
            }
        }
        return mn;

}

GtkWidget *creation(Menu *mn,GtkWidget *barmenu)
{
    if(!mn) EXIT_FAILURE;
//    GtkWidget *barmenu = gtk_menu_bar_new(); ///Should be declared in the main, so we can create new menus
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *item;
    GList *plist = NULL;
    lstitm *p;
    p = mn->itm;
    while(p)
    {
        int nbr = p->type;
        switch(nbr)
        {
            case 0: item = gtk_menu_item_new_with_label((const gchar*)p->nm);
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item); break;
            case 1: item = gtk_image_menu_item_new_from_stock((const gchar*)p->nm,NULL);
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item); break;
            case 2: item = gtk_check_menu_item_new_with_label((const gchar*)p->nm);
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item); break;
            case 3: if(p->gp) plist = NULL;
                    item = gtk_radio_menu_item_new_with_label(plist, (const gchar*)p->nm);
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
                    plist = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(item)); break;
            case 4: item = gtk_separator_menu_item_new();
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); break;
            case 5: item = gtk_tearoff_menu_item_new();
                    gtk_menu_shell_append(GTK_MENU_SHELL(menu),item); break;
        }
        p = p->suivant;
    }
    item = gtk_menu_item_new_with_label((const gchar*)mn->name);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(barmenu), item);
    return barmenu;
}

