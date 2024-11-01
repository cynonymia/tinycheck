#pragma once
#include <istream>
#include <memory>
#include <cassert>
#include "parser.hpp"

#define ASSIGNMENT_TRUE 1
#define ASSIGNMENT_FALSE -1
#define ASSIGNMENT_NONE 0

#define TINY_CHECK_FAIL -1
#define TINY_CHECK_SAT 10
#define TINY_CHECK_UNSAT 20

#define MATCH_ASSIGNED(x) (assignments[abs(x)] != 0) && (assignments[abs(x)] < 0 == x < 0)

class TinyCheck{
    std::istream& formula;
    std::istream& model;

public:
    TinyCheck(std::istream& formula, std::istream& model) 
        : formula(formula), model(model) {}

    int check(){
        DBG("Start Checking");
        Parser parser(formula);
        int n, m;
        parser.readPreamble(n, m);
        DBG("Predict " << n << " variables and " << m << " clauses");
        std::unique_ptr<char[]> assignments = std::make_unique<char[]>(n+1);
        Parser modelParser(model);

        //Read model
        int assignment;
        while(modelParser.nextNumber(assignment)){
            DBG("Register assignment " << assignment);
            assert(abs(assignment) <= n);
            assignments[abs(assignment)] = assignment > 0 ? ASSIGNMENT_TRUE : ASSIGNMENT_FALSE;
        }
        if(!modelParser.eof()){
            ERR("Did not reach end while reading model! Terminating...");
            return TINY_CHECK_FAIL;
        }

        bool curClauseSAT = false;
        int clauseNr = 1;
        int curLit;
        while(parser.nextNumber(curLit)){
            if(curLit == 0){
                if(!curClauseSAT){
                    ERR("[Clause " << clauseNr<< "] Not satisfied by assignment! Model Check failed!");
                    return TINY_CHECK_UNSAT;
                }
                curClauseSAT = false;
                clauseNr++;
            }
            if(curClauseSAT) continue;  //skip if already satisfied

            curClauseSAT = MATCH_ASSIGNED(curLit);
            if(curClauseSAT) {
                DBG("[Clause "<< clauseNr<<"] Satisfied by " << curLit);
            }
        }

        if(!parser.eof()){
            ERR("Did not reach end while reading formula! Terminating...");
            return TINY_CHECK_FAIL;
        }        
        return TINY_CHECK_SAT;
    }  
};