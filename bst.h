#ifndef BST_H
#define BST_H

template <class dataType>
class bst
{   
   public:
      bst();
      bool insert (const dataType &);
      bool empty() const;
      bool search (const dataType &) const;
      void get_top_similar_words(const dataType& word, std::vector<std::pair<dataType, int>>& top_words) const;
      void preorder_save (std::ofstream& file) const;
      void graph() const;
      void remove (const dataType &);
      
   private:
	   class treeNode
	   {
		public:
			dataType data;	
			treeNode *left;		       
			treeNode *right;	
	   }; 

	   typedef treeNode * NodePointer;
      NodePointer root;
	  
      bool search2 (NodePointer , const dataType &) const;
      bool insert2 (NodePointer &, const dataType &);
      void get_top_similar_words2 (NodePointer, const dataType&, std::vector<std::pair<dataType, int>>&) const; 
	   void graph2 (int ,NodePointer ) const;
      void parentSearch ( const dataType &d, bool &found, 
							NodePointer &locptr, NodePointer &parent) const;
      int hamming_distance(const dataType& word1, const dataType& word2) const;
}; 
#include "bst.cpp"
#endif 
