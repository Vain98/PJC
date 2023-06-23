#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct Connection
{
    string from;
    string to;
    int duration;
    Connection(string from, string to, int duration)
        : from(from), to(to), duration(duration)
    {
    }
};
ostream& operator<<(ostream& s, const Connection& c)
{
    return s << c.from << "->" << c.to << " : " << c.duration << "  seconds";
}
int main()
{
    map<string, vector<Connection>> m;
    ifstream infile("STL-telephones.dat");
    int time = 0, totalTime = 0;
    string caller = "", to = "", line = "";
    
    while (infile >> caller >> to >> time)
    {
     
        Connection c{ caller, to, time };
        m[caller].push_back(c);
    }

    infile.close();
    string chatterbox;   
    int longestTime = 0;
    
    for (auto elem : m)
    {
        for (auto elem2 : elem.second)
        {
            totalTime = totalTime + elem2.duration;
        }
        if (totalTime > longestTime)
        {
            chatterbox = elem.first;
            longestTime = totalTime;
        }
        line = elem.first + " : " + to_string(totalTime) + "  seconds";
        cout << line << endl;
        totalTime = 0;
    }
    
    line = chatterbox + " chattered for " + to_string(longestTime) + " seconds in " + to_string(m[chatterbox].size()) + " connections.";
    cout << line << endl;
    for (auto elem : m[chatterbox])
    {
        cout << elem << endl;
    }
}
