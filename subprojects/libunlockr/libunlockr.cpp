#include <qpdf/QPDF.hh>
#include <qpdf/QPDFWriter.hh>
#include <glib.h>
#include <glib/gstrfuncs.h>

extern "C" const char *
getVersion ()
{
  QPDF qpdf;
  std::string ver = qpdf.QPDFVersion();
  return g_strdup(ver.c_str());
}

extern "C" bool
isFileEncrypted (char *filepath)
{

  QPDF qpdf;

  try
    {
      qpdf.setPasswordIsHexKey (true);
      qpdf.processFile (filepath);
      bool e = qpdf.isEncrypted ();
      qpdf.closeInputSource ();
      return e;
    }
  catch (std::exception &err)
    {
      if (err.what ())
        std::cout << err.what () << std::endl;
        qpdf.closeInputSource();
      return false;
    }
}

extern "C" bool
decryptPDF (char *filepath, char *out, char *password)
{

  QPDF qpdf;

  try
    {
      qpdf.processFile (filepath, password);
      QPDFWriter w (qpdf, out);
      w.setPreserveEncryption (false);
      w.write ();
      qpdf.closeInputSource ();
      return true;
    }
  catch (std::exception &err)
    {
      // std::cout << err.what () << std::endl;
      g_warning ("%s", err.what ());
      qpdf.closeInputSource();
      return NULL;
    }
}

extern "C" bool
verifyPassword (char *filepath, char *password)
{
  QPDF qpdf;

  try
    {
      qpdf.processFile (filepath, password);
      qpdf.closeInputSource();
      return true;
    }
  catch (std::exception &err)
    {
      g_warning ("%s", err.what ());
      qpdf.closeInputSource();
      return false;
    }
}