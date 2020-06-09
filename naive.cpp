#include <bits/stdc++.h>
using namespace std;

vector<double> raw_data[2];

void read(int test_case){
	string filename = "./AIcup_testset_ok/";
	filename += to_string(test_case) + "/" + to_string(test_case) + "_vocal.json";

    string line, test;
    ifstream file(filename);
    assert(file.is_open());

    getline (file, line);
    istringstream in(line);

    int con = 0;

    //string::size_type sz;
    while(getline(in, test, ',')){
        if(con == 0){
            //cout << test << endl;
            int i = 0;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                test.erase(test.begin() + i);
                //cout << test << endl;
            }
            i = test.length() - 1;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                    test.erase(test.begin() + i);
                    i --;
                    //cout << test << endl;
            }
            //cout << test << endl;
            raw_data[0].push_back(stod(test));
            con = 1;
        }
        else{
            int i = 0;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                test.erase(test.begin() + i);
            }
            i = test.length() - 1;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                    test.erase(test.begin() + i);
                    i --;
            }
            //cout << test << endl;
            raw_data[1].push_back(stod(test));
            con = 0;
        }
	}
}

void solve(int test_case){

	vector < tuple < double, double, int > > ans;
	read(test_case);

	int size = raw_data[0].size();

	for(int i = 0; i < size; i++){
		if(raw_data[1][i] == 0)
			continue;

		if(ans.size() != 0 && round(raw_data[1][i]) == get<2>(ans.back()))
			get<1>(ans.back()) = raw_data[0][i];
		else
			ans.push_back(make_tuple(raw_data[0][i], raw_data[0][i], round(raw_data[1][i])));
		
	}

	for(int i = 0; i < ans.size(); i++){
		auto c = ans[i];
		cout << "\t\t[" << get<0>(c) << ", " << get<1>(c) << ", " << get<2>(c) << "]";
		if(i != ans.size() - 1)
			cout << ",";
		cout << endl;
	}
	raw_data[0].clear();
	raw_data[1].clear();
}

int main(){
	cout << "{" << endl;
	 for(int i = 1; i <= 1500; i++){
	 	cout << "\t\"" << i << "\":[" << endl;
	 	solve(i);
	 	cout << "\t]";
	 	if(i != 1500)
	 		cout << ",";
	 	cout << endl;
	 }
	cout << "}" << endl;

	 return 0;
}