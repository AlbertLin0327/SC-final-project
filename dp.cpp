#include <bits/stdc++.h>
using namespace std;

vector<double> raw_data[2];

void read(int test_case){
	string filename = "./test_json/";
	filename += to_string(test_case) + "_vocal.json";

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


double mean(vector <double> &V, int size){
	double sum = 0;
	for(int i = 0; i < size; i++)
		sum += V[i];

	return double(sum) / (double)size;
}

double error(vector <double> &V, int size){
	double M = mean(V, size);

	double err = 0;
	for(int i = 0; i < size; i++)
		err += abs(V[i] - M);

	return err;
}

void solve(int test_case){
	vector <double> base;
	vector <double> level;

	vector < tuple < double, double, int > > ans;

	read(test_case);

	int idx = 0;
	int size = raw_data[0].size();

	for(int i = 0; i < size; i++){

		if(raw_data[1][i] == 0 && idx == 0){
			base.clear();
			level.clear();
			continue;
		}
		
		if(idx == 0){
			base.push_back(raw_data[1][i]);
			idx++;
			continue;
		}

		base.push_back(raw_data[1][i]);
		level.push_back(raw_data[1][i]);

		double level_error = error(level, idx);
		double base_error = error(base, idx);

		//cout << level_error << "  " << base_error << endl;

		if(level_error > base_error || raw_data[1][i] == 0 || i == size - 1){
			int m = ceil(mean(base, idx));
			if(!ans.empty() && get<2>(ans.back()) == m)
				get<1>(ans.back()) = raw_data[0][i - 1];
			else{
				auto t = make_tuple(raw_data[0][i - idx], raw_data[0][i - 1], m);
				ans.push_back(t);
			}
			
			level.clear();
			base.clear();
			base.push_back(raw_data[1][i]);
			i--; idx = -1;
		}

		idx++;
	}

	for(int i = 0; i < ans.size(); i++){
		auto c = ans[i];
		cout << "\t\t[" << get<0>(c) << ", " << get<1>(c) << ", " << get<2>(c) << "]";
		if(i != ans.size() - 1)
			cout << ",";
		cout << endl;
	}
	ans.clear();
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
