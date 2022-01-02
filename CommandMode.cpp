#include "header"
void print_header(){
        ostringstream out;
		struct stat fileStat;
        stat(current_path().filename().c_str(), &fileStat);
        struct passwd *pw = getpwuid(fileStat.st_uid);
		out << "\033[0;32m"<<pw->pw_name << "@"<<current_path().string()<<":"<<"\033[0m";
		cout <<out.str();
}
bool search(path p, string keyword){
    recursive_directory_iterator r_d_itr(p);
    for (auto e : r_d_itr){
        if (e.path().stem() == keyword){
            return true;
        }
        if(e.is_directory()){
            if(search(e.path(),keyword))return true;
        }
    }
    return false;
}
void processCommand(string command){
    vector <string> tokens;
    stringstream cstream(command);
    string word="";
    int breakSp=1;
    for(int i=0;i<command.size();i++){
        if(command[i]=='\'')breakSp++;
        else if((breakSp&1)&&command[i]==' '){
            if(!word.empty())tokens.push_back(word);
            word="";
        }else word+=command[i];
    }
    if(!word.empty())tokens.push_back(word);
    if(tokens[0]=="copy"){
        int last=tokens.size()-1;
        const auto copyOptions = copy_options::overwrite_existing|copy_options::recursive;
        string dest="";
        dest=(tokens[last][0]=='.'&&tokens[last][1]=='/')?string(current_path())+"/"+tokens[last].substr(2):tokens[last];
        if(dest.back()!='/')dest+='/';

        int doesnotexist=0;
        for(int i=1;i<last;i++){
            if(!directory_entry(tokens[i]).exists()) {
                doesnotexist=1;
                cout <<tokens[i]<<" ";
            }
            else{
                if(directory_entry(tokens[i]).is_directory()){
                    copy(path(string(current_path())+"/"+tokens[i]),path(dest+tokens[i]),copyOptions);
                }
                else copy(path(string(current_path())+"/"+tokens[i]),path(dest),copyOptions);
            }

        }
        if(doesnotexist)cout<<"- File(s)/Directory(s) does not exist in "<<current_path()<<endl;
        else cout<<"Files moved to "<<dest<<" successfully\n";
    }
    else if(tokens[0]=="move"){
        if(!directory_entry(tokens[1]).exists())cout<<"No such File/Directory exist in "<<current_path()<<endl;
        else rename(path(tokens[1]),path(string(tokens[2])+"/"+tokens[1]));
    }
    else if(tokens[0]=="rename"){
        if(!directory_entry(tokens[1]).exists())cout<<"No such File/Directory exist in "<<current_path()<<endl;
        else rename(path(tokens[1]),path(tokens[2]));
    }
    else if(tokens[0]=="create_file"){
	fstream f;
        f.open(tokens[2]+"/"+ tokens[1], ios::app);
        f.close();
    }
    else if(tokens[0]=="create_dir"){
            create_directory(current_path()/tokens[1]);
    }
    else if(tokens[0]=="del_file"){
        if(!directory_entry(tokens[1]).exists())cout<<"No such File exist in "<<current_path()<<endl;
        else remove(path(string(current_path())+"/"+tokens[1]));
    }
    else if(tokens[0]=="del_dir"){
        if(!directory_entry(tokens[1]).exists())cout<<"No such Directory exist in "<<current_path()<<endl;
        else remove_all(path(string(current_path())+"/"+tokens[1]));
    }
    else if(tokens[0]=="goto"){
        if(!directory_entry(tokens[1]).exists())cout<<"No such Directory exist"<<endl;
        else current_path(absolute(path(tokens[1])));
    }
    else if(tokens[0]=="search"){
        cout<<search(current_path(),tokens[1]);
    }
}

bool enterCommandMode(){
    cout << CLEAR;
    print_header();
    string command="";
    while(true){
        char c=cin.get();
        if(c==8||c==127){
            if(command.empty())continue;
            cout<<"\b \b";
            command.pop_back();
        }
        else if(c==10){
            cout<<"\n";
            //enter
            if(command=="q")return true;
            if(command=="usermode")return false;
            processCommand(command);
            command="";
            print_header();

        }
        else if(c==27){}
        else{
            command+=c;
            cout<<c;
        }
    }
    return false;
}
