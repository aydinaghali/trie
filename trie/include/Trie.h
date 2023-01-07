#ifndef TRIE_H
#define TRIE_H

#include <cstdio>
#include <vector>

template <class T>
class Trie{
public:
	std::vector<T> keys;
	std::vector<Trie<T> *> children;
	T value;

	Trie();
	~Trie();
	void addItem(T key, Trie<T> *child);
	Trie *getItem(T key);
	Trie *getItem(std::vector<T> key);
	Trie *getItem(std::string key);
	Trie *operator[](T key);
	Trie *operator[](std::vector<T> key);
	Trie *operator[](std::string key);
	void deleteChildren();
	void addWord(T word[], int depth, int length);
	void addWord(std::vector<T> word);
	void addWord(std::string word);
	std::vector<std::vector<T> > getWords();
	std::vector<std::vector<T> > getWords(int depth);
};

/*template <class T>
class Trie{
public:
	Trie<T> *root;

	Trie();
	~Trie();
	void insert(std::vector<T> word);
};*/

template <class T>
Trie<T>::Trie(){	
}

template <class T>
Trie<T>::~Trie(){
	deleteChildren();
}

template <class T>
void Trie<T>::addItem(T key, Trie<T> *child){
	keys.push_back(key);
	children.push_back(child);
}

template <class T>
Trie<T> *Trie<T>::getItem(T key){
	for(int i=0; i<keys.size(); ++i){
		if(keys[i] == key){
			return children[i];
		}
	}	
	return NULL;
}

template <class T>
Trie<T> *Trie<T>::getItem(std::vector<T> key){
	Trie *result = this;
	for(int i=0; i<key.size(); ++i){
		result = result->getItem(key[i]);
		if(result == NULL) break;
	}

	return result;
}

template <>
Trie<char> *Trie<char>::getItem(std::string s){
	std::vector<char> key(s.begin(), s.end());
	return getItem(key);
}

template <class T>
Trie<T> *Trie<T>::operator[](T key){
	return getItem(key);
}

template <class T>
Trie<T> *Trie<T>::operator[](std::vector<T> key){
	return getItem(key);
}

template <>
Trie<char> *Trie<char>::operator[](std::string s){
	std::vector<char> key(s.begin(), s.end());
	return getItem(key);
}

template <class T>
void Trie<T>::deleteChildren(){
	for(int i=0; i<children.size(); ++i){
		delete children[i];
	}
}

template <class T>
void Trie<T>::addWord(T word[], int depth, int length){
	if(depth>=length) return;

	Trie *child = getItem(word[0]);
	if(child == NULL){
		child = new Trie();
		child->value = word[0];
		addItem(word[0], child);
	}
	child->addWord(word+1, depth+1, length);
}

template <class T>
void Trie<T>::addWord(std::vector<T> word){
	addWord(word.data(), 0, word.size());
}

template <>
void Trie<char>::addWord(std::string s){
	std::vector<char> word(s.begin(), s.end());
	addWord(word.data(), 0, word.size());
}

template <class T>
std::vector<std::vector<T> > Trie<T>::getWords(){
	return getWords(0);
}

template <class T>
std::vector<std::vector<T> > Trie<T>::getWords(int depth){
	std::vector<std::vector<T> > result;
	if(children.size() == 0){
		result.push_back(std::vector<T>(1, value));
		return result;
	}
	
	//printf("%lu\n", children.size());
	for(int i=0; i<children.size(); ++i){
		std::vector<std::vector<T> > child_words = children[i]->getWords(depth+1);
		for(int j=0; j<child_words.size(); ++j){
			if(depth!=0) child_words[j].insert(child_words[j].begin(), value);
			result.push_back(child_words[j]);
		}
	}

	return result;
}

/*template <class T>
Trie<T>::Trie(){
	root = new Trie<T>();	
}

template <class T>
Trie<T>::~Trie(){
	delete root;
}

template <class T>
void Trie<T>::insert(std::vector<T> word){
	for(int i=0; i<word.size(); ++i){
		
	}
}*/

#endif
