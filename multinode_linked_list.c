#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


struct node{
	char name[20];
	int marks;
	struct node *next_node_by_marks;
	struct node *next_node_by_names;
};


int debug=0;
struct node *head_by_marks;
struct node *head_by_names;


int display(struct node *temp, bool by_marks);
int insert_by_marks(char *name, int marks);
int insert_by_names(char *name, int marks);

int insert_by_marks(char *name, int marks){
	
	struct node *temp = (struct node*) malloc(sizeof(struct node));
	temp->next_node_by_marks=NULL;
	strcpy(temp->name,name);
	temp->marks=marks;

	if(head_by_marks==NULL){
		head_by_marks=temp;
		if(debug) printf("student %s inserted with marks %d at head node.",name,marks);
		return 0;
	}else if(head_by_marks->marks==marks){
		if(strcmp(name,head_by_marks->name)<0){
                	temp->next_node_by_marks=head_by_marks;
                        head_by_marks=temp;
		}else{
			temp->next_node_by_marks=head_by_marks->next_node_by_marks;
			head_by_marks->next_node_by_marks=temp;
		}
		if(debug) printf("student %s inserted with marks %d.\n",name,marks);
		return 0;
	}else if(head_by_marks->marks < marks){
		temp->next_node_by_marks=head_by_marks;
		head_by_marks=temp;
		if(debug) printf("student %s inserted with marks %d at position 1.",name,marks);
		return 0;
	}
	else{
		struct node *ptr1=head_by_marks;
		struct node *ptr2=NULL;
		while(ptr1!=NULL){
			if(ptr1->marks==marks){
				if(strcmp(name,ptr1->name)>0){
					temp->next_node_by_marks=ptr1->next_node_by_marks;
					ptr1->next_node_by_marks=temp;
					printf("student %s inserted with marks %d.\n",name,marks);
					return 0;
				}
				break;
			}else if(ptr1->marks>marks){
				// continue with next iteration
			}else if(ptr1->marks<marks){
				break;
			}
		ptr2=ptr1;
		ptr1=ptr1->next_node_by_marks;
		}
		temp->next_node_by_marks=ptr1;
		ptr2->next_node_by_marks=temp;
	}
	if(debug) printf("student %s inserted with marks %d.\n",name,marks);
}


int insert_by_names(char *name, int marks){

        struct node *temp = (struct node*) malloc(sizeof(struct node));
        temp->next_node_by_names=NULL;
        strcpy(temp->name,name);
        temp->marks=marks;

        if(head_by_names==NULL){
                head_by_names=temp;
                if(debug) printf("student %s inserted with marks %d at head node.",name,marks);
                return 0;
        }else if(strcmp(name,head_by_names->name)<0){
                temp->next_node_by_names=head_by_names;
                head_by_names=temp;
                if(debug) printf("student %s inserted with marks %d at position 1.",name,marks);
                return 0;
        }
        else{
                struct node *ptr1=head_by_names;
                struct node *ptr2=NULL;
                while(ptr1!=NULL){
			int val=strcmp(name,ptr1->name);
                        if(val==0){
                                if(marks<ptr1->marks){
                                        temp->next_node_by_marks=ptr1->next_node_by_marks;
                                        ptr1->next_node_by_marks=temp;
					printf("student %s inserted with marks %d.\n",name,marks);
                                        return 0;
                                }
                                break;
                        }else if(val<0){
                                break;
                        }else if(val>0){
                                // continue with next iteration
                        }
                ptr2=ptr1;
                ptr1=ptr1->next_node_by_names;
                }
                temp->next_node_by_names=ptr1;
                ptr2->next_node_by_names=temp;
        }
        if(debug) printf("student %s inserted with marks %d.\n",name,marks);
}


int display(struct node *temp,bool by_marks){
	if(debug){
		if(by_marks) printf("\ndisplaying the list by marks");
		else printf("\n displaying the list by names");
	}

	if(temp==NULL) {
		printf("Underflow.");
		return 0;
	}

	while(temp!=NULL){
		printf("%s %d, ",temp->name,temp->marks);
		if(by_marks==true)
			temp=temp->next_node_by_marks;
		else
			temp=temp->next_node_by_names;
	}
}

int main(){
	
	char name[20];
	char anchor_condition[]="-999";
	int marks;
	char ch;
	
	//struct node *head_by_marks;
	//struct node *head_by_names;	

	do{
		if(debug) printf("\nenter the name: ");
		scanf("%[^\n]s",name);
		// validating the anchor condition -999
		if(strlen(name)>=4 && strcmp(name,anchor_condition)==0){
			if(debug) printf("\nuser entered the -999, breaking the loop.");
			break;
		}

		// validating the student name for special characters
		for(int i=0;i<strlen(name);i++){
			if(name[i]!=' '){
				if((name[i]>='a' && name[i]<='z') || (name[i]>='A' && name[i]<='Z')){
					continue;
				}else{
					printf("Input Error!!! Name of a student should only have alphabets.");
					exit(0);
				}
			}
		}
		
		if(debug) printf("enter the marks: ");	
		scanf("%d",&marks);
		printf("marks->%d",marks);
		// validating the student marks for negative
		if(marks<0){
			printf("marks cannot be negative.");
			return 0;
		}

		// validating the student marks if user missed
		// logic works only in IITK compiler :)
		if(marks>100){
			printf("Input Error!!! student marks missing.");
			return 0;
		}

		// clearing the buffer for scnaf %[^\n]s
		scanf("%c",&ch);
		
		insert_by_marks(name, marks);
		insert_by_names(name,marks);
		//display(head_by_marks,true);
	}while(1);

	if(head_by_marks==NULL || head_by_names==NULL){
		printf("\nYou must enter atleast one student.");
		return 0;
	}

	printf("\nDescending order of Marks: ");
	display(head_by_marks,true);
	if(debug) printf("\n");
	printf("\nAlphabetical Order: ");
	display(head_by_names,false);
	if(debug) printf("\n");

return 0;
}
