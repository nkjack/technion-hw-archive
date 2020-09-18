#include "hw2.h"
#include <iostream>



std::vector<bool> compute_nullable_helper(){
	std::vector<nonterminal> prev;
	std::vector<nonterminal> curr;

	for (int i = 0; i < grammar.size(); ++i)
    {
        grammar_rule gr = grammar[i];
        
        if (gr.rhs.size() == 0){
        	prev.push_back((nonterminal)gr.lhs);
        	curr.push_back((nonterminal)gr.lhs);
        }

    }

    bool had_changes = true;
    while (had_changes)
    {
    	had_changes = false;
    
    	for (int i = 0; i < grammar.size(); ++i)
	    {
	        grammar_rule gr = grammar[i];
	   		

			if(std::find(prev.begin(), prev.end(), gr.lhs) == prev.end()) {
			    /* prev contains x */

				bool tmp_bool = true;
				for (int j = 0; j < gr.rhs.size(); j++){
					if(std::find(prev.begin(), prev.end(), gr.rhs[j]) == prev.end()) {
						tmp_bool = false;
					}
				}
				if (tmp_bool){
					curr.push_back((nonterminal)gr.lhs);
					had_changes = true;
				}
	    	}
		}
		prev = curr; // deep copy because no pointers
	} 
	
	// create a std::vector<bool> where nonterminal
	std::vector<bool> nullabels;

	for ( int nonterminal = S; nonterminal != NONTERMINAL_ENUM_SIZE; nonterminal++ )
	{
	   if(std::find(curr.begin(), curr.end(), nonterminal) != curr.end()) 
	   {
	   		//found
	   		nullabels.push_back(true);
	   }
	   else{
	   		nullabels.push_back(false);
	   }
	}
	return nullabels;
}

void compute_nullable(){
	
	print_nullable(compute_nullable_helper());
	
}


std::vector<std::set<tokens> > compute_first_helper(){
	// compute nullabels
	std::vector<bool> nullabels = compute_nullable_helper();
	
	// intiate non-teminals variables with empty set
	std::vector<std::set<tokens> > nonterminals;
	for ( int nonterminal = S; nonterminal != NONTERMINAL_ENUM_SIZE; nonterminal++ )
	{
	   nonterminals.push_back(std::set<tokens>()); // initiate empty set 
	}

	bool had_changes = true;
	while(had_changes){
		had_changes = false;

		for (int i = 0; i < grammar.size(); ++i)
	    {
	        grammar_rule gr = grammar[i];
	   			
	        if (gr.rhs.size() > 0){

	        	// first(gr.lhs) = first(gr.lhs) V first(gr.rhs[0])
	        	if (gr.rhs[0] <= NONTERMINAL_ENUM_SIZE){
	        		// a non terminal
			        for (std::set<tokens>::const_iterator it = nonterminals[gr.rhs[0]].begin(); 
			        	it != nonterminals[gr.rhs[0]].end(); ++it)
			        {
			        	// check if token in first of lhs
			            if(std::find(nonterminals[gr.lhs].begin(), 
				        			nonterminals[gr.lhs].end(), 
				        			*it) == nonterminals[gr.lhs].end()) { 
						    
						    /* not contains terminal */
							nonterminals[gr.lhs].insert(*it);
							had_changes = true;
				    	}
			        }
	        	}
	        	else{
	        		if(std::find(nonterminals[gr.lhs].begin(), 
	        			nonterminals[gr.lhs].end(), 
	        			gr.rhs[0]) == nonterminals[gr.lhs].end()) {
					    
					    /* not contains terminal */
					    int token_to_insert = (int)gr.rhs[0];
						nonterminals[gr.lhs].insert((tokens)token_to_insert);
						had_changes = true;
			    	}
	        	}
	        
	        	bool bool_tmp = true;
	        	for (int j=0; j < gr.rhs.size()-1; j++){
	        		if ((gr.rhs[j] <= NONTERMINAL_ENUM_SIZE) &&
	        			(nullabels[gr.rhs[j]] == true) &&
	        			(bool_tmp == true)){

	        			if (gr.rhs[j+1] <= NONTERMINAL_ENUM_SIZE){
			        		
			        		// a non terminal
					        for (std::set<tokens>::const_iterator it = nonterminals[gr.rhs[j+1]].begin(); 
					        	it != nonterminals[gr.rhs[j+1]].end(); ++it)
					        {
					        	// check if token in first of lhs
					            if(std::find(nonterminals[gr.lhs].begin(), 
						        			nonterminals[gr.lhs].end(), 
						        			*it) == nonterminals[gr.lhs].end()) { 
								    
								    /* not contains terminal */
									nonterminals[gr.lhs].insert(*it);
									had_changes = true;
						    	}
					        }
			        	}
			        	else{
			        		if(std::find(nonterminals[gr.lhs].begin(), 
			        			nonterminals[gr.lhs].end(), 
			        			gr.rhs[j+1]) == nonterminals[gr.lhs].end()) {
							    
							    /* not contains terminal */
								nonterminals[gr.lhs].insert((tokens)gr.rhs[j+1]);
								had_changes = true;
					    	}
			        	}
	        		}
	        		else{
	        			bool_tmp = false;
	        		}
	        	}
	        }
		}
	}
	return nonterminals;
}

void compute_first(){
	print_first(compute_first_helper());
}


std::set<tokens> compute_first_pasuk(std::vector<int> pasuk){
	
	std::vector<std::set<tokens> > nonterminals = compute_first_helper();
	std::vector<bool> nullabels = compute_nullable_helper();

	std::set<tokens> first_to_return;

	if (pasuk.size() > 0){

		// add first(pasuk[0]) to first_to_return
		if (pasuk[0] <= NONTERMINAL_ENUM_SIZE){
			// terminal
			first_to_return.insert(nonterminals[pasuk[0]].begin(), nonterminals[pasuk[0]].end());
			if (nullabels[pasuk[0]] == false){
				return first_to_return;
			}
		}
		else{
			// non terminal
			first_to_return.insert((tokens)pasuk[0]);
			return first_to_return; // because not nullable
		}


		bool bool_tmp = true;
    	for (int i=0; i < pasuk.size()-1; i++){
    		if ((pasuk[i] <= NONTERMINAL_ENUM_SIZE) &&
    			(nullabels[pasuk[i]] == true) &&
    			(bool_tmp == true)){

    			if (pasuk[i+1] <= NONTERMINAL_ENUM_SIZE){
	        		// a non terminal
    				first_to_return.insert(nonterminals[pasuk[i+1]].begin(), nonterminals[pasuk[i+1]].end());
	        	}
	        	else{
	        		// non terminal
					first_to_return.insert((tokens)pasuk[i+1]);
					bool_tmp = false;
	        	}
    		}
    		else{
    			bool_tmp = false;
    		}
    	}
	}

	return first_to_return;
}


bool check_if_pasuk_nullable(std::vector<int> pasuk){
	std::vector<bool> nullabels = compute_nullable_helper();

	bool tmp = true;
	for (int i=0; i<pasuk.size(); i++){
		if (pasuk[i] > NONTERMINAL_ENUM_SIZE){
			tmp = false;
		}
		if (nullabels[pasuk[i]] == false){
			tmp = false;
		}
	}
	return tmp;

}


template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    typename std::vector<T>::const_iterator first = v.begin() + m;
    typename std::vector<T>::const_iterator last = v.begin() + n + 1;
 
    std::vector<T> vec(first, last);
    return vec;
}

std::vector<std::set<tokens> > compute_follow_helper(){
	//initiate
	std::vector<std::set<tokens> > nonterminals;

	for ( int nonterminal = S; nonterminal != NONTERMINAL_ENUM_SIZE; nonterminal++ )
	{
		if (nonterminal == S){
			nonterminals.push_back(std::set<tokens>()); // initiate empty set 
			nonterminals[S].insert(EF); // insert dollar
		}
		else{
	   		nonterminals.push_back(std::set<tokens>()); // initiate empty set 
	    }
	}


	bool had_changes = true;

	while(had_changes){
		had_changes = false;

		for ( int nonterminal = S; nonterminal != NONTERMINAL_ENUM_SIZE; nonterminal++ )
		{
			for (int i=0; i<grammar.size();i++){
				
				grammar_rule gr = grammar[i];

				// bool is_non_term_in_gr = false;

				if (gr.rhs.size() > 0){
					for (int j=0; j<gr.rhs.size(); j++){
						if (gr.rhs[j] == nonterminal){
							// found A in rhs
							if (j < gr.rhs.size()-1){
								std::vector<int> sub_vec = slice(gr.rhs, j+1, gr.rhs.size()-1);
								std::set<tokens> first_of_pasuk =  compute_first_pasuk(sub_vec);

								// check if there is a token if first that not in follow
								bool tmp_had_changes = false;
								for (std::set<tokens>::const_iterator it = first_of_pasuk.begin(); 
									it != first_of_pasuk.end();
									it++)
								{
									if(std::find(nonterminals[nonterminal].begin(), 
										nonterminals[nonterminal].end(), 
										*it) == nonterminals[nonterminal].end()) {
										// not found
										tmp_had_changes = true; // we changes
							    	}
						    	}
								
								if (tmp_had_changes){
									nonterminals[nonterminal].insert(first_of_pasuk.begin(), first_of_pasuk.end());
									had_changes = true;	
								}

								if (check_if_pasuk_nullable(sub_vec)){
									// add follow of terminal to lhs
									bool tmp_had_changes = false;
									for (std::set<tokens>::const_iterator it = nonterminals[gr.lhs].begin(); 
										it != nonterminals[gr.lhs].end();
										it++)
									{
										if(std::find(nonterminals[nonterminal].begin(), 
											nonterminals[nonterminal].end(), 
											*it) == nonterminals[nonterminal].end()) {
											// not found
											tmp_had_changes = true; // we changes
								    	}
							    	}
							    	if (tmp_had_changes){
										nonterminals[nonterminal].insert(nonterminals[gr.lhs].begin(), 
																	nonterminals[gr.lhs].end());
										had_changes = true;	
									}
								}
							}
							else if ((j == gr.rhs.size()-1)){
								bool tmp_had_changes = false;
								for (std::set<tokens>::const_iterator it = nonterminals[gr.lhs].begin(); 
									it != nonterminals[gr.lhs].end();
									it++)
								{
									if(std::find(nonterminals[nonterminal].begin(), 
										nonterminals[nonterminal].end(), 
										*it) == nonterminals[nonterminal].end()) 
									{
										// not found
										tmp_had_changes = true; // we changes
							    	}
						    	}
						    	if (tmp_had_changes){
									nonterminals[nonterminal].insert(nonterminals[gr.lhs].begin(), 
																nonterminals[gr.lhs].end());
									had_changes = true;	
								}
							}
						}
					}
				}
			}
		}
	}
	return nonterminals;
}

void compute_follow(){
	print_follow(compute_follow_helper());
}


std::vector<std::set<tokens> > compute_select_helper(){
	std::vector<std::set<tokens> > rules_select;
	std::vector<std::set<tokens> > nonterminals_follow = compute_follow_helper();

	for (int i=0; i<grammar.size(); i++)
	{
		grammar_rule gr = grammar[i];
		rules_select.push_back(std::set<tokens>());

		if (check_if_pasuk_nullable(gr.rhs)){
			// pasuk nullable
			// select = first(pasuk) U follow(gr.lhs)
			std::set<tokens> first_of_pasuk = compute_first_pasuk(gr.rhs);
			rules_select[i].insert(first_of_pasuk.begin(), first_of_pasuk.end());
			rules_select[i].insert(nonterminals_follow[gr.lhs].begin(),
									nonterminals_follow[gr.lhs].end());
		}
		else{
			// select = first(pasuk)
			std::set<tokens> first_of_pasuk = compute_first_pasuk(gr.rhs);
			rules_select[i].insert(first_of_pasuk.begin(), first_of_pasuk.end());
		}
	}
	return rules_select;
}

void compute_select(){
	print_select(compute_select_helper());
}

bool match(tokens X, tokens t){
	return X==t;
}

void predict(nonterminal X, tokens t){

}

void parser(){
	std::vector<int> Q;
	//init Q with S
	Q.push_back(S);

	// map <nonterminal, map<token, rule_index>
	std::map<nonterminal,std::map<tokens,int> > M;
	std::vector<std::set<tokens> > rules_select = compute_select_helper();

	// init M
	/*
		for each rule in grammar:
			take select of rule:
				for each terminal in select:
					add to M:
						- <rule.lhs, <terminal, rule_index>>
	*/

	for (int i=0; i<grammar.size(); i++){
		grammar_rule gr = grammar[i];
		
		std::set<tokens> gr_select = rules_select[i];
		std::map<tokens,int> map_for_rule;

		for (std::set<tokens>::const_iterator it=gr_select.begin(); it != gr_select.end(); it++){
			// add to map_for_rule <*it, i>
			map_for_rule.insert(std::make_pair(*it, i));
		}
		// if gr.lhs in M, add map_for_rule
		std::map<nonterminal,std::map<tokens,int> >::iterator it = M.find((nonterminal)gr.lhs);
		if (it != M.end()){
			(it->second).insert(map_for_rule.begin(),map_for_rule.end());
		}
		else{
			M.insert(std::make_pair(gr.lhs, map_for_rule));
		}
	}


	int t = yylex();
	// for (int i=0; i<20;i++){
	// 	print_token((tokens)t);
	// 	std::cout << std::endl;
	// 	t = yylex();
	// }
	
	while (!Q.empty())
	{
		// print_token((tokens)t);
		// std::cout << std::endl;

		int X = Q.back();
		Q.pop_back();
		if (X < NONTERMINAL_ENUM_SIZE){
			// non terminal
			// predict M(X,t)

			std::map<nonterminal,std::map<tokens,int> >::iterator it1 = M.find((nonterminal)X);
			if (it1 != M.end()){
				// (it->second).insert(map_for_rule.begin(),map_for_rule.end());
				// find by t
				std::map<tokens,int>::iterator it2 = (it1->second).find((tokens)t);

				if (it2 != (it1->second).end()){
					// assuming no conflicts
					int num_rule = it2->second;
					std::cout << num_rule+1 << "\n";

					grammar_rule gr = grammar[num_rule];
					for (int i=gr.rhs.size()-1; i >= 0; i--){
						Q.push_back(gr.rhs[i]);
					}

				}
				else{
					// not found t
					std::cout << "Syntax error\n";
					return;
				}

			}
			else{
				// not found X
				std::cout << "Syntax error\n";
				return;
			}
		}
		else{
			// terminal
			if (!match((tokens)X,(tokens)t)){
				std::cout << "Syntax error\n";
				return;
			}
			t = yylex();
		}
	}
	
	if (t == EF){
		std::cout << "Success\n";
	}
	else{
		std::cout << "Syntax error\n";	
	}
	

	/*
	 init - push S to Q, t is the next terminal in input

	 1. (isEmpty(Q)):
	 	- if t==EF, report success
	 	- else, report error

	 2. else:
	 	- X = top(Q)
	 	- if (X is terminal)
	 		- Match(X,t)
	 	- if (X is variable)
	 		- Predict(X,t)

	 3. goto 1
	 */
}

