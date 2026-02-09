#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "usage: embed_generator.exe <input.h> <output.cpp>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "failed to open input file\n";
        return 1;
    }

    std::ofstream out(argv[2]);
    if (!out)
    {
        std::cerr << "failed to open output file\n";
        return 1;
    }

    std::regex bitmapRegex("EMBED_WX_BITMAP\\s*\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*[^,]+,\\s*\"([^\"]+)\"\\s*\\)");
    std::regex binaryRegex("EMBED_BINARY\\s*\\(\\s*([a-zA-Z_][a-zA-Z0-9_]*)\\s*,\\s*\"([^\"]+)\"\\s*\\)");

    std::regex lineCommentRegex("//.*");
    std::regex blockCommentRegex("/\\*.*?\\*/");

    out << "#include \"resources.h\"\n\n";

    std::string line;

    while (std::getline(in, line))
    {
        std::string clean = std::regex_replace(line, blockCommentRegex, "");
        clean = std::regex_replace(clean, lineCommentRegex, "");

        std::smatch m;

        if (std::regex_search(clean, m, bitmapRegex))
            out << "INCBIN(" << m[1] << ", \"" << m[2] << "\")\n";
        else if (std::regex_search(clean, m, binaryRegex))
            out << "INCBIN(" << m[1] << ", \"" << m[2] << "\")\n";
    }

    return 0;
}
