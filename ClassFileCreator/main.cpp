#include <iostream>
#include <fstream>
#include <string>
#include "main.hpp"

int s;

void open_file(std::ofstream &file, std::string &name)
{
    file.open(name, std::ios::out | std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error : opening file : " << name << '.' << std::endl;
        std::exit(1);
    }
}

std::string get_macro_name(std::string &filename)
{
    size_t      length;
    std::string macro_name;

    length = filename.length();
    for (size_t i = 0 ; i < length ; i++)
    {
        if (filename[i] == '.')
            macro_name.push_back('_');
        else
            macro_name.push_back(std::toupper(filename[i]));
    }
    return (macro_name);
}

void    fill_hpp_file(std::ofstream &file, std::string &name, char *class_name)
{
    std::string macro_name = get_macro_name(name);

    file << "#ifndef " << macro_name << std::endl;
    file << "# define " << macro_name << std::endl << std::endl;
    file << "class " << class_name << std::endl << '{' << std::endl << "\tpublic :" << std::endl;
    file << "\t\t" << class_name << "(void);" << std::endl;
    file << "\t\t" << class_name << '(' << class_name << " const &copy);" << std::endl;
    file << "\t\t" << '~' << class_name << "(void);" << std::endl;
    file << "\t\t" << class_name << " const &operator = (" << class_name << " const &rhs);" << std::endl;
    file << "};" << std::endl;
    file << std::endl << "#endif";
    file.close();
}

void    fill_cpp_file(std::ofstream &file, std::string &filename, char *class_name)
{
    file << "#include \"" << filename.substr(0, filename.length() - 4) << ".hpp\"" << std::endl << std::endl;
    file << class_name << "::" << class_name << "(void) {}" << std::endl << std::endl;
    file << class_name << "::" << class_name << '(' << class_name << " const &copy) {}" << std::endl << std::endl;
    file << class_name << "::~" << class_name << "(void) {}" << std::endl << std::endl;
    file << class_name << " const\t&" << class_name << "::operator = (" << class_name << " const &rhs) {}";
    file.close();
}

void    open_and_fill(char *class_name, int type)
{
    std::string     filename;
    std::ofstream   file;

    filename = class_name;
    if (type == HPP)
    {
        if (s)
            filename.append(".hpp");
        else
            filename.append(".class.hpp");
        open_file(file, filename);
        fill_hpp_file(file, filename, class_name);
    }
    else if (type == CPP)
    {
        if (s)
            filename.append(".cpp");
        else
            filename.append(".class.cpp");
        open_file(file, filename);
        fill_cpp_file(file, filename, class_name);
    }
    file.close();
}

void    show_help(char *program_name)
{
    std::cout << "\tclasses' .cpp and .hpp files creator" << std::endl << std::endl;
    std::cout << "\tusage : " << program_name << " -h | [-s] class_names ..." << std::endl << std::endl;
    std::cout << "\t\ts : create with simple filenames (without *.class*)" << std::endl;
    std::cout << "\t\th : show help" << std::endl;
    std::exit(0);
}

bool    check_name_validity(char *class_name)
{
    int length;

    length = std::strlen(class_name);
    if (!isalpha(class_name[0]) && (class_name[0] != '_'))
        return (0);
    for (int i = 1 ; i < length ; i++)
        if (!std::isalnum(class_name[i]) && (class_name[i] != '_'))
            return (0);
    return (1);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!std::strcmp(argv[1], "-h"))
            show_help(argv[0]);
        else if (!std::strcmp(argv[1], "-s"))
            s = 1;
        for (int i = s + 1 ; i < argc ; i++)
        {
            if (!check_name_validity(argv[i]))
                std::cerr << "Error : " << argv[i] << " ; Bad name" << std::endl;
            else
            {
                open_and_fill(argv[i], HPP);
                open_and_fill(argv[i], CPP);
            }
        }
    }
    else
        std::cout << "usage : " << argv[0] << " -h | [-s] class_names ..." << std::endl;
    return (0);
}