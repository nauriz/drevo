#include <iostream>
#define EXIT_WHILE 7							/// const for exit from infinite loop

struct leaf
{
	int val;
	leaf *parent;
	leaf *son_l;
	leaf *son_r;
};
void delete_tree(leaf *root);
void create_tree(leaf *root);
int give_val();
int give_mFlag();
int give_cFlag(leaf *nowRoot);
leaf* up_root(leaf *root);
leaf* cr_left_son(leaf *parent);
leaf* cr_right_son(leaf *parent);
void inorder(leaf *root);
void preorder(leaf *root);
void postorder(leaf *root);
void print_tree(leaf* root);


int main ()
{
	short flag = 11;							/// flag for menu
	leaf *root;									/// root of tree

	root = new leaf;
	root->parent = NULL;						/// totaly null root of tree
	root->son_l = NULL;							///
	root->son_r = NULL;							///
	root->val = NULL;							///

	while(1)
	{
		switch (give_mFlag())					/// give flag
		{
		case 1: 
			create_tree(root);					/// create tree
			printf("\n....tree was created");
			break;
		case 2:
			print_tree(root);					/// print tree
			break;
		case 0:
			delete_tree(root);					/// destroy tree 
			printf("\n....tree was destroied"); 
			flag = EXIT_WHILE;					/// and exit from programm
			break;
		}
		if (flag == EXIT_WHILE) break;
	}

	getchar();
	getchar();
}



int give_val()
{
	int val;
		printf ("....value of leaf: ");
		scanf("%d", &val);
	return val;
}



int give_mFlag()
{
	int flag = 11;
		while (flag != 2 && flag != 1 && flag != 0)
		{
			printf ("\n Create tree\t\t[input: 1]");
			printf ("\n Print tree\t\t[input: 2]");
			printf ("\n Destroy and exit\t[input: 0]");
			printf ("\n\tCommand: ");  scanf("%d", &flag);
			printf(" ");
		}
	return flag;
}



int give_cFlag(leaf *nowRoot)
{
	int flag = 11;
		while (flag != 3 && flag!=2 && flag != 1 && flag != 0)
		{
			printf ("\n Add left leaf for\t(%d)\t[input: 1]",nowRoot->val);
			printf ("\n Add right leaf for\t(%d)\t[input: 2]",nowRoot->val);
			if(nowRoot->parent == NULL)
				printf ("\n# Up to root\t\t(--)\t[No parent]");
			else
				printf ("\n Up to root\t\t(%d)\t[input: 3]",nowRoot->parent->val);
			printf ("\n Exit to main menu\t\t[input: 0]");
			printf ("\n\tCommand: ");  scanf("%d", &flag);
		}
	return flag;
}



leaf* up_root(leaf *root)
{
	if (root->parent)
	{
		printf("....now you at leaf \t(%d)\n", root->parent->val);
		return root->parent;
	}
	else
	{
		printf("....now you at leaf (%d), (%d) - ROOT of all tree!\n", root->val, root->val);
		return root;
	}
}



leaf* cr_left_son(leaf *parent)
{
	leaf *tmpSon;
	tmpSon = new leaf;
		if (parent->son_l)						/// if we already has son
		{
			delete tmpSon;
			printf ("....parent (%d) has left son (%d)", parent->val, parent->son_l->val);
			printf ("\n....return pointer to left son (%d)\n", parent->son_l->val);
			return parent->son_l;
		}
	parent->son_l = tmpSon;
	tmpSon->parent = parent;
	tmpSon->val = give_val();
	tmpSon->son_l = NULL;
	tmpSon->son_r = NULL;
	return tmpSon;
}



leaf* cr_right_son(leaf *parent)
{
	leaf *tmpSon;
	tmpSon = new leaf;
		if (parent->son_r)						/// if we already has son
		{
			delete tmpSon;
			printf ("....parent (%d) has right son (%d)", parent->val, parent->son_r->val);
			printf ("\n....return pointer to right son (%d)\n", parent->son_r->val);
			return parent->son_r;
		}
	tmpSon->val = give_val();
	tmpSon->parent = parent;
	tmpSon->son_l = NULL;
	tmpSon->son_r = NULL;
	parent->son_r= tmpSon;
	return tmpSon;
}



void create_tree(leaf *root)
{
	short flag = NULL;
	printf ("\nLet\'s create binar tree.");
	printf ("\n....Input value of root: ");
	scanf ("%d", &(root->val));
		while (1)
		{
			switch (give_cFlag(root))			/// give flag
			{
				case 1:
					root = cr_left_son(root);	/// create left son
					break;
				case 2:
					root = cr_right_son(root);	/// create right son
					break;
				case 3:
					root = up_root(root);		/// go up to parent
					break;
				case 0:
					flag = EXIT_WHILE;			/// exit from create part
					break;
				default:
					;
			}
			if (flag == EXIT_WHILE) break;
		}
}



void inorder(leaf *root)
{
	if(!root) return;

	inorder(root->son_l);
	if(root->val) printf("%d ", root->val);
	inorder(root->son_r);
}



void preorder(leaf *root)
{
	if(!root) return;

	if(root->val) printf("%d ", root->val);
	preorder(root->son_l);
	preorder(root->son_r);
}



void postorder(leaf *root)
{
	if(!root) return;

	postorder(root->son_l);
	postorder(root->son_r);
	if(root->val) printf("%d ", root->val);
}



void print_tree(leaf* root)
{
	printf("\nPrinted tree:");
	printf("\nSimmetric order:\t");
	inorder(root);
	printf("\nDirect order:\t\t");
	preorder(root);
	printf("\nBack order:\t\t");
	postorder(root);
	printf("\n");
}



void delete_tree(leaf *root)
{
	if(!root) return;

	delete_tree(root->son_l);
	delete_tree(root->son_r);
	if(root->val) 
	{
		printf("\n....destroy (%d)", root->val);
		delete root;
	}
}