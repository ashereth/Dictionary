/***
* Creates a dictionary of key/value pairs using a BST ADT
***/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

// Helper Functions ---------------------------------------------

//transplant()
//used with remove for certain cases
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent==this->nil){
        this->root=v;
    }else if (u==u->parent->left)
    {
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    if(v!=nil){
        v->parent=u->parent;
    }
    
}

void Dictionary::postOrderDelete(Node* R){
    if(R==nil){
        return;
    }
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    delete R;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != nil) { 
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if (R != nil && R!=N) { 
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    /*if x == NIL or k == x.key
      return x
    else if k < x.key
      return TreeSearch(x.left, k)
    else // k > x.key
      return TreeSearch(x.right, k)*/
    if(R==nil || R->key==k){
        return R;
    }else if (k.compare(R->key)<0)
    {
        return search(R->left, k);
    }else{
        return search(R->right, k);
    }
} 


// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    while(R->left!=nil){
        R=R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    while(R->right!=nil){
        R=R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    //if N is the rightmost node or nil return nil
    if(this->findMax(this->root)==N || N==nil){
        return nil;
    }
    // If N has a right child, find the leftmost node in its right subtree
    if (N->right != nil) {
        Node* nextNode = N->right;
        while (nextNode->left != nil) {
            nextNode = nextNode->left;
        }
        return nextNode;
    }

    // If N doesn't have a right child, move up the tree until finding the first ancestor
    // where the current node is in the left subtree
    Node* parent = N->parent;
    while (parent != nil && N == parent->right) {
        N = parent;
        parent = parent->parent;
    }

    return parent;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    //if N is the leftmost node or nil return nil
    if(this->findMin(this->root)==N || N==nil){
        return nil;
    }
    // If N has a left child, find the rightmost node in its left subtree
    if (N->left != nil) {
        Node* prevNode = N->left;
        while (prevNode->right != nil) {
            prevNode = prevNode->right;
        }
        return prevNode;
    }

    // If N doesn't have a left child, move up the tree until finding the first ancestor
    // where the current node is in the right subtree
    Node* parent = N->parent;
    while (parent != nil && N == parent->left) {
        N = parent;
        parent = parent->parent;
    }

    return parent;
}


// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
    Node* empty = new Node("", 0);
    empty->parent = nullptr;
    empty->left = nullptr;
    empty->right = nullptr;

    // Set root/nil/current to be the new dummy node
    root = empty;
    nil = empty;
    current = nil;

    // Set number of pairs to be 0 initially
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    Node* empty = new Node("", 0);
    empty->parent = nullptr;
    empty->left = nullptr;
    empty->right = nullptr;

    // Set root/nil/current to be the new dummy node
    root = empty;
    nil = empty;
    current = nil;

    // Set number of pairs to be 0 initially
    num_pairs = 0;
    //call preorder copy starting from D's root and going to D's nil Node
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return this->num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if(this->search(this->root, k)!=nil){
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(!this->contains(k)){
        throw std::out_of_range("getValue(): key does not exist");
    }
    Node* value = this->search(this->root, k);
    return value->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(this->current!=nil){
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(!this->hasCurrent()){
        throw std::out_of_range("currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!this->hasCurrent()){
        throw std::out_of_range("currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // If key already exists, update value
    Node* existingNode = this->search(root, k);
    
    if (existingNode != nil) {
        existingNode->val = v;
    } else {
        // Key doesn't exist, insert new pair (k, v)
        this->num_pairs++;
        Node* z = new Node(k, v);
        Node* y = nil;
        Node* x = root;
        z->left = nil;
        z->right = nil;
        while (x != nil) {
            y = x;
            if (k.compare(x->key) < 0) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil) {
            this->root = z;
            root->parent=nil;
        } else if (k.compare(y->key) < 0) {
            y->left = z;
            z->parent = y;
        } else {
            y->right = z;
            z->parent = y;
        }
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(!this->contains(k)){
        throw std::out_of_range("remove(): key does not exist");
    }
    Node* z = this->search(this->root, k);
    if(z==current){//if we are removing the current then make current nil
        current=nil;
    }
    if(z->left==nil){
        transplant(z, z->right);
    }else if (z->right==nil)
    {
        transplant(z, z->left);
    }else{
        Node* y = this->findMin(z->right);
        if(y->parent!=z){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    //decriment num_pairs
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(num_pairs>0){
        current = this->findMin(this->root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(num_pairs>0){
        current = this->findMax(this->root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(!this->hasCurrent()){
        throw std::out_of_range("next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!this->hasCurrent()){
        throw std::out_of_range("prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string result;
    inOrderString(result, root);
    return result;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string result;
    preOrderString(result, root);
    return result;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    //order of pairs doesnt matter so just 
    // inorder traverse them and compare result
    std::string thisstring = this->to_string();
    std::string thatstring = D.to_string();

    // Compare the string representations of the dictionaries
    return thisstring == thatstring;
}

// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    std::string string = D.to_string();
    stream << string;
    return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    this->clear();
    this->preOrderCopy(D.root, D.nil);
    return *this;
}