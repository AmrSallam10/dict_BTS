#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stack>
#include "bst.h"
using namespace std;

template <class dataType>
bst<dataType>::bst()
{ root = NULL; }

template <class dataType>
bool bst<dataType>::search(const dataType &k) const  
{
   return search2(root, k); 
} 

template <class dataType>
bool bst<dataType>::search2(NodePointer aRoot,
									 const dataType &d)	const
{
    if (aRoot == NULL)      
		return false;                     
    else if (d == aRoot->data)
		return true; 
    else if (d < aRoot->data)
		return search2(aRoot->left, d); 
    else
		return search2(aRoot->right, d); 
}

template <class dataType>
bool bst<dataType>::insert(const dataType &d)
{    
	return insert2 (root, d);
} 

template <class dataType>
bool bst<dataType>::insert2(NodePointer &aRoot, const dataType &d)
{  

  if (aRoot == NULL)
  { 
    aRoot = new treeNode; 
    aRoot->left = NULL; 
    aRoot->right = NULL;
	aRoot->data = d;
    return true;
  }
  else if (d == aRoot->data)
    return false;  
  else if (d < aRoot->data)
    return insert2 (aRoot->left, d); 
  else
    return insert2 (aRoot->right, d); 
} 

template <class dataType>
bool bst<dataType>::empty() const
{
   return(root == NULL);
} 

template <class dataType>
void bst<dataType>::get_top_similar_words(const dataType& word, std::vector<std::pair<dataType, int>>& top_words) const
{
	get_top_similar_words2 (root, word, top_words);
} 

template <class dataType>
void bst<dataType>::get_top_similar_words2 (NodePointer aRoot, const dataType& word, 
		std::vector<std::pair<dataType, int>>& top_words) const       
{
   if (aRoot != NULL)
   { 
     get_top_similar_words2 (aRoot->left, word, top_words);       
		int distance = hamming_distance(aRoot->data, word);
		sort(top_words.begin(), top_words.end(), [](const pair<dataType, int>& a, const pair<dataType, int>& b) { 
			return a.second < b.second; });
		if (top_words.size() < 5)
			top_words.push_back(make_pair(aRoot->data, distance));
		else if (distance < top_words.back().second)
		{
			top_words.pop_back();
			top_words.push_back(make_pair(aRoot->data, distance));
		}
     get_top_similar_words2 (aRoot->right, word, top_words); 
   }
   
}

template <class dataType>
void bst<dataType>::preorder_save (std::ofstream& file) const       
{
	stack<NodePointer> s;
	NodePointer t = root;
	s.push(t);
	while(!s.empty())
	{
		t = s.top();
		s.pop(); 
		file << t->data <<" ";
		if ( t->right != NULL ) s.push(t->right);
		if ( t->left  != NULL ) s.push (t->left);
	}
	file << '\n';
}

template <class dataType>
void bst<dataType>::graph() const
{
	graph2 (0 , root);
}

template <class dataType>
void bst<dataType>::graph2(int indent, NodePointer aRoot) const
{
	if (aRoot != NULL)
	{
      graph2 (indent+8, aRoot->right);           
      cout << setw(indent) << " " << aRoot->data << endl; 
      graph2 (indent+8, aRoot->left); 
	}
}
	  
template <class dataType>
void bst<dataType>::remove (const dataType &d)
{
	bool found;
	NodePointer x,parent;
	parentSearch (d, found, x, parent);
	if (!found)
	{
		cout << "Item not in BST\n"; 
		return;
	}
	if ((x->left != NULL)&&(x->right != NULL))
	{	
		NodePointer xSucc = x->right;
		parent = x;
		while (xSucc->left != NULL) 
		{ parent = xSucc; xSucc = xSucc->left; }
		x->data = xSucc->data;
		x = xSucc;
	} 
	NodePointer subtree = x->left; 
	if (subtree == NULL) subtree = x->right;
	if (parent == NULL) root = subtree; 
	else if (parent->left == x) 
		parent->left = subtree;
	else parent->right = subtree; 
	delete x;
} 

template <class dataType>
void bst<dataType>::parentSearch (const dataType &d, 
											bool &found, 
											NodePointer &locptr,
				   							NodePointer &parent) const
{
	locptr = root;  parent = NULL; found = false;
	while (!found && locptr != NULL)
	{
		if (d < locptr->data)
		{
			parent = locptr;	locptr = locptr->left;
		}
		else if (locptr->data < d)
		{
			parent = locptr;	locptr = locptr->right;
		}
		else found = true;
	}
} 

template <class dataType>
int bst<dataType>::hamming_distance(const dataType& word1, const dataType& word2) const
{
    int m = std::min(word1.size(), word2.size());
    int M = std::max(word1.size(), word2.size());
    int matches = 0;
    for (int i = 0; i < m; i++) 
        if (word1[i] == word2[i])
            matches++;
			
    return M - matches;
}