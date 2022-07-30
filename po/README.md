# How To Translate

0. The Usual, fork the repository, clone, and checkout to a branch.

1. Download & Install [PoEdit](https://poedit.net/download).
2. There are two ways to extract strings from the source code:
    
    * 2.1. Base your translations on `po/en.po`

        `en.po` frequently updates whenever new strings are added to the source code, its purpose is to serve as a template for basing other translations.

        2.1.1. `File-Open-> [Choose en.po]`

        2.1.2. `Translation->Properties-> [Set Language to suit your workflow.]`
    
    * 2.2. Extract strings from source code.

        2.2.1.  `File -> New`, select the language you want to translate to.
        
        2.2.2. Save the file.
        
        2.2.3. Click "Extract From Sources" and add the following paths
        ```
        src/
        data/
        ```
        2.2.4. Press `OK`. This will extract strings from the source code.


3. save it as LANGUAGECODE.po in `po` directory.
4. Add LANGUAGECODE to `po/LINUGUAS`

