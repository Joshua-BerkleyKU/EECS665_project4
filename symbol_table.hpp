#ifndef CSHANTYC_SYMBOL_TABLE_HPP
#define CSHANTYC_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using namespace std;

namespace cshanty{

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols 
// exist for the lifetime of a scope in the 
// symbol table. 
class SemSymbol {
	//TODO add the fields that 
	// each semantic symbol should track
	// (i.e. the kind of the symbol (either a variable or function)
	// and functions to get/set those fields
	public:
		SemSymbol(std::string  * name, std::string * kind): Name(name), Kind(kind) {}
		void setName(std::string * name) { Name = name; }
		void setKind(std::string * kind) { Kind = kind; }
		std::string * getName() { return Name; }
		std::string * getKind() { return Kind; }
	private:
		std::string * Name;
		std::string * Kind;
};

//A single scope. The symbol table is broken down into a 
// chain of scope tables, and each scope table holds 
// semantic symbols for a single scope. For example,
// the globals scope will be represented by a ScopeTable,
// and the contents of each function can be represented by
// a ScopeTable.
class ScopeTable {
	public:
		ScopeTable() {
			symbols = new HashMap<std::string, SemSymbol *>();
		}
		bool insert(std::string id, SemSymbol * symbol) {
			std::pair<std::string, SemSymbol *> item(id, symbol);
			return symbols->insert(item).second;
		}
		SemSymbol * lookup(std::string id) {
			std::unordered_map<std::string, SemSymbol *>::const_iterator item = symbols->find(id);
			if (item == symbols->end()) {
				std::string errorMsg = "No item found in hashtable with id " + id;
				InternalError error(errorMsg.c_str());
				throw error;
			} else {
				return item->second;
			}
		}
	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		//TODO: add functions to create a new ScopeTable
		// when a new scope is entered, drop a ScopeTable
		// when a scope is exited, etc. 
	private:
		std::list<ScopeTable *> * scopeTableChain;
};

	
}

#endif
