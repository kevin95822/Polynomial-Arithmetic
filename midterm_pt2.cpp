#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

map<int,int>poly1, poly2, sum;

map<int,int> add(map<int,int>poly1, map<int,int>poly2){
    sum = poly1;
    map<int,int>::iterator it2;
    for(it2 = poly2.begin(); it2 != poly2.end(); it2++){
        if(sum.find(it2->first) == sum.end())sum[it2->first] = 0;

        sum[it2->first] += it2->second;

        if(sum[it2->first] == 0)sum.erase(it2->first);
    }
    return sum;
}

map<int,int> sub(map<int,int>poly1, map<int,int>poly2){
    map<int,int>result = poly1;
    map<int,int>::iterator it2;
    for(it2 = poly2.begin(); it2 != poly2.end(); it2++){
        if(result.find(it2->first) == result.end())result[it2->first] = 0;

        result[it2->first] -= it2->second;

        if(result[it2->first] == 0)result.erase(it2->first);
    }
    return result;
}

map<int,int> mul(map<int,int>poly1, map<int,int>poly2){
    map<int,int>result;
    map<int,int>::iterator it;
    map<int,int>::iterator it2;

    for(it = poly1.begin(); it != poly1.end(); it++){
        for(it2 = poly2.begin(); it2 != poly2.end(); it2++){
            int x = (it->first) + (it2->first);
            if(result.find(x) == result.end())result[x]=0;
            result[x] += (it->second) * (it2->second);
            if(result[x] == 0)result.erase(x);
        }
    }
    return result;
}

int main(){
    ifstream input;
    string second;
    string line1;
    string line2;
    int i = 0;
    int j = 0;
    //length of input line 1 and line2
    //could not figure out a clever way to input the lines into the map thus using this dumb way
    int val[16];
    int val2[6];
    input.open("C:\\Users\\kevin95822\\Desktop\\CS381\\Assignments\\test.txt");

    //if file is not open exit
    if(!input.is_open()){
        cout<<"Fail to open file";
        exit(EXIT_FAILURE);
    }
    else{
        char c;
        while(input.get(c)){
            if(c == '\n'){
                break;
            }
            input>>line1;
            istringstream iss1(line1);
            int v;
            iss1 >> v;
            val[i] = v;
            i++;
        }
        while(input>>second){
            val2[j] = stoi(second);
            j++;
        }

        for(int k = 1; k < sizeof(val)/sizeof(val[0]); k+=2){
            if(poly1.find(val[k]) == poly1.end()){
                poly1.insert(std::pair<int,int>(val[k], val[k-1]));
            }
            else{
                poly1[val[k]] = val[k-1] + poly1.at(val[k]);
            }
        }

         for(int k = 1; k < sizeof(val2)/sizeof(val2[0]); k+=2){
            if(poly2.find(val2[k]) == poly2.end()){
                poly2.insert(std::pair<int,int>(val2[k], val2[k-1]));
            }
            else{
                poly2[val2[k]] = val2[k-1] + poly1.at(val2[k]);
            }
        }

        //test cases
        map<int,int>a = add(poly1,poly2);
        map<int,int>s = sub(poly1,poly2);
        map<int,int>r = mul(poly1,poly2);
        map<int,int>::iterator it1;
        map<int,int>::iterator it2;
        map<int,int>::iterator it3;
        cout<<"Addition result: "<<endl;
        for(it1 = a.begin(); it1 != a.end(); it1++){
            cout<<it1->first<<" "<<it1->second<<'\n';
        }
        cout<<endl;
        cout<<"Subtraction result: "<<endl;
        for(it2 = s.begin(); it2 != s.end(); it2++){
            cout<<it2->first<<" "<<it2->second<<'\n';
        }
        cout<<endl;
        cout<<"Multiplication result: "<<endl;
        for(it3 = r.begin(); it3 != r.end(); it3++){
            cout<<it3->first<<" "<<it3->second<<'\n';
        }
    }
    return 0;
}