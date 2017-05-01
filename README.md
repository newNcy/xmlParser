this is a simple xml parser
===========================

        to use it , yiu should include its header file

        run the make command and:
        release the files in dir include to your include dir and the files in libs to your libs dir 
        #include <xml.h>

######write your code like this

        xml doc;
        /* parse from file */
        doc.parse_file(your_xml_path);
        /* parse from string */
        doc.parse(xml_string);

        after finish the parse, we can get the nodes or attribute message like fellows:

        /** get the declaration of xml :
         \* <?xml ... ?>
         **/
        node header = doc.header();
string version = header["version"];
printf("version:%s\n", version.c_str());

but not :
printf(doc.header()["version"]);

when you finished your code, don't forget the option of compile : -lxml

