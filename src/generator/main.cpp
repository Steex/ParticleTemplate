#include "gen_head.h"

#include <iostream>
#include <fstream>


String getFileContent(const String& _path)
{
    std::ifstream file(_path.getUtf8());
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}


void writeFileContent(const String& _path, const String& _content)
{
    std::ofstream file(_path.getUtf8());
    file << (std::string)_content;
}


int main(int argc, char *argv[])
{
    // Read system parameters.
    if (argc != 4)
    {
        std::cerr << "Bad arguments count" << std::endl;
        return 1;
    }

    String system_name = argv[1];
    String xml_path = argv[2];
    String out_path = argv[3];

    // Read the config.
    String xml_content = getFileContent(xml_path);

    // Read template files.
    String exe_folder = Utils::extractPath(argv[0]);
    String templ_header = getFileContent(exe_folder + "/templates/particle_system.h.templ");
    String templ_source = getFileContent(exe_folder + "/templates/particle_system.cpp.templ");

    // Process templates.
    templ_header = templ_header.replaceAll("$system_name$", system_name);
    templ_header = templ_header.replaceAll("$SYSTEM_NAME$", system_name.toUpper());

    templ_source = templ_source.replaceAll("$system_name$", system_name);
    templ_source = templ_source.replaceAll("$SYSTEM_NAME$", system_name.toUpper());

    // Write processed templates.
    writeFileContent(out_path + "/" + system_name + ".h",   templ_header);
    writeFileContent(out_path + "/" + system_name + ".cpp", templ_source);

    return 0;
}
