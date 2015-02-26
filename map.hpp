#include <initializer_list>
#include <utility>
#include <string>
#include <iostream>
#include <stdexcept>

namespace cs540 {
	template <typename Key, typename Value> class Map {
		public:
			class Node {
				public:
					std::pair<const Key, Value> data;
					Node *parent;
					Node *left;
					Node *right;
				Node(std::pair<const Key, Value> pair):data(pair){
					parent = NULL;
					left = NULL;
					right = NULL;
				}
				~Node(){
					if(left != NULL){
						delete left;
					}
					if(right != NULL){
						delete right;
					}
				//	delete this;
				}
			};
			class Iterator;
			class ConstIterator;
			class ReverseIterator;
			//Iterator DONE
			class Iterator {
				public:
					Node* ptr;

					Iterator() = default;

					Iterator(std::pair<const Key, Value> pair) {
						ptr = new Node(pair);
					}
					
					//Postfix
					Iterator& operator++() {
						Node *last = this->ptr;
						if ((this->ptr)->right != nullptr) {
							(this->ptr) = (this->ptr)->right;
							while((this->ptr)->left != nullptr) {
								(this->ptr) = (this->ptr)->left;
							}
						} else {
							if ((this->ptr)->parent->left == (this->ptr)) {
								(this->ptr) = (this->ptr)->parent;
							} else {
								while((this->ptr) != (this->ptr)->parent->left) {
									(this->ptr) = (this->ptr)->parent;
									if(this->ptr->parent == NULL) {
										Iterator *it = new Iterator();
										it->ptr = last + 1;
										this->ptr = last+1;
										return *it;
									}
								}	
							}
						}
						return *this;
					}

					//Prefix
					Iterator operator++(int){
						Node *current = this->ptr;
						Node *last = this->ptr;
						if (this->ptr->right != nullptr) {
							this->ptr = this->ptr->right;
							while(this->ptr->left!=nullptr) {
								this->ptr = this->ptr->left;
							}
						} else {
							if (this->ptr->parent->left == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->left) {
									this->ptr = this->ptr->parent;
									if(this->ptr->parent == NULL) {
										Iterator *it = new Iterator();
										it->ptr = last + 1;
										this->ptr = last+1;
										return *it;
									}
								}	
								last = this->ptr;
							}
						}
						Iterator * iter = new Iterator();
						iter->ptr = current;
						return *iter;
					}

					//Postfix
					Iterator& operator--() {
						Node *last = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right != nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseIterator).!\n");
										Iterator *it = new Iterator();
										it->ptr = last - 1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						return *this;
					}

					//Prefix
					Iterator operator--(int) {
						Node *last = this->ptr;
						Node *current = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right != nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseIterator).!\n");
										Iterator *it = new Iterator();
										it->ptr = last - 1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						Iterator * iter = new Iterator();
						iter->ptr = current;
						return *iter;
					}
					
					std::pair<const Key, Value>& operator*() const{
						return ptr->data;
					}
					bool operator==(const Iterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}
					bool operator!=(const Iterator& b){
						if(*(*this) != (*b)){
							return true;
						}else{
							return false;
						}
					}
					bool operator==(const ConstIterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}
					bool operator!=(const ConstIterator& b){
						if(*(*this) != (*b)){
							return true;
						}else{
							return false;
						}
					}
			};
		//ConstIterator DONE
			class ConstIterator {
				public:
					Node* ptr;

					ConstIterator() = default;

					ConstIterator(std::pair<const Key, Value> pair) {
						ptr = new Node(pair);
					}
					
					ConstIterator(const Iterator& i){
						ptr = i.ptr;
					}				
	
					ConstIterator& operator++() {
						Node *last = this->ptr;
						if ((this->ptr)->right != nullptr) {
							(this->ptr) = (this->ptr)->right;
							while((this->ptr)->left != nullptr) {
								(this->ptr) = (this->ptr)->left;
							}
						} else {
							if ((this->ptr)->parent->left == (this->ptr)) {
								(this->ptr) = (this->ptr)->parent;
							} else {
								while((this->ptr) != (this->ptr)->parent->left) {
									(this->ptr) = (this->ptr)->parent;
									if(this->ptr->parent == NULL) {
										ConstIterator *it = new ConstIterator();
										it->ptr = last+1;
										this->ptr = last+1;
										return *it;
//										throw std::out_of_range("You've gone too far!\n");
									}
								}	
							}
						}
						return *this;
					}

					ConstIterator operator++(int){
						Node *current = this->ptr;
						Node *last = this->ptr;
						if (this->ptr->right != nullptr) {
							this->ptr = this->ptr->right;
							while(this->ptr->left!=nullptr) {
								this->ptr = this->ptr->left;
							}
						} else {
							if (this->ptr->parent->left == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->left) {
									this->ptr = this->ptr->parent;
									if(this->ptr->parent == NULL) {
										ConstIterator *it = new ConstIterator();
										it->ptr = last + 1;
										this->ptr = last+1;
										return *it;
									}
								}	
								last = this->ptr;
							}
						}
						ConstIterator * iter = new ConstIterator();
						iter->ptr = current;
						return *iter;
					}

					ConstIterator& operator--() {
						Node *last = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right != nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseConstIterator).!\n");
										ConstIterator *it = new ConstIterator();
										it->ptr = last - 1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						return *this;
					}

					ConstIterator operator--(int) {
						Node *last = this->ptr;
						Node *current = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right != nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseConstIterator).!\n");
										ConstIterator *it = new ConstIterator();
										it->ptr = last - 1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						ConstIterator * iter = new ConstIterator();
						iter->ptr = current;
						return *iter;
					}
					
					std::pair<const Key, Value>& operator*() const{
						return ptr->data;
					}

					bool operator==(const ConstIterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}

					bool operator!=(const ConstIterator& b){
						if(*(*this) != (*b)){
							return true;
						}else{
							return false;
						}
					}

					bool operator==(const Iterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}
					bool operator!=(const Iterator& b){
						if(*(*this) != (*b)){
							return true;
						}else{
							return false;
						}
					}
			};
		//Reverse Iterator DONE
			class ReverseIterator {
				public:
					Node* ptr;

					ReverseIterator() = default;

					ReverseIterator(std::pair<const Key, Value> pair) {
						ptr = new Node(pair);
					}
					
					ReverseIterator& operator--() {
						Node *last = this->ptr;
						if ((this->ptr)->right != nullptr) {
							(this->ptr) = (this->ptr)->right;
							while((this->ptr)->left!=nullptr) {
								(this->ptr) = (this->ptr)->left;
							}
						} else {
							if ((this->ptr)->parent->left == (this->ptr)) {
								(this->ptr) = (this->ptr)->parent;
							} else {
								while((this->ptr) != (this->ptr)->parent->left) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseReverseIterator).!\n");
										ReverseIterator *it = new ReverseIterator();
										it->ptr = last+1;
										this->ptr = last+1;
										return *it;
									}
									(this->ptr) = (this->ptr)->parent;
								}	
							}
						}
						return *this;
					}
					ReverseIterator operator--(int) {
						Node *last = this->ptr;
						Node *current = this->ptr;
						if (this->ptr->right != nullptr) {
							this->ptr = this->ptr->right;
							while(this->ptr->left!=nullptr) {
								this->ptr = this->ptr->left;
							}
						} else {
							if (this->ptr->parent->left == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->left) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseReverseIterator).!\n");
										ReverseIterator *it = new ReverseIterator();
										it->ptr = last+1;
										this->ptr = last+1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						ReverseIterator * iter = new ReverseIterator();
						iter->ptr = current;
						return *iter;
					}

					ReverseIterator& operator++() {					
						Node *last = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right!=nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseReverseIterator).!\n");
										ReverseIterator *it = new ReverseIterator();
										it->ptr = last-1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						return *this;
					}

					ReverseIterator operator++(int){
						Node *last = this->ptr;
						Node *current = this->ptr;
						if (this->ptr->left != nullptr) {
							this->ptr = this->ptr->left;
							while(this->ptr->right != nullptr) {
								this->ptr = this->ptr->right;
							}
						} else {
							if (this->ptr->parent->right == this->ptr) {
								this->ptr = this->ptr->parent;
							} else {
								while(this->ptr != this->ptr->parent->right) {
									if(this->ptr->parent == NULL) {
										throw std::out_of_range("You've gone below begin(). (Try using a ReverseReverseIterator).!\n");
										ReverseIterator *it = new ReverseIterator();
										it->ptr = last-1;
										this->ptr = last-1;
										return *it;
									}
									this->ptr = this->ptr->parent;
								}	
							}
						}
						ReverseIterator * iter = new ReverseIterator();
						iter->ptr = current;
						return *iter;
					}
					
					std::pair<const Key, Value>& operator*() const{
						return ptr->data;
					}
					bool operator==(const ReverseIterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}
					bool operator!=(const ReverseIterator& b){
						if(*(*this) == (*b)){
							return true;
						}else{
							return false;
						}
					}
			};
		public:
			Node* root;
			Node* finish;
			std::size_t nodes;
		public:
		//constructors DONE
			Map() {
				root = nullptr;
				finish = nullptr;
				nodes = 0;
			}
			Map(const Map& m){
				if(m.root != NULL){
					nodes = m.size();
					Node * newNode = new Node(m.root->data);

					root = newNode;

					Node * temp = root;
					Node * copy = m.root;
					while(temp != NULL){
						while((temp->left==NULL) && (copy->left != NULL)){
							//we need a new node
							Node * newNode = new Node(copy->left->data);
							//point to the new node
							temp->left = newNode;
							//set the new nodes parent
							temp->left->parent = temp;
							//move to the next one
							temp = temp->left;
							copy = copy->left;
						}
						if(temp->right==NULL && copy->right != NULL){
							//we need a new node
							Node * newNode = new Node(copy->right->data);
							//point to the new node
							temp->right = newNode;
							//set the new nodes parent
							temp->right->parent = temp;
							//move to the next one
							temp = temp->right;
							copy = copy->right;
						}else if(((temp->left == NULL && copy->left==NULL)||(temp->left != NULL && copy->left!=NULL)) && ((temp->right == NULL && copy->right==NULL)||(temp->right != NULL && copy->right!=NULL))){
							temp=temp->parent;
							copy=copy->parent;
						}
					}
				}else{
					root = NULL;				
				}
			}
			Map& operator=(const Map& m){
				if(m.root != NULL){
					nodes = m.size();
					Node * newNode = new Node(m.root->data);
					root = newNode;
					Node * temp = root;
					Node * copy = m.root;
					while(temp != NULL){
						while((temp->left==NULL) && (copy->left != NULL)){
							//we need a new node
							Node * newNode = new Node(copy->left->data);
							//point to the new node
							temp->left = newNode;
							//set the new nodes parent
							temp->left->parent = temp;
							//move to the next one
							temp = temp->left;
							copy = copy->left;
						}
						if(temp->right==NULL && copy->right != NULL){
							//we need a new node
							Node * newNode = new Node(copy->right->data);
							//point to the new node
							temp->right = newNode;
							//set the new nodes parent
							temp->right->parent = temp;
							//move to the next one
							temp = temp->right;
							copy = copy->right;
						}else if(((temp->left == NULL && copy->left==NULL)||(temp->left != NULL && copy->left!=NULL)) && ((temp->right == NULL && copy->right==NULL)||(temp->right != NULL && copy->right!=NULL))){
							temp=temp->parent;
							copy=copy->parent;
						}
					}
				}else{
					nodes = m.size();
					root = NULL;				
				}
				return *this;				
			}

			Map(Map&& m) {
				root = m.root;
				finish = m.finish;
			}

			Map& operator=(Map&& m){
				root = m.root;
				finish = m.finish;
				return *this;
			}

			Map(std::initializer_list<std::pair<const Key, Value>> pair) {
				nodes = 0;
				root = nullptr;
				finish = nullptr;
				for (std::pair<const Key, Value> it: pair){
					//printf("pair info: %x\n",it.second);
					this->insert(it);
				}
			}

			~Map(){
				delete root;
			}
		//Modifiers DONE
			Iterator insert(const std::pair<const Key, Value> &data) {
				Node * newNode = new Node(data);
				Node * temp = root;
				if(temp == NULL){
					root = newNode;
					nodes +=1;
					Iterator * iter = new Iterator();
					iter->ptr = newNode;
					return *iter;
				}else{
					while(temp != NULL){
						if(temp->data.first < data.first){
							if(temp->right == NULL){
								nodes +=1;
								temp->right = newNode;
								newNode->parent = temp;	
								Iterator * iter = new Iterator();
								iter->ptr = newNode;
								return *iter;				
							}else{					
								temp=temp->right;
							}	
						}else if(data.first < temp->data.first){
							if(temp->left == NULL){
								temp->left = newNode;
								nodes +=1;
								newNode->parent = temp;	
								Iterator * iter = new Iterator();
								iter->ptr = newNode;
								return *iter;				
							}else{					
								temp=temp->left;
							}	
						}else{
							Iterator * iter = new Iterator();
							iter->ptr = temp;
							return *iter;
						}
					}
					Iterator * iter = new Iterator();
					iter->ptr = newNode;
					return *iter;
				}
			}
			
			Iterator insert(std::pair<const Key, Value>&& data){
				Node * newNode = new Node(data);
				Node * temp = root;
				// If the root is null, set the root to newNode
				if(temp == NULL){
					root = newNode;
					nodes +=1;
					Iterator * iter = new Iterator();
					iter->ptr = newNode;
					return *iter;
				}else{
					//
					while(temp != NULL){
						if(temp->data.first < data.first){
							if(temp->right == NULL){
								nodes+=1;
								temp->right = newNode;
								newNode->parent = temp;	
								Iterator * iter = new Iterator();
								iter->ptr = newNode;
								return *iter;				
							}else{					
								temp=temp->right;
							}	
						}else if(data.first < temp->data.first){
							if(temp->left == NULL){
								nodes+=1;
								temp->left = newNode;
								newNode->parent = temp;	
								Iterator * iter = new Iterator();
								iter->ptr = newNode;
								return *iter;				
							}else{					
								temp=temp->left;
							}	
						}else{
							Iterator * iter = new Iterator();
							iter->ptr = temp;
							return *iter;
						}
					}
				}
				Iterator * iter = new Iterator();
				iter->ptr = newNode;
				return *iter;
			}

			void erase(Iterator i) {
				Node * current = i.ptr;
				if(current != NULL){
					if(root == current){
						root = NULL;
					}else{
						nodes-=1;
						Node * daddy = current->parent;
						if(daddy->left == current){
							daddy->left = NULL;
						}else if(daddy->right == current){
							daddy->right = NULL;
						}
						current->parent = NULL;							
					}
					Node * temp = current; 
					while(temp != NULL){
						while((temp->left != NULL) && (find(temp->left->data.first).ptr == end().ptr)) {
							nodes--;
							insert(temp->left->data);
							temp = temp->left;						
						}
						if((temp->right != NULL) && (find(temp->right->data.first).ptr == end().ptr)) {
							nodes--;
							insert(temp->right->data);
							temp = temp->right;
						} else if (temp->left == NULL && temp->right == NULL) {
							if (temp->parent != NULL) {
								temp = temp->parent;
							} else {
								temp = NULL;
							}
						} else if (temp->left == NULL && find(temp->right->data.first).ptr != end().ptr) {
							if (temp->parent != NULL) {
								temp = temp->parent;
							} else {
								temp = NULL;
							}
						} else if (find(temp->left->data.first).ptr != end().ptr && temp->right == NULL) {
							if (temp->parent != NULL) {
								temp = temp->parent;
							} else {
								temp = NULL;
							}
						} else if (find(temp->left->data.first).ptr != end().ptr && find(temp->right->data.first).ptr != end().ptr) {
							if (temp->parent != NULL) {
								temp = temp->parent;
							} else {
								temp = NULL;
							}
						}
					}
					delete current;
				}
			}
			void remove(const Key& key){
				Iterator iter = find(key);
				if((iter.ptr) == (end().ptr)){
					throw std::out_of_range("Error: Key is out of range");
				}else{
					nodes-=1;
					Node * current = iter.ptr;
					if(current != NULL){
						if(root == iter.ptr){
							root = NULL;
						}else{
							Node * daddy = current->parent;
							if(daddy->left == current){
								daddy->left = NULL;
							}else if(daddy->right == current){
								daddy->right = NULL;
							}
							current->parent = NULL;							
						}
						Node * temp = current;
						while(temp != NULL){
							while((temp->left != NULL) && (find(temp->left->data.first).ptr != end().ptr)){
								insert(temp->left->data);
								temp = temp->left;						
							}
							if((temp->right != NULL) && (find(temp->right->data.first).ptr != end().ptr)){
								insert(temp->right->data);
								temp = temp->right;
							}else if(((temp->left != NULL) || (find(temp->left->data.first).ptr != end().ptr)) && ((temp->right != NULL) || (find(temp->right->data.first).ptr != end().ptr))){
								temp=temp->parent;
							}
						}
						delete current;
					}
				}
			}

			void clear(){
				delete root;
				root = NULL;
			}
		//lookup
			// Average log(n)
			Iterator find(const Key& k) {
				Node * temp = root;		
				Iterator * newIt = new Iterator();
				while (temp != NULL) {
					if (temp->data.first == k) {
						newIt->ptr = temp;
						return *newIt;
					}
					if(k < temp->data.first){
						temp = temp->left;
					} else if(temp->data.first < k){
						temp = temp->right;
					}
				}
				return end();
			}

			Value& at(const Key& k) {
			    Iterator m = find(k);
				if(m.ptr == end().ptr){
					throw std::out_of_range("Error: Key is out of range"); 
				}
				return m.ptr->data.second;
			}

			ConstIterator find(const Key& k) const{
				Node * temp = root;		
				ConstIterator * newIt = new ConstIterator();
				while (temp != NULL) {
					if (temp->data.first == k) {
						newIt->ptr = temp;
						return *newIt;
					}
					if(k < temp->data.first){
						temp = temp->left;
					} else if(temp->data.first < k){
						temp = temp->right;
					}
				}
				return end();
			}

			const Value& at(const Key& k) const{
			    ConstIterator m = find(k);
				if(m.ptr == end().ptr){
					throw std::out_of_range("Error: Key is out of range"); 
				}
				return m.ptr->data.second;
			}

			Value& operator[](const Key& k) { 
				Node *temp = root;
				std::pair<const Key, Value> pair {k, {}};
				if(nodes == 0){
					root = new Node(pair);
					nodes++;
					return root->data.second;
				}
				// Search for key in the map
				while(temp != nullptr){
					// If found, return it's value
					if(temp->data.first == k){
						return (temp->data.second);
					}
					// Else keep iterating
					else{
						if(temp->data.first < k) {
							temp = temp->right;
						}
						else temp = temp->left;
					}
				}
				//Insert elment and return value using iterator
				Iterator it=insert(pair);
				return it.ptr->data.second;
			}
		//size DONE
			std::size_t size() const{
				return nodes;
			}

			bool empty() const{
				if(nodes == 0){
					return true;
				}else{
					return false;
				}
			}
		//comparison 
    		bool operator==(const Map& m) const {
				if(size() == m.size()){
					ConstIterator iter = m.begin();
					Node * found = iter.ptr;
					while(iter.ptr != m.end().ptr) {
						found = find(iter.ptr->data.first).ptr;
						if (found == end().ptr) {
							return false;
						}
						iter++;
					}
					return true;
				}
				return false;
			}
			
			bool operator!=(const Map& m) const {
				if((*this) == m){
					return false;
				}else{
					return true;

				}
			
			}
		//iterators
			Iterator begin(){
				Node * temp = root;
				while(temp->left != NULL){
					temp = temp->left;
				}
				Iterator * iter = new Iterator();
				iter->ptr = temp;
				return *iter;
			}
			Iterator end(){
				Node * temp = root;
				while(temp->right != NULL){
					temp = temp->right;
				}
				Iterator * iter = new Iterator();
				iter->ptr = temp+1;
				return *iter;
			}
			ConstIterator begin() const{
				Node * temp = root;
				while(temp->left != NULL){
					temp = temp->left;
				}
				ConstIterator * iter = new ConstIterator();
				iter->ptr = temp;
				return *iter;
			}
			ConstIterator end() const{
				Node * temp = root;
				while(temp->right != NULL){
					temp = temp->right;
				}
				ConstIterator * iter = new ConstIterator();
				iter->ptr = temp+1;
				return *iter;
			}
			ReverseIterator rbegin(){
				Node * temp = root;
				while(temp->right != NULL){
					temp = temp->right;
				}
				ReverseIterator * iter = new ReverseIterator();
				iter->ptr = temp;
				return *iter;
			}
			ReverseIterator rend(){
				Node * temp = root;
				while(temp->left != NULL){
					temp = temp->left;
				}
				ReverseIterator * iter = new ReverseIterator();
				iter->ptr = temp-1;
				return *iter;
			}
	};
}
