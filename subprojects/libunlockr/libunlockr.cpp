#include <qpdf/QPDF.hh>
#include <qpdf/QPDFWriter.hh>
#include <glib.h>

extern "C" const char *
getVersion ()
{
  QPDF qpdf;
  return qpdf.QPDFVersion ().c_str ();
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
      return NULL;
    }
}