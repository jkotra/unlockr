#include <adwaita.h>
#include "main.h"

void
add_class_to_widget (GtkWidget *widget, char *class_name)
{
  gtk_widget_add_css_class (widget, class_name);
};

void
remove_class_from_widget (GtkWidget *widget, char *class_name)
{
  gtk_widget_remove_css_class (widget, class_name);
};

void
set_toast_color_to_green (GtkWidget *toast_overlay)
{
  remove_class_from_widget (toast_overlay, "red_toast");
  add_class_to_widget (toast_overlay, "green_toast");
}

void
set_toast_color_to_red (GtkWidget *toast_overlay)
{
  remove_class_from_widget (toast_overlay, "green_toast");
  add_class_to_widget (toast_overlay, "red_toast");
}

void
print_file_struct (struct File *file)
{
  g_debug ("{\n\tname: %s\n\tpath: %s\n\tstatus: %d\n}", file->name, file->path,
           file->decrypt_status);
}

void
free_file_struct (struct File *file)
{
  g_free (file->name);
  g_free (file->path);
  file->decrypt_status = false;
}