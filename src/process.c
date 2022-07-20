#include <adwaita.h>
#include <glib.h>
#include <libintl.h>
#include "main.h"
#include "utils.h"
#include "libunlockr.h"

struct ProcessPageWidgets Pwidgets = { 0 };
struct File *Pfile;

void
set_file (struct File *_file)
{
  Pfile = _file;
  print_file_struct (Pfile);
}

void
set_toast_priority (AdwToast *toast)
{
  GValue v = G_VALUE_INIT;
  g_value_init (&v, G_TYPE_INT);
  g_value_set_int (&v, ADW_TOAST_PRIORITY_HIGH);
  g_object_set_property (G_OBJECT (toast), "priority", &v);
}

void
set_input_placeholder (GtkWidget *input)
{
  GValue a = G_VALUE_INIT;
  g_value_init (&a, G_TYPE_STRING);
  g_value_set_string (&a, gettext ("Enter Password..."));

  g_object_set_property (G_OBJECT (input), "placeholder-text", &a);
}

void
send_toast (char *message)
{
  AdwToast *toast = adw_toast_new (message);
  set_toast_priority (toast);
  adw_toast_overlay_add_toast (ADW_TOAST_OVERLAY (Pwidgets.toast_overlay),
                               toast);
}

void
on_password_changed (GtkWidget *password_entry, gpointer user_data)
{
  const char *text = gtk_editable_get_text (GTK_EDITABLE (password_entry));
  g_debug ("%s", text);
  if (strlen (text) < 1)
    {
      gtk_widget_set_sensitive (Pwidgets.decrypt_btn, FALSE);
    }
  else
    {
      gtk_widget_set_sensitive (Pwidgets.decrypt_btn, TRUE);
    }
}

void
on_decrypt_btn_clicked (GtkWidget *btn, gpointer user_data)
{

  const char *text =
      gtk_editable_get_text (GTK_EDITABLE (Pwidgets.password_input));

  const gchar *home = g_get_home_dir ();
  gchar *out = g_build_filename (home, "Documents", Pfile->name, NULL);
  bool result = decryptPDF (Pfile->path, (char *) out, (char *) text);
  if (result)
    {
      set_toast_color_to_green (Pwidgets.toast_overlay);
      send_toast (gettext ("File Decryped &amp; Saved to Documents!"));
      Pfile->decrypt_status = true;
    }
  else
    {
      set_toast_color_to_red (Pwidgets.toast_overlay);
      send_toast (gettext ("Invalid Password!"));
    }
}

struct ProcessPageWidgets
construct_process (GtkWidget *box)
{
  GtkWidget *top_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  GtkWidget *bottom_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  GtkWidget *combined_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *toast_overlay = adw_toast_overlay_new ();

  gtk_box_append (GTK_BOX (combined_box), top_box);
  gtk_box_append (GTK_BOX (combined_box), bottom_box);
  adw_toast_overlay_set_child (ADW_TOAST_OVERLAY (toast_overlay), combined_box);
  gtk_box_append (GTK_BOX (box), toast_overlay);

  gtk_widget_set_vexpand (top_box, TRUE);
  gtk_widget_set_valign (top_box, GTK_ALIGN_CENTER);

  GtkWidget *file_label = gtk_label_new (NULL);
  gtk_label_set_wrap (GTK_LABEL (file_label), TRUE);
  add_class_to_widget (file_label, "file-label");

  GtkWidget *password_input = gtk_password_entry_new ();
  gtk_widget_set_size_request (password_input, -1, 80);
  g_signal_connect (password_input, "changed", G_CALLBACK (on_password_changed),
                    NULL);
  gtk_password_entry_set_show_peek_icon (GTK_PASSWORD_ENTRY (password_input),
                                         TRUE);
  set_input_placeholder (password_input);
  add_class_to_widget (password_input, "password-input");

  GtkWidget *decrypt_button = gtk_button_new_with_label (gettext ("Decrypt"));
  add_class_to_widget (decrypt_button, "suggested-action");
  g_signal_connect (decrypt_button, "clicked",
                    G_CALLBACK (on_decrypt_btn_clicked), NULL);
  gtk_widget_set_sensitive (decrypt_button, FALSE);
  add_class_to_widget (decrypt_button, "m-12");

  gtk_box_append (GTK_BOX (top_box), file_label);
  gtk_box_append (GTK_BOX (top_box), password_input);

  gtk_box_append (GTK_BOX (bottom_box), decrypt_button);

  Pwidgets.file_label = file_label;
  Pwidgets.password_input = password_input;
  Pwidgets.decrypt_btn = decrypt_button;
  Pwidgets.toast_overlay = toast_overlay;

  return Pwidgets;
}