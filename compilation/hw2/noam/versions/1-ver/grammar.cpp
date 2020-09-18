#include "tokens.h"
#include "grammar.h"
#include "hw2.h"
#include <iostream>

void print_token(tokens tok)
{
    switch (tok)
    {
    case IMPORTANT:
        std::cout << "IMPORTANT";
        break;
    case NAME:
        std::cout << "NAME";
        break;
    case HASHID:
        std::cout << "HASHID";
        break;
    case IMPORT:
        std::cout << "IMPORT";
        break;
    case STRING:
        std::cout << "STRING";
        break;
    case COMB:
        std::cout << "COMB";
        break;
    case COLON:
        std::cout << "COLON";
        break;
    case SEMICOLON:
        std::cout << "SEMICOLON";
        break;
    case COMMA:
        std::cout << "COMMA";
        break;
    case LBRACE:
        std::cout << "LBRACE";
        break;
    case RBRACE:
        std::cout << "RBRACE";
        break;
    case LBRACKET:
        std::cout << "LBRACKET";
        break;
    case RBRACKET:
        std::cout << "RBRACKET";
        break;
    case EQUAL:
        std::cout << "EQUAL";
        break;
    case ASTERISK:
        std::cout << "ASTRISK";
        break;
    case DOT:
        std::cout << "DOT";
        break;
    case NUMBER:
        std::cout << "NUMBER";
        break;
    case UNIT:
        std::cout << "UNIT";
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
    case S:
        std::cout << "S";
        break;
    case LImports:
        std::cout << "LImports";
        break;
    case Import:
        std::cout << "Import";
        break;
    case LRules:
        std::cout << "LRules";
        break;
    case Rule:
        std::cout << "Rule";
        break;
    case LDeclarations:
        std::cout << "LDeclaretions";
        break;
    case MoreDeclarations:
        std::cout << "MoreDeclerations";
        break;
    case Selectors:
        std::cout << "Selectors";
        break;
    case MoreSelectors:
        std::cout << "MoreSelectors";
        break;
    case SimpleSelector:
        std::cout << "SimpleSelector";
        break;
    case Astrisk:
        std::cout << "Astrisk";
        break;
    case SelectorModifier:
        std::cout << "SelectorModifier";
        break;
    case Declaration:
        std::cout << "Declaration";
        break;
    case Important:
        std::cout << "Important";
        break;
    case LTerms:
        std::cout << "LTerms";
        break;
    case MoreTerms:
        std::cout << "MoreTerms";
        break;
    case Term:
        std::cout << "Term";
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

    int rule1[] = {LImports, LRules};
    res.push_back(grammar_rule(S, std::vector<int>(rule1, rule1 + 2)));

    int rule2[] = {Import, LImports};
    res.push_back(grammar_rule(LImports, std::vector<int>(rule2, rule2 + 2)));
    res.push_back(grammar_rule(LImports, std::vector<int>()));

    int rule4[] = {IMPORT, STRING, SEMICOLON};
    res.push_back(grammar_rule(Import, std::vector<int>(rule4, rule4 + 3)));

    int rule5[] = {Rule, LRules};
    res.push_back(grammar_rule(LRules, std::vector<int>(rule5, rule5 + 2)));
    res.push_back(grammar_rule(LRules, std::vector<int>()));

    int rule7[] = {Selectors, LBRACE, LDeclarations, RBRACE};
    res.push_back(grammar_rule(Rule, std::vector<int>(rule7, rule7 + 4)));

    int rule8[] = {Declaration, SEMICOLON, MoreDeclarations};
    res.push_back(grammar_rule(LDeclarations, std::vector<int>(rule8, rule8 + 3)));

    res.push_back(grammar_rule(MoreDeclarations, std::vector<int>(1, LDeclarations)));
    res.push_back(grammar_rule(MoreDeclarations, std::vector<int>()));

    int rule11[] = {SimpleSelector, MoreSelectors};
    res.push_back(grammar_rule(Selectors, std::vector<int>(rule11, rule11 + 2)));

    res.push_back(grammar_rule(MoreSelectors, std::vector<int>(1, Selectors)));
    res.push_back(grammar_rule(MoreSelectors, std::vector<int>()));

    int rule14[] = {Astrisk, SelectorModifier};
    res.push_back(grammar_rule(SimpleSelector, std::vector<int>(rule14, rule14 + 2)));

    res.push_back(grammar_rule(Astrisk, std::vector<int>(1, ASTERISK)));
    res.push_back(grammar_rule(Astrisk, std::vector<int>()));

    int rule17[] = {DOT, NAME};
    int rule18[] = {COLON, NAME};
    int rule19[] = {LBRACKET, NAME, EQUAL, Term, RBRACKET};
    res.push_back(grammar_rule(SelectorModifier, std::vector<int>(rule17, rule17 + 2)));
    res.push_back(grammar_rule(SelectorModifier, std::vector<int>(rule18, rule18 + 2)));
    res.push_back(grammar_rule(SelectorModifier, std::vector<int>(rule19, rule19 + 5)));
    res.push_back(grammar_rule(SelectorModifier, std::vector<int>(1, HASHID)));
    res.push_back(grammar_rule(SelectorModifier, std::vector<int>(1, NAME)));

    int rule22[] = {NAME, COLON, LTerms, Important};
    res.push_back(grammar_rule(Declaration, std::vector<int>(rule22, rule22 + 4)));

    res.push_back(grammar_rule(Important, std::vector<int>(1, IMPORTANT)));
    res.push_back(grammar_rule(Important, std::vector<int>()));

    int rule25[] = {Term, MoreTerms};
    res.push_back(grammar_rule(LTerms, std::vector<int>(rule25, rule25 + 2)));

    res.push_back(grammar_rule(MoreTerms, std::vector<int>(1, LTerms)));
    res.push_back(grammar_rule(MoreTerms, std::vector<int>()));

    res.push_back(grammar_rule(Term, std::vector<int>(1, NUMBER)));
    res.push_back(grammar_rule(Term, std::vector<int>(1, UNIT)));
    res.push_back(grammar_rule(Term, std::vector<int>(1, STRING)));
    res.push_back(grammar_rule(Term, std::vector<int>(1, NAME)));
    res.push_back(grammar_rule(Term, std::vector<int>(1, HASHID)));

    return res;
}

std::vector<grammar_rule> grammar = make_grammar();
