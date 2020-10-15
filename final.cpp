#include<iostream>
#include<string>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


struct Node
{
public:
        Node *parent;
        Node *left;
        Node *right;
//      Node *head;
//      Node *tail;
        int cost;
        int bf;
        int height;
        int reversed;
        int external_bit;
        Node()
        {
                parent=NULL;
                left=NULL;
                right=NULL;
                cost=0;
                bf=0;
                height=1;
                reversed=0;
                external_bit=0;
        };
};

Node* find_parent(Node* u)
{
        cout<< "whoa we are in find parent\n";
        while( u->parent!= NULL)
        {
		cout<<"we are stuck\n";
                u=(*u).parent;
        }
        return u;
}

void modify_height(Node *u)
{
	cout<< "we are modifying the height\n";
	while( u!= NULL)
	{
		cout<<"we are stuck in height\n";
                (*u).height++;
		u=(*u).parent;
	}
}

void update_bf(Node *u)
{
	while(u!=NULL)
	{
        	(*u).bf=(*((u->left))).height-(*((u->right))).height;
		u=(*u).parent;
	}
}

void balance(Node *p)
{
        cout<<"we are in balance\n";
	update_bf(p);
        cout<<"balance factor is " <<(*p).bf<<"\n";
        while(((*p).bf!=-1)&&((*p).bf!=0)&&((*p).bf!=1))
        {
                cout<<"we are in while\n";
                if((*p).bf>1)
                {
                        if((*((*p).left)).bf>=0)
                        {
                                (*p).parent=(*p).left;
                                (*((*p).left)).parent=NULL;
                        //      (*((*p).left)).right=p;
                                (*p).left=(*((*p).left)).right; //aniruddh's favourite
                                (*((*p).left)).parent=p;
                                (*((*p).parent)).right=p;
                                (*p).height=(*p).height-2;
                                update_bf(p);
                                p=(*p).parent;
//                              update_bf(p);
                                (*p).height=(*((*p).left)).height+1;
                                update_bf(p);
				balance((*p).parent);
                        /*        if((*((*p).right)).bf!=-1||(*((*p).right)).bf!=0||(*((*p).right)).bf!=1)
                                {
                                        balance(((*p).right));
                                }*/
                        }
//                      if((*((*p).left)).bf<0)
                        else
                        {
                                (*p).parent=(*((*p).left)).right;
                                (*(*((*p).left)).right).parent=NULL;
                                (*((*p).left)).right=(*((*p).parent)).left;
                                (*(*((*p).left)).right).parent=(*p).left;
                                update_bf((*p).left);
                                (*((*p).left)).height=(*(*((*p).left)).left).height+1;
                                (*((*p).left)).parent=(*p).parent;
                                (*((*p).parent)).left=(*p).left;
                                (*p).left=(*((*p).parent)).right;
                //              (*((*p).right).parent)=p;
                                (*(*((*p).parent)).right).parent=p;
                                (*((*p).parent)).right=p;
                                (*p).height=(*p).height-2;
                                update_bf(p);
                                p=(*p).parent;
                                (*p).height=(*((*p).right)).height+1;
                                update_bf(p);
				balance((*p).parent);
                           /*     if((*((*p).right)).bf!=-1||(*((*p).right)).bf!=0||(*((*p).right)).bf!=1)
                                {
                                        balance(((*p).right));
                                }*/
                        }
		}
              //  else if((*p).bf<-1)
		else
                {
                        if((*((*p).left)).bf>=0)
                        {
                                (*p).parent=(*((*p).right)).left;
                                (*(*((*p).right)).left).parent=NULL;
                                (*((*p).right)).left=(*((*p).parent)).right;
                                (*(*((*p).parent)).right).parent=(*p).right;      //j is left of a
                                (*(*p).right).height=(*(*p).right).height-1;    //height of a
                                update_bf((*p).right);
                                (*((*p).parent)).right=(*p).right;
                                (*((*p).right)).parent=(*p).parent;             //a is right of c
                                (*p).right=(*((*p).parent)).left;
                                (*(*((*p).parent)).left).parent=p;         //i is right of b
                                (*p).height=(*p).height-2;                      //height of b
                                update_bf(p);
                                (*((*p).parent)).left=p;                //complete
                                p=(*p).parent;
                                (*p).height=(*(*p).left).height + 1;
                                update_bf(p);
				balance((*p).parent);
                             /*   if((*((*p).left)).bf!=-1||(*((*p).left)).bf!=0||(*((*p).left)).bf!=1)
                                {
                                        balance(((*p).left));
                                }*/

                        }
//                      if((*((*p).left)).bf<0)
                        else
                        {
                                (*p).parent=(*p).right;
                                (*((*p).parent)).right=NULL;
                                (*p).right=(*(*p).right).left;
                                (*(*(*p).right).left).parent=p;         // c is right of p
                                (*p).height=(*p).height-2;
                                update_bf(p);
                                (*((*p).parent)).left=p;                //p is left of a
                                p=(*p).parent;
                                update_bf(p);
				balance((*p).parent);
                              /*  if((*((*p).left)).bf!=-1||(*((*p).left)).bf!=0||(*((*p).left)).bf!=1)
                                {
                                        balance(((*p).left));
                                }*/
                        }

                }
        }
}



void link(Node* u,Node* v, int w)
{
	Node *N;
        N=new Node;
        (*N).cost=w;
	Node *lparent;
        lparent= new Node;
        Node *rparent;
        rparent= new Node;
        lparent=find_parent(u);
	cout<< "parent of u is "<<(*find_parent(u)).cost<< "\n";
	cout<< "parent of v is "<<(*find_parent(v)).cost<< "\n";
        rparent=find_parent(v);
	if((*lparent).height<=(*rparent).height)
	{
		cout<<"right is greater\n";
//		Node *lparent;
//		lparent= new Node;
//		Node *rparent;
//		rparent= new Node;
//		lparent=find_parent(u);
//		rparent=find_parent(v);
		Node *cur;
		cur = new Node;
		cur=rparent;
		while((*cur).height>(*lparent).height)
		{
			cur=(*cur).left;
		}
//		Node *N;
//                N=new Node;
//		(*N).cost=w;
		if(cur==rparent)
		{
//			cout <<"CASE R1\n";
			(*N).left=lparent;
			(*lparent).parent=N;
			(*N).right=rparent;
			(*rparent).parent=N;
			(*N).height=(*rparent).height+1;
			update_bf(N);
		}
		else if((*(*cur).parent).bf==-1)
		{
			cout<< "CASE R2\n";
			(*N).parent=(*cur).parent;
			(*(*cur).parent).left=N;
			(*N).left=lparent;
			(*lparent).parent=N;
			(*N).right=cur;
			(*cur).parent=N;
//			if((*N).parent)
  //                              modify_height((*N).parent);
			(*N).height=(*cur).height+1;
			if((*(*N).parent).height==(*N).height)
                                modify_height((*N).parent);
			update_bf(N);
		}
		else
		{
			cout <<"CASE R3\n";
			(*N).parent=(*((*cur)).parent).parent;
	//		(*(*cur).parent).parent=N;
			if(((*((*cur)).parent).parent))
				(*(*((*cur)).parent).parent).left=N;
			(*N).right=(*cur).parent;
			(*(*cur).parent).parent=N;
			(*N).height=(*(*cur).parent).height+1;
			if((*N).parent)
				modify_height((*N).parent);
			(*N).left=lparent;
			(*lparent).parent=N;
			update_bf(N);
			if((*N).parent)
			{
				if(((*(*N).parent).bf!=-1)&&((*(*N).parent).bf!=-0)&&((*(*N).parent).bf!=1))
                        	{
                                	balance((*N).parent);
                        	}
			}
		}

	}
//	if((*lparent).height>(*rparent).height)
	else
	{
		cout<< "left is greater\n";
//		Node *lparent;
 //               lparent= new Node;
   //             Node *rparent;
     //           rparent= new Node;
       //         lparent=find_parent(u);
         //       rparent=find_parent(v);
                Node *cur;
                cur = new Node;
                cur=lparent;
                while((*cur).height>(*rparent).height)
                {
                        cur=(*cur).right;
                }
		if(cur==lparent)
		{
			cout<<"CASE L1\n";
			(*N).left=lparent;
                        (*lparent).parent=N;
                        (*N).right=rparent;
                        (*rparent).parent=N;
			(*N).height=(*lparent).height+1;
			update_bf(N);
		}
		else if((*(*cur).parent).bf==1)
		{
			cout<<"CASE L2\n";
			(*N).parent=(*cur).parent;
                        (*(*cur).parent).right=N;
                        (*N).right=rparent;
                        (*rparent).parent=N;
                        (*N).left=cur;
                        (*cur).parent=N;
//			if((*N).parent)
  //                              modify_height((*N).parent);
			(*N).height=(*rparent).height+1;
			if((*(*N).parent).height==(*N).height)
                                modify_height((*N).parent);
			update_bf(N);
		}
		else
                {
			cout<<"CASE L3\n";
			(*N).parent=(*((*cur)).parent).parent;
          //              (*(*cur).parent).parent=N;
			if((*((*cur)).parent).parent)
				(*(*((*cur)).parent).parent).right=N;
                        (*N).left=(*cur).parent;
                        (*(*cur).parent).parent=N;
			(*N).height=(*(*cur).parent).height+1;
			if((*N).parent)
                                modify_height((*N).parent);
                        (*N).right=rparent;
                        (*rparent).parent=N;
			update_bf(N);
			cout<<"before balancing in L3\n";
			if((*N).parent)
			{
				if(((*(*N).parent).bf!=-1)&&((*(*N).parent).bf!=-0)&&((*(*N).parent).bf!=1))
				{
					balance((*N).parent);
				}
			}
                }


	}
	cout<< "cost of N is "<<(*N).cost<<" cost of left is "<<(*N).left->cost <<" and cost of right is "<<(*N).right->cost <<" and height is " << (*N).height<<" and bf is "<< (*N).bf<< " and the root with bf is " <<(*find_parent(N)).cost<<" " << (*find_parent(N)).bf<< "\n";
}

Node *tree_minimum(Node *a)
{
	while((*a).left!=NULL)
		a=(*a).left;
	return a;
}

Node *tree_maximum(Node *a)
{
        while((*a).right!=NULL)
                a=(*a).right;
        return a;
}

Node *pre(Node* x)
{
        if((*x).left!=NULL)
                return  tree_maximum((*x).left);
        Node *y;
        y=(*x).parent;
        while(((*y).parent!=NULL)&&(x==(*y).left))
        {
                x=y;
                y=(*y).parent;
        }
        return y;
}

Node *suc(Node* x)
{
	cout<<" we are in suc\n";
//	if((*x).external_bit==1)
//		return x;
	if((*x).right!=NULL)
		return  tree_minimum((*x).right);
	Node *y;
	y=(*x).parent;
	cout<<" y is " <<(*y).cost << " and its left is " <<(*(*y).left).cost <<" and parent is "<<(*y).parent<<"\n";
	cout<<"parent of "<<(*x).cost<<" is "<< (*(*x).parent).cost << "\n";
	while(((*y).parent!=NULL)&&(x==(*y).right))
	{
		cout<<" we are in loop\n";
		x=y;
		y=(*y).parent;
	}
	cout<<" we are out of loop\n";
	return y;
}
void inorder(Node *r)
{
        if(r!=NULL)
        {
                inorder((*r).left);
                cout<<"inorder node is "<<(*r).cost<<"\n";
                inorder((*r).right);
        }
}

void cut(Node* u, Node* v)
{
	Node *pred,*sucs;
        pred=pre(v);
	sucs=suc(u);
	cout<< "we are in cut\n";
	cout<<"cost of suc of u"<<(*suc(u)).cost<<"\n";
        if ((*suc(u)).parent==NULL)
        {       cout<<"we r in C1\n";
                (*(*suc(u)).left).parent=NULL;
                (*(*pre(v)).right).parent=NULL;
        }
//	Node *pred;
//	pred=pre(v);

 	else if(suc(u)==((*(*suc(u)).parent).right))
	{
		cout<<"we r in C2\n";
		Node *y,*x;
		cout<<"cost of predec of v "<<(*pre(v)).cost<<"\n";
		x=pre(v);
		y=(*pre(v)).parent;
		while(((*y).parent!=NULL)&&(x==(*y).right))
        	{
                	cout<<" we are in loop\n";
                	x=y;
                	y=(*y).parent;
        	}

		(*(*y).right).parent=NULL;
	//	(*y).left=NULL;
		(*(*pre(v)).right).parent=NULL;
		cout<<"OLD Y is " <<(*y).cost<<"\n";
	//	(*(*sucs).right).parent=NULL;
		cout<<"BEFORE LINK1 "<<(*suc(u)).cost<<" "<<(*(*sucs).right).cost<<" "<<(*(*y).right).cost<<" "<<(*y).cost<<"\n";
		link((*suc(u)).right,(*y).right,(*y).cost);
		cout<<"NEW Y is " << (*y).cost<<"\n";
	//	inorder(y);
		Node *a,*b;
		b=pred;
	//	(*b).right=NULL;
		cout<< "previos of v is " << (*pred).cost << "\n" ;
		while((*b).parent!=y)
                {

                //      a=pre(v);
                        (*(*(*b).parent).left).parent=NULL;
                        (*(*b).left).parent=NULL;
			cout<<" WE ARE HERE\n";
			cout<<" b , b.parent, b.parent.left,b.left "<<(*b).cost<<" "<<(*(*b).parent).cost<<" "<<(*(*(*b).parent).left).cost<< " "<< (*(*b).left).cost<<" "<< (*(*b).right).cost <<"\n";
                        link((*(*b).parent).left,(*b).left,(*(*b).parent).cost);
			cout<<" b , b.parent, b.parent.left,b.left "<<(*b).cost<<" "<<(*(*b).parent).cost<<" "<<(*(*(*b).parent).left).cost<< " "<< (*(*b).left).cost<<" "<< (*(*b).right).cost <<"\n";
			cout<<"AFTER LINK in C2\n";
                        a=(*(*b).left).parent;
                        b=(*b).parent;
                        (*b).left=a;
                        (*a).parent=b;
                }
                (*a).parent=NULL;
		if((*y).parent)
		{
                	(*(*(*y).parent).left).parent=NULL;
                	link(a,(*(*y).parent).left,(*(*y).parent).cost);
		}

	}

//			(*(*pre(v)).right).parent=(*(*pre(v)).parent).parent;
	//		(*(*pre(v)).right).parent=y;
//			(*(*(*pre(v)).parent).parent).left=(*pre(v)).right;
	//		(*y).left=(*pre(v)).right;
//		(*pre(v)).right=NULL;
	//	cout<<"pre success\n";
	//	balance((*suc(u)).parent);
	//	balance((*(*pre(v)).right).parent);

	else if(suc(u)==((*(*suc(u)).parent).left))
	{       cout<<"we r in C3\n";
		Node *y,*x;
		x=pre(v);
                y=(*pre(v)).parent;
                while(((*y).parent!=NULL)&&(x==(*y).left))
                {
                         cout<<" we are in loop\n";
                         x=y;
                         y=(*y).parent;
                }
		(*(*y).left).parent=NULL;
		link((*y).left,(*suc(u)).left,(*y).cost);
		cout<<"HELLO BABY\n";
		Node *a,*b;
		b=pred;
		while((*b).parent!=y)
		{

		//	a=pre(v);
			(*(*(*b).parent).right).parent=NULL;
			(*(*b).right).parent=NULL;
			link((*(*b).parent).right,(*b).right,(*(*b).parent).cost);
			a=(*(*b).right).parent;
			b=(*b).parent;
			(*b).right=a;
			(*a).parent=b;
		}
		(*a).parent=NULL;
		if((*y).parent)
		{
			(*(*(*y).parent).right).parent=NULL;
			link(a,(*(*y).parent).right,(*(*y).parent).cost);
		}
	}
}

void multi_add_weight(Node* u,Node* v,int w)
{
	Node* a;
	a=suc(u);
	Node* b;
	b=pre(v);
//	while(a!=b)
	{

	}

}
void swap(Node *u)
{
	Node *l;
	l=new Node;
        l=(*u).left;
        (*u).left=(*u).right;
        (*u).right=l;
}
void reversed(Node *p)
{
//	Node *l;
//	l=(*u).left;
//	(*u).left=(*u).right;
//	(*u).right=(*u).left;
	if(p!=NULL)
	{
		cout<<"we are in reversed and p is "<<(*p).cost<<"\n";
		reversed((*p).left);
		if((((*p).left)!=NULL)&&(((*p).right)!=NULL))
		{
			(*p).reversed=1;
		}
		cout<< "reversed bit of "<<(*p).cost<<" is "<<(*p).reversed<<" and left is "<<(*p).left<<"\n";
		reversed((*p).right);
	}
}
void inorder_reverse(Node *r)
{
	if(r!=NULL)
	{
		cout<<"we are in inorder reverse and r is "<<(*r).cost<< " and left is "<< (*r).left<<"\n";
		inorder_reverse((*r).left);
		cout<<"node is "<<(*r).cost<<" and left,right is "<< (*r).left<<","<<(*r).right<<"\n";
		if((*r).reversed==1)
		{
			swap(r);
			(*r).reversed=0;
		}
		else
			cout<<"node is "<<(*r).cost<<" and new left,right is "<< (*r).left<<","<<(*r).right<<"\n";

		inorder_reverse((*r).right);
	}
	else return;
}
/*void inorder(Node *r)
{
        if(r!=NULL)
        {
                inorder((*r).left);
                cout<<"inorder node is "<<(*r).cost<<"\n";
                inorder((*r).right);
        }
}*/

void reverse_path(Node* u)
{
	(*u).reversed=1;
}
Node a[10000000];
int main()
{
	int u,v,w;
        unsigned int i,n;
        char code;
        cin >> n;
        //Node a[n];
        for(i=0;i<n;i++)
        {
                a[i].cost=i;
        //        a[i].left=NULL;
        //      a[i].right=NULL;
        //      a[i].parent=NULL;
        //      a[i].head=NULL;
        //      a[i].tail=NULL;
                a[i].external_bit=1;
        //      a[i].height=1;
        //      a[i].bf=0;
        //      a[i].cost=i;
        //      a[i].reversed=0;
                cout << a[i].cost <<"\n";
        }
        cout<< a[i+1].cost << "\n";
        cin.clear();
        cin.ignore();

	while(1)
        {
                scanf("%s",&code);
                switch(code)
                {
                        case 'L':
//                              cout << "in L \n";
                                scanf("%d",&u);
                                scanf("%d",&v);
                                cout << "before entering w \n";
                                scanf("%d",&w);
                                cout << "before link\n";
                                link(&a[u],&a[v],w);
                                cout << "after link\n";
				cout<<"the cost and height of grand parent is " << (*find_parent(&a[4])).cost<< " "<<(*find_parent(&a[4])).height<<""<<(*(*find_parent(&a[4])).right).cost<<"\n";
                                cin.clear();
                                cin.ignore();
                                break;
                        case 'C':
                                scanf("%d",&u);
                                scanf("%d",&v);
				cout<<"parent of u and v before are "<<(*find_parent(&a[u])).cost<< " " <<(*find_parent(&a[v])).cost<< "\n" ;
                                cut(&a[u],&a[v]);
				cout<< "revised parent are "<<(*find_parent(&a[u])).cost<<" "<<(*find_parent(&a[v])).cost<<"\n";
                                cout << "we are in C \n";
                                cin.clear();
                                cin.ignore();
                                break;
                        case 'A':
                                scanf("%d",&u);
                                scanf("%d",&v);
                                scanf("%d",&w);
                                cout << "we are in A\n";
                                cin.clear();
                                cin.ignore();
                                break;
                        case 'R':
                                scanf("%d",&u);
                                cout << "we are in R \n";
				reverse_path(&a[u]);
                                cin.clear();
                                cin.ignore();
                                break;
                        case 'M':
                                scanf("%d",&u);
                                scanf("%d",&v);
                                cout << " we are in M \n";
                                cin.clear();
                                cin.ignore();
                                break;
                        case 'I':
                                scanf("%d",&u);
                                scanf("%d",&v);
                                cout << " we are in I \n";
			case 'E':
				break;
                        default:
                                cout << "Enter valid symbol\n";
                                cin.clear();
                                cin.ignore();
                                break;
                }
                for(i=0;i<n;i++)
                {
                        cout << a[i].cost <<"\n";
                }


        }
}


