#include <adwaita.h>
#include <gio/gio.h>
#include <gdk/gdk.h>
#include <libintl.h>
#include "main.h"
#include "about.h"
#include "process.h"
#include "utils.h"
#include "libunlockr.h"
#include "details.h"

AppWidgets widgets = { 0 };
struct File file = { 0 };

void
hello_world (GtkWidget *widget, gpointer *userdata)
{
  static int count = 1;
  g_message ("Hello for the %dth time!", count);
  count++;
}

void
go_back_to_welcome (GtkWidget *btn, gpointer data)
{
  gtk_widget_set_visible (btn, FALSE);
  gtk_stack_set_visible_child_name (GTK_STACK (widgets.stack), "welcome");

  gtk_editable_set_text (GTK_EDITABLE (widgets.process_widgets.password_input),
                         "");
  g_debug ("password reset to empty!");
  free_file_struct (&file);
}

void
setup_process_for_file ()
{

  // set file for process stage.
  set_file (&file);

  g_message ("file: %s | status: %s", file.name,
             file.decrypt_status ? "Encrypted" : "Not Encrypted");
  char *markup = g_markup_printf_escaped (
      gettext ("<span size=\"large\">%s is <span "
               "weight=\"bold\">%s.</span></"
               "span>"),
      file.name,
      file.decrypt_status ? gettext ("Encrypted") : gettext ("Not Encrypted"));

  gtk_label_set_markup (GTK_LABEL (widgets.process_widgets.file_label), markup);
  g_free (markup);
  gtk_widget_set_visible (widgets.header_cancel_btn, TRUE);
  gtk_stack_set_visible_child_name (GTK_STACK (widgets.stack), "process");

  if (!file.decrypt_status)
    {
      gtk_widget_set_visible (widgets.process_widgets.password_input, FALSE);
      gtk_widget_set_visible (widgets.process_widgets.decrypt_btn, FALSE);
    }
  else
    {
      gtk_widget_set_visible (widgets.process_widgets.password_input, TRUE);
      gtk_widget_set_visible (widgets.process_widgets.decrypt_btn, TRUE);
    }
}

void
on_drop (GtkDropTarget *target,
         const GValue *value,
         double x,
         double y,
         gpointer data)
{
  GFile *dropped_file = G_FILE (g_value_get_object (value));
  g_message ("dropped (%f, %f): %s", x, y, g_file_get_basename (dropped_file));

  char *chosen_path = g_file_get_path (dropped_file);

  file.name = g_file_get_basename (dropped_file);
  file.path = chosen_path;
  file.decrypt_status = isFileEncrypted (file.path);

  setup_process_for_file ();
}

void
on_file_chosen (GtkFileDialog *dialog, GAsyncResult *res, gpointer data)
{
  GFile *chosen_file = gtk_file_dialog_open_finish (dialog, res, NULL);
  if (!chosen_file)
    {
      return;
    }
  char *chosen_path = g_file_get_path (chosen_file);

  file.name = g_file_get_basename (chosen_file);
  file.path = chosen_path;
  file.decrypt_status = isFileEncrypted (file.path);

  setup_process_for_file ();
}

void
choose_file (GtkWidget *btn, GtkWindow *window)
{
  GtkFileDialog *filechooser = gtk_file_dialog_new ();
  GtkFileFilter *filter = gtk_file_filter_new ();
  gtk_file_filter_set_name (filter, "*.PDF");
  gtk_file_filter_add_suffix (filter, "pdf");
  gtk_file_dialog_set_default_filter (filechooser, filter);
  gtk_file_dialog_open (filechooser, window, NULL,
                        (GAsyncReadyCallback) on_file_chosen, NULL);
}

void
inject_css ()
{
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_resource (
      provider, "/com/github/jkotra/unlockr/css/main.css");
  GdkDisplay *display = gdk_display_get_default ();
  gtk_style_context_add_provider_for_display (
      display, GTK_STYLE_PROVIDER (provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void
construct_popover_menu (GtkApplication *app,
                        GtkWidget *window,
                        GtkWidget *header_bar)
{
  GMenu *menu = g_menu_new ();

  GtkWidget *menu_btn = gtk_menu_button_new ();
  gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (menu_btn),
                                 "open-menu-symbolic");

  GtkWidget *popover = gtk_popover_menu_new_from_model (G_MENU_MODEL (menu));
  gtk_menu_button_set_popover (GTK_MENU_BUTTON (menu_btn), popover);

  GSimpleAction *action = g_simple_action_new ("about", NULL);
  g_signal_connect (action, "activate", G_CALLBACK (show_about), window);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (action));

  const gchar *accls[] = { (gchar *) "<Primary>A", NULL };
  gtk_application_set_accels_for_action (app, "app.about", accls);

  GMenuItem *m_item = g_menu_item_new (gettext ("About"), "about");
  g_menu_item_set_action_and_target_value (m_item, "app.about", NULL);
  g_menu_append_item (menu, m_item);

  adw_header_bar_pack_end (ADW_HEADER_BAR (header_bar), GTK_WIDGET (menu_btn));
}

static void
on_activate (GtkApplication *app)
{
  GtkWidget *app_window = adw_application_window_new (app);
  gtk_window_set_default_size (GTK_WINDOW (app_window), 600, 400);
  gtk_window_set_title (GTK_WINDOW (app_window), "unlockR");
  gtk_window_set_icon_name (GTK_WINDOW (app_window),
                            "com.github.jkotra.unlockr");
  widgets.main_window = app_window;
  inject_css ();
  if (getenv ("G_MESSAGES_DEBUG") != NULL)
    {
      gtk_widget_add_css_class (app_window, "devel");
    }

  GtkWidget *header_bar = adw_header_bar_new ();
  construct_popover_menu (app, app_window, header_bar);

  GtkWidget *cancel_btn = gtk_button_new_with_label (gettext ("Cancel"));
  add_class_to_widget (cancel_btn, "destructive-action");
  adw_header_bar_pack_start (ADW_HEADER_BAR (header_bar), cancel_btn);
  gtk_widget_set_visible (cancel_btn, FALSE); // initial state
  g_signal_connect (cancel_btn, "clicked", G_CALLBACK (go_back_to_welcome),
                    NULL);
  widgets.header_cancel_btn = cancel_btn;

  /* main_leaf is top most widget */
  GtkWidget *main_leaf = adw_leaflet_new ();
  gtk_widget_set_size_request (main_leaf, -1, 340);
  gtk_orientable_set_orientation (GTK_ORIENTABLE (main_leaf),
                                  GTK_ORIENTATION_VERTICAL);
  widgets.main_leaf = main_leaf;

  /* add header to leaflet */
  adw_leaflet_append (ADW_LEAFLET (main_leaf), GTK_WIDGET (header_bar));

  /* set main_leaf as content of our app */
  adw_application_window_set_content (ADW_APPLICATION_WINDOW (app_window),
                                      GTK_WIDGET (main_leaf));

  /* we have two stages in app cycle:

      1. welcome (choose file)
      2. process (ask password AND decrypt)
          - send toast on success / failure.
  */
  GtkWidget *welcome_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  gtk_widget_set_vexpand (welcome_box, TRUE);
  gtk_widget_set_hexpand (welcome_box, TRUE);

  // set drag-n-drop
  GtkDropTarget *drop = gtk_drop_target_new (G_TYPE_FILE, GDK_ACTION_COPY);
  g_signal_connect (drop, "drop", G_CALLBACK (on_drop), NULL);
  gtk_widget_add_controller (welcome_box, GTK_EVENT_CONTROLLER (drop));

  GtkWidget *process_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  gtk_widget_set_vexpand (process_box, TRUE);

  /* stack holds both the welcome and process */
  GtkWidget *stack = gtk_stack_new ();
  gtk_stack_set_transition_type (GTK_STACK (stack),
                                 GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  gtk_stack_add_named (GTK_STACK (stack), welcome_box, "welcome");
  gtk_stack_add_named (GTK_STACK (stack), process_box, "process");
  adw_leaflet_append (ADW_LEAFLET (main_leaf), stack);

  widgets.stack = stack;
  widgets.welcome_box = welcome_box;
  widgets.process_box = process_box;

  widgets.process_widgets = construct_process (process_box);

  GtkWidget *_logo =
      gtk_image_new_from_resource ("/com/github/jkotra/unlockr/icons/hero.png");
  gtk_image_set_pixel_size (GTK_IMAGE (_logo), 164);
  gtk_widget_set_valign (_logo, GTK_ALIGN_CENTER);
  gtk_widget_set_vexpand (_logo, TRUE);
  gtk_widget_add_css_class (_logo, "m-12");
  gtk_box_append (GTK_BOX (welcome_box), _logo);

  GtkWidget *choose_btn = gtk_button_new ();
  gtk_button_set_label (GTK_BUTTON (choose_btn), gettext ("Choose a File..."));
  gtk_widget_set_valign (choose_btn, GTK_ALIGN_CENTER);
  gtk_box_append (GTK_BOX (welcome_box), choose_btn);
  add_class_to_widget (choose_btn, "choose-btn");
  widgets.choose_button = choose_btn;

  g_signal_connect (choose_btn, "clicked", G_CALLBACK (choose_file),
                    app_window);

  gtk_window_present (GTK_WINDOW (app_window));
}

int
main (int argc, char *argv[])
{

  textdomain ("unlockr");
  bindtextdomain ("unlockr", LOCALE_PATH);
  g_debug ("textdomain=%s LOCALE_PATH=%s", textdomain (NULL), LOCALE_PATH);

  // Create a new application
  AdwApplication *app = adw_application_new ("com.github.jkotra.unlockr",
                                             G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
  return g_application_run (G_APPLICATION (app), argc, argv);
}
