#include "tokens.h"
#include "grammar.h"
#include "hw2.h"
#include <iostream>

void print_token(tokens tok)
{
    switch (tok)
    {
    case VOID:
        std::cout << "VOID";
        break;
    case INT:
        std::cout << "INT";
        break;
    case BYTE:
        std::cout << "BYTE";
        break;
    case B:
        std::cout << "B";
        break;
    case BOOL:
        std::cout << "BOOL";
        break;
    case AND:
        std::cout << "AND";
        break;
    case OR:
        std::cout << "OR";
        break;
    case NOT:
        std::cout << "NOT";
        break;
    case TRUE:
        std::cout << "TRUE";
        break;
    case FALSE:
        std::cout << "FALSE";
        break;
    case RETURN:
        std::cout << "RETURN";
        break;
    case IF:
        std::cout << "IF";
        break;
    case ELSE:
        std::cout << "ELSE";
        break;
    case WHILE:
        std::cout << "WHILE";
        break;
    case BREAK:
        std::cout << "BREAK";
        break;
    case CONTINUE:
        std::cout << "CONTINUE";
        break;
    case PRECOND:
        std::cout << "PRECOND";
        break;
    case SC:
        std::cout << "SC";
        break;
    case COMMA:
        std::cout << "COMMA";
        break;
    case LPAREN:
        std::cout << "LPAREN";
        break;
    case RPAREN:
        std::cout << "RPAREN";
        break;
    case LBRACE:
        std::cout << "LBRACE";
        break;
    case RBRACE:
        std::cout << "RBRACE";
        break;
    case ASSIGN:
        std::cout << "ASSIGN";
        break;
    case RELOP:
        std::cout << "RELOP";
        break;
    case BINOP:
        std::cout << "BINOP";
        break;
    case ID:
        std::cout << "ID";
        break;
    case NUM:
        std::cout << "NUM";
        break;
    case STRING:
        std::cout << "STRING";
        break;    
    case EF:
        std::cout << "EF";
        break;
    };
}

void print_nonterminal(nonterminal var)
{
    switch (var)
    {
    case PROGRAM:
        std::cout << "PROGRAM";
        break;
    case FUNCS:
        std::cout << "FUNCS";
        break;
    case FUNCDECL:
        std::cout << "FUNCDECL";
        break;
    case RETTYPE:
        std::cout << "RETTYPE";
        break;
    case FORMALS:
        std::cout << "FORMALS";
        break;
    case FORMALSLIST:
        std::cout << "FORMALSLIST";
        break;
    case FORMALDECL:
        std::cout << "FORMALDECL";
        break;
    case PRECONDITIONS:
        std::cout << "PRECONDITIONS";
        break;
    case PRECONDITION:
        std::cout << "PRECONDITION";
        break;
    case STATEMENTS:
        std::cout << "STATEMENTS";
        break;
    case STATEMENT:
        std::cout << "STATEMENT";
        break;
    case CALL:
        std::cout << "CALL";
        break;
    case EXPLIST:
        std::cout << "EXPLIST";
        break;
    case TYPE:
        std::cout << "TYPE";
        break;
    case EXP:
        std::cout << "EXP";
        break;
    default:
        std::cout << "?" << var << "?";
        break;
    };
}

void print_nullable(const std::vector<bool> &vec)
{
    std::cout << "Nullable:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i)
    {
        print_nonterminal((nonterminal)(i));
        std::cout << " = ";
        if (vec[i])
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_first(const std::vector<std::set<tokens> > &vec)
{
    std::cout << "First:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i)
    {
        print_nonterminal((nonterminal)(i));
        std::cout << " = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it)
        {
            if (it != vec[i].begin())
                std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_follow(const std::vector<std::set<tokens> > &vec)
{
    std::cout << "Follow:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i)
    {
        print_nonterminal((nonterminal)(i));
        std::cout << " = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it)
        {
            if (it != vec[i].begin())
                std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_select(const std::vector<std::set<tokens> > &vec)
{
    std::cout << "Select:" << std::endl;
    for (int i = 0; i < grammar.size(); ++i)
    {
        grammar_rule gr = grammar[i];
        std::cout << "( ";
        print_nonterminal((nonterminal)gr.lhs);
        std::cout << " -> ";
        for (int j = 0; j < gr.rhs.size(); ++j)
        {
            if (j > 0)
                std::cout << " ";
            if (gr.rhs[j] >= NONTERMINAL_ENUM_SIZE)
                print_token((tokens)gr.rhs[j]);
            else
                print_nonterminal((nonterminal)gr.rhs[j]);
        }
        std::cout << " ) = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it)
        {
            if (it != vec[i].begin())
                std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<grammar_rule> make_grammar()
{
    std::vector<grammar_rule> res;

    res.push_back(grammar_rule(PROGRAM, std::vector<int>(1, FUNCS)));

    res.push_back(grammar_rule(FUNCS, std::vector<int>()));
    int rule3[] = {FUNCDECL, FUNCS};
    res.push_back(grammar_rule(FUNCS, std::vector<int>(rule3,rule3+2)));

    int rule4[] = {RETTYPE, ID, LPAREN, FORMALS, RPAREN, PRECONDITIONS, LBRACE, STATEMENTS, RBRACE};
    res.push_back(grammar_rule(FUNCDECL, std::vector<int>(rule4, rule4 + 9)));

    res.push_back(grammar_rule(RETTYPE, std::vector<int>(1, TYPE)));    
    res.push_back(grammar_rule(RETTYPE, std::vector<int>(1, VOID)));

    res.push_back(grammar_rule(FORMALS, std::vector<int>()));
    res.push_back(grammar_rule(RETTYPE, std::vector<int>(1, FORMALSLIST)));

    res.push_back(grammar_rule(FORMALSLIST, std::vector<int>(1, FORMALDECL)));

    int rule10[] = {FORMALDECL, COMMA, FORMALSLIST};
    res.push_back(grammar_rule(FORMALSLIST, std::vector<int>(rule10, rule10+3)));

    int rule11[] = {TYPE, ID};
    res.push_back(grammar_rule(FORMALDECL, std::vector<int>(rule11, rule11+2)));

    res.push_back(grammar_rule(PRECONDITIONS, std::vector<int>()));
    int rule13[] = {PRECONDITIONS, PRECONDITION};
    res.push_back(grammar_rule(PRECONDITIONS, std::vector<int>(rule13, rule13+2)));

    int rule14[] = {PRECOND, LPAREN, EXP, RPAREN};
    res.push_back(grammar_rule(PRECONDITION, std::vector<int>(rule14, rule14+4)));

    res.push_back(grammar_rule(STATEMENTS, std::vector<int>(1, STATEMENT)));

    int rule16[] = {STATEMENTS, STATEMENT};
    res.push_back(grammar_rule(STATEMENTS, std::vector<int>(rule16, rule16+2)));

    int rule17[] = {LBRACE, STATEMENTS, RBRACE};
    int rule18[] = {TYPE, ID, SC};
    int rule19[] = {TYPE, ID, ASSIGN, EXP, SC};
    int rule20[] = {ID, ASSIGN, EXP, SC};
    int rule21[] = {CALL, SC};
    int rule22[] = {RETURN SC};
    int rule23[] = {RETURN, EXP, SC};
    int rule24[] = {IF, LPAREN, EXP, RPAREN, STATEMENT};
    int rule25[] = {IF, LPAREN, EXP, RPAREN, STATEMENT, ELSE, STATEMENT};
    int rule26[] = {WHILE, LPAREN, EXP, RPAREN, STATEMENT};
    int rule27[] = {BREAK, SC};
    int rule28[] = {CONTINUE, SC};
    
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule17, rule17+3)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule18, rule18+3)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule19, rule19+5)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule20, rule20+4)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule21, rule21+2)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule22, rule22+2)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule23, rule23+3)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule24, rule24+5)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule25, rule25+7)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule26, rule26+5)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule27, rule27+2)));
    res.push_back(grammar_rule(STATEMENT, std::vector<int>(rule28, rule28+2)));

    int rule29[] = {ID, LPAREN, EXPLIST, RPAREN};
    int rule30[] = {ID, LPAREN, RPAREN};
    
    res.push_back(grammar_rule(CALL, std::vector<int>(rule29, rule29+4)));
    res.push_back(grammar_rule(CALL, std::vector<int>(rule30, rule30+3)));

    int rule32[] = {EXP, COMMA, EXPLIST};

    res.push_back(grammar_rule(EXPLIST, std::vector<int>(1, EXP)));
    res.push_back(grammar_rule(EXPLIST, std::vector<int>(rule32, rule32+3)));

    res.push_back(grammar_rule(EXPLIST, std::vector<int>(1, INT)));
    res.push_back(grammar_rule(EXPLIST, std::vector<int>(1, BYTE)));
    res.push_back(grammar_rule(EXPLIST, std::vector<int>(1, BOOL)));

    int rule36[] = {LPAREN, EXP, RPAREN};
    int rule37[] = {EXP, BINOP, EXP};
    int rule41[] = {NUM, B};
    int rule45[] = {NOT, EXP};
    int rule46[] = {EXP, AND, EXP};
    int rule47[] = {EXP, OR, EXP};
    int rule48[] = {EXP, RELOP, EXP};

    res.push_back(grammar_rule(EXP, std::vector<int>(rule36, rule36+3)));
    res.push_back(grammar_rule(EXP, std::vector<int>(rule37, rule37+3)));

    res.push_back(grammar_rule(EXP, std::vector<int>(1, ID)));
    res.push_back(grammar_rule(EXP, std::vector<int>(1, CALL)));
    res.push_back(grammar_rule(EXP, std::vector<int>(1, NUM)));
    res.push_back(grammar_rule(EXP, std::vector<int>(rule41, rule41+2)));
    
    res.push_back(grammar_rule(EXP, std::vector<int>(1, STRING)));
    res.push_back(grammar_rule(EXP, std::vector<int>(1, TRUE)));
    res.push_back(grammar_rule(EXP, std::vector<int>(1, FALSE)));

    res.push_back(grammar_rule(EXP, std::vector<int>(rule45, rule45+2)));
    res.push_back(grammar_rule(EXP, std::vector<int>(rule46, rule46+3)));
    res.push_back(grammar_rule(EXP, std::vector<int>(rule47, rule47+3)));
    res.push_back(grammar_rule(EXP, std::vector<int>(rule48, rule48+3)));

    return res;
}

std::vector<grammar_rule> grammar = make_grammar();
