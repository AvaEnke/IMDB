/****************************
 *
 * Program 4: IMDB
 *
 * Course: CS 141, Fall 2022
 * System: c++ using CLion
 * Author: Ava Enke, starter code provided by Dr. Sara Riazi
 *
 ***************************/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>
#include<algorithm>
using namespace std;

int run(string titlesFile, string namesFile, string principalsFile);
int menu1(string titlesFile, string principalsFile, string namesFile, string searchKey);
int menu2(string titlesFile, string principalsFile, string namesFile, string searchKey);

struct TitleRecord{
    string titleID;
    string primaryTitle;
    string startYear;
    string genres;
};

struct NameRecord{
    string nameID;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

struct PrincipalRecord{
    string titleID;
    string nameID;
    string character;
};


/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}


/**********************************************************************************************************/


//function to read each string other than header from the title file into a vector.
void readTitle(string readFile, vector<TitleRecord>& Title){

    string x;

    ifstream fin;
    fin.open(readFile);

    if(fin.is_open()){
        getline(fin,x);
        while(!fin.eof()){
            getline(fin,x);
            if (!fin.fail()) {
                vector<string> lineStr;
                splitString(x,'\t',lineStr);

                TitleRecord tempTitle;
                tempTitle.titleID = lineStr.at(0);
                tempTitle.primaryTitle = lineStr.at(2);
                tempTitle.startYear = lineStr.at(5);
                tempTitle.genres = lineStr.at(lineStr.size() - 1);


               Title.push_back(tempTitle);


            }
        }

    }
    fin.close();
}

//function to read each string other than header line from the name file into a vector.
void readName(string readFile, vector<NameRecord>& Name){
    string x;
    ifstream fin;
    fin.open(readFile);

    if(fin.is_open()){
        getline(fin,x);
        while(!fin.eof()){
            getline(fin,x);
            if(!fin.fail()){
                vector<string> lineStr;
                splitString(x,'\t',lineStr);

                NameRecord tempName;
                tempName.nameID = lineStr.at(0);
                tempName.primaryName = lineStr.at(1);
                tempName.birthYear = lineStr.at(2);
                tempName.deathYear = lineStr.at(3);
                tempName.primaryProfession = lineStr.at(4);

                Name.push_back(tempName);
            }
        }
    }
    fin.close();
}

//function to read each string other than header line from principals file into a vector.
void readPrincipals(string readFile, vector<PrincipalRecord>& Principal){
    string x;

    ifstream fin;
    fin.open(readFile);

    if(fin.is_open()){
        getline(fin,x);
        while(!fin.eof()){
            getline(fin,x);
            if(!fin.fail()){
                vector<string> lineStr;
                splitString(x,'\t',lineStr);

                PrincipalRecord tempPrincipal;
                tempPrincipal.titleID = lineStr.at(0);
                tempPrincipal.nameID = lineStr.at(2);
                tempPrincipal.character = lineStr.at((lineStr.size() -1));

                Principal.push_back(tempPrincipal);
            }
        }
    }
    fin.close();
}
int run(string titlesFile, string namesFile, string principalsFile) {
    //Three empty vectors to call and pass by reference in the menu options
    vector<PrincipalRecord> Principal;
    vector<NameRecord> Name;
    vector<TitleRecord> Title;


    //user choice of what to search for or exit, and takes the user search phrase as input
    int menuOption = 0;
    string searchPhrase;
    cout << "Select a menu option:  \n"
         << "   1. Search for movies  \n"
         << "   2. Search for actors/actresses  \n"
         << "   3. Exit  \n"
         << "Your choice -> ";
    cin >> menuOption;


    if (menuOption == 3) {
        exit(0);
    } else if (menuOption == 1) {
        cout << "Enter search phrase: ";
        cin >> searchPhrase;
        cout << endl;
        menu1(titlesFile, principalsFile, namesFile, searchPhrase);
    }
    else if (menuOption == 2) {
        cout << "Enter search phrase: ";
        cin >> searchPhrase;
        cout << endl;
        menu2(titlesFile, principalsFile, namesFile, searchPhrase);
    }
    return 0;
}

int menu1(string titlesFile, string principalsFile, string namesFile, string searchKey) {
    int count = 0;
    int searchNum = 0;
    bool found = true;
    string tempStrLow = "";
    string tempStrUp = "";
    vector<string> searchWords;
    vector<NameRecord> names;
    vector<PrincipalRecord> Principal;
    vector<TitleRecord> compare;
    vector<TitleRecord> Title;
    readName(namesFile,names);
    readTitle(titlesFile, Title);
    readPrincipals(principalsFile,Principal);
    splitString(searchKey, '+', searchWords);

//Changing user search tolower
    for (int i = 0; i < searchWords.size(); i++) {
        for (int j = 0; j < (searchWords.at(i)).size(); j++) {
            searchWords.at(i).at(j) = tolower((searchWords.at(i).at(j)));
        }
    }

    int ind = 0;
    for (int i = 0; i < Title.size(); i++) {
        found = true;
        tempStrLow = "";
        for (int j = 0; j < Title.at(i).primaryTitle.size(); j++) {
            tempStrLow += tolower(Title.at(i).primaryTitle.at(j));
        }

        for (int b = 0; b < searchWords.size(); b++) {
            if (tempStrLow.find(searchWords.at(b)) != string::npos) {
                ind = i;

            } else {
                found = false;
                break;

            }

        }

        if (found) {
            compare.push_back(Title.at(ind));
            cout << count << ":" << "\n"
                 << "Title: " << Title.at(ind).primaryTitle << "\n"
                 << "Year: " << Title.at(ind).startYear << endl;
//
                    for(int z = 0; z < Title.at(i).genres.size();z++){
                        if(Title.at(ind).genres.at(z) == ',') {
                            Title.at(ind).genres.at(z) = ' ';
                        }
                    }
                    cout << "Genre: " << Title.at(ind).genres << '\n'
                         << "---------------" << endl;
            count = count + 1;
        }


    }
    if(compare.size() == 0){
        cout << "No match found!" << endl;
        run(titlesFile, namesFile, principalsFile);
    }

    cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
    cin >> searchNum;
    cout << endl;


        for (int i = searchNum; i < compare.size(); i++) {
            for (int j = 0; j < Principal.size(); j++) {
                if (compare.at(searchNum).titleID == Principal.at(j).titleID) {
                    for (int l = 0; l < names.size(); l++) {
                        if (Principal.at(j).nameID == names.at(l).nameID) {
                            cout  << names.at(l).primaryName << " " << Principal.at(j).character << endl;
                        }
                    }
                }
            }
        }

    return 0;
}

int menu2(string titlesFile, string principalsFile, string namesFile, string searchKey) {
    vector<string> searchWords;
    vector<NameRecord> compare2;
    vector<NameRecord> Names;
    vector<PrincipalRecord> principal;
    vector<TitleRecord> Title;
    bool found2 = true;
    int searchNum2 = 0;
    int count2 = 0;
    string nameLow = "";
    readName(namesFile, Names);
    splitString(searchKey, '+', searchWords);
    readTitle(titlesFile, Title);
    readPrincipals(principalsFile, principal);

//lowering search words
    for (int i = 0; i < searchWords.size(); i++) {
        for (int j = 0; j < (searchWords.at(i)).size(); j++) {
            searchWords.at(i).at(j) = tolower((searchWords.at(i).at(j)));
        }
    }

    int ind2 = 0;
    for (int i = 0; i < Names.size(); i++) {
        found2 = true;
        nameLow = "";
        for (int j = 0; j < Names.at(i).primaryName.size(); j++) {
            nameLow += tolower(Names.at(i).primaryName.at(j));
        }
        for (int b = 0; b < searchWords.size(); b++) {
            if (nameLow.find(searchWords.at(b)) != string::npos) {
                ind2 = i;

            } else {
                found2 = false;
                break;

            }
        }

        if (found2) {
            //what to do about someone like doris day??
            compare2.push_back(Names.at(ind2));
            cout << "---------------" << '\n'
                 << count2 << ":" << '\n'
                 << Names.at(ind2).primaryName << '\n'
                 << Names.at(ind2).primaryProfession << '\n'
                 << '(' << Names.at(ind2).birthYear << '-' << Names.at(ind2).deathYear << ')' << '\n'
                 << "---------------" << endl;
        }
    }
    //how and where to do no macth found
    if(compare2.size() == 0) {
    cout << "No match found!" << endl;
    run(titlesFile, namesFile, principalsFile);
    }
    cout << "Select an actor/actress to see moves (-1 to go back to the previous menu): ";
    cin >> searchNum2;

    for (int i = searchNum2; i < compare2.size(); i++) {
        for (int j = 0; j < principal.size(); j++) {
            if (compare2.at(searchNum2).nameID == principal.at(j).nameID) {
                for (int z = 0; z < Title.size(); z++) {
                    if (principal.at(j).titleID == Title.at(z).titleID) {
                        cout << Title.at(z).primaryTitle << " " <<  Title.at(z).startYear << " " << principal.at(j).character << endl;
                    }
                }
            }
        }
    }



        //how to go back to previous menu

         cout << "Enter a search phrase (type done to go back to the previous menu): ";

        return 0;

}





//runs the main part of the program


    int main() {
        //Change these addresses according to your local machine
        string titlesFile = "movie.titles.tsv";
        string namesFile = "movie.names.tsv";
        string principalsFile = "movie.principals.tsv";


        //DO NOT change the main function. The main function will be removed by the autograder
        run(titlesFile, namesFile, principalsFile);
        return 0;
    }




