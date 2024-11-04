#pragma once

#include <istream>
#include <vector>
#include <stack>
#include <algorithm>
#include "logging.hpp"

#define LEMMA_PROC_READ_SIZE 4096

#define IS_WHITESPACE(x) ((x) == ' ' || (x) == '\r' || (x) == '\t' || (x) == '\n')
#define SKIP_WHITESPACES while(IS_WHITESPACE(current)) { next(); }
#define SKIP_LINE {while(!eof() && current != '\n') {next();} next(); }

class Parser{
    std::istream& input;
    char current = -2;
    int line = 1; 
    int col = 0;
    bool eofFlag = false;
    char buffer[LEMMA_PROC_READ_SIZE];
    int bufsize = 0;
    int bufptr = -1;    

    void nextBlock(){
        bufsize = LEMMA_PROC_READ_SIZE;
        this->input.read(buffer, bufsize);
        std::size_t read = this->input.gcount();
        if(read < LEMMA_PROC_READ_SIZE){
            eofFlag = true;
            bufsize = read;
        }
        DBG("[Parser] (Buffered read): Read " << read << " bytes");
        bufptr = -1;
    }

    void next(){
        if(!eof()){
            if(bufptr >= bufsize-1) nextBlock();
            current = this->buffer[++bufptr];
            col++;
            if(current == '\n'){
                line++;
                col = 0;
            }
        }
        else current = EOF;
    
    }

    void check(char expected){
        if(current == expected)
            next();
        else{
            ERR("Parser error in line " << line << ", column " << col <<"! Expected " << expected 
                 << " (" << (int) expected << ") but got " << current << " (" << (int) current << "). Terminating...");
            exit(-1);
        }
    }

    int read_number(){
        bool valid = true;
        int result = 0;
        bool neg = false;
        do{
            switch (current)
            {
                case '0': case '1': case '2': case '3': case '4': 
                case '5': case '6': case '7': case '8': case '9':
                    result = result * 10 + (current - '0'); next();
                    break;
                case '-': neg = true; next(); break;            
                default: valid = false; break;  
            }
        } while(valid);
        return neg ? -result : result;
    }

    bool check_number(){
        switch (current)
        {
            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9': case '-': 
                return true;
            default: return false;
        }
    }


public:
    Parser(std::istream& input) : input(input) {  this->nextBlock(); next();}

    inline bool eof() { return eofFlag && bufptr >= bufsize; }

    void readPreamble(int& n, int& m){
        while(current == 'c') SKIP_LINE;
        check('p'); check(' ');
        check('c'); check('n'); check('f'); check(' ');
        n = read_number(); check(' ');
        m = read_number();
    }

    inline bool nextNumber(int& target){
        SKIP_WHITESPACES;
        if(eof() || !check_number())
            return false;               
        
        target = read_number();
        return true;        
    }
};
