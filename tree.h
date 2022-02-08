#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxrecords 2048
#define maxtxtsize 33

struct stacksss{
	int size;
	int stacks[maxrecords];
};


void startstack(struct stacksss *stack){
	stack->size=0;
}
int push(struct stacksss *stack,int value){
	int i=0;
	i=stack->size;
	stack->stacks[stack->size]=value;
	stack->size++;
	return i;
}
int pop(struct stacksss *stack){
	int i=0;
	i=-1;
	if(stack->size>0){
		stack->size--;
		i=stack->stacks[stack->size];
	}
	return i;
}

void reportStack(struct stacksss *stack){
	int i=0;
	printf("\n");
	for(i=0;i<stack->size;i++){
		printf("%d",stack->stacks[i]);
		if(i!=stack->size-1){
			printf(",");
		}else{
			printf("\n");			
		}
	}
	
}

struct node{
	char caption[maxtxtsize];
	char text[maxtxtsize];
	int back;
	int nexts;
	int parent;
	int sun;
	int delete;
};

struct trees{
	int size;
	int roots;
	struct node nodes[maxrecords];
};

int starttree(struct trees *tree1){
	tree1->size=0;
	tree1->roots=-1;
}

int newnode(struct trees *tree1,char *caption,char *text){
	int i=tree1->size;
	int ii=0;
	int n=strlen(caption);
	struct node *nnode;
	if (tree1->size+1<maxrecords){
		nnode=&tree1->nodes[tree1->size];
		if(n>maxtxtsize-1)n=maxtxtsize-1;
		strncpy(nnode->caption,caption,n);
		nnode->caption[maxtxtsize-1]=0;
		n=strlen(text);
		if(n>maxtxtsize-1)n=maxtxtsize-1;
		strncpy(nnode->text,text,n);
		nnode->text[maxtxtsize-1]=0;
		nnode->back=-1;
		nnode->nexts=-1;
		nnode->parent=-1;
		nnode->sun=-1;
		nnode->delete=0;
		tree1->size++;
	}else{
		i=-1;
		for(ii=0;i<tree1->size;i++){
			nnode=&tree1->nodes[ii];
			if(nnode->delete==-1)i=ii;
		}
		if(i!=-1){
			nnode=&tree1->nodes[i];
			if(n>maxtxtsize-1)n=maxtxtsize-1;
			strncpy(nnode->caption,caption,n);
			nnode->caption[maxtxtsize-1]=0;
			n=strlen(text);
			if(n>maxtxtsize-1)n=maxtxtsize-1;
			strncpy(nnode->text,text,n);
			nnode->text[maxtxtsize-1]=0;
			nnode->back=-1;
			nnode->nexts=-1;
			nnode->parent=-1;
			nnode->sun=-1;
			nnode->delete=0;

		}else{
			printf("error no more space for nodes");
		}
	}
	return i;
}
void reporttree(struct trees *tree1,int node0){
	int b=0;
	int tabs=0;
	int current=node0;
	int pr=0;
	int i=0;
	int counter=0;
	struct stacksss stack;
	struct node *nnode;
	startstack(&stack);
	nnode=&tree1->nodes[node0];
	b=node0;	
	while (b!=-1){
		counter=0;
		pr=0;
		for(i=0;i<tabs;i++)printf("    ");
		printf("%s,%s\n",nnode->caption,nnode->text);
		if(nnode->sun!=-1){
			tabs++;
			push(&stack,current);
			current=nnode->sun;
			nnode=&tree1->nodes[current];
			b=current;
			pr=-1;
		}
		if (pr==0){
			b=nnode->nexts;
			if(b!=-1){
				current=nnode->nexts;
				nnode=&tree1->nodes[current];
				b=current;
				pr=-1;
			}
			if (stack.size > 0 && b==-1){
				b=-1;
				counter=0;
				while(stack.size>0 && b==-1){
					current=pop(&stack);
					tabs--;
					nnode=&tree1->nodes[current];
					counter++;
					b=nnode->nexts;
				}
				if(nnode->nexts != -1){
					current=nnode->nexts;
					nnode=&tree1->nodes[current];
					
				}				
			}
	
			

		}
		if(stack.size < 1 && pr==0){
			b=nnode->nexts;
		}else{
			b=current;
		}

	}

}

void setfather(struct trees *tree1,int node0,int nodeme){
	int i=0;
	int b=0;
	int bb=0;
	struct node *nnode;
	nnode=&tree1->nodes[node0];
	if(nnode->sun==-1){
		nnode->sun=nodeme;
		nnode=&tree1->nodes[nodeme];
		nnode->parent=node0;
		nnode->nexts=-1;
	}else{
		b=nnode->sun;
		nnode=&tree1->nodes[b];
		bb=b;
		while(b!=-1){
			b=nnode->nexts;
			if(b==-1){
				nnode->nexts=nodeme;
				nnode=&tree1->nodes[nodeme];
				nnode->back=bb;
				nnode->nexts=-1;
				b=-1;
			}else{
				b=nnode->nexts;
				nnode=&tree1->nodes[b];
				bb=b;
			}
		}
	}
}

void settreeRoot(struct trees *tree1,int node0){
	tree1->roots=node0;
}

void cleartree(struct trees *tree1){
	tree1->size=0;
	tree1->roots=-1;
}

void savetree(struct trees *tree1,char *name,long sizes){
	FILE *f1;
	f1=fopen(name,"w");
	fwrite(tree1,sizes,1,f1);
	fclose(f1);
}

void loadtree(struct trees *tree1,char *name,long sizes){
	FILE *f1;
	f1=fopen(name,"r");
	fread(tree1,sizes,1,f1);
	fclose(f1);
}


void reportnode(struct trees *tree1,int node0){
	struct node *nnode;
	nnode=&tree1->nodes[node0];
	printf("%s,%s,%d,%d,%d,%d,%d\n",nnode->caption,nnode->text,nnode->back,nnode->nexts,nnode->parent,nnode->delete,nnode->sun);
}


void deletetreenode(struct trees *tree1,int node0){
	int b=0;
	int tabs=0;
	int current=node0;
	int pr=0;
	int i=0;
	int counter=0;
	struct stacksss stack;
	struct node *nnode;
	startstack(&stack);
	struct node *nnode1;
	nnode=&tree1->nodes[node0];
	nnode1=&tree1->nodes[node0];
	printf("DELETE NODE****");
	nnode->delete=-1;
	if (nnode->nexts!=-1){
		if (nnode->back!=-1){
			nnode1=&tree1->nodes[nnode->nexts];
			nnode1->back=nnode->back;
			nnode1=&tree1->nodes[nnode->back];
			nnode1->nexts=nnode->nexts;
		}else{
			if(nnode->parent!=-1){
				nnode1=&tree1->nodes[nnode->parent];
				nnode1->sun=nnode->nexts;
				nnode->parent=-1;
			}
		}
	}else{
			
		if (nnode->back!=-1){
			nnode1=&tree1->nodes[nnode->back];
			nnode1->nexts=-1;
		}else{
			if(nnode->parent!=-1){
				nnode1=&tree1->nodes[nnode->parent];
				nnode1->sun=nnode->nexts;
				nnode->parent=-1;
			}
			
		}
	}
	nnode=&tree1->nodes[node0];
	nnode->back=-1;
	nnode->nexts=-1;
	nnode->parent=-1;
	while (b!=-1){
		counter=0;
		pr=0;
		for(i=0;i<tabs;i++)printf("    ");
		printf("%s,%s\n",nnode->caption,nnode->text);
		nnode->delete=-1;
		nnode->caption[0]=0;
		nnode->text[0]=0;
		if(nnode->sun!=-1){
			tabs++;
			push(&stack,current);
			current=nnode->sun;
			nnode=&tree1->nodes[current];
			b=current;
			pr=-1;
		}
		if (pr==0){
			b=nnode->nexts;
			if(b!=-1){
				current=nnode->nexts;
				nnode=&tree1->nodes[current];
				b=current;
				pr=-1;
			}
			if (stack.size > 0 && b==-1){
				b=-1;
				counter=0;
				while(stack.size>0 && b==-1){
					current=pop(&stack);
					tabs--;
					nnode=&tree1->nodes[current];
					counter++;
					b=nnode->nexts;
				}
				if(nnode->nexts != -1){
					current=nnode->nexts;
					nnode=&tree1->nodes[current];
					
				}				
			}
	
			

		}
		if(stack.size < 1 && pr==0){
			b=nnode->nexts;
		}else{
			b=current;
		}

	}

	
}

void debugtree(struct trees *tree1,int node0,int nodeinto){
	int i=0;
	int ii=node0;
	int iii=nodeinto;
	if(node0<0 || node0>tree1->size)node0=0;
	if(nodeinto<0 || node0>tree1->size)nodeinto=tree1->size;
	for(i=ii;i<iii;i++)reportnode(tree1,i);

}

void settreenodecaption(struct trees *tree1,int node0,char *caption){
	int n=strlen(caption);
	struct node *nnode;
	nnode=&tree1->nodes[node0];
	if(n>maxtxtsize-1)n=maxtxtsize-1;
	strncpy(nnode->caption,caption,n);
	nnode->caption[maxtxtsize-1]=0;
}

void settreenodetext(struct trees *tree1,int node0,char *txt){
	int n=strlen(txt);
	struct node *nnode;
	nnode=&tree1->nodes[node0];
	if(n>maxtxtsize-1)n=maxtxtsize-1;
	strncpy(nnode->text,txt,n);
	nnode->caption[maxtxtsize-1]=0;
}



