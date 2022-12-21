#pragma once

#include <unordered_map>

// This class is in charge of the hashing in the program.
// It's a template class which builds a hash table based on given 
// parameters and manages it.
 template <typename T, typename U> 
 class HashTable 
 {
 public:
	 // C-tor and d-tor.
	 HashTable(std::unordered_map<T,U> map);
	~HashTable() = default;

	// Management.
	void setKey(T key , U val) { this->m_map[key] = val; }
	U getVal(T key) { return this->m_map[key]; }
 private:
	 std::unordered_map<T, U> m_map; // Data structure.
};

 // C-tor.
 template<typename T, typename U>
 inline HashTable<T, U>::HashTable(std::unordered_map<T, U> map)
	 : m_map(map)
 {}
