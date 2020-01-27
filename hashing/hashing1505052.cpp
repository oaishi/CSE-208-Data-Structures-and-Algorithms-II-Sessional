#include<bits/stdc++.h>
using namespace std;
int wordlength;
int hashlength;
int null = -1;
char word[100];
int option;

typedef struct
{
    string key;
    int value;
} node;

class item
{
public:
    string key;
    int value;
    item * next;

    item(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

item** hashchain;
node *nodes;
node flag;

int number[6]= {1,11,111,1111,11111,111111};

void initialization()
{
    if(option==1||option==3||option==5)
    {
        flag.key="deleted";
        flag.value=-1;
        nodes = new node[hashlength];
        for(int i=0; i<hashlength; i++)
        {
            nodes[i].key = "null";
            nodes[i].value = null;
        }
    }
    else
    {
        hashchain = new item*[hashlength];
        for(int i = 0; i <hashlength; i++)
        {
            hashchain[i] = NULL;
        }
    }
}

int GenerateHashVersionOne(string newword)
{
    string::iterator it;
    int code = 0;
    int init = 0;
    for (it=newword.begin(); it!=newword.end(); ++it)
    {
        char po = (*it);
        int per = po ;
        per = per*number[init%6];
        per = per%hashlength;
        code += per;
        code = code%hashlength;
        init++;
    }
    return code;
}

int GenerateHashVersionTwo(string newword)
{
    string::iterator it;
    int code = 0;
    int init = 0;
    for (it=newword.begin(); it!=newword.end(); ++it)
    {
        int per = (*it);
        per = per*pow(13,init%6);
        per = per%hashlength;
        code += per;
        code = code%hashlength;
        init++;
    }
    return code;
}

int GenerateHashVersionThree(string newword)
{
    string::iterator it;
    int code = 0;
    int init = 0;
    for (it=newword.begin(); it!=newword.end(); ++it)
    {
        int per = (*it);
        per = per*pow(13,init);
        per = per%hashlength;
        code += per;
        code = code%hashlength;
        init++;
        init = (init%6)+1;
    }
    return code;
}

int SearchLinear(string key)
{
    int index ;
    if(option==1)
        index = GenerateHashVersionOne(key) ;
    else if(option==3)
        index = GenerateHashVersionTwo(key) ;
    else if(option==5)
        index = GenerateHashVersionThree(key);
    int i = 0;
    while(nodes[index].key!=flag.key)
    {
        if(nodes[index].key == key)
            return index;
        index++;
        index %= hashlength;
        i++;
        if(i==hashlength)
            return -1;
    }
    return -1;
}


bool SearchChain(string key)
{
    int index;
    if(option==2)
        index = GenerateHashVersionOne(key) ;
    else if(option==4)
        index = GenerateHashVersionTwo(key) ;
    else
        index = GenerateHashVersionThree(key);
    item * root = hashchain[index];
    while(root!=NULL)
    {
        if(root->key == key)
        {
            return true;
        }
        root = root->next;
    }
    return false;
}

bool InsertNode(string key,int value)
{
    node temp;
    temp.key = key;
    int index;
    if(option==1)
        index = GenerateHashVersionOne(key);
    else if(option==3)
        index = GenerateHashVersionTwo(key) ;
    else if(option==5)
        index = GenerateHashVersionThree(key);
    temp.value = value;
        while(nodes[index].key != "null" && nodes[index].value != null
                && nodes[index].key != key
                && nodes[index].key!=flag.key)
        {
            if(nodes[index].key == key)
                return false;
            index++;
            index %= hashlength;
        }

        if(nodes[index].key==key)
            return false;

        nodes[index] = temp;
        return true;
}

void InsertChain(string key,int value)
{
    int index;
    if(option==2)
        index = GenerateHashVersionOne(key);
    else if(option==4)
        index = GenerateHashVersionTwo(key) ;
    else
        index = GenerateHashVersionThree(key);
    item* prev = NULL;
    item* curr = hashchain[index];

    while(curr != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL)
    {
        curr = new item (key,value);
        if(prev == NULL)
        {
            hashchain[index] = curr;
        }
        else
        {
            prev->next = curr;
        }
    }
    else
    {
        curr->value = value;
    }

}


void printHashtable()
{
    if(option==2||option==4||option==6)
    {
        for(int i = 0; i < hashlength; i++)
        {
            cout<<i+1<<": ";
            item* root = hashchain[i];
            while(root!=NULL)
            {
                printf("%d\t",root->value);
                root = root->next;
            }
            cout<<endl;
        }
    }
    else
    {
        for(int i = 0; i < hashlength; i++)
        {
            cout<<i+1<<" : ";
            printf("%d\n",nodes[i].value);
        }
    }
}

void WordGenerator()
{
    int collision = 0;
    vector<int> hashvalues;
    string hashtable;
    srand (0);
    int i=0;
    while(i<hashlength)
    {
        for(int j=0; j<wordlength; j++)
        {
            word[j] = (rand() % 10) + 65;
        }
        hashtable=word;
        if(option==1||option==3||option==5)
        {
            if(InsertNode(hashtable,i))
            {
                i++;
                int value;
                if(option==1)
                    value = GenerateHashVersionOne(hashtable);
                else if(option==3)
                    value = GenerateHashVersionTwo(hashtable) ;
                else
                    value = GenerateHashVersionThree(hashtable);
                if(find(hashvalues.begin(),hashvalues.end(),value)!= hashvalues.end())
                    collision++;
                else
                    hashvalues.push_back(value);
            }
        }
        else if(SearchChain(hashtable)==false)
        {
            InsertChain(hashtable,i);
            i++;
            int value;
            if(option==2)
                value = GenerateHashVersionOne(hashtable);
            else if(option==4)
                value = GenerateHashVersionTwo(hashtable) ;
            else
                value = GenerateHashVersionThree(hashtable);
            if(find(hashvalues.begin(),hashvalues.end(),value)!= hashvalues.end())
                collision++;
            else
                hashvalues.push_back(value);
        }
    }
    cout<<"Collision Count : "<<collision<<endl;
}


void Delete(string key)
{
    if(option==1||option==3||option==5)
    {
        int index = SearchLinear(key);
        if(index!=-1)
            nodes[index]= flag;
    }
    else
    {
        if(SearchChain(key))
        {
            int index ;
            if(option==2)
                index = GenerateHashVersionOne(key) ;
            else if(option==4)
                index = GenerateHashVersionTwo(key) ;
            else
                index = GenerateHashVersionThree(key);

            item * root = hashchain[index];
            item *prev = NULL;
            while(root!=NULL)
            {
                if(root->key == key)
                {
                    root = root->next;
                    if(prev!=NULL)
                        prev->next = root;
                    else
                        hashchain[index]=root;
                    break;
                }
                prev = root;
                root = root->next;
            }
        }
    }
}

//not finished yet
void WordGeneratorSearch()
{
    string hashtable[hashlength];
    srand (1);//65-90
    int i=0;
    for(int i=0; i<hashlength; i++)
    {
        for(int j=0; j<wordlength; j++)
        {
            word[j] = (rand() % 26) + 65;
        }
        hashtable[i]=word;
    }
    if(option==1||option==3||option==5)
    {
        const clock_t begin_time = clock();
        for(int i=0; i<hashlength; i++)
            SearchLinear(hashtable[i]);
        cout<<"timer : "<<float( clock () - begin_time )<<endl;
    }
    else
    {
        const clock_t begin_time = clock();
        for(int i=0; i<hashlength; i++)
            SearchChain(hashtable[i]);
        cout<<"timer : "<<float( clock () - begin_time )<<endl;
    }
}

int main()
{
    cout<<"Enter word length"<<endl;
    cin>>wordlength;
    cout<<"Enter table length"<<endl;
    cin>>hashlength;
    while(1)
    {
        cout<<"1.Press 1 to run linear probing with hash1"<<endl;
        cout<<"2.Press 2 to run separate chaining with hash1"<<endl;
        cout<<"3.Press 3 to run linear probing with hash2"<<endl;
        cout<<"4.Press 4 to run separate chaining with hash2"<<endl;
        cout<<"5.Press 5 to run linear probing with hash3"<<endl;
        cout<<"6.Press 6 to run separate chaining with hash3"<<endl;
        cin>>option;
        if(option>6||option<1)
            break;
        initialization();
        WordGenerator();
        WordGeneratorSearch();
        //printHashtable();
    }

    return 0;
}
