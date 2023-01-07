#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"

int main(){	

	std::ifstream dict_file;
	dict_file.open("../words.txt");
	std::vector<std::string> words;
	if(dict_file.is_open()){
		char c;
		std::string str;
		while(dict_file){
			c = dict_file.get();
			if(c == '\n'){
				words.push_back(str);
				str = "";
			}else{
				str.push_back(c);
			}
		}
	}

	Trie<char> t = Trie<char>();
	for(int i=0; i<words.size(); ++i){
		t.addWord(words[i]);
	}

	while(true){
		std::string search;
		std::cout<<"Search: ";
		std::getline(std::cin, search);
		
		if(search == std::string("")) continue;

		Trie<char> *node = t[search];
		if(node == NULL){
			std::cout<<"Word not found\n";
			continue;
		}
		std::vector<std::vector<char> > w = node->getWords();	
		for(int i=0; i<w.size(); ++i){
			std::cout<<i+1<<". ";
			std::string result = search;
			for(int j=0; j<w[i].size(); ++j){
				result.push_back(w[i][j]);
			}
			std::cout<<result;
			std::cout<<std::endl;
		}

	}

	return 0;
}

