struct Bank//An array of this struct will be used to store info of each bank.
{
    char* name;//name of bank
    GraphPtr Currency;//all the values of different currency conversions
}

struct HashT;
typedef struct HashT HashTable;
typedef HashTable* HashPtr;
/* This HashTable will be used to register a bank or currency, and assign it a unique key, which can preferably be set
as the order in which they are registered. This unique key will be used to access the arrays in which graphs for each bank
will be store. In case of currencies, this key will be used to store currencies in the graph.
It is easier to deal with numbers, so in short, this hash table turns string names of currencies and banks
into numerical keys and thus making it easier for us to run different algorithms*/
struct HashT
{
  char name[100];//name of the bank/currency(whichever of the two the hashtable is used for)
  int index;/*the unique of the bank/currency added, which is like the roll no. of bank/currency,
  please note that it is 'not' the hash key value*/
  HashPtr next;// for separate chaining

};

HashPtr MakeHashNode(int srno,char* name)// to create a node in hash table
{
    HashPtr P = (HashPtr)malloc(sizeof(HashTable));
    P->index = srno;
    strcpy(name[key]->name, name);
    P->next = NULL;

    return P;

}
/////////////////////////
int hash(char *name)//hash function
{
    long long int hashval = 0, i = 0;
    while (name[i] != '\0')
    {
        hashval = (37 * hashval) + (int)name[i++];
    }
    hashval = hashval % 501; // change according to total number of banks possible (next prime number after that value)
    return hashval;
}
////////////////////////
void AddIntoHashTable(HashPtr table[], char* name, int serial)/*to register a new bank or currency into a
particular hashtable under the unique key"serial"*/
{
    int key=hash(name);
  HashPtr P =  MakeHashNode(serial,name);
  HashPtr dummy = table[key];
  /*To check if in case the given bank already exists in the hash table, in order to avoid duplicates*/
  while(dummy->next!=NULL)
  {
      if(strcmp(dummy->next->name,name)==0)
      return;

      dummy = dummy->next;
  }
/*Duplicate checker ends here, now we register the bank, since it isn't already registered*/
  P->next=table[key]->next;
  table[key]->next=P;

}

int FindUniqueKey(HashPtr table[], char* name)//to find the unique key value of the bank/currency
{
    int key=hash(name);

  HashPtr dummy = table[key];

  while(dummy->next!=NULL)
  {
      if(strcmp(dummy->next->name,name)==0)
      return dummy->next->index;

      dummy = dummy->next;
  }
return -1;//since the given bank/currency isn't registered
}


