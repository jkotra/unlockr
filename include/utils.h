void add_class_to_widget (GtkWidget *widget, char *class_name);
void remove_class_from_widget (GtkWidget *widget, char *class_name);
void print_file_struct (struct File *file);
void free_file_struct (struct File *file);
void set_toast_color_to_green (GtkWidget *toast_overlay);
void set_toast_color_to_red (GtkWidget *toast_overlay);

#ifdef _WIN32
bool set_gsettings_env_var_win32 ();
#endif