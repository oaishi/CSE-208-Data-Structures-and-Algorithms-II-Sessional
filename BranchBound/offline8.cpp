#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int key; //key - lower bound
    int level; //set count
    vector<int> cover; //how many covered so far
    vector<int> subsets;
} node ;

class Compare
{
public:
    bool operator() (node x,node y)
    {
        if(x.key>y.key)
            return true;
        return false;
    }
};

int main()
{
    std::priority_queue<node, std::vector<node>, Compare> pq;
    bool flag = true;
    node root;
    root.level = 0;
    root.key = 0;
    pq.push(root);


    vector<bool> flags; // flags to see which are covered
    vector<vector<int> > subset;
    fill(flags.begin(), flags.end(), false);

    int n, m, entry ;
    char tem;
    cin>>n>>m;

    for(int i = 0 ; i<m ; i++)
    {
        vector<int> dummy ;
        do
        {
            scanf("%d%c", &entry, &tem);
            dummy.push_back(entry);
        }
        while(tem!= '\n');
        subset.push_back(dummy);
    }

    node left, right ;
    int level ;
    vector<int> cover ;
    vector<int>::iterator it;
    while (pq.empty() == false)
    {
        level = pq.top().level ;
        cover = pq.top().cover ;
        if(cover.size()==n)
        {
            cout << "Subsets Used : " ;
            for (vector<int>::const_iterator i = pq.top().subsets.begin(); i != pq.top().subsets.end(); ++i)
                std::cout << *i+1 << " - ";
            cout<<endl;
            flag = false;
            break;
        }
        right.level = level + 1;
        left.level = level + 1;
        right.cover = cover ;
        left.cover = cover ;
        right.subsets = pq.top().subsets;
        left.subsets = pq.top().subsets;
        pq.pop();
        left.subsets.push_back(level);
        if(level<m)
        {
            vector<int> np = subset.at(level);
            for(int j=0 ; j<np.size() ; j++) //left's cover set
            {
                it = find (left.cover.begin(), left.cover.end(), np.at(j));
                if (it != left.cover.end())
                {
                    //found
                }
                else
                    left.cover.push_back(np.at(j));
            }
            int maximum = 0;
            int minimum = 0;
            int mini = 0;
            for(int j = level+1; j<subset.size(); j++)
            {
                int sum = subset.at(j).size();
                maximum = max(maximum, sum);
                int sum1 = 0;
                for(int i=0; i<sum; i++)
                {
                    it = find (left.cover.begin(), left.cover.end(), subset.at(j).at(i));
                    if (it != left.cover.end())
                    {
                        //found
                    }
                    else
                        sum1++;
                }
                minimum = max(sum1,minimum);
                int sum2 = 0;
                for(int i=0; i<sum; i++)
                {
                    it = find (right.cover.begin(), right.cover.end(), subset.at(j).at(i));
                    if (it != right.cover.end())
                    {
                        //found
                    }
                    else
                        sum2++;
                }
                mini = max(sum2,mini);

            }
            //if(minimum)
            left.key = ceil((double)n-left.cover.size()+(double)((double)(level+1)/(double)minimum));
            /*else
                left.key = 0;*/
            //if(mini)
            right.key = ceil((double)(n-right.cover.size()+level+1)/(double)mini);
            /*else
                right.key = 0;*/
            pq.push(left);
            pq.push(right);
        }
    }
    if(flag)
        cout<<"No Set Cover Found";
    return 0;
}
