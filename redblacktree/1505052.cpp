#include <iostream>
#include <stack>

using namespace std;

static int RED = 0;
static int BLACK = 1;

class RedBlackTreeNode
{
public:
	//RedBlackTreeNode() :key(T()), parent(NULL), left(NULL), right(NULL), color(BLACK) {}
	RedBlackTreeNode()
	{
	    key = 0;
	    parent = NULL;
	    left = NULL;
	    right = NULL;
	    color = BLACK;
	}
	int key;
	RedBlackTreeNode* parent;
	RedBlackTreeNode* left;
	RedBlackTreeNode* right;
	int color;
};

class RedBlackTree
{
public:
	RedBlackTree();
	int search_element(int& k);
	int get_minmum(int& retmin);
	int get_maxmum(int& retmax);
	int get_successor(int& k, int& ret);
	int get_predecessor(int& k, int& ret);
	int insert_key(int& k);
	int delete_key(int& k);
	void inorder_tree_walk();
	RedBlackTreeNode* get_root();
	~RedBlackTree();
private:
	RedBlackTreeNode* root;
	static  RedBlackTreeNode *NIL;
	RedBlackTreeNode* get_parent(RedBlackTreeNode* pnode) ;
	RedBlackTreeNode* get_left(RedBlackTreeNode* pnode) ;
	RedBlackTreeNode* get_right(RedBlackTreeNode* pnode) ;
	int get_key(RedBlackTreeNode* pnode) ;
	int get_color(RedBlackTreeNode* pnode) ;
	void set_color(RedBlackTreeNode* pnode, int color);
	void left_rotate(RedBlackTreeNode *pnode);
	void right_rotate(RedBlackTreeNode *pnode);
	void rb_insert_fixup(RedBlackTreeNode *pnode);
	void rb_delete_fixup(RedBlackTreeNode *pnode);
	RedBlackTreeNode* get_maxmum(RedBlackTreeNode *root) ;
	RedBlackTreeNode* get_minmum(RedBlackTreeNode *root) ;
	RedBlackTreeNode* get_successor(RedBlackTreeNode *pnode) ;
	RedBlackTreeNode* get_predecessor(RedBlackTreeNode *pnode) ;
	RedBlackTreeNode* search_tree_node(int& k);
	void make_empty(RedBlackTreeNode* root);
};

RedBlackTreeNode* RedBlackTree::NIL = new RedBlackTreeNode();

RedBlackTree::RedBlackTree()
{
	root = NULL;
}

int RedBlackTree::search_element(int& k)
{
	return (NIL != search_tree_node(k));
}

int RedBlackTree::get_minmum(int& retmin)
{
	if (root)
	{
		retmin = get_minmum(root)->key;
		return 0;
	}
	return -1;
}

int RedBlackTree::get_maxmum(int& retmax)
{
	if (root)
	{
		retmax = get_maxmum(root)->key;
		return 0;
	}
	return -1;
}

int RedBlackTree::get_successor(int& k, int& ret)
{
	RedBlackTreeNode* pnode = search_tree_node(k);

	if (pnode != NIL)
	{
		pnode = get_successor(pnode);
		if (pnode != NIL)
		{
			ret = pnode->key;
			return 0;
		}
		return -1;
	}
	return -1;
}

int RedBlackTree::get_predecessor(int& k, int& ret)
{
	RedBlackTreeNode* pnode = search_tree_node(k);
	if (pnode != NIL)
	{
		pnode = get_predecessor(pnode);
		if (pnode != NIL)
		{
			ret = pnode->key;
			return 0;
		}
		return -1;
	}
	return -1;
}

int RedBlackTree::insert_key(int& k)
{
	RedBlackTreeNode *newnode = new RedBlackTreeNode();
	newnode->key = k;
	newnode->color = RED;
	newnode->left = NIL;
	newnode->right = NIL;
	newnode->parent = NIL;

	if (NULL == root)
		root = newnode;
	else
	{
		RedBlackTreeNode* pnode = root;
		RedBlackTreeNode* qnode = root;
		while (pnode != NIL)
		{
			qnode = pnode;
			if (pnode->key > newnode->key)
				pnode = pnode->left;
			else
				pnode = pnode->right;
		}
		newnode->parent = qnode;
		if (qnode->key > newnode->key)
			qnode->left = newnode;
		else
			qnode->right = newnode;
	}
	rb_insert_fixup(newnode);
	return 0;
}

int RedBlackTree::delete_key(int& k)
{
	RedBlackTreeNode* pnode = search_tree_node(k);
	if (NIL != pnode)
	{
		RedBlackTreeNode* qnode, *tnode;
		if (get_left(pnode) == NIL || get_right(pnode) == NIL)
			qnode = pnode;
		else
			qnode = get_successor(pnode);

		if (get_left(qnode) != NIL)
			tnode = get_left(qnode);
		else
			tnode = get_right(qnode);

		tnode->parent = get_parent(qnode);

		if (get_parent(qnode) == NIL)
			root = tnode;
		else if (qnode == get_left(get_parent(qnode)))
			qnode->parent->left = tnode;
		else
			qnode->parent->right = tnode;

		if (qnode != pnode)
			pnode->key = get_key(qnode);

		if (get_color(qnode) == BLACK)
			rb_delete_fixup(tnode);

		delete qnode;
		return 0;
	}
	return -1;
}

RedBlackTree::~RedBlackTree()
{
	make_empty(root);
}

RedBlackTreeNode* RedBlackTree::get_root()
{
	return root;
}

RedBlackTreeNode* RedBlackTree::get_parent(RedBlackTreeNode* pnode)
{
	return pnode->parent;
}

RedBlackTreeNode* RedBlackTree::get_left(RedBlackTreeNode* pnode)
{
	return pnode->left;
}

RedBlackTreeNode* RedBlackTree::get_right(RedBlackTreeNode* pnode)
{
	return pnode->right;
}

int RedBlackTree::get_key(RedBlackTreeNode* pnode)
{
	return pnode->key;
}

int RedBlackTree::get_color(RedBlackTreeNode* pnode)
{
	return pnode->color;
}


void RedBlackTree::set_color(RedBlackTreeNode* pnode, int color)
{
	pnode->color = color;
}

void RedBlackTree::left_rotate(RedBlackTreeNode *pnode)
{
	RedBlackTreeNode* rightnode = pnode->right;
	pnode->right = rightnode->left;
	if (rightnode->left != NIL)
		rightnode->left->parent = pnode;
	rightnode->parent = pnode->parent;
	if (pnode->parent == NIL)
		root = rightnode;
	else if (pnode == pnode->parent->left)
		pnode->parent->left = rightnode;
	else
		pnode->parent->right = rightnode;
	rightnode->left = pnode;
	pnode->parent = rightnode;
}

void RedBlackTree::right_rotate(RedBlackTreeNode *pnode)
{
	RedBlackTreeNode* leftnode = pnode->left;
	pnode->left = leftnode->right;
	if (leftnode->right != NIL)
		leftnode->right->parent = pnode;
	leftnode->parent = pnode->parent;
	if (pnode->parent == NIL)
		root = leftnode;
	else if (pnode == pnode->parent->left)
		pnode->parent->left = leftnode;
	else
		pnode->parent->right = leftnode;
	leftnode->right = pnode;
	pnode->parent = leftnode;
}

void RedBlackTree::rb_insert_fixup(RedBlackTreeNode *pnode)
{
	RedBlackTreeNode *qnode, *tnode;
	while (get_color(get_parent(pnode)) == RED)
	{
		qnode = get_parent(get_parent(pnode));
		if (get_parent(pnode) == get_left(qnode))
		{
			tnode = get_right(qnode);
			if (get_color(tnode) == RED)
			{
				set_color(get_parent(pnode), BLACK);
				set_color(tnode, BLACK);
				set_color(qnode, RED);
				pnode = qnode;
			}
			else
			{
				if (pnode == get_right(get_parent(pnode)))
				{
					pnode = get_parent(pnode);
					left_rotate(pnode);
				}
				set_color(get_parent(pnode), BLACK);
				qnode = get_parent(get_parent(pnode));
				set_color(qnode, RED);
				right_rotate(qnode);
			}
		}
		else
		{
			tnode = get_left(qnode);
			if (get_color(tnode) == RED)
			{
				set_color(get_parent(pnode), BLACK);
				set_color(tnode, BLACK);
				set_color(qnode, RED);
				pnode = qnode;
			}
			else
			{
				if (pnode == get_left(get_parent(pnode)))
				{
					pnode = get_parent(pnode);
					right_rotate(pnode);
				}
				set_color(get_parent(pnode), BLACK);
				qnode = get_parent(get_parent(pnode));
				set_color(qnode, RED);
				left_rotate(qnode);
			}
		}
	}
	set_color(root, BLACK);
}

void RedBlackTree::rb_delete_fixup(RedBlackTreeNode *pnode)
{
	while (pnode != root && get_color(pnode) == BLACK)
	{
		RedBlackTreeNode *qnode, *tnode;
		if (pnode == get_left(get_parent(pnode)))
		{
			qnode = get_right(get_parent(pnode));
			if (get_color(qnode) == RED)
			{
				set_color(qnode, BLACK);
				set_color(get_parent(pnode), RED);
				left_rotate(get_parent(pnode));
				qnode = get_right(get_parent(pnode));
			}


			if (get_color(get_left(qnode)) == BLACK && get_color(get_right(qnode)) == BLACK)
			{
				set_color(qnode, RED);
				pnode = get_parent(pnode);
			}
			else
			{
				if (get_color(get_right(qnode)) == BLACK)
				{
					set_color(get_left(qnode), BLACK);
					set_color(qnode, RED);
					right_rotate(qnode);
					qnode = get_right(get_parent(pnode));
				}
				set_color(qnode, get_color(get_parent(pnode)));
				set_color(get_parent(pnode), BLACK);
				set_color(get_right(qnode), BLACK);
				left_rotate(get_parent(pnode));
				pnode = root;
			}
		}
		else
		{
			qnode = get_left(get_parent(pnode));
			if (get_color(qnode) == RED)
			{
				set_color(qnode, BLACK);
				set_color(get_parent(pnode), RED);
				right_rotate(get_parent(pnode));
				qnode = get_left(get_parent(pnode));
			}
			if (get_color(get_right(qnode)) == BLACK && get_color(get_left(qnode)) == BLACK)
			{
				set_color(qnode, RED);
				pnode = get_parent(pnode);
			}
			else
			{
				if (get_color(get_left(qnode)) == BLACK)
				{
					set_color(get_right(qnode), BLACK);
					set_color(qnode, RED);
					left_rotate(qnode);
					qnode = get_left(get_parent(pnode));
				}
				set_color(qnode, get_color(get_parent(pnode)));
				set_color(get_parent(pnode), BLACK);
				set_color(get_left(qnode), BLACK);
				right_rotate(get_parent(pnode));
				pnode = root;
			}
		}
	}
	set_color(pnode, BLACK);
}


RedBlackTreeNode* RedBlackTree::get_maxmum(RedBlackTreeNode *root)
{
	RedBlackTreeNode *pnode = root;
	while (pnode->right != NIL)
		pnode = pnode->right;
	return pnode;
}


RedBlackTreeNode* RedBlackTree::get_minmum(RedBlackTreeNode *root)
{
	RedBlackTreeNode *pnode = root;
	while (pnode->left != NIL)
		pnode = pnode->left;
	return pnode;
}


RedBlackTreeNode* RedBlackTree::get_successor(RedBlackTreeNode *pnode)
{
	if (pnode->right != NIL)
		return get_minmum(pnode->right);
	RedBlackTreeNode* parentnode = get_parent(pnode);
	while (parentnode != NIL && get_right(parentnode) == pnode)
	{
		pnode = parentnode;
		parentnode = get_parent(pnode);
	}
	return parentnode;
}

RedBlackTreeNode* RedBlackTree::get_predecessor(RedBlackTreeNode *pnode)
{
	if (pnode->left != NIL)
		return get_maxmum(pnode->left);
	RedBlackTreeNode* parentnode = get_parent(pnode);
	while (parentnode != NIL && get_left(parentnode) == pnode)
	{
		pnode = parentnode;
		parentnode = get_parent(pnode);
	}
	return parentnode;
}


RedBlackTreeNode* RedBlackTree::search_tree_node(int& k)
{
    RedBlackTreeNode* pnode = NIL;
    if(root!=NULL)
    pnode = root;
	while (pnode != NIL)
	{
		if (pnode->key == k)
			break;
		else if (pnode->key > k)
			pnode = pnode->left;
		else
			pnode = pnode->right;
	}
	return pnode;
}

void RedBlackTree::make_empty(RedBlackTreeNode* root)
{
	if (root)
	{
		RedBlackTreeNode *pleft = root->left;
		RedBlackTreeNode* pright = root->right;
		delete root;
		if (pleft != NIL)
			make_empty(pleft);
		if (pright != NIL)
			make_empty(pright);
	}
}

void RedBlackTree::inorder_tree_walk()
{
	if (NULL != root)
	{
		stack<RedBlackTreeNode* > s;
		RedBlackTreeNode *ptmpnode;
		ptmpnode = root;
		while (NIL != ptmpnode || !s.empty())
		{
			if (NIL != ptmpnode)
			{
				s.push(ptmpnode);
				ptmpnode = ptmpnode->left;
			}
			else
			{
				ptmpnode = s.top();
				s.pop();
				cout << ptmpnode->key << ":";
				if (ptmpnode->color == BLACK)
					cout << "Black" << endl;
				else
					cout << "Red" << endl;
				ptmpnode = ptmpnode->right;
			}
		}
	}
}
int main()
{
	RedBlackTree rbtree;
	int value;
    int input;
    int taken;
	while(1)
    {
        cout<<"1.Insert"<<endl;
        cout<<"2.Search"<<endl;
        cout<<"3.Delete"<<endl;
        cout<<"4.Print"<<endl;
        cout<<"5.Min"<<endl;
        cout<<"6.Max"<<endl;
        cin>>input;
        switch(input)
        {
            case 1:
            cin>>taken;
            rbtree.insert_key(taken);
            break;
            case 2:
            cin>>taken;
            if(rbtree.search_element(taken))
            cout<<"Found"<<endl;
            else
                cout<<"Not Found"<<endl;
            break;
            case 3:
            cin>>taken;
            rbtree.delete_key(taken);
            break;
            case 4:
            rbtree.inorder_tree_walk();
            break;
            case 5:
            if (rbtree.get_maxmum(value) == 0)
            cout << "maxmum is: " << value << endl;
            break;
            case 6:
            if (rbtree.get_minmum(value) == 0)
            cout << "minmum is: " << value << endl;
            break;
            default:
                break;
        }
        cout<<endl;
    }
	return 0;
}
