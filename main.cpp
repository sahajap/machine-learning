#include "csvstream.h"
#include <iostream>
#include <cmath>
#include <string>
#include <map>
using namespace std;

class Classifier {
public:
    void creator(char* argv[]);
    void labelMapCreator(vector<string> &words);
    void wordMapCreator(vector<string> &words);
    void mapOfMapCreator(vector<pair<string, string>> &together);
    void postCounter(vector<string> &words);
    void wordCounter(vector<string> &words);
    int get_total_num_posts();
    int get_total_num_words();
    double log_prior(string label);
    double log_likelihood(string word, string label);
    double log_prob_score(vector<string> &words, string label);
    void print_output(int argc, char* argv[]);
    void print_output_no_debug(char* argv[]);
//set word
    //get word
    //set label
    //get label
private:
    map<pair<string,string>, int> bigMap;
    double total_posts;
    double total_words;
    double total_words_with_label;
    double word_with_label_DNE;
    double posts_with_label;
    
    map<string, int> wordMap;
    map<string, int> labelMap;
    vector<pair<string, string>> together;
    vector<pair<string, string>> print_together;
    vector<string> words;
    vector<string> labels;
};

int main (int argc, char *argv[]) {
        
    cout.precision(3);
    int princess = 0;
    
    string debug = "--debug";
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    //CHANGE 4 TO 3
    if (argc == 4 && (strcmp(argv[3], debug.c_str()) != 0)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -12;
    }
    
    if (argc == 4 && (strcmp(argv[3], debug.c_str()) == 0)) {
        princess = 4;
    }
    
    //CHANGE 2 TO 1
    ifstream fileIn;
    fileIn.open(argv[1]);
    if (!fileIn.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        return 5;
    }

    ifstream fileIn2;
    fileIn2.open(argv[2]);
    if (!fileIn2.is_open()) {
    cout << "Error opening " << argv[2] << endl;
        return 6;
    }
    
    Classifier hi;
    hi.creator(argv);
    hi.print_output(princess, argv);

    }

//This function reads in the csvin file and creates vector for
// 1. label and tag together 2. only labels 3. only tags
void Classifier::creator(char* argv[]) {
    //CHANGE 2 TO 1
    csvstream csvin(argv[1]);
    
    map<string, string> input;
    
    while (csvin >> input) {
        print_together.push_back(std::make_pair((input["tag"]),(input["content"])));
        labels.push_back(input["tag"]);
        string text = input["content"];
        istringstream iss(text);
        vector<std::string> result(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());
        //delete duplicates
        sort(result.begin(),result.end() );
        result.erase( unique(result.begin(), result.end()), result.end());
        
        for (int i = 0; i < result.size(); i++) {
            together.push_back(std::make_pair((input["tag"]),(result[i])));
        }
        words.insert(words.end(), result.begin(), result.end());
    }
    labelMapCreator(labels);
    postCounter(labels);
    wordMapCreator(words);
    mapOfMapCreator(together);
}

void Classifier::labelMapCreator(vector<string> &words) {
    for (const auto &word: words) {
        labelMap[word] += 1;
    }
}

void Classifier::wordMapCreator(vector<string> &words) {
    for (const auto &word: words) {
        wordMap[word] += 1;
    }
}

void Classifier::mapOfMapCreator(vector<pair<string, string>> &bigstring) {
    for (const auto &penguin: bigstring) {
        bigMap[penguin] += 1;
//            const auto word = penguin.first;
//        const auto word2 = penguin.second;
//            cout << word << " " << word2 << endl;
    }
}

//DUPLICATE FIGURE OUT HOW TO CONSOLIDATE INTO ONE FUNCTION
void Classifier::postCounter(vector<string> &words) {
    int counter = 0;
    for (int i = 0; i < words.size(); i++) {
        counter++;
    }
    total_posts = counter;
}

//DUPLICATE FIGURE OUT HOW TO CONSOLIDATE INTO ONE FUNCTION
void Classifier::wordCounter(vector<string> &words) {
    int counter = 0;
    for (int i = 0; i < words.size(); i++) {
        counter++;
    }
    total_words = counter;
}

int Classifier::get_total_num_posts() {
    return total_posts;
}

int Classifier::get_total_num_words() {
    return total_words;
}

double Classifier::log_prior(string label) {
    std::map<string,int>::iterator it;
    it = labelMap.find(label);
    posts_with_label = (*it).second;
    
    double num = (posts_with_label/total_posts);
    
    return log(num);
}

double Classifier::log_likelihood(string word, string label) {
    pair<string, string> happy;
    happy.first = label;
    happy.second = word;
    
    std::map<string,int>::iterator it3;
    it3 = labelMap.find(label);
    posts_with_label = (*it3).second;
    
    std::map<string,int>::iterator it;
    it = wordMap.find(word);
    word_with_label_DNE = (*it).second;
    
    std::map<pair<string,string>, int>::iterator it2;
    it2 = bigMap.find(happy);
    total_words_with_label = (*it2).second;
    
    
    if (wordMap.find(word) == wordMap.end()) {
        return log(1/total_posts);
    }
    else if (bigMap.find(happy) == bigMap.end()) {
        return log(word_with_label_DNE/total_posts);
    }
    else {
        return log(total_words_with_label/posts_with_label);
    }
}

double Classifier::log_prob_score(vector<string> &words, string label) {
    double total_log_like = 0;
    for (int i = 0; i < words.size(); i++) {
        total_log_like += log_likelihood(words[i], label);
    }
    return (log_prior(label) + total_log_like);
}

void Classifier::print_output(int num, char* argv[]) {
    string debug = "--debug";
    
    if (num != 4) {
        cout << "trained on " << labels.size() << " examples" << endl << endl;
    }
    else {
        cout << "training data:" << endl;
        for (int i = 0; i < print_together.size(); i++) {
            cout << "  label = " << print_together[i].first << ", " <<
            "content = " << print_together[i].second << endl;
        }
        
        cout << "trained on " << total_posts << " examples" << endl;
        cout << "vocabulary size = " << wordMap.size() << endl << endl;
        
        cout << "classes:" << endl;
        for (auto it = labelMap.begin(); it != labelMap.end(); ++it) {
            cout << "  " << (*it).first << ", " << (*it).second
            << " examples, log-prior = " << log_prior((*it).first) << endl;
        }
        cout << endl;
        
        cout << "classifier parameters:" << endl;
        for (auto it = bigMap.cbegin(); it != bigMap.cend(); ++it) {
            cout << "  " << (*it).first.first << ":" << (*it).first.second <<
            ", count = " << (*it).second << ", log-likelihood = " <<
            log_likelihood((*it).first.second, (*it).first.first) << endl;
        }
    }
    print_output_no_debug(argv);
}
    
void Classifier::print_output_no_debug(char* argv[]) {
    cout << "test data:" << endl;
    csvstream csvin(argv[2]);
    
    map<string, string> input;
    
    double max = -99999;
    string max_label = "";
    int counter = 0;
    int posttot = 0;
    
    while (csvin >> input) {
        max = -9999;
        vector<pair<string, string>> newtogether;

        string shampoo = input["content"];
        istringstream iss2(shampoo);
        vector<std::string> result(std::istream_iterator<std::string>{iss2},
                                   std::istream_iterator<std::string>());
        //delete duplicates
        sort(result.begin(),result.end() );
        result.erase( unique(result.begin(), result.end()), result.end());
        
        for (int i = 0; i < result.size(); i++) {
            newtogether.push_back(std::make_pair((input["tag"]),(result[i])));
        }
        
        for (auto it = labelMap.begin(); it != labelMap.end(); ++it) {
            double probscore = log_prob_score(result, (*it).first);
            if (probscore > max) {
                max = probscore;
                max_label = (*it).first;
            }
        }
        
        cout << "  correct = " << input["tag"] << ", predicted = " <<
        max_label << ", log-probability score = " << max << endl;
        cout << "  content = " << input["content"] << endl << endl;
        
        if (input["tag"] == max_label) {
            counter++;
        }
        posttot++;
    }
    
    cout << "performance: " << counter << " / " << posttot <<
    " posts predicted correctly" << endl;
//    }
}




//need to create function that counts words and creates a map
//need to create function that counts labels and creates a map
//need to create function that counts labels with words and creates a map

//FUNCTION NOT CLASSIFIER - reads in number of
