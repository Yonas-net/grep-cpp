#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef BOOST_MSVC
#pragma warning(disable:4512 4244)
#endif

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv) {
    std::vector<std::string> pattern;

    try {
        po::options_description opts("Usage: ./boost-grepCommand [OPTION] PATTERN [FILE]\n"
                                     "Search for PATTERN in a FILE.\n"
                                     "Example: grep -i 'Hallo Welt' *.txt\n\n"
                                     "Sample selection and interpretation");
        opts.add_options()
                ("fixed-strings,F",
                 "Interpret PATTERN as a list of fixed strings, separated by newlines, any of which is to be matched")
                ("regexp,e", po::value<std::vector<std::string>>(&pattern)->required(),
                 "Specifies expression with this option. Can use multiple times");

        po::options_description cmdline_options;
        cmdline_options.add(opts);

        po::variables_map variablesMap;
        po::store(
                po::command_line_parser(argc, argv)
                        .options(cmdline_options).run(),
                variablesMap);

        po::notify(variablesMap);

        if (variablesMap.count("help")) {
            std::cout << opts << "\n";
            return EXIT_SUCCESS;
        }

        if (variablesMap.count("regexp")) {
            std::string line;
            while (getline(std::cin, line)) {
                for (auto &value: pattern) {
                    auto search = line.find(value);
                    if (search != std::string::npos) {
                        std::cout << line << "\n";
                        break;
                    }
                }
            }
        } else {
            std::cerr << "boost-grepCommand: at least the -e parameter is needed" << std::endl;
            return EXIT_FAILURE;
        }

    } catch (const std::exception &exception) {
        std::cerr << exception.what() << "\n";
    }

    return EXIT_SUCCESS;
}
