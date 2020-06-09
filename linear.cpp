#include <bits/stdc++.h>
using namespace std;

// vector to read in the json form input
// the first degree suggest the timeline and the second suggest the pitch height
vector<double> raw_data[2];

// parse the json form input and store in raw_data vector 
void read(int test_case){
	// the file where me store 
	string filename = "./test_json/" + to_string(test_case) + "/" + to_string(test_case) + "_vocal.json";

    string line, test;
    ifstream file(filename);
    assert(file.is_open());

    getline (file, line);
    istringstream in(line);

    // parse the json form file
    int flag = 0;
    while(getline(in, test, ',')){
        if(flag == 0){
            int i = 0;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' )
                test.erase(test.begin() + i);
               
            i = test.length() - 1;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                    test.erase(test.begin() + i);
                    i--;
            }

            raw_data[0].push_back(stod(test));
            flag = 1;
        }
        else{
            int i = 0;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' )
                test.erase(test.begin() + i);
            
            i = test.length() - 1;
            while(test.at(i) == '[' || test.at(i) == ' ' || test.at(i) == ']' ){
                    test.erase(test.begin() + i);
                    i--;
            }
    
            raw_data[1].push_back(stod(test));
            flag = 0;
        }
	}
}

void solve(int test_case){

	// store the pitch which belongs to same group.
	vector <int> base;

	// store the answer of the <starting time, end time, pitch>
	vector < tuple < double, double, double > > ans;
	read(test_case);

	int size = raw_data[0].size();

	for(int i = 0; i < size; i++){

		// get rid of consecutive 0
		if(raw_data[1][i] == 0 && base.size() == 0)
			continue;

		// for the first pitch in a group
		if(base.size() == 0){
			base.push_back(i);
			continue;
		}

		// determine whether the new pitch belongs to this group
		if(base.size() != 0 && fabs(raw_data[1][base[0]] - raw_data[1][i]) < 0.49 && fabs(raw_data[1][base[base.size() - 1]] - raw_data[1][i]) < 0.49)
			base.push_back(i);
		else if(base.size() != 0){

			// store the previous group and start a new one
			// calculate the mean of this group
			double mean = 0;
			for(int k = 0; k < base.size(); k++)
				mean += raw_data[1][base[k]];
			mean /= base.size();

			// if it happens to get the same value as the previous, merge two groups, else make a store the new group
			if(ans.size() != 0 && (fabs(mean - get<2>(ans.back())) < 0.5 || (i != 0 && get<1>(ans.back()) == raw_data[0][base[0] - 1])))
				get<1>(ans.back()) = raw_data[0][base[base.size() - 1]];
			else
				ans.push_back(make_tuple(raw_data[0][base[0]], raw_data[0][base[base.size() - 1]], mean)); 
			base.clear();
		}
	}

	for(int i = 0; i < ans.size(); i++){
		auto c = ans[i];
		cout << "\t\t[" << get<0>(c) << ", " << get<1>(c) << ", " << round(get<2>(c)) << "]";
		if(i != ans.size() - 1)
			cout << ",";
		cout << endl;
	}
	raw_data[0].clear();
	raw_data[1].clear();
}

int main(){
	// output the answer
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