struct ProcessPageWidgets
{
  GtkWidget *main_window;
  GtkWidget *file_label;
  GtkWidget *password_input;
  GtkWidget *decrypt_btn;
  struct File *file;
  GtkWidget *toast_overlay;
  AdwToast *current_toast;
};

typedef struct WelcomePageWidgets
{
  GtkWidget *header_cancel_btn;
  GtkWidget *main_window;
  GtkWidget *main_leaf;
  GtkWidget *welcome_box;
  GtkWidget *process_box;
  GtkWidget *choose_button;
  GtkWidget *stack;
  struct ProcessPageWidgets process_widgets;
} AppWidgets;

struct File
{
  char *name;
  char *path;
  int decrypt_status;
};