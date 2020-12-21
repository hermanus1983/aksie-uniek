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

static void open_file(GtkFileChooserButton *btn, gpointer ptr)
{
	printf("%s selected\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(btn)));
}

void menu_bar(GtkWidget *mbar);
void file_menu(GtkWidget *file_mi);

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

    GtkWidget *mbar = gtk_menu_bar_new();
    GtkWidget *vbox = gtk_vbox_new(FALSE, 10);
    GtkWidget *tab = gtk_table_new(3, 3, TRUE);

    gtk_box_pack_start(GTK_BOX(vbox), mbar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), tab, TRUE, TRUE, 0);

    gtk_table_attach_defaults(GTK_TABLE(tab), lbl, 0, 2, 0, 1); 
    gtk_table_attach_defaults(GTK_TABLE(tab), btn2, 2, 3, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tab), btn, 2, 3, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tab), txt, 0, 2, 1, 2);

	menu_bar(mbar);

	gtk_container_add(GTK_CONTAINER(win), vbox);

	gtk_widget_show_all(win);
	gtk_main();
	
	return 0;
}

void menu_bar(GtkWidget *mbar)
{
	GtkWidget *file_mi = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), file_mi);
    
    file_menu(file_mi);
    
    GtkWidget *edit_mi = gtk_menu_item_new_with_label("Edit");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), edit_mi);
    
    GtkWidget *options_mi = gtk_menu_item_new_with_label("Options");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), options_mi);
    
    GtkWidget *about_mi = gtk_menu_item_new_with_label("About");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), about_mi);
}

void file_menu(GtkWidget *file_mi)
{
	GtkWidget *f_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), f_menu);

	GtkWidget *new_mi = gtk_menu_item_new_with_label("New");
	GtkWidget *open_mi = gtk_menu_item_new_with_label("Open");
	GtkWidget *save_mi = gtk_menu_item_new_with_label("save");
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), new_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), open_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), save_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
    g_signal_connect(quit_mi, "activate", G_CALLBACK(end_app), NULL);
}

