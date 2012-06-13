#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define throw_if(condition) if (condition) { throw #condition; }

typedef vector<int> price_list;
typedef vector<int> credit_list;
typedef pair<int,int> two_items;
typedef vector<two_items> solution_list;

two_items purchase(price_list & p, int credit)
{
    for (int i=0; i<p.size(); i++)
    {
        if (p[i] >= credit)
            continue;

        for (int j=i+1; j<p.size(); j++)
        {
            if ( p[j] + p[i] == credit )
                return make_pair(i+1, j+1);
        }
    }

    return make_pair(-1,-1);
}

void read_from_file(const char* name, credit_list & c, vector<price_list> & v)
{
    fstream f(name, ios::in);

    throw_if(!f.is_open());

    int m;
    f >> m;

    while (m--)
    {
        price_list p;

        int credit;
        f >> credit;

        c.push_back(credit);

        int n;
        f >> n;

        while (n--)
        {
            int price;
            f >> price;
            p.push_back(price);
        }

        v.push_back(p);
    }

    f.close();
}

void write_to_file(const char* name, solution_list & s)
{
    fstream f(name, ios::out);

    throw_if(!f.is_open());

    for (int i=0; i<s.size(); i++)
        f << "Case #" << (i+1) << ": " << s[i].first << " " << s[i].second << endl;

    f.close();
}

class print_items
{
    credit_list & c; int j;
public:
    print_items(credit_list & credit) : c(credit), j(0) {}
    void operator() (two_items & i)
    {
        cout << c[j++] << " " << i.first << " " << i.second << endl;
    }
};

int main()
{
    solution_list s;

    credit_list c;

    vector<price_list> v;

    read_from_file("/Users/tyeung/Google Drive/google code jam/Store_Credit/A-small-practice.in", c, v);

    for (int i=0; i<v.size(); i++)
    {
        two_items items = purchase(v[i], c[i]);
        //throw_if(items.first + items.second != c[i]);
        s.push_back(items);
    }

    for_each(s.begin(), s.end(), print_items(c));

    write_to_file("/Users/tyeung/Google Drive/google code jam/Store_Credit/A-small-practice.txt", s);

    return 0;
}
