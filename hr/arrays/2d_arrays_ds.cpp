#include <bits/stdc++.h>

using namespace std;

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
    
    int lines = 6;
    int rows = 6;
    
    int biggest = 0;
    
    int result = 0;
    bool first = true;
    
    for (int l = 0; l <= lines-3; l++) {
        
        for (int r = 0; r <= rows-3; r++) { 
            
            
            for (int i = 0; i < 3; i++) {
                
                if (i == 0 || i == 2) {
                    
                    for (int y = 0; y < 3; y++) {
                        result += arr[l+i][r+y];
                    }
                    
                } else {
                    result += arr[l+1][r+1];
                }
                
            }
            
            if (first) {
                biggest = result;
                first = false;
                result = 0;
            } else {
                if (result > biggest) biggest = result;
                result = 0; 
            }
            
        }
        
    }
    
    return biggest;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
