#include <getopt.h>
#include <fstream>
#include "logging.hpp"
#include "parser.hpp"
#include "tinycheck.hpp"


struct argument_settings
{
    char verbose = VERBOSE_ERROR;
    bool help_mode = false;
	char* formula = nullptr;
    char* model = nullptr;	
};

static const struct option options[] =
{
	{"help", no_argument, 0, 'h'},
	{"debug", no_argument, 0, 'd'},
	{"quiet", no_argument, 0, 'q'},
	0
};

static void parse_arguments(int argc, char** argv, struct argument_settings& settings)
{    
	int idx = 0;
	int result = 0;
	while (result != -1)
	{        
		result = getopt_long(argc, argv, "hdq", options, &idx);
		switch (result)
		{
		case 'h': settings.help_mode = true; break;
		case 'd': settings.verbose = VERBOSE_DEBUG; break;
		case 'q': settings.verbose = VERBOSE_SILENT; break;
		case ':': std::cout << "Missing Argument!" << std::endl;
		case '?':            
		default:
			break;
		}		
	}
	if (optind < argc)
		settings.formula = argv[optind++];	
    if(optind < argc)
        settings.model = argv[optind++];
}

void print_help()
{
	std::cout << "TinyCheck v0.1 (alpha-phase)" << std::endl;
	std::cout << "A small, efficient model checker" << std::endl;
	std::cout << "usage: <Formula> [<Model>] [-h] [-d] [-q]" << std::endl;
	std::cout << "<Source File>:         A file containing the target formula. If non specified or \"-\", stdin is used" << std::endl;
	std::cout << "-h, --help:            When specified, this text is printed" << std::endl;
	std::cout << "                       <Formula> and <Model> are ignored with this argument" << std::endl;    
	std::cout << "-d, --debug:           When specified, verbose is set to debug level." << std::endl;
	std::cout << "-q, --quiet:           When specified, verbose is turned off" << std::endl;
}


int main(int argc, char** argv){
    struct argument_settings args;
	parse_arguments(argc, argv, args);

    if(args.help_mode){
        print_help();
        return 0;
    }

    global_verbose = args.verbose;
    if(args.formula == nullptr){
        ERR("Not enough file inputs specified! Expected at least one of <Formula>");
        exit(-1);
    }

    std::fstream input(args.formula);
    if(!input.good()){
        ERR("Unable to open formula file: " << args.formula);
        exit(-1);
    }

    std::fstream modelFile(args.model);

    if(args.model == nullptr)
        ALERT("No model-file specified, reading input from stdin!");        

    if(!modelFile.good()){
        ERR("Unable to open model file: " << args.formula);
        exit(-1);
    }

    std::istream& model = args.model == nullptr ? std::cin : modelFile;

    TinyCheck check(input, model);       

    int result = check.check();
    switch (result)
    {
    case TINY_CHECK_SAT:   ALERT("SAT"); break;
    case TINY_CHECK_UNSAT: ALERT("UNSAT"); break; 
    default: ALERT("FAIL"); break; 
    }
    return result;
}
