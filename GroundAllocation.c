
#include<stdio.h>
#include <string.h>
#define N 100

//Structure Declaration

struct ground_records
{
    char name[50];
    char state[50];
    char city[50];
    struct games
    {
        char name_of_game[20];
        struct scheduled
        {
            char dates[10];
            char times[12];
        }sch[4];
        struct available
        {
            char datea[10];
            char timea[12];
        }avlbl[4];
        int hourly_rate;
    }games[3];
    
}g[9];


//end of structure declaration

/*Sorting functions*/


void Merge_self(struct ground_records g[],int mid,int lo,int hi)
{
    int i,j,k,value,value1;
    i=lo,j=mid+1,k=lo;
    struct ground_records C[100];
    
    while(i<=mid && j<=hi)
    {
        value=strcmp(g[i].city,g[j].city);
        if(value==0)
        {
            value1=strcmp(g[i].name,g[j].name);
            if(value1<0)
            {
                C[k]=g[i];
                k++,i++;
            }
            else
            {
                C[k]=g[j];
                k++,j++;
            }
        }
        else
        {
            if(value<0)
            {
                C[k]=g[i];
                k++,i++;
            }
            else
            {
                C[k]=g[j];
                k++,j++;
            }
        }
    }
    
    while(i<=mid)
    {
        C[k]=g[i];
        k++,i++;
    }
    
    
    while(j<=hi)
    {
        C[k]=g[j];
        k++,j++;
    }
    
    for(int i=lo;i<=hi;i++)
    {
        g[i]=C[i];
    }
}


void Mergesort(struct ground_records g[],int lo,int hi)
{
    int mid;
    if(lo<hi)
    {
        mid=(lo+hi)/2;
        Mergesort(g,lo,mid);
        Mergesort(g,mid+1,hi);
        Merge_self(g,mid,lo,hi);
    }
}


void sortedData(struct ground_records g[])
{
    Mergesort(g,0,8);
    char value[10];
    
    for(int i=0;i<9;i++)
    {

        
            printf("%s\t",g[i].name);
            printf("%s\t",g[i].city);
            printf("%s\t",g[i].state);
            for(int j=0;j<3;j++)
            {
                printf("%s\t",g[i].games[j].name_of_game);
                printf("%d\t",g[i].games[j].hourly_rate);
                for(int k=0;k<4;k++)
                {
                    strcpy(value,g[i].games[j].sch[k].dates);
                    if(value!="0")
                    {
                        printf("%s\t",g[i].games[j].sch[k].dates);
                        printf("%s\t",g[i].games[j].sch[k].times);
                        printf("%s\t",g[i].games[j].avlbl[k].datea);
                        printf("%s\t",g[i].games[j].avlbl[k].timea);
                        printf("\n\t\t\t\t\t\t\t\t\t");
                    }
                }
            }   
        
        printf("\n");
        
    }
}


void Merge_self_date(struct ground_records g[],int mid,int lo,int hi)
{
    int i,j,k,value,value1;
    i=lo,j=mid+1,k=lo;
    struct ground_records C[100];
    
    
    while(i<=mid && j<=hi)
    {
        int ddi,ddj,mmi,mmj;
        sscanf(g[i].games[0].sch[0].dates,"%d-%d",&ddi,&mmi);
        sscanf(g[j].games[0].sch[0].dates,"%d-%d",&ddj,&mmj);
        if(mmi==mmj)
        {
            if(ddi<ddj)
            {
                C[k]=g[i];
                k++,i++;
            }
            else if(ddi>ddj)
            {
                C[k]=g[j];
                k++,j++;
            }
            else
            {
                value=strcmp(g[i].games[i].sch[i].times,g[i].games[j].sch[j].times);
                if(value<0)
                {
                    C[k]=g[i];
                    k++,i++;
                }
                else
                {
                    C[k]=g[j];
                    k++,j++;
                }
                
            }
        }
        else
        {
            if(mmi<mmj)
            {
                C[k]=g[i];
                k++,i++;
            }
            else
            {
                C[k]=g[j];
                k++,j++;
            }
        }
    }
    
    while(i<=mid)
    {
        C[k]=g[i];
        k++,i++;
    }
    
    
    while(j<=hi)
    {
        C[k]=g[j];
        k++,j++;
    }
    
    for(int i=lo;i<=hi;i++)
    {
        g[i]=C[i];
    }
}


void Mergesort_date(struct ground_records g[],int lo,int hi)
{
    int mid;
    if(lo<hi)
    {
        mid=(lo+hi)/2;
        Mergesort(g,lo,mid);
        Mergesort(g,mid+1,hi);
        Merge_self_date(g,mid,lo,hi);
    }
}


/*end of sorting functions*/


void getFixturesinCity(struct ground_records g[]) //Function a.
{
    char city[50];
    char date1[10],date2[10];

    printf("Enter the range of dates for which u wanna check the fixtures:");
    printf("\nEnter the start date:");
    scanf("%s",date1);
    printf("\nEnter the end date:");
    scanf("%s",date2);

    int i,j,k;
    int flag=1,loc;
    printf("Enter the name of city whose fixtures u wanna check:");
    scanf("%s",city);
        
    while(flag==1)
    {
        i=0;
        while(i<9 && flag==1)
        {
            if((strcmp(city,g[i].city))==0)
            {
                loc=i;  //loc-> 1st location of the city 
                flag=0;
            }
            else 
                i++;
        }
        if(flag==1)
        {
            printf("Previous entry was invalid,pls enter the name of city once again:");
            scanf("%s",city);
        }
    }

    flag=1;
    int size;
    char c[3][20]; // used to store the name of a game -> a maximum of 3 games can be played in a ground
    int search;
    char taarikh[10],tmp[10];              
       
    printf("The fixtures are as follows:\n");

    while(strcmp(g[loc].city,city)==0)
    {
        size=0;
        k=0;
        

        while(k<3)  //object corresponding to the games 
        {
            search=0;
            flag=1;
            while(search<4 && flag==1)
            {
                strcpy(taarikh,g[loc].games[k].sch[search].dates);
                if( (strcmp(taarikh,date1)>0) && (strcmp(taarikh,date2)<0) )
                    flag=0;
                    
                search++;
            } 
            if(flag==0)
            {
                strcpy(c[size],g[loc].games[k].name_of_game);
                size++;
            }
            k++; 
        }

        for(j=0;j<size;j++)         //bubble sort algorithm
        {
            for(k=0;k<size-1-j;k++)
            {
                if(strcmp(c[k],c[k+1])>0)
                {
                    strcpy(tmp,c[k]);
                    strcpy(c[k],c[k+1]);
                    strcpy(c[k+1],tmp);
                }
            }
        }

        printf("%s : ",g[loc].name);

        for(j=0;j<size;j++)
            printf("%s ",c[j]);
            
        printf("\n");
        loc++;
    }
    
    
}    


void getFixturesSortedonDate(struct ground_records g[]) // Function b.
{
    Mergesort_date(g,0,8);
    for(int i=0;i<9;i++)
    {
        printf(" %s ",g[i].name);
        for(int j=0;j<3;j++)
        {
            printf(" %s ",g[i].games[j].name_of_game);
            for(int k=0;k<4;k++)
            {
                printf(" %s ",g[i].games[j].sch[k].dates);
                printf(" %s ",g[i].games[j].sch[k].times);
                printf(" \n\t\t  ");
            }
            printf(" \n\t ");
        }
        printf(" \n ");
    }
}


void Merge_self_state_city(struct ground_records g[],int mid,int lo,int hi)
{
    int i,j,k,value,value1;
    i=lo,j=mid+1,k=lo;
    struct ground_records C[100];
    
    while(i<=mid && j<=hi)
    {
        value=strcmp(g[i].state,g[j].state);
        if(value==0)
        {
            value1=strcmp(g[i].city,g[j].city);
            if(value1<0)
            {
                C[k]=g[i];
                k++,i++;
            }
            else
            {
                C[k]=g[j];
                k++,j++;
            }
        }
        else
        {
            if(value<0)
            {
                C[k]=g[i];
                k++,i++;
            }
            else
            {
                C[k]=g[j];
                k++,j++;
            }
        }
    }
    
    while(i<=mid)
    {
        C[k]=g[i];
        k++,i++;
    }
    
    
    while(j<=hi)
    {
        C[k]=g[j];
        k++,j++;
    }
    
    for(int i=lo;i<=hi;i++)
    {
        g[i]=C[i];
    }
}


void Mergesort_state_city(struct ground_records g[],int lo,int hi)
{
    int mid;
    if(lo<hi)
    {
        mid=(lo+hi)/2;
        Mergesort(g,lo,mid);
        Mergesort(g,mid+1,hi);
        Merge_self_state_city(g,mid,lo,hi);
    }
}


void isAvailable(struct ground_records g[]) // Function c.
{
    char sport[20],datew[10],timew[12];
    struct ground_records gw[15];
   
    printf("Enter the sport you want:");
    scanf("%s",sport);
    
    printf("Enter the date you want:");
    scanf("%s",datew);
    
    printf("Enter the time you want:");
    scanf("%s",timew);
    
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(strcmp(sport,g[i].games[j].name_of_game)==0)
            {
                for(int k=0;k<4;k++)
                {
                    if(strcmp(datew,g[i].games[j].avlbl[k].datea)==0  &&  strcmp(timew,g[i].games[j].avlbl[k].timea)==0)
                    {
                        gw[i]=g[i];
                    }
                }
            }
        }
    }
    
    Mergesort(gw,0,8);
    for(int i=0;i<9;i++)
    {
        printf("%s ",gw[i].name);
        printf("%s ",gw[i].city);
        printf("%s ",gw[i].state);
        printf("\n");
    }

}


void UniqueSports(struct ground_records g[]) // Function d.
{
    char groundName[20],city[20];
    int flag,index;

    printf("Enter the name of ground:");
    scanf("%s",groundName);
    printf("Enter the city:");
    scanf("%s",city);
    
    for(int i=0;i<9;i++)
    {
        if(strcmp(groundName,g[i].name)==0)
        {
            index=i;
        }
    }
    
    for(int i=0;i<9;i++)
    {
        if(strcmp(g[i].city,city)==0)
        {
            for(int j=0;j<3;j++)
            {
                flag=0;
                for(int k=0;k<3 && flag==0;k++)
                {
                    if(strcmp(g[index].games[j].name_of_game,g[i].games[k].name_of_game)==0 && strcmp(g[i].city,city)==0)
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    printf("%s\n",(g[index].games[j].name_of_game));
                }
            }
        }
    }
}


void FindLocationsForGameInTimeRange(struct ground_records g[]) // Function e.
{
    int i,j,k;
    int flag=1,flag2=1;
    char gname[10];
    char timew[12];
    char date1[10];
    char date2[10];

    printf("Enter the name of the game:");
    scanf("%s",gname);

    
    printf(" note: A particular game can be played only once in a day ");
    printf("\n2 time slots are possible:");
    printf("\nChoose from 9:00-14:00 and 15:00-20:00");
    printf("\nhence ,enter the time slot:");
    
    scanf("%s",timew);

    printf("Enter the range of dates for which u wanna check the fixtures:");
    printf("\nEnter the start date:");
    scanf("%s",date1);

    printf("\nEnter the end date:");
    scanf("%s",date2);
    
    
    for(i=0;i<9;i++)
    {
        flag=1;
        for(j=0;j<3 && flag==1;j++)    // every game record
        {
            if((strcmp(gname,g[i].games[j].name_of_game))==0)
            {
                flag=0;     // the reqd game is found
                flag2=1;
                for(k=0;k<4 && flag2==1;k++)       // a game can have a maximum of 4 schedules possible, hence the loop runs 4 times
                {
                    if((strcmp(g[i].games[j].avlbl[k].timea,timew)==0) && (strcmp(g[i].games[j].avlbl[k].datea,date1)>0) && (strcmp(g[i].games[j].avlbl[k].datea,date2)<0) )
                    {
                            flag2=0;    // date and time(available) fits in the range entered
                            printf("%s\t",g[i].name);
                            printf("%s\t",g[i].city);
                            printf("\n");
                    }
                }
            } 
        }
    }
    
}


void ClashOfMatches(struct ground_records g[])  // Function f.
{
    char game_namew[20],datew[10],ground_namew[9][20];
    int i=0,flag=0;

    printf("Print NA if you finish with max of 4 entries of ground\n");     //we have considered that max of 4 games the user can check for
    while(i<4)
    {
        scanf("%s",ground_namew[i]);
        i++;
    }
    
    printf("\nEnter the date you want to check for:");
    scanf("%s",datew);
    
    printf("\nEnter the name of game you want to check for:");
    scanf("%s",game_namew);
    
    for(int n=0;n<4;n++)
    {
        for(int j=0;j<9;j++)
        {
            if(strcmp(ground_namew[n],g[j].name)==0)
            {
                for(int k=0;k<3;k++)
                {
                    if(strcmp(g[j].games[k].name_of_game,game_namew)==0)
                    {
                        for(int l=0;l<5;l++)
                        {
                            if(strcmp(g[j].games[k].sch[l].dates,datew)==0)
                            {
                                printf(" %s ",g[j].name);
                                printf(" %s ",g[j].games[k].name_of_game);
                                printf(" %s ",g[j].games[k].sch[l].dates);
                                printf(" %s ",g[j].games[k].sch[l].times);
                                printf("\n");
                            }
                        }
                    }
                }
            }
        }
    }
    
    scanf("%s",game_namew);
    scanf("%s",datew);
    
}


void GiveListOfGroundsHavingAtLeastKMatches(struct ground_records g[])  //Function g.
{
    char sport[5][20],date[10],city[20];
    int value,flag=0,k;
    int no,count=0;
    char ground[N][N];
    
    printf("Enter value of k:");
    scanf("%d",&k);
    
    printf("Enter the date for which you want to check:");
    scanf("%s",date);
    
    printf("Enter the city you want to check for:");
    scanf("%s",city);
    int o=0;
    
    //printf("1-Next sport \n 2-Exit");
    
    for(int i=0;i<5;i++)
    {
        scanf("%s",sport[i]);
    }
    
    
    for(int i=0;i<9 && flag==0;i++)
    {
        flag=0;
        if(strcmp(g[i].city,city)==0)
        {
            for(int j=0;j<5;j++)
            {
                for(int l=0;l<4;l++)
                {
                    value=strcmp(g[i].games[l].name_of_game,sport[j]);
                    if(value==0)
                    {
                        for(int n=0;n<4;n++)
                        {
                            if(strcmp(g[i].games[l].sch[n].dates,date)==0 && value==0 && strcmp(g[i].city,city)==0)
                            {
                                count++;
                                strcpy(ground[o],g[i].name);
                                printf("%s\n",ground[o]);
                                o++;
                            }
                        }
                    }
                }
            }
        }
    }

    if(count==k)
    {
        for(int i=0;i<o;i++)
        {
            printf("\n%s",ground[o]);
        }
        
    }

}


void Merge_self_price(int A[],int mid,int lo,int hi)
{
    int i,j,k;
    i=lo,j=mid+1,k=lo;
    int C[100];
    
    while(i<=mid && j<=hi)
    {
        if(A[i]<A[j])
        {
            C[k]=A[i];
            k++,i++;
        }
        else
        {
            C[k]=A[j];
            k++,j++;
        }
    }
    
    while(i<=mid)
    {
        C[k]=A[i];
        k++,i++;
    }
    
    
    while(j<=hi)
    {
        C[k]=A[j];
        k++,j++;
    }
    
    for(int i=lo;i<=hi;i++)
    {
        A[i]=C[i];
    }
}


void Mergesort_price(int g[],int lo,int hi)
{
    int mid;
    if(lo<hi)
    {
        mid=(lo+hi)/2;
        Mergesort_price(g,lo,mid);
        Mergesort_price(g,mid+1,hi);
        Merge_self_price(g,mid,lo,hi);
    }
}


void SortOnPriceForAGame(struct ground_records g[]) // Function h.
{
    char gamew[20],datew[10],timew[12];
    int o,price,pricearr[20];
    
    printf("Enter the game:");
    scanf("%s",gamew);
    printf("\nEnter the date(DD-MM-YYYY):");
    scanf("%s",datew);
    printf("\nEnter the time(HH:MM):");
    scanf("%s",timew);
    
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(strcmp(g[i].games[j].name_of_game,gamew)==0)
            {
                for(int k=0;k<4;k++)
                {
                    if(strcmp(g[i].games[j].sch[k].dates,datew)==0  && strcmp(g[i].games[j].sch[k].times,timew)==0)
                    {
                        price=g[i].games[j].hourly_rate;
                        pricearr[o]=price;
                        o++;
                    }
                }
            }
        }
    }
    Mergesort_price(pricearr,0,o-1);
    for(int i=0;i<o;i++)
    {
        for(int j=0;j<9;j++) 
        {
            for(int k=0;k<3;k++)
            if(g[j].games[k].hourly_rate==pricearr[i])
            {
            
                printf("%s\t ",g[j].name);
                printf("%s\t",g[j].games[k].name_of_game);
                printf("%d   ",g[j].games[k].hourly_rate);
                printf("\n");
            
            }
        }
    }
}


int main()
{
    int n;
    
    //defining data
    struct ground_records g[9]=
    {
       {.name="Narendra-Modi-Stadium",.city="Ahmedabad",.state="Gujarat",.games[0].name_of_game="Rugby",.games[0].hourly_rate=1000,.games[0].sch[0].dates="5-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="26-11-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="17-12-23",.games[0].sch[1].times="9:00-14:00",.games[0].avlbl[1].datea="10-12-23",.games[0].avlbl[1].timea="9:00-14:00",
     .games[0].sch[2].dates="31-12-23",.games[0].sch[2].times="15:00-20:00",.games[0].avlbl[2].datea="24-12-23",.games[0].avlbl[2].timea="15:00-20:00",
     .games[1].name_of_game="Football",.games[1].hourly_rate=1000,.games[1].sch[0].dates="5-11-23",.games[1].sch[0].times="15:00-20:00",.games[1].avlbl[0].datea="24-12-23",.games[1].avlbl[0].timea="15:00-20:00",
     .games[1].sch[1].dates="17-12-23",.games[1].sch[1].times="15:00-20:00",.games[1].avlbl[1].datea="31-12-23",.games[1].avlbl[1].timea="15:00-20:00",
     .games[1].sch[2].dates="31-12-23",.games[1].sch[2].times="15:00-20:00",.games[1].avlbl[2].datea="3-12-23",.games[1].avlbl[2].timea="9:00-14:00",
     .games[2].name_of_game="Volleyball",.games[2].hourly_rate=1000,.games[2].sch[0].dates="12-11-23",.games[2].sch[0].times="15:00-20:00",.games[2].avlbl[0].datea="5-11-23",.games[2].avlbl[0].timea="15:00-20:00",
     .games[2].sch[1].dates="10-12-23",.games[2].sch[1].times="9:00-14:00",.games[2].avlbl[1].datea="10-12-23",.games[2].avlbl[1].timea="9:00-14:00",
     .games[2].sch[2].dates="24-12-23",.games[2].sch[2].times="15:00-20:00",.games[2].avlbl[2].datea="19-11-23",.games[2].avlbl[2].timea="9:00-14:00",}
     ,{
     .name="Chinna-Swami",.city="Bangalore",.state="Karnataka",.games[0].name_of_game="Football",.games[0].hourly_rate=1000,.games[0].sch[0].dates="19-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="17-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="10-12-23",.games[0].sch[1].times="15:00-20:00",.games[0].avlbl[1].datea="31-12-23",.games[0].avlbl[1].timea="9:00-14:00",
     .games[0].sch[2].dates="24-12-23",.games[0].sch[2].times="15:00-20:00",.games[0].avlbl[2].datea="5-11-23",.games[0].avlbl[2].timea="15:00-20:00",
     .games[1].name_of_game="Cricket",.games[1].hourly_rate=1000,.games[1].sch[0].dates="19-11-23",.games[1].sch[0].times="15:00-20:00",.games[1].avlbl[0].datea="26-11-23",.games[1].avlbl[0].timea="15:00-20:00",
     .games[1].sch[1].dates="31-12-23",.games[1].sch[1].times="15:00-20:00",.games[1].avlbl[1].datea="12-11-23",.games[1].avlbl[1].timea="9:00-14:00",
                                                                                       .games[1].avlbl[2].datea="31-12-23",.games[1].avlbl[2].timea="15:00-20:00"},
     {.name="JSCA-Stadium",.city="Ranchi",.state="Jharkhand",.games[0].name_of_game="Football",.games[0].hourly_rate=1000,.games[0].sch[0].dates="19-11-23",.games[0].sch[0].times="15:00-20:00",.games[0].avlbl[0].datea="10-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="12-11-23",.games[0].sch[1].times="15:00-20:00",.games[0].avlbl[1].datea="19-11-23",.games[0].avlbl[1].timea="9:00-14:00",
     .games[0].sch[2].dates="3-12-23",.games[0].sch[2].times="9:00-14:00",.games[0].avlbl[2].datea="26-11-23",.games[0].avlbl[2].timea="9:00-14:00",
     .games[1].name_of_game="Rugby",.games[1].hourly_rate=1000,.games[1].sch[0].dates="12-11-23",.games[1].sch[0].times="9:00-14:00",.games[1].avlbl[0].datea="17-12-23",.games[1].avlbl[0].timea="15:00-20:00",
     .games[1].sch[1].dates="31-12-23",.games[1].sch[1].times="9:00-14:00",.games[1].avlbl[1].datea="10-12-23",.games[1].avlbl[1].timea="15:00-20:00",
   
      .games[2].name_of_game="Badminton",.games[2].hourly_rate=1000,.games[2].sch[0].dates="3-12-23",.games[2].sch[0].times="15:00-20:00",.games[2].avlbl[0].datea="5-11-23",.games[2].avlbl[0].timea="15:00-20:00",
     .games[2].sch[1].dates="31-12-23",.games[2].sch[1].times="15:00-20:00",.games[2].avlbl[1].datea="10-12-23",.games[2].avlbl[1].timea="9:00-14:00",},

     {.name="Eden-Gardens",.city="Kolkata",.state="West Bengal",.games[0].name_of_game="Football",.games[0].hourly_rate=1000,.games[0].sch[0].dates="5-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="17-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="12-11-23",.games[0].sch[1].times="15:00-20:00",.games[0].avlbl[1].datea="31-12-23",.games[0].avlbl[1].timea="15:00-20:00",
     .games[0].sch[2].dates="26-11-23",.games[0].sch[2].times="15:00-20:00"},

     {.name="Wankhede",.city="Mumbai",.state="Maharashtra",.games[0].name_of_game="Football",.games[0].hourly_rate=1000,.games[0].sch[0].dates="12-11-23",.games[0].sch[0].times="15:00-20:00",.games[0].avlbl[0].datea="10-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="17-12-23",.games[0].sch[1].times="15:00-20:00",.games[0].avlbl[1].datea="24-12-23",.games[0].avlbl[1].timea="9:00-14:00",
                                                                                       .games[0].avlbl[2].datea="26-11-23",.games[0].avlbl[2].timea="15:00-20:00",
     .games[1].name_of_game="Cricket",.games[1].hourly_rate=1000,.games[1].sch[0].dates="12-11-23",.games[1].sch[0].times="9:00-14:00",.games[1].avlbl[0].datea="5-11-23",.games[1].avlbl[0].timea="9:00-14:00",
     .games[1].sch[1].dates="26-11-23",.games[1].sch[1].times="9:00-14:00",.games[1].avlbl[1].datea="24-12-23",.games[1].avlbl[1].timea="15:00-20:00",
     .games[1].sch[2].dates="10-12-23",.games[1].sch[2].times="15:00-20:00"},

     {.name="Jawaharlal-Nehru-Stadium",.city="Pune",.state="Maharashtra",.games[0].name_of_game="Cricket",.games[0].hourly_rate=1000,.games[0].sch[0].dates="12-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="12-11-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="17-12-23",.games[0].sch[1].times="9:00-14:00",.games[0].avlbl[1].datea="31-12-23",.games[0].avlbl[1].timea="15:00-20:00",
                                                                                      .games[0].avlbl[2].datea="10-12-23",.games[0].avlbl[2].timea="9:00-14:00"},
      {.name="Sri-Kaatetrava-Stadium",.city="Bangalore",.state="Karnataka",.games[0].name_of_game="LawnTennis",.games[0].hourly_rate=1000,.games[0].sch[0].dates="19-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="17-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="26-11-23",.games[0].sch[1].times="9:00-14:00",.games[0].avlbl[1].datea="31-12-23",.games[0].avlbl[1].timea="15:00-20:00",
     .games[0].sch[2].dates="10-12-23",.games[0].sch[2].times="15:00-20:00",
      .games[1].name_of_game="Volleyball",.games[1].hourly_rate=1000,.games[1].sch[0].dates="3-12-23",.games[1].sch[0].times="15:00-20:00",.games[1].avlbl[0].datea="19-11-23",.games[1].avlbl[0].timea="9:00-14:00",
     .games[1].sch[1].dates="24-12-23",.games[1].sch[1].times="9:00-14:00",.games[1].avlbl[1].datea="12-11-23",.games[1].avlbl[1].timea="15:00-20:00",
                                                                                      .games[1].avlbl[2].datea="17-12-23",.games[1].avlbl[2].timea="15:00-20:00"
     },

     {.name="EkaArena",.city="Ahmedabad",.state="Gujarat",.games[0].name_of_game="Football",.games[0].hourly_rate=1000,.games[0].sch[0].dates="19-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="12-11-23",.games[0].avlbl[0].timea="15:00-20:00",
                                                                                      .games[0].avlbl[1].datea="26-11-23",.games[0].avlbl[1].timea="15:00-20:00",
                                                                                      .games[0].avlbl[2].datea="17-12-23",.games[0].avlbl[2].timea="9:00-14:00",
      .games[1].name_of_game="Cricket",.games[1].hourly_rate=1000,.games[1].sch[0].dates="12-11-23",.games[1].sch[0].times="15:00-20:00",.games[1].avlbl[0].datea="5-11-23",.games[1].avlbl[0].timea="9:00-14:00",
     .games[1].sch[1].dates="24-12-23",.games[1].sch[1].times="15:00-20:00",.games[1].avlbl[1].datea="24-12-23",.games[1].avlbl[1].timea="9:00-14:00",
 
      .games[2].name_of_game="Basketball",.games[2].hourly_rate=1000,.games[2].sch[0].dates="12-11-23",.games[2].sch[0].times="9:00-14:00",.games[2].avlbl[0].datea="3-12-23",.games[2].avlbl[0].timea="15:00-20:00",
     .games[2].sch[1].dates="10-12-23",.games[2].sch[1].times="9:00-14:00",.games[2].avlbl[1].datea="5-11-23",.games[2].avlbl[1].timea="15:00-20:00",
                                                                          .games[2].avlbl[2].datea="12-11-23",.games[2].avlbl[2].timea="15:00-20:00"},

     {.name="Oval",.city="Mumbai",.state="Maharashtra",.games[0].name_of_game="Cricket",.games[0].hourly_rate=1000,.games[0].sch[0].dates="19-11-23",.games[0].sch[0].times="9:00-14:00",.games[0].avlbl[0].datea="17-12-23",.games[0].avlbl[0].timea="9:00-14:00",
     .games[0].sch[1].dates="10-12-23",.games[0].sch[1].times="9:00-14:00",.games[0].avlbl[1].datea="31-12-23",.games[0].avlbl[1].timea="15:00-20:00",
     .games[0].sch[2].dates="24-12-23",.games[0].sch[2].times="9:00-14:00"}
     };
    struct ground_records g1[9];
    for(int i=0;i<9;i++)
    {
        g1[i]=g[i];
    }
    
    printf("WELCOME USER!!");
    printf("\nThe following are the options availbale for you. You may enter the digit corresponding to the option you desire:\n1.Display data sorted on basis of ground name and city\n2.Lists the games scheduled in the city sorted according to ground name and sport name\n3.List of grounds sorted according to the date and time\n4.List of grounds available on the date and time sorted according to the state and city names\n5.list of unique sports happening in the ground\n6.List of grounds where a particular game can be scheduled to be played at a particular time\n7.List all the clashing matches for a given game on a given date among the list-of-grounds input\n8.List of grounds in the given city having atleast K matches in total (in that city) for any of games\n9.List of grounds sorted based on the prices for the given game on given date and time\n");
    printf("\nEnter the option you desire:");
    scanf("%d",&n);
     
    switch(n)
    {
        case(1):    // basic sorting 
        {
            sortedData(g);
        }
        break;
        case(2):
        {
            Mergesort(g,0,8);
            getFixturesinCity(g);
        }
        break;
        case(3):
        {
            getFixturesSortedonDate(g1);
        }
        break;
        case(4):
        {
            isAvailable(g);
        }
        break;
        case(5):
        {
            UniqueSports(g);
        }
        break;
        case(6):
        {
            FindLocationsForGameInTimeRange(g);
        }
        break;
        case(7):
        {
            ClashOfMatches(g);
        }
        break;
        case(8):
        {
            GiveListOfGroundsHavingAtLeastKMatches(g);
        }
        break;
        case 9:
        {
            SortOnPriceForAGame(g);
        }
        break;
        default:
        printf("Invalid option !!");
    }

    printf("Program ends!!");

    return 0;
}
