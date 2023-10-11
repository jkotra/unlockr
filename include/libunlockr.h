const char *getVersion ();
bool isFileEncrypted (char *filepath);
bool decryptPDF (char *filepath, char *out, char *password);
bool verifyPassword (char *filepath, char *password);