#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iterator>

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<string>linesFromFile;
    vector<string>v;
    string line;
    int nextGroupOfNums = 1;
    int recipeCounter;
    int ingredientCounter;
    int writtenPortion;
    int desiredPortion;
    int mainElement;
    float mainScaleWeight = 0.0;
    float scalingFactor;
    
    recipeCounter = 1;
    ingredientCounter = 1;
    
    /*ifstream infile("/Users/johnreeves/Desktop/Questions/Question2/question2/question2/recipes-01.in");
    while (!infile.eof()){
        getline(infile, line);
        linesFromFile.push_back(line);
    }*/
    
    while (getline(cin, line)){
        linesFromFile.push_back(line);
    }
    
    //handles the zero case
    if(linesFromFile.size() == 0){
        return 0;
    }
    
    
    for (size_t i=1; i<linesFromFile.size(); ++i) {
        if(linesFromFile[i] == ""){
            break;
        }
        
        if(i == nextGroupOfNums){
            istringstream iss(linesFromFile[i]);
            vector<string>v {istream_iterator<string>{iss}, istream_iterator<string>{}};
            nextGroupOfNums = (int) i + 1 + atoi(v[0].c_str());
            ingredientCounter = atoi(v[0].c_str());
            writtenPortion = atoi(v[1].c_str());
            desiredPortion = atoi(v[2].c_str());
            
            scalingFactor =  (((float)desiredPortion / (float)writtenPortion) * 10) / 10;
            int start = (int)i;
            
            //loop through current i and nextGroupOfNums and look for 100.0 at end of string/element
            for(int x = start; x < nextGroupOfNums; ++x){
                if(linesFromFile[x].substr(linesFromFile[x].length() - 5) == "100.0"){
                    //let's calculate main ingredient scaled weight
                    mainElement = x;
                    istringstream iss(linesFromFile[x]);
                    vector<string>mainIngredientVector {istream_iterator<string>{iss}, istream_iterator<string>{}};
                    mainScaleWeight = scalingFactor * atof(mainIngredientVector[1].c_str());
                    break;
                }
            }
            
            cout<<"Recipe # "<<recipeCounter<<endl;
            recipeCounter++;
            i++;
        }
        
        istringstream iss(linesFromFile[i]);
        vector<string>info {istream_iterator<string>{iss}, istream_iterator<string>{}};
        float newPercentage = atof(info[2].c_str()) / 100;
        cout << info[0] << " " << round((mainScaleWeight * newPercentage) * 10) / 10 << endl;
        
        if(i == nextGroupOfNums-1){
            cout<<"----------------------------------------"<<endl;
        }
    }
    return 0;
}