#include "tree.h"

int main(int argc,char *argv[]){
	struct trees tree1;
	int roots=-1;
	int ARM=-1;
	int X86=-1;
	int APPLE=-1;
	int subnode=-1;
	int subnode1=-1;
	printf("\ec\e[44;36m\n\a\n");
	starttree(&tree1);
	roots=newnode(&tree1,"PC","pcs");
	settreeRoot(&tree1,roots);
	ARM=newnode(&tree1,"ARM","arm");
	X86=newnode(&tree1,"X86","x86");
	APPLE=newnode(&tree1,"APPLE","apple");
	setfather(&tree1,roots,ARM);
	setfather(&tree1,roots,X86);
	setfather(&tree1,roots,APPLE);
	subnode=newnode(&tree1,"ARM6","arm6");
	setfather(&tree1,ARM,subnode);	
	subnode=newnode(&tree1,"ARM7","arm7");
	setfather(&tree1,ARM,subnode);	
	subnode=newnode(&tree1,"X8086","8086");
	setfather(&tree1,X86,subnode);	
	subnode=newnode(&tree1,"X80186","80186");
	setfather(&tree1,X86,subnode);	
	subnode=newnode(&tree1,"X80286","80286");
	setfather(&tree1,X86,subnode);	
	subnode=newnode(&tree1,"X80386","80386");
	setfather(&tree1,X86,subnode);	
	subnode=newnode(&tree1,"X80486","80486");
	setfather(&tree1,X86,subnode);	
	subnode=newnode(&tree1,"X80586","80586");
	setfather(&tree1,X86,subnode);	
	subnode1=subnode;
	subnode=newnode(&tree1,"MAC","mac");
	setfather(&tree1,APPLE,subnode);	
	deletetreenode(&tree1,APPLE);
	printf("***********\n");
	settreenodecaption(&tree1,tree1.roots,"MYPC");
	settreenodetext(&tree1,tree1.roots,"MYPC");
	reporttree(&tree1,tree1.roots);
	savetree(&tree1,"tree.dat",sizeof(tree1));
	cleartree(&tree1);
	/*
	loadtree(&tree1,"tree.dat",sizeof(tree1));
	reporttree(&tree1,tree1.roots);
	*/
}
