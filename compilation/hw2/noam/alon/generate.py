#! /usr/bin/env python3
from nltk import CFG, ChartParser
from random import choice

def produce(grammar, symbol):
    words = []
    productions = grammar.productions(lhs = symbol)
    production = choice(productions)
    for sym in production.rhs():
        if isinstance(sym, str):
            words.append(sym)
        else:
            words.extend(produce(grammar, sym))
    return words

	
grammar = CFG.fromstring("""
 S -> LImports LRules
 LImports -> Import LImports | 
 Import -> '@import' '"string"' ';'
 LRules -> Rule LRules | 
 Rule -> Selectors '{' LDeclaretions '}'
 LDeclaretions -> Declaration ';' MoreDeclerations
 MoreDeclerations -> LDeclaretions | 
 Selectors -> SimpleSelector MoreSelectors
 MoreSelectors -> Selectors | 
 SimpleSelector -> Astrisk SelectorModifier
 Astrisk -> '*' | 
 SelectorModifier -> '.' 'name' | ':' 'name' | '[' 'name' '=' Term ']' | '#hashid' | 'name'
 Declaration -> 'name' ':' LTerms Important
 Important -> '!ImPoRtAnT' | 
 LTerms -> Term MoreTerms
 MoreTerms -> LTerms | 
 Term -> '1337' | '15%' | '"string"' | 'name' | '#hashid'
 """)

parser = ChartParser(grammar)
gr = parser.grammar()
print(' '.join(produce(gr, gr.start())))
