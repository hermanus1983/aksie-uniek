#include<stdio.h>
#include<string.h>
#include<stdint.h>

#include<gtk/gtk.h>

uint32_t count = 0;
GtkWidget *txt;

void end_app(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

void count_button(GtkWidget *wid, gpointer ptr)
{
    char buffer[30];
    count++;
    sprintf(buffer, "button pressed %u times", count);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

void copy_text(GtkWidget *wid, gpointer ptr)
{
    const char *INPUT = gtk_entry_get_text(GTK_ENTRY(txt));
    gtk_label_set_text(GTK_LABEL(ptr), INPUT);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close Window");
	
	g_signal_connect(btn, "clicked", G_CALLBACK(end_app), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_app), NULL);

    GtkWidget *lbl = gtk_label_new("My Label");
    GtkWidget *btn2 = gtk_button_new_with_label("Copy Button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(copy_text), lbl);

    txt = gtk_entry_new();

    GtkWidget *tab = gtk_table_new(2, 2, TRUE);

    gtk_table_attach_defaults(GTK_TABLE(tab), lbl, 0, 1, 0, 1); 
    gtk_table_attach_defaults(GTK_TABLE(tab), btn2, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tab), btn, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tab), txt, 1, 2, 1, 2);

	gtk_container_add(GTK_CONTAINER(win), tab);

	gtk_widget_show_all(win);
	gtk_main();
	
	return 0;
}
