#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <memory>

using namespace std;

vector<vector<string>> db = {
        {"rizz", "rizzler", "rizzgod", "skibidi", "ohio", "sussy", "baka", "impostor", "sigma", "alpha", "beta", "omega", "gigachad", "chad", 
        "blud", "god", "ambatukum", "whopper", "ishowspeed", "mrbeast", "ahh", "bussing", "amogus", "reddit", "zesty", "poggers", "glizzy", "t-pose", "caseoh", 
        "mewing", "mewmaxxing", "rizzmaxxing", "looksmaxxing", "ratio", "L", "redpilled", "bluepilled", "basepilled", "backrooms", 
        "fortnite", "delulu", "based", "goon", "gooning", "fr", "ong", "irl", "npc", "sus", "edging", "mogging", "mogger", "mogmaxxing", "glazing", "glaze",
        "edgemaxxing", "jelqing", "Jelqmaxxing", "yapping", "yap", "yapper", "yappachino", "munting", "gyattdamn", "baddie", "goated", "aura", "slay", "slayed",
        "devoured"},
        {"fanum tax", "duke dennis", "baby gronk", "andrew tate", "omega male", "sigma male", "alpha male", "beta male", "goon cave", "sigma grindset", 
        "smurf cat", "kai cenat", "goofy ahh", "aiden ross", "grimace shake", "sussy impostor", "sussy baka", "lightskin stare", "family guy", "subway surfers",
        "social credit", "battle pass", "bing chilling", "ice spice", "james charles", "rizzing up", "rizz up", "the rizzler", "livyy dunn", "hawk tuah", 
        "edging streak", "freddy fazbear", "peter griffin", "huggy wuggy", "lil bro", "lock in", "quandale dingle", "kumala savesta", "skibidi toilet", 
        "thug shaker", "thug shake", "rizz party", "rizzly bear", "nuh uh", "say gex", "super idol", "uno reverse", "oiled up", "morbin time",
        "josh hutcherson", "kid named"},
        {"only in ohio", "ohio final boss", "level 1 gyat", "level 2 gyat", "level 5 gyat", "level 10 gyat", "level 100 gyat", "level infinite gyat", 
        "family guy compilation", "hit the griddy", "hitting the griddy", "fortnite battle pass", "raid shadow legends", "garten of banban", "in real life",
        "kid named finger", "metal pipe faling", "what the sigma", "better call saul", "mommy long legs"},
        
};

int db_rows = db.size();

vector<float> weights;

random_device dev;
mt19937 rng(dev());


uniform_int_distribution<int> getRandom(0, 100); // 100 is quite arbitrary, I basically want rand without having to include <cstdlib> and <time.h>

unique_ptr<discrete_distribution<int>> getWeightedIndex;

void spewBrainrot(int wordcount)
{
    vector<string> vec;
    for (int i = 0; i < wordcount; i++)
    {   

        int ind = (*getWeightedIndex)(rng);
        if (i + ind + 1 > wordcount) // don't output more words than the stream had
        {   
            ind = wordcount - i - 1;
        }
        vec = db[ind];
        cout << vec[getRandom(rng) % vec.size()];
        if (i < wordcount - ind - 1)
        {
            cout << " ";
        }
        i += ind;
    }
    
    return;
}

bool is_special(char character)
{
    return (ispunct(character) || isdigit(character) || character == '\t');
}

void convertStream(istream *f)
{
    string charstr;
    while (getline(*f, charstr))
    {

        // get number of words
        int wordcount = 0;
        bool FOUND_WORD = false;
        int l = charstr.size();

        for (int ind = 0; ind < l; ind++)
        {
            char character = charstr[ind];
            if (is_special(character)) 
            {
                if (FOUND_WORD)
                {
                    spewBrainrot(wordcount);
                } else if (wordcount > 0)
                {
                    spewBrainrot(wordcount);
                    cout << " ";
                }
                
                cout << character;
                // while the next characters are special, print them
                while (ind < l && is_special(charstr[ind + 1]))
                {
                    ind++;
                    cout << charstr[ind];
                }
                if (ind + 1 < l && !isalpha(charstr[ind + 1]))
                {
                    cout << " ";
                }
                
                wordcount = 0;
                FOUND_WORD = false;

            } else if (isspace(character))
            {
                if (FOUND_WORD)
                {
                    FOUND_WORD = false;
                }

                while (isspace(charstr[ind + 1]))
                {
                    ind++;
                    cout << " ";
                }



            } else if (!isspace(character) && !FOUND_WORD)
            {
                FOUND_WORD = true;
                wordcount++;
            }
        }
        spewBrainrot(wordcount);

        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    // word database things

    vector<string> vec;

    // Count all words in db
    int rotwordcount = 0;
    for (vector vec : db)
    {
        rotwordcount += vec.size();
    }

    // every word should have an equal probability of being chosen, but each row doesnt have the same number of words, 
    // so assign a weightto each row
    for (int i = 0; i < db_rows; i++)
    {
        weights.push_back(((float) db[i].size())/rotwordcount);
    }
    // cout << weights[0] << weights[1] << weights[2] << endl;

    getWeightedIndex = make_unique<discrete_distribution<int>>(weights.begin(), weights.end()); 

    // parse arguments

    if (argc == 1 || string(argv[1]) == "-" || string(argv[1]) == "--")
    {
        //get from stdin
        convertStream(&cin);
    } else {
        //get from file
        ifstream f;
        string fname = argv[1];
        f.open(fname);
        if (!f.is_open())
        {
            cerr << "Could not open file: \"" << fname << "\"" << endl;
            return -1;      
        }
        convertStream(&f);
        f.close();
    }



    cout << endl;
    return 0;
}