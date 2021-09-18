// Created by: Kenil Chovatiya

#include <stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>


struct tweet_requirment
  {
      int id;
      char created_at[51];
      char text[141];
      char user[21];
      struct tweet_requirment *next;
  };
  
  typedef struct tweet_requirment user;

void CreateNewTweet(user **head,char username[],int *id1)
{
	user *temp = (user*)malloc(sizeof(user));
	temp->id = *id1;
	*id1 = *id1+1;
	temp->next = NULL;
	strcpy(temp->user,username);
	printf("Enter the tweet :");
	scanf("%[^\n]s",(temp->text));
	
	
	if(*head==NULL)
	{
		*head=temp;
	}
	else
	{
		temp->next=*head;
		*head=temp;
	}
	 /*get UTC time*/
  
   struct tm *local;
  
   time_t t;
  
   t = time(NULL);
  
   local = gmtime(&t);
  
   strcpy(temp->created_at,asctime(local));   //get time
  
   strcpy(temp->created_at,strtok(temp->created_at,"\n") );   //eliminate the newline character
  
   printf("New Tweet Created:\n");
   printf("id: %-10dCreated at: %s by %s\n%s\n",temp->id,temp->created_at, temp->user,temp->text);
  
}


void SearchTweets (user *head, char keyword[21])
{
	user *current=head;
	int x=0;
	while(current!=NULL)
	{
        if(strstr(current->text, keyword) != NULL )
		{
           printf("Found match:\n");
           printf("ID: %d,Created at: %s by %s\nTWEET : \"%s\"\n",current->id,current->created_at,current->user, current->text);
           x++;
        }
		current=current->next;
	}
	if(x== 0)
		printf("No tweets matched\n");
  
	else
		printf(" %d tweets found!\n", x);
}

void DisplayTweets(user *head)
{
	while(head!=NULL)
	{
		printf("ID: %d,Created at: %s by %s\nTWEET : \"%s\"\n",head->id,head->created_at,head->user,head->text);
		 
		head=head->next;
	}
}


int sizeoftweet(user *tweets)
 {
     int count;
     while(tweets!=NULL)
      {
          count++;
          tweets=tweets->next;
      }
      return count;
 }
 
int SaveTweets(const user *tweets, char *fname)
{
  int size=sizeoftweet(tweets);
   int c = 0;       //c is for counting how many tweets in the array
  
   for(int i = 0; i < size; i++){
      
       if((tweets + i)->id >= 1000 && (tweets + i)->id < 1005){
          
           c++;
          
       }
      
   }
  
   FILE *fp;
  
   fp = fopen(fname,"w");
  
   if(fp != NULL){
      
       for(int n = 0; n < c; n++){
      
           fprintf(fp,"%d\n%s\n%s\n%s\n",
           (tweets+n)->id,(tweets+n)->created_at,(tweets+n)->user,(tweets+n)->text);
          
       }
      
       fclose(fp);
      
       printf("%d tweet(s) saved in file \"%s\"",c,fname);
   }else{
      
       printf("There's something wrong with the file");
      
   }
  
   return 0;
          
}

int LoadTweets(user *tweets, char *filename)
{
  
  int size= sizeoftweet(tweets);
   FILE *fp;
  
   int count = 0;
  
   fp = fopen(filename,"r");
  
   if(fp!=NULL){
      
      
       while(!feof(fp)){
          
           fscanf(fp,"%d%*c",&tweets[count].id);
          
           fscanf(fp,"%24[^\n]s",tweets[count].created_at);
          
           fscanf(fp,"%*c");
          
           fscanf(fp,"%20[^\n]s",tweets[count].user);
          
           fscanf(fp,"%*c");
          
           fscanf(fp,"%140[^\n]s",tweets[count].text);
           
           count++;
       }
      
       fclose(fp);
      
       count--;
       return count;
      
   }else{
      
       puts("There's something wrong with the file");
      
       return 0;
   }
  
}


int main()
{
   user *tweet=NULL;
     int i; //Chossing option.
     int _id = 1000;   //initialize the id start at 1000
    char username[21];  // for user name 
    char word[21];      // for key word to search 
    char fname[21];     // for file name at the time of saving
    char lfile[21];     // for loading file 
    int  c = 0;         // number of loaded tweets 
   printf(" simple twitter….....\n");
   printf("---------------------------------------\n");
  
   printf("Please enter your name: ");
  
   scanf("%20[^\n]s", username);
 
   printf("Welcome %s, let's start tweeting...", username);
    top:
    printf("\n1. Create a new tweet\n");
       printf("2. Search tweets\n");
       printf("3. Display tweets\n");
       printf("4. Save tweets to file\n");
       printf("5. Load tweets from file\n");
       printf("6. Exit\n");
       printf("\n\nEnter your choice : ");
      
       scanf("%d",&i);
      
       getchar();
       
  while(i!=6) {
      
     switch(i)
      {
          case 1:
            {
                   printf("Tweet text (No more than 140 characters): ");
                   CreateNewTweet(&tweet, username,&_id);
                   _id++;
              goto top;
              break;
            }      
          case 2:
            {
              printf("Please enter the search keyword: ");
              
               scanf("%s", word);
              
               SearchTweets(tweet,word);
              goto top;
              break;
            }
          case 3:
            {
              DisplayTweets(tweet);
              goto top;
              break;
            }      
          case 4:
            {
              printf("Please enter a filename: ");
              
               scanf("%20[^\n]s%*c", fname);
              
               SaveTweets(tweet,fname);
              goto top;
              break;
            }
          case 5:
            {
              printf("Please enter a filename: ");
              
               scanf("%20[^\n]s%*c", lfile);
              
               c = LoadTweets(tweet,lfile);
              
               _id = 1000 + c;
              
               printf("%d tweet(s) loaded form file \"%s\"",c, lfile);
              goto top;
              break;
              
            }
            case 6:
            break;
            default:
              
               printf("\nNo Such Function\n");
              goto top;
               break;
          
       }
    } 
    return 0;
}






