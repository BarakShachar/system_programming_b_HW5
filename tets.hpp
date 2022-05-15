# pragma once
#include <iostream>

namespace ariel {

template <typename T>
class BinaryTree{

/* node struct : */
struct Node{

    T data; // the data of the node
    Node *left; // left son of this->node
    Node *right; // right son of this->node (son is a node)
    Node *parent; // father of this->node (father is a node)

    /* constuctor of the node : Receiving a data , at first its(the node) has just a data , his parent 
       right son , left son is a nullptr (going forward we insert) */
    Node(T val) : data(val), parent(nullptr), right(nullptr), left(nullptr) {}

};   
    /* the root of the tree */
    Node *root;

    /* clean to destructor : clean the tree by remove left,right node with calls to fuction clean
       in ant iteriton to clean all the nodes of the tree */
    void clean(Node* node){
            if(node != nullptr){
                clean(node->right);
                clean(node->left);
                delete node;
            }
        }

    /* search of old in the tree , in any iteration we going through in the tree , if data of current 
       node == old we found old , else we calls the function with right or left node of current node  */    
    Node* getNode(const T& old, Node* newNode){

            if (newNode == nullptr){
                return nullptr;
            }
            if (newNode->data == old){
                return newNode;
            }
            Node *next = getNode(old,newNode->right);
            if (next == nullptr){
                next =  getNode(old,newNode->left);
            }
            return next;
    }

    /* create a new node , we use it in the deep copy ..*/
    void create_node(Node* current, Node* node){
        
           if (node->left != nullptr)
            {
                current->left = new Node{node->left->data};
                current->left->parent = current;
                create_node(current->left, node->left);
            }

            if (node->right != nullptr)
            {
                current->right = new Node{node->right->data};
                current->right->parent = current;
                create_node(current->right, node->right);
            }
            
        }
    public:
    
       BinaryTree(): root(nullptr){}

       //deep copy
       BinaryTree(const BinaryTree &t){
            if(t.root != nullptr){
              root = new Node(t.root->data);
              create_node(root, t.root);
             }
       }

        //shallow copy
        BinaryTree(BinaryTree && other)noexcept{
               root = other.root;
               other.root = nullptr;
                if(root->parent != nullptr){
                    root->parent = other.root->parent;
                    other.root->parent = nullptr;
                }
        }


        //destructor
       ~BinaryTree(){
             clean(root);
        }

    /* Receives one input and puts it at the root of the tree.
     If there is already something in the root, it is replaced. */    
    BinaryTree &add_root(T r){
            /* if this-> root == nullptr : create a new node and puts it at the root*/
            if(this->root == nullptr){
                this->root = new Node{r};
                return *this;
            }
            
            /* else if there is already something in the root, it is replaced */
            this->root->data = r;
            return *this;
    }

    /* Receives two inputs: The first input indicates something that already exists in the tree.
       The second input indicates something new to be added as his left child 
       (if he already has a left child - his content should be replaced). */
    BinaryTree &add_left(T oldVal,T leftRoot){

        Node *temp = getNode(oldVal,root);
        /* if temp != nullptr there is already something in the leftSon(nullptr), it is replaced */
            if (temp != nullptr){
                if(temp->left != nullptr){
                temp->left->data = leftRoot;
                }else{     /* else if temp == nullptr create a new node and puts it at the leftSon*/
                   Node* t = new Node{leftRoot};
                   temp->left = t;
                   t->parent = temp;
            }
                return *this;
            }
           
        throw std::invalid_argument{"cant found the root of the tree"};
    }

     /* Receives two inputs: The first input indicates something that already exists in the tree.
       The second input indicates something new to be added as his right child 
       (if he already has a right child - his content should be replaced). */
    BinaryTree &add_right(T oldVal,T rightRoot){

            Node *temp = getNode(oldVal,root);
            /* if temp != nullptr there is already something in the rightSon(nullptr), it is replaced */
            if (temp != nullptr){
                if(temp->right != nullptr){
                temp->right->data = rightRoot;
            }else{     /* else if temp == nullptr create a new node and puts it at the rightSon*/
                Node* t = new Node{rightRoot};
                temp->right = t;
                t->parent = temp;
            }
                return *this;
            }
           
        throw std::invalid_argument{"cant found the node of the tree"};
    }
    
    friend std::ostream &operator<<(std::ostream& os , const BinaryTree<T> &b){
          return os;
    }

    
    //pre order iterator parent -> left son -> right son
class pre_iterator{

        Node *curNode; // current node

        public:
        //constructor
         pre_iterator(Node* ptr = nullptr)
                : curNode(ptr) {}

        // pre_iterator(Node *n){
        //     curNode = n;
        // }
        
        //return data of currently node
        T &operator*() const{

            return curNode->data;
        }

        Node* get_node(){
            return curNode;
        }

        // return true if currently node != it node -- else return false
        bool operator!=(const pre_iterator &it) {
           
            return curNode != it.curNode;
        }

        // to through on the tree in preOrder way :
        pre_iterator& operator++() {

                /*if there are a left son then curNode = curNode.left 
                (becouse preOrder way :parent - > left -> right) and in the end return this*/
                if(curNode->left != nullptr){        
                    curNode = curNode->left;
                    return *this;
                }

                /*if there is no left son to curr node then we have to advance to right son
                  becouse in preOrder way we go left(null) -> "right" ---> return this */
                if(curNode->right != nullptr){       
                    curNode = curNode->right;
                    return *this;
                }

                /*if we advanced to left and right (left == nullptr && right == nullptr)
                  then we have to go to onther side : we have to go up to fathers and
                  check if the left son of curr father == curr node that we have alredy checked
                  && the there are a right son to the curr father then we have to go to the right son
                  and to continue to advance in preOrder way (parent -> left -> right) */
                if(curNode->parent != nullptr){
                    Node* temp = curNode->parent;
                    Node* son = curNode;
                    while(temp->parent != nullptr){
                        if(temp->left == son && temp->right != nullptr){
                            curNode = temp->right;
                            return *this;
                        }
                        son = temp;
                        temp = temp->parent;
                    }
                    if(temp->left == son && temp->right != nullptr){
                        curNode = temp->right;
                        return *this;
                    }
                }

                curNode = nullptr;
                return *this;
            }

            //advance our object and return it befor ..
            pre_iterator operator++(int) {
                pre_iterator tmp = *this;//temp in order to save the curr object(the object befor we advanced it)
                ++*this;
                return tmp;
            }

        T *operator->() const{
                return &(this->curNode->data);
            }

        //return true if currently node == it node -- else return false
        bool operator==(const pre_iterator &it) const{
    
            return this->curNode == it.curNode;
        }
    };

    pre_iterator begin_preorder(){
        return (pre_iterator(root));
    }

    pre_iterator end_preorder(){
        return pre_iterator();
    }

    // inorder : leftSon -> parent -> rightSon
    class in_iterator{

        Node *curNode;

        public:
        //constructor
        in_iterator(Node* ptr = nullptr)
                : curNode(ptr) {}

        // in_iterator(Node* n){
        //     curNode = n;
        // }
        
        T &operator*() const{

            return this->curNode->data;
        }

        Node* get_node(){
            return curNode;
        }

        bool operator!=(const in_iterator &it) {
           
            return curNode != it.curNode;
        }

        in_iterator &operator++(){

            if(curNode->right != nullptr){
                    Node* temp = curNode->right;
                    while(temp->left != nullptr){
                        temp = temp->left;
                    }
                    curNode = temp;
                    return *this;
                }
                if(curNode->parent != nullptr){
                    Node* temp = curNode->parent;
                    Node* son = curNode;
                    while(temp->right == son && temp->parent != nullptr){
                        son = temp;
                        temp = temp->parent;
                    }
                    if(temp->left == son){
                        curNode = temp;
                        return *this;
                    }
                }
                curNode = nullptr;
                return *this;
        }

        in_iterator operator++(int) {
                in_iterator tmp= *this;
                ++*this;
                return tmp;
            }

        T *operator->() const{
                return &(this->curNode->data);
            }

        bool operator==(const in_iterator &it) const{
            
            return curNode == it.curNode;
        }

    };

    in_iterator begin_inorder(){
        if(root == nullptr){
                return in_iterator{nullptr};
            }
            Node* temp = root;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return in_iterator{temp};
    }

    in_iterator end_inorder(){
        return in_iterator();
    }

    // postOrder:  leftSOn -> rightSon -> parent
    class post_iterator{

        Node *curNode;

        public:
        //constructor
        post_iterator(Node* ptr = nullptr)
                : curNode(ptr) {}
        
        T &operator*() const{

            return this->curNode->data;
        }

        bool operator!=(const post_iterator &it) {
           
            return curNode != it.curNode;
        }

        Node* get_node(){
            return curNode;
        }

        post_iterator &operator++(){

            if(curNode->parent != nullptr){
                    Node* temp = curNode->parent;
                    if(temp->left == curNode){
                        while(temp->right != nullptr){
                            temp = temp->right;
                            while(temp->left != nullptr){
                                temp = temp->left;
                            }
                        }
                        curNode = temp;
                        return *this;
                    }
                    curNode = temp;
                    return *this;

                }
                curNode = nullptr;
                return *this;
        }

        post_iterator operator++(int) {
                post_iterator tmp= *this;
                ++*this;
                return tmp;
            }

        T *operator->() const{
                return &(this->curNode->data);
            }

        bool operator==(const post_iterator &it) const{
            
            return curNode == it.curNode;
        }

    };

         post_iterator begin_postorder(){
           if(root == nullptr){
                return post_iterator{nullptr};    
            }
            Node* temp = root;
            while(true){
                if(temp->left != nullptr){
                    temp = temp->left;
                }
                else if(temp->right != nullptr){
                    temp = temp->right;
                }
                else{
                    return post_iterator{temp};
                }
            }
            return post_iterator{nullptr};
         }

        post_iterator end_postorder(){
           return post_iterator();
         }

        in_iterator begin(){
            if(root == nullptr){
                return in_iterator{nullptr};
            }
            Node* temp = root;
            while(temp->left != nullptr){
                temp = temp->left;
            }
            return in_iterator{temp};
        }

        in_iterator end(){
            return in_iterator{nullptr};
        }

        
        BinaryTree& operator=(const BinaryTree& other){

            if(this != &other){
                clean(root);
                //*this = BinaryTree(other);
                root = new Node{other.root->data};
                create_node(root, other.root);
            }

            return *this;
        }

        BinaryTree& operator=(BinaryTree && other) noexcept{

            if(this != &other){
            if(root != nullptr){
                clean(root);
            }
            root = other.root;
            other.root = nullptr;
             }
            return *this;
        }

};

}