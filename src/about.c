#include <adwaita.h>
#include "libunlockr.h"

void
show_about (GSimpleAction *self, GVariant *parameter, GtkWidget *window)
{

  GtkWidget *about = adw_about_window_new ();
  adw_about_window_set_application_name (ADW_ABOUT_WINDOW (about), "unlockr");
  adw_about_window_set_version (ADW_ABOUT_WINDOW (about), "0.07");
  adw_about_window_set_website (ADW_ABOUT_WINDOW (about),
                                "https://github.com/jkotra/unlockr");
  adw_about_window_set_license_type (ADW_ABOUT_WINDOW (about),
                                     GTK_LICENSE_GPL_3_0);
  adw_about_window_set_application_icon (ADW_ABOUT_WINDOW (about),
                                         "com.github.jkotra.unlockr");
  adw_about_window_set_issue_url (ADW_ABOUT_WINDOW (about),
                                  "https://github.com/jkotra/unlockr/issues");

  char *qpdf_v = malloc (sizeof (char) * 24);
  sprintf (qpdf_v, "QPDF version: %s\n", getVersion ());
  adw_about_window_set_debug_info (ADW_ABOUT_WINDOW (about), qpdf_v);
  free (qpdf_v);

  const char *authors[] = { "Jagadeesh Kotra", NULL };
  adw_about_window_set_developers (ADW_ABOUT_WINDOW (about), authors);

  gtk_window_set_transient_for (GTK_WINDOW (about), GTK_WINDOW (window));
  gtk_window_set_modal (GTK_WINDOW (about), TRUE);
  gtk_window_present (GTK_WINDOW (about));
}