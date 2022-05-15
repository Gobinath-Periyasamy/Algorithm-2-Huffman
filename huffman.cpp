#include<bits/stdc++.h>
using namespace std;


/**********************************
Created on Sat May 07 10:22:15 2022

Name: Gobinath P
Roll No : CS21M501
Huffman Coding and Decoding for given string
************************************/

// To create Tree

class HuffmanTree
{
    public:
        int valuate;
        char character;
        HuffmanTree *left_side;
        HuffmanTree *right_side;

        // Init
        HuffmanTree(int valuate, char c)
        {
            this->valuate = valuate;
            this->character = c;
            this->left_side = NULL;
            this->right_side = NULL;
        }
};



// Declare int at first in pair
// So if we sort, it will sort the respective char in terms of frequency

vector <pair<int, char>> FrequencyDect (string s)
{
    // Map them the same
    map<char, int> mp;
    for (int i = 0; i<s.size();i++)
    {
        // Incremeent the map equivalent to string
        mp[s[i]]++;
    }


    vector <pair<int, char>> v ;
    // loop through all char string to push back
    for (int i = 0; i<s.size();i++)
    {
        if(mp[s[i]]!=0)
        {
            // push back the mp[s[i]]
            v.push_back(make_pair(mp[s[i]],s[i]));
            //set to 0 once push back
            mp[s[i]] = 0;
        }
    }

    // Frequency coutn of each char in given string:
    cout << "Given String's Frequency Count : "<<endl;
    for (int i = 0; i<v.size();i++)
        cout<<v[i].first<<" : "<<v[i].second<<"\t";

    cout << endl;
    return v;
}


//Class to compare and return true for greater a

class Compare
{
    public:
        bool operator() (HuffmanTree* a, HuffmanTree* b)

        {
            if(a->valuate > b->valuate)
                return true;
            else
                return false;
        }
};


void display(priority_queue<HuffmanTree*,  vector<HuffmanTree*>, Compare> &q)
{
    while(q.size())
    {
        cout<<q.top()->character<<" "<<q.top()->valuate<<endl;
        q.pop();
    }
}

HuffmanTree *makeTree(vector<pair<int,char>> &frq)
{
    priority_queue<HuffmanTree*, vector<HuffmanTree*>, Compare> q;
    for (int i=0;i<frq.size();i++)
    {
        q.push(new HuffmanTree(frq[i].first,frq[i].second));
    }
    //display(q);
    while(q.size()>1)
    {
        HuffmanTree *left_side = q.top();
        q.pop();
        HuffmanTree *right_side = q.top();
        q.pop();

        // Addition of left_side value and right_side value
        HuffmanTree *nd = new HuffmanTree(left_side->valuate+right_side->valuate,'~');
        nd->left_side = left_side;
        nd->right_side = right_side;
        q.push(nd);
    }

    return q.top();
}


void InOrder(HuffmanTree *tree)
{
    if(tree)
    {
        InOrder(tree->left_side);
        cout<<tree->valuate<<endl;
        InOrder(tree->right_side);

    }
}

void getValues(HuffmanTree *root,string s,map<char,string>& vtr)
{
    if(!root)
    {
        return;
    }
    if(root->character!='~')
    {
        vtr[root->character]=s;
        return;
    }
    else
    {
        getValues(root->left_side,s+"0",vtr);
        getValues(root->right_side,s+"1",vtr);
    }
}

// Huffman Decoding :

string decode(HuffmanTree *tree, string s, int &i)
{
    string str = "";

    while(i<=s.size())
    {
        //Base case:
        if(tree -> character!='~')
        {
            str += tree -> character;
            return str;
        }
        // If 0 take left_side edge
        else if(s[i]=='0')
        {
            if(tree->left_side)
            {
                tree = tree -> left_side;
                i++;
            }
            else
                return str;

        }

        // If 1 take right_side edge
        else if(s[i]=='1')
        {
            if(tree->right_side)
            {
                tree = tree -> right_side;
                i++;
            }
            else
                return str;
        }
    }
   return "";
}

int main()
{



    cout << "\n*********************************************"<<endl;
    cout << "* Name: Gobinath P                          *"<<endl;
    cout << "* Roll No : CS21M501                        *"<<endl;
    cout << "* Huffman Coding Algorithm                  *"<<endl;
    cout << "*********************************************"<<endl;
    string s;
    cout<< "Please Enter your String : ";
    cin>>s;

    vector <pair<int, char>> frq;
    frq = FrequencyDect(s);

    // Sort the vector pair in terms of Freq:
    sort(frq.begin(),frq.end());

    cout << "Frequency Count and char in Sorted Ascending order: "<<endl;

    for (int i = 0; i<frq.size();i++)
        cout<<frq[i].first<<" : "<<frq[i].second<<"\t";

    cout << endl;

    map<char,string> vtr;
    HuffmanTree *tree = makeTree(frq);
    //InOrder(tree);
    getValues(tree,"",vtr);

    string res = "";
    
    for (auto i:vtr)
    {
        cout<<i.first<<" "<<i.second<<endl;
        //res+=i.second;
    } 


    for (auto i:s)
    {
        res+=vtr[i];
    }
    cout<<"\n*******************************************************"<<endl;
    //cout<<s<<endl;
    cout<< "Huffman Coding : \n";
    cout<< "----------------\n"<< endl;
    cout<<res<<endl;

    string original = "";
    for (int i=0;i<res.size();)
    {
        original += decode(tree, res, i);
    }

    cout<< "\nHuffman Decoding : \n";
    cout<< "------------------\n"<< endl;
    cout<<original<<endl;
    cout<<"\n*******************************************************"<<endl;
    cout << " Time Complexity of the Algorithm is O(N*logN)"<<endl;


    system("PAUSE");

    return EXIT_SUCCESS;
}
