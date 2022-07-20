#include <adwaita.h>
#include "libunlockr.h"

void
show_about (GSimpleAction *self, GVariant *parameter, GtkWidget *window)
{

  GtkWidget *about = gtk_about_dialog_new ();

  gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (about), "unlockr");
  gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (about), "0.02");
  gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (about),
                                "https://github.com/jkotra/unlockr");

  GdkTexture *about_logo = gdk_texture_new_from_resource (
      "/com/github/jkotra/unlockr/icons/com.github.jkotra.unlockr.png");

  gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (about),
                             GDK_PAINTABLE (about_logo));
  g_object_unref (about_logo);

  gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG (about),
                                     GTK_LICENSE_GPL_3_0);

  char *qpdf_v = malloc (sizeof (char) * 24);
  sprintf (qpdf_v, "QPDF version: %s\n", getVersion ());
  gtk_about_dialog_set_system_information (GTK_ABOUT_DIALOG (about), qpdf_v);
  const char *authors[] = { "Jagadeesh Kotra", NULL };
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (about), authors);

  gtk_window_set_transient_for (GTK_WINDOW (about), GTK_WINDOW (window));
  gtk_window_set_modal (GTK_WINDOW (about), (gboolean) TRUE);

  gtk_window_present (GTK_WINDOW (about));

  free (qpdf_v);
}