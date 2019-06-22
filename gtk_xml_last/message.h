#include "biblio.h"

typedef struct msg
{
    GtkWidget *mg;
    int type;
    char *txt;
}msg;

msg *init_msg(xmlNode *root)
{
    msg *m;
    m = (msg*)malloc(sizeof(msg));
    if(!m) EXIT_FAILURE;
    xmlChar *propertyContent;
    propertyContent = xmlGetProp(root,"type");
    if(propertyContent)
        m->type = atoi(propertyContent);
    else
        m->type = 0;
    propertyContent = xmlGetProp(root,"message");
    if(propertyContent)
    {
        m->txt = (char*)malloc(strlen(propertyContent)*sizeof(char));
        strcpy(m->txt, propertyContent);
    }
    else
        m->txt = NULL;
    return m;
}

void create_msg(msg *m)
{
    switch(m->type)
    {
        case 1: m->mg = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"%s",m->txt);break;
        case 2: m->mg = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK_CANCEL,"%s",m->txt);break;
        case 3: m->mg = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,
                                               "%s",m->txt);break;
        default: m->mg = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"%s",m->txt);break;
    }
}



















